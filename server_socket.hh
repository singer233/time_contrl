#pragma once
class ssl_socket
{
private:
    int socket_fd;
    std::string path;
public:
    ssl_socket(const char path[],int sizeof_path);
    ~ssl_socket();
    int set_listen(int n);
    int Server_establish_connection(void (*func)(std::string),std::mutex lock);
};
