#ifndef UI_HPP
#define UI_HPP

#include "../options.hpp"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <conio.h>  // :/

class UI
{
public:
    explicit UI(std::ostream&);

    enum class Justification { Right, Center, Left };
    enum class Colors { Blue = 1, Green, Lightblue, Red, Purple, Yellow, White, Grey};

    auto OptionsUI(const Options&) -> Options;
    auto cls() const noexcept -> void;
    auto print_logo() noexcept -> void;

    auto operator<< (Colors) -> UI&;        //text color

    struct Setw { UI::Justification just; std::size_t size; };
    auto operator<< (const Setw&) -> UI&;   //text justification

    template <typename T>
    UI& operator<< (const T& x)
    {
        os << x;
        return *this;
    }

private:
    std::ostream& os;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
};

#endif // !UI_HPP
