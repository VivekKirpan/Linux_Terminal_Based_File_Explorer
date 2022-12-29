#pragma once
#include "headers.h"
#include "function_declarations.h"

// Deletes File
bool deleteFile(string file_path) {
    struct stat file_info;
    if(stat(file_path.c_str(), &file_info) == -1 || S_ISDIR(file_info.st_mode)) {
        statusBar("File does not exists!!");
        return false;
    }
    if(remove(file_path.c_str()) == 0) {
        statusBar("File Deleted Successfully!!");
        return true;
    } else {
        statusBar("Failed to delete file!!");
        return false;
    }
}

// Deletes Directory
bool deleteDirectory(string dir_path) {
    DIR *dir = opendir(dir_path.c_str());
    if(dir == NULL) {
        statusBar("Directory does not exist!!");
        return false;
    }
    struct dirent *dir_entry;
    struct stat file_info;
    bool success = true;

    while(dir_entry = readdir(dir)) {
        if((strcmp(dir_entry->d_name, ".") == 0) ||
        (strcmp(dir_entry->d_name, "..") == 0)) {
            continue;
        }
        string path = dir_path + "/" + string(dir_entry->d_name);
        stat(path.c_str(), &file_info);
        if(S_ISDIR(file_info.st_mode)) {
            success = deleteDirectory(path);
        } else {
            success = deleteFile(path);
        }
        if(!success) {
            closedir(dir);
            statusBar("Failed to Delete Directory!!");
            return success;
        }
    }
    closedir(dir);
    if(rmdir(dir_path.c_str()) == -1) {
        statusBar("Failed to Delete Directory!!");
    } else {
        statusBar("Directory Deleted Successfully!!");
    }
    return success;
}
