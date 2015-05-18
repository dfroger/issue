#include <string>
#include <iostream>

#include "greet.hxx"

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " NAME" << std::endl;
        exit(1);
    }
    std::string name = argv[1];
    greet(name);

    return 0;
}
