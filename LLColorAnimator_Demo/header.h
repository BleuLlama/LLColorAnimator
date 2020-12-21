

#ifndef __HEADER_H__
#define __HEADER_H__

/*****************************************************************************
   Standard librarires, misc
*/
#include <avr/pgmspace.h>

////////////////////////////////////////////////////////////////

class Button {
  private:
    int pin;
    bool isPressing;
    bool wasPressed;
    bool wasStarted;
    unsigned long nextWait;
    
  public:
    Button( int _pin );
    ~Button();

  public:
    void Poll( void );
    bool WasStarted( void );
    bool WasPressed( void );
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

#define kSetting_User     (5)
#define kSetting_Pattern  (kSetting_User + 0)



#endif
