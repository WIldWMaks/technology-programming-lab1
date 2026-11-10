#include "Keeper.h"
#include "Submarine.h"
#include "Sailboat.h"
#include "Motorboat.h"
#include "Input.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <climits>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <utility>
Keeper::Keeper() : items_(nullptr),count_(0),capacity_(0) {
    std::cout << "[Keeper] Конструктор без параметров: " << this << '\n';
}
Keeper::Keeper(const Base& first) : items_(nullptr),count_(0),capacity_(0) {
    add(first);
    std::cout << "[Keeper] Конструктор с параметром: " << this << '\n';
}
Keeper::Keeper(const Keeper& other) : items_(nullptr),count_(0),capacity_(0) {
    try { for(int i=0;i<other.count_;++i) add(*other.items_[i]); }
    catch(...) { clear(); delete[] items_; throw; }
    std::cout << "[Keeper] Конструктор копирования: " << &other << " -> " << this << '\n';
}
Keeper::~Keeper() {
    clear(); delete[] items_;
    std::cout << "[Keeper] Деструктор: " << this << '\n';
}
void Keeper::reserve(int capacity) {
    if(capacity<=capacity_) return;
    std::unique_ptr<Base*[]> next(new Base*[capacity]);
    for(int i=0;i<count_;++i) next[i]=items_[i];
    delete[] items_; items_=next.release(); capacity_=capacity;
}
void Keeper::swap(Keeper& other) noexcept {
    std::swap(items_,other.items_); std::swap(count_,other.count_);
    std::swap(capacity_,other.capacity_);
}
Keeper& Keeper::operator=(const Keeper& other) {
    if(this!=&other) { Keeper temp(other); swap(temp); }
    return *this;
}
int Keeper::size() const { return count_; }
Base& Keeper::operator[](int i) {
    if(i<0 || i>=count_) throw std::out_of_range("Корабля с таким номером нет.");
    return *items_[i];
}
const Base& Keeper::operator[](int i) const {
    if(i<0 || i>=count_) throw std::out_of_range("Корабля с таким номером нет.");
    return *items_[i];
}
void Keeper::add(const Base& item) {
    std::unique_ptr<Base> copy(item.clone());
    if(count_==capacity_) {
        if(capacity_>INT_MAX/2) throw std::length_error("Контейнер слишком велик.");
        reserve(capacity_?capacity_*2:4);
    }
    items_[count_++]=copy.release();
}
void Keeper::remove(int i) {
    if(i<0 || i>=count_) throw std::out_of_range("Корабля с таким номером нет.");
    delete items_[i];
    for(int j=i;j+1<count_;++j) items_[j]=items_[j+1];
    --count_;
}
void Keeper::clear() noexcept {
    for(int i=0;i<count_;++i) delete items_[i];
    count_=0;
}
Keeper& Keeper::operator+=(const Base& item) { add(item); return *this; }
Keeper& Keeper::operator-=(int index) { remove(index); return *this; }
std::ostream& operator<<(std::ostream& out,const Keeper& keeper) {
    out << "Кораблей: " << keeper.size() << '\n';
    for(int i=0;i<keeper.size();++i) out << "\nНомер " << i+1 << ":\n" << keeper[i];
    return out;
}
void Keeper::save(const char* path) const {
    io::checkText(path);
    std::ofstream out(std::filesystem::u8path(path));
    if(!out) throw std::runtime_error("Не удалось открыть файл для записи.");
    out << "SHIP_KEEPER_V1\n" << count_ << '\n' << std::setprecision(17);
    for(int i=0;i<count_;++i) { out << items_[i]->type() << '\n'; items_[i]->write(out); }
    out.flush();
    if(!out) throw std::runtime_error("Ошибка записи файла.");
}
void Keeper::load(const char* path) {
    io::checkText(path);
    std::ifstream in(std::filesystem::u8path(path));
    if(!in) throw std::runtime_error("Не удалось открыть файл для чтения.");
    auto header=io::line(in);
    if(std::strcmp(header.get(),"SHIP_KEEPER_V1")!=0) throw std::runtime_error("Неизвестный формат файла.");
    int n=io::integer(in,nullptr,0,1000000);
    Keeper loaded;
    for(int i=0;i<n;++i) {
        int t=io::integer(in,nullptr,1,3); std::unique_ptr<Base> ship;
        if(t==1) ship=std::make_unique<Submarine>();
        if(t==2) ship=std::make_unique<Sailboat>();
        if(t==3) ship=std::make_unique<Motorboat>();
        ship->read(in,false); loaded.add(*ship);
    }
    char c=0;
    while(in.get(c)) if(!std::isspace(static_cast<unsigned char>(c)))
        throw std::runtime_error("Лишние данные после последнего объекта.");
    if(in.bad()) throw std::runtime_error("Ошибка чтения файла.");
    swap(loaded);
}
