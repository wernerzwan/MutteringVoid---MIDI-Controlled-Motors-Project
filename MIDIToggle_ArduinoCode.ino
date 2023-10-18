#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const byte LEDPWM1 = 3;
const byte LEDPWM2 = 5;
const byte LEDPWM3 = 6;
const byte LEDPWM4 = 9;
const byte LEDPWM5 = 10;


byte trashcans[] = {LEDPWM1, LEDPWM2, LEDPWM3, LEDPWM4 ,LEDPWM5};
bool toggles[] = {0, 0, 0, 0, 0};
byte mem [] = {0, 0, 0, 0, 0};
// bool motorsActive[5] = {false, false, false, false, false};

void setup() {

  Serial.begin(31250);

  TCCR2B = TCCR2B & B11111000 | B00000110;
  TCCR0B = TCCR0B & B11111000 | B00000101;
  TCCR1B = TCCR1B & B11111000 | B00000100;

  pinMode(LEDPWM1, OUTPUT);
  pinMode(LEDPWM2, OUTPUT);
  pinMode(LEDPWM3, OUTPUT);
  pinMode(LEDPWM4, OUTPUT);
  pinMode(LEDPWM5, OUTPUT);

  MIDI.begin(MIDI_CHANNEL_OMNI);

  MIDI.setHandleControlChange(MyCCFunction);
}

void loop() {
  MIDI.read();

}

// void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {

//   Serial.print("Received Pitch ON: ");
//   Serial.print(pitch);
//   Serial.print(" Velocity: ");
//   Serial.println(velocity);

//   if (pitch >= 24 && pitch <= 28) {
//     int motorIndex = pitch - 24;
//     motorsActive[motorIndex] = true;
//   }
// }

// void MyHandleNoteOff(byte channel, byte pitch, byte velocity) {

//   // Serial.print("Received Pitch OFF: ");
//   // Serial.print(pitch);
//   // Serial.print(" Velocity: ");
//   // Serial.println(velocity);

//   if (pitch >= 24 && pitch <= 28) {
//     int motorIndex = pitch - 24;
//     motorsActive[motorIndex] = false;
//   }
// }

void MyCCFunction(byte channel, byte ccNumber, byte value) {
  Serial.print("Received CC: ");
  Serial.print(ccNumber);
  Serial.print(" Value: ");
  Serial.println(value);

  if (ccNumber >= 1 && ccNumber <= 5) {
   mem[ccNumber - 1] = value;
   analogWrite(trashcans[ccNumber - 1], (mem[ccNumber - 1] * 2) * toggles[ccNumber - 1]);

  }
  if (ccNumber >= 6 && ccNumber <=10) {
    toggles[ccNumber - 6] = (value / 127);
    analogWrite(trashcans[ccNumber - 6], (mem[ccNumber - 6] * 2) * toggles[ccNumber - 6]);
  }
}