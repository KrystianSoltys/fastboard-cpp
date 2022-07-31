#include "application.hpp"

auto main(int argc, char** argv) -> int
{
	Application a(argc, argv);

	return a.exec();
}
