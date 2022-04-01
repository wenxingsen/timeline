// author wenxingsen@qq.com
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#define BUFF_MAX 1024
#define TIMELINE_VERSION "0.1 beta"

void get_now_time_str(char *timeStr)
{
    time_t now = time(NULL);
    strftime(timeStr, BUFF_MAX, "%Y-%m-%d %H:%M:%S", localtime(&now));
}

int timeline_main(int argc, char *argv[])
{
    // print help
    if (argc == 1)
    {
        printf("A tool likes time command, which outputs more real-time log. version: %s.\n\n", TIMELINE_VERSION);
        printf("Usage:\n\ttimeline [cmd]\n");
        printf("Exeample:\n\ttimeline make\n");
        printf("\ttimeline ./demo-cmd.sh\n");
        printf("\ttimeline ping baidu.com\n");
        return 1;
    }

    char run_cmd[BUFF_MAX] = {};
    int index = 0;
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < strlen(argv[i]); j++)
        {
            run_cmd[index] = argv[i][j];
            index++;
        }
        run_cmd[index] = ' ';
        index++;
    }

    struct timeval timeval_begin, timeval_end;
    FILE *fp;
    char buffer[BUFF_MAX];

    fp = popen(run_cmd, "r");
    gettimeofday(&timeval_begin, NULL);
    long n_duration;
    char now_time[BUFF_MAX];
    while (1)
    {
        get_now_time_str(now_time);
        char *t = fgets(buffer, sizeof(buffer), fp);
        // end of run
        if (t == NULL)
        {
            break;
        }

        gettimeofday(&timeval_end, NULL);
        n_duration = timeval_end.tv_sec - timeval_begin.tv_sec;
        printf("[%s][%lds] %s", now_time, n_duration, buffer);
    }

    gettimeofday(&timeval_end, NULL);
    n_duration = timeval_end.tv_sec - timeval_begin.tv_sec;
    printf("[%s][%lds] %s\n", now_time, n_duration, "<<< the end");

    int return_code = WEXITSTATUS(pclose(fp));
    printf("\ncost time: %lds, return code: %d\n", n_duration, return_code);
    
    return return_code;
}

int main(int argc, char *argv[])
{
    return timeline_main(argc, argv);
}