#pragma once
#include <ostream>
#pragma warning(push)
#pragma warning(disable: 26812)
namespace Color {
    enum Code {
        FG_BLACK = 30,
        FG_MAGENTA = 35,
        FG_GREEN = 92,
        FG_ORANGE = 33,
        FG_BLUE = 94,
        FG_CYAN = 36,
        FG_WHITE = 37,
        FG_DEFAULT = 39,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_DEFAULT = 49,
        FG_GREY = 90,
        FG_RED = 91,
        FG_YELLOW = 93,
        FG_PINK = 95,
        FG_BRCYAN = 96,
        BG_BRWHITE = 97
    };
    class Modifier
    {
        Code code;
    public:
        Modifier(Code pCode) :
            code(pCode) {}
        friend std::ostream&
            operator<<(std::ostream& os, const Modifier& mod)
        {
            return os << "\033[" << mod.code << "m";
        }
    };
    Color::Modifier magenta(Color::FG_MAGENTA);// " << mag << "
    Color::Modifier red(Color::FG_RED);// " << rou << "
    Color::Modifier def(Color::FG_DEFAULT);// " << def << "
    Color::Modifier yellow(Color::FG_YELLOW);// " << yel << "
    Color::Modifier green(Color::FG_GREEN);// " << gre << "
    Color::Modifier orange(Color::FG_ORANGE);// " << ora << "
    Color::Modifier pink(Color::FG_PINK);// " << pin << "
    Color::Modifier black(Color::FG_BLACK);// " << bla << "
    Color::Modifier gray(Color::FG_GREY);// " << gry << "
    Color::Modifier white(Color::FG_WHITE);// " << whi << "
    Color::Modifier brwhite(Color::BG_BRWHITE);// " << big << "
    Color::Modifier brcyan(Color::FG_BRCYAN);// " << bcc << "
    Color::Modifier cyan(Color::FG_CYAN);// " << cya << "
    Color::Modifier blue(Color::FG_BLUE);// " << blu << "
}
#pragma warning(pop)
/*
Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107
*/