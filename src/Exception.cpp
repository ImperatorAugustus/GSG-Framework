#include <include/Exception.hpp>

#include <cstdarg>

/*
 * Basic exception class that I had lying around.
 * Allows for throwing, catching and re-throwing with variable kinds of arguments.
 * Hint: when an exception is caught, a new exception can be thrown with the caught exception as its first argument,
 *    this can create a nice exception stacktrace to locate the error more precisely.
 *
 * For example:
 *     func loadgraphics() {
 *          try {
 *	          loadImage("file1.png");
 *	          loadImage("file2.png");
 *	          loadImage("file3.png");
 *          } catch (Exception ex) {
 *	          throw Exception(ex, "Failed to load graphics.");
 *          }
 *     }
 *
 * Re-throwing the caught exception allows to differentiate to where the exception originated from (if properly thrown from the loadImage function).
 * This can give a stacktrace such as:
 *
 *   Failed to load graphics.
 *       Failed to open file "file2.png".
 *       File does not exist.
 *
 * That stacktrace is a lot more helpful than just a simple "failed to load graphics" output.
 */

util::Exception::Exception()
{
	this->error = "";
}

util::Exception::Exception(std::string err, ...)
{
	char buf[1024 * 16];
	va_list arg_ptr;
	
	va_start(arg_ptr, err.c_str());
	vsnprintf(buf, sizeof(buf), err.c_str(), arg_ptr);
	va_end(arg_ptr);
	
	this->error = std::string(buf);
}

util::Exception::Exception(util::Exception ex, std::string err, ...)
{
	char buf[1024 * 16];
	va_list arg_ptr;
	
	va_start(arg_ptr, err.c_str());
	vsnprintf(buf, sizeof(buf), err.c_str(), arg_ptr);
	va_end(arg_ptr);
	
	this->error = std::string(buf) + std::string("\n") + ex.what();
}

util::Exception::~Exception()
{
}

const char* util::Exception::what() const
{
	return this->error.c_str();
}

