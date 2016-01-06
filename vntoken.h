#ifndef VN_TOKEN_H
#define VN_TOKEN_H

#include <string>
#include <node.h>

class NodeTokenWrapper 
	: public node::ObjectWrap {
	private:
		std::string* s_;

		explicit NodeTokenWrapper(std::string s = "");
		~NodeTokenWrapper();

	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> add(const v8::Arguments& args);
	static v8::Handle<v8::Value> toString(const v8::Arguments& args);

	public:
		static void Init(v8::Handle<v8::Object> exports);
};

#endif