#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define PORT 8000

int main(int argc, char const *argv[]) {
    int socket_fd;
    int inet_res, connect_res, fork_res;
    struct sockaddr_in server_addr;


    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_fd <= 0){
        printf("Socket couldn't be created\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    inet_res = inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if(inet_res <= 0){
        printf("Invalid address. Terminated\n");
        return -1;
    }

    printf("Attempting to connect\n");
    connect_res = connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if(connect_res < 0){
        printf("Connection Failed. Terminated\n");
        return -1;
    }

    printf("Connection established\n");

    char buff1[1024];// = {0};
    char buff2[1024];// = {0};

    for(;;){
        memset(buff1, 0, sizeof(buff1));
        scanf("%[^\n]%*c", buff1);
        send(socket_fd, buff1, strlen(buff1), 0);

        memset(buff2, 0, sizeof(buff2));
        while(read(socket_fd, buff2, 1024) == 0){

        }
        printf("Server says: %s\n", buff2);

    }









    return 0;
}
