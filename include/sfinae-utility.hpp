#pragma once

#include <type_traits>
#include <utility>

namespace sfinae
{
    // Ref: https://stackoverflow.com/a/31207079

    namespace detail
    {
        template <typename... Ts>
        struct helper {
        };
    }

    template <class Container, class = void>
    struct is_container : std::false_type {
    };
    template <class Container>
    struct is_container<
        Container,
        typename std::conditional<
            false,
            detail::helper<typename Container::value_type,
                           typename Container::size_type,
                           typename Container::allocator_type,
                           typename Container::iterator,
                           typename Container::const_iterator,
                           decltype(std::declval<Container>().size()),
                           decltype(std::declval<Container>().begin()),
                           decltype(std::declval<Container>().end())>,
            void>::type> : std::true_type {
    };
    template <class Container>
    constexpr bool is_container_v = is_container<Container>::value;

    template <class Container, class T, class = void>
    struct has_find_method : std::false_type {
    };
    template <class Container, class T>
    struct has_find_method<
        Container, T,
        typename std::conditional<
            false,
            detail::helper<decltype(
                std::declval<Container>().find(std::declval<T>()))>,
            void>::type> : std::true_type {
    };
    template <class Container, class T>
    constexpr bool has_find_method_v = has_find_method<Container, T>::value;

    template <class Container, class T>
    struct has_key_type : std::is_same<typename Container::key_type, T> {
    };
    template <class Container, class T>
    constexpr bool has_key_type_v = has_key_type<Container, T>::value;

    template <class Container, class T>
    struct has_value_type : std::is_same<typename Container::value_type, T> {
    };
    template <class Container, class T>
    constexpr bool has_value_type_v = has_value_type<Container, T>::value;

    template <class Container, class T>
    struct has_mapped_type : std::is_same<typename Container::mapped_type, T> {
    };
    template <class Container, class T>
    constexpr bool has_mapped_type_v = has_mapped_type<Container, T>::value;

    template <class Container, class T>
    struct has_key_or_value_type
        : std::integral_constant<bool,
                                 has_key_type<Container, T>::value ||
                                     has_value_type<Container, T>::value> {
    };
    template <class Container, class T>
    constexpr bool has_key_or_value_type_v =
        has_key_or_value_type<Container, T>::value;

    template <class Container, class T>
    struct is_container_with_value_type
        : std::integral_constant<bool,
                                 is_container<Container>::value &&
                                     has_value_type<Container, T>::value> {
    };
    template <class Container, class T>
    constexpr bool is_container_with_value_type_v =
        is_container_with_value_type<Container, T>::value;

    template <class Container, class T>
    struct is_container_with_find_method
        : std::integral_constant<
              bool, is_container<Container>::value &&
                        has_find_method<Container, T>::value &&
                        has_key_or_value_type<Container, T>::value> {
    };
    template <class Container, class T>
    constexpr bool is_container_with_find_method_v =
        is_container_with_find_method<Container, T>::value;

    template <class Container, class Key, class Value>
    struct is_map_container_with_types
        : std::integral_constant<bool,
                                 is_container<Container>::value &&
                                     has_find_method<Container, Key>::value &&
                                     has_key_type<Container, Key>::value &&
                                     has_mapped_type<Container, Value>::value> {
    };
    template <class Container, class Key, class Value>
    constexpr bool is_map_container_with_types_v =
        is_map_container_with_types<Container, Key, Value>::value;
}
