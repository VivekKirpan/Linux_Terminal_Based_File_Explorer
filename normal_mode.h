#pragma once
#include "headers.h"
#include "display_files.h"
#include "helpers.h"


// Scrolls the cursor up one position
void cursorUp() {
    if(cursor_pos > start_index) {
        cursor_pos--;
        cout << "\x1b[1A";
    } else if(start_index > 0) {
        cursor_pos--;
        start_index--;
        end_index--;
        displayFiles();
        cursor_pos = start_index;
    }
}

// Scrolls the cursor down one position
void cursorDown() {
    if(cursor_pos < end_index) {
        cursor_pos++;
        cout << "\x1b[1B";
    } else if(end_index < files.size()-1) {
        cursor_pos++;
        start_index++;
        end_index++;
        displayFiles();
        cursor_pos = end_index;
        cout << "\x1b[" << end_index-start_index << "B";
    }
}

// Gets the files of the directory
void getDirectory() {
    struct dirent *dir_entry;
    DIR *dir = opendir(cur_dir);
    if(dir == NULL) {
        fprintf(stderr, "Can't open directory: %s\n", cur_dir);
        return;
    }
    files.clear();
    while(dir_entry = readdir(dir)) {
        files.push_back(string(dir_entry->d_name));
    }
    closedir(dir);
    sort(files.begin(), files.end());
    start_index = 0;
    end_index = min(term_props.ws_row-5, (int)files.size())-1;
    displayFiles();
}

// Goes back in the history of navigated directories
void goBack() {
    if(backStack.empty()) return;
    forwardStack.push(string(cur_dir));
    string path = backStack.top();
    backStack.pop();
    strcpy(cur_dir, path.c_str());
    getDirectory();
}

// Goes forward in the history of navigated directories
void goForward() {
    if(forwardStack.empty()) return;
    backStack.push(string(cur_dir));
    string path = forwardStack.top();
    forwardStack.pop();
    strcpy(cur_dir, path.c_str());
    getDirectory();
}

// Goes to the parent directory
void goUp() {
    string dir_str(cur_dir);
    if(dir_str == "/") return;
    backStack.push(dir_str);
    while(!forwardStack.empty()) forwardStack.pop();
    int i=dir_str.size()-1;
    for(; i>=0; i--) {
        if(dir_str[i] == '/') break;
    }
    if(i == 0) {
        dir_str = dir_str.substr(0, 1);
    } else {
        dir_str = dir_str.substr(0, i);
    }
    strcpy(cur_dir, dir_str.c_str());
    getDirectory();
}

// Opens a file or directory
void enterKey() {
    string filename = files[cursor_pos];
    char path[1024];
    strcpy(path, filename.c_str());
    if(filename != "." && filename != "..") {
        strcpy(path, cur_dir);
        if(strlen(cur_dir) > 1) strcat(path, "/");
        strcat(path, filename.c_str());
    }
    struct stat file_info;
    stat(path, &file_info);
    if(filename == ".") return;
    if(filename == "..") {
        goUp();
    } else if(S_ISDIR(file_info.st_mode)) {
        backStack.push(string(cur_dir));
        while(!forwardStack.empty()) forwardStack.pop();
        strcpy(cur_dir, path);
        getDirectory();
    } else {
        pid_t pid = fork();
        if(pid == 0) {
            execl("/usr/bin/xdg-open", "xdg-open", path, (char *)NULL);
            error("Failed to open file");
        }
    }
}
