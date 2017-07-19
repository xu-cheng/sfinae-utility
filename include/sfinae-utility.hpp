#pragma once

#include <type_traits>
#include <utility>

namespace sfinae
{
    // Ref: http://stackoverflow.com/a/31207079

    template <typename... Ts>
    struct _helper {
    };

    template <class Container, class = void>
    struct is_container : std::false_type {
    };
    template <class Container>
    struct is_container<Container,
                        typename std::conditional<
                            false,
                            _helper<typename Container::value_type,
                                    typename Container::size_type,
                                    typename Container::allocator_type,
                                    typename Container::iterator,
                                    typename Container::const_iterator,
                                    decltype(std::declval<Container>().size()),
                                    decltype(std::declval<Container>().begin()),
                                    decltype(std::declval<Container>().end())>,
                            void>::type> : std::true_type {
    };

    template <class Container, class T, class = void>
    struct has_find_method : std::false_type {
    };
    template <class Container, class T>
    struct has_find_method<Container, T,
                           typename std::conditional<
                               false,
                               _helper<decltype(std::declval<Container>().find(
                                   std::declval<T>()))>,
                               void>::type> : std::true_type {
    };

    template <class Container, class T>
    struct has_the_same_key_type
        : std::is_same<typename Container::key_type, T> {
    };

    template <class Container, class T>
    struct has_the_same_value_type
        : std::is_same<typename Container::value_type, T> {
    };

    template <class Container, class T>
    struct has_the_same_mapped_type
        : std::is_same<typename Container::mapped_type, T> {
    };

    template <class Container, class T>
    struct has_the_same_key_or_value_type
        : std::integral_constant<
              bool, has_the_same_key_type<Container, T>::value ||
                        has_the_same_value_type<Container, T>::value> {
    };

    template <class Container, class T>
    struct is_container_with_fixed_value_type
        : std::integral_constant<
              bool, is_container<Container>::value &&
                        has_the_same_value_type<Container, T>::value> {
    };

    template <class Container, class T>
    struct is_container_with_fixed_type_and_find_method
        : std::integral_constant<
              bool, is_container<Container>::value &&
                        has_find_method<Container, T>::value &&
                        has_the_same_key_or_value_type<Container, T>::value> {
    };

    template <class Container, class Key, class Value>
    struct is_map_container_with_fixed_type
        : std::integral_constant<
              bool, is_container<Container>::value &&
                        has_find_method<Container, Key>::value &&
                        has_the_same_key_type<Container, Key>::value &&
                        has_the_same_mapped_type<Container, Value>::value> {
    };
}
