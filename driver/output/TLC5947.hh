#ifndef TLC5947_H
#define TLC5947_H

#include <stdint.h>

class TLC5947 {
    public:
        TLC5947(const uint8_t& chips, const uint8_t& data, const uint8_t& clock, const uint8_t& latch, const char* wiring);
        ~TLC5947(void);
        void setLED(const uint16_t& led, const uint16_t& pwm, const char* method = "setLED");
        void setRGBLED(const uint16_t& rgb, const uint16_t* pwm, const char* method = "setRGBLED");
        void clearLED(const uint16_t& led, const char* method = "clearLED");
        void clearRGBLED(const uint16_t& rgb, const char* method = "clearRGBLED");
        void write(void);

    private:

       struct RGB {
            uint8_t red;
            uint8_t green;
            uint8_t blue;
            RGB(const char* wiring);
        };

        uint16_t* buffer_;
        const uint8_t chips_, data_, clock_, latch_;
        const RGB wiring_;
        static void throwOutOfRangeError(const uint16_t& checked, const uint16_t& compared, const char* message, const char* method);
};

#endif
