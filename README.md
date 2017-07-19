# sfinae-utility

A C++ header-only library for [SFINAE](http://en.cppreference.com/w/cpp/language/sfinae).

## How to use?

This is a single header library. So just copy the file inside `include/` into your project.

The following SFINAE functions are provided:
```
is_container<Container>
has_find_method<Container, TypePassToFindMethod>
has_the_same_key_type<Container, KeyType>
has_the_same_value_type<Container, ValueType>
has_the_same_mapped_type<Container, MappedType>
has_the_same_key_or_value_type<Container, KeyOrValueType>
is_container_with_fixed_value_type<Container, ValueType>
is_container_with_fixed_type_and_find_method<Container, KeyOrValueType>
is_map_container_with_fixed_type<Conainer, KeyType, MappedType>
```

## Author

* [Xu Cheng](https://xuc.me)

## License

MIT License.
