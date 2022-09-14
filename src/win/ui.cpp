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


auto UI::operator<<(Colors col) -> UI&
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(col));
    return *this;
}

auto UI::operator<< (const Setw& setw) -> UI&
{
    auto cols = static_cast<int>(consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1);

    switch (setw.just)
    {
    case UI::Justification::Right:
        os << std::setw((cols + 1) - setw.size);
        break;
    case UI::Justification::Center:
        os << std::setw((cols / 2) - (setw.size / 2)) << " \b";
        break;

    default:
        break;
    }
}