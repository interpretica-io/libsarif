# libsarif (C++)

This project is just a trivial header-only parser/serializer for [Static Analysis Results Interchange Format (SARIF)](https://github.com/oasis-tcs/sarif-spec).

## Integration

There are numerous ways to use the library.

Use git submodules:
```
git submodule add https://github.com/maximmenshikov/libsarif
```

After that it is possible to add subdirectory:

```add_subdirectory(libsarif)```

Link to `libsarif`:

```
target_link_libraries(target libsarif)
```

## Parsing example

This example shows how to parse SARIF example from specification.

```
const char sarif_example[] =
    "{\n"
    "  \"version\": \"2.1.0\",\n"
    "  \"runs\": [\n"
    "    {\n"
    "      \"tool\": {\n"
    "        \"driver\": {\n"
    "          \"name\": \"CodeScanner\"\n"
    "        }\n"
    "      },\n"
    "      \"results\": []\n"
    "    }\n"
    "  ]\n"
    "}";

TEST(Sarif, basic_parse)
{
    libsarif::TopLevel data = nlohmann::json::parse(sarif_example);
    ASSERT_EQ(data.get_version(), libsarif::Version::THE_210);
    for (auto &run : data.get_runs())
    {
        ASSERT_EQ(run.get_tool().get_driver().get_name(), "CodeScanner");
    }
}
```

## Update schema

Use ```./generate.sh <json schema file>``` to build a new header.

## License and acknowledgements

See LICENSE (which is MIT), make sure you comply to license in the [official specification repository](https://github.com/oasis-tcs/sarif-spec).

Authors of this library don't hold copyright of the SARIF specification.

Thanks to the developers of SARIF specification, [quicktype](https://github.com/quicktype/quicktype) library authors, Niels Lohmann for his [JSON library](https://github.com/nlohmann/json).
