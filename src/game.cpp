#include "game.hpp"

Game::Game(UI& _ui, const std::string& _txt)
	: ui(_ui), m_txt(_txt)
{
}


auto Game::play() -> void
{
    std::stringstream ss(m_txt);

    std::vector<s_Results> lineResultsVec;
    std::vector<char> userInput;
        
    for(std::string orgTxt, userInput; std::getline(ss, orgTxt);)
    {
        userInput.erase();
        //debug purposes begin
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        ui << orgTxt.c_str() << "\n";
       
        //debug purposes end
        for (size_t i = 0; i < orgTxt.length();)
        {
            char x = _getch();
            if (x == 8)
            {
                if (userInput.length() > 0)
                {
                    --i;
                    if (i > 0) --i;
                    std::cout << "\b \b";
                    userInput.pop_back();
                }
            }

            else
            {
                if (x == orgTxt[i])
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                    userInput.push_back(x);
                }

                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                    userInput.push_back(x);
                }
                std::cout << x;

                i++;
            }
            
        }

        std::cout << "\n";

        lineResultsVec.push_back(check_line(orgTxt, userInput));
    }


    for (const auto& i : lineResultsVec)
    {
        if (i.ct_correct == 0 && i.ct_incorrect == 0) return;

        m_results.ct_correct += i.ct_correct;
        m_results.ct_incorrect += i.ct_incorrect;
    }

    m_results.rate = static_cast<double> (m_results.ct_correct) 
        / (static_cast<double> (m_results.ct_correct) + static_cast<double> (m_results.ct_incorrect));

    std::cout << "\n\nRate: " << m_results.rate*100.0 << "\nCorrect: " << m_results.ct_correct <<
        "\nIncorrect: " << m_results.ct_incorrect << std::endl;

    system("pause");
}


auto Game::check_line(const std::string_view& orgStr, const std::string_view& userStr) -> s_Results
{
    std::size_t len = (orgStr.length() < userStr.length()) ? orgStr.length() : userStr.length();

    long correct = 0;

    for (size_t i = 0; i < len; i++)
    {
        try
        {
            if (orgStr.at(i) == userStr.at(i)) ++correct;
        }
        catch (const std::out_of_range&)
        {
            return s_Results{ -1.0,-1,-1 };
        }
        catch (...)
        {
            std::exit(EXIT_FAILURE);
        }
    }

    long incorrect = orgStr.length() - correct;
    double rt = static_cast<double>(correct / (correct+incorrect));

    return s_Results{ rt, correct, incorrect};
}
