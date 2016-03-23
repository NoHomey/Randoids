#include <node.h>
#include <iostream>

namespace output_addon {
    using namespace std;
    using namespace v8;
    
    void Print(const FunctionCallbackInfo<Value>& args) {
        Local<Uint16Array> arr = Local<Uint16Array>::Cast(args[0]);
        for(unsigned int i = 0;i < arr->Length(); ++i) {
            Local<Value> item = arr->Get(i);
            cout << "Output[" << i << "]:" << item->ToUint32()->Value() << endl;
        }
    }

    void Init(Local<Object> exports) {
        NODE_SET_METHOD(exports, "print", Print);
    }

    NODE_MODULE(output, Init)
}