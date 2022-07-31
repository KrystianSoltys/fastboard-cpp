#include "application.hpp"
#include <iostream>
Application::Application(int argc, char** argv)
	: argc(argc), argv(argv)
{
}

int Application::exec()
{
	try
	{
		parseFile();
	}
	catch (const appexception& exc)
	{
		std::cerr << exc.what();
	}
	catch (...)
	{
		return EXIT_FAILURE;
	}
	



	return 0;
}

bool Application::parseFile()
{
	if (argc > 2) throw appexception("Too many application arguments");

	m_filePath = argv[1];

	std::ifstream file;
	file.open(m_filePath);

	if (!file) throw appexception("File can't be opened");

	std::string text;

	for (std::string line; std::getline(file, line);)
	{
		if (!line.empty()) text += line;
		else
		{
			m_textsVec.push_back(text);
			text.erase();
		}
	}

	if(!text.empty()) m_textsVec.push_back(text);

	file.close();

	return true;
}

void Application::appAbort(std::string_view) const noexcept
{
}
