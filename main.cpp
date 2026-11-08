#include "Base.h"
#include "Submarine.h"
#include "Sailboat.h"
#include "Motorboat.h"
#include "Input.h"
#include <iostream>
#include <memory>
#ifdef _WIN32
#include <windows.h>
#endif
int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8);
#endif
    while(true) {
        try {
            int type=io::integer(std::cin,
                "1. Подлодка  2. Парусник  3. Катер  0. Выход: ",0,3);
            if(!type) break;
            std::unique_ptr<Base> ship;
            if(type==1) ship=std::make_unique<Submarine>();
            if(type==2) ship=std::make_unique<Sailboat>();
            if(type==3) ship=std::make_unique<Motorboat>();
            ship->read(std::cin,true);
            std::cout << *ship;
            std::unique_ptr<Base> copy(ship->clone());
            std::cout << "Копия объекта:\n" << *copy;
        } catch(const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << '\n';
            if(std::cin.eof() || std::cin.bad()) break;
        }
    }
}
