#include <iostream>
#include <fstream>
#include <string>
#include "editor.h"

std::string* read_file(const std::string& filename) {
    std::ifstream file(filename);

    if (file.fail())
        return nullptr;

    std::string str;
    std::string* file_contents = new std::string();
    while (std::getline(file, str)) {
        *file_contents += str;
        file_contents->push_back('\n');
    }
    
    return file_contents;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Please provide a file path.\n";
        return 1;
    }

    std::string filepath(argv[1]);
    std::string* contents = read_file(filepath);
    if (contents == nullptr) {
        std::cout << "Error reading file.\n";
        return 1;
    }

    Editor editor(contents);
    editor.run_editor();

    delete contents;

    return 0;
}
