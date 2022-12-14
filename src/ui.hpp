#ifndef UI_HPP
#define UI_HPP

#include "options.hpp"
#include <iostream>
#include <iomanip>

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>

#elif UNIX
#include <>

#endif // _WIN32 / UNIX



class UI
{
public:
    explicit UI(std::ostream&);

    enum class Justification { Right, Center, Left };
    enum class Colors { Blue = 1, Green, Lightblue, Red, Purple, Yellow, White, Grey};

    auto OptionsUI(const Options&) -> Options;
    auto cls() const noexcept -> void;
    auto print_logo() noexcept -> void;
    auto getchar() noexcept -> int;
    auto setStatusBar(std::uint16_t x, std::uint16_t max) -> void;

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
};

#endif // !UI_HPP
