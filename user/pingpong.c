#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int to_parent[2];
  int to_child[2];

  pipe(to_parent);
  pipe(to_child);

  int pid = fork();

  if(pid == 0) {
    // child
    char received;
    read(to_child[0], &received, 1);
    printf("%d: received ping\n", getpid());
    write(to_parent[1], "o", 1);
  } else {
    // parent
    char received;
    write(to_child[1], "i", 1);
    read(to_parent[0], &received, 1);
    printf("%d: received pong\n", getpid());
  }

  exit(0);
}