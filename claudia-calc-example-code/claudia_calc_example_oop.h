#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>

using namespace std;

#define NUM_REGISTERS 4
#define MENU_WIDTH 140

namespace claudia_calc
{

    enum reg_type
    {
        NUMBER = 0,
        STRING
    };

    enum reg_name
    {
        A = 0,
        B,
        C,
        D
    };
    enum operation : char
    {
        PLUS = '+',
        MINUS = '-',
        MULTIPLY = '*',
        DIVIDE = '/'
    };

    class reg
    {
    private:
        reg_name _name;
        reg_type _type;
        float _num;
        string _str;

    public:
        reg(reg_name name, reg_type type) : _name(name), _type(type), _num(0.0F), _str() {}
        // no destructor, using rule of zero
        float get_number() const { return _num; }
        void set_number(float val) { _num = val; }
        void clear()
        {
            _num = 0.0F;
            _str.clear();
        }
        reg_name name() const { return _name; }
        reg_type type() const { return _type; }
    };

    class calc {
        private:
         array<reg, NUM_REGISTERS> _regs;
     
        public:
         calc();
     
         reg& get(reg_name name) { return _regs[static_cast<int>(name)]; }
         const reg& get(reg_name name) const { return _regs[static_cast<int>(name)]; }
     
         void set(reg_name name, float value) { _regs[static_cast<int>(name)].set_number(value); }
         void clear(reg_name name) { _regs[static_cast<int>(name)].clear(); }
     
         void clear_all() {
             for (auto& r : _regs) {
                 r.clear();
             }
         }
     
         void perform(operation op);  // optional if you want centralized math logic
     };

     class ui {
        
        public:
            void print_menu(const calc& c) const;
            void execute(calc& c, const string cmd);
            void start(calc& c);
        };

     

} // namespace claudia_calc