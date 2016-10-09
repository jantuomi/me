#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Please provide a file path.";
        return 1;
    }

    std::string filepath(argv[1]);

    return 0;
}
