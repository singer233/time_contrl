#include <iostream>
#include <syslog.h>
#include <unistd.h>
#include <cstdlib>
#include <thread>
#include <mutex>


#include "deamonize.hh"
#include "server_socket.hh"
void callback_change_setting(std::string);
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
    std::mutex wiksmz;
// initlizing socket for communicate with client
    ssl_socket sk = ssl_socket(socket_path,sizeof(socket_path));
    sk.set_listen(1);
    std::cout << "hello deamon";
    sk.Server_establish_connection(callback_change_setting,wiksmz);

//clean and exit()

    return 0;
}
void callback_change_setting(std::string)
{

}

