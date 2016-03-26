#include "Output.hh"

namespace output_addon {
    using namespace v8;
    using namespace std;
    
    Persistent<Function> Output::constructor;
    
    Output::Output(const uint16_t& chips, const uint8_t& data, const uint8_t& clock, const uint8_t& latch)
    : TLC5947(chips, data, clock, latch) {}
        
    Output::~Output() {}
    
    void Output::Init(Local<Object> exports) {
        Isolate* isolate = exports->GetIsolate();
        Local<FunctionTemplate> tmpl = FunctionTemplate::New(isolate, New);
        tmpl->SetClassName(String::NewFromUtf8(isolate, "Output"));
        tmpl->InstanceTemplate()->SetInternalFieldCount(4);
        NODE_SET_PROTOTYPE_METHOD(tmpl, "setup", Setup);
        NODE_SET_PROTOTYPE_METHOD(tmpl, "write", Write);
        NODE_SET_PROTOTYPE_METHOD(tmpl, "setLED", SetLED);
        NODE_SET_PROTOTYPE_METHOD(tmpl, "setRGBLED", SetRGBLED);
        constructor.Reset(isolate, tmpl->GetFunction());
        exports->Set(String::NewFromUtf8(isolate, "Output"), tmpl->GetFunction());
    }
    
    void Output::New(const FunctionCallbackInfo<Value>& args) {
        uint16_t chips = args[0]->ToUint32()->Value();
        uint8_t data = args[1]->ToUint32()->Value();
        uint8_t clock = args[2]->ToUint32()->Value();
        uint8_t latch = args[3]->ToUint32()->Value();
        //char* wire = *(String::Utf8Value(args[4]->ToString()));
        Output* obj = new Output(chips, data, clock, latch);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    
    void Output::Setup(const FunctionCallbackInfo<Value>& args) {
        Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
        obj->setup();
    }
    
    void Output::ThrowError(const FunctionCallbackInfo<Value>& args, const invalid_argument& error) {
        Isolate* isolate = args.GetIsolate();
        isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, error.what())));   
    }
    
    void Output::Write(const FunctionCallbackInfo<Value>& args) {
        Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
        obj->write();
    }
    
    void Output::SetLED(const FunctionCallbackInfo<Value>& args) {
         try {
            uint16_t led = args[0]->ToUint32()->Value();
            uint16_t pwm = args[1]->ToUint32()->Value();
            Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
            obj->setLED(led, pwm);
        } catch (const invalid_argument& error) {
            ThrowError(args, error);
        }
    }
    
    void Output::SetRGBLED(const FunctionCallbackInfo<Value>& args) {
        try {
            Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
            uint16_t rgb = args[0]->ToUint32()->Value();
            Local<Uint16Array> array = Local<Uint16Array>::Cast(args[1]);
            uint16_t pwm[3];
            for(uint8_t i = 0; i < 3; ++i) {
                pwm[i] = array->Get(i)->ToUint32()->Value();
            }
            obj->setRGBLED(rgb, pwm);
        } catch (const invalid_argument& error) {
            ThrowError(args, error);
        }
    }
}
