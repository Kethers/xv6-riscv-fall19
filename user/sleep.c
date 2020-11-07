#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(2, "error message\n");
    }
    else
    {
        int time = atoi(argv[1]);
        if (time < 0)
        {
            printf("invalid time input");
        }
        else
        {
            sleep(time);
        }
    }
    exit();
    return 0;
}