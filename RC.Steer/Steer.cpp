#include "Steer.h"
#include <VarSpeedServo.h>

VarSpeedServo _servo;

unsigned long int servo_time_before = 0, horn_time_before = 0;

Steer::Steer(byte servo_pin, int input_min_reference, int input_max_reference, unsigned int min_pos, unsigned int max_pos){
  _servo_pin = servo_pin;
  _min_pos = min_pos;
  _max_pos = max_pos;
  _input_min_reference = input_min_reference;
  _input_max_reference = input_max_reference;
}

void Steer::Read(unsigned int input, bool horn_input){
  _servo_pos = map(input, _input_min_reference, _input_max_reference, _min_pos, _max_pos);
  if (_horn_enabled) {
    _horn_read = digitalRead(_horn_input_pin);
    Serial.println(_horn);
  }
}

void Steer::Set(){
  if(millis() - servo_time_before >= 150) {
    servo_time_before = millis();
    _servo.write(_servo_pos);
  }

  if(millis() - horn_time_before >= 100) {
    if (_horn_enabled) {
      if (_horn_read == LOW) {
        if(!_horn){
          horn_time_before = millis();
          tone(_horn_pin, _horn_frequency);
          _horn = true;
        }
      } else {
        if(_horn){
          horn_time_before = millis();
          noTone(_horn_pin);
          _horn = false;
        }
      }
    }
  }
}

void Steer::Setup(byte horn_pin, byte horn_input_pin, int horn_frequency){
  _servo.attach(_servo_pin);
  if ((horn_pin != 0) && (horn_input_pin != 0)) {
    _horn_enabled = true;
    _horn_pin = horn_pin;
    _horn_input_pin = horn_input_pin;
    _horn_frequency = horn_frequency;
    pinMode(_horn_pin, OUTPUT);
    pinMode(_horn_input_pin, INPUT_PULLUP);
  }

  Serial.begin(115200);
}
