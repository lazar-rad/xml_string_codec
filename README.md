# XML_string_codec

A simple library for encoding and decoding strings for the use in XML files

Written for [*Triangulator*](https://github.com/vvmarko/triangulator)

# Use

The library contains the following two functions:

    std::string encode_string_for_xml( std::string s );
    std::string decode_string_from_xml( std::string s );

The strings are encoded by escaping the “problematic” characters: `<`, `>`, `&`, `'`, and `"`, as well as the `space` character, using standard ways of doing so:

- `<` --> `&lt;`
- `>` --> `&gt;`
- `&` --> `&amp;`
- `'` --> `&apos;`
- `"` --> `&quot;`
- ` ` --> `&#x20;`

Only the aforementioned characters can be produced when decoding an escaped portion, even though it can be argued that the library should decode all numerical escapings.

When decoding, if the input string was not escaped correctly, string `"error"` is returned.

# Build

- `make lib` : creates a static library called `libxml_string_codec.a`
- `make test` : creates an executable out of the `test.cpp` source and the static library

# Testing

By default, the test showcases examples of encoding and decoding of all considered characters. The test also showcases several examples of decoding incorrect strings.

When invoking `test`, you can pass string arguments to be encoded or decoded. Use the options `-e` or `-d` before the argument to denote whether it should be encoded or decoded, respectively. Arguments that are not preceded by an option are ignored. The default examples are shown after the ones passed by you.