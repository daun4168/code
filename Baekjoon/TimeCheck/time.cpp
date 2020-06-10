#include <iostream>
#include <sys/times.h>
#include <unistd.h>
using namespace std;

static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *);

int main(int argc, char *argv[])
{
    int i;
    setbuf(stdout, NULL);
    for (i = 1; i < argc; i++)
        do_cmd(argv[i]);    /* once for each command-line arg */
    exit(0);
}

    static void
do_cmd(char *cmd)        /* execute and time the "cmd" */
{
    struct tms  tmsstart, tmsend;
    clock_t     start, end;
    int         status;

    printf("\ncommand: %s\n", cmd);

    if ((start = times(&tmsstart)) == -1)    /* starting values */
        cout << "times error" << endl; 

    if ((status = system(cmd)) < 0)     /* execute command */
        cout << "system error" << endl; 

    if ((end = times(&tmsend)) == -1)
        cout << "times error" << endl;                                          
    pr_times(end-start, &tmsstart,
            &tmsend);
    exit(status);
}
    static void
pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    static long     clktck = 0;

    if (clktck == 0)    /* fetch clock ticks per second first time */
        if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
            cout << "sysconf error" << endl;
    printf(" real:  %7.2f\n", real / (double) clktck);
    printf(" user:  %7.2f\n",
    
            (tmsend->tms_utime - tmsstart->tms_utime) / (double) clktck);
    printf(" sys:   %7.2f\n",
            (tmsend->tms_stime - tmsstart->tms_stime) / (double)
            clktck);
    printf(" child user:   %7.2f\n",
            (tmsend->tms_cutime - tmsstart->tms_cutime) /
            (double) clktck);
    printf(" child sys:    %7.2f\n",
            (tmsend->tms_cstime - tmsstart->tms_cstime) /
            (double) clktck);
}