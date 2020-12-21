
#include "header.h"

    
Button::Button( int _pin )
  : pin( _pin )
  , isPressing( false )
  , wasPressed( false )
  , nextWait( 0 )
{
  pinMode( this->pin, INPUT_PULLUP );

}

Button::~Button()
{
}

void Button::Poll( void )
{
  if( millis() <= this->nextWait ) {
    return;
  }

  if( !this->isPressing ) {  
    if ( digitalRead( this->pin ) == LOW ) {
      // press start or still pressing...
      this->isPressing = true;
      this->wasStarted = true;
      this->nextWait = millis() + 20;
    }
    
  } else {
    
    if( this->isPressing ) {
      // handle release
      if( digitalRead( this->pin ) == HIGH ) {
        this->wasPressed = true;
        this->isPressing = false;
        this->nextWait = millis() + 20;
      }
    }
  }
}


bool Button::WasStarted( void )
{
  if( this->wasStarted ) {
    this->wasStarted = false;
    return true;
  }
  return false;
}

bool Button::WasPressed( void )
{
  if( this->wasPressed ) {
    this->wasPressed = false;
    return true;
  }
  return false;
}
