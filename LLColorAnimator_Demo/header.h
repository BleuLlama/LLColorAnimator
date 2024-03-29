

#ifndef __HEADER_H__
#define __HEADER_H__

/*****************************************************************************
   Standard librarires, misc
*/
#include <avr/pgmspace.h>


////////////////////////////////////////////////////////////////
// Settings



// are the sequences in PROGMEM (flash)?
// Probably worthwhile to do...
#define SEQUENCES_IN_PROGMEM

#ifdef SEQUENCES_IN_PROGMEM
  #define SEQLOC PROGMEM
#else
  #define SEQLOC
#endif


// what does button D do?
#define kButtonDFunction_Flash
#undef kButtonDFunction_Brightness

////////////////////////////////////////////////////////////////
// Hardware Configuration (Uno)
//    4-wire LEDs
//  GND                  (BLUE)
//  D11 --- WS2801 Clock (GREEN)
//  D12 --- WS2801 Data  (WHITE)
//  +5v                  (RED)
//
//    3-wire LEDs (neopixel)
//  D12 --- Neopixel Data
//
//  A1 --- Button A --- [gnd]     (previous sequence)
//  A0 --- Button B --- [gnd]     (next sequence)
//  A4 --- Button C --- [gnd]     (tap tempo)
//  A5 --- Button D --- [gnd]     (flash/accent)
//
//  A2 --- 10k pot wiper          (animation speed)
//  A3 --- 10k pot wiper          (display brightness)
//    pot poles are wired to +5v on one side, ground on the other
//
//
/* config for Uno board above */

/* config for scrollytroller ssmicro (leonardo) */
/*
                (GRN) (RED)

        UP         B   A     (Rotary)
    LEFT  RIGHT      C
       DOWN        E   D
  
  A0  D-pad Right
  A1  Button A
  A2  Button B
  
  D0  Button C (not connected)
  D1  D-pad Up / External cord data
  D2  Rotary A
  D3  Rotary B
  D6  D-Pad Down
  D9  Button D
  D10 Button E
  D11 D-pad Left
  D14 red led
  D15 green led
  D16 Rotary button
  
 */
#undef kHARDWARE_UNO
#define kHARDWARE_LEONARDO
/* The strand that I have has four wires:
     Red    +5v
     White  Data
     Green  Clock
     Blue   Ground
*/
#define kNumberOfLights (14)        // # lights in the strand

#ifdef kHARDWARE_UNO
/* pin configuration on Arduino */
#define kWS2801_Data  (12)    // data line (white wire)
#define kWS2801_Clock (11)    // clock line (green wire)

/* and for neopixel use */
#define kNeoPixelPin  (12)    // data out

#define kStrand_WS2801      // 4-wire
//#define kStrand_NeoPixel    // 3-wire


#ifdef kUSE_ANALOG_KNOBS
#define kKnobA (A2)     // Duration / update interval
#define kKnobB (A3)     // Brightness
#endif
#undef kUSE_BUTTONS_FOR_SPEED


#define kButtonA  (A1)  // previous sequence
#define kButtonB  (A0)  // next sequence
#define kButtonC  (A4)  // tap-tempo
#define kButtonD  (A5)  // flash/accent or brightness

#define kButtonMode (A6)

#endif


#ifdef kHARDWARE_LEONARDO

#define kStrand_NeoPixel    // 3-wire LEDs
#define kNeoPixelPin  (1)   // (UP) data out
#undef kUSE_ANALOG_KNOBS    // no analog knobs

#define kUSE_BUTTONS_FOR_SPEED

#define kButtonSlower (A1) // (B NW)
#define kButtonFaster (A2) // (A NE)

#define kButtonA  (11)  // (LEFT) previous sequence
#define kButtonB  (A0)  // (RIGHT) next sequence

#define kButtonC  (10)  // (E SW) tap-tempo
#define kButtonD  (6)   // (DOWN) flash/accent
#define kButtonMode (9) // (D SE) view mode change

// setup button D use (down)
#define kButtonDFunction_Brightness
#undef kButtonDFunction_Flash
#endif



////////////////////////////////////////////////////////////////

class Button {
  protected:
    int pin;
    bool isPressing;
    bool wasPressed;
    bool wasStarted;
    unsigned long nextWait;
    unsigned long startTime;
    
  public:
    Button( int _pin );
    ~Button();

  public:
    void Poll( void );
    bool WasStarted( void );
    bool WasPressed( void );
    bool IsPressing( void ) { return this->isPressing; }
    unsigned long StartTime( void ) { return this->startTime; }
};

#define kTempoCt (8)

class TapTempo: public Button {
  private:
    unsigned long taps[ kTempoCt ];
    unsigned long previousStartTime;
    unsigned long lastGet = 0;
  
  public:
    TapTempo( int _pin );

  private:
    void AddNow();

  public:
    void Clear();
    void Dump();

  public:
    void Poll( void );
    unsigned long Get( void );
};

////////////////////////////////////////////////////////////////

class Settings {
  private:
    bool verified;
    void Initialize();
    void Verify();

  private:
    void Read_All();
    void SetDefaults();
    
  public:
    unsigned char s_pattern;
    
  public:
    Settings();
    ~Settings();

  public:
    // v1: no buffering.  direct io.
    unsigned char Get( unsigned char key );
    void Set( int key, unsigned char value );
};

// where in eeprom we store various setting.
#define kSetting_User     (5)
#define kSetting_Pattern  (kSetting_User + 0)
#define kSetting_Transition  (kSetting_User + 1)    // which transition style are we using

#define kTransition_Cut_Cut   (0)     // cut out, cut in
#define kTransition_Cut_Fade  (1)     // cut out, fade in
#define kTransition_Fade_Cut  (2)     // fade out, cut in
#define kTransition_Fade_Fade (3)     // fade out, fade in
#define kTransition_Crossfade (4)     // crossfade between frames



#endif
