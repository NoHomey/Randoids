#include "Output.hh"
#include <wiringPi.h>
#include <iostream>

namespace output_addon {
    #define LEDS 24
    #define MAXPWM 4095
    using namespace v8;
    using namespace std;
    
    Persistent<Function> Output::constructor;
    
    Output::Output(const uint8_t& num, const uint16_t& data, const uint16_t& clock, const uint16_t& latch, const char* wire)
    : chips(num),
      maxLEDs(num * LEDS),
      maxRGBLEDs(num * LEDS / 3),
      red(1),
      green(2),
      blue(0),
      data_(data),
      clock_(clock),
      latch_(latch),
      buffer_(new uint16_t[num * LEDS]) {
        pinMode(data, OUTPUT);
        pinMode(clock, OUTPUT);
        pinMode(latch, OUTPUT);
        string wiring = string(wire);
       /*uint8_t* ptr;
        ptr = (uint8_t*)(&red);
        *ptr = wiring.find('R');
        ptr = (uint8_t*)(&green);
        *ptr = wiring.find('G');
        ptr = (uint8_t*)(&blue);
        *ptr = wiring.find('B');*/
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
    
    bool Output::ThrowError(const uint16_t& checked, const uint16_t& compared, const FunctionCallbackInfo<Value>& args, const char* message) {
        if(checked >= compared) {
            Isolate* isolate = args.GetIsolate();
            isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, message)));
            return true;
        }
        return false;    
    }
    
    void Output::Write(const FunctionCallbackInfo<Value>& args) {
        Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
        digitalWrite(obj->latch_, LOW);
        for(int16_t i = obj->maxLEDs - 1;i >= 0; --i) {
            cout << i << " " << obj->buffer_[i] << endl;
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
    
    void Output::SetLED(Output* obj, const FunctionCallbackInfo<Value>& args, const uint8_t& led, const uint16_t& pwm) {
        if(!ThrowError(led, obj->maxLEDs, args, "LED number must be between [0 and 24 * number of chips)")) {
            if(!ThrowError(pwm, MAXPWM, args, "LED pwm value must be between [0 and 4095)")) {
                obj->buffer_[led] = pwm;
            }
        }       
    }
    
    void Output::SetLED(const FunctionCallbackInfo<Value>& args) {
        Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
        uint16_t led = args[0]->ToUint32()->Value();
        uint16_t pwm = args[1]->ToUint32()->Value();
        SetLED(obj, args, led, pwm);
    }
    
    void Output::SetRGBLED(const FunctionCallbackInfo<Value>& args) {
        Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
        uint16_t rgb = args[0]->ToUint32()->Value();
        Local<Uint16Array> pwm = Local<Uint16Array>::Cast(args[1]);
        if(!ThrowError(rgb, obj->maxRGBLEDs, args, "RGB number must be between [0 and 8 * number of chips)")) {
            rgb *= 3;
            SetLED(obj, args, rgb + obj->red, pwm->Get(obj->red)->ToUint32()->Value());
            SetLED(obj, args, rgb + obj->blue, pwm->Get(obj->blue)->ToUint32()->Value());
            SetLED(obj, args, rgb + obj->green, pwm->Get(obj->green)->ToUint32()->Value());
        }
    }
}
