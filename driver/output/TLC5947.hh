#ifndef TLC5947_H
#define TLC5947_H

#include <stdint.h>

class Adafruit_TLC5947 {
    public:
        TLC5947(const uint8_t& num, const uint8_t& data, const uint8_t& clock, const uint8_t& latch);
        ~TLC5947(void);
        void setLED(const uint16_t& led, const uint16_t& pwm);
        void setRGBLED(const uint8_t& rgb, const uint16_t* pwm);
        void write(void);
        void setup(void);
        const uint8_t& chips;
        const uint8_t& maxLEDs;
        const uint8_t& maxRGBLEDs;
  
    private:
        static void throwError(const uint16_t& checked, const uint16_t& compared, const char* message);
        uint16_t *buffer_;
        const uint8_t data_;
        const uint16_t clock_;
        const uint16_t latch_;    
};

#endif