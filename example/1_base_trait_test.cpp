// Пример написания своих gtest трейтов и их использования

// Определяем класс с необходимыи нам трейтами, для этого подключаем заголовок ниже
#include <TestTraits/traits_utils.h>

// Пишем свой трейт класс (это кринжовое рабочее название)
#include <iostream>

// Обязательно нужно указать базовый тип, это тот у которого мы будем парсить значения трейтов
template<typename BaseClass>
class memePrinter {
    // Этот макрос определяет нам трейт и задает его дефолтное значение
    TRAIT_INIT(BaseClass, print_aboba_on_case_set_up, std::false_type)

    TRAIT_INIT(BaseClass, print_zeleboba_on_case_tear_down, std::true_type)
    TRAIT_INIT(BaseClass, print_biba_on_test_set_up, std::false_type)
    TRAIT_INIT(BaseClass, print_boba_on_test_tear_down, std::true_type)

public:
    // Далее необходимо определить целевые методы трейта, а именно

    // doBeforeSetUpTestCase
    // doAfterSetUpTestCase
    // doBeforeTearDownTestCase
    // doAfterTearDownTestCase
    // doBeforeSetUp
    // doAfterSetUp
    // doBeforeTearDown
    // doAfterTearDown

    // Если вы знаете gtest, то всё поймете по названию

    // Целевые методы в текущей реализации нужно определять именно в public
    // Никакого ограничения на то, какие методы должны быть опередены нет, можно и никакой не определять,
    // но тогда трейт по сути ничего не будет делать

    // Хочу печатать абобу перед каждым набором тестов
    static void doBeforeSetUpTestCase() {
        if constexpr (print_aboba_on_case_set_up::value) {
            std::cout << "Aboba!\n";
        }
    }

    static void doAfterSetUpTestCase() { std::cout << "Printed after SetUpTestCase\n"; }

    // Конечно можно определять и другие методы, которые потом унаследуются сконструированным классом
    // Вот это потом используем
    static void printSetUpTestCaseBody() { std::cout << "SetUpTestCase of base class\n"; }

private: // Бибу хочу принтить только в трейтах
    void printBiba() { std::cout << "Biba!\n"; }

public:
    static void doBeforeTearDownTestCase() {
        if constexpr (print_zeleboba_on_case_tear_down::value) {
            std::cout << "Zeleboba!\n";
        }
    }

    void doBeforeSetUp() {
        if constexpr (print_biba_on_test_set_up::value) {
            printBiba(); // использовали внутреннию функцию трейта
        }
    }

    void doBeforeTearDown() {
        if constexpr (print_boba_on_test_tear_down::value) {
            std::cout << "Boba!\n";
        }
    }
};

// Дальше удобно сделать alias, на статическую факту, которая по сути аккамулирует в себе множество трейтов
// В нашем случае это множество из одного трейта, но так то их кол-во неограниченно (теоритически)

// TODO: возможно это стоит запихнуть это в отдельный обязательный макрос
#include <TestTraits/traits_group_factory.h>
MAKE_TRAIT_GROUP(PrinterTraitConstructor, memePrinter)

// Теперь самое интересное - как использовать трейты

// Определим класс (ну или лучше структуру) с трейтами
// Для трейтов которые мы не определили используются дефолтные значения, которые мы задали в трейт классе
class printer_traits {
public:
    using print_aboba_on_case_set_up = std::true_type;
};

// Далее наследуемся от нашей группы трейтов
class dummy : public PrinterTraitConstructor<printer_traits> {
public:
    // Определяем методы для тест кейса. Причем можем использовать переменные и методы из классов трейтов.
    // (мне лень писать пример с переменной, умные все поняли)
    static void doSetUpTestCase() { printSetUpTestCaseBody(); }

    static void doTearDownTestCase() { std::cout << "TearDownTestCase of base class\n"; }

    void doSetUp() { std::cout << "Test SetUp of base class\n"; }

    void doTearDown() { std::cout << "Test TearDown of base class\n"; }
};

// Ну а дальше даем макросу сконструировать нам итоговый тест сьют (йес, айм фром ингланд)
#include <TestTraits/traits_fixture_factory.h>
TRAIT_FIXTURE_INIT(Traits_fixture_test, dummy)

TEST_F(Traits_fixture_test, Positive_traitsTest) {
    std::cout << "Test body!\n";
}
