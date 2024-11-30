#ifndef __ARCADE_TUBE_H__
#define __ARCADE_TUBE_H__

#include "AnimatedValue.h"

class ArcadeTube {
  private:
    int idn;
    int primeNumber;
    int phase;
    int animationType;
    uint32_t color;
    uint32_t colorA;
    uint32_t colorB;
    AnimatedValue * v;

    uint32_t themeColorA;
    uint32_t themeColorB;
    uint32_t themeColorSolid;

  public:
    ArcadeTube( int _id, int _primeNumber = 0 );

    void setup();
    void poll();
    
    void SetupNewPhase();
    
    void SetupAnimation( int _type );
    void DoAnimationFrame();

    uint32_t getColor() { return this->color; }
    uint32_t MakeRandomColor(
        unsigned char r0, unsigned char r1,
        unsigned char g0, unsigned char g1,
        unsigned char b0, unsigned char b1 );
    
    static uint32_t  Color( uint8_t r, uint8_t g, uint8_t b, uint8_t w = 255) {
      return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
    }

    static uint32_t numberToColor( int n ) {
      return ArcadeTube::Color((n&0x01)?255:0, (n&0x02)?255:0, (n&0x04)?255:0 );
    }

    uint32_t makePercentColor( float v );
    
};




#endif
