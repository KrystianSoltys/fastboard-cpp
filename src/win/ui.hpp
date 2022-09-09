#ifndef UI_HPP
#define UI_HPP

#include "../options.hpp"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <conio.h>

class UI
{
public:
    UI(std::ostream&);

    enum class AppModulesEnum { sw_PlayGame, sw_Options, sw_Statistics, sw_Exit };
    enum class Justification { Right, Center, Left };

    auto Print(const std::string_view&, Justification = Justification::Left) const  -> void;
    auto MainMenuUI() -> AppModulesEnum;
    auto OptionsUI(const Options&) -> Options;

    UI& operator<<(const std::string_view&);

private:
    std::ostream& os;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
};

#endif // !UI_HPP
