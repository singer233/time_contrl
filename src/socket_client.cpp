#include <sys/socket.h>
#include <iostream>
#include <sys/un.h>
int main(int argc, char const *argv[])
{
    char buffer[] = "1,0,0:0:0,0";
    const char path[]="/tmp/socket";
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path,path,sizeof(path));
    int socket_fd = socket(AF_UNIX,SOCK_STREAM,0);
    std::cout << "here"<<std::endl;
    if(connect(socket_fd,( struct sockaddr *)&address,sizeof(address))==-1) std::cout<<"error";
    send(socket_fd,buffer,sizeof(buffer),0);
    return 0;
}
