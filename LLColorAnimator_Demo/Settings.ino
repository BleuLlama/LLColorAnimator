
#include <EEPROM.h> /* for storing the previous settings */
#include "header.h"

    
Settings::Settings()
{
  this->verified = false;
  this->Verify();
}

Settings::~Settings()
{
  this->Verify();
  this->Read_All();
}

void Settings::SetDefaults( void )
{
  this->Set( kSetting_Pattern, 0 );
}

void Settings::Read_All( void )
{
  this->s_pattern = this->Get( kSetting_Pattern );
}

void Settings::Initialize( void )
{
  // never used before... let's initialize.
  // sentinel
  EEPROM.write( 0, 'S' );
  EEPROM.write( 1, 'c' );
  EEPROM.write( 2, 'o' );
  EEPROM.write( 3, 't' );
  EEPROM.write( 4, '2' );

  // default values
  this->SetDefaults();
}

void Settings::Verify( void )
{
  boolean valid = true;

  if( this->verified ) {
    return;
  }
  
  // validate the eeprom has been initialized
  if ( EEPROM.read( 0 ) != 'S' ) valid = false;
  if ( EEPROM.read( 1 ) != 'c' ) valid = false;
  if ( EEPROM.read( 2 ) != 'o' ) valid = false;
  if ( EEPROM.read( 3 ) != 't' ) valid = false;
  if ( EEPROM.read( 4 ) != '2' ) valid = false;

  if( !valid ){
    this->Initialize();
  }
  this->verified = true;
}
    
unsigned char Settings::Get( unsigned char key )
{
  this->Verify();

  // get from the cache
  switch( key ){
    case( kSetting_Pattern ):
      this->s_pattern = EEPROM.read( kSetting_Pattern );
      return( this->s_pattern );
    default:
      break;
  }
  return 0;
}

void Settings::Set( int key, unsigned char value )
{
  this->Verify();

  EEPROM.write( key, value );

  // store in the cache too
  switch( key ){
    case( kSetting_Pattern ):
      this->s_pattern = value;
    default:
      break;
  }
}
