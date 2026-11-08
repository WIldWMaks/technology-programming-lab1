#pragma once
#include <iosfwd>
class Base {
public:
    Base();
    explicit Base(const char* type);
    Base(const Base& other);
    virtual ~Base();
    virtual int type() const = 0;
    virtual Base* clone() const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void read(std::istream& in, bool prompts) = 0;
    virtual void edit(std::istream& in) = 0;
    virtual void write(std::ostream& out) const = 0;
};
std::ostream& operator<<(std::ostream& out, const Base& ship);
