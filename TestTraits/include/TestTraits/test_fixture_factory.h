#pragma once
#include "traits_utils.h"

#include <gtest/gtest.h>

#define CALL_IF_HAS_METHOD(NAME)                                                     \
    if constexpr (std::experimental::is_detected<NAME##_method, BaseClass>::value) { \
        BaseClass::NAME();                                                           \
    }

// Final test fixture class construction
template<typename BaseClass>
class FinalTestFixtureStaticFactory : public BaseClass,
                                      public ::testing::Test {
public:
    // template member functions can't be virtual, so we should instantiate every one of gtest care methods there
    void SetUp() override {
        CALL_IF_HAS_METHOD(doBeforeSetUp)
        CALL_IF_HAS_METHOD(doSetUp)
        CALL_IF_HAS_METHOD(doAfterSetUp)
    }

    void TearDown() override {
        CALL_IF_HAS_METHOD(doBeforeTearDown)
        CALL_IF_HAS_METHOD(doTearDown)
        CALL_IF_HAS_METHOD(doAfterTearDown)
    }

    static void SetUpTestCase() {
        CALL_IF_HAS_METHOD(doBeforeSetUpTestCase)
        CALL_IF_HAS_METHOD(doSetUpTestCase)
        CALL_IF_HAS_METHOD(doAfterSetUpTestCase)
    }

    static void TearDownTestCase() {
        CALL_IF_HAS_METHOD(doBeforeTearDownTestCase)
        CALL_IF_HAS_METHOD(doTearDownTestCase)
        CALL_IF_HAS_METHOD(doAfterTearDownTestCase)
    }
};

// Сначала явно инстанцируем трейт потому что так мы точно будем уверены что инстанцируются все методы
// В принципе можно обойтись и без этого, но так будет безопаснее т.к. отловим все синтаксические ошибки в классе
// Способ удобнее задать имя для фикстуры я не придумал
#define TEST_TRAIT_INIT(TRAIT_FIXTURE_NAME, TRAIT_FIXTURE)       \
    template class FinalTestFixtureStaticFactory<TRAIT_FIXTURE>; \
    using TRAIT_FIXTURE_NAME = FinalTestFixtureStaticFactory<TRAIT_FIXTURE>;
