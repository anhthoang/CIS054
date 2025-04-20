#include "claudia_calc_example_oop.h"

#include <sys/types.h>

#include <iomanip>
#include <iostream>

#include "spdlog/spdlog.h"
using namespace std;

namespace claudia_calc
{

    /*
     * calculator functions
     */

    calc::calc()
        : _regs{reg(A, reg_type::NUMBER), reg(B, reg_type::NUMBER), reg(C, reg_type::NUMBER), reg(D, reg_type::NUMBER)} {}

    inline void print_line() { cout << std::string(MENU_WIDTH, '-') << endl; }

    inline void print_title(string const title) { cout << fmt::format("{:^{}}", title, MENU_WIDTH) << endl; }

    /*
     * ui functions
     */

    void ui::print_menu(calc const &c) const
    {
        print_line();
        print_title("ClaudiaCalc");
        print_line();
        cout << "+\tAdd" << endl;
        cout << "-\tSubtract" << endl;
        cout << "*\tMultiply" << endl;
        cout << "/\tDivide" << endl;
        cout << "a-d\tEnter a number or string for A,B,C,D" << endl;
        cout << "1-4\tClear register A,B,C,D" << endl;
        cout << "m\tPrints the menu" << endl;
        cout << "p\tPrints the registers" << endl;
        cout << "q\tQuits the app" << endl;
        print_line();
    }

    //helper function to read input for registers 
    void handle_register_input(calc& c, reg_name name) {
        string input;
        cout << "Enter value for register " << static_cast<char>('A' + static_cast<int>(name)) << ": ";
        cin.ignore();
        getline(cin, input);
    
        stringstream ss(input);
        float num;
        if (ss >> num && ss.eof()) {
            c.set(name, num);
            spdlog::info("Stored number {} in register {}", num, static_cast<char>('A' + static_cast<int>(name)));
        } else {
            c.get(name).set_string(input);
            spdlog::info("Stored string \"{}\" in register {}", input, static_cast<char>('A' + static_cast<int>(name)));
        }
    }

    // execute a command
    // a   Asks the user to enter a number or string for A
    // b   Asks the user to enter a number or string for B
    // c   Asks the user to enter a number or string for C
    // d   Asks the user to enter a number or string for D
    // +   A gets the value of A plus B. In other words, A = A + B
    // -   A gets the value of A minus B. In other words, A = A - B
    // *   A gets the value of A times B. In other words, A = A * B
    // /   A gets the value of A divided by B. In other words, A = A / B
    // c   Clears the values for both A, B, C, D.  A, B, C, D are set to 0
    // 1   Clears the values for A
    // 2   Clears the values for B
    // 3   Clears the values for C
    // 4   Clears the values for D
    // m    Prints the menu
    // p   Prints the values of A, B, C, D
    // q   Quits the app
    void ui::execute(calc &c, string const cmd)
    {
        // validate command size
        if (cmd.size() == 0)
        {
            spdlog::error("Empty command");
            return;
        }
        // lower annd get first char of command
        char const cmd_ch = std::tolower(cmd[0]);

        switch (cmd_ch)
        {
        case 'a':

            handle_register_input(c,A);
            break;
        
        case 'b':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case 'c':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case 'd':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '+':
        {
            float a_val = c.get(A).get_number();
            float b_val = c.get(B).get_number();
            float result = a_val + b_val;
            c.set(A, result);
            spdlog::info("A = A + B -> {} + {} = {}", a_val, b_val, result);
            // spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '-':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '*':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '/':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '1':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '2':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '3':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '4':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case 'm':
        {
            print_menu(c);
            break;
        }
        case 'p':
        {
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case 'q':
        {
            break;
        }
        default:
        {
            spdlog::error("{} is an unknown command", cmd_ch);
            break;
        }
        }
    }

    // start the calculator
    void ui::start(calc &c)
    {
        string cmd = "";
        // print menu
        print_menu(c);
        while (cmd != "q")
        {
            cout << "Enter a command: ";
            cin >> cmd;
            spdlog::debug("cmd={}", cmd);
            execute(c, cmd);
        }
    }
} // namespace claudia_calc

using namespace claudia_calc;

int main()
{
    spdlog::set_level(spdlog::level::info);

    // create calculator, ui, and start
    calc calculator;
    ui user_interface;
    user_interface.start(calculator);

    return 0;
}
