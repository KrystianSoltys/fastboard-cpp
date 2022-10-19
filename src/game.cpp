#include "game.hpp"

Game::Game(UI& _ui)
	: ui(_ui)
{
}


auto Game::play(const std::string& str) -> void
{   
    m_txt = str;

    using Just = UI::Justification;

    std::vector<std::string> linesVec;
    std::stringstream ss(m_txt);

    for (std::string orgTxt; std::getline(ss, orgTxt);)
    {
        linesVec.push_back(orgTxt);
    }


    std::vector<char> userInputVec;
    std::vector<s_Results> lineResultsVec;
    std::size_t ct_bcksp;

    for(const auto& orgStr: linesVec)
    {
        ct_bcksp = 0;
        userInputVec.clear();

        ui << UI::Colors::White << UI::Setw{Just::Center, orgStr.size()} << orgStr.c_str() << "\n";
       
        ui << UI::Setw{ Just::Center, orgStr.size() };
        
        for (std::size_t i = 0; i < orgStr.length();)
        {
            char ch = ui.getchar();
            if (ch == 3) return; //ctrl + c 
            if (ch == 13) continue; //enter
            if (ch == 8)
            {
                if (userInputVec.size() > 0)
                {
                    if (i > 0)
                    {
                        --i;
                        ++ct_bcksp;
                    }
                    ui << "\b \b";
                    userInputVec.pop_back();
                }
            }

            else
            {
                if (ch == orgStr[i])
                {
                    ui << UI::Colors::Green;
                    userInputVec.push_back(ch);
                }

                else
                {
                    ui << UI::Colors::Red;
                    userInputVec.push_back(ch);
                }
                ui << ch;

                i++;
            }
            
        }

        ui << "\n";

        lineResultsVec.push_back(
            check_line(orgStr, std::string(userInputVec.begin(), userInputVec.end())));
        (*lineResultsVec.rbegin()).ct_backspaces = ct_bcksp;
    }


    for (const auto& i : lineResultsVec)
    {
        if (i.ct_correct == 0 && i.ct_incorrect == 0) return;

        m_results.ct_correct += i.ct_correct;
        m_results.ct_incorrect += i.ct_incorrect;
        m_results.ct_backspaces += i.ct_backspaces;
    }

    m_results.rate = static_cast<double> (m_results.ct_correct) 
        / (static_cast<double> (m_results.ct_correct) + static_cast<double> (m_results.ct_incorrect));

    ui << "\n\n";
    ui << UI::Setw{ Just::Center, 13 }
       << UI::Colors::Lightblue << "Rate: " << std::setprecision(4) << m_results.rate * 100.0 << "%\n"
       << UI::Setw {Just::Center, 13 }
       << UI::Colors::Green << "Correct: " << m_results.ct_correct << "\n"
       << UI::Setw{ Just::Center, 13 }
       << UI::Colors::Red << "Incorrect: " << m_results.ct_incorrect << "\n"
       << UI::Setw{ Just::Center, 13 }
       << UI::Colors::Purple << "Backspaces: " << m_results.ct_backspaces << "\n";

       _getch();
}


auto Game::main_menu() -> ModulesEnum
{
    using Just = UI::Justification;


    while (true)
    {
        ui.cls();
        ui << UI::Colors::White;
        ui.print_logo();
        ui << "\n\n";
        ui << UI::Colors::White;
        ui << UI::Setw{ Just::Center, std::string_view("(1) Play").length() } << "(1) Play\n\n";
        ui << UI::Colors::Grey; //not usable yet
        ui << UI::Setw{ Just::Center, std::string_view("(2) Options").length() } << "(2) Options\n\n";
        ui << UI::Colors::Grey; //not usable yet
        ui << UI::Setw{ Just::Center, std::string_view("(3) Statistics").length() } << "(3) Statistics\n\n";
        ui << UI::Colors::White;
        ui << UI::Setw{ Just::Center, std::string_view("(4) Exit").length() } << "(4) Exit\n\n";

        int x = _getch();
        ui.cls();
        if (x >= 49 && x <= 52) return static_cast<ModulesEnum> (x - 48);
    }

    

    
}




auto Game::check_line(const std::string_view& orgStr, const std::string_view& userStr) -> s_Results
{
    std::size_t len = (orgStr.length() < userStr.length()) ? orgStr.length() : userStr.length();

    std::size_t correct = 0;

    for (std::size_t i = 0; i < len; i++)
    {
        try
        {
            if (orgStr.at(i) == userStr.at(i)) ++correct;
        }
        catch (const std::out_of_range&)
        {
            return s_Results{ -1.0, 0, 0, 0};
        }
        catch (...)
        {
            std::exit(EXIT_FAILURE);
        }
    }

    std::size_t incorrect = orgStr.length() - correct;
    double rt = static_cast<double>(correct / (correct+incorrect));

    return s_Results {rt, correct, incorrect, 0};
}
