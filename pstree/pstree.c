#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//#define _POSIX_SOURCE
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
//#undef _POSIX_SOURCE


#define BUF_SIZE 1024


// record rhe process name , pid and parent's pid
struct t_process
{
    /* data */
    char name[50];
    pid_t pid;   
    pid_t ppid;
} t_process, *pt_process;

// declare function
void usage(const char *filename);
void pstree_version();
void list_process();
void getInfoByPid(pid_t, struct t_process *);



int main(int argc, char *argv[]) {
  // for (int i = 0; i < argc; i++) {
  //   assert(argv[i]);
  //   printf("argv[%d] = %s\n", i, argv[i]);
  // }
  // assert(!argv[argc]);
  int opt;
  const char *optString="p::n::V::h::";
  while ((opt = getopt(argc,argv,optString)) != -1)
  {
    /* code */
    switch (opt)
    {
    case 'p':
      /* code */
      break;
    case 'n':
      break;
    case 'V':
      pstree_version();
      break;
    case 'h':
      usage(argv[0]);
    default:      
      //usage(argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  list_process();
  // if(optind >= argc){
  //   fprintf(stderr,"Expected argument after options\n");
  //   usage(argv[0]);
  //   exit(EXIT_FAILURE);
  // }

  exit(EXIT_SUCCESS);
  return 0;
}


void usage(const char *filename){
  fprintf(stderr,"Usage: %s [-p, -n, -V]\n",filename);
  printf("把系统中的进程按照父亲-孩子的树状结构打印到终端。\n");
  printf("-p \t--show-pids: 打印每个进程的进程号。\n");
  printf("-n \t--numeric-sort: 按照pid的数值从小到大顺序输出一个进程的直接孩子。\n");
  printf("-V \t--version: 打印版本信息。\n"); 
}


void pstree_version(){
  printf("pstree (simple) 1.0 Copyright (C) 2023-2023 \nThis is free software, and you are welcome to redistribute it under the terms of the GNU General Public License. \nFor more information about these matters, see the files named COPYING.\n");
}

void list_process(){
DIR *pd;
int fd;
struct dirent *pdir;

pd = opendir("/proc");
while ((pdir = readdir(pd)) != NULL)
    {
        /* code */
        struct t_process process;
        char proc_name[50];
        int pid = atoi(pdir->d_name);
        if(pid != 0){
       getInfoByPid(pid,&process);
        //printf("%s\t %s\n",pdir->d_name,proc_name);
        printf("Name:%s\t Pid:%d\t PPid:%d\t\n",process.name,process.pid,process.ppid);

        }
  }
closedir(pd);
// pid_t tp = getpid();
// printf("%d\n",tp);
// char tpname[50];
// getNameByPid(tp,tpname);
// printf("%s\n",tpname);
// strcpy(tpname, argv[0]+2);
// printf("task name is %s\n", tpname); 
// return 0;
}



 
void getInfoByPid(pid_t pid, struct t_process *process) {
    char proc_pid_path[50];
    char task_name[50];
    char buf[BUF_SIZE];
    int apid,ppid;
    sprintf(proc_pid_path, "/proc/%d/stat", pid);
    FILE* fp = fopen(proc_pid_path, "r");
    if(NULL != fp){
       if( fgets(buf, BUF_SIZE-1, fp)== NULL ){
           fclose(fp);
       }
       fclose(fp);
       //printf("%s\n",buf); 
       sscanf(buf, "%d %s %*s %d\n",&apid,task_name,&ppid);

      //size_t length = sizeof(task_name)/sizeof(task_name[0]);
      //printf("%ld\n",length);
       strcpy(process->name,task_name);
       //process->name = task_name;
       process->pid = apid;
       process->ppid = ppid;
       //printf("%d %s %d\n",apid,task_name,ppid);
     }
 }