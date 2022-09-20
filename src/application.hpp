#ifndef APPLICATION_HPP
#define APPLICATION_HPP


#include "game.hpp"
#include "appexception.hpp"
#include "data.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <string_view>

class Application
{
public:
	explicit Application(int, char**);

	int exec();


private:
	int argc;
	char** argv;

    UI m_ui;
	Options m_options {};
	std::string m_filePath{};
	std::vector<std::string> m_textsVec;

	//bool parseFile();
	void appAbort(const std::string_view&) const noexcept;
};



#endif // !APPLICATION_HPP
