
#include "ArcadeTube.h"


//////////////////////////////////////////


ArcadeTube::ArcadeTube( int _id, int _primeNumber )
{
  this->idn = _id;
  this->primeNumber = _primeNumber;
  this->phase = random( -1, 7);
  this->color = ArcadeTube::Color( 0, 0, 0 );

  this->themeColorA = this->MakeRandomColor( 32, 255, 32, 255, 32,255 );
  this->themeColorB = this->MakeRandomColor( 32, 255, 32, 255, 32,255 );
  
  this->themeColorSolid = ArcadeTube::numberToColor( random( 1,7 ));
  
  if( _primeNumber == 0 ) {
    this->primeNumber = random( 100,2000 );
  }

  this->v = new AnimatedValue();
  //this->v->Set( 1000 );
  this->v->Kick();
}


uint32_t ArcadeTube::MakeRandomColor(
    unsigned char r0, unsigned char r1,
    unsigned char g0, unsigned char g1,
    unsigned char b0, unsigned char b1 )
{
  this->color = ArcadeTube::Color( random( r0, r1 ), random( g0, g1 ), random( b0, b1 ) );
  return this->color;
}

/*
 * Modes:
 * Solid color (4+random(4) seconds
 * flash to black (4x/sec)
 * Slow color fade between colors
 */

void ArcadeTube::setup()
{
}


uint32_t ArcadeTube::makePercentColor( float v )
{
  float iv = 1.0 - v;
  
  float rA = this->colorA & 0x0000FF;
  float rB = this->colorB & 0x0000FF;
  float gA = (this->colorA & 0x00FF00) >> 8;
  float gB = (this->colorB & 0x00FF00) >> 8;
  float bA = 0xff & ( (this->colorA & 0xFF0000) >> 16 );
  float bB = 0xff & ( (this->colorB & 0xFF0000) >> 16 );

  uint32_t c = ArcadeTube::Color( 
    (int) ( rA * v + rB * iv ),
    (int) ( gA * v + gB * iv ) ,
    (int) ( bA * v + bB * iv ) 
    );

    return c;
}

#define kType_RandomOrange      (0)
#define kType_DarkCyan500       (1)
#define kType_FlashingColor     (2)
#define kType_FlashingColor     (2)
#define kType_SlowFadeDarkLight (3)
#define kType_SlowFadeLightDark (4)
#define kType_FlashingFast      (5)
#define kType_Off               (6)
#define kType_FlashingRandomColor (7)

void ArcadeTube::SetupAnimation( int _type )
{
  this->animationType = _type;
  
  switch( this->animationType ) {
    case( kType_Off ):
      // black for 1 second
      this->color = ArcadeTube::Color( 0,0,0 );
      this->v->Set( 1000 );
      break;
      
    case( kType_RandomOrange ):
      // random orange for 3 seconds
      this->color = this->MakeRandomColor( 0, 0, 0, 255, 0, 255 );
      this->v->Set( 3000 );
      break;
      
    case( kType_DarkCyan500 ):
      // dark cyan for 1/2 second
      this->MakeRandomColor( 0, 0, 8, 10, 8, 10 );
      this->v->Set( 700 + this->primeNumber );
      break;

    case( kType_FlashingColor ):
      // flashing color
      this->colorA = this->themeColorSolid;
      this->colorB = ArcadeTube::Color( 0, 0, 0 );
      this->v->Set( 1000 );
      break;
      
    case( kType_FlashingRandomColor ):
      // flashing color
      this->colorA = this->MakeRandomColor( 0, 255, 0, 255, 0, 255 );
      this->colorB = ArcadeTube::Color( 0, 0, 0 );
      this->v->Set( 1000 );
      break;
      
    case( kType_SlowFadeDarkLight ):
      // slow fade dark color to light color
      this->colorA = this->MakeRandomColor( 1,2, 1,3, 1,10 );
      this->colorB = this->themeColorA;
      this->v->Set( 8000 );
      break;
      
    case( kType_SlowFadeLightDark ):
      // slow fade light color to dark color
      this->colorA = this->themeColorB;
      this->colorB = ~this->themeColorA;
      this->v->Set( 8000 );
      break;

    case( kType_FlashingFast ):
      this->colorA = ArcadeTube::Color( 0,0,0 );
      this->colorB = ArcadeTube::Color( 255,255,255 );

      this->v->Set( 3000 );
      break;
  }
}

void ArcadeTube::DoAnimationFrame( void )
{
  float v = this->v->Get();
  
  switch( this->animationType ) {
    case( kType_FlashingColor ):
           if( v > 0.8 ) { this->color = this->colorA; }
      else if( v > 0.6 ) { this->color = this->colorB; }
      else if( v > 0.4 ) { this->color = this->colorA; }
      else if( v > 0.2 ) { this->color = this->colorB; }
      else if( v > 0.0 ) { this->color = this->colorA; }
      break;
    
    case( kType_SlowFadeDarkLight ):
    case( kType_SlowFadeLightDark ):
      this->color = this->makePercentColor( v );
      break;

    case( kType_FlashingFast ):
    case( kType_FlashingRandomColor ):
           if( v > 0.9 ) { this->color = this->colorA; }
      else if( v > 0.8 ) { this->color = this->colorB; }
      else if( v > 0.7 ) { this->color = this->colorA; }
      else if( v > 0.6 ) { this->color = this->colorB; }
      else if( v > 0.5 ) { this->color = this->colorA; }
      else if( v > 0.4 ) { this->color = this->colorB; }
      else if( v > 0.3 ) { this->color = this->colorA; }
      else if( v > 0.2 ) { this->color = this->colorB; }
      else if( v > 0.1 ) { this->color = this->colorA; }
      else if( v > 0.0 ) { this->color = this->colorB; }
      break;
      
    case( kType_Off ):
      break;
 
    default:
      break;
  }
}



void ArcadeTube::SetupNewPhase()
{
  switch( this->phase ) {
    case( 0 ):
      this->SetupAnimation( kType_RandomOrange );
      break;
      
    case( 1 ):
      this->SetupAnimation( kType_DarkCyan500 );
      break;
      
    case( 2 ):
      this->SetupAnimation( kType_FlashingColor );
      break;

      
    case( 5 ):
      this->SetupAnimation( kType_FlashingRandomColor );
      break;
      
    case( 3 ):
    case( 6 ):
      this->SetupAnimation( kType_SlowFadeDarkLight );
      break;
      
    case( 4 ):
    case( 7 ):
      this->SetupAnimation( kType_SlowFadeLightDark );
      break;
      
    case( 8 ):
      this->SetupAnimation( kType_FlashingFast );
      break;
      
    case( 9 ):
      this->SetupAnimation( kType_Off );
      break;
    default:
    break;
  }
}




void ArcadeTube::poll()
{
  if( this->v->Get() >= 1.0 ) {
    // new phase time
    this->phase++;
    if( this->phase > 9 ) { this->phase = 0; }

    this->SetupNewPhase();
    
    this->v->Kick();
  }
  this->DoAnimationFrame();
}
