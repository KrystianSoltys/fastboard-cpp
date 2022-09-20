#include "application.hpp"

Application::Application(int argc, char** argv)
	: argc(argc), argv(argv), m_ui(std::cout)
{
}

auto Application::exec() -> int
{
	std::size_t ct = 0;
	Game x(m_ui);

	while (true)
	{
		switch (x.main_menu())
		{
		case Game::ModulesEnum::sw_PlayGame:
			x.play(Data::texts.at(ct % Data::texts.size()));
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

		++ct;
	}

	return EXIT_FAILURE;
}


auto Application::appAbort(const std::string_view& _str) const noexcept -> void
{
	std::exit(EXIT_FAILURE);
}
