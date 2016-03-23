#include <node.h>
#include "Output.hh"

namespace output_addon {
    using namespace v8;

    void Init(Local<Object> exports) {
        Output::Init(exports);
    }

    NODE_MODULE(output, Init)
}