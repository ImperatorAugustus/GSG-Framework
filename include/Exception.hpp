#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>

namespace util
{
	class Exception
	{
		public:
			Exception();
			Exception(std::string, ...);
			Exception(Exception, std::string, ...);

			~Exception();

			const char* what() const;

		private:
			std::string error;
	};
}

#endif // EXCEPTION_HPP

