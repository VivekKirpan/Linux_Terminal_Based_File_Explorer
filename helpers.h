#pragma once
#include "headers.h"
#include "function_declarations.h"

// Clears the terminal screen
void clear() {
    cursor_pos = 0;
    cout << "\x1b[H\x1b[J";
}

// Error Handling Function
void error(const char *ch) {
    clear();
    perror(ch);
    exit(1);
}

// Disables non-canonical terminal mode
void disableNonCanonicalMode() {
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin_termios) == -1) error("Error from tcsetattr()");
}

// Enables non-canonical terminal mode
void enableNonCanonicalMode() {
    if(tcgetattr(STDIN_FILENO, &origin_termios) == -1) error("Error from tcgetattr()");
    struct termios new_termios = origin_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios) == -1) error("Error from tcsetattr()");
    atexit(disableNonCanonicalMode);
}

// Prints Status Bar
void statusBar(string status) {
    cout << "\x1b[" << term_props.ws_row-2 << ";1H";
    cout << "\x1b[J";
    if(isCommandMode) {
        cout << "***Command Mode***\tPress 'esc' to enter Normal Mode\t\tType 'quit' to exit\n";
        if(!status.empty()) cout << "Status: " << status;
        cout << "\nEnter Command: ";
    } else {
        cout << "***Normal Mode***\tPress ':' to enter Command Mode\t\tPress 'q' to exit\n";
        cout << "Current Directory: " << cur_dir;
        cout << "\x1b[H";
    }
}

string getAbsolutePath(string raw_path) {
    if(raw_path[0] == '/') {
        return raw_path;
    }
    string abs_path;
    if(raw_path[0] == '~') {
        abs_path = string(home_dir) + raw_path.substr(1);
    } else if(raw_path == ".") {
        abs_path = string(cur_dir);
    } else if(raw_path == "..") {
        abs_path = string(cur_dir);
        int index = abs_path.find_last_of('/');
        if(index == 0) {
            abs_path = "/";
        } else {
            abs_path = abs_path.substr(0, index);
        }
    } else if(raw_path[0] == '.' && raw_path[1] == '/') {
        abs_path = string(cur_dir) + raw_path.substr(1);
    } else {
        abs_path = string(cur_dir) + "/" + raw_path;
    }
    return abs_path;
}

// Handles the text rendering when terminal is resized
void win_handler(int sig) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &term_props);
    start_index = 0;
    end_index = min(term_props.ws_row-5, (int)files.size())-1;
    displayFiles();
}
