#include <node.h>
#include "vntoken.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  NodeTokenWrapper::Init(exports);
}

NODE_MODULE(addon, InitAll)