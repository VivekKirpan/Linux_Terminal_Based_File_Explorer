#pragma once
#include "headers.h"

void clear();
void error(const char *ch);
void disableNonCanonicalMode();
void enableNonCanonicalMode();
void statusBar(string status="");
string getAbsolutePath(string raw_path);
void displayFiles();
void win_handler(int sig);
void cursorUp();
void cursorDown();
void getDirectory();
void goBack();
void goForward();
void goUp();
void enterKey();
void parseCommand(string &command);
void renameCommand();
void goTo();
void createFile();
void createDir();
bool copyFile(string src_file, string dst_file);
bool copyDirectory(string src_path, string dst_path);
bool copy(string name, string dst_path);
bool deleteFile(string file_path);
bool deleteDirectory(string dir_path);
bool move(string name, string dst_path);
void search();
bool commandMode();
