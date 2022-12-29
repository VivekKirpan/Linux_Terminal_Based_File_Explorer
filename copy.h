#pragma once
#include "headers.h"
#include "function_declarations.h"

// Copy File
bool copyFile(string src_file, string dst_file) {
    int buf_sz = 8192;
    char buffer[buf_sz];
    int src_fd, dst_fd, sz;
    struct stat file_info;
    bool success = true;

    src_fd = open(src_file.c_str(), O_RDONLY);
    stat(src_file.c_str(), &file_info);
    dst_fd = creat(dst_file.c_str(), file_info.st_mode);

    while(1) {
        sz = read(src_fd, buffer, buf_sz);
        if(sz <= 0) break;
        write(dst_fd, buffer, sz);
    }

    if(sz == -1) {
        success = false;
        statusBar("Failed to copy file!!");
    }
    close(src_fd);
    close(dst_fd);
    return success;
}

// Copy Directory
bool copyDirectory(string src_path, string dst_path) {
    mkdir(dst_path.c_str(), 0777);
    DIR *dir = opendir(src_path.c_str());
    struct dirent *dir_entry;
    struct stat file_info;
    bool success = true;

    while(dir_entry = readdir(dir)) {
        if((strcmp(dir_entry->d_name, ".") == 0) ||
        (strcmp(dir_entry->d_name, "..") == 0)) {
            continue;
        }
        string path1 = src_path + "/" + string(dir_entry->d_name);
        string path2 = dst_path + "/" + string(dir_entry->d_name);
        stat(path1.c_str(), &file_info);
        if(S_ISDIR(file_info.st_mode)) {
            success = copyDirectory(path1, path2);
        } else {
            success = copyFile(path1, path2);
        }
        if(!success) {
            statusBar("Failed to copy directory!!");
            break;
        }
    }
    closedir(dir);
    return success;
}

// Copy driver function for file/directory
bool copy(string name, string dst_path) {
    struct stat file_info;
    bool success = true;
    if(stat(dst_path.c_str(), &file_info) == 0 && S_ISDIR(file_info.st_mode)) {
        string src_path = string(cur_dir) + "/" + name;
        dst_path = dst_path + "/" + name;
        if(stat(src_path.c_str(), &file_info) == 0) {
            if(S_ISDIR(file_info.st_mode)) {
                success = copyDirectory(src_path, dst_path);
            } else {
                success = copyFile(src_path, dst_path);
            }
            if(success) {
                statusBar("Copy Successful!!");
            } else {
                statusBar("Failed to copy File/Directory!!");
            }
        } else {
            statusBar("File/Directory doesn't exist!!");
            success = false;
        }
    } else {
        statusBar("Invalid Directory Path!!");
        success = false;
    }
    return success;
}
