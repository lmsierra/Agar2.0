#ifndef __CUSTOM_TYPES__
#define __CUSTOM_TYPES__

#include <stdlib.h>

typedef signed   char  int8;
typedef signed   short int16;
typedef signed   int   int32;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

struct Color
{


    static Color RED()        { return Color(255,   0,   0); }
    static Color GREEN()      { return Color(  0, 255,   0); }
    static Color BLUE()       { return Color(  0,   0, 255); }
    static Color YELLOW()     { return Color(255, 255,   0); }
    static Color CYAN()       { return Color(  0, 255, 255); }
    static Color PINK()       { return Color(255,   0, 255); }
    static Color ORANGE()     { return Color(255, 175,   0); }
    static Color PURPLE()     { return Color(175,   0, 255); }
    static Color WHITE()      { return Color(255, 255, 255); }
    static Color BLACK()      { return Color(  0,   0,   0); }
    static Color DARK_GREEN() { return Color(  0, 100,   0); }
    static Color DARK_BLUE()  { return Color(  0,   0, 100); }
    static Color DARK_RED()   { return Color(100,   0,   0); }

    static const int8 NUM_COLORS = 13;

    static Color Rand() { 
        uint8 r = rand() % 255;
        uint8 g = rand() % 255;
        uint8 b = rand() % 255;

        return Color(r, g, b);
    }

    static Color RandAlpha() {
        Color color = Rand();
        color.A = rand() % 255;
        return color;
    }

    static Color RandPredefined(bool blackwhite) {
    
        int num = rand() % ((blackwhite) ? NUM_COLORS : NUM_COLORS - 2);

        switch (num)
        {
        case 0:
            return RED();
            break;
        case 1:
            return GREEN();
            break; 
        case 2:
            return BLUE();
            break;
        case 3:
            return YELLOW();
            break;
        case 4:
            return CYAN();
            break;
        case 5:
            return PINK();
            break;
        case 6:
            return ORANGE();
            break;
        case 7:
            return PURPLE();
            break;
        case 8:
            return DARK_GREEN();
            break;
        case 9:
            return DARK_BLUE();
            break;
        case 10:
            return DARK_RED();
            break;
        case 11:
            return WHITE();
            break;
        case 12:
            return BLACK();
            break;
        default:
            return ORANGE();
            break;
        }
    }

    uint8 R;
    uint8 G;
    uint8 B;
    uint8 A;

    Color()                                   : R(0), G(0), B(0), A(1) {}
    Color(uint8 x, uint8 y, uint8 z)          : R(x), G(y), B(z), A(1) {}
    Color(uint8 x, uint8 y, uint8 z, uint8 a) : R(x), G(y), B(z), A(a) {}
};

#endif  /* __CUSTOM_TYPES__ */