#include "../ui.hpp"

UI::UI(std::ostream& _os) : os(_os)
{
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

auto UI::getchar() noexcept -> int
{
    return _getch();
}

auto UI::setStatusBar(std::uint16_t x, std::uint16_t max) -> void
{
    double progress = static_cast<double>(x) / static_cast<double>(max);

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);
    COORD pos = {csbi.srWindow.Left, csbi.srWindow.Bottom};
    COORD current = csbi.dwCursorPosition;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    int len = progress * static_cast<double>(csbi.srWindow.Right);
    *this << UI::Colors::Yellow;
    for(int i=0; i<len; i++) *this << (char)219;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
}


auto UI::operator<<(Colors col) -> UI&
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(col));
    return *this;
}

auto UI::operator<< (const Setw& setw) -> UI&
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
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