#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <errno.h>


#ifndef BACKLOGS
#define BACKLOGS 1
#endif
#include "error_loger.hh"
int init_server_socket(const char path[],int sizeof_path)
{
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,path,sizeof_path);
    int socket_fd =socket(AF_UNIX,SOCK_STREAM,0);
    if(socket_fd == -1) error_handle("can't create socket");
    if(bind(socket_fd,(const sockaddr*)&addr,sizeof(addr))==-1) error_handle("can't bind socket");
    if(listen(socket_fd,1)==-1) error_handle("can not listen");
    return socket_fd;
}
