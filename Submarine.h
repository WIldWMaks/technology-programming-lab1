#pragma once
#include "Base.h"
#include <memory>
class Submarine : public Base {
private:
    double length_;
    double width_;
    int crew_;
    double endurance_;
    double speed_;
    std::unique_ptr<char[]> weapons_;
    void swap(Submarine& other) noexcept;
public:
    Submarine();
    Submarine(double length, double width, int crew, double endurance, double speed, const char* weapons);
    Submarine(const Submarine& other);
    ~Submarine() override;
    Submarine& operator=(const Submarine& other);
    double getLength() const;
    void setLength(double value);
    double getWidth() const;
    void setWidth(double value);
    int getCrew() const;
    void setCrew(int value);
    double getEndurance() const;
    void setEndurance(double value);
    double getSpeed() const;
    void setSpeed(double value);
    const char* getWeapons() const;
    void setWeapons(const char* value);
    int type() const override;
    Base* clone() const override;
    void print(std::ostream& out) const override;
    void read(std::istream& in, bool prompts) override;
    void edit(std::istream& in) override;
    void write(std::ostream& out) const override;
};
