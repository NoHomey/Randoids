#include "Output.hh"
#include <wiringPi.h>

namespace output_addon {
    using namespace v8;
    
    Persistent<Function> Output::constructor;
    
    Output::Output(const uint16_t& data, const uint16_t& clock, const uint16_t& latch, const uint16_t& blank = -1)
    : data_(data), clock_(clock), latch_(latch), blank_(blank) {
        pinMode(data, OUTPUT);
        pinMode(clock, OUTPUT);
        pinMode(latch, OUTPUT);
        pinMode(blank, OUTPUT);
    };
    
    Output::~Output() {};
    
    void Output::Init(Local<Object> exports) {
        Isolate* isolate = exports->GetIsolate();
        Local<FunctionTemplate> tmpl = FunctionTemplate::New(isolate, New);
        tmpl->SetClassName(String::NewFromUtf8(isolate, "Output"));
        tmpl->InstanceTemplate()->SetInternalFieldCount(4);
        NODE_SET_PROTOTYPE_METHOD(tmpl, "write", Write);
        constructor.Reset(isolate, tmpl->GetFunction());
        exports->Set(String::NewFromUtf8(isolate, "Output"), tmpl->GetFunction());
    }
    
    void Output::New(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        uint16_t data = args[0]->ToUint32()->Value();
        uint16_t clock = args[1]->ToUint32()->Value();
        uint16_t latch = args[2]->ToUint32()->Value();
        uint16_t blank = args[3]->ToUint32()->Value();
        Output* obj = new Output(data, clock, latch, blank);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    
    void Output::Write(const FunctionCallbackInfo<Value>& args) {
        Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
        Local<Uint16Array> arr = Local<Uint16Array>::Cast(args[0]);
        if(obj->blank_ > -1) {
            digitalWrite(obj->blank_, LOW);
        }
        for(unsigned int i = 0;i < arr->Length(); ++i) {
            Local<Value> item = arr->Get(i);
            uint32_t value = item->ToUint32()->Value();
            for (int8_t bit = 11; bit >=0 ; --bit) {
                digitalWrite(obj->clock_, LOW);
                digitalWrite(obj->data_, ((value & (1 << bit)) ? HIGH : LOW));
                digitalWrite(obj->clock_, HIGH);
            }
            digitalWrite(obj->clock_, LOW);
            digitalWrite(obj->latch_, HIGH);
            digitalWrite(obj->latch_, LOW);
        }
    }   
}