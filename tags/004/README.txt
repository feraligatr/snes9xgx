ｭ覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧溜
:::::::::::::::ﾗ::::::::::::   .______   :::::::::::::::::::   _   ::::::::::
|        _________            /   ___ｰ/           -------.    (_)'\ /     `ｰ|
ﾗ       /______ ｰ   ---__---./   /___ _________  /  ---  /    __| / \      ｰｲ
ﾗ      _______\ \ /  ___  //  /____//\_____ ｰ  /---/   / ___    ---         ﾗ
|     ｰ________/ /  / /  //  /__    _______\ \    /   /  \  \  / /        .||
::::::::::::::::/   /::--/_______\::.________/::::/   /:ｭ::\   _  \::::::ﾗ:::
:::::::ｰ:::::::/___\:::::::::::::::::::::::::::::/   /::::/__/   \--::ｭ::::::
ｰ:::::::::::::::::ﾗ:::::::::::::::ｰ::::ﾗ:::::::::\--/::::::::::::::::::ﾗ:::::
ｭ覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧覧藍ﾟrK�

ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                          SNES9XGX v004                        ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'

PLEASE NOTE: THIS DOCUMENT IS A WORK IN PROGRESS

[What's New 004]

- added: option to disable AA filtering 
         (snes graphics 'crisper', AA now default OFF)
- added: mapped zooming and turbo mode to classic controller
- added: preliminary usb support (loading)
- changed: sram and freezes now saved by filename, not internal romname. 
           If you have multiple versions of the same game, you can now have 
           srams and freezes for each version. A prompt to convert to the 
           new naming is provided for sram only.
- changed: by default, autoload/save sram and freeze enabled

[What Was New 003]
- added: alphabetical file sorting
- added: background logo/backdrop + nicer menus
- added: scrolling in ROM selector
- fixed: switching between pal/ntsc ROMS doesn't mess up timings
- fixed: GC controller config works now
- fixed: freeze autoloading on ROM load
- fixed: zipped ROMS should now load in a reasonable time
- fixed: precompiled dols for autosaving to various locations (see readme)
- changed: GC default quickload slot (to sd) (thanks kerframil)
- changed: default load/save dirs are now "/snes9x/roms" and 
           "/snes/save/"  (thanks kerframil)
- changed: Classic X and Y defaults aren't switched
- changed: if autosave is enabled, it doesn't ask to save SRAM 
           anymore. It is saved in the background.
- updated README

[Whats Was New 002]
- added: classic and nunchuk support
- added: all controllers can now be configured
- added: GC version (untested)
- changed: mappings are no longer stored in SRAM, but in config file. 
           This means no per-game configurations, but one global 
           config per controller.
- one makefile to make all versions. (thanks to snes9x143 SVN)


[What Was New 001]
- compiles with latest devkitppc (r15)
- now uses libfat (can use front sd slot on wii)
- updated menu items a bit
- wiimote support
- fixed: autoload sram/freeze
- fixed: rom plays immediately after loading

[older update history at the bottom]


ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                            FEATURES                           ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'
- Based on Snes9x 1.5 - superior ROM compatibility
- Auto Load/Save Freeze States and SRAM
- Custom controller configurations
- Wiimote, Nunchuk, Classic, and Gamecube controller support
- Autodetect PAL/NTSC
- Zip Support
- Open Source!

ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                         SETUP & INSTALLATION                  ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'

Unzip the archive into a folder. You'll find 4 variations of the dol for both 
wii and gamecube versions. The variants auto save and load preferences and sram 
to/from different locations as follows (you can also manually save and load 
SRAM to any location).
[A default version is provided for quick install. See loading from HBC below.]

  filename                        preferences/sram autoloading location
  -------------------------       -------------------------------------
  snes9xGX-00x-sd-xxxx.dol          SD card
  snes9xGX-00x-mcslota-xxxx.dol     Memory card in slot A
  snes9xGX-00x-mcslotb-xxxx.dol     Memory card in slot B
  snes9xGX-00x-smb-xxxx.dol         SMB share (see SMB section below)
//  snes9xGX-00x-noload-xxxx.dol      none - doesn't load prefs nor autosave SRAM

The last part of the filename (shown above as xxxx), denotes the wii and gamecube
versions.

----------------------------
ROMS, Preferences, and Saves:
----------------------------
Your SNES rom images must be in the Super Magicom (SMC) or FIG format. Generally,
all images you find will be in this format, but if you run across one that isn't
please download RTOOL which will allow you to convert the image into SMC format.


    Wii
----------
On the Wii, you can load roms from any SD card (Front SD, SD Gecko, etc).
By default, ROMs are loaded from "snes9x/roms/" and saves and preferences are 
stored in "snes9x/saves/". Therefore, on your SD card, you should have the following
folders:

  snes9x/
       roms/
       saves/


  Gamecube
------------
You can load roms from DVD, SD card or SMB share. If you wish to use an SD card
or SMB share, you must create the same folder tree as above. Put your roms in the 
"snes9x/roms" folder. On DVD you can either place your roms at the top level, or 
optionally you may have an SNESROMS folder at the top level of the DVD, in which 
case the game selectorwill default to showing that folder when first entered. 
If you create a bootable DVD of Snes9xGx you can put roms on the same DVD.

------------------------------
Loading / Running the Emulator:
------------------------------

Via Homebrew Channel:
--------------------
The most popular method of running homebrew on the wii is through the Homebrew
Channel. If you already have the channel installed, just copy over the apps folder
included in the archive into the root of your SD card (the SD autosaving version 
for wii is included in the apps/Snes9xGX/ folder renamed to boot.dol).

Remember to also create the snes9x/roms and snes9x/saves directories. See above.

If you wish to use a version that autosaves to  other available saving locations, 
just choose the appropriate dol, copy it into the apps/Snes9XGX/ folder, and 
RENAME it to boot.dol (remove the other version). Then proceed to copy
the entire apps folder to your sd card and run it with the HBC.

If you haven't installed the homebrew channel yet, read about how to here:
	http://hbc.hackmii.com/


Gamecube:
---------
You can load it via sdload and an SD card in slot A, or by streaming it to your
cube, or by booting a bootable DVD (gamecube only) with it on it. This document doesn't cover
how to do any of that. A good source for information on these topics is the
tehskeen forums:

	http://www.tehskeen.com/forums/
ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                         ABOUT SNES9X                          ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'
Welcome to the revolution in GameCube emulators! SNES9X is by far the most
complete and accurate Super Nintendo Entertainment System emulator to date.
Taking full power of the ATi-GX chipset and packed full of features that are
to die for after playing your games you'll never want to come back to
reality.

SNES9X is a very popular open source emulator mainly for the PC platform, but
has seen many ports to other consoles such as the Nintendo DS, Microsoft XBOX
and now thanks to SoftDev the Nintendo GameCube! This is a straight port and
is not based on any previous SNES emulators that have existed for the
GameCube. You can get more information on SNES9X here from the below URL.
http://snes9x.ipherswipsite.com/

ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                   DEFAULT CONTROLLER MAPPING                  ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'

NOTE: You can change the controller configurations to your liking in the menu
under the Config Controllers option.

Below are the default button mappings for supported controllers. The wiimote
configuration allows you to play with the wiimote held sideways.

Wiimote		SNES				Nunchuk		SNES
---------------------				---------------------
  1		  Y				  Z		  Y
  2		  B				  B		  B
  A		  A				  A		  A
  B		  X				  C		  X
  -		SELECT				  2		SELECT
  +		START				  1		START
HOME	    Emulator menu			HOME	    Emulator menu
		 LT				  -		 LT
		 RT				  +		 RT




Classic		SNES				GC PAD		SNES
---------------------				---------------------
  X		  X				  Y		  Y
  B		  B				  B		  B
  A		  A				  A		  A
  Y		  Y				  X		  X
  -		SELECT				  Z		SELECT
  +		START				 START		START
HOME	    Emulator menu			
 LT		 LT				  LT		 LT
 RT		 RT				  RT		 RT



ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                             ZIP SUPPORT                       ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'

The Zip support in the emulator is courtesy of the zlib library. Currently,
it supports only the Inflate method.

The good news is that this is by far the most common zip method!

You should note also that this implementation assumes that the first file
in each archive is the required rom in smc/fig format.

In an attempt to save you time, we recommend using 7-Zip as the compressor,
as it gives a gain of 5-25% better compression over standard zips. This being
said, you can very well use WinZip or any other zip utility to create your zipped
ROMs.

To use 7-Zip compression on either linux or windows, use the following command:

  7za a -tzip -mx=9 myrom.zip myrom.smc

ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                              MAIN MENU                        ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'

Once the DOL file is loaded you will be presented with main menu where you can
load a ROM, set options for the emulator, set the joypad configuration, save or 
load freezes, manage SRAM, etc.
After loading a game the game will start running immediately. If you have the
auto-load SRAM option enabled it will automatically load SRAM (if it exists)
before starting play. 

You can return to the main menu at any time by pressing
the c-stick (the yellow control stick) to the left, or by pressing L+R+X+Y.
Return to the game by selecting "Resume Game" or by pressing the B button until
play resumes.

ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                             TURBO MODE                        ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'

TurboMode increases the playback speed of the game by about 2x. To use TurboMode
simply press the c-stick (yellow control stick) to the right and hold it right
as long as you want playback to be double-speed. Release the c-stick when you
want normal playback speed to resume.

ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                   IMPORTING AND EXPORTING SRAM                ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'

Snes9xGx 2.0.1 now includes the ability to load SRAM from Snes9x on other
platforms (Mac/PC/Linux/Etc) and to save back to those platforms. To use this
feature simply save or load SRAM to/from SD card or an SMB share.

The only thing to be aware of is that Snes9xGx requires that the SRM file have a
name that is the rom name (not necessarily the same as the file name!) with .SRM
at the end. For example, the game "Super Mario All-Stars + World" has a rom name
of "ALL_STARS + WORLD", so the SRAM file should have the name "ALL_STARS +
WORLD.srm". You can see the rom name for a game by loading the game - the rom
name is shown in the information that is briefly shown at the bottom of the
screen. A perhaps easier way to find the correct name is simply to load the game
and then save SRAM to SD or SMB and look at the filename that Snes9xGx uses.
That's the name you should use when importing an SRAM from another platform.

To use an Snes9xGx SRAM on another platform just do the opposite: save SRAM to
SD or SMB, and then copy that saved SRAM file to the other platform. You may
have to rename the file to be what that version of snes9x expects it to be.

ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                      UPDATE HISTORY (old)                     ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'

[What Was New 2.0.1b8]
* Added: SD slot B options for freezes, sram and loading of roms
* Changed: SMB options no longer displayed in menus when run on a Wii
* Changed: Game auto resumes running after resetting when choosing the "Reset
    Game" menu option
* Fixed (maybe): Reading of DVDs past the 1.36 GB barrier (Wii only) please
    test! - svpe

[What Was New 2.0.1b7]
* Fixed: Zip compressed freezes to memory card could become corrupted as the
    file size changed - fixed this by deleting the existing file before writing
    a new one if the file size increased. If the file got smaller or stayed the
    same the original file is updated, using less of the existing file if the
    actual file size is smaller. A check is made before deleting the existing
    freeze file to ensure that there is enough space available for the new
    file. Note that additional space equivalent to the new file size must be
    available. If not enough space is available the original freeze is retained
    and the user is informed of the lack of space.
* Fixed: If option to auto-load freeze was selected, joypad config would not
    be restored since that is stored in SRAM. Resolved this for now by first
    loading SRAM if any and then loading the freeze. Obviously having to have
    both SRAM and freeze is not ideal, but this gets the job done if you have
    enough space on your memory card, SD card, etc.
* Added prompt when returning to the menu with autosave enabled allowing the
    user choose whether or not to perform the save. Press A to save or B if you
    don't wish to save.
* Added optional verification of Gamecube memory card saves. After writing
    the file it reads it back in and verifies that the written file matches
    what was to be saved. If it doesn't or if there was a problem opening the
    file it reports the problem to the user. Set this option in the preferences
    if desired.
* Added Reset Gamecube/Wii menu item
* Experimental DVD support for reading beyond 1.36 GB barrier on Wii. I have
    no way to test this, so please report on whether or not it works! Based on
    svpe's code.
    
NOTE: due to changes in the settings, this version will reset your emulator
options settings, so if you had saved preferences you will need to make your
changes to the emulator settings again and save them.

[What Was New 2.0.1b6a]
* Fixed: Going up a directory when selecting a rom on a DVD wasn't working
    
[What's Was New 2.0.1b6]
* PAL Wii support - no separate version necessary! - eke-eke
* PAL roms now play at correct speed via internal timer, ntsc roms still use
    more accurate VSYNC timing - eke-eke
* Zipped freezes to memory card - take 9-12 blocks or so - based on denman's
    code
* Added option for auto save and load of freezes. For saving, can do both SRAM
    and Freeze if desired
* Memory card saving and loading shows a progress bar
* More miscellaneous ease-of-use improvements and cleanup
* Fixed: pressing B to get out of a rom file selection screen no longer drops
    you all the way back to the main menu. Now goes back to choice of where to
    load ROM (the "Load from DVD", "Load from SMB"... screen)
* Fixed: loading of joypad configuration in SRAM works again - no longer gets
    messed up

[ What Was New in 2.0.1b5]
* B button implemented in all menus (returns to previous menu)
* Fixed bug when freezing state to SD card - would crash if SD support was not
    previously initialized
* Fixed double A button press needed after manual prefs/sram save to memory card
* Fixed delay after pressing A button after saving freeze to SD card
* Fixed problem of ".srm" SRAM file being created when SRAM was saved with no
    ROM loaded
* Fixed version number in SRAM and preferences
* Minor other code revisions

[ What Was New 2.0.1b1 through 2.0.1b4]
* SRAM saving and loading from snes9x on other platforms via SD card or SMB
* Games now autostart once loaded
* After manually loading SRAM the emulator is automatically reset
* Optional auto-loading of SRAM from memory card, SD or SMB after game loads
* Optional auto-saving of SRAM to memory card, SD or SMB when returning to menu
* TurboMode
* Global emulator preferences
* Menus redesigned (hopefully for the better!)
* Comes in 6 variants, each auto-loading/saving preferences/sram to a different
  location: mcslota, mcslotb, sdslota, sdslotb, smb, and noload
* ROM injector works again
* A number of small improvements and bug fixes
  
[ What Was New in 2.0 WIP6 ]
* Port of SNES9X 1.50
* SMB support
* SD support
* Greatly improved emulation and timing for NTSC roms
* Save states (freezes) to SD and SMB
* Screen zoom
* Improved font and display
* ROM injector
* ... and more ...

[ Features - OLD 1.43 LIST! ]
* Port of SNES9X v1.43
* Fullscreen Graphics
* Sound Emulation
* SRAM Manager
* DVD Loading
* 1-4 Player Support
* Mode 7 Supported
* Super FX Supported
* SDD1, SRTC, SA-1 Supported
* DSP1 & DSP2 Supported
* Partial DSP4 Support
* Supports Hi-Res 512x224 screens
* Joliet Browser
* PAD Configuration saved with SRAM
* Memcard save/load time extended
* Partial Zip support
* Crude Timer
* Sound Sync Option
* Analog Clip
* XenoGC Support (GC-Linux Homebrew DVD Compatibility)


ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                               CREDITS                         ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'

                             Technical Credits

                       Snes9x v1.5.0/1.4.3 - Snes9x Team
                 GameCube Port 2.0 WIP6 and earlier - SoftDev
                 Additional improvements to 2.0 WIP6 - eke-eke
                   GameCube 2.0.1bx enhancements - crunchy2
                         v00x updates - michniewski
                        GX - http://www.gc-linux.org
                        libogc - Shagkur & wintermute


                                 Testing
                     crunchy2 / tehskeen users / others


                              Documentation
                      brakken, crunchy2, michniewski

ﾗ蘭ｭ蘭ｭ蘭ｭ蘭ｭ 妙蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ� ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ蘭ｭ�-ｭ蘭ｭ-抹ｬ
|0Oﾗ�oｷ                                                               ｷo�ﾗO0|
`ｨ物ｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨｨ ｨｨｨｨｨｨｨｨｨｨｨｨｨ'