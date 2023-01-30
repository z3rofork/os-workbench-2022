#include <stdio.h>
#include <assert.h>

/*把系统中的进程按照父亲-孩子的树状结构打印到终端。 \
//-p, --show-pids: 打印每个进程的进程号。 \
//-n --numeric-sort: 按照pid的数值从小到大顺序输出一个进程的直接孩子。 \
//-V --version: 打印版本信息。 \
//你可以在命令行中观察系统的 pstree 的执行行为 (如执行 pstree -V、pstree --show-pids 等)。这些参数可能任意组合，但你不需要处理单字母参数合并的情况，例如 -np。
*/

int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    assert(argv[i]);
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  assert(!argv[argc]);
  return 0;
}
