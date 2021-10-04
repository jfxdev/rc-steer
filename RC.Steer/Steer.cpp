#include "Steer.h"
#include <VarSpeedServo.h>

VarSpeedServo _servo;

unsigned long int servo_time_before = 0, horn_time_before = 0;
int servo_central_pos, servo_central_pos_min, servo_central_pos_max, servo_error_margin_min, servo_error_margin_max;

Steer::Steer(byte servo_pin, int input_min_reference, int input_max_reference, unsigned int servo_min_pos, unsigned int servo_max_pos, int tolerated_error_margin){
  _servo_pin = servo_pin;
  _servo_min_pos = servo_min_pos;
  _servo_max_pos = servo_max_pos;
  _servo_error_margin = tolerated_error_margin;

  _input_min_reference = input_min_reference;
  _input_max_reference = input_max_reference;

  servo_central_pos = (_servo_max_pos / 2) + _servo_min_pos;
  servo_central_pos_min = servo_central_pos - tolerated_error_margin;
  servo_central_pos_max = servo_central_pos + tolerated_error_margin;
}

void Steer::Read(unsigned int input, bool horn_input){
  _servo_pos = map(input, _input_min_reference, _input_max_reference, _servo_min_pos, _servo_max_pos);
  if (_horn_enabled) {
    _horn_read = digitalRead(_horn_input_pin);
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

byte Steer::Direction(){
  if ((_servo_pos >= servo_central_pos_min) && (_servo_pos <= servo_central_pos_max)){
     return 0;
  } else if (_servo_pos < servo_central_pos_min) {
     return 1;
  }
  return 2;
}
