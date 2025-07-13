// Пример с полями трейтовы

#include <TestTraits/traits_utils.h>

#include <iostream>
#include <string>
template<typename BaseClass>
class abobaInputer {
private:
    int num = 0;

public:
    std::string word;

public:
    void doBeforeSetUp() {
        std::cout << "Input \"Aboba\"\n";
        std::cin >> word;
        while (word != "Aboba") {
            ++num;
            std::cout << "\nAboba EXPEXTED!!!!!!!!!!\n";
            std::cin >> word;
        }
        std::cout << "Good job!\n";
    }

    int getNum() { return num; }
};

#include <TestTraits/traits_group_factory.h>
MAKE_TRAIT_GROUP(AbobaInputerTraitConstructor, abobaInputer)

class Empty {};

class dummy3 : public AbobaInputerTraitConstructor<Empty> {
public:
    void doSetUp() { std::cout << "Aboba printed on " << getNum() << " atempt!\n"; }
};

#include <TestTraits/traits_fixture_factory.h>
TRAIT_FIXTURE_INIT(Traits_members_test, dummy3)

TEST_F(Traits_members_test, Positive_traitsTest) {
    std::cout << "You printed " << word << " word... You are clown.\n";
}
