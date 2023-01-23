/*
 Name:    LED_Experiment_Code_Lux.ino
 Created: 1/23/2023 12:47:14 PM
 Author:  Darik A. O'Neil & Lux Steinberg, Rafael Yuste Laboratory, Columbia University
*/

/*
This code runs LED experiment. Requires Arduino UNO, L293D motor shield or equivalent,
X number of LEDs, and a single-pole double throw switch.
 
 */

String program_name = "LED_Experiment";

// Sampling
const int reading_period = 100; // Size of circular buffer
const int threshold = 90; // trigger threshold (number of rolling_hits hits per circular buffer)
int rolling_hits = 0; // rolling_hits hits


#include <CircularBuffer.h>
CircularBuffer<int, reading_period> circ_buff; // circular buffer for reading switch

// Debug Mode
//#define DebugMode // remove "//" to enter debug mode
//#define CheckTimes
// #define LEDCommands // remove "//" to debug led commands
//#define SwitchReader // remove "//" to debug switch reader
//#define SwitchState

//parameters


const int on_durations[] = {1, 4, 180};
const int off_durations[] = {3, 3, 3};
const int trials_per_duration = 3;

const int led_on_duration_seconds_1 = 1;
const int led_on_duration_seconds_2 = 1;
const int led_on_duration_seconds_3 = 1;
const int led_on_duration_seconds_4 = 4;
const int led_on_duration_seconds_5 = 4;
const int led_on_duration_seconds_6 = 4;
const int led_on_duration_seconds_7 = 180;
const int led_on_duration_seconds_8 = 180;
const int led_on_duration_seconds_9 = 180;

const int led_off_duration_seconds_1 = 3;
const int led_off_duration_seconds_2 = 3;
const int led_off_duration_seconds_3 = 3;
const int led_off_duration_seconds_4 = 3;
const int led_off_duration_seconds_5 = 3;
const int led_off_duration_seconds_6 = 3;
const int led_off_duration_seconds_7 = 3;
const int led_off_duration_seconds_8 = 3;
const int led_off_duration_seconds_9 = 3;


const long led_on_duration_1 = led_on_duration_seconds_1*1000000; // Microseconds
const long led_on_duration_2 = led_on_duration_seconds_2*1000000; // Microseconds
const long led_on_duration_3 = led_on_duration_seconds_3*1000000; // Microseconds
const long led_on_duration_4 = led_on_duration_seconds_4*1000000; // Microseconds
const long led_on_duration_5 = led_on_duration_seconds_5*1000000; // Microseconds
const long led_on_duration_6 = led_on_duration_seconds_6*1000000; // Microseconds
const long led_on_duration_7 = led_on_duration_seconds_7*1000000; // Microseconds
const long led_on_duration_8 = led_on_duration_seconds_8*1000000; // Microseconds
const long led_on_duration_9 = led_on_duration_seconds_9*1000000; // Microseconds

const long led_timeout_1 = led_off_duration_seconds_1*1000000; //Microseconds
const long led_timeout_2 = led_off_duration_seconds_2*1000000;
const long led_timeout_3 = led_off_duration_seconds_3*1000000;
const long led_timeout_4 = led_off_duration_seconds_4*1000000;
const long led_timeout_5 = led_off_duration_seconds_5*1000000; //Microseconds
const long led_timeout_6 = led_off_duration_seconds_6*1000000;
const long led_timeout_7 = led_off_duration_seconds_7*1000000;
const long led_timeout_8 = led_off_duration_seconds_8*1000000;
const long led_timeout_9 = led_off_duration_seconds_9*1000000;

const long led_timeout = 600*1000000;

const int switch_trigger_pin = 10; // if high trigger led
const int switch_drive_pin = 2; //sends signal to switch which sends to trigger or ground
const int led_enable_pin = 4; //enable pin for L293D shield
const int led_trigger_pin = 5;//if switch trigger pin then triggers led

//variables
long led_on_start_1 = 0;
long led_on_start_2 = 0;
long led_on_start_3 = 0;
long led_on_start_4 = 0;
long led_on_start_5 = 0;
long led_on_start_6 = 0;
long led_on_start_7 = 0;
long led_on_start_8 = 0;
long led_on_start_9 = 0;

long led_off_time_1 = 0;
long led_off_time_2 = 0;
long led_off_time_3 = 0;
long led_off_time_4 = 0;
long led_off_time_5 = 0;
long led_off_time_6 = 0;
long led_off_time_7 = 0;
long led_off_time_8 = 0;
long led_off_time_9 = 0;

long led_timeout_over = 0;

void setup() {
  // put your setup code here, to run once:
  #ifdef DebugMode
    Serial.begin(9600);
    Serial.flush();
    Serial.println();
    Serial.print(program_name);
   #endif
   // Setup Pins
    pinMode(switch_trigger_pin, INPUT);
    pinMode(switch_drive_pin, OUTPUT);
    pinMode(led_enable_pin, OUTPUT);
    pinMode(led_trigger_pin, OUTPUT);
    // Set Outputs
    digitalWrite(switch_drive_pin, HIGH);
    digitalWrite(led_enable_pin, HIGH);
    digitalWrite(led_trigger_pin, LOW);
}

void loop() {

  if (switch_is_on() && micros()>(led_timeout_over)) {
     update_times();
     turn_on_leds();
  }
  else if ((micros()>led_off_time_1) && (micros()<led_on_start_2)){
    turn_off_leds();
  }
  else if ((micros()>led_on_start_2) && (micros()<led_off_time_2)){
  turn_on_leds();
}
  else if ((micros()>led_off_time_2) && (micros()<led_on_start_3)) {
    turn_off_leds();
  }
  else if ((micros()>led_on_start_3) && (micros()<led_off_time_3)) {
    turn_on_leds();
  }
  else if ((micros()>led_off_time_3) && (micros()<led_on_start_4)) {
    turn_off_leds();
  }
  else if ((micros()>led_on_start_4) && (micros()<led_off_time_4)) {
    turn_on_leds();
  }
  else if ((micros()>led_off_time_4) && (micros()<led_on_start_5)) {
    turn_off_leds();
  }
  else if ((micros()>led_on_start_5) && (micros()<led_off_time_5)) {
    turn_on_leds();
  }
  else if ((micros()>led_off_time_5) && (micros()<led_on_start_6)) {
    turn_off_leds();
  }
  else if ((micros()>led_on_start_6) && (micros()<led_off_time_6)) {
    turn_on_leds();
  }
  else if ((micros()>led_off_time_6) && (micros()<led_on_start_7)) {
    turn_off_leds();
  }
  else if ((micros()>led_on_start_7) && (micros()<led_off_time_7)) {
    turn_on_leds();
  }
  else if ((micros()>led_off_time_7) && (micros()<led_on_start_8)) {
    turn_off_leds();
  }
  else if ((micros()>led_on_start_8) && (micros()<led_off_time_8)) {
    turn_on_leds();
  }
  else if ((micros()>led_off_time_8) && (micros()<led_on_start_9)) {
    turn_off_leds();
  } 
  else if ((micros()>led_on_start_9) && (micros()<led_off_time_9)) {
    turn_on_leds();
  }
  else if (micros()>led_off_time_9){
    turn_off_leds();
  }

}

void update_times() {
  led_on_start_1 = micros();
  led_off_time_1 = led_on_start_1 + led_on_duration_1;
  led_timeout_over = led_off_time_1 + led_timeout;

  led_on_start_2 = led_off_time_1+led_timeout_1;
  led_off_time_2 = led_on_start_2+led_on_duration_2;

  led_on_start_3 = led_off_time_2+led_timeout_2;
  led_off_time_3 = led_on_start_3+led_on_duration_3;

  led_on_start_4 = led_off_time_3+led_timeout_3;
  led_off_time_4 = led_on_start_4+led_on_duration_4;

  led_on_start_5 = led_off_time_4+led_timeout_3;
  led_off_time_5 = led_on_start_5+led_on_duration_5;

  led_on_start_6 = led_off_time_5+led_timeout_5;
  led_off_time_6 = led_on_start_6+led_on_duration_6;

  led_on_start_7 = led_off_time_6+led_timeout_6;
  led_off_time_7 = led_on_start_7+led_on_duration_7;

  led_on_start_8 = led_off_time_7+led_timeout_7;
  led_off_time_8 = led_on_start_8+led_on_duration_8;

  led_on_start_9 = led_off_time_8+led_timeout_8;
  led_off_time_9 = led_on_start_9+led_on_duration_9;
  
  #ifdef CheckTimes
    Serial.println();
    Serial.print("Led Start Time: ");
    Serial.print(led_on_start_1);
    Serial.println();
    Serial.print("Led Off Time: ");
    Serial.print(led_off_time_4);
    Serial.println();
    Serial.print("Led Timeout Over: ");
    Serial.print(led_timeout_over);
    Serial.println();
  #endif
}

void turn_on_leds() {
  #ifdef LEDCommands
    Serial.println();
    Serial.print("Turning on LEDs");
    Serial.println();
  #endif
    digitalWrite(led_trigger_pin, HIGH);
}

void turn_off_leds() {
    #ifdef LEDCommands
      Serial.println();
      Serial.print("Turning off LEDs");
      Serial.println();
    #endif
   digitalWrite(led_trigger_pin, LOW);
}
bool switch_is_on() {
    #ifdef SwitchReader
      Serial.println();
      Serial.print("Checking Switch");
      Serial.println();
    #endif
    bool _switch_state;
   // #ifdef SwitchState
    //  Serial.println();
    //  Serial.print(digitalRead(switch_trigger_pin));
    //  Serial.println();
    //#endif

    circ_buff.push(digitalRead(switch_trigger_pin));
    rolling_hits = 0;
    for(int i=0; i<circ_buff.size(); i++) {
      rolling_hits += circ_buff[i];
    }
    //if (digitalRead(switch_trigger_pin)==HIGH) {
    if (rolling_hits > threshold) {
      _switch_state = true;
      #ifdef SwitchState
        Serial.println();
        Serial.print("Switch On");
        Serial.println();
      #endif
    }
    else {
      _switch_state = false;
    }
    return _switch_state;
}
