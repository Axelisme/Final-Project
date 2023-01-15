#include "global.h"
#include <iostream>
#include <string>

// work dir path
std::string WORKDIR;

void work_dir_init() {
    //WORKDIR = "";
    char temp[1024];
    int n = readlink("/proc/self/exe", temp, 1024);
    temp[n] = '\0';
    WORKDIR = temp;
    WORKDIR = WORKDIR.substr(0,WORKDIR.find("/bin"));
    show_msg(WORKDIR);
}

void raise_err(const std::string &msg){
    if (Debug) std::cerr << "error: " << msg << std::endl;
}

void raise_warn(const std::string &msg){
    if (Debug) std::cerr << "warning: " << msg << std::endl;
}

void show_msg(const std::string &msg){
    std::cout << "Messenger: " << msg << std::endl;
}