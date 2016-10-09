#include "editor.h"
#include "utils.h"

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
    }
    return 0;
}

int Editor::print_contents_on_line(int line) const {
    for (int i = line; i < m_contents->size(); i++) {
        std::cout << i << " " << m_contents->at(i) << '\n';
    }
}
