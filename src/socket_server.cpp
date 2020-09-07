#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>


#define BACKLOG 1


int main(int argc, char const *argv[])
{
    char buffer[1024]={0};
    char massage[]="hello socket";
    const char path[]="./socket";
    int sock_fd;
    sock_fd = socket(AF_UNIX,SOCK_STREAM,0);
    //start bind socket
    struct sockaddr_un address;
    address.sun_family =AF_UNIX;
    strncpy(address.sun_path,path,sizeof(path));
    if(remove(path) && errno != ENOENT) std::cout<< "can't delete socket" << std::endl;
    if(bind(sock_fd,(struct sockaddr *)&address,sizeof(address)) == -1) exit(9);
    //start listen
    if(listen(sock_fd,BACKLOG) == -1) exit(-1);
    //accept 
    int accept_fd = accept(sock_fd,NULL,NULL);
    if(accept_fd == -1) exit(10);
    //dealing with client
  // int recived = recv(accept_fd,buffer,sizeof(buffer),0);
  //  if(recived == -1) exit(11);
  //  if(recived == 0) exit(12);
  //  if(recived > 0) 
  send(accept_fd,massage,sizeof(massage),0);
    return 0;


}
    
