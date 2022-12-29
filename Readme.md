# Linux Terminal Based File Explorer

## Prerequisite
Linux OS with g++ compiler. Compiler can be installed using the command:
```
sudo apt install g++
```

## How to run the program
Open Terminal in the program directory and run the following commands:
```
g++ main.cpp -o main
./main
```

## Introduction
1. The File Explorer has two modes to work with Normal Mode and Command Mode.
2. Normal Mode is the default mode in which the application starts. It is basically UI mode in which keyboard navigations can be used.
3. While Command Mode is command line mode where operations can be performed by using certain commands.
4. The application starts in the root/home directory of the system.
5. The bottom section shows the status bar with the current mode, current directory and some commands.
6. Press ```:``` to switch to Command Mode. Press ```esc``` to switch to Normal Mode.

## Normal mode:
Normal mode is the default mode of the application. It should has the following functionalities -
1. Displays a list of directories and files in the current folder
* Every file in the directory should is displayed on a new line with the following
attributes for each file -
    * File Name
    * File Size
    * Ownership (user and group) and Permissions
    * Last modified
* The file explorer shows entries “.” and “..” for current and parent directory
respectively.
* User can navigate up and down in the file list using the corresponding up
and down arrow keys. The up and down arrow keys can also be used in scrolling.

2. Opens the directory/file pointed by cursor when Enter key is pressed.

3. Traversal
* Go back - Left arrow key takes the user to the previously visited directory
* Go forward - Right arrow key takes the user to the next directory
* Up one level - Backspace key take the user up one level to parent directory
* Home - h key takes the user to the home folder


## Command Mode:

The application enters the Command button whenever “:” (colon) key is pressed. In the command
mode, the user is able to enter different commands. All commands appear in the status bar at the
bottom.
1. Copy –
```
$ copy <source_file(s)> <destination_directory>
```

2. Move –
```
$ move <source_file(s)> <destination_directory>
```

3. Rename –
```
$ rename <old_filename> <new_filename>
``` 

* Eg –
```
$ copy foo.txt bar.txt baz.mp4 ~/foobar
$ move foo.txt bar.txt baz.mp4 ~/foobar
$ rename foo.txt bar.txt
```

4. Create File –
```
$ create_file <file_name> <destination_path>
```

5. Create Directory –
```
$ create_dir <dir_name> <destination_path>
```

* Eg – 
```
$ create_file foo.txt ~/foobar create_file foo.txt
$ create_dir foo ~/foobar
```

6. Delete File –
```
$ delete_file <file_path>
```

7. Delete Directory –
```
$ delete_dir <dir_path>
```

8. Goto –
```
$ goto <directory_path>
```

9. Search –
```
$ search <file_name>/<directory_name>
```

* Searchs for a given file or folder in the home directory recursively.

* Output is True or False depending on whether the file or folder exists.

10. On pressing ```q``` key in normal mode, the application is closed. Similarly, entering the ```quit``` command in command mode closes the application.