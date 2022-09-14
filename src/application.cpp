#include "application.hpp"
#include <iostream>
Application::Application(int argc, char** argv)
	: argc(argc), argv(argv), m_ui(std::cout)
{
}

auto Application::exec() -> int
{
	Game x(m_ui, "Ala ma kota\n\
a kot ma Alee");

	x.play();


	return 0;
}


auto Application::appAbort(const std::string_view& _str) const noexcept -> void
{
	std::exit(EXIT_FAILURE);
}
