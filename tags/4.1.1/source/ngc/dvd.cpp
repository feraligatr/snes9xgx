/****************************************************************************
 * Snes9x 1.51 Nintendo Wii/Gamecube Port
 *
 * softdev July 2006
 * svpe & crunchy2 June 2007
 * Tantric 2008-2009
 *
 * dvd.cpp
 *
 * DVD I/O functions
 ***************************************************************************/

#include <gccore.h>
#include <ogcsys.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#ifdef HW_RVL
#include <di/di.h>
#endif

#include "snes9xGX.h"
#include "menu.h"
#include "gcunzip.h"
#include "filebrowser.h"
#include "fileop.h"

static int diroffset = 0;
static u64 dvddir = 0; // offset of currently selected file or folder
static int dvddirlength = 0; // length of currently selected file or folder
static u64 dvdrootdir = 0; // offset of DVD root
static int dvdrootlength = 0; // length of DVD root
static bool isWii = false;

#ifdef HW_DOL
/** DVD I/O Address base **/
volatile unsigned long *dvd = (volatile unsigned long *) 0xCC006000;
#endif

/****************************************************************************
 * dvd_read
 *
 * Main DVD function, everything else uses this!
 * returns: 1 - ok ; 0 - error
 ***************************************************************************/
#define ALIGN_FORWARD(x,align) 	((typeof(x))((((uint32_t)(x)) + (align) - 1) & (~(align-1))))
#define ALIGN_BACKWARD(x,align)	((typeof(x))(((uint32_t)(x)) & (~(align-1))))

static int
dvd_read (void *dst, unsigned int len, u64 offset)
{
	if (len > 2048)
		return 0;				/*** We only allow 2k reads **/

	// don't read past the end of the DVD (1.5 GB for GC DVD, 4.7 GB for DVD)
	if((offset < 0x57057C00) || (isWii && (offset < 0x118244F00LL)))
	{
		u8 * buffer = (u8 *)memalign(32, 0x8000);
		u32 off_size = 0;

		DCInvalidateRange ((void *) buffer, len);

		#ifdef HW_DOL
			dvd[0] = 0x2E;
			dvd[1] = 0;
			dvd[2] = 0xA8000000;
			dvd[3] = (u32)(offset >> 2);
			dvd[4] = len;
			dvd[5] = (u32) buffer;
			dvd[6] = len;
			dvd[7] = 3;

			// Enable reading with DMA
			while (dvd[7] & 1);

			// Ensure it has completed
			if (dvd[0] & 0x4)
				return 0;
		#else
			off_size = offset - ALIGN_BACKWARD(offset,0x800);
			if (DI_ReadDVD(
				buffer,
				(ALIGN_FORWARD(offset + len,0x800) - ALIGN_BACKWARD(offset,0x800)) >> 11,
				(u32)(ALIGN_BACKWARD(offset, 0x800) >> 11)
			))
				return 0;
		#endif

		memcpy (dst, buffer+off_size, len);
		free(buffer);
		return 1;
	}

	return 0;
}

/****************************************************************************
 * dvd_buffered_read
 *
 * the GC's dvd drive only supports offsets and length which are a multiple
 * of 32 bytes additionally the max length of a read is 2048 bytes
 * this function removes these limitations
 * additionally the 7zip SDK does often read data in 1 byte parts from the
 * DVD even when it could read 32 bytes. the dvdsf_buffer has been added to
 * avoid having to read the same sector over and over again
 ***************************************************************************/

#define DVD_LENGTH_MULTIPLY 32
#define DVD_OFFSET_MULTIPLY 32
#define DVD_MAX_READ_LENGTH 2048
#define DVD_SECTOR_SIZE 2048

static unsigned char dvdsf_buffer[DVD_SECTOR_SIZE];
static u64 dvdsf_last_offset = 0;
static u64 dvdsf_last_length = 0;

static int dvd_buffered_read(void *dst, u32 len, u64 offset)
{
	int ret = 1;

	// only read data if the data inside dvdsf_buffer cannot be used
	if(offset != dvdsf_last_offset || len > dvdsf_last_length)
	{
		memset(&dvdsf_buffer, '\0', DVD_SECTOR_SIZE);
		ret = dvd_read(&dvdsf_buffer, len, offset);
		dvdsf_last_offset = offset;
        dvdsf_last_length = len;
	}

	memcpy(dst, &dvdsf_buffer, len);
	return ret;
}

/****************************************************************************
 * dvd_safe_read
 *
 * A 'safer' DVD read function
 * This function relies on dvddir (file offset) being prepopulated!
 * returns: 1 - ok ; 0 - error
 ***************************************************************************/
int dvd_safe_read(void *dst_v, u32 len, u64 fileoffset)
{
	u64 offset = dvddir + fileoffset;

	unsigned char buffer[DVD_SECTOR_SIZE]; // buffer for one dvd sector

    // if read size and length are a multiply of DVD_(OFFSET,LENGTH)_MULTIPLY and length < DVD_MAX_READ_LENGTH
    // we don't need to fix anything
    if(len % DVD_LENGTH_MULTIPLY == 0 && offset % DVD_OFFSET_MULTIPLY == 0 && len <= DVD_MAX_READ_LENGTH)
    {
        int ret = dvd_buffered_read(buffer, len, offset);
        memcpy(dst_v, &buffer, len);
        return ret;
    }
    else
    {
        // no errors yet -> ret = 1
        // the return value of dvd_read will be AND'd with ret
        // because dvd_read does return 0 on error and 1 on success and
        // because 1 & 0 = 0 ret will also contain 0 if at least one error
        // occured and 1 otherwise ;)
        int ret = 1; // return value of dvd_read

        // we might need to fix all 3 issues
        unsigned char *dst = (unsigned char *)dst_v; // gcc will not allow to use var[num] on void* types
        u64 bytesToRead; // the number of bytes we still need to read & copy to the output buffer
        u64 currentOffset; // the current dvd offset
        u64 bufferOffset; // the current buffer offset
        u64 i, j, k; // temporary variables which might be used for different stuff
        //	unsigned char buffer[DVD_SECTOR_SIZE]; // buffer for one dvd sector

        currentOffset = offset;
        bytesToRead = len;
        bufferOffset = 0;

        // fix first issue (offset is not a multiply of 32)
        if(offset % DVD_OFFSET_MULTIPLY)
        {
            // calculate offset of the prior 32 byte position
            i = currentOffset - (currentOffset % DVD_OFFSET_MULTIPLY);

            // calculate the offset from which the data of the dvd buffer will be copied
            j = currentOffset % DVD_OFFSET_MULTIPLY;

            // calculate the number of bytes needed to reach the next DVD_OFFSET_MULTIPLY byte mark
            k = DVD_OFFSET_MULTIPLY - j;

            // maybe we'll only need to copy a few bytes and we therefore don't even reach the next sector
            if(k > len)
            {
                k = len;
            }

            // read 32 bytes from the last 32 byte position
            ret &= dvd_buffered_read(buffer, DVD_OFFSET_MULTIPLY, i);

            // copy the bytes to the output buffer and update currentOffset, bufferOffset and bytesToRead
            memcpy(&dst[bufferOffset], &buffer[j], k);
            currentOffset += k;
            bufferOffset += k;
            bytesToRead -= k;
        }

        // fix second issue (more than 2048 bytes are needed)
        if(bytesToRead > DVD_MAX_READ_LENGTH)
        {
            // calculate the number of 2048 bytes sector needed to get all data
            i = (bytesToRead - (bytesToRead % DVD_MAX_READ_LENGTH)) / DVD_MAX_READ_LENGTH;

            // read data in 2048 byte sector
            for(j = 0; j < i; j++)
            {
                ret &= dvd_buffered_read(buffer, DVD_MAX_READ_LENGTH, currentOffset); // read sector
                memcpy(&dst[bufferOffset], buffer, DVD_MAX_READ_LENGTH); // copy to output buffer

                // update currentOffset, bufferOffset and bytesToRead
                currentOffset += DVD_MAX_READ_LENGTH;
                bufferOffset += DVD_MAX_READ_LENGTH;
                bytesToRead -= DVD_MAX_READ_LENGTH;
            }
        }

        // fix third issue (length is not a multiply of 32)
        if(bytesToRead)
        {
            ret &= dvd_buffered_read(buffer, DVD_MAX_READ_LENGTH, currentOffset); // read 32 byte from the dvd
            memcpy(&dst[bufferOffset], buffer, bytesToRead); // copy bytes to output buffer
        }
        return ret;
    }
}

/** Minimal ISO Directory Definition **/
#define RECLEN 0		/* Record length */
#define EXTENT 6		/* Extent */
#define FILE_LENGTH 14		/* File length (BIG ENDIAN) */
#define FILE_FLAGS 25		/* File flags */
#define FILENAME_LENGTH 32	/* Filename length */
#define FILENAME 33		/* ASCIIZ filename */

/** Minimal Primary Volume Descriptor **/
#define PVDROOT 0x9c
static int IsJoliet = 0;

/****************************************************************************
 * Primary Volume Descriptor
 *
 * The PVD should reside between sector 16 and 31.
 * This is for single session DVD only.
 ***************************************************************************/
static int
getpvd ()
{
	int sector = 16;
	u32 rootdir32;
	unsigned char dvdbuffer[2048];

	dvddir = dvddirlength = 0;
	IsJoliet = -1;

	/** Look for Joliet PVD first **/
	while (sector < 32)
	{
		if (dvd_read (&dvdbuffer, 2048, (u64)(sector << 11)))
		{
			if (memcmp (&dvdbuffer, "\2CD001\1", 8) == 0)
			{
				memcpy(&rootdir32, &dvdbuffer[PVDROOT + EXTENT], 4);
				dvddir = (u64)rootdir32;
				dvddir <<= 11;
				memcpy (&dvddirlength, &dvdbuffer[PVDROOT + FILE_LENGTH], 4);
				dvdrootdir = dvddir;
				dvdrootlength = dvddirlength;
				IsJoliet = 1;
				break;
			}
		}
		else
			return 0;			/*** Can't read sector! ***/
		sector++;
	}

	if (IsJoliet > 0)		/*** Joliet PVD Found ? ***/
		return 1;

	sector = 16;

	/*** Look for standard ISO9660 PVD ***/
	while (sector < 32)
	{
		if (dvd_read (&dvdbuffer, 2048, sector << 11))
		{
			if (memcmp (&dvdbuffer, "\1CD001\1", 8) == 0)
			{
				memcpy (&rootdir32, &dvdbuffer[PVDROOT + EXTENT], 4);
				dvddir = (u64)rootdir32;
				dvddir <<= 11;
				memcpy (&dvddirlength, &dvdbuffer[PVDROOT + FILE_LENGTH], 4);
				dvdrootdir = dvddir;
				dvdrootlength = dvddirlength;
				IsJoliet = 0;
				break;
			}
		}
		else
			return 0;			/*** Can't read sector! ***/
		sector++;
	}
	return (IsJoliet == 0);
}

/****************************************************************************
 * MountDVD()
 *
 * Tests if a ISO9660 DVD is inserted and available, and mounts it
 ***************************************************************************/
bool MountDVD(bool silent)
{
	bool res = false;

	if (getpvd())
	{
		return true;
	}
	else
	{
		ShowAction("Loading DVD...");
		#ifdef HW_DOL
		DVD_Mount(); // mount the DVD unit again
		#else
		u32 val;
		DI_GetCoverRegister(&val);
		if(val & 0x1)	// True if no disc inside, use (val & 0x2) for true if disc inside.
		{
			if(!silent)
				ErrorPrompt("No disc inserted!");
			CancelAction();
			return false;
		}
		DI_Mount();
		while(DI_GetStatus() & DVD_INIT) usleep(20000);
		#endif

		if (getpvd())
			res = true;
		else if(!silent)
			ErrorPrompt("Invalid DVD.");
	}
	CancelAction();
	return res;
}

/****************************************************************************
 * getentry
 *
 * Support function to return the next file entry, if any
 * Declared static to avoid accidental external entry.
 ***************************************************************************/
static int
getentry (int entrycount, unsigned char dvdbuffer[])
{
	char fname[512];		/* Huge, but experience has determined this */
	char tmpname[512];
	char *ptr;
	char *filename;
	char *filenamelength;
	char *rr;
	int j;
	u32 offset32;

	if (diroffset >= 2048 || diroffset < 0)
		return 0;

	/** Decode this entry **/
	if (dvdbuffer[diroffset])	/* Record length available */
	{
		/* Update offsets into sector buffer */
		ptr = (char *) &dvdbuffer[0];
		ptr += diroffset;
		filename = ptr + FILENAME;
		filenamelength = ptr + FILENAME_LENGTH;

		/* Check for wrap round - illegal in ISO spec,
		* but certain crap writers do it! */
		if ((diroffset + dvdbuffer[diroffset]) > 2048 || (diroffset + dvdbuffer[diroffset]) < 0)
			return 0;

		if (*filenamelength)
		{
			memset (&fname, 0, 512);

			if (!IsJoliet)			/*** Do ISO 9660 first ***/
			{
				strncpy (fname, filename, 512);
			}
			else
			{			/*** The more tortuous unicode joliet entries ***/
				for (j = 0; j < (*filenamelength >> 1); j++)
				{
					fname[j] = filename[j * 2 + 1];
				}

				fname[j] = 0;

				if (strlen (fname) >= MAXJOLIET)
					fname[MAXJOLIET - 1] = 0;

				if (strlen (fname) == 0)
					fname[0] = filename[0];
			}

			if (strlen (fname) == 0) // root entry
			{
				fname[0] = 0; // we'll skip it by setting the filename to 0 length
			}
			else
			{
				if (fname[0] == 1)
				{
					if(dvddir == dvdrootdir) // at root already, don't show ..
						fname[0] = 0;
					else
						strcpy (fname, "..");
				}
				else
				{
					/*
					* Move *filenamelength to t,
					* Only to stop gcc warning for noobs :)
					*/
					int t = *filenamelength;
					fname[t] = 0;
				}
			}
			/** Rockridge Check **/
			rr = strstr (fname, ";");
			if (rr != NULL)
				*rr = 0;

			BROWSERENTRY * newBrowserList = (BROWSERENTRY *)realloc(browserList, (entrycount+1) * sizeof(BROWSERENTRY));
			if(!newBrowserList) // failed to allocate required memory
			{
				ResetBrowser();
				ErrorPrompt("Out of memory: too many files!");
				return 0;
			}
			else
			{
				browserList = newBrowserList;
			}
			memset(&(browserList[entrycount]), 0, sizeof(BROWSERENTRY)); // clear the new entry

			strncpy (browserList[entrycount].filename, fname, MAXJOLIET);

			if(strcmp(fname,"..") == 0)
			{
				sprintf(browserList[entrycount].displayname, "Up One Level");
			}
			else
			{
				StripExt(tmpname, fname); // hide file extension
				strncpy (browserList[entrycount].displayname, tmpname, MAXJOLIET);
			}

			memcpy (&offset32, &dvdbuffer[diroffset + EXTENT], 4);

			browserList[entrycount].offset = (u64)offset32;
			memcpy (&(browserList[entrycount].length), &dvdbuffer[diroffset + FILE_LENGTH], 4);
			memcpy (&(browserList[entrycount].isdir), &dvdbuffer[diroffset + FILE_FLAGS], 1);

			browserList[entrycount].offset <<= 11;
			browserList[entrycount].isdir = browserList[entrycount].isdir & 2;

			/*** Prepare for next entry ***/

			diroffset += dvdbuffer[diroffset];
			return 1;
		}
	}
	return 0;
}

/****************************************************************************
 * ParseDVDdirectory
 *
 * This function will parse the directory tree.
 * It relies on dvddir and dvddirlength being pre-populated by a call to
 * getpvd, a previous parse or a menu selection.
 *
 * The return value is number of files collected, or -1 on failure.
 ***************************************************************************/
int
ParseDVDdirectory ()
{
	int pdlength;
	u64 pdoffset;
	u64 rdoffset;
	int len = 0;
	int filecount = 0;
	unsigned char dvdbuffer[2048];

	// reset browser
	ResetBrowser();

	pdoffset = rdoffset = dvddir;
	pdlength = dvddirlength;
	filecount = 0;

	/*** Get as many files as possible ***/
	while (len < pdlength)
	{
		if (dvd_read (&dvdbuffer, 2048, pdoffset) == 0)
			return -1;

		diroffset = 0;

		while (getentry (filecount, dvdbuffer))
		{
			if(strlen(browserList[filecount].filename) > 0)
				filecount++;
		}

		len += 2048;
		pdoffset = rdoffset + len;
	}

	// Sort the file list
	qsort(browserList, filecount, sizeof(BROWSERENTRY), FileSortCallback);

	browser.numEntries = filecount;
	return filecount;
}

/****************************************************************************
 * SetDVDdirectory
 * Set the current DVD file offset
 ***************************************************************************/
void SetDVDdirectory(u64 dir, int length)
{
	dvddir = dir;
	dvddirlength = length;
}

/****************************************************************************
 * DirectorySearch
 *
 * Searches for the directory name specified within the current directory
 * Returns the index of the directory, or -1 if not found
 ***************************************************************************/
static int DirectorySearch(char dir[512])
{
	for (int i = 0; i < browser.numEntries; i++ )
		if (strcmp(browserList[i].filename, dir) == 0)
			return i;
	return -1;
}

/****************************************************************************
 * SwitchDVDFolderR
 *
 * Recursively searches for any directory path 'dir' specified
 * Also can be used to find and set the offset for a file
 * Also loads the directory contents via ParseDVDdirectory()
 * It relies on dvddir, dvddirlength, and filelist being pre-populated
 ***************************************************************************/
static bool SwitchDVDFolderR(char * dir, int maxDepth)
{
	if(maxDepth > 8) // only search to a max depth of 8 levels
		return false;

	bool lastdir = false;
	char * nextdir = NULL;
	unsigned int t = strcspn(dir, "/");

	if(t != strlen(dir))
		nextdir = dir + t + 1; // next directory path to find
	else
		lastdir = true;

	dir[t] = 0;

	int dirindex = DirectorySearch(dir);

	if(dirindex >= 0)
	{
		browser.selIndex = dirindex;

		if(browserList[dirindex].isdir) // only parse directories
		{
			UpdateDirName(METHOD_DVD);
			ParseDVDdirectory();
		}
		else
		{
			dvddir = browserList[dirindex].offset;
			dvddirlength = browserList[dirindex].length;
		}

		if(lastdir)
			return true;
		else
			return SwitchDVDFolderR(nextdir, maxDepth++);
	}
	return false;
}

bool SwitchDVDFolder(char origdir[])
{
	// make a copy of origdir so we don't mess with original
	char dir[1024];
	strncpy(dir, origdir, 1024);

	char * dirptr = dir;

	// strip off leading/trailing slashes on the directory path
	// we don't want to screw up our recursion!
	if(dir[0] == '/')
		dirptr = dirptr + 1;
	if(dir[strlen(dir)-1] == '/')
		dir[strlen(dir)-1] = 0;

	// start searching at root of DVD
	dvddir = dvdrootdir;
	dvddirlength = dvdrootlength;
	browser.dir[0] = 0;
	ParseDVDdirectory();

	return SwitchDVDFolderR(dirptr, 0);
}

/****************************************************************************
 * LoadDVDFileOffset
 * This function will load a file from DVD
 * It assumes dvddir and dvddirlength are prepopulated
 ***************************************************************************/
int
LoadDVDFileOffset (unsigned char *buffer, int length)
{
	int result = 0;
	int offset;
	int blocks;
	int i;
	int ret = 0;
	u64 discoffset;
	char readbuffer[2048];

	// How many 2k blocks to read
	blocks = dvddirlength / 2048;
	offset = 0;
	discoffset = dvddir;
	ShowAction ("Loading...");

	if(length > 0 && length <= 2048)
	{
		ret = dvd_read (buffer, length, discoffset);
		if(ret <= 0) // read failure
			goto done;
		else
			result = length;
	}
	else // load whole file
	{
		ret = dvd_read (readbuffer, 2048, discoffset);
		if(ret <= 0) // read failure
			goto done;

		if (IsZipFile (readbuffer))
		{
			result = UnZipBuffer (buffer, METHOD_DVD); // unzip from dvd
		}
		else
		{
			for (i = 0; i < blocks; i++)
			{
				ret = dvd_read (readbuffer, 2048, discoffset);
				if(ret <= 0) // read failure
					goto done;
				memcpy (buffer + offset, readbuffer, 2048);
				offset += 2048;
				discoffset += 2048;
				ShowProgress ("Loading...", offset, length);
			}

			/*** And final cleanup ***/
			if (dvddirlength % 2048)
			{
				i = dvddirlength % 2048;
				ret = dvd_read (readbuffer, 2048, discoffset);
				if(ret <= 0) // read failure
					goto done;
				memcpy (buffer + offset, readbuffer, i);
			}
			result = dvddirlength;
		}
	}
done:
	CancelAction();
	return result;
}

/****************************************************************************
 * LoadDVDFile
 * This function will load a file from DVD, given a filepath
 * It will attempt to find the offset of the file, and if successful it
 * will populate dvddir and dvddirlength, and load the file
 ***************************************************************************/
int
LoadDVDFile(char * buffer, char *filepath, int datasize, bool silent)
{
	int ret = 0;

	// retain original browser information
	char origDir[MAXPATHLEN];
	memset(origDir, 0, MAXPATHLEN);
	strncpy(origDir, browser.dir, MAXPATHLEN);
	int origSelIndex = browser.selIndex;
	int origPageIndex = browser.selIndex;

	if(SwitchDVDFolder(filepath))
		ret = LoadDVDFileOffset ((unsigned char *)buffer, datasize);
	else if(!silent)
		ErrorPrompt("Error loading file!");

	// restore browser information
	memset(browser.dir, 0, MAXPATHLEN);
	strncpy(browser.dir, origDir, MAXPATHLEN);
	browser.selIndex = origSelIndex;
	browser.pageIndex = origPageIndex;

	return ret;
}

/****************************************************************************
 * uselessinquiry
 *
 * As the name suggests, this function is quite useless.
 * It's only purpose is to stop any pending DVD interrupts while we use the
 * memcard interface.
 *
 * libOGC tends to foul up if you don't, and sometimes does if you do!
 ***************************************************************************/
#ifdef HW_DOL
void uselessinquiry ()
{
	dvd[0] = 0;
	dvd[1] = 0;
	dvd[2] = 0x12000000;
	dvd[3] = 0;
	dvd[4] = 0x20;
	dvd[5] = 0x80000000;
	dvd[6] = 0x20;
	dvd[7] = 1;

	while (dvd[7] & 1);
}

/****************************************************************************
 * dvd_motor_off( )
 * Turns off DVD drive motor so it doesn't make noise (Gamecube only)
 ***************************************************************************/
void dvd_motor_off ()
{
	dvd[0] = 0x2e;
	dvd[1] = 0;
	dvd[2] = 0xe3000000;
	dvd[3] = 0;
	dvd[4] = 0;
	dvd[5] = 0;
	dvd[6] = 0;
	dvd[7] = 1; // Do immediate
	while (dvd[7] & 1);

	/*** PSO Stops blackscreen at reload ***/
	dvd[0] = 0x14;
	dvd[1] = 0;
}

/****************************************************************************
 * dvd_driveid
 *
 * Gets and returns the dvd driveid
 ***************************************************************************/

int dvd_driveid()
{
	static unsigned char *inquiry=(unsigned char *)0x80000004;

    dvd[0] = 0x2e;
    dvd[1] = 0;
    dvd[2] = 0x12000000;
    dvd[3] = 0;
    dvd[4] = 0x20;
    dvd[5] = 0x80000000;
    dvd[6] = 0x20;
    dvd[7] = 3;

    while( dvd[7] & 1 );

    DCFlushRange((void *)0x80000000, 32);

    return (int)inquiry[2];
}

#endif

/****************************************************************************
 * SetDVDDriveType()
 *
 * Sets the DVD drive ID for use to determine disc size (1.5 GB or 4.7 GB)
 ***************************************************************************/
void SetDVDDriveType()
{
	#ifdef HW_RVL
	isWii = true;
	#else
	int drvid = dvd_driveid ();
	if ( drvid == 4 || drvid == 6 || drvid == 8 )
		isWii = false;
	else
		isWii = true;
	#endif
}
