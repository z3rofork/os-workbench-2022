#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>

void Usage(const char *filename);
void Pstree_Version();
int main(int argc, char *argv[]) {
  // for (int i = 0; i < argc; i++) {
  //   assert(argv[i]);
  //   printf("argv[%d] = %s\n", i, argv[i]);
  // }
  // assert(!argv[argc]);
  int opt;
  const char *optString="p::n::V::";
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
      Pstree_Version();
      break;

    default:
      
      Usage(argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  if(optind >= argc){
    fprintf(stderr,"Expected argument after options\n");
    Usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
  return 0;
}


void Usage(const char *filename){
  fprintf(stderr,"Usage: %s [-p, -n, -V]\n",filename);
  printf("把系统中的进程按照父亲-孩子的树状结构打印到终端。\n");
  printf("-p \t--show-pids: 打印每个进程的进程号。\n");
  printf("-n \t--numeric-sort: 按照pid的数值从小到大顺序输出一个进程的直接孩子。\n");
  printf("-V \t--version: 打印版本信息。\n"); 
}


void Pstree_Version(){
  printf("pstree (simple) 1.0 Copyright (C) 2023-2023 \nThis is free software, and you are welcome to redistribute it under the terms of the GNU General Public License. \nFor more information about these matters, see the files named COPYING.\n");
}