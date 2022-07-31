#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "appexception.hpp"
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

	std::string m_filePath{};
	std::vector<std::string> m_textsVec;

	bool parseFile();
	void appAbort(std::string_view) const noexcept;
};



#endif // !APPLICATION_HPP
