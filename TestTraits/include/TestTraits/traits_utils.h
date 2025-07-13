#pragma once

#include <experimental/type_traits>
#include <type_traits>

#define HAS_TRAIT_INIT(CLASS, TRAIT)                                             \
private:                                                                         \
    template<typename T, typename = void>                                        \
    struct check_##TRAIT : std::false_type {};                                   \
                                                                                 \
    template<typename T>                                                         \
    struct check_##TRAIT<T, std::void_t<typename T::TRAIT>> : std::true_type {}; \
                                                                                 \
public:                                                                          \
    using has_##TRAIT = check_##TRAIT<CLASS>;

#define CHECK_TEST_TRAIT_METHOD(NAME) \
    template<typename traitClass>     \
    using NAME##_method = decltype(std::declval<traitClass>().NAME());

namespace test_traits {
namespace detail {
CHECK_TEST_TRAIT_METHOD(doBeforeSetUp)
CHECK_TEST_TRAIT_METHOD(doAfterSetUp)
CHECK_TEST_TRAIT_METHOD(doBeforeTearDown)
CHECK_TEST_TRAIT_METHOD(doAfterTearDown)
CHECK_TEST_TRAIT_METHOD(doBeforeSetUpTestCase)
CHECK_TEST_TRAIT_METHOD(doAfterSetUpTestCase)
CHECK_TEST_TRAIT_METHOD(doBeforeTearDownTestCase)
CHECK_TEST_TRAIT_METHOD(doAfterTearDownTestCase)

CHECK_TEST_TRAIT_METHOD(doSetUp)
CHECK_TEST_TRAIT_METHOD(doTearDown)
CHECK_TEST_TRAIT_METHOD(doSetUpTestCase)
CHECK_TEST_TRAIT_METHOD(doTearDownTestCase)
} // namespace detail
} // namespace test_traits

// macro for definition of test traits in traits class
#define TRAIT_INIT(CLASS, TRAIT, DEFAULT)                                 \
    HAS_TRAIT_INIT(CLASS, TRAIT)                                          \
private:                                                                  \
    template<typename T, typename = void>                                 \
    struct init_##TRAIT : DEFAULT {};                                     \
                                                                          \
    template<typename T>                                                  \
    struct init_##TRAIT<T, std::void_t<typename T::TRAIT>> : T::TRAIT {}; \
                                                                          \
public:                                                                   \
    using TRAIT = typename init_##TRAIT<CLASS>::type;
