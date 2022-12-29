#pragma once
#include "normal_mode.h"
#include "create.h"
#include "copy.h"
#include "delete.h"
#include "search.h"

using namespace std;

// Splits the command string into words
void parseCommand(string &command) {
    cmd_params.clear();
    string word;
    for(char ch: command) {
        if(ch == ' ') {
            cmd_params.push_back(word);
            word.clear();
        } else {
            word.push_back(ch);
        }
    }
    cmd_params.push_back(word);
}

// Renames the file
void renameCommand() {
    string old_file_path = string(cur_dir) + "/" + cmd_params[1];
    string new_file_path = string(cur_dir) + "/" + cmd_params[2];
    if(rename(old_file_path.c_str(), new_file_path.c_str()) == -1) {
        statusBar("File does not exits!!");
    } else {
        getDirectory();
        statusBar("Rename Successful!!");
    }
}

// Change the current directory to the specified directory
void goTo() {
    struct stat file_info;
    string dir_path = getAbsolutePath(cmd_params[1]);
    if(stat(dir_path.c_str(), &file_info) == 0 && S_ISDIR(file_info.st_mode)) {
        backStack.push(string(cur_dir));
        while(!forwardStack.empty()) forwardStack.pop();
        strcpy(cur_dir, dir_path.c_str());
        getDirectory();
        statusBar("Directory Changed to " + dir_path);
    } else {
        statusBar("Invalid Path!!");
    }
}

// Moves File/Directory
bool move(string name, string dst_path) {
    struct stat file_info;
    bool success = copy(name, dst_path);
    if(!success) {
        return success;
    }
    string src_path = string(cur_dir) + "/" + name;
    if(stat(src_path.c_str(), &file_info) == 0 && S_ISDIR(file_info.st_mode)) {
        success = deleteDirectory(src_path);
    } else {
        success = deleteFile(src_path);
    }
    if(success) {
        statusBar("Successfully moved files/directory!!");
    } else {
        statusBar("Failed to move File/Directory!!");
    }
    return success;
}

// Enters Command Mode
bool commandMode() {
    isCommandMode = true;
    statusBar();
    char ch;
    string command;
    while(1) {
        command.clear();
        while(1) {
            ch = cin.get();
            if(ch == 27 || ch == 10) break;
            if(ch == 127) {
                if(!command.empty()) {
                    command.pop_back();
                    cout << "\b \b";
                }
            } else {
                cout << ch;
                command.push_back(ch);
            }
        }
        if(ch == 27) break;
        if(ch == 10) {
            parseCommand(command);
            if(cmd_params[0] == "quit") return false;
            if(cmd_params[0] == "rename") {
                renameCommand();
            } else if(cmd_params[0] == "goto") {
                goTo();
            } else if(cmd_params[0] == "create_file") {
                createFile();
            } else if(cmd_params[0] == "create_dir") {
                createDir();
            } else if(cmd_params[0] == "copy") {
                int n = cmd_params.size();
                string dir_path = getAbsolutePath(cmd_params[n-1]);
                for(int i=1; i<n-1; i++) {
                    if(!copy(cmd_params[i], dir_path)) break;
                }
            } else if(cmd_params[0] == "delete_file") {
                deleteFile(getAbsolutePath(cmd_params[1]));
            } else if(cmd_params[0] == "delete_dir") {
                deleteDirectory(getAbsolutePath(cmd_params[1]));
            } else if(cmd_params[0] == "move") {
                int n = cmd_params.size();
                string dir_path = getAbsolutePath(cmd_params[n-1]);
                for(int i=1; i<n-1; i++) {
                    if(!move(cmd_params[i], dir_path)) break;
                }
            } else if(cmd_params[0] == "search") {
                search();
            } else {
                statusBar("Invalid Command!!");
            }
        }
    }
    return true;
}
