#include <iostream>
#include <syslog.h>
#include <unistd.h>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <vector>
#include "headers/config.hh"

#include "headers/deamonize.hh"
#include "headers/a_socket.hh"
std::mutex lock;
int MsgHandler(char* Msg,int sizeof_Msg);
void cleanup(int socket_fd);
int main(void)
{
    const char socket_path[] =SOCKET_PATH;
#ifndef DEBUG
    uid_t user_uid = getuid();
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
    std::thread connection(server_wait_connection,socket_fd,&MsgHandler);
    std::cout << "hello deamon";
    //
    connection.detach();
    std::thread clean_up(cleanup,socket_fd);
    clean_up.join();
}
void cleanup(int socket_fd)
{
    while (Continue)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    close(socket_fd);
    remove(SOCKET_PATH);
}

int MsgHandler(char* Msg,int sizeof_Msg)
{
    std::cout<< Msg << std::endl;
    lock.lock();
    if(!Continue){
        lock.unlock();
        std::cout<<"accept_threader_exited" <<std::endl;
        return 0;
    }
    lock.unlock();
    int Control;
    int hour,minute,second;
    int uid;
    int one_time;
    sscanf(Msg,"%d,%d,%d:%d:%d,%d",&Control,&uid,&hour,&minute,&second,&one_time);
    std::cout<< Msg<<std::endl;
    switch (Control)
    {
    case STOP:
        lock.lock();
        Continue = false;
        lock.unlock();
        return 0;
    case SET: // set time limitation for users
        //TODO:here
        return 0;
    default:
        //TODO: Here.
        return -1;
    }
}
