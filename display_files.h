#pragma once
#include "headers.h"
#include "function_declarations.h"

// Displays details of files in current directory
void displayFiles() {
    struct stat file_info;
    clear();
    float gb = 1 << 30;
    float mb = 1 << 20;
    float kb = 1 << 10;

    for(int i=start_index; i<=end_index; i++) {
        char path[1024];
        string filename = files[i];
        strcpy(path, filename.c_str());
        if(filename != "." && filename != "..") {
            strcpy(path, cur_dir);
            strcat(path, "/");
            strcat(path, filename.c_str());
        }
        stat(path, &file_info);
        cout << "  ";
        cout << ((file_info.st_mode & S_IFDIR) ? "d" : "-");
        cout << ((file_info.st_mode & S_IRUSR) ? "r" : "-");
        cout << ((file_info.st_mode & S_IWUSR) ? "w" : "-");
        cout << ((file_info.st_mode & S_IXUSR) ? "x" : "-");
        cout << ((file_info.st_mode & S_IRGRP) ? "r" : "-");
        cout << ((file_info.st_mode & S_IWGRP) ? "w" : "-");
        cout << ((file_info.st_mode & S_IXGRP) ? "x" : "-");
        cout << ((file_info.st_mode & S_IROTH) ? "r" : "-");
        cout << ((file_info.st_mode & S_IWOTH) ? "w" : "-");
        cout << ((file_info.st_mode & S_IXOTH) ? "x" : "-");

        struct passwd *usr = getpwuid(file_info.st_uid);
        struct group *grp = getgrgid(file_info.st_gid);

        cout << "\t" << usr->pw_name << "\t" << grp->gr_name;

        float size = file_info.st_size;
        string unit = "B";
        if(size > gb) {
            size /= gb;
            unit = "G";
        } else if(size > mb) {
            size /= mb;
            unit = "M";
        } else if(size > kb) {
            size /= kb;
            unit = "K";
        }
        printf("\t%6.2f%s", size, unit.c_str());

        string time = ctime(&file_info.st_mtime);
        cout << "\t\t" << time.substr(0, time.length()-1);

        cout << "\t" << filename << "\n";
    }
    statusBar();
}
