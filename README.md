# sfinae-utility

A C++ header-only library for [SFINAE](http://en.cppreference.com/w/cpp/language/sfinae).

## How to use?

This is a single header library. So just copy the file inside `include/` into your project.

The following SFINAE functions are provided:
```
is_container<Container>
has_find_method<Container, TypePassToFindMethod>
has_key_type<Container, KeyType>
has_value_type<Container, ValueType>
has_mapped_type<Container, MappedType>
has_key_or_value_type<Container, KeyOrValueType>
is_container_with_value_type<Container, ValueType>
is_container_with_find_method<Container, KeyOrValueType>
is_map_container_with_types<Conainer, KeyType, MappedType>
```

For each of these functions, there is a helper variable template whose name has a suffix `_v`. For example, `is_container_v<Container>` is equivalent to `is_container<Container>::value`.

## Functions

* `is_container<Container>`

Return true if the input is a STL-like container. Specially, it checks whether `Container` has certain member types (`value_type`, `size_type`, `allocator_type`, `iterator` and `const_iterator`) and accepts certain methods (`size()`, `begin()` and `end()`).

* `has_find_method<Container, TypePassToFindMethod>`

Return true if the container accepts `find(TypePassToFindMethod)` method.

* `has_key_type<Container, KeyType>`

Return true if the `Container::key_type` is `KeyType`.

* `has_value_type<Container, ValueType>`

Return true if the `Container::value_type` is `ValueType`.

* `has_mapped_type<Container, MappedType>`

Return true if the `Container::mapped_type` is `MappedType`.

* `has_key_or_value_type<Container, KeyOrValueType>`

Return true if the input has `KeyOrValueType` as `Container::key_type` or `Container::value_type`.

* `is_container_with_value_type<Container, ValueType>`

Return true if the input is a STL-like container and has `ValueType` as `Container::value_type`.

* `is_container_with_find_method<Container, KeyOrValueType>`

Return true if the input is a STL-like container, has `KeyOrValueType` as `Container::key_type` or `Container::value_type`, and accepts `find(KeyOrValueType)` method. This is useful to check whether the input is a `std::set` or `std::map` like container.

* `is_map_container_with_types<Conainer, KeyType, MappedType>`

Return true if the input is a STL-like map container and has `KeyType` as `Container::key_type` and `MappedType` as `Container::mapped_type`.

## Author

* [Xu Cheng](https://xuc.me)

## License

MIT License.
