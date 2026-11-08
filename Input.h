#pragma once
#include <memory>
#include <iosfwd>
namespace io {
using Text = std::unique_ptr<char[]>;
Text copy(const char* text);
void checkText(const char* text);
void checkReal(double value);
void checkInt(int value);
Text line(std::istream& in, const char* prompt = nullptr);
Text text(std::istream& in, const char* prompt = nullptr);
int integer(std::istream& in, const char* prompt, int min, int max);
double real(std::istream& in, const char* prompt = nullptr);
}
