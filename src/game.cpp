#include "game.hpp"

Game::Game(UI& _ui, const std::string& _txt)
	: ui(_ui), m_txt(_txt)
{
}


auto Game::play() -> void
{   
    using Just = UI::Justification;

    std::vector<std::string> linesVec;
    std::stringstream ss(m_txt);

    for (std::string orgTxt; std::getline(ss, orgTxt);)
    {
        linesVec.push_back(orgTxt);
    }


    std::vector<char> userInputVec;
    std::vector<s_Results> lineResultsVec;

    for(const auto& orgStr: linesVec)
    {
        userInputVec.clear();

        ui << UI::Colors::White << UI::Setw{Just::Center, orgStr.size()} << orgStr.c_str() << "\n";
       
        ui << UI::Setw{ Just::Center, orgStr.size() };
        
        for (std::size_t i = 0; i < orgStr.length();)
        {
            char ch = _getch();
            if (ch == 8)
            {
                if (userInputVec.size() > 0)
                {
                    if (i > 0) --i;
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
    }


    for (const auto& i : lineResultsVec)
    {
        if (i.ct_correct == 0 && i.ct_incorrect == 0) return;

        m_results.ct_correct += i.ct_correct;
        m_results.ct_incorrect += i.ct_incorrect;
    }

    m_results.rate = static_cast<double> (m_results.ct_correct) 
        / (static_cast<double> (m_results.ct_correct) + static_cast<double> (m_results.ct_incorrect));


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    ui << "\n\nRate: " << m_results.rate * 100.0 << "\nCorrect: " << m_results.ct_correct <<
        "\nIncorrect: " << m_results.ct_incorrect << "\n";
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
            return s_Results{ -1.0, 0, 0 };
        }
        catch (...)
        {
            std::exit(EXIT_FAILURE);
        }
    }

    std::size_t incorrect = orgStr.length() - correct;
    double rt = static_cast<double>(correct / (correct+incorrect));

    return s_Results {rt, correct, incorrect};
}
