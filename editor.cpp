#include "editor.h"
#include "utils.h"
#include <fstream>
#include <limits>
#include <iostream>

Editor::Editor(std::vector<std::string>* contents, const std::string& filename):
    m_current_line(0), m_filename(filename), m_stopped(false)  {

    m_contents = contents;
}

int Editor::run_editor() {
    std::vector<std::string>* c = m_contents;

    while (!m_stopped) {
        print_contents_on_line(m_current_line);
        
        char input = Utils::getch();
        switch (input) {
        case 'e':
            edit_command();
            break;
        case 'm':
            move_to_command();
            break;
        case 'w':
            write_command();
            break;
        case 'q':
            quit_command();
            break;
        default:
            break;
        }
    }
    return 0;
}

int Editor::print_contents_on_line(int line) const {
    int output_length = m_contents->size();
    bool truncated = false;
    if ((int) m_contents->size() > line + OUTPUT_LINE_MAX) {
        output_length = line + OUTPUT_LINE_MAX;
        truncated = true;
    }
    for (int i = line; i < std::min((int) m_contents->size(), line + OUTPUT_LINE_MAX); i++) {
        std::cout << i << " " << m_contents->at(i) << '\n';
    }
    if (truncated) {
        std::cout << "...\n";
    }
}

int Editor::edit_command() {
    std::cout << "Edit which line? ";
    int line;
    std::cin >> line; 
    if (std::cin.fail() || line < 0) {
        std::cout << "Not a valid line number!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return 1;
    }

    return edit_line(line);
}

int Editor::edit_line(int line) {

    if (line >= m_contents->size()) {
        m_contents->resize(line + 1, "");
    }

    std::cout << "> ";
    std::string input;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::getline(std::cin, input);
    std::cin.clear();
    (*m_contents)[line] = input;

    return 0;
}

int Editor::move_to_command() {
    std::cout << "Move to which line? ";
    int line;
    std::cin >> line;
    if (std::cin.fail() || line < 0 || line >= m_contents->size()) {
        std::cout << "Not a valid line number!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return 1;
    }

    return move_to_line(line);
}

int Editor::move_to_line(int line) {
    m_current_line = line;
    return 0;
}

int Editor::write_command() {
    std::cout << "Write to file? [y/n] ";
    char answer = Utils::getch();

    if (answer == 'y') {
        return write();
    }

    return 0;
}

int Editor::write() {
    std::ofstream file;
    file.open(m_filename);
    if (file.fail()) {
        std::cout << "Can't open file " << m_filename << " for writing!";
        return 1;
    }

    for (int i = 0; i < m_contents->size(); i++) {
        file << m_contents->at(i) << '\n';
    }

    file.close();
    
    return 0;   
}

int Editor::quit_command() {
    std::cout << "Really quit? [y/n] ";
    char answer = Utils::getch();

    if (answer == 'y') {
        m_stopped = true;
        std::cout << "\n";
    }

    return 0;
}
