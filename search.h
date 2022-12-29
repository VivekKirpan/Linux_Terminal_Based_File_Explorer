#pragma once
#include "headers.h"
#include "function_declarations.h"

// Searches file/directory in Home Directory
void search() {
    stack<string> dir_stack;
    dir_stack.push(string(home_dir));
    while(!dir_stack.empty()) {
        string dir = dir_stack.top();
        dir_stack.pop();
        DIR *dir_ptr = opendir(dir.c_str());
        if(dir_ptr == NULL) continue;
        struct dirent *dir_entry;
        struct stat file_info;
        while(dir_entry = readdir(dir_ptr)) {
            string filename(dir_entry->d_name);
            if(filename == "." || filename == "..") continue;
            if(filename == cmd_params[1]) {
                statusBar("True");
                return;
            }
            string file_path;
            if(dir == "/") {
                file_path = dir + filename;
            } else {
                file_path = dir + "/" + filename;
            }
            if(stat(file_path.c_str(), &file_info) == 0 && S_ISDIR(file_info.st_mode)) {
                dir_stack.push(file_path);
            }
        }
        closedir(dir_ptr);
    }
    statusBar("False");
}
