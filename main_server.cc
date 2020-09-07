#include <iostream>
#include <syslog.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>


#include "deamonize.hh"
#include "server_socket.hh"

int main(int argc, char const *argv[])
{
    const char socket_path[] ="/tmp/socket";
    uid_t user_uid = getuid();
#ifndef DEBUG
    if(user_uid != 0)
    {
        std::cout << "only run on root" << std::endl;
        return -1;
    }
#else
    std::cout << "run on debug mode"<<std::endl;
#endif
// initlizing socket for communicate with client
    int socket_fd = init_server_socket(socket_path,sizeof(socket_path));
    std::cout << "hello deamon";
    remove("/tmp/socket");
    return 0;
}
