#ifndef EDITOR_H
#define EDITOR_H
#include <string>
#include <iostream>
#include <vector>

class Editor {
    public:
        Editor(std::vector<std::string>* contents, const std::string& filename);
        int run_editor();
    private:
        std::vector<std::string>* m_contents;
        std::string m_filename;
        int m_current_line;
        bool m_stopped;

        int print_contents_on_line(int line) const;
        int edit_command();
        int move_to_command();
        int write_command();
        int quit_command();
        int delete_and_clamp_command();
        int append_after_command();
        int prepend_before_command();
        int swap_lines_command();

        int edit_line(int line);
        int move_to_line(int line);
        int write();
        int delete_and_clamp(int line);
        int append_after_line(int line);
        int prepend_before_line(int line);
        int swap_lines(int first, int second);
};

#endif
