#pragma once

#include "traits_utils.h"

#include <tuple>

namespace test_traits {
namespace detail {

// yeeeee, this is fu..ed up
// instantiate method only if it exist in some trait (good for binary weight)
// than call N lambdas, where N - number of traits.
// In lambda check that trait has method and if true - call it.
#define TEST_TRAIT_METHOD(NAME)                                                                                  \
    template<typename T = TraitsList>                                                                            \
    typename std::enable_if_t<(std::experimental::is_detected<NAME##_method, Traits<T>>::value && ...)> NAME() { \
        (..., [this]() {                                                                                         \
            if constexpr (std::experimental::is_detected<NAME##_method, Traits<T>>::value) {                     \
                Traits<T>::NAME();                                                                               \
            }                                                                                                    \
        }());                                                                                                    \
    }

// can't use this in static functions, so made additional macro
// In the ideal happy world tear down methods should execute in reverse order, but world not ideal or happy, god not
// exist, your dad probably abondoned family and you should write ugly metashitcode to resolve this issue
// TODO: there is defenitly better solution for static methods
#define STATIC_TEST_TRAIT_METHOD(NAME)                                                                         \
    template<typename T = TraitsList>                                                                          \
    static typename std::enable_if_t<(std::experimental::is_detected<NAME##_method, Traits<T>>::value && ...)> \
    NAME() {                                                                                                   \
        (..., []() {                                                                                           \
            if constexpr (std::experimental::is_detected<NAME##_method, Traits<T>>::value) {                   \
                Traits<T>::NAME();                                                                             \
            }                                                                                                  \
        }());                                                                                                  \
    }

template<typename TraitsList, template<typename BaseClass> typename... Traits>
class TraitsGroupStaticFactory : public TraitsList,
                                 public Traits<TraitsList>... {
public:
    TEST_TRAIT_METHOD(doBeforeSetUp)
    TEST_TRAIT_METHOD(doAfterSetUp)

    TEST_TRAIT_METHOD(doBeforeTearDown)
    TEST_TRAIT_METHOD(doAfterTearDown)

    STATIC_TEST_TRAIT_METHOD(doBeforeSetUpTestCase)
    STATIC_TEST_TRAIT_METHOD(doAfterSetUpTestCase)

    STATIC_TEST_TRAIT_METHOD(doBeforeTearDownTestCase)
    STATIC_TEST_TRAIT_METHOD(doAfterTearDownTestCase)
};
} // namespace detail
} // namespace test_traits

// -Ебанет?
// -Да вроде не должно. (This macro wasn't tested)
#define MAKE_TRAIT_GROUP(NAME, ...) \
    template<typename BaseClass>    \
    using NAME = test_traits::detail::TraitsGroupStaticFactory<BaseClass, __VA_ARGS__>;
