#include "Output.hh"
#include <wiringPi.h>
#include <iostream>

namespace output_addon {
    #define LEDS 24
    using namespace v8;
    using namespace std;
    
    Persistent<Function> Output::constructor;
    
    Output::Output(const uint8_t& num, const uint16_t& data, const uint16_t& clock, const uint16_t& latch, const char* wire)
    : chips(num),
      data_(data),
      clock_(clock),
      latch_(latch),
      maxLEDs(num * LEDS),
      maxRGBLEDSs(num * LEDS / 3),
      buffer_(new uint16_t[num * LEDS]),
      red(0),
      green(1),
      blue(2) {
        pinMode(data, OUTPUT);
        pinMode(clock, OUTPUT);
        pinMode(latch, OUTPUT);
        string wiring = string(wire);
        uint8_t* ptr;
        ptr = (uint8_t*) &red
        *ptr = wiring.find('R');
        ptr = (uint8_t*) &green
        *ptr = wiring.find('G');
        ptr = (uint8_t*) &blue;
        *ptr = wiring.find('B');
    }
    
    Output::~Output() {}
    
    void Output::Init(Local<Object> exports) {
        Isolate* isolate = exports->GetIsolate();
        Local<FunctionTemplate> tmpl = FunctionTemplate::New(isolate, New);
        tmpl->SetClassName(String::NewFromUtf8(isolate, "Output"));
        tmpl->InstanceTemplate()->SetInternalFieldCount(4);
        NODE_SET_PROTOTYPE_METHOD(tmpl, "write", Write);
        NODE_SET_PROTOTYPE_METHOD(tmpl, "setLED", SetLED);
        NODE_SET_PROTOTYPE_METHOD(tmpl, "setRGBLED", SetRGBLED);
        constructor.Reset(isolate, tmpl->GetFunction());
        exports->Set(String::NewFromUtf8(isolate, "Output"), tmpl->GetFunction());
        wiringPiSetup();
    }
    
    void Output::New(const FunctionCallbackInfo<Value>& args) {
        uint8_t chips = args[0]->ToUint32()->Value();
        uint16_t data = args[1]->ToUint32()->Value();
        uint16_t clock = args[2]->ToUint32()->Value();
        uint16_t latch = args[3]->ToUint32()->Value();
        char* wire = *(String::Utf8Value(args[4]->ToString()));
        Output* obj = new Output(chips, data, clock, latch, wire);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    
    void Output::Write(const FunctionCallbackInfo<Value>& args) {
        Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
        digitalWrite(obj->latch_, LOW);
        for(int16_t i = obj->maxLEDs - 1;i >= 0; --i) {
            for (int8_t bit = 11; bit >=0 ; --bit) {
                digitalWrite(obj->clock_, LOW);
                digitalWrite(obj->data_, ((obj->buffer_[i] & (1 << bit)) ? HIGH : LOW));
                digitalWrite(obj->clock_, HIGH);
            }
        }
        digitalWrite(obj->clock_, LOW);
        digitalWrite(obj->latch_, HIGH);
        digitalWrite(obj->latch_, LOW);
    }
    
    void Output::SetLED(const FunctionCallbackInfo<Value>& args) {
        Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
        uint16_t led = args[0]->ToUint32()->Value();
        uint16_t pwm = args[1]->ToUint32()->Value();
        if(led >= obj->maxLEDs) {
            Isolate* isolate = args.GetIsolate();
            isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, "LED number must be between [0 and 24 * number of chips)")));
            return;
        }
        obj->buffer_[led] = pwm;
    }
    
    void Output::SetRGBLED(const FunctionCallbackInfo<Value>& args) {
        Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
        uint16_t rgb = args[0]->ToUint32()->Value();
        Local<Uint16Array> pwm = Local<Uint16Array>::Cast(args[1]);
        if(rgb >= obj->maxRGBLEDs) {
            Isolate* isolate = args.GetIsolate();
            isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, "RGB number must be between [0 and 8 * number of chips)")));
            return;
        }
        rgb *= 3;
        obj->buffer_[rgb + obj->red] = pwm->Get(obj->red)->ToUint32()->Value();
        obj->buffer_[rgb + obj->green] = pwm->Get(obj->green)->ToUint32()->Value();
        obj->buffer_[rgb + obj->blue] = pwm->Get(obj->blue)->ToUint32()->Value();
    }
}