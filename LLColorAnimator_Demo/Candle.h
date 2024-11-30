#ifndef __CANDLE_H__
#define __CANDLE_H__

#include "AnimatedValue.h"

#define k2_Component  // animates with Yellow + Red components
#undef k4_Component   // animates with Red + Orange + Yellow + Yellow components

#ifdef k2_Component
#define kNumComponets (2)
#else
#define kNumComponets (4) 
#endif


class Candle {
  private:
    unsigned long tupdate;

    // use four colors so the averaging is easier.
    uint8_t r[kNumComponets];
    uint8_t g[kNumComponets];
    uint8_t b[kNumComponets];

    AnimatedValue *v[kNumComponets];

  public:
    Candle( );

    void SetColor( int idx, uint8_t r, uint8_t g, uint8_t b );
    
    uint32_t GetColor( int idx = -1 );


    uint32_t  MakeColor( uint8_t r, uint8_t g, uint8_t b, uint8_t w = 255) {
      return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
    }
};




#endif
