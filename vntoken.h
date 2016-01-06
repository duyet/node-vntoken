#ifndef VN_TOKEN_H
#define VN_TOKEN_H

#include <string>
#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>

using namespace v8;

class NodeTokenWrapper 
	: public node::ObjectWrap {
	private:
		std::string* s_;

		explicit NodeTokenWrapper(std::string s = "");
		~NodeTokenWrapper();

	static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void add(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void toString(const v8::FunctionCallbackInfo<v8::Value>& args);

	static v8::Persistent<v8::Function> constructor;

	public:
		static void Init(v8::Handle<v8::Object> exports);
};

#endif