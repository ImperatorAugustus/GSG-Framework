#include <include/Logger.hpp>

// Set the current debug log level.
// Preferably, if we ever have a separate DEBUG build target, we would want
//    the logging debug level to be set to a low level for that one, and a
//    higher level for the main build target. For now, I've set this to low.
util::Level util::CurrentDebugLevel = util::Info;
