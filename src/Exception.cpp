#include <include/Exception.hpp>

#include <cstdarg>

util::Exception::Exception() {
	this->error = "";
}

util::Exception::Exception(std::string err, ...) {
	char buf[1024 * 16];
	va_list arg_ptr;
	
	va_start(arg_ptr, err.c_str());
	vsnprintf(buf, sizeof(buf), err.c_str(), arg_ptr);
	va_end(arg_ptr);
	
	this->error = std::string(buf);
}

util::Exception::Exception(util::Exception ex, std::string err, ...) {
	char buf[1024 * 16];
	va_list arg_ptr;
	
	va_start(arg_ptr, err.c_str());
	vsnprintf(buf, sizeof(buf), err.c_str(), arg_ptr);
	va_end(arg_ptr);
	
	this->error = std::string(buf) + std::string("\n") + ex.what();
}

util::Exception::Exception(std::string err, util::Exception ex, ...) {
	char buf[1024 * 16];
	va_list arg_ptr;
	
	va_start(arg_ptr, err.c_str());
	vsnprintf(buf, sizeof(buf), err.c_str(), arg_ptr);
	va_end(arg_ptr);
	
	this->error = std::string(buf) + std::string("\n") + ex.what();
}

util::Exception::~Exception() {
}

const char* util::Exception::what() const {
	return this->error.c_str();
}

