#include "claudia_calc_example.h"

#include <sys/types.h>

#include <iostream>

#include "spdlog/spdlog.h"

#include <iomanip>
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

inline void print_line() { cout << std::string(MENU_WIDTH, '-') << endl; }

inline void print_title(string const title) { cout << fmt::format("{:^{}}", title, MENU_WIDTH) << endl; }

//validate input command 
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
    cout << fixed << setprecision(3);
    cout << "Current register values" << endl;
    cout << "A = " << registers[A] << endl;
    cout << "B = " << registers[B] << endl;
    cout << "C = " << registers[C] << endl;
    cout << "D = " << registers[D] << endl;
    print_line();
}

//validate_input_value
double validate_input_value(){
    string input;
    float value;
    bool valid;

    do{
        getline(cin, input);
        stringstream parseString(input);
        valid = (parseString >> value && parseString.eof());

        if(!valid){
            cout << "Invalid input. Please enter a number:";
        }
    }while(!valid);

    return value;
    
}


/*
 * calculator functions
 */



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
    // if (cmd.size() == 0) {
    //     spdlog::error("Empty command");
    //     return;
    // }
    // lower annd get first char of command
    char const cmd_ch = std::tolower(cmd[0]);
    //double input_value = 0.0;

    switch (cmd_ch) {
        case 'a':
            float value_a;
            cout << "Enter value for register A: ";
            value_a = validate_input_value();
            registers[A] = value_a;
            // spdlog:: info("Store {} in register A", value_a);
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case 'b':
            float value_b;
            cout << "Enter value for register B: ";
            value_b = validate_input_value();
            registers[B] = value_b;
            //spdlog:: info("Store {} in register B", value_b);
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case 'c':
            float value_c;
            cout << "Enter value for register C: ";
            value_c = validate_input_value();
           
            registers[C] = value_c;
            //spdlog:: info("Store {} in register C", value_c);
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case 'd':
            float value_d;
            cout << "Enter value for register D: ";
            value_d = validate_input_value();
            registers[D] = value_d;
            //spdlog:: info("Store {} in register D", value_d);
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '+': {
            char lhs_reg, rhs_reg;
            cout << "Enter a lhs register (a-d): ";
            cin >> lhs_reg;
            cout << "Enter a rhs register (a-d): ";
            cin >> rhs_reg;
            cin.ignore();

            if (!is_register(lhs_reg) || !is_register(rhs_reg)) {
                cout << "Invalid register(s). Operation cancelled.\n";
                break;
            }

            registers[to_reg_name(lhs_reg)] += registers[to_reg_name(rhs_reg)];
            display_registers();
            break;
        }
        case '-': {
            char lhs_reg, rhs_reg;
            cout << "Enter a lhs register (a-d): ";
            cin >> lhs_reg;
            cout << "Enter a rhs register (a-d): ";
            cin >> rhs_reg;
            cin.ignore();

            if (!is_register(lhs_reg) || !is_register(rhs_reg)) {
                cout << "Invalid register(s). Operation cancelled.\n";
                break;
            }

            registers[to_reg_name(lhs_reg)] -= registers[to_reg_name(rhs_reg)];
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '*': {
            char lhs_reg, rhs_reg;
            cout << "Enter a lhs register (a-d): ";
            cin >> lhs_reg;
            cout << "Enter a rhs register (a-d): ";
            cin >> rhs_reg;
            cin.ignore();

            if (!is_register(lhs_reg) || !is_register(rhs_reg)) {
                cout << "Invalid register(s). Operation cancelled.\n";
                break;
            }

            registers[to_reg_name(lhs_reg)] *= registers[to_reg_name(rhs_reg)];
            //spdlog::info("Added {} to {}. New value: {}", rhs_reg, lhs_reg, registers[to_reg_name(lhs_reg)]);
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '/': {
            char lhs_reg, rhs_reg;
            double rhs_value;
            cout << "Enter a lhs register (a-d): ";
            cin >> lhs_reg;
            cout << "Enter a rhs register (a-d): ";
            cin >> rhs_reg;
            cin.ignore();

            if (!is_register(lhs_reg) || !is_register(rhs_reg)) {
                cout << "Invalid register(s). Operation cancelled.\n";
                break;
            }

            rhs_value = registers[to_reg_name(rhs_reg)];
            if (rhs_value == 0) {
                cout << "Error: Division by zero.\n";
                break;
            }

            registers[to_reg_name(lhs_reg)] /= rhs_value;
            //spdlog::info("Divided {} by {}. New value: {}", lhs_reg, rhs_reg, registers[to_reg_name(lhs_reg)]);
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        }
        case '1':
            registers[A] = 0;
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '2':
            registers[B] = 0;
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '3':
            registers[C] = 0;
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case '4':
            registers[D] = 0;
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
            break;
        case 'm':
            //spdlog::error("cmd={} not implemented", cmd_ch);
            print_menu();
            break;
        case 'p':
            display_registers();
            //spdlog::error("cmd={} not implemented", cmd_ch);
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
        //spdlog::debug("User input : '{}'", cmd);

        if (!validate_command(cmd)) {
            spdlog::error("Invalid command: '{}'", cmd);
            cout << "Invalid input! Enter only one character command. Type 'm' to see menu.\n";
            continue;
        }

        cin.ignore();
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
