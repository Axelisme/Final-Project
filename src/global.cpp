#include "global.h"
#include <iostream>
#include <string>

void raise_err(const std::string &msg){
    if (Debug) std::cerr << "error: " << msg << std::endl;
}

void raise_warn(const std::string &msg){
    if (Debug) std::cerr << "warning: " << msg << std::endl;
}

void show_msg(const std::string &msg){
    std::cout << "Messenger: " << msg << std::endl;
}