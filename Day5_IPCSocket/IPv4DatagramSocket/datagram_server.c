#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

#define BUF_SIZE 10
#define PORT_NUM 8080

int main(int argc, char *argv[]){
    struct sockaddr_in ser_addr, client_addr;
    int fd,j;
    ssize_t numBytes;
    socklen_t len;
    char buf[BUF_SIZE];
    char clientStr[INET_ADDRSTRLEN];

    fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd == -1){
        return 1;
    }
    memset(&ser_addr,0,sizeof(struct sockaddr_in));

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = INADDR_ANY;
    ser_addr.sin_port = htons(PORT_NUM);

    if(bind(fd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr_in)) == -1)
        return 1;
    
    printf("start listening on server\n");

    for(;;)  // vong lap vo han
    {
        len = sizeof(struct sockaddr_in);
        numBytes = recvfrom(fd, buf, BUF_SIZE,0,(struct sockaddr *)&client_addr,&len);
        if(numBytes == -1){
            return 1;
        }
        buf[numBytes] = '\0'; // thêm ký tự NULL để đảm bảo chuỗi in ra đúng
        printf("Message from client: %s\n", buf);


        if(inet_ntop(AF_INET, &client_addr.sin_addr,clientStr,INET_ADDRSTRLEN) == NULL)
            printf("Couldnt convert client address to string\n");
        

        else
            printf("server received %ld bytes from (%s, %u)\n", (long) numBytes, clientStr, ntohs(client_addr.sin_port));
            
            for(j = 0;j<numBytes;j++)
                buf[j] = toupper((unsigned char )buf[j]);
            
                if(sendto(fd,buf,numBytes,0,(struct sockaddr *) &client_addr, len ) != numBytes)
                printf("sendto error\n");
    }

    
}