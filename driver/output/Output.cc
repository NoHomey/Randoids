#include "Output.hh"
#include <iostream>

namespace output_addon {
    using namespace v8;
    using namespace std;
    
    Persistent<Function> Output::constructor;
    
    Output::Output(const uint16_t& data, const uint16_t& clock, const uint16_t& latch, const uint16_t& blank)
    : data_(data), clock_(clock), latch_(latch), blank_(blank) {
        /*pinMode(data, OUTPUT);
        pinMode(clock, OUTPUT);
        pinMode(latch, OUTPUT);
        pinMode(blank, OUTPUT);*/
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
        if (args.IsConstructCall()) {
            uint16_t data = args[0]->ToUint32()->Value();
            uint16_t clock = args[1]->ToUint32()->Value();
            uint16_t latch = args[2]->ToUint32()->Value();
            uint16_t blank = args[3]->ToUint32()->Value();
            Output* obj = new Output(data, clock, latch, blank);
            obj->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        } else {
            const int argc = 4;
            Local<Value> argv[argc] = { args[0], args[1], args[2], args[3] };
            Local<Function> construct = Local<Function>::New(isolate, constructor);
            args.GetReturnValue().Set(construct->NewInstance(argc, argv));
        }
    }
    
    void Output::Write(const FunctionCallbackInfo<Value>& args) {
        //Output* obj = ObjectWrap::Unwrap<Output>(args.Holder());
        Local<Uint16Array> arr = Local<Uint16Array>::Cast(args[0]);
        for(unsigned int i = 0;i < arr->Length(); ++i) {
            Local<Value> item = arr->Get(i);
            uint32_t value = item->ToUint32()->Value();
            cout << "Output[" << i << "]:" << value << endl;
        }
    }   
}