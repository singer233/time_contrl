#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <errno.h>
#include <unistd.h>
#include <mutex>
#include <thread>
#include "error_loger.hh"
#include "server_socket.hh"
int real_connection(int socket_fd,void (*func)(std::string),std::mutex lock);
ssl_socket::ssl_socket(const char path[],int sizeof_path)
{
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,path,sizeof_path);
    int socket_fd =socket(AF_UNIX,SOCK_STREAM,0);
    if(socket_fd == -1) error_handle("can't create socket");
    if(bind(socket_fd,(const sockaddr*)&addr,sizeof(addr))==-1) error_handle("can't bind socket");
    this->socket_fd = socket_fd;
    this->path = path;
}
int ssl_socket::set_listen(int n)
{
    return listen(this->socket_fd,n);
}
ssl_socket::~ssl_socket()
{
    close(this->socket_fd);
    remove(this->path.c_str());
}
int ssl_socket::Server_establish_connection(void (*func)(std::string),std::mutex lock)
{
    std::thread t1(real_connection,func,lock);
    t1.detach();
}
int real_connection(int socket_fd,void (*func)(std::string),std::mutex lock)
{
    std::cout <<"yep";
    return 0;
}
