#ifndef UTILS_H
#define UTILS_H

#include <netinet/in.h>  

void printError(const char* msg);
void getIPAddressString(struct sockaddr_in* addr, char* ipStr, int len);

#endif
