#ifndef GAME_HPP
#define GAME_HPP

#include <string>


#ifdef _WIN32
#include <Windows.h>


#else
#include <otherlinuxfiles>

#endif // WIN32


class Game
{
public:

	explicit Game(const std::string&);



	struct s_Results
	{
		double rate;
		long ct_correct;
		long ct_incorrect;
		long ct_all;
	};

private:
	std::string txt;
};


#endif // !GAME_HPP
