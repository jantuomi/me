#ifndef EDITOR_H
#define EDITOR_H
#include <string>
#include <iostream>
#include <vector>

class Editor {
    public:
        Editor(std::vector<std::string>* contents);
        int run_editor();
    private:
        std::vector<std::string>* m_contents;
        int m_current_line;

        int print_contents_on_line(int line) const;
};

#endif
