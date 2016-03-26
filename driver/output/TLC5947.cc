#include "TLC5947.hh"
#include <wiringPi.h>
#include <stdexcept>
#include <string> 

#define LEDS 24
#define MAXPWM 4096

TLC5947::TLC5947(const uint8_t& chips, const uint8_t& data, const uint8_t& clock, const uint8_t& latch)
: buffer_(new uint16_t[chips * LEDS]), chips_(chips), data_(data), clock_(clock), latch_(latch)
{}

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

void TLC5947::throwOutOfRangeError(const uint16_t& checked, const uint16_t& compared, const char* message, const char* method) {
    if(checked >= compared) {
        std::string formatted = std::string(message);
        formated += "when calling '" + method + "' with " + std::to_string(cheked) + std::endl;
        throw std::out_of_range(formated);
    }
}

void TLC5947::setLED(const uint16_t& led, const uint16_t& pwm) {
    throwOutOfRangeError(led, LEDS * chips_, "LED number must be between [0 and 24 * number of chips)");
    throwOutOfRangeError(pwm, MAXPWM, "LED pwm value must be between [0 and 4095)", "setLED");
    buffer_[led] = pwm;
}

void TLC5947::setRGBLED(const uint16_t& rgb, const uint16_t* pwm) {
    throwOutOfRangeError(rgb, LEDS * chips_ / 3, "RGB number must be between [0 and 8 * number of chips)", "setRGBLED");
    uint16_t led = rgb * 3;
    setLED(led, pwm[2]);
    setLED(led + 1, pwm[0]);
    setLED(led + 2, pwm[1]);
}

void TLC5947::setup(void) {
    pinMode(data_, OUTPUT);
    pinMode(clock_, OUTPUT);
    pinMode(latch_, OUTPUT);
}
