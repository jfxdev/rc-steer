#ifndef Steer_h
#define Steer_h

#include "Arduino.h"

class Steer
{
  public:
    Steer(byte servo_pin, int input_min_reference = 0, int input_max_reference = 1023, unsigned int min_pos = 0, unsigned int max_pos = 180);
    void Setup(byte horn_pin = 0, byte horn_input_pin = 0, int horn_frequency = 1000);
    void Read(unsigned int input, bool hornInput = false);
    void Set();
  private:
    byte         _servo_pin;
    unsigned int _pos_x = 0;
    unsigned int _min_pos;
    unsigned int _max_pos;
    unsigned int _servo_pos = 0;
    unsigned int _input_read;
    int          _input_min_reference;
    int          _input_max_reference;
    byte         _horn_pin;
    byte         _horn_input_pin;
    bool         _horn_enabled = false;
    bool         _horn_read = false;
    bool         _horn = false;
    bool         _horn_frequency;

};

#endif
