#include "Lightning.h"
#include <Adafruit_NeoPixel.h>

#define kNPositions (11)  // kNumberOfLights
 
Lightning::Lightning()
{
  this->v = new AnimatedValue(); // v is used for the flashes
  this->v->Kick();
  this->v->Set(200);

  this->pindex = floor( random( 0, kNPositions ));
  
  this->tim = new AnimatedValue(); // timeout
  this->tim->Kick();
  this->tim->Set(0);
}

void Lightning::TimerPoll()
{
  if( this->tim->GetVal() < 1.0 ) { return; } // timer hasn't timed out yet

  if( this->flashCount <= 0 ) {
    // it was a long timeout that ended
    // start a new flashcount
    this->flashCount = random( 1, 8 );
    
    // pick a new light to start on
    this->pindex = (int) random( 0, kNPositions );
    
  } else {
    // let the lights wander...
    int r = random( 100 );
    if( r > 70 ) { this->pindex = min( kNPositions-1, this->pindex +1 ); }
    if( r < 30 ) { this->pindex = max( 0, this->pindex -1 ); }
  }
  
  // trigger a new flash
  this->TriggerFlash();
  this->flashCount--;
 
  if( this->flashCount > 0 ) {
    // set a short timeout
    this->tim->Set( 100 + random( 0, 100 ));
    
  } else {
    this->tim->Set( 3000 + random( 1000, 3000 ));
    // prep for the next trigger (which light will light up
  }
  
  this->tim->Kick();
}

void Lightning::TriggerFlash()
{
  this->v->Set(100 + random( 1, 300 ));
  this->v->Kick();
  
  this->intensity = 100 + random( 0, 100 );
}


uint32_t Lightning::GetColor()
{ 
  this->TimerPoll();
  
  float intensity = 1.0 - this->v->GetVal();
  int level = 255 * intensity;
  
  return( this->MakeColor( level, level, level ) );
}
