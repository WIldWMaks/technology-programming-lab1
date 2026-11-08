#include "Input.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cmath>
#include <cctype>
#include <stdexcept>
namespace io {
Text copy(const char* value) {
    if (!value) throw std::invalid_argument("Текст не может быть nullptr.");
    Text p(new char[std::strlen(value)+1]);
    std::strcpy(p.get(),value); return p;
}
void checkText(const char* value) {
    if (!value) throw std::invalid_argument("Текст не задан.");
    bool nonblank=false;
    for (const unsigned char* p=reinterpret_cast<const unsigned char*>(value); *p; ++p) {
        if (*p=='\n' || *p=='\r') throw std::invalid_argument("Введите одну строку.");
        if (!std::isspace(*p)) nonblank=true;
    }
    if (!nonblank) throw std::invalid_argument("Текст не должен быть пустым.");
}
void checkReal(double v) {
    if (!std::isfinite(v) || v<=0) throw std::invalid_argument("Число должно быть конечным и больше нуля.");
}
void checkInt(int v) {
    if (v<=0) throw std::invalid_argument("Количество должно быть больше нуля.");
}
Text line(std::istream& in,const char* prompt) {
    if (prompt) std::cout << prompt;
    std::size_t len=0,cap=64; Text p(new char[cap]);
    char ch=0;
    while (in.get(ch) && ch!='\n') {
        if (len>=1024*1024) throw std::runtime_error("Строка длиннее 1 Мбайт.");
        if (len+1>=cap) {
            Text q(new char[cap*2]); std::memcpy(q.get(),p.get(),len);
            p=std::move(q); cap*=2;
        }
        p[len++]=ch;
    }
    if (in.bad() || (in.eof() && len==0)) throw std::runtime_error("Данные закончились или не читаются.");
    if (len && p[len-1]=='\r') --len;
    p[len]='\0'; return p;
}
Text text(std::istream& in,const char* prompt) {
    auto p=line(in,prompt); checkText(p.get()); return p;
}
static bool tailOK(const char* end) {
    while (*end && std::isspace(static_cast<unsigned char>(*end))) ++end;
    return *end=='\0';
}
int integer(std::istream& in,const char* prompt,int min,int max) {
    auto p=line(in,prompt); char* end=nullptr; errno=0;
    long value=std::strtol(p.get(),&end,10);
    if (end==p.get() || !tailOK(end) || errno==ERANGE || value<min || value>max)
        throw std::invalid_argument("Нужно целое число в указанном диапазоне.");
    return static_cast<int>(value);
}
double real(std::istream& in,const char* prompt) {
    auto p=line(in,prompt);
    for (char* q=p.get(); *q; ++q) if (*q==',') *q='.';
    char* end=nullptr; errno=0; double value=std::strtod(p.get(),&end);
    if (end==p.get() || !tailOK(end) || errno==ERANGE)
        throw std::invalid_argument("Нужно корректное вещественное число.");
    checkReal(value); return value;
}
}
