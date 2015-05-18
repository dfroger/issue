The **libc++.dylib clang** C++ standard libarry is incompatible with the
**libstdc++.dylib GNU** C++ standard library.

A program must be compiled and linked with only **-stdlib=libc++** (the
default) or with only **-stdlib=stdlibc++**.

See http://stackoverflow.com/a/8457799

For example:

    $ make -f Makefile.bad
    clang++ -c main.cxx -stdlib=libc++
    clang++ -c greet.cxx -stdlib=libstdc++
    clang++ -o greet main.o greet.o
    Undefined symbols for architecture x86_64:
      "greet(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >)", referenced from:
          _main in main.o
      "std::ostream::operator<<(std::ostream& (*)(std::ostream&))", referenced from:
          greet(std::string) in greet.o
      "std::ios_base::Init::Init()", referenced from:
          ___cxx_global_var_init in greet.o
      "std::ios_base::Init::~Init()", referenced from:
          ___cxx_global_var_init in greet.o
      "std::cout", referenced from:
          greet(std::string) in greet.o
      "std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)", referenced from:
          greet(std::string) in greet.o
      "std::basic_ostream<char, std::char_traits<char> >& std::operator<<<std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)", referenced from:
          greet(std::string) in greet.o
      "std::basic_ostream<char, std::char_traits<char> >& std::operator<<<char, std::char_traits<char>, std::allocator<char> >(std::basic_ostream<char, std::char_traits<char> >&, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)", referenced from:
          greet(std::string) in greet.o
    ld: symbol(s) not found for architecture x86_64
    clang: error: linker command failed with exit code 1 (use -v to see invocation)
    make: *** [main] Error 1


Symbols in `greet.o` are:

    $ nm greet.o | grep greet
    0000000000000000 T __Z5greetSs
    0000000000000150 S __Z5greetSs.eh


While symbols in `main.o` are:

    $ nm main.o | grep greet
                     U __Z5greetNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE


Unmangling the symbols give:

    $ c++filt __Z5greetSs __Z5greetSs.eh __Z5greetNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE
    greet(std::string)
    greet(std::string) (.eh)
    greet(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >)



