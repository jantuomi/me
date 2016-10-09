#ifndef EDITOR_H
#define EDITOR_H
#include <string>
#include <iostream>

class Editor {
    public:
        Editor(std::string* contents);
        int run_editor();
    private:
        std::string* m_contents;
};

#endif
