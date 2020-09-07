#include <iostream>
#include <string>
void error_handle(std::string msg)
{
    std::cout << msg <<std::endl;
    exit(-1);
}