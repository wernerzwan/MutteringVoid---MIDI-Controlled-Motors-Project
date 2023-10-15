// This code make it possible to control motors with MIDI. The Velocity of the notes is linked to the value of PWM / speed of the motors. 

#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>
#define LEDPWM1 3
#define LEDPWM2 5
#define LEDPWM3 6
#define LEDPWM4 9
#define LEDPWM5 10
// #define LICHT 11
//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

int velo;

void setup() {
  TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz   
  TCCR0B = TCCR0B & B11111000 | B00000101;    // set timer 0 divisor to  1024 for PWM frequency of    61.04 Hz
  TCCR1B = TCCR1B & B11111000 | B00000100;    // set timer 1 divisor to   256 for PWM frequency of   122.55 Hz

  pinMode (3, OUTPUT); // PWM Motor 1  
  pinMode (5, OUTPUT); // PWM Motor 2   
  pinMode (6, OUTPUT); // PWM Motor 3   
  pinMode (9, OUTPUT); // PWM Motor 4  
  pinMode (10, OUTPUT); // PWM Motor 5
  // pinMode (11, OUTPUT); // 
  

  MIDI.begin(MIDI_CHANNEL_OMNI);

  MIDI.setHandleNoteOn(MyHandleNoteOn);
  MIDI.setHandleNoteOff(MyHandleNoteOff);
//  MIDI.setHandleControlChange(MyCCFunction);
}

void loop() { //
  MIDI.read(); // Read Midi
}


void MyHandleNoteOn(byte channel, byte pitch, byte velocity)
{
  digitalWrite(LED_BUILTIN, HIGH);
  
  velo = map(velocity, 0, 127, 0, 255);

  //MOTOR1
  if (pitch == 24)
    analogWrite(LEDPWM1, velo);
  if (pitch == 25)
    analogWrite(LEDPWM2, velo);
  if (pitch == 26)
    analogWrite(LEDPWM3, velo);
  if (pitch == 27)
    analogWrite(LEDPWM4, velo);
  if (pitch == 28)
    analogWrite(LEDPWM5, velo);
  // if (pitch == 29)
  //   digitalWrite(LICHT, HIGH);
    

}

void MyHandleNoteOff(byte channel, byte pitch, byte velocity)
{
  
  //MOTOR1
  if (pitch == 24)
   analogWrite(LEDPWM1, 0);
  if (pitch == 25)
   analogWrite(LEDPWM2, 0);
  if (pitch == 26)
   analogWrite(LEDPWM3, 0);
  if (pitch == 27)
   analogWrite(LEDPWM4, 0);
  if (pitch == 28)
   analogWrite(LEDPWM5, 0);
  // if (pitch == 29)
  //  digitalWrite(LICHT, LOW);
}

/*void MyCCFunction(byte channel, byte number, byte value) {
  switch (number) {
    case 1:
      analogWrite(LEDPWM1, value * 2);
      break;
    case 2:
      analogWrite(LEDPWM2, value * 2);
      break;
    case 3:
      analogWrite(LEDPWM3, value * 2);
      break;
    case 4:
      analogWrite(LEDPWM4, value * 2);
      break;
    case 5:
      analogWrite(LEDPWM5, value * 2);
      break;
    case 6:
      analogWrite(LEDPWM6, value * 2);
      break;
  }
}
*/
