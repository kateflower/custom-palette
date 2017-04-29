# palette
Atari Lynx programming tutorial working with the color palette.

Here we show how to use a custom palette.

For your game you need to pick your 16 colors.

The code will first clear the screen, display a header, then print the hex values twice: once against a black background and another time against a white background.


## Requirements

cc65

http://cc65.github.io/cc65

## Environment

export CC65_HOME={cc65 home dir}

## Build

make clean<br />
make all

load the resultant color.lyx file into your emulator


### palette index 

These names are defined in the lynx.h include file.

```
Palette index		Name
0			COLOR_BLACK
1			COLOR_RED
2			COLOR_BLUE
3			COLOR_GREEN
4			COLOR_VIOLET
5			COLOR_CYAN
6			COLOR_PEAGREEN
7			COLOR_GREY
8			COLOR_NAVYBLUE
9			COLOR_LIGHTRED
A			COLOR_LIGHTBLUE
B			COLOR_LIGHTGREEN
C			COLOR_LIGHTPURPLE
D			COLOR_LIGHTCYAN
E			COLOR_YELLOW
F			COLOR_WHITE
```

## References

Coding example are build using the Lynx Programming Tutorial:

https://atarilynxdeveloper.wordpress.com/2012/04/25/programming-tutorial-part-6colors/