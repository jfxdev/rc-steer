#ifndef Steer_h
#define Steer_h

#include "Arduino.h"

class Steer
{
  public:
    Steer(byte servo_pin, int input_min_reference = 0, int input_max_reference = 1023, unsigned int servo_min_pos = 0, unsigned int servo_max_pos = 180, int tolerated_error_margin = 10);
    void Setup(byte horn_pin = 0, byte horn_input_pin = 0, int horn_frequency = 1000);
    void Read(unsigned int input, bool hornInput = false);
    void Set();
    byte Direction();
  private:
    byte         _servo_pin;
    unsigned int _servo_pos = 0;
    int          _servo_error_margin;
    unsigned int _servo_min_pos;
    unsigned int _servo_max_pos;
    int          _input_min_reference;
    int          _input_max_reference;
    byte         _horn_pin;
    byte         _horn_input_pin;
    bool         _horn_enabled = false;
    bool         _horn_read = false;
    bool         _horn = false;
    int          _horn_frequency;
};

#endif
