#include "vntoken.h"

using namespace v8;

v8::Persistent<v8::Function> NodeTokenWrapper::constructor;

NodeTokenWrapper::NodeTokenWrapper(std::string s) {
    s_ = new std::string(s);
}

NodeTokenWrapper::~NodeTokenWrapper() {
    delete s_;
}

void NodeTokenWrapper::Init(v8::Handle<v8::Object> exports) {
	Isolate* isolate = Isolate::GetCurrent();

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "NodeToken"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "add", add);
	// NODE_SET_PROTOTYPE_METHOD(tpl, "toString", toString);

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

void NodeTokenWrapper::add(const v8::FunctionCallbackInfo<v8::Value>&  args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);


	v8::String::Utf8Value str(args[0]->ToString());
	std::string s(*str);

	NodeTokenWrapper* obj = ObjectWrap::Unwrap<NodeTokenWrapper>(args.This());
	obj->s_->append(s);

	args.GetReturnValue().Set(obj->s_->c_str());
}

void NodeTokenWrapper::toString(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	NodeTokenWrapper* obj = ObjectWrap::Unwrap<NodeTokenWrapper>(args.This());

	args.GetReturnValue().Set(obj->s_->c_str());
}