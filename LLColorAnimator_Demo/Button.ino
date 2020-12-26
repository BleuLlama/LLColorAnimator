
#include "header.h"

    
Button::Button( int _pin )
  : pin( _pin )
  , isPressing( false )
  , wasPressed( false )
  , nextWait( 0 )
  , startTime( 0 )
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

      this->startTime = millis();
    }
    
  } else {
    
    if( this->isPressing ) {
      // handle release
      if( digitalRead( this->pin ) == HIGH ) {
        this->wasPressed = true;
        this->isPressing = false;
        this->nextWait = millis() + 20;  
        this->startTime = 0;
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


//////////////////////////////////////////////////
// TapTempo class

TapTempo::TapTempo( int _pin )
  : Button( _pin )
  , previousStartTime( 0 )
{
  this->Clear();
}


void TapTempo::Clear( void )
{
  for( int i = 0 ; i < kTempoCt ; i ++ )
  {
    this->taps[ i ] = 0;
  }
}

void TapTempo::AddNow( void )
{
  unsigned long thisDuration = millis() - this->startTime;

  if( thisDuration > 2000 ) {
    // if timer went for > 2 sec, just clear it to start over.
    this->Clear();
  } else {
    // shift them all over...
    for( int i = kTempoCt ; i > 0 ; i-- )
    {
      this->taps[ i ] = this->taps[ i-1 ];
    }
    // store the difference from the past start time to now.
    this->taps[ 0 ] = millis() - this->startTime;
  }
}


void TapTempo::Poll( void )
{
  if( !this->isPressing ) {  
    if ( digitalRead( this->pin ) == LOW ) {
      // press start or still pressing...
      this->AddNow();
      
      this->isPressing = true;
      this->wasStarted = true;

      this->startTime = millis();
    }
    
  } else {
    if( this->isPressing ) {
      if( digitalRead( this->pin ) == HIGH ) {
        this->isPressing = false;
      }
    }
  }
}


unsigned long TapTempo::Get( void )
{
  unsigned long acc = 0;
  int nElem = 0;

  // accumulate all of the valid tap intervals (nonzero)
  for( int i = 0 ; i < kTempoCt ; i ++ ) 
  {
    if( this->taps[i] != 0 ) {
      acc += this->taps[ i ];
      nElem += 1;
    }
  }
  
  // if there are no valid items, just return 0
  if( nElem == 0 ) {
    this->lastGet = 0;
    return 0;
  }

  // require 2 taps to register
  if( nElem < 2 ) {
    return this->lastGet;
  }

  
  this->lastGet = (unsigned long) ( acc/nElem );
  return this->lastGet;
}


/*
unsigned long nextDumpTime = 0;
void TapTempo::Dump( void )
{
  if( millis() >= nextDumpTime ) {
    Serial.print( "TapTempo:    " );
    for( int i=0 ; i < kTempoCt ; i++ ) {
      Serial.print( this->taps[i], DEC );
      Serial.print( "  " );
    }
    Serial.print( "--> " );
    Serial.println( this->Get(), DEC );
  
    nextDumpTime = millis() + 500;
  }
}
*/
