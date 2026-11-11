#include "Keeper.h"
#include "Submarine.h"
#include "Sailboat.h"
#include "Motorboat.h"
#include "Input.h"
#include <cassert>
#include <cstring>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <limits>
#include <iostream>
#include <stdexcept>
template<class F> void mustThrow(F f) {
    bool thrown=false;
    try { f(); } catch(const std::exception&) { thrown=true; }
    assert(thrown);
}
class Fixture : public Base {
public:
    static int alive;
    Fixture() { ++alive; }
    Fixture(const Fixture& x) : Base(x) { ++alive; }
    ~Fixture() override { --alive; }
    int type() const override { return 1; }
    Base* clone() const override { return new Fixture(*this); }
    void print(std::ostream&) const override {}
    void read(std::istream&,bool) override {}
    void edit(std::istream&) override {}
    void write(std::ostream&) const override {}
};
int Fixture::alive=0;
int main(int argc,char** argv) {
    assert(argc==2);
    { Keeper k; Fixture f; k.add(f); assert(k.size()==1); }
    assert(Fixture::alive==0);
    Submarine sub(100,12,80,1000,25,"Torpedoes");
    Sailboat sail("Бриг","Маяк",false,30,12,12);
    Motorboat boat("Рыбалка","Алюминий","Глиссирующий",20,4);
    Keeper k; k+=sub; k+=sail; k+=boat;
    assert(k.size()==3 && k[0].type()==1 && k[1].type()==2 && k[2].type()==3);
    Keeper copied(k); Keeper assigned; assigned=k;
    dynamic_cast<Sailboat&>(k[1]).setName("Новый");
    assert(std::strcmp(dynamic_cast<Sailboat&>(copied[1]).getName(),"Маяк")==0);
    assert(std::strcmp(dynamic_cast<Sailboat&>(assigned[1]).getName(),"Маяк")==0);
    k=k; k+=k[1]; assert(k.size()==4);
    k-=0; assert(k.size()==3 && k[0].type()==2);
    mustThrow([&]{ k.remove(-1); });
    mustThrow([&]{ (void)k[3]; });
    mustThrow([&]{ sub.setSpeed(0); });
    mustThrow([&]{ boat.setPeople(-3); });
    mustThrow([&]{ sail.setName("   "); });
    mustThrow([&]{ sub.setWidth(std::numeric_limits<double>::quiet_NaN()); });
    assert(sub.getSpeed()==25 && boat.getPeople()==4);
    std::istringstream field("2\nПарус\n"); sail.edit(field);
    assert(std::strcmp(sail.getName(),"Парус")==0);
    auto path=std::filesystem::u8path(argv[1]);
    k.save(argv[1]);
    Keeper loaded; loaded.load(argv[1]);
    assert(loaded.size()==3 && loaded[0].type()==2 && loaded[1].type()==3);
    assert(std::strcmp(dynamic_cast<Sailboat&>(loaded[0]).getName(),"Новый")==0);
    assert(dynamic_cast<Motorboat&>(loaded[1]).getSpeed()==20);
    {
        std::ofstream f(path); f << "SHIP_KEEPER_V1\n2\n1\n100\n12\n";
    }
    mustThrow([&]{ loaded.load(argv[1]); });
    assert(loaded.size()==3 && loaded[0].type()==2);
    {
        std::ofstream f(path); f << "SHIP_KEEPER_V1\n1\n99\n";
    }
    mustThrow([&]{ loaded.load(argv[1]); }); assert(loaded.size()==3);
    {
        std::ofstream f(path); f << "BAD\n";
    }
    mustThrow([&]{ loaded.load(argv[1]); }); assert(loaded.size()==3);
    {
        std::ofstream f(path); f << "SHIP_KEEPER_V1\n0\nJUNK\n";
    }
    mustThrow([&]{ loaded.load(argv[1]); }); assert(loaded.size()==3);
    Keeper empty; empty.save(argv[1]); loaded.load(argv[1]); assert(loaded.size()==0);
    std::istringstream comma("2,75\n"); assert(io::real(comma)==2.75);
    std::istringstream junk("12abc\n"); mustThrow([&]{ io::integer(junk,nullptr,0,100); });
    std::istringstream infinity("inf\n"); mustThrow([&]{ io::real(infinity); });
    std::istringstream badRead("20\n0\n"); mustThrow([&]{ sub.read(badRead,false); });
    assert(sub.getLength()==100);
    std::unique_ptr<char[]> longText(new char[10001]);
    std::memset(longText.get(),'a',10000); longText[10000]=0;
    sail.setName(longText.get()); assert(std::strlen(sail.getName())==10000);
    Keeper first(sub); assert(first.size()==1);
    std::cout << "ALL TESTS PASSED\n";
}
