#include "editor.h"
#include "utils.h"
#include <fstream>
#include <limits>
#include <iostream>
#include <iomanip>

Editor::Editor(std::vector<std::string>* contents, const std::string& filename):
    m_contents(contents), m_filename(filename), m_current_line(0), m_stopped(false)  {

    m_contents = contents;
}

int Editor::run_editor() {

    while (!m_stopped) {
        if (m_contents->size() == 0) {
            m_contents->push_back("");
        }

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
        case 'd':
            delete_and_clamp_command();
            break;
        case 'a':
            append_after_command();
            break;
        case 'b':
            prepend_before_command();
            break;
        case 's':
            swap_lines_command();
            break;
        default:
            std::cout << "Not a recognized command " << input << ".\n";
            break;
        }
    }
    return 0;
}

int Editor::print_contents_on_line(int line) const {
    Utils::clear_screen();

    int file_length = m_contents->size();
    int line_diff = Utils::window_height() / 2 - 2;
    int start_line = std::max(0, line - line_diff);
    int end_line = std::max(0, std::min(file_length - 1, line + line_diff));

    int line_number_width = Utils::count_digits(m_contents->size());

    if (start_line != 0) {
        std::cout << "...\n";
    }

    for (int i = start_line; i <= end_line; i++) {
        if (i == line) {
            std::cout << "> ";
        }

        std::cout << std::setw(line_number_width) << i;
        std::cout << " " << m_contents->at(i) << '\n';
    }

    if (end_line != file_length - 1) {
        std::cout << "...\n";
    }

    return 0;
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

    if (line >= (int) m_contents->size()) {
        m_contents->resize(line + 1, "");
    }

    std::cout << "> ";
    std::string input;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::getline(std::cin, input);
    std::cin.clear();
    (*m_contents)[line] = input;

    move_to_line(line);
    return 0;
}

int Editor::move_to_command() {
    std::cout << "Move to which line? ";
    int line;
    std::cin >> line;
    if (std::cin.fail() || line < 0 || line >= (int) m_contents->size()) {
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

    for (int i = 0; i < (int) m_contents->size(); i++) {
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

int Editor::delete_and_clamp_command() {
    std::cout << "Delete and clamp which line? ";
    int line;
    std::cin >> line;
    if (std::cin.fail() || line < 0 || line >= (int) m_contents->size()) {
        std::cout << "Not a valid line number!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return 1;
    }

    return delete_and_clamp(line);
}

int Editor::delete_and_clamp(int line) {
    m_contents->erase(m_contents->begin() + line);
    return 0;
}

int Editor::append_after_command() {
    std::cout << "Append after which line? ";
    int line;
    std::cin >> line;
    if (std::cin.fail() || line < 0 || line >= (int) m_contents->size()) {
        std::cout << "Not a valid line number!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return 1;
    }

    return append_after_line(line);
}

int Editor::append_after_line(int line) {
    m_contents->insert(m_contents->begin() + line + 1, "");
    return edit_line(line + 1);
}

int Editor::prepend_before_command() {
    std::cout << "Prepend before which line? ";
    int line;
    std::cin >> line;
    if (std::cin.fail() || line < 0 || line >= (int) m_contents->size()) {
        std::cout << "Not a valid line number!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return 1;
    }

    return prepend_before_line(line);
}

int Editor::prepend_before_line(int line) {
    m_contents->insert(m_contents->begin() + line, "");
    return edit_line(line);
}

int Editor::swap_lines_command() {

    std::cout << "First line to swap? ";
    int first;
    std::cin >> first;
    if (std::cin.fail() || first < 0 || first >= (int) m_contents->size()) {
        std::cout << "Not a valid line number!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return 1;
    }

    std::cout << "Second line to swap? ";
    int second;
    std::cin >> second;
    if (std::cin.fail() || second < 0 || second >= (int) m_contents->size()) {
        std::cout << "Not a valid line number!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        return 1;
    }

    return swap_lines(first, second);
}

int Editor::swap_lines(int first, int second) {
    std::string first_str = m_contents->at(first);
    std::string second_str = m_contents->at(second);

    (*m_contents)[first] = second_str;
    (*m_contents)[second] = first_str;

    move_to_line(first);
    return 0;
}
