#include "ui.hpp"

UI::UI(std::ostream& _os) : os(_os)
{
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
}

auto UI::MainMenuUI() -> AppModulesEnum
{

	return AppModulesEnum::sw_PlayGame;
}


auto UI::OptionsUI(const Options& _opt) -> Options
{
    return Options();
}

UI& UI::operator<<(const std::string_view& str)
{
    UI::Print(str);
    return *this; 
}

auto UI::Print(const std::string_view& str, UI::Justification just) const -> void
{
    /*HWND consoleInfo = GetConsoleWindow();
    consoleInfo.srWindow.Right = 5000;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    switch (just)
    {
        case Justification::Left:
        {
            os << str << std::endl;
            break;
        }
        case Justification::Center:
        {
            os << std::setw(consoleInfo.srWindow.Right/2 - (str.size() / 2)) << str << std::endl;
            break;
        }
        case Justification::Right:
        {
            os << std::right << str << std::endl << std::left;
            break;
        }
        default:
        {
            os << str << std::endl;
            break;
        }
    }*/
    std::cout << str;
}

