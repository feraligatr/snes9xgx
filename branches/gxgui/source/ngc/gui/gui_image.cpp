/****************************************************************************
 * Snes9x 1.51 Nintendo Wii/Gamecube Port
 *
 * Tantric February 2009
 *
 * gui_image.cpp
 *
 * GUI class definitions
 ***************************************************************************/

#include "gui.h"
/**
 * Constructor for the GuiImage class.
 */

GuiImage::GuiImage(GuiImageData * img)
{
	image = img->GetImage();
	width = img->GetWidth();
	height = img->GetHeight();
	imageangle = 0;
	tile = 0;
}

GuiImage::GuiImage(u8 * img, int w, int h)
{
	image = img;
	width = w;
	height = h;
	imageangle = 0;
	tile = 0;
}

GuiImage::GuiImage(int w, int h, GXColor c)
{
	image = (u8 *)memalign (32, w * h * 4);
	width = w;
	height = h;
	imageangle = 0;
	tile = 0;

	int x, y;

	for(y=0; y < h; y++)
	{
		for(x=0; x < w; x++)
		{
			this->SetPixel(x, y, c);
		}
	}
	DCFlushRange(image, w * h * 4);
}

/**
 * Destructor for the GuiImage class.
 */
GuiImage::~GuiImage()
{
}

u8 * GuiImage::GetImage()
{
	return image;
}

void GuiImage::SetImage(GuiImageData * img)
{
	image = img->GetImage();
	width = img->GetWidth();
	height = img->GetHeight();
}

void GuiImage::SetImage(u8 * img, int w, int h)
{
	image = img;
	width = w;
	height = h;
}

void GuiImage::SetAngle(float a)
{
	imageangle = a;
}

void GuiImage::SetTile(int t)
{
	tile = t;
}

GXColor GuiImage::GetPixel(int x, int y)
{
	u32 offset = (((y >> 2)<<4)*this->GetWidth()) + ((x >> 2)<<6) + (((y%4 << 2) + x%4 ) << 1);
	GXColor color;
	color.a = *(image+offset);
	color.r = *(image+offset+1);
	color.g = *(image+offset+32);
	color.b = *(image+offset+33);
	return color;
}

void GuiImage::SetPixel(int x, int y, GXColor color)
{
	u32 offset = (((y >> 2)<<4)*this->GetWidth()) + ((x >> 2)<<6) + (((y%4 << 2) + x%4 ) << 1);
	*(image+offset) = color.a;
	*(image+offset+1) = color.r;
	*(image+offset+32) = color.g;
	*(image+offset+33) = color.b;
}

void GuiImage::Stripe(int shift)
{
	int x, y;
	GXColor color;
	int alt = 0;

	for(y=0; y < this->GetHeight(); y++)
	{
		if(y % 3 == 0)
			alt ^= 1;

		for(x=0; x < this->GetWidth(); x++)
		{
			color = GetPixel(x, y);

			if(alt)
			{
				if(color.r < 255-shift)
					color.r += shift;
				else
					color.r = 255;
				if(color.g < 255-shift)
					color.g += shift;
				else
					color.g = 255;
				if(color.b < 255-shift)
					color.b += shift;
				else
					color.b = 255;

				color.a = 255;
			}
			else
			{
				if(color.r > shift)
					color.r -= shift;
				else
					color.r = 0;
				if(color.g > shift)
					color.g -= shift;
				else
					color.g = 0;
				if(color.b > shift)
					color.b -= shift;
				else
					color.b = 0;

				color.a = 255;
			}
			SetPixel(x, y, color);
		}
	}
}

/**
 * Draw the button on screen
 */
void GuiImage::Draw()
{
	if(!image || !this->IsVisible())
		return;

	float currScale = this->GetScale();
	int currLeft = this->GetLeft();

	if(tile > 0)
	{
		for(int i=0; i<tile; i++)
			Menu_DrawImg(currLeft+width*i, this->GetTop(), width, height, image, imageangle, currScale, currScale, this->GetAlpha());
	}
	else
	{
		// temporary (maybe), used to correct offset for scaled images
		if(scale != 1)
			currLeft = currLeft - width/2 + (width*scale)/2;

		Menu_DrawImg(currLeft, this->GetTop(), width, height, image, imageangle, currScale, currScale, this->GetAlpha());
	}

	this->UpdateEffects();
}
