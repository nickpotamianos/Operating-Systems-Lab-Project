/*
#AGGELOS NIKOLAOS POTAMIANOS, 1084537
#GRIGORIOS TZWRTZAKIS, 1084538
#ANDREAS KATSAROS, 1084522
*/


// integral_seq.c numerical integration - sequential code
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

//prosthiki
#include <mqueue.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
//telos prosthikis


double get_wtime(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec*1.0e-6;
}

double f(double x)
{
    return log(x)*sqrt(x);
}


// WolframAlpha: integral_1^4 log(x) sqrt(x) dx = 4/9 (4 log(64)-7) 
// -> 4.28245881486164
int main(int argc, char *argv[])
{
    double a = 1.0;
    double b = 4.0;
    unsigned long const n = 1e9;
    const double dx = (b-a)/n;
    
    double S = 0;
    
    double t0 = get_wtime();
    
    //prosthiki
    int num_procs = atoi(argv[1]);
    mqd_t mq;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(double);
    attr.mq_curmsgs = 0;
    mq = mq_open("/integral_queue", O_CREAT | O_RDWR, 0644, &attr);
    pid_t pid;

    for (int i = 0; i < num_procs; i++) {
        pid = fork();
        if (pid == 0) {
            // diergasia paidi
            unsigned long start = i * (n / num_procs);
            unsigned long end = (i + 1) * (n / num_procs);
            double child_S = 0;
            //telos prosthikis
			
			for (unsigned long i = start; i < end; i++) {
                double xi = a + (i + 0.5)*dx;
                child_S += f(xi);
            }
            child_S *= dx;
            //telos prosthikis
            
            //prosthiki
            mq_send(mq, (char *) &child_S, sizeof(double), 0);
            mq_close(mq);
            exit(0);
        }
    }

    // diergasia gonea
    double received_S;
    for (int i = 0; i < num_procs; i++) {
        mq_receive(mq, (char *) &received_S, sizeof(double), 0);
        S += received_S;
    }
    //telos prosthikis
    
    double t1 = get_wtime();
    printf("Time=%lf seconds, Result=%.8f\n", t1-t0, S);
    
	//prosthiki
	mq_close(mq);
    mq_unlink("/integral_queue");
    for (int i = 0; i < num_procs; i++) {
        wait(NULL);
    }
    return 0;
}

