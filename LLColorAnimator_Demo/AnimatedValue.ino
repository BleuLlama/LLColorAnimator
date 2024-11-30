
#include "AnimatedValue.h"

AnimatedValue::AnimatedValue()
{
  this->millisStart = 0;
  this->millisEnd = 0;
  this->randomRange = 250;

  this->vstart = 0.0;
  this->vend = 1.0;
  
  this->Set( 1000 );
}


float AnimatedValue::Get()
{
  unsigned long now = millis();

  if( now > this->millisEnd ) {
    return 1.0;
  }
  return (float)(now - this->millisStart) / (float)this->duration ;
}

void AnimatedValue::Kick( void )
{
  this->millisStart = millis();
  this->millisEnd = this->millisStart + this->duration;
}

void AnimatedValue::Set( unsigned long _duration )
{
  if( _duration > 0 ) {
    this->duration = _duration;
  }

  if( this->randomRange > 0 ) {
    this->duration = this->duration + random( 0, this->randomRange ) - ( this->randomRange / 2 );
  }
}


void AnimatedValue::SetValRange( float startv, float endv ) {
  this->vstart = startv;
  this->vend = endv;
}
    
float AnimatedValue::GetVal()
{
  float p = this->Get();
  if( p > 1.0 ) { p = 1.0; }
  float v = this->vstart + ((this->vend - this->vstart) * p );
  return v;
}
