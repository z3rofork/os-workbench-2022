#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[]) {
  //parse args
  char *exec_argv[] = {};
  char **exec_envp = environ;
  int env_num = 0;

  exec_argv[0] = "/usr/bin/strace";
  exec_argv[1] = "-c -U time,syscall";
  for (int i = 2; i < argc; i++)  { exec_argv[i] = argv[i]; }
  exec_argv[argc+1] = NULL;
  for(env_num;exec_envp[env_num] != 0;env_num++)  {}
  exec_envp[env_num+1] = NULL;

  if(fork() == 0){
    execve("/bin/strace",exec_argv,exec_envp);
  }

  //parse args


  //execve("strace",          exec_argv, exec_envp);
  //execve("/bin/strace",     exec_argv, exec_envp);
  //execve("/usr/bin/strace", exec_argv, exec_envp);
  printf("%s\n",exec_argv[0]);
  perror(argv[0]);
  exit(EXIT_FAILURE);
}
