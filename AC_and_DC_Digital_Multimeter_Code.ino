#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd ( 0x 3F , 16 , 2 ) ;
bool switch1;
bool switch2;
int readtimes= 0 ;
float inputarduinovoltage = 0.0 ;
float volts= 0.0 ;
float shunt_res = 4 ;
float v_out= 0.0 ;
float current= 0.0 ;
float AC_v_output [ 15 ];
void setup ()
{
Serial . begin ( 9600 ) ;
pinMode ( 3 ,INPUT ) ;
pinMode ( 4 ,INPUT ) ;
lcd . init () ; // initialize the LCD
lcd . backlight () ; // Turn on the blacklight and print a message.
lcd . clear () ;
lcd . setCursor ( 0 , 1 ) ;
lcd . print ( "MultiMeter:" ) ;
delay ( 2000 ) ;
lcd . clear () ;
lcd . print ( "By:Zohaib Saadat" ) ;
lcd . setCursor ( 0 , 1 ) ;
lcd . print ( "Roll:21i-0946" ) ;
delay ( 2000 ) ;
lcd . clear () ;
}
void loop ()
{
switch1= digitalRead ( 3 ) ;
switch2= digitalRead ( 4 ) ;
Serial . print ( "\nswitch1:" ) ;
Serial . print ( switch1 ) ;
delay ( 500 ) ;
Serial . print ( "\nswitch2:" ) ;
Serial . print ( switch2 ) ;
delay ( 500 ) ;
if ( switch1== 0 ) //AC
{
if ( switch2== 0 ) //Ammeter
{
lcd . setCursor ( 0 , 1 ) ;
lcd . print ( "AC I: " ) ;
delay ( 2000 ) ;
lcd . clear () ;
}
else if ( switch2== 1 ) //voltmeter
{
lcd . setCursor ( 0 , 1 ) ;
lcd . print ( "AC V:" ) ;
delay ( 2000 ) ;
lcd . clear () ;
}
}
else //DC
{
if ( switch2== 1 ) //Voltmeter
{
lcd . setCursor ( 0 , 1 ) ;
lcd . print ( "DC V: " ) ;
delay ( 2000 ) ;
lcd . clear () ;
Serial . print ( inputarduinovoltage ) ;
Serial . print ( "\n" ) ;
inputarduinovoltage= analogRead ( A0 ) ;
if ( inputarduinovoltage< 204.0 ||readtimes< 10 ) //The deafult arduino analog
reads 440(Max), 204(min that gives less than 1v) when no voltage input
therefore we consider it 0v.
{ //the readtimes just for letting the arduino adjust at a certain
level.(Like letting the ripples in the water settle after disturbtion)
volts= 0.0 ;
readtimes++;
}
else
{
volts= ( 5 / 1024.0 ) *inputarduinovoltage;
}
lcd . setCursor ( 0 , 1 ) ;
lcd . print ( "DC VOLT: " ) ;
lcd . print ( volts ) ;
delay ( 300 ) ;
}
else if ( switch2== 0 ) //Ammeter
{
lcd . setCursor ( 0 , 1 ) ;
lcd . print ( "DC I: " ) ;
delay ( 2000 ) ;
lcd . clear () ;
// put your main code here, to run repeatedly:
switch1= digitalRead ( 3 ) ;
switch2= digitalRead ( 4 ) ;
//Serial.print("\nswitch1:");
//Serial.print(switch1);
delay ( 1000 ) ;
//Serial.print("\nswitch2:");
//Serial.print(switch2);
lcd . clear () ;
delay ( 400 ) ;
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////
if ( switch1== 0 ) //AC
{
if ( switch2== 0 ) //Ammeter
{
lcd . setCursor ( 0 , 1 ) ;
lcd . print ( "AC I: " ) ;
delay ( 100 ) ;
} /////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////
else if ( switch2== 1 ) //voltmeter
{
lcd . setCursor ( 0 , 1 ) ;
lcd . print ( "AC V: " ) ;
delay ( 100 ) ;
}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////
else if ( switch2== 0 ) //Ammeter
{
v_out= analogRead ( A1 ) ;
v_out=v_out* ( 5 / 1024 ) ;
current=v_out/shunt_res;
lcd . setCursor ( 0 , 1 ) ;
lcd . print ( "DC I: " ) ;
lcd . print ( current ) ;
}
}
}
}
