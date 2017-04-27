#include <stdlib.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <peekpoke.h>


// It is important to realize that changing the palette renders the symbolic color names virtually useless. 
// The names refer to an index, not the actual color. For example, assume you changed the color for index 0 to yellow. 
// The COLOR_BLACK still refers to the color at index 0, which is now yellow. This means when you change the palette
// you need to define your own symbolic names for these.

/*
//#define COLOR_BLACK		0x00
#define COLOR_DARK_RED	0x01
//#define COLOR_BLUE		0x02
//#define COLOR_GREEN		0x03
#define COLOR_DARK_BROWN	0x04
#define COLOR_LIGHT_BROWN	0x05
#define COLOR_DARK_GREY	0x06
//#define COLOR_GREY		0x07
//#define COLOR_BROWN		0x08
#define COLOR_ORANGE		0x09
//#define COLOR_PINK		0x0a
#define COLOR_DARK_YELLOW	0x0b
#define COLOR_DARK_GREEN	0x0c
#define COLOR_YELLOW_GREEN	0x0d
//#define COLOR_YELLOW	0x0e
//#define COLOR_WHITE		0x0f
*/


// enable Mikeys interrupt response
//#define CLI asm("\tcli")

// These header files are related to the processor family, the Lynx and the TGI libraries.


// The code will first clear the screen, display a header, then print the hex values twice: once against 
// a black background and another time against a white background.

//  this array will contain a string “tgi” that indicates that the loading of the driver was successful.
extern char lynxtgi[]; 

// For your game you need to pick your 16 colors that you will use. Once you have these just a 
// little code is required to set the palette. First, declare an array of all values for the 16 colors 
// in the format 0x0GBR (e.g. 0xF0F for yellow).

static int rawpalette[] =  {
  0x0000, 0x011a, 0x0692, 0x0946, 0x0404, 0x0818,
  0x0666, 0x0888, 0x0616, 0x0b7f, 0x066e, 0x0b3b, 
  0x0513, 0x0b55, 0x0f5f, 0x0eee
};

// you need to transfer these integer values to the color addresses: 
// The high bytes go to FDA0-FDAF and the low bytes go to FDB0-FDBF. 
// A little piece of code will help transfer this.

void setpalette(const int* palette)
{
  char index;
  for (index = 0; index < 0x10; index++)
  {
    //The POKE method will stick a byte value into an address. It is available if you include peekpoke.h in your code.
    POKE(0xFDA0 + index, palette[index] >> 8);
    POKE(0xFDB0 + index, palette[index] & 0xFF);
  }
}


void initialize()
{
	// driver for the Tiny Graphics Interface (TGI)
	// allows for 2D graphics primitives like drawing and text 
  	// Lynx file is called lynx-160-102-16.tgi and is part of the Lynx specific CC65 files
	// function call to tgi_install will install the Lynx specific TGI driver
	// Lynx does not have the ability to load a driver dynamically it needs to be linked statically when the game is built.   
	tgi_install(&lynxtgi);

	// performs the initialization of the loaded drivers of which the TGI graphics driver is just one
	// There are two additional drivers (joystick and comlynx) that you can load as well. 
  	tgi_init();

	// represents the CLI assembly instruction for the 65SC02 processor
	// allows you to clear the Interrupt Disable flag of the processor,   
  	CLI();
	
  	while (tgi_busy())  {  };
 
  	tgi_setpalette(tgi_getdefpalette());
  	tgi_setcolor(COLOR_WHITE);
  	tgi_setbgcolor(COLOR_BLACK);
  	tgi_clear();
}

// The code will first clear the screen, display a header, 
// then print the hex values twice: once against a black background and another 
// time against a white background.
void show_palette(const char* header)
{
  char index = 0;
  char text[5];
 
  tgi_clear();
	
  tgi_setbgcolor(COLOR_BLACK);
  tgi_setcolor(COLOR_WHITE);
  tgi_outtextxy(10, 0, header);
 
  tgi_gotoxy(10, 10);
  for (index = 0; index < 16; index++)
  {
    itoa(index, text, 16);
    tgi_setcolor(index);
    tgi_outtext(text);
  }
 
  tgi_setbgcolor(COLOR_WHITE);
  tgi_gotoxy(10, 20);
  for (index = 0; index < 16; index++)
  {
    itoa(index, text, 16);
    tgi_setcolor(index);
    tgi_outtext(text);
  }
 
  tgi_updatedisplay();
  while (tgi_busy());
}



// The entry point is the main function
void main(void)  {	
  	initialize();
	  
	// An infinite loop where we remain forever  
  while (1) {
    //  a call to setpalette is needed, passing in the array of palette color values.
    // After that all is done. The palette has changed.
    setpalette(rawpalette);
    show_palette("Custom palette");
  };

}