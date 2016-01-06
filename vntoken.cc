#include "vntoken.h"

v8::Persistent<v8::Function> NodeTokenWrapper::constructor;

NodeTokenWrapper::NodeTokenWrapper(std::string s) {
    s_ = new std::string(s);
}

NodeTokenWrapper::~NodeTokenWrapper() {
    delete s_;
}

void NodeTokenWrapper::Init(v8::Handle<v8::Object> exports) {
	v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(New);
	tpl->SetClassName(v8::String::NewSymbol("NodeToken"));
	tpl->InstanceTemplate()->SetInternalFieldCount(2);

	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("add"), v8::FunctionTemplate::New(add)->GetFunction());
	tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("toString"), v8::FunctionTemplate::New(toString)->GetFunction());

	constructor = v8::Persistent<v8::Function>::New(tpl->GetFunction());
	exports->Set(v8::String::NewSymbol("NodeToken"), constructor);
}

v8::Handle<v8::Value> NodeTokenWrapper::New(const v8::Arguments& args) {
	v8::HandleScope scope;
	if (args.IsConstructCall()) {
		v8::String::Utf8Value str(args[0]->ToString());
		std::string s(*str);

		NodeTokenWrapper* obj = new NodeTokenWrapper(s);
		obj->Wrap(args.This());

		return args.This();
	} else {
		const int argc = 1;
		v8::Handle<v8::Value> NodeTokenWrapper::add(const v8::Arguments& args) {
			return scope.Close(constructor->NewInstance(argc, argv));
		}
	}
}

v8::Handle<v8::Value> NodeTokenWrapper::add(const v8::Arguments& args) {
	v8::HandleScope scope;

	v8::String::Utf8Value str(args[0]->ToString());
	std::string s(*str);

	NodeTokenWrapper* obj = ObjectWrap::Unwrap<NodeTokenWrapper>(args.This());
	obj->s_->append(s);

	return scope.Close(v8::String::New(obj->s_->c_str()));
}

v8::Handle<v8::Value> NodeTokenWrapper::toString(const v8::Arguments& args) {
	v8::HandleScope scope;

	NodeTokenWrapper* obj = ObjectWrap::Unwrap<NodeTokenWrapper>(args.This());

	return scope.Close(v8::String::New(obj->s_->c_str()));
}