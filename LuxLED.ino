/*
 Name:    LED_Experiment_Code_Lux.ino
 Created: 11/16/2022 11:26:14 AM
 Author:  Darik A. O'Neil & Lux Steinberg, Rafael Yuste Laboratory, Columbia University
*/

/*
This code runs LED experiment. Requires Arduino UNO, L293D motor shield or equivalent,
X number of LEDs, and a single-pole double throw switch.
 
 */

String program_name = "LED_Experiment";

// Debug Mode
//#define DebugMode // remove "//" to enter debug mode
//#define LEDCommands // remove "//" to debug led commands
//#define SwitchReader // remove "//" to debug switch reader
//#define CheckTimes // remove "//" to debug times

//parameters
const int led_on_duration_seconds = 5;
const int led_timeout_seconds = 5;
const long led_on_duration = led_on_duration_seconds*1000000; // Microseconds
const long led_timeout = led_timeout_seconds*1000000; //Microseconds

//pins
const int switch_trigger_pin = 2; // if high trigger led
const int switch_drive_pin = 3; //sends signal to switch which sends to trigger or ground
const int led_enable_pin = 4; //enable pin for L293D shield
const int led_trigger_pin = 5;//if switch trigger pin then triggers led

//variables
long led_on_start = 0;
long led_off_time = 0;
long led_timeout_over = 0;

void setup() {
  // put your setup code here, to run once:
  #ifdef DebugMode
    Serial.begin(115200);
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

  if (switch_is_on && micros()>(led_timeout_over)) {
     update_times();
     turn_on_leds();
  }
  else if (switch_is_on && micros()>led_off_time){
    turn_off_leds();
  }
  
}

void update_times() {
  led_on_start = micros();
  led_off_time = led_on_start + led_on_duration;
  led_timeout_over = led_off_time + led_timeout;
  #ifdef CheckTimes
    Serial.println();
    Serial.print("Led Start Time: ");
    Serial.print(led_on_start);
    Serial.println();
    Serial.print("Led Off Time: ");
    Serial.print(led_off_time);
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
    if (digitalRead(switch_trigger_pin)==HIGH) {
      _switch_state = true;
    }
    else {
      _switch_state = false;
    }
    return _switch_state;
}
