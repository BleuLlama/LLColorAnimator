#include "Candle.h"
#include <Adafruit_NeoPixel.h>

/*

The original code:
  - set up three colors, yellow, red, orange
  - Every 10 ticks, it picks a new random percentage 20-100% (in steps of 10)
  - Then it applies that percentage to the original colors, storing that value
  - Then it determines step values to go from the current color to that color
  - and to transition to that a speed of 300 + 600*brightness percentage (so darker dips go faster
  - then every tick, it adds/subtracts that step to the current to get to that color
  
 */

 
Candle::Candle()
{
  // setup the color components
#ifdef k4_Component
  this->SetColor( 0, 100, 0, 0 );   // red 
  this->SetColor( 1, 60, 30, 0 );   // orange
  this->SetColor( 2, 100, 70, 0 );  // yellow
  this->SetColor( 3, 250, 250, 0 ); // my addition... makes it more yellow, and lets us use a /4 ( >>2 ) to quicken math
#endif

#ifdef k2_Component // vaslty simplified
  this->SetColor( 0, 255, 255, 0 );   // Yellow
  this->SetColor( 1, 255, 0, 0 );     // Red.  that's it.
#endif

  // initialize the animated values we're gonna use
  for( int j = 0 ; j < kNumComponets ; j++ )
  {
    this->v[j] = new AnimatedValue();
    this->v[j]->Kick();
    this->v[j]->Set( 0 );
  }
}


void Candle::SetColor( int idx, uint8_t r, uint8_t g, uint8_t b )
{
  // helper to make setup cleaner.
  this->r[idx] = r;
  this->g[idx] = g;
  this->b[idx] = b;
}


uint32_t Candle::GetColor( int idx )
{ 
  int r,g,b;
  if( idx >= 0 ) {
    // just return the core components.
    return( this->MakeColor( this->r[idx] * v[idx]->GetVal(), this->g[idx]* v[idx]->GetVal(), this->b[idx]* v[idx]->GetVal() ));
  }

  // check and update components, toggle fades 
  for( int j = 0 ; j < kNumComponets ; j++ ) {
    if( v[j]->Get() == 1.0 ) {
      float pcnt = random(2, 11)/10.0;
      
      v[j]->SetValRange( v[j]->GetValEnd(), pcnt );
      v[j]->Set( 200 + random( 800 * pcnt ));
      v[j]->Kick();
    }
  }

  r = g=b=0;

  // accumulate the colors
  for( int j = 0 ; j < kNumComponets ; j++ ) {
    r += this->r[j] * v[j]->GetVal();
    g += this->g[j] * v[j]->GetVal();
    b += this->b[j] * v[j]->GetVal();
  }

  // finally, build the color to return
#ifdef k2_Component
  return this->MakeColor( ((int)r)>>1, ((int)g)>>1, ((int)b)>>1 );  // div by 2
#else
  return this->MakeColor( ((int)r)>>2, ((int)g)>>2, ((int)b)>>2 );  // div by 4
#endif
 
}
