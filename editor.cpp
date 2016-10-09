#include "editor.h"
#include "utils.h"
#include <limits>
#include <iostream>

Editor::Editor(std::vector<std::string>* contents):
    m_current_line(0)  {

    m_contents = contents;
}

int Editor::run_editor() {
    std::vector<std::string>* c = m_contents;

    bool stopped = false;
    while (!stopped) {
        print_contents_on_line(m_current_line);
        
        char input = Utils::getch();
        switch (input) {
        case 'e':
            edit_command();
            break;
        case 'm':
            move_to_command();
            break;
        default:
            break;
        }
    }
    return 0;
}

int Editor::print_contents_on_line(int line) const {
    for (int i = line; i < std::min((int) m_contents->size(), line + OUTPUT_LINE_MAX); i++) {
        std::cout << i << " " << m_contents->at(i) << '\n';
    }
}

int Editor::edit_command() {
    std::cout << "Edit which line? ";
    int line;
    std::cin >> line; if (std::cin.fail() || line < 0 || line >= m_contents->size()) {
        std::cout << "Not a valid line number!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return 1;
    }

    return edit_line(line);
}

int Editor::edit_line(int line) {
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
