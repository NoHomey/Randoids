#include "TLC5947.hh"
#include <wiringPi.h>
#include <stdexcept>

#define LEDS 24
#define MAXPWM 4095

TLC5947::TLC5947(const uint16_t& chips, const uint8_t& data, const uint8_t& clock, const uint8_t& latch)
: chips_(chips), buffer_(new uint16_t[chips * LEDS]), data_(data), clock_(clock), latch_(latch)
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
    uint16_t i = chips_ * LEDS - 1;
    while(1) {
        uint8_t bit = 11;
        while(1) {
            digitalWrite(clock_, LOW);
            digitalWrite(data_, (buffer_[i] & (1 << bit)) ? HIGH : LOW);
            digitalWrite(clock_, HIGH);
            if(bit == 0) {
                break;
            }
            bit--;
        }
        if(i == 0) {
            break;
        }
        i--;
    }
    digitalWrite(clock_, LOW);
    digitalWrite(latch_, HIGH);
    digitalWrite(latch_, LOW);
}

void TLC5947::setLED(const uint16_t& led, const uint16_t& pwm) {
  throwError(led, LEDS * chips_, "LED number must be between [0 and 24 * number of chips)");
  throwError(pwm, MAXPWM, "LED pwm value must be between [0 and 4095)");
  buffer_[led] = pwm;
}

void TLC5947::setRGBLED(const uint16_t& rgb, const uint16_t* pwm) {
    throwError(rgb, LEDS * chips_ / 3, "RGB number must be between [0 and 8 * number of chips)");
    uint16_t led = rgb * 3;
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
