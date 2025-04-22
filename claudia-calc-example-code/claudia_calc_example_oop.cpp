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
        c.display_registers();
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

    //helper function to display registers
    void calc::display_registers() const
    {
        for (int i = 0; i < NUM_REGISTERS; ++i)
        {
            const reg &r = _regs[i];
            char label = 'A' + i;

            cout << label << "  ";

            if (r.type() == NUMBER)
            {
                cout << "number = " << fixed << setprecision(3) << r.get_number();
            }
            else if (r.type() == STRING)
            {
                cout << "string = " << r.get_string() << "";
            }

            if (i != NUM_REGISTERS - 1)
                cout << "     ";
        }

        cout << endl;
    }

    // helper function to read input for registers
    void handle_register_input(calc &c, reg_name name)
    {
        string input;
        cout << "Enter value for register " << static_cast<char>('A' + static_cast<int>(name)) << ": ";
        cin.ignore();
        getline(cin, input);

        stringstream ss(input);
        float num;
        if (ss >> num && ss.eof())
        {
            c.set(name, num);
            c.display_registers();
        }
        else
        {
            c.get(name).set_string(input);
            c.display_registers();
        }
    }

    // Helper function to handle operation for numbers
    void handle_number_operation(reg &regA, reg &regB, operation op)
    {
        float lhs = regA.get_number();
        float rhs = regB.get_number();

        switch (op)
        {
        case PLUS:
            lhs = lhs + rhs;
            break;
        case MINUS:
            lhs = lhs - rhs;
            break;
        case MULTIPLY:
            lhs = lhs * rhs;
            break;
        case DIVIDE:
            if (rhs == 0.0F)
            {
                spdlog::info("Division by zero is invalid");
                return;
            }
            lhs = lhs / rhs;
            break;
        default:
            spdlog::info("Unknown number operation");
            return;
        }

        regA.set_number(lhs);
    }

    // Helper function to handle operations with strings
    void handle_string_operation(reg &regA, reg &regB, operation op)
    {
        reg_type typeA = regA.type();
        reg_type typeB = regB.type();

        string lhs = regA.get_string();
        string rhs = regB.get_string();
        string result;

        // Case 1: both strings
        if (typeA == STRING && typeB == STRING)
        {
            switch (op)
            {
            case PLUS:
                result = lhs + rhs;
                break;
            case MINUS:
            {
                size_t pos = lhs.find(rhs);
                result = lhs;
                if (pos != string::npos)
                {
                    result.erase(pos, rhs.length());
                }
                break;
            }
            case MULTIPLY:
            {
                for (char chL : lhs)
                {
                    for (char chR : rhs)
                    {
                        result += chL;
                        result += chR;
                    }
                }
                break;
            }
            default:
                spdlog::info("Unsupported operation for strings.");
                return;
            }
        }

        // Case 2: one string, one number → only allow MULTIPLY
        else if (op == MULTIPLY &&
                 ((typeA == STRING && typeB == NUMBER) ||
                  (typeA == NUMBER && typeB == STRING)))
        {
            string str_part;
            float repeat_float = 0;

            if (typeA == NUMBER && typeB == STRING)
            {
                str_part = rhs;
                repeat_float = regA.get_number();
            }
            else
            {
                str_part = lhs;
                repeat_float = regB.get_number();
            }

            int repeat_count = static_cast<int>(floor(repeat_float));
            for (int i = 0; i < repeat_count; ++i)
            {
                result += str_part;
            }
        }

        // Case 3: invalid mixed type for +, -, or unsupported op
        else
        {
            spdlog::info("Invalid operation for mixed types");
            return;
        }

        regA.set_string(result);
    }

    /*
     Function to handle operations, covers two cases:
     - registers are numbers
     - one of registers is string
    */

    void handle_operation(calc &c, operation op, reg_name lhs, reg_name rhs)
    {
        reg &regLHS = c.get(lhs);
        reg &regRHS = c.get(rhs);

        if (regLHS.type() == NUMBER && regRHS.type() == NUMBER)
        {
            handle_number_operation(regLHS, regRHS, op);
        }
        else
        {
            handle_string_operation(regLHS, regRHS, op);
        }

        c.display_registers();
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
        // lower and get first char of command
        char const cmd_ch = std::tolower(cmd[0]);

        switch (cmd_ch)
        {
        case 'a':

            handle_register_input(c, A);
            break;

        case 'b':

            handle_register_input(c, B);
            break;

        case 'c':

            handle_register_input(c, C);
            break;

        case 'd':

            handle_register_input(c, D);
            break;

        case '+':
        {
            char lhs_ch, rhs_ch;
            cout << "Enter LHS register (A–D): ";
            cin >> lhs_ch;
            cout << "Enter RHS register (A–D): ";
            cin >> rhs_ch;

            reg_name lhs = static_cast<reg_name>(tolower(lhs_ch) - 'a');
            reg_name rhs = static_cast<reg_name>(tolower(rhs_ch) - 'a');

            handle_operation(c, PLUS, lhs, rhs);
            break;
        }
        case '-':
        {
            char lhs_ch, rhs_ch;
            cout << "Enter LHS register (A–D): ";
            cin >> lhs_ch;
            cout << "Enter RHS register (A–D): ";
            cin >> rhs_ch;

            reg_name lhs = static_cast<reg_name>(tolower(lhs_ch) - 'a');
            reg_name rhs = static_cast<reg_name>(tolower(rhs_ch) - 'a');

            handle_operation(c, MINUS, lhs, rhs);
            break;
        }
        case '*':
        {
            char lhs_ch, rhs_ch;
            cout << "Enter LHS register (A–D): ";
            cin >> lhs_ch;
            cout << "Enter RHS register (A–D): ";
            cin >> rhs_ch;

            reg_name lhs = static_cast<reg_name>(tolower(lhs_ch) - 'a');
            reg_name rhs = static_cast<reg_name>(tolower(rhs_ch) - 'a');

            handle_operation(c, MULTIPLY, lhs, rhs);
            break;
        }
        case '/':
        {
            char lhs_ch, rhs_ch;
            cout << "Enter LHS register (A-D): ";
            cin >> lhs_ch;
            cout << "Enter RHS register (A-D): ";
            cin >> rhs_ch;

            reg_name lhs = static_cast<reg_name>(tolower(lhs_ch) - 'a');
            reg_name rhs = static_cast<reg_name>(tolower(rhs_ch) - 'a');

            handle_operation(c, DIVIDE, lhs, rhs);
            break;
        }
        case '1':
        {
            c.clear(A);
            c.display_registers();
            break;
        }
        case '2':
        {
            c.clear(B);
            c.display_registers();
            break;
        }
        case '3':
        {
            c.clear(C);
            c.display_registers();
            break;
        }
        case '4':
        {
            c.clear(D);
            c.display_registers();
            break;
        }
        case 'm':
        {
            print_menu(c);
            break;
        }
        case 'p':
        {
            c.display_registers();
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
