#ifndef GAME_HPP
#define GAME_HPP


#ifdef _WIN32
#include "win/ui.hpp"

#elif _UNIX
#include "unix/ui.hpp"

#endif //_WIN32


#include <string>
#include <sstream>
#include <vector>
#include <array>

class Game
{
public:

	explicit Game(UI&, const std::string&);

	enum class ModulesEnum { sw_PlayGame = 1, sw_Options, sw_Statistics, sw_Exit };
	struct s_Results
	{
		double rate;
		std::size_t ct_correct;
		std::size_t ct_incorrect;
	};

    auto play() -> void;
	auto main_menu() -> ModulesEnum;
	auto check_line(const std::string_view&, const std::string_view&) -> s_Results;

private:
	UI& ui;
	std::string m_txt;
	s_Results m_results{};
};


#endif // !GAME_HPP
