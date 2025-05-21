#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void printError(const char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}
void getIPAddressString(struct sockaddr_in* addr,char* ipStr,int len){
    inet_ntop(AF_INET,&(addr -> sin_addr),ipStr,len);
}