#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(){
   pid_t chilPid = fork(); 
   
   if(chilPid == -1) {
      printf("Failed to creat child process\n");
      return 1;
   }

   else if(chilPid == 0) {
      printf("Child Process PID: %d\n",getpid()); 
      return 0;
   }

   else {
      printf("Parent Process PID: %d\n",getpid());
      return 0;
   }

   return 0;
}


