#define _GLIBCXX_USE_CXX11_ABI 0

#include "token/Machine.h"
#include "token/FeaturesSelection.h"
#include "vntoken.h"

using namespace v8;

v8::Persistent<v8::Function> NodeTokenWrapper::constructor;

NodeTokenWrapper::NodeTokenWrapper(std::string s) {
    s_ = s;
}

NodeTokenWrapper::~NodeTokenWrapper() {
    // delete s_;
}

void NodeTokenWrapper::Init(v8::Handle<v8::Object> exports) {
	Isolate* isolate = Isolate::GetCurrent();

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "NodeToken"));
	tpl->InstanceTemplate()->SetInternalFieldCount(2);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "toString", toString);
	NODE_SET_PROTOTYPE_METHOD(tpl, "token", token);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "NodeToken"),
		tpl->GetFunction());
}

void NodeTokenWrapper::New(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.IsConstructCall()) {
		v8::String::Utf8Value str(args[0]->ToString());
		std::string s(*str);

		NodeTokenWrapper* obj = new NodeTokenWrapper(s);
		obj->Wrap(args.This());

		args.GetReturnValue().Set(args.This());
	} else {
		const int argc = 1;

		Local<Value> argv[argc] = { args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);

		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}


void NodeTokenWrapper::toString(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	NodeTokenWrapper* obj = ObjectWrap::Unwrap<NodeTokenWrapper>(args.This());

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, obj->s_.c_str()));
}

void NodeTokenWrapper::token(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	NodeTokenWrapper* obj = ObjectWrap::Unwrap<NodeTokenWrapper>(args.This());
	
	// Token string
	std::Machine predictor(3, "", std::PREDICT);
	if (!predictor.load()) {
		printf("%s\n", "Failed to load data token model");
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, ""));
		return;
	}
	std::string *s = new std::string(obj->s_);
	std::string result = predictor.segment(*s);
	std::string *ss = new std::string(result);

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, ss->c_str()));
}

