#include "Keeper.h"
#include "Submarine.h"
#include "Sailboat.h"
#include "Motorboat.h"
#include "Input.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif
int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8);
#endif
    Keeper keeper;
    while(true) {
        std::cout << "\nКорабли. Вариант 7\n"
          "1. Добавить корабль\n2. Показать все\n3. Показать один\n"
          "4. Изменить поле\n5. Удалить\n6. Копировать корабль\n"
          "7. Сохранить в файл\n8. Загрузить из файла\n"
          "9. Копировать контейнер\n10. Очистить контейнер\n0. Выход\n";
        try {
            int action=io::integer(std::cin,"Действие (0-10): ",0,10);
            if(action==0) break;
            switch(action) {
            case 1: {
                int type=io::integer(std::cin,"Тип: 1 - подлодка, 2 - парусник, 3 - катер: ",1,3);
                std::unique_ptr<Base> ship;
                if(type==1) ship=std::make_unique<Submarine>();
                if(type==2) ship=std::make_unique<Sailboat>();
                if(type==3) ship=std::make_unique<Motorboat>();
                ship->read(std::cin,true); keeper+=*ship;
                std::cout << "Корабль добавлен.\n"; break;
            }
            case 2: std::cout << keeper; break;
            case 3: case 4: case 5: case 6: {
                if(!keeper.size()) throw std::runtime_error("Контейнер пуст.");
                int id=io::integer(std::cin,"Номер корабля: ",1,keeper.size())-1;
                if(action==3) std::cout << keeper[id];
                if(action==4) { keeper[id].edit(std::cin); std::cout << "Поле изменено.\n"; }
                if(action==5) { keeper-=id; std::cout << "Корабль удалён.\n"; }
                if(action==6) { keeper+=keeper[id]; std::cout << "Копия добавлена.\n"; }
                break;
            }
            case 7: case 8: {
                auto path=io::text(std::cin,"Путь к файлу: ");
                if(action==7) keeper.save(path.get()); else keeper.load(path.get());
                std::cout << (action==7?"Данные сохранены.\n":"Данные загружены.\n"); break;
            }
            case 9: {
                Keeper copy(keeper); Keeper assigned; assigned=copy;
                std::cout << "Глубокая копия контейнера:\n" << assigned; break;
            }
            case 10: keeper.clear(); std::cout << "Контейнер очищен.\n"; break;
            }
        } catch(const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << '\n';
            if(std::cin.eof() || std::cin.bad()) break;
        }
    }
}
