#  string_enum
string_enum is a small header-only C++ library. It provides a  macro  that  generates an  object  which  behaves  as a  enum  class  and can be converted to a string.

# motivation
I think that every programmer faced the following problem: one would like to send a enum value to a log stream, but when a enum value is printed, one sees an integer number which doesn't give much understanding what is that until one counts elements in the enum. Enum element's name would be much more preferable. So, string_enum has been designed to solve this problem without adding significant overhead.


#  how  to  build
This  project  uses CMake as a build system, so build procedure for string_enum is very typical for it.
```
git clone https://github.com/eugenebas/string_enum.git
mkdir string_enum_build && cd ./string_enum_build
cmake ../string_enum
cmake --build . -j
```
To make sure the build is OK, one can run unit tests:
```
ctest .
```
To install it in Slackware style one can launch install target (default location is `/usr/local`):
```
cmake --install .
```
To redefine default prefix use `--prefix` option:
```
cmake --install . --prefix "/my/special/prefix/for/github/libraries"
```
For redistribution you can pack into in archive (check supported archive formats in the [CMake documentation](https://cmake.org/cmake/help/latest/cpack_gen/archive.html)):
```
cpack -G ZIP
```
For better integration with OS package manager you can generate .deb package:
```
cpack -G DEB
```
or .rpm package:
```
cpack -G RPM
```

# how to use
To be able to use the library include the only public header `string_enum/string_enum.hpp`. And then use `STRING_ENUM` macro to define new enums (it's behavior should be consistent with built-in enum classes, so old declarations can be replaced with the `STRING_ENUM` macro without necessity to re-write legacy code). Here's an example:
```
#include <string_enum/string_enum.hpp>
#include <iostream>

STRING_ENUM(Color,
  Red,
  Green,
  Blue
);

int main(int argc, char** argv) {
        std::cout << Color::Red << std::endl;
        Color c = Color::Green;
        std::cout << Color::Green << std::endl;
        c = Color::Blue;
        switch(c) {
                case Color::Red:
                case Color::Green:
                        std::cout << "We expected Blue :(" << std::endl;
                        return 1;
                case Color::Blue:
                        std::cout << "Blue is the color I've expected!" << std::endl;
        }
        return 0;
}
```
And here's the output of this example:
```
Red
Green
Blue is the color I've expected!
```

# known restrictions
1. STRING_ENUM macro doesn't support explicit value setting for its elements
2. STRING_ENUM macro doesn't support explicit setting of the underlying integer type
3. STRING_ENUM element count can't exceed STRING_ENUM_MAX_SIZE which is set during the build procedure (default value is 255)
4. STRING_ENUM macro doesn't support creation from string
