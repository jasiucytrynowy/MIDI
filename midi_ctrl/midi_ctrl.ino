#include <MIDI.h>

MIDI_CREATE_INSTANCE();

#define LED_A 2
#define LED_B 3
#define LED_C 4
#define LED_D 5

#define BTN_A 6
#define BTN_B 7
#define BTN_C 8
#define BTN_D 9

#define INFO_LED 13

int button_state[4] = 0;

void setup(){

  pinMode(LED_A,OUTPUT);
  pinMode(LED_B,OUTPUT);
  pinMode(LED_C,OUTPUT);
  pinMode(LED_D,OUTPUT);

  pinMode(BTN_A,INPUT);
  pinMode(BTN_B,INPUT);
  pinMode(BTN_C,INPUT);
  pinMode(BTN_D,INPUT);

  MIDI.begin(4);
  
}
void loop()
{
  button_state[0] = digitalRead(BTN_A);
  button_state[1] = digitalRead(BTN_B);
  button_state[2] = digitalRead(BTN_C);
  button_state[4] = digitalRead(BTN_D);
  
  if(BTN_A == 1){
    MIDI.sendNoteOn(42,127,1);
    delay(50);
  } else if(BTN_B == 1){
    MIDI.sendNoteOn(54,127,1);
    delay(50);
  } else if(BTN_C == 1){
    MIDI.sendNoteOn(68,127,1);
    delay(50);
  } else if(BTN_D == 1){
    MIDI.sendNoteOn(82,127,1);
    delay(50);
  }
  delay(5);
}


