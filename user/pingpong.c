#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
//#include "kernel/proc.h"

int main(int argc, char *argv[])
{
    int parent_fd[2], child_fd[2];  //[0] output, [1] input
    char buf[64];

    pipe(parent_fd);
    pipe(child_fd);

    if (fork() == 0)
    {
        read(parent_fd[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        write(child_fd[1], "pong", 4);
    }
    else
    {
        write(parent_fd[1], "ping", 4);
        read(child_fd[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
    }
    exit();
    return 0;
}