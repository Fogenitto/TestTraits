// Пример с несколькоими трейтами

#include <TestTraits/traits_utils.h>

#include <iostream>
// пишем первый трейт
template<typename BaseClass>
class printer1 {
    TRAIT_INIT(BaseClass, print_first_trait, std::false_type)

public:
    static void doBeforeSetUpTestCase() {
        if constexpr (print_first_trait::value) {
            std::cout << "First trait set up test case!\n";
        }
    }

    static void doBeforeTearDownTestCase() {
        if constexpr (print_first_trait::value) {
            std::cout << "First trait tear down test case!\n";
        }
    }

    void doBeforeSetUp() {
        if constexpr (print_first_trait::value) {
            std::cout << "First trait set up!\n";
        }
    }

    void doBeforeTearDown() {
        if constexpr (print_first_trait::value) {
            std::cout << "First trait tear down!\n";
        }
    }
};

// пишем первый трейт
template<typename BaseClass>
class printer2 {
    TRAIT_INIT(BaseClass, print_second_trait, std::false_type)

public:
    static void doBeforeSetUpTestCase() {
        if constexpr (print_second_trait::value) {
            std::cout << "Second trait set up test case!\n";
        }
    }

    static void doBeforeTearDownTestCase() {
        if constexpr (print_second_trait::value) {
            std::cout << "Second trait tear down test case!\n";
        }
    }

    void doBeforeSetUp() {
        if constexpr (print_second_trait::value) {
            std::cout << "Second trait set up!\n";
        }
    }

    void doBeforeTearDown() {
        if constexpr (print_second_trait::value) {
            std::cout << "Second trait tear down!\n";
        }
    }
};

template<typename BaseClass>
class printer3 {
    TRAIT_INIT(BaseClass, print_third_trait, std::false_type)

public:
    static void doBeforeSetUpTestCase() {
        if constexpr (print_third_trait::value) {
            std::cout << "Third trait set up test case!\n";
        }
    }

    static void doBeforeTearDownTestCase() {
        if constexpr (print_third_trait::value) {
            std::cout << "Third trait tear down test case!\n";
        }
    }

    void doBeforeSetUp() {
        if constexpr (print_third_trait::value) {
            std::cout << "Third trait set up!\n";
        }
    }

    void doBeforeTearDown() {
        if constexpr (print_third_trait::value) {
            std::cout << "Third trait tear down!\n";
        }
    }
};

#include <TestTraits/fixture_traits_factory.h>
template<typename BaseClass>
using MultiplePrinterTraitConstructor = TraitsFixtureStaticFactory<BaseClass, printer1, printer2, printer3>;

class printer_traits {
public:
    using print_first_trait = std::true_type;
    using print_second_trait = std::true_type;
    using print_third_trait = std::true_type;
};

class dummy2 : public MultiplePrinterTraitConstructor<printer_traits> {
public:
    static void doSetUpTestCase() { std::cout << "SetUpTestCase of base class\n"; }

    static void doTearDownTestCase() { std::cout << "TearDownTestCase of base class\n"; }

    void doSetUp() { std::cout << "Test SetUp of base class\n"; }

    void doTearDown() { std::cout << "Test TearDown of base class\n"; }
};

#include <TestTraits/test_fixture_factory.h>
TEST_TRAIT_INIT(Multiple_traits_test, dummy2)

TEST_F(Multiple_traits_test, Positive_traitsTest) {
    std::cout << "Test body!\n";
}
