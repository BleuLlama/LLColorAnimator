#ifndef __LIGHTNING_H__
#define __LIGHTNING_H__


#include "AnimatedValue.h" 

class Lightning {
  private:
    int flashCount = 0;
    int intensity = 0;
    int pindex = 0;

    AnimatedValue *tim;
    AnimatedValue *v;

  public:
    Lightning( );

    void SetTimeout( unsigned long msTime );
    void TriggerFlash();
    void TimerPoll();

    int Pindex() { return this->pindex; }
    
    uint32_t GetColor();
    int GetIntensity() { return this->intensity; }
    
    uint32_t  MakeColor( uint8_t r, uint8_t g, uint8_t b, uint8_t w = 255) {
      return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
    }
};



#endif
