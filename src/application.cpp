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

	while (true)
	{
		switch (x.main_menu())
		{
		case Game::ModulesEnum::sw_PlayGame:
			x.play();
			break;
		case Game::ModulesEnum::sw_Options:
			break;
		case Game::ModulesEnum::sw_Statistics:
			break;
		case Game::ModulesEnum::sw_Exit:
			return EXIT_SUCCESS;

		default:
			break;
		}
	}

	return EXIT_FAILURE;
}


auto Application::appAbort(const std::string_view& _str) const noexcept -> void
{
	std::exit(EXIT_FAILURE);
}
