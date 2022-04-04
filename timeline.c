// author wenxingsen@qq.com
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#define BUFF_MAX 1024
#define TIMELINE_VERSION "0.2 beta"
#define DEFAULT_TIMELINE_FORMAT "%Y-%m-%d %H:%M:%S"

char str_timeline_format[BUFF_MAX];

void get_now_time_str(char *timeStr)
{
    time_t now = time(NULL);
    strftime(timeStr, BUFF_MAX, str_timeline_format, localtime(&now));
}

void human_time(int m_s, char* time_cost)
{
    long m_sec = m_s % 1000;
    long last_sec = m_s / 1000;
    long sec = last_sec % 60;
    long min = last_sec / 60;

    sprintf(time_cost, "%ldm%ld.%03lds", min, sec, m_sec);
}

void print_line_log(char* now_time, char* time_cost, char* str_buffer)
{
    if(strlen(now_time) == 0)
    {
       printf("[%s] %s", time_cost, str_buffer);
    }
    else
    {
        printf("[%s %s] %s", now_time, time_cost, str_buffer);
    }
}

void show_help()
{
    printf("A tool likes 'time' command, which outputs time in every line log.\n");
    printf("version: %s.\n\n", TIMELINE_VERSION);
    printf("Usage:\n\ttimeline [cmd]\n");
    printf("Exeample:\n\ttimeline make\n");
    printf("\ttimeline ./demo-cmd.sh\n");
    printf("\ttimeline ping baidu.com\n");
    printf("Config:\n");
    printf("\t env: TIMELINE_FORMAT, defualt is '%s'\n", DEFAULT_TIMELINE_FORMAT);
}

int timeline_main(int argc, char *argv[])
{
    // print help
    if (argc == 1)
    {
        show_help();
        return 0;
    }

    char* timeline_format = getenv("TIMELINE_FORMAT");
    if(timeline_format == NULL) 
    {
        strcpy(str_timeline_format, DEFAULT_TIMELINE_FORMAT);
    } 
    else 
    {
        strcpy(str_timeline_format, timeline_format);
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
    long ms_duration;
    char now_time[BUFF_MAX];
    char time_cost[BUFF_MAX];
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
        ms_duration = ((timeval_end.tv_sec-timeval_begin.tv_sec) * 1000000 + (timeval_end.tv_usec-timeval_begin.tv_usec)) / 1000;
        human_time(ms_duration, time_cost);
        print_line_log(now_time, time_cost, buffer);
    }

    gettimeofday(&timeval_end, NULL);
    ms_duration = ((timeval_end.tv_sec-timeval_begin.tv_sec) * 1000000 + (timeval_end.tv_usec-timeval_begin.tv_usec)) / 1000;
    human_time(ms_duration, time_cost);
    print_line_log(now_time, time_cost, "<<< the end"); 

    int return_code = WEXITSTATUS(pclose(fp));
    
    human_time(ms_duration, time_cost);
    printf("\n\ncost time: %s, return code: %d\n", time_cost, return_code);
 
    return return_code;
}

int main(int argc, char *argv[])
{
    return timeline_main(argc, argv);
}
