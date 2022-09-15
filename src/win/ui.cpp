#include "ui.hpp"

UI::UI(std::ostream& _os) : os(_os)
{
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
}


auto UI::OptionsUI(const Options& _opt) -> Options
{
    return Options();
}

auto UI::cls() const noexcept -> void
{
    system("cls");
}

auto UI::print_logo() noexcept -> void
{
   *this << UI::Setw {Justification::Center, 97} <<
"   __                 _     _                                  _                                \n"
<< UI::Setw{ Justification::Center, 97 } <<
"  / _|               | |   | |                                | |                                \n"
<< UI::Setw{ Justification::Center, 97 } <<
" | |_    __ _   ___  | |_  | |__     ___     __ _   _ __    __| |  ______    ___   _ __    _ __  \n"
<< UI::Setw{ Justification::Center, 97 } <<
" |  _|  / _` | / __| | __| | '_ \\   / _ \\   / _` | | '__|  / _` | |______|  / __| | '_ \\  | '_ \\ \n"
<< UI::Setw{ Justification::Center, 97 } <<
" | |   | (_| | \\__ \\ | |_  | |_) | | (_) | | (_| | | |    | (_| |          | (__  | |_) | | |_) | \n"
<< UI::Setw{ Justification::Center, 97 } <<
" |_|    \\__,_| |___/  \\__| |_.__/   \\___/   \\__,_| |_|     \\__,_|           \\___| | .__/  | .__/ \n"
<< UI::Setw{ Justification::Center, 97 } <<
"                                                                                  | |     | |    \n"
<< UI::Setw{ Justification::Center, 97 } <<
"                                                                                  |_|     |_|    \n";
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

    return *this;
}