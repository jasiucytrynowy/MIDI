/*
    Simple MIDI footswitch 1.0
 
    by Mikael Norrgard 2012 <http://www.witchmastercreations.com>
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
 
#include <Bounce.h>
#include <MIDI.h>
 
#define BUTTON1 2          // The pin for first button
#define NUMBUTTONS 5       // The number of buttons
#define MIDICHANNEL 11     // The midi channel to use
 
// For the for-loops
byte i=0;
 
// Define arrays
Bounce *bouncer;                            // pointer to bouncer objects
byte value[NUMBUTTONS];                     // keeping track of the current pin values
byte previousValue[NUMBUTTONS];             // keeping track of the previous pin values
int note[NUMBUTTONS] = {24,26,28,25,27};    // the array for the midi notes to send, in my case C0, D0, E0, C#0, Eb0
 
void setup() {
 
  // Allocate memory for the bouncer objects
  bouncer = (Bounce *) malloc(sizeof(Bounce) * NUMBUTTONS);
 
  for(i=0;i<NUMBUTTONS;i++)
  {
    // Instantiate five Bounce objects with a 5 millisecond debounce time
    bouncer[i] = Bounce( BUTTON1+i,5 );
 
    // Initiate the values
    value[i] = LOW;
    previousValue[i] = LOW;
 
    // Set input pins
    pinMode(BUTTON1+i,INPUT);
  }
 
  //initialize MIDI
  MIDI.begin(MIDICHANNEL);
}
 
void loop() {
 
  // Cycle through all inputs
  for(i=0;i<NUMBUTTONS;i++)
  {
    // Update the bouncer object
    bouncer[i].update();
 
    // Read the current pin-values
    value[i] = bouncer[i].read();
 
    // Has the value changed, in other words, has the button been pressed or released?
    if(value[i] != previousValue[i]) {
     // If button has become pressed, send a midi note on message
     if(value[i] == HIGH) {
       MIDI.sendNoteOn(note[i], 127, MIDICHANNEL); // Send note on
     }
     // Otherwise, send a note off message
     else {
       MIDI.sendNoteOff(note[i], 0, MIDICHANNEL); // Send note off
     }
     // Pause for 300ms (this is to further help with button bounces, my buttons are VERY bouncy.
     // This delay does not hurt the function in my case, since the latency for pushing a button is still very short
     delay(300);
     // Set the previous pin state to the current one for next check
     previousValue[i] = value[i];
    }
  }
}
