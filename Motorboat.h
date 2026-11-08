#pragma once
#include "Base.h"
#include <memory>
class Motorboat : public Base {
private:
    std::unique_ptr<char[]> purpose_;
    std::unique_ptr<char[]> material_;
    std::unique_ptr<char[]> qualities_;
    double speed_;
    int people_;
    void swap(Motorboat& other) noexcept;
public:
    Motorboat();
    Motorboat(const char* purpose, const char* material, const char* qualities, double speed, int people);
    Motorboat(const Motorboat& other);
    ~Motorboat() override;
    Motorboat& operator=(const Motorboat& other);
    const char* getPurpose() const;
    void setPurpose(const char* value);
    const char* getMaterial() const;
    void setMaterial(const char* value);
    const char* getQualities() const;
    void setQualities(const char* value);
    double getSpeed() const;
    void setSpeed(double value);
    int getPeople() const;
    void setPeople(int value);
    int type() const override;
    Base* clone() const override;
    void print(std::ostream& out) const override;
    void read(std::istream& in, bool prompts) override;
    void edit(std::istream& in) override;
    void write(std::ostream& out) const override;
};
