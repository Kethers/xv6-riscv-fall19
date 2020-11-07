#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define R 0
#define W 1

int main(int argc, char *argv[])
{
    int numbers[100], cnt = 0;
    int fd[2];

    for (int i = 2; i <= 35; i++)
    {
        numbers[cnt++] = i;
    }

    while (cnt > 0)
    {
        pipe(fd);
        if (fork() == 0) //子进程
        {
            int prime, this_prime = 0;
            close(fd[W]);
            cnt = -1;
            while (read(fd[R], &prime, sizeof(prime)) != 0)
            {
                if (cnt == -1) //设置当前进程的素数，筛选掉能被当前素数整除的数
                {
                    this_prime = prime;
                    cnt = 0;
                }
                else
                {
                    if (prime % this_prime != 0)
                    {
                        numbers[cnt++] = prime;
                    }
                }
            }
            printf("prime %d\n", this_prime);
            close(fd[R]);
        }

        else //父进程
        {
            close(fd[R]);
            for (int i = 0; i < cnt; i++)
            {
                write(fd[W], &numbers[i], sizeof(numbers[0]));
            }
            close(fd[W]);
            wait();
            break;
        }
    }

    exit();
    return 0;
}