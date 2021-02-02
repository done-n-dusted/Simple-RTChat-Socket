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
    int inet_res, sockopt_res, bind_res;
    int listen_res;
    int socket2;

    int opt = 1;

    struct sockaddr_in addr;
    int addr_len = sizeof(addr);


    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_fd <= 0){
        printf("Socket couldn't be created\n");
        return -1;
    }

    sockopt_res = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind_res = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));

    if(bind_res < 0){
        printf("Binding wasn't possible\n");
        return -1;
    }

    listen_res = listen(socket_fd, 3);

    if(listen_res < 0){
        printf("Listen failed\n");
        return -1;
    }

    socket2 = accept(socket_fd, (struct sockaddr *) &addr, (socklen_t *) &addr_len);

    if(socket2 < 0){
        printf("Acceptance failure\n");
        // return -1;

    }

    char buff1[1024];// = {0};
    char buff2[1024];// = {0};

    for(;;){
        memset(buff2, 0, sizeof(buff2));
        while(read(socket2, buff2, 1024)==0){

        }
        printf("Client says: %s\n", buff2);

        memset(buff1, 0, sizeof(buff1));
        scanf("%[^\n]%*c", buff1);
        send(socket2, buff1, strlen(buff1), 0);
    }


    return 0;
}
