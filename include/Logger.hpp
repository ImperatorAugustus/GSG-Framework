#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <vector>

namespace util
{
	/*
	 * Basic enum instance for differentiating various debug level.
	 * If something is put to the logs with a lower level than the
	 * currently active level, the logger ignores it and just skips.
	 */
	enum Level
	{
		// Should only ever be shown in a DEBUG build
		Debug = 1,
		// Should only ever be used in a context where more verbal output is explicitly asked (test functions etc.)
		Verbose = 2,
		// For the user's info only, no further action required.
		Info = 3,
		// Something went wrong that is not immediately problematic, but user discretion is advised.
		Warning = 4,
		// Something went wrong that caused some unintended side-effects, but we can still run the program.
		Error = 5,
		// Something went wrong that irrevocably forces a system crash.
		Fatal = 6,
		
		All = 0
	};
	
	extern Level CurrentDebugLevel;
	static std::vector<std::string> LevelNames = { "NOLELVEL", "DEBUG", "VERBOSE", "INFO", "WARNING", "ERROR", "FATAL" };
	
	/*
	 * Basic logger class. Does not need to be instantized, automatically pipes things to stdout with some basic formatting.
	 * Could include a formatted clock in the output as well, but that might take up a lot of space.
	 * Optionally this class could be extended to include instantized loggers that flush to a file.
	 */
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
