#include "application.hpp"
#include <iostream>
Application::Application(int argc, char** argv)
	: argc(argc), argv(argv), m_ui(std::cout)
{
}

auto Application::exec() -> int
{
	Game x(m_ui, "AAA\n\
BBb");

	x.play();


	return 0;
}

//auto Application::parseFile() -> bool
//{
//	//probably gonna change
//
//	/*if (argc > 2) throw appexception("Too many application arguments");
//
//	m_filePath = argv[1];
//
//	std::ifstream file;
//	file.open(m_filePath);
//
//	if (!file) throw appexception("File can't be opened");
//
//	std::string text;
//
//	for (std::string line; std::getline(file, line);)
//	{
//		if (!line.empty()) text += line;
//		else
//		{
//			m_textsVec.push_back(text);
//			text.erase();
//		}
//	}
//
//	if(!text.empty()) m_textsVec.push_back(text);
//
//	file.close*/
//
//	return true;
//}

auto Application::appAbort(const std::string_view& _str) const noexcept -> void
{
	std::exit(EXIT_FAILURE);
}
