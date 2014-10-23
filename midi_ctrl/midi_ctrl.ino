#include <MIDI.h>

#define tracer

#ifdef tracer
MIDI_CREATE_DEFAULT_INSTANCE();
#endif

#define LED_A 2
#define LED_B 3
#define LED_C 4
#define LED_D 5

#define BTN_A 6
#define BTN_B 7
#define BTN_C 8
#define BTN_D 9

#define INFO_LED 13

int led_array[4];
int led_outs[4] = {LED_A,LED_B,LED_C,LED_D};

int button_state[4];
int button_last_status[4];
int button_state_bin;
int last_button_state_bin;
int actual_button_state_bin = 0;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 10;    // the debounce time; increase if the output flickers

void setup(){

  pinMode(LED_A,OUTPUT);
  pinMode(LED_B,OUTPUT);
  pinMode(LED_C,OUTPUT);
  pinMode(LED_D,OUTPUT);

  pinMode(BTN_A,INPUT);
  pinMode(BTN_B,INPUT);
  pinMode(BTN_C,INPUT);
  pinMode(BTN_D,INPUT);

  Serial.begin(9600);
#ifdef tracer
  MIDI.begin(MIDI_CHANNEL_OMNI);
#endif
}
void loop()
{
  button_state[0] = digitalRead(BTN_A);
  button_state[1] = digitalRead(BTN_B);
  button_state[2] = digitalRead(BTN_C);
  button_state[3] = digitalRead(BTN_D);

  button_state_bin = button_state[0]<<3 | button_state[1]<<2 | button_state[2]<<1 | button_state[3];

  if(button_state_bin != last_button_state_bin){
    lastDebounceTime = millis();
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (button_state_bin != last_button_state_bin) {
      switch(button_state_bin){
      case 0b00000001:
        MIDI.sendNoteOn(15,127,1);
        if(led_array[0]!=0) led_array[0] = 0;
        break;
      case 0b00000010:
        MIDI.sendNoteOn(16,127,1);
        if(led_array[1]!=0) led_array[1] = 0;
        break;
      case 0b00000100:
        MIDI.sendNoteOn(17,127,1);
        if(led_array[2]!=0) led_array[2] = 0;
        break;
      case 0b00001000:
        MIDI.sendNoteOn(18,127,1);
        if(led_array[3]!=0) led_array[3] = 0;
        break;
      }
      actual_button_state_bin &= button_state_bin;
    }
  }
  last_button_state_bin = button_state_bin;
  for(int i =0;i<4;i++){
    digitalWrite(led_outs[i],led_array[i]);
  }

  /*
  for(int i =0;i<4;i++){
   if(button_state[i] == 1){
   if(button_last_status[i] == 0){
   button_last_status[i] = 1;
   digitalWrite(led_array[i], HIGH);
   } 
   else {
   button_last_status[i] = 0;
   digitalWrite(led_array[i], LOW);
   }
   MIDI.sendNoteOn(15+i,127,1);
   delay(50);
   }
   }
   */
}









