#ifndef ServoTimer2_h
#define ServoTimer2_h

#include <inttypes.h>

#define MIN_PULSE_WIDTH       750        // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2250        // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500        // default pulse width when servo is attached
#define FRAME_SYNC_PERIOD   20000        // total frame duration in microseconds 
#define NBR_CHANNELS 8                   // the maximum number of channels, don't change this 

typedef struct  {
      uint8_t nbr        :5 ;  // a pin number from 0 to 31
      uint8_t isActive   :1 ;  // false if this channel not enabled, pin only pulsed if true 
} ServoPin_t;

typedef struct {
  ServoPin_t Pin;
  uint8_t counter;  // Changed 'byte' to 'uint8_t'
  uint8_t remainder;  // Changed 'byte' to 'uint8_t'
}  servo_t;

class ServoTimer2
{
  public:
    // constructor:
    ServoTimer2();

    uint8_t attach(int);     // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
                             // the attached servo is pulsed with the current pulse width value, (see the write method)
    uint8_t attach(int, int, int); // as above but also sets min and max values for writes. 
    void detach();
    void write(int);         // store the pulse width in microseconds (between MIN_PULSE_WIDTH and MAX_PULSE_WIDTH) for this channel
    int read();              // returns current pulse width in microseconds for this servo
    bool attached();         // return true if this servo is attached 
 private:
    uint8_t chanIndex;      // index into the channel data for this servo
};

class ServoArrayT2
{
  public:
    // constructor:
    ServoArrayT2();

    uint8_t attach(int);     // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
                             // channels are assigned consecutively starting from 1
                             // the attached servo is pulsed with the current pulse width value, (see the write method)
    void detach(int);        // detach the servo on the given channel
    void write(int, int);    // store the pulse width in microseconds (between MIN_PULSE_WIDTH and MAX_PULSE_WIDTH) for the given channel
    int read(int);           // returns current pulse width in microseconds for the given channel
    bool attached(int);      // return true if the servo on the given channel is attached 
 private:
    uint8_t chanIndex;      // index into the channel data for this servo
};

#endif
