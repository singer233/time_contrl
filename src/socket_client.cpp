#include <sys/socket.h>
#include <iostream>
#include <sys/un.h>
int main(int argc, char const *argv[])
{
    char buffer[1024] = {0};
    int socket_fd = socket(AF_UNIX,SOCK_STREAM,0);
    const char path[]="./socket";
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path,path,sizeof(path));
    connect(socket_fd,( struct sockaddr *)&address,sizeof(address));
    recv(socket_fd,buffer,sizeof(buffer),0);
    std::cout << buffer;
    return 0;
}
