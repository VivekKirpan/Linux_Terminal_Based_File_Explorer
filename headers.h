#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stack>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

using namespace std;

//Global Variables
extern struct termios origin_termios;
extern struct winsize term_props;
extern char cur_dir[1024];
extern const char *home_dir;
extern vector<string> files;
extern vector<string> cmd_params;
extern stack<string> backStack, forwardStack;
extern int cursor_pos, start_index, end_index;
extern bool isCommandMode;
