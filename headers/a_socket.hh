int init_server_socket(const char path[],int sizeof_path);
void server_wait_connection(int socket_fd,int (*callback)(char* Msg,int sizeof_Msg));
extern bool Continue;