#include <iostream>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <string>
#include <mutex>
#include <errno.h>
#include <unistd.h>
#include <thread>
#include "headers/config.hh"

#include "headers/error_loger.hh"
bool Continue = true;

int init_socket()
{
    int socket_fd =socket(AF_UNIX,SOCK_STREAM,0);
    if(socket_fd == -1) error_handle("can't create socket");
    return socket_fd;
}
int init_server_socket(const char path[],int sizeof_path)
{
    int socket_fd = init_socket();
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,path,sizeof_path);
#ifndef DEBUG
    fchown(socket_fd,0,0);
#endif
    fchmod(socket_fd,S_IRUSR|S_IWUSR|S_IXUSR);
    if(bind(socket_fd,(const sockaddr*)&addr,sizeof(addr))==-1) error_handle("can't bind socket");
    if(listen(socket_fd,1)==-1) error_handle("can not listen");
    return socket_fd;
}
int client_commucation(const char path[],int sizeof_path, const char Msg[], int sizeof_Msg)
{
    int socket_fd = init_socket();
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,path,sizeof_path);
    connect(socket_fd,(const sockaddr*)&addr,sizeof(addr));
    send(socket_fd,Msg,sizeof_Msg,0);
    close(socket_fd);
    return 0;
}
void server_wait_connection(int socket_fd,int (*callback)(char* Msg,int sizeof_Msg))
{
    while (Continue)
    {
        char buffer[1000]= {0};
        int AcceptSocket_fd = accept(socket_fd,NULL,NULL);
        int Msg_size = recv(AcceptSocket_fd,buffer,sizeof(buffer),0);
        if(Msg_size == -1) send(AcceptSocket_fd,&Msg_size,sizeof(int),0);
        else
        {
            int result =callback(buffer,Msg_size);
            send(AcceptSocket_fd,&result,sizeof(int),0);
        }
        
    }
    return;
}