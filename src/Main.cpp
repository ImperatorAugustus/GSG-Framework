#include <include/Engine.hpp>
#include <include/Exception.hpp>
#include <include/Logger.hpp>

int main(int argc, char* argv[])
{
	eng::Engine* engine;
	
	try
	{
		engine = new eng::Engine();
		engine->run();
	}
	catch (const util::Exception& ex)
	{
		util::Log(util::Error) << ex.what();
	}
	
	delete engine;
}
