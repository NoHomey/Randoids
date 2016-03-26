#include "TLC5947.hh"
#include <wiringPi.h>
#include <stdexcept>
#include <string>
#include <iostream>

#define LEDS 24
#define MAXPWM 4096

TLC5947::RGB::RGB(const char* wiring) {
    std::string buffer = std::string(wiring);
    red = buffer.find('R');
    green = buffer.find('G');
    blue = buffer.find('B');
}

TLC5947::TLC5947(const uint8_t& chips, const uint8_t& data, const uint8_t& clock, const uint8_t& latch, const char* wiring)
: buffer_(new uint16_t[chips * LEDS]), chips_(chips), data_(data), clock_(clock), latch_(latch), wiring_(RGB(wiring)) {
    pinMode(data_, OUTPUT);
    pinMode(clock_, OUTPUT);
    pinMode(latch_, OUTPUT);
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

void TLC5947::throwOutOfRangeError(const uint16_t& checked, const uint16_t& compared, const char* message, const char* method) {
    if(checked >= compared) {
        std::string report = std::string(message);
        report += std::string(" when calling '") + std::string(method) + std::string("' with ") + std::to_string(checked);
        throw std::out_of_range(report);
    }
}

void TLC5947::setLED(const uint16_t& led, const uint16_t& pwm, const char* method) {
    throwOutOfRangeError(led, LEDS * chips_, "LED number must be between [0 and 24 * number of chips)", method);
    throwOutOfRangeError(pwm, MAXPWM, "LED pwm value must be between [0 and 4095)", method);
    buffer_[led] = pwm;
}

void TLC5947::setRGBLED(const uint16_t& rgb, const uint16_t* pwm, const char* method) {
    throwOutOfRangeError(rgb, LEDS * chips_ / 3, "RGB number must be between [0 and 8 * number of chips)", method);
    uint16_t led = rgb * 3;
    setLED(led + wiring_.red, pwm[0], method);
    setLED(led + wiring_.green, pwm[1], method);
    setLED(led + wiring_.blue, pwm[2], method);
}