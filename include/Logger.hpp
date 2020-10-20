#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <vector>

namespace util
{
	enum Level
	{
		Debug = 1,
		Verbose = 2,
		Info = 3,
		Warning = 4,
		Error = 5,
		
		All = 0
	};
	
	extern Level CurrentDebugLevel;
	static std::vector<std::string> LevelNames = { "NOLELVEL", "DEBUG", "VERBOSE", "INFO", "WARNING", "ERROR" };
	
	class Log
	{
	private:
		Level level;

	public:
		Log(Level level) {
			this->level = level;

			if (this->level >= CurrentDebugLevel) {
				std::cout << "[" << LevelNames[this->level] << "]: ";
			}
		}

		template<typename T> Log& operator<<(T&& rhs) {
			if (this->level >= CurrentDebugLevel) {
				std::cout << std::forward<T>(rhs);
			}

			return (*this);
		}

		~Log() {
			if (this->level >= CurrentDebugLevel) {
				std::cout << std::endl;
			}
		}
	};
}

#endif // LOGGER_HPP
