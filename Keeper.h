#pragma once
#include "Base.h"
class Keeper {
private:
    Base** items_;
    int count_;
    int capacity_;
    void reserve(int capacity);
    void swap(Keeper& other) noexcept;
public:
    Keeper();
    explicit Keeper(const Base& first);
    Keeper(const Keeper& other);
    ~Keeper();
    Keeper& operator=(const Keeper& other);
    Keeper& operator+=(const Base& item);
    Keeper& operator-=(int index);
    Base& operator[](int index);
    const Base& operator[](int index) const;
    int size() const;
    void add(const Base& item);
    void remove(int index);
    void clear() noexcept;
    void save(const char* path) const;
    void load(const char* path);
};
std::ostream& operator<<(std::ostream& out,const Keeper& keeper);
