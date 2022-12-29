#pragma once
#include "function_declarations.h"

// Create File
void createFile() {
    struct stat file_info;
    int sz;
    string dst_path = getAbsolutePath(cmd_params[2]);
    if(stat(dst_path.c_str(), &file_info) == 0 && S_ISDIR(file_info.st_mode)) {
        string path = dst_path + "/" + cmd_params[1];
        sz = creat(path.c_str(), 0664);
        if(sz == -1) {
            statusBar("Failed to create File!!");
        } else {
            close(sz);
            if(dst_path == string(cur_dir)) getDirectory();
            statusBar("File Created Successfully!!");
        }
    } else {
        statusBar("Invalid Directory Path!!");
    }
}

// Create Directory
void createDir() {
    struct stat file_info;
    string dir_path = getAbsolutePath(cmd_params[2]);
    if(stat(dir_path.c_str(), &file_info) == 0 && S_ISDIR(file_info.st_mode)) {
        string path = dir_path + "/" + cmd_params[1];
        if(mkdir(path.c_str(), 0777) == -1) {
            statusBar("Failed to create Directory!!");
        } else {
            if(dir_path == string(cur_dir)) getDirectory();
            statusBar("Directory Created Successfully!!");
        }
    } else {
        statusBar("Invalid Directory Path!!");
    }
}
