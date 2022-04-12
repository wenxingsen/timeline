// author wenxingsen@qq.com
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>

#define BUFF_MAX 1024
#define TIMELINE_VERSION "0.3 beta"
#define DEFAULT_TIMELINE_FORMAT "%Y-%m-%d %H:%M:%S"

char str_timeline_format[BUFF_MAX];

int thread_flag = 0;
int print_every_sec = 0;
long print_every_period = 0;

char now_time[BUFF_MAX];
struct timeval timeval_begin, timeval_end;
long ms_duration;
long ms_duration_last = 0;
char time_cost[BUFF_MAX];

pthread_mutex_t print_mutex;

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

    sprintf(time_cost, "%ldm%02ld.%03lds", min, sec, m_sec);
}

void print_line_log(char* str_buffer, int update_ms_duration)
{
    get_now_time_str(now_time);
    gettimeofday(&timeval_end, NULL);
    long ms_duration_ = ((timeval_end.tv_sec-timeval_begin.tv_sec) * 1000000 + (timeval_end.tv_usec-timeval_begin.tv_usec)) / 1000;
    human_time(ms_duration_, time_cost);
    pthread_mutex_lock(&print_mutex);
    if(strlen(now_time) > 0) 
    {
        printf("[%s %s] %s", now_time, time_cost, str_buffer);
    }
    else
    {
        printf("[%s] %s", time_cost, str_buffer);
    }
    pthread_mutex_unlock(&print_mutex);
    if (update_ms_duration == 1)
    {
        ms_duration = ms_duration_;
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
    printf("\t env: PRINT_EVERY_SEC, defualt is none\n");
}

void thread_print_every_sec(void* arg)
{
    while(thread_flag)
    {
        long time_left = print_every_period * 1000 * print_every_sec;
        sleep(print_every_sec);
        print_every_period++;
        if(time_left >= ms_duration)
        {
            print_line_log(">>>\n", 0);
        } 
    }
}

int timeline_main(int argc, char *argv[])
{
    // print help
    if (argc == 1)
    {
        show_help();
        return 0;
    }

    pthread_mutex_init(&print_mutex, NULL);

    char* timeline_format = getenv("TIMELINE_FORMAT");
    if(timeline_format == NULL) 
    {
        strcpy(str_timeline_format, DEFAULT_TIMELINE_FORMAT);
    } 
    else 
    {
        strcpy(str_timeline_format, timeline_format);
    }
    
    pthread_t every_time_pid;
    char* str_print_every_sec = getenv("PRINT_EVERY_SEC");
    if (str_print_every_sec != NULL)
    {
        print_every_sec = atoi(str_print_every_sec);
        if(print_every_sec > 0)
        {
			thread_flag = 1;
            if (pthread_create(&every_time_pid, NULL, (void*)thread_print_every_sec, NULL) != 0) {
                printf("[Warning] pthread_create error");
            }
        }
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

    FILE *fp;
    char buffer[BUFF_MAX];

    fp = popen(run_cmd, "r");
    gettimeofday(&timeval_begin, NULL);
    while (1)
    {
        char *t = fgets(buffer, sizeof(buffer), fp);
        // end of run
        if (t == NULL)
        {
            break;
        }

        print_line_log(buffer, 1);
    }

    print_line_log(">>> the end", 1); 
	
    if (thread_flag != 0)
    {
        thread_flag = 0;
        pthread_join(every_time_pid, NULL);
    }

    int return_code = WEXITSTATUS(pclose(fp));
    
    human_time(ms_duration, time_cost);
    printf("\n\ncost time: %s, return code: %d\n", time_cost, return_code);
 
    return return_code;
}

int main(int argc, char *argv[])
{
    return timeline_main(argc, argv);
}
