#include "normal_mode.h"
#include "command_mode.h"

struct termios origin_termios;
struct winsize term_props;
char cur_dir[1024];
const char *home_dir;
vector<string> files;
vector<string> cmd_params;
stack<string> backStack, forwardStack;
int cursor_pos = 0, start_index = 0, end_index;
bool isCommandMode = false;


int main() {
    char ch;
    clear();
    enableNonCanonicalMode();
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &term_props);
    end_index = term_props.ws_row-5;
    signal(SIGWINCH, win_handler);
    home_dir = getenv("HOME");
    if(home_dir == NULL) {
        home_dir = getpwuid(getuid())->pw_dir;
    }
    strcpy(cur_dir, home_dir);
    getDirectory();
    while(1) {
        ch = cin.get();
        if(ch == EOF) error("Error from read()");
        if(ch == 'q') break;
        if(ch == 27) {
            char ch2, ch3;
            ch2 = cin.get();
            ch3 = cin.get();
            if(ch2 == '[') {
                if(ch3 == 'A') {
                    cursorUp();
                } else if(ch3 == 'B') {
                    cursorDown();
                } else if(ch3 == 'C') {
                    goForward();
                } else if(ch3 == 'D') {
                    goBack();
                }
            }

        } else if(ch == 10) {
            enterKey();
        } else if(ch == 127) {
            goUp();
        } else if(ch == 'h') {
            strcpy(cur_dir, home_dir);
            getDirectory();
        } else if(ch == ':') {
            if(!commandMode()) break;
            isCommandMode = false;
            getDirectory();
        }
    };
    clear();
    return 0;
}