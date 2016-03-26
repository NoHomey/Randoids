#include <node.h>
#include <wiringPi.h>

namespace wiringPiSetup_addon {
    using namespace v8;
    
    void WiringPiSetup(const FunctionCallbackInfo<Value>& args) {
        wiringPiSetup();
    }

    void Init(Local<Object> exports, Local<Object> module) {
        NODE_SET_METHOD(module, "exports", WiringPiSetup);
    }

    NODE_MODULE(wiringPiSetup, Init)
}
