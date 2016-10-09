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
        const static int OUTPUT_LINE_MAX = 10;

        std::vector<std::string>* m_contents;
        int m_current_line;

        int print_contents_on_line(int line) const;
        int edit_command();
        int move_to_command();

        int edit_line(int line);
        int move_to_line(int line);
};

#endif
