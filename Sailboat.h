#pragma once
#include "Base.h"
#include <memory>
class Sailboat : public Base {
private:
    std::unique_ptr<char[]> sailType_;
    std::unique_ptr<char[]> name_;
    bool military_;
    double length_;
    double speed_;
    int crew_;
    void swap(Sailboat& other) noexcept;
public:
    Sailboat();
    Sailboat(const char* sailType, const char* name, bool military, double length, double speed, int crew);
    Sailboat(const Sailboat& other);
    ~Sailboat() override;
    Sailboat& operator=(const Sailboat& other);
    const char* getSailType() const;
    void setSailType(const char* value);
    const char* getName() const;
    void setName(const char* value);
    bool getMilitary() const;
    void setMilitary(bool value);
    double getLength() const;
    void setLength(double value);
    double getSpeed() const;
    void setSpeed(double value);
    int getCrew() const;
    void setCrew(int value);
    int type() const override;
    Base* clone() const override;
    void print(std::ostream& out) const override;
    void read(std::istream& in, bool prompts) override;
    void edit(std::istream& in) override;
    void write(std::ostream& out) const override;
};
