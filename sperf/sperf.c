#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SIZE 4096
extern char **environ;


int main(int argc, char *argv[]) {
  //parse args
  int exec_argc = 4;
  pid_t pid;
  char *exec_argv[] = {"strace","-c","-U","time,syscall",};
  char *exec_envp[] = {
    "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
    NULL,
    };
  int env_num = 0;
  int pipefd[2];

  if(argc != 2){
    printf("Usage: %s <String>\n",argv[0]);
    exit(EXIT_FAILURE);
  }
  //receive and parse args
  for (;exec_argc - 3 < argc; exec_argc++)  { exec_argv[exec_argc] = argv[exec_argc-3];}
  exec_argv[exec_argc++] = NULL;

  //error handlering  
  if(pipe(pipefd) != 0){
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  //begin create new process
  pid = fork();
  if(pid == 0){
    //pipe control
    close(1);
    dup(pipefd[1]);
    execve("/bin/strace",exec_argv,exec_envp);
    //printf("%d\n",pid);
    close(0);
    close(pipefd[1]);
  }
  else if (pid ==-1)  { perror("fork");exit(EXIT_FAILURE);}

  else {
    close(0);
    dup(pipefd[0]);
    printf("this is me !!!!!\n");
    wait(NULL);
    printf("this is me too !!!!!\n");

    close(pipefd[0]);
    close(pipefd[1]);
  }




  //execve("strace",          exec_argv, exec_envp);
  //execve("/bin/strace",     exec_argv, exec_envp);
  //execve("/usr/bin/strace", exec_argv, exec_envp);
  //printf("%s\n",exec_argv[0]);
  //perror(argv[0]);
  exit(EXIT_FAILURE);
}
