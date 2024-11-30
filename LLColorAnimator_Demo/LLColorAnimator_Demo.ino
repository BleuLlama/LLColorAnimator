// LLColorAnimator Demo (WS2801 or Neopixel)
//  yorgle@gmail.com
//
//	Pattern manager and runtime for Addressable LED strands
//
//  2024-11-29  - code cleanups, 
//  2024-11-02  - haunt added for lego haunted mansion
//  2023-12-05  - xmas caterpillar 3, 4 line leds on mega
//  2023-10-24  - Support for SSMicro instead of Uno
//  2022-01-09  - transition support starting
//  2022-01-02  - Support for Neopixels
//  2020-12-20  - initial version

#define kVersion "LCA - 2024-11-29"
#define kDisplayVers "24.11.29"

#include "header.h"


/*****************************************************************************
*  Color Animator configuration
*/
#include "LLColorAnimator.h"

extern const unsigned long palette[];
extern const char * sequences[];

LLColorAnimator ca = LLColorAnimator( palette, sequences );

/*****************************************************************************
*  LED strand configuration
*/

// if we're using a 4-wire, WS2801 based strand...
#ifdef kStrand_WS2801
  #include <Adafruit_WS2801.h>
  #include <SPI.h>
  Adafruit_WS2801 strip = Adafruit_WS2801(kNumberOfLights, kWS2801_Data, kWS2801_Clock);
#endif

// or if we're using a 3-wire, neopixel based strand...
#ifdef kStrand_NeoPixel
  #include <Adafruit_NeoPixel.h>
  Adafruit_NeoPixel strip(kNumberOfLights, kNeoPixelPin, NEO_GRB + NEO_KHZ800);
#endif


#ifndef kUSE_ANALOG_BUTTONS
  // button input helper classes
  Button buttonA = Button( kButtonA );
  Button buttonB = Button( kButtonB );
  TapTempo buttonC = TapTempo( kButtonC );
  Button buttonD = Button( kButtonD );
  
  #ifdef kUSE_BUTTONS_FOR_SPEED
    Button buttonFaster = Button( kButtonFaster );
    Button buttonSlower = Button( kButtonSlower );
  #endif
  
  Button buttonMode = Button( kButtonMode );
#endif


int buttonSpeed = 100;
int viewMode = 0;
int buttonBrightness = 255;

Settings settings = Settings();

#include "Lightning.h"
#include "Candle.h"
#include "ArcadeTube.h"
// arcade tubes
#define kNumTubes (13)

ArcadeTube theTubes[ kNumTubes ] = {
  ArcadeTube( 1, 3),
  ArcadeTube( 2, 7),
  ArcadeTube( 3, 11),
  ArcadeTube( 4, 13),
  ArcadeTube( 5, 399),
  ArcadeTube( 6, 45 ),
  ArcadeTube( 7, 91 ),
  ArcadeTube( 8 ),
  ArcadeTube( 9 ),
  ArcadeTube( 10 ),
  ArcadeTube( 11, 53),
  ArcadeTube( 12, 723 ),
  ArcadeTube( 13, 831 ),
};

#ifdef kLowMemory
#define kNumCandles (3)
#else 
#define kNumCandles (19)
#endif
Candle theCandles[ kNumCandles ] = {
  Candle(), Candle(), Candle(),
  
#ifndef kLowMemory
  Candle(), Candle(), Candle(),
  Candle(), Candle(), Candle(),
  Candle(), Candle(), Candle(),
  Candle(), Candle(), Candle(),
  Candle(), Candle(), Candle(),
  Candle()
#endif


};

Lightning theLightning = Lightning();


#ifdef kUseDisplay
  #include <TM1637Display.h>
  
  uint8_t digit_remapping[] = { 2, 1, 0, 5, 4, 3 };
  uint8_t __encodeBuffer[] = { 0, 0, 0, 0, 0, 0 };
  uint8_t * encodeBuffer;
  char textBuffer[ 16 ];
  
  TM1637Display display(kDisplayPinClk, kDisplayPinData, DEFAULT_BIT_DELAY, 6, digit_remapping );
#endif

void setup()
{
  #ifdef kUseDisplay
    encodeBuffer = &__encodeBuffer[0];

    display.setBrightness( 3 ); // full bright = 7
    sprintf( textBuffer, kDisplayVers );
    display.setSegments( display.encodeText( textBuffer, encodeBuffer ));
    delay( 700 );
  #endif

  // serial console setup
  Serial.begin( 115200 );
  Serial.println( F( kVersion ));

  ca.AnimRange( kNumberOfLights );
  ca.SequenceSet( settings.Get( kSetting_Pattern ) );
  //ca.Dump();
  
  // random setup
  randomSeed( analogRead( 0 ) + analogRead( 1 ) );
  #ifdef kUSE_ANALOG_BUTTONS
    pinMode( kAnalogButton, INPUT );
  #endif

  #ifdef kUSE_ANALOG_KNOBS
    pinMode( kKnobA, INPUT );
    pinMode( kKnobB, INPUT );
  #endif

  // initialize tubes
  for( int i = 0 ; i < kNumTubes ; i++ ) {
    theTubes[i].setup();
  }
    
  #ifdef kStrand_NeoPixel
    strip.setBrightness( 128 );
  #endif

  // secondary groundish
  pinMode( 6, OUTPUT );
  digitalWrite( 6, LOW );

  // Builtin LED setup
  pinMode( LED_BUILTIN, OUTPUT );
  digitalWrite( LED_BUILTIN, LOW );

  // strip setup
  strip.begin();
  strip.setPixelColor( 0, COLOR( 100, 0, 0 ));
  strip.show();
  // Update LED contents, to start they are all 'off'

  Serial.println( F( " Hellorld." ));
  
  #ifdef kFixed_Sequence_Value
    ca.SequenceSet( kFixed_Sequence_Value );
  #endif

  #ifdef kFixed_Speed_Value
    buttonSpeed = kFixed_Speed_Value;
    ca.DurationA( kFixed_Speed_Value );
  #endif


}



float getBrightness()
{
  #ifdef kFixed_Brightness
    return kFixed_Brightness;
  #endif

  #ifdef kUSE_ANALOG_KNOBS
    #ifdef kInvertKnobB
      int v = analogRead( kKnobB );
    #else
      int v = 1024 - analogRead( kKnobB );
    #endif
  #else
    int v = buttonBrightness;
  #endif

  // add some dead spots
  if( v < 3 ) { v = 0; }
  if( v > 1020 ) { v= 1024; }
  
  float b = (float) v / 1024.0;
  return( b );
}

void SequenceMinus()
{
  int seq = 0;
  seq = ca.SequencePrev();
  settings.Set( kSetting_Pattern , seq );
  //Serial.print( F("- Pattern # ") );
  //Serial.println( seq );
}

void SequencePlus()
{
  int seq = 0;
  seq = ca.SequenceNext();
  settings.Set( kSetting_Pattern , seq );
  //Serial.print( F("+ Pattern # ") );
  //Serial.println( seq );
  
}


#ifndef kUSE_ANALOG_BUTTONS
int pollButtons()
{
  int seq = 0;
  int buttonHandled = 0;

  // why was this here?
  /*
  int p = settings.Get( kSetting_Pattern );
  ca.SequenceSet( p );
  */
  
  #ifdef kUSE_BUTTONS_FOR_SPEED
    buttonFaster.Poll();
    buttonSlower.Poll();

    if( buttonFaster.WasStarted() ) {
      buttonSpeed += 10;
      if( buttonSpeed > 1024 ) { buttonSpeed = 1024; }
      
      Serial.print( F("+ Speed : ") );
      Serial.println( buttonSpeed );
    }
    
    if( buttonSlower.WasStarted() ) {
      buttonSpeed -= 10;
      if( buttonSpeed < 1 ) { buttonSpeed = 1; }
      
      Serial.print( F("- Speed : ") );
      Serial.println( buttonSpeed );
    }
  #endif
  #ifdef kFixed_Speed_Value
    buttonSpeed = kFixed_Speed_Value;
  #endif

  
  buttonA.Poll();
  buttonB.Poll();

  if( buttonA.WasStarted() ) {
    SequenceMinus();
    buttonHandled = 1;
    Serial.print( F("- Pattern # ") );
    Serial.println( seq );
  }

  if( buttonB.WasStarted() ) {
    //p++;
    SequencePlus();
    buttonHandled = 1;
    Serial.print( F("+ Pattern # ") );
    Serial.println( seq );
  }

  // button C is tap tempo
  buttonC.Poll();

#ifdef kButtonDFunction_Transition
#endif
  buttonMode.Poll();
  if( buttonMode.WasStarted() ) {
     viewMode++;
     if( viewMode > 4 ) { viewMode = 0; }
     if( viewMode == 0 ) { Serial.println( F("Cut Out, Cut In") ); }
     if( viewMode == 1 ) { Serial.println( F("Cut Out, Fade In") ); }
     if( viewMode == 2 ) { Serial.println( F("Fade Out, Cut In") ); }
     if( viewMode == 3 ) { Serial.println( F("Fade Out, Fade In") ); }
     if( viewMode == 4 ) { Serial.println( F("Blend") ); }
  }

  #ifdef kButtonDFunction_Flash
    // button D triggers a flash
    buttonD.Poll();
    if( buttonD.IsPressing() ) {
        
        while( buttonD.StartTime() ) {
          unsigned long dt = millis() - buttonD.StartTime();
          
          if( dt > 100 ) {
            fillPixels( 0 );
          } else {
            dt = 100-(dt);
            /*
            if( buttonD.PressCount() & 1 ) {
              fillPixelsAlternating( COLOR( dt,dt,dt ), 0 );
            } else {
              fillPixelsAlternating( 0, COLOR( dt,dt,dt ) );
            }*/
            fillPixels( COLOR( dt, dt, dt ));
            
          }
          buttonD.Poll();
        }
    }
  #endif

  #ifdef kButtonDFunction_Brightness
    // button D triggers a flash
    buttonD.Poll();
    if( buttonD.WasPressed() ) {
      
      if( buttonBrightness > 700 ) buttonBrightness -= 100;
      else if( buttonBrightness > 500 ) buttonBrightness -= 50;
      else if( buttonBrightness > 100 ) buttonBrightness -= 20;
      else if( buttonBrightness > 50 ) buttonBrightness -= 7;
      else if( buttonBrightness > 20 ) buttonBrightness -= 5;
      else if( buttonBrightness > 9 ) buttonBrightness -= 1;
      else buttonBrightness = 1024;

      
      if( buttonBrightness < 1 ) {
        buttonBrightness = 1024;
      }
      Serial.print( F("Brightness: ") );
      Serial.println( buttonBrightness );
    }
  #endif

  if ( buttonHandled ) {
    return 1;
  }
  return 0;
}
#endif

#ifdef kUSE_ANALOG_BUTTONS

  // analog buttons are multiple buttons that pull an input down from +vcc to ground through different resistors.
  void pollAnalogButtons()
  {
    static int lastButton = 0;
    int whichButton = 0;
    
    int val = analogRead( kAnalogButton );
    if( val > 400 ) { 
      whichButton = 0;
    } else if ( val > 200 ) { 
      whichButton = 1;
    } else if ( val > 100 ) { 
      whichButton = 2;
    } else {
      whichButton = 3;
    }

    if( ( whichButton > 0 ) && ( lastButton == 0 )) {
      // pressed.

      switch( whichButton ) {
        case( 1 ):
          SequenceMinus();
          break;
          
        case( 2 ):
          SequencePlus();
          break;
          
        case( 3 ):
          break;
      }
    }
    lastButton = whichButton;
  }
#endif


void fillPixels( uint32_t c ) 
{
  for (uint16_t i = 0; i < strip.numPixels(); i++ ) {
    strip.setPixelColor( i, c );
  }
  strip.show();
}

void fillPixelsAlternating( uint32_t c1, uint32_t c2 )
{
  for (uint16_t i = 0; i < strip.numPixels(); i++ ) {
    if( i & 1 ) {
      strip.setPixelColor( i, c1 );
    } else {
      strip.setPixelColor( i, c2 );
    }
  }
  strip.show();
}

void renderPixels()
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, ca.GetColor( i ) );
  }
  strip.show();
}

uint32_t RemapOrangeToGreens( uint32_t ccc )
{
  int r = LLCA_COLOR_R( ccc );  // most
  int g = LLCA_COLOR_G( ccc );  // med
  int b = LLCA_COLOR_B( ccc );  // smallest

  return LLCA_COLOR( 0, b, r, g/2 );

}

uint32_t RemapOrangeToBlues( uint32_t ccc )
{
  int r = LLCA_COLOR_R( ccc );  // most
  int g = LLCA_COLOR_G( ccc );  // med
  int b = LLCA_COLOR_B( ccc );  // smallest

  return LLCA_COLOR( 0, 0, (g+r+r+r)/4, r );
}


void loop() {
  digitalWrite( LED_BUILTIN, millis() & 0x80 );
  
  #ifdef kUSE_ANALOG_BUTTONS
    pollAnalogButtons();
  #else
    pollButtons();
  #endif

  if( ca.Mode() == 'm' ) {
    /////////////////////
    // Arcade Machine special sequences

    #ifdef kStrand_NeoPixel
      strip.setBrightness( getBrightness( )*255 );
    #endif
      
    for( int i = 0 ; i < kNumTubes ; i++ ) {
      theTubes[i].poll(); // arcade tube polling
    }
    for( int j = 0 ; j < kNumberOfLights ; j++ )
    {
      strip.setPixelColor( j, theTubes[j % kNumTubes].getColor() );
    }
    strip.show();
 

  } else if( ca.Mode() == 'c' ) {
    /////////////////////
    // candles!
    #ifdef kStrand_NeoPixel
      strip.setBrightness( getBrightness( )*255 );
    #endif

    for( int i = 0 ; i < kNumberOfLights ; i++ ) {
      strip.setPixelColor( i, theCandles[i % kNumCandles].GetColor() ); // repeat when there's no more data.
    }
    
    strip.show();
    
  } else if( ca.Mode() == 'l' ) {
    /////////////////////
    // lightning!
    for( int i = 0 ; i < kNumberOfLights ; i++ ) {
      if( i == theLightning.Pindex() ) {
        strip.setPixelColor( i, theLightning.GetColor() );
      } else {
        strip.setPixelColor( i, 0 );
      }
    }
    
   
    strip.show();

  } else if( ca.Mode() == 'h' ) {

    // first four are candles for now
    for( int i = 0 ; i < 4 ; i++ ) {
      strip.setPixelColor( i, theCandles[i % kNumCandles].GetColor() ); // repeat when there's no more data.
    }
    // attic
    strip.setPixelColor( 4, RemapOrangeToGreens( theCandles[4  % kNumCandles].GetColor() ));
    strip.setPixelColor( 5, RemapOrangeToGreens( theCandles[5  % kNumCandles].GetColor() ));
    strip.setPixelColor( 6, RemapOrangeToGreens( theCandles[6  % kNumCandles].GetColor() ));
    strip.setPixelColor( 7, RemapOrangeToGreens( theCandles[7  % kNumCandles].GetColor() ));


    // entry way
    strip.setPixelColor( 8, theCandles[8  % kNumCandles].GetColor() & 0x00FF0000 ); // just red

    // ghosts
    strip.setPixelColor( 9, RemapOrangeToBlues( theCandles[9  % kNumCandles].GetColor() ));
    strip.setPixelColor( 10, RemapOrangeToBlues( theCandles[10  % kNumCandles].GetColor() ));


    // lightning overlay, but only on the first 8
    for( int i = 0 ; i <=8 ; i++ ) {
      if( i == theLightning.Pindex() ) {
        strip.setPixelColor( i, theLightning.GetColor() );
      }
    }

    strip.show();

  }  else {

    #ifndef kFixed_Speed_Value
      // this next chunk is kinda a mess...
      #ifndef kUSE_ANALOG_BUTTONS
        // tap tempo routine
        int d = buttonC.Get();
        if( d == 0 ) {
          #ifdef kUSE_ANALOG_KNOBS
            int v = analogRead( kKnobA ); // why twice?
            // hack fix for bad knob
            if( v < 10 ) {
              v = 10;
            }
            v = 150;
            ca.DurationA( v );
          #else
            ca.DurationA( buttonSpeed );
          #endif
        } else {
          ca.DurationA( d );  // if you want to be tapping whole notes of 4/4 time, then divide by 4
        }
        
      #else // digital buttons

        int v = analogRead( kKnobA );
        #ifdef kBADKNOBFIX
          // hack fix for bad knob
          if( v < 10 ) {
            v = 10;
          }
          v = 150;
        #endif
        ca.DurationA( v );
      #endif  // digital buttons else
    
    #else
      ca.DurationA( kFixed_Speed_Value ); 
    #endif
    
    // brightness adjust
    ca.Brightness( getBrightness( ));
    ca.Update();
    renderPixels();
  }
}
