#include "TLC5947.hh"
#include <wiringPi.h>
#include <stdexcept>

#define LEDS 24
#define MAXPWM 4095

TLC5947::TLC5947(const uint8_t& num, const uint8_t& data, const uint8_t& clock, const uint8_t& latch)
: chips(num), buffer_(new uint16_t[num * LEDS]), data_(data), clock_(clock), latch_(latch)
{}

void TLC5947::throwError(const uint16_t& checked, const uint16_t& compared, const char* message) {
    if(checked >= compared) {
        throw std::invalid_argument(message);
    }
}

TLC5947::~TLC5947(void) {
    delete[] buffer_;
}

void TLC5947::write(void) {
    digitalWrite(latch_, LOW);
    for (int16_t i = LEDS * 8 - 1;i >= 0;--i) {
        for (int8_t bit = 11; bit >=0 ; --bit) {
            digitalWrite(clock_, LOW);
            digitalWrite(data_, (buffer_[i] & (1 << bit)) ? HIGH : LOW);
            digitalWrite(clock_, HIGH);
        }
    }
    digitalWrite(clock_, LOW);
    digitalWrite(latch_, HIGH);
    digitalWrite(latch_, LOW);
}

void TLC5947::setLED(const uint8_t& led, const uint16_t& pwm) {
  throwError(led, LEDS * 8, "LED number must be between [0 and 24 * number of chips)");
  throwError(pwm, MAXPWM, "LED pwm value must be between [0 and 4095)");
  buffer_[led] = pwm;
}

void TLC5947::setRGBLED(const uint8_t& rgb, const uint16_t* pwm) {
    throwError(rgb, LEDS * 8 / 3, "RGB number must be between [0 and 8 * number of chips)");
    uint8_t led = rgb * 3;
    setLED(led, pwm[1]);
    setLED(led + 1, pwm[0]);
    setLED(led + 2, pwm[2]);
}

void TLC5947::setup(void) {
    wiringPiSetup();
    pinMode(data_, OUTPUT);
    pinMode(clock_, OUTPUT);
    pinMode(latch_, OUTPUT);
}
