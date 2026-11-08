#include "Motorboat.h"
#include "Input.h"
#include <iostream>
#include <climits>
#include <utility>
Motorboat::Motorboat() : Base("Motorboat"), purpose_(io::copy("")), material_(io::copy("")), qualities_(io::copy("")), speed_(0), people_(0) {
    std::cout << "[Motorboat] Конструктор без параметров: " << this << '\n';
}
Motorboat::Motorboat(const char* purpose, const char* material, const char* qualities, double speed, int people) : Base("Motorboat"), purpose_(io::copy(purpose)), material_(io::copy(material)), qualities_(io::copy(qualities)), speed_(speed), people_(people) {
    io::checkText(purpose_.get());
    io::checkText(material_.get());
    io::checkText(qualities_.get());
    io::checkReal(speed_);
    io::checkInt(people_);
    std::cout << "[Motorboat] Конструктор с параметрами: " << this << '\n';
}
Motorboat::Motorboat(const Motorboat& other) : Base(other), purpose_(io::copy(other.purpose_.get())), material_(io::copy(other.material_.get())), qualities_(io::copy(other.qualities_.get())), speed_(other.speed_), people_(other.people_) {
    std::cout << "[Motorboat] Конструктор копирования: " << &other << " -> " << this << '\n';
}
Motorboat::~Motorboat() { std::cout << "[Motorboat] Деструктор: " << this << '\n'; }
void Motorboat::swap(Motorboat& other) noexcept {
    std::swap(purpose_,other.purpose_);
    std::swap(material_,other.material_);
    std::swap(qualities_,other.qualities_);
    std::swap(speed_,other.speed_);
    std::swap(people_,other.people_);
}
Motorboat& Motorboat::operator=(const Motorboat& other) {
    if (this!=&other) { Motorboat temp(other); swap(temp); }
    return *this;
}
const char* Motorboat::getPurpose() const { return purpose_.get(); }
void Motorboat::setPurpose(const char* value) {
    io::checkText(value);
    purpose_=io::copy(value);
}
const char* Motorboat::getMaterial() const { return material_.get(); }
void Motorboat::setMaterial(const char* value) {
    io::checkText(value);
    material_=io::copy(value);
}
const char* Motorboat::getQualities() const { return qualities_.get(); }
void Motorboat::setQualities(const char* value) {
    io::checkText(value);
    qualities_=io::copy(value);
}
double Motorboat::getSpeed() const { return speed_; }
void Motorboat::setSpeed(double value) {
    io::checkReal(value);
    speed_=value;
}
int Motorboat::getPeople() const { return people_; }
void Motorboat::setPeople(int value) {
    io::checkInt(value);
    people_=value;
}
int Motorboat::type() const { return 3; }
Base* Motorboat::clone() const { return new Motorboat(*this); }
void Motorboat::print(std::ostream& out) const {
    out << "Катер\n";
    out << "Назначение: " << getPurpose() << '\n';
    out << "Материал корпуса: " << getMaterial() << '\n';
    out << "Ходовые качества: " << getQualities() << '\n';
    out << "Скорость, узлы: " << getSpeed() << '\n';
    out << "Людей на борту: " << getPeople() << '\n';
}
void Motorboat::read(std::istream& in,bool prompts) {
    auto new_purpose=io::text(in,prompts?"Назначение: ":nullptr);
    auto new_material=io::text(in,prompts?"Материал корпуса: ":nullptr);
    auto new_qualities=io::text(in,prompts?"Ходовые качества: ":nullptr);
    auto new_speed=io::real(in,prompts?"Скорость, узлы: ":nullptr);
    auto new_people=io::integer(in,prompts?"Людей на борту: ":nullptr,1,INT_MAX);
    Motorboat temp(new_purpose.get(), new_material.get(), new_qualities.get(), new_speed, new_people);
    *this=temp;
}
void Motorboat::edit(std::istream& in) {
    std::cout << "1. Назначение\n";
    std::cout << "2. Материал корпуса\n";
    std::cout << "3. Ходовые качества\n";
    std::cout << "4. Скорость, узлы\n";
    std::cout << "5. Людей на борту\n";
    int field=io::integer(in,"Номер поля: ",1,5);
    switch(field) {
    case 1: { auto value=io::text(in,"Назначение: "); setPurpose(value.get()); break; }
    case 2: { auto value=io::text(in,"Материал корпуса: "); setMaterial(value.get()); break; }
    case 3: { auto value=io::text(in,"Ходовые качества: "); setQualities(value.get()); break; }
    case 4: { auto value=io::real(in,"Скорость, узлы: "); setSpeed(value); break; }
    case 5: { auto value=io::integer(in,"Людей на борту: ",1,INT_MAX); setPeople(value); break; }
    }
}
void Motorboat::write(std::ostream& out) const {
    out << purpose_.get() << '\n';
    out << material_.get() << '\n';
    out << qualities_.get() << '\n';
    out << speed_ << '\n';
    out << people_ << '\n';
}
