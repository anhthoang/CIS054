#include "claudia_calc_example.h"

#include <sys/types.h>

#include <iostream>

#include "spdlog/spdlog.h"
using namespace std;

namespace claudia_calc {

/*
 * utility functions
 */

//add registers array to hold value
double registers[NUM_REGISTERS] = {0};


inline bool is_register(char const ch) { return tolower(ch) >= 'a' && ch <= 'd'; }

inline bool is_register(string const str) { return str.size() == 1 && is_register(str[0]); }

inline reg_name to_reg_name(char const ch) {
    assert(is_register(ch));
    return static_cast<reg_name>(tolower(ch) - 'a');
}

inline reg_name to_reg_name(string const str) {
    assert(is_register(str));
    return to_reg_name(str[0]);
}

inline char to_char(reg_name rn) { return static_cast<char>(rn + 'a'); }

//validate input 
inline bool validate_command(const string &cmd) {
    if (cmd.size() != 1) {
        return false;  // Must be exactly one character long
    }

    char ch = cmd[0];
    return is_register(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
           ch == 'm' || ch == 'p' || ch == 'q' || (ch >= '1' && ch <= '4');
}

//display the registers

void display_registers(){
    cout << "A = " << registers[A] << endl;
    cout << "B = " << registers[B] << endl;
    cout << "C = " << registers[C] << endl;
    cout << "D = " << registers[D] << endl;
}


/*
 * calculator functions
 */

inline void print_line() { cout << std::string(MENU_WIDTH, '-') << endl; }

inline void print_title(string const title) { cout << fmt::format("{:^{}}", title, MENU_WIDTH) << endl; }

void print_menu() {
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

void execute(string const cmd) {
    // validate command size
    if (cmd.size() == 0) {
        spdlog::error("Empty command");
        return;
    }
    // lower annd get first char of command
    char const cmd_ch = std::tolower(cmd[0]);

    switch (cmd_ch) {
        case 'a':
            double value;
            cout << "Enter value for register A: ";
            cin >> value;
            cin.ignore();
            registers[A] = value;
            spdlog:: info("Store {} in register A", value);
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case 'b':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case 'c':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case 'd':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '+':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '-':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '*':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '/':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '1':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '2':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '3':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '4':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case 'm':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case 'p':
            spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case 'q':
            break;
        default:
            spdlog::error("{} is an unknown command", cmd_ch);
            break;
    }
}

// start the calculator
void start() {
    string cmd = "";
    // print menu
    print_menu();
    while (cmd != "q") {
        cout << "Enter a command: ";
        cin >> cmd;
        spdlog::debug("User input : '{}'", cmd);

        if (!validate_command(cmd)) {
            spdlog::error("Invalid command: '{}'", cmd);
            cout << "Invalid input! Enter only one character command. Type 'm' to see menu.\n";
            continue;
        }

        execute(cmd);
    }
}
}  // namespace claudia_calc

using namespace claudia_calc;

int main() {
    spdlog::set_level(spdlog::level::debug);
    start();

    return 0;
}
