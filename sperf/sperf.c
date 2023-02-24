#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
extern char **environ;

int main(int argc, char *argv[]) {
    if(argc != 2){
    printf("Usage: %s <String>\n",argv[0]);
    exit(EXIT_FAILURE);
  }
  //parse args
  int exec_argc = 4;
  pid_t pid;
  char *exec_argv[] = {"strace","-c","-U","time,syscall",};
  char *exec_envp[] = {
    "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
    NULL,
    };
  int env_num = 0;
  //receive and parse args
  for (;exec_argc - 3 < argc; exec_argc++)  { exec_argv[exec_argc] = argv[exec_argc-3];}
  exec_argv[exec_argc++] = NULL;
  
  if((pid = fork()) == 0){
    execve("/bin/strace",exec_argv,exec_envp);
    //printf("%d\n",pid);
  }
  else{
    //printf("%d\n",getpid());
  }



  //execve("strace",          exec_argv, exec_envp);
  //execve("/bin/strace",     exec_argv, exec_envp);
  //execve("/usr/bin/strace", exec_argv, exec_envp);
  //printf("%s\n",exec_argv[0]);
  //perror(argv[0]);
  exit(EXIT_FAILURE);
}
