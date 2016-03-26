#include <node.h>
#include <wiringPi.h>
#include <stdio.h>

namespace input_addon {
    using namespace v8;
    
    void Input(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        int buttons;
        switch(getchar()) {
            case 'a':
                buttons = 1;
                break;
            case 's':
                buttons = 5;
                break;
            case 'd':
                buttons = 4;
                break;
            default:
                buttons = 0;
                break;
        }
        Local<Number> input = Number::New(isolate, buttons);
        args.GetReturnValue().Set(input);
    }

    void Init(Local<Object> exports, Local<Object> module) {
        NODE_SET_METHOD(module, "exports", Input);
    }

    NODE_MODULE(input, Init)
}