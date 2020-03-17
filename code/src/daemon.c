#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <errno.h>
#include <mqueue.h>
#include <string.h>
#include <time.h>

#include "daemon.h"

void daemonize()
{

    pid_t pid, sid;

    // create a child process
    pid = fork();

    // check if fork succeeded
    if (pid < 0)
        exit(EXIT_FAILURE);

    // kill parent process
    if (pid > 0)
        exit(EXIT_SUCCESS);

    // create a new session
    sid = setsid();

    // check if session was created
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    // handle signals
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    // fork again
    pid = fork();

    // check if fork succeeded
    if (pid < 0)
        exit(EXIT_FAILURE);

    // kill parent process
    if (pid > 0)
        exit(EXIT_SUCCESS);

    // allow access to created files
    umask(0);

    // Attempt to change dir to root 
    if (chdir("/") < 0)
    {
        exit(EXIT_FAILURE);
    }

    // close file descriptors
    for (int i = sysconf(_SC_OPEN_MAX); i >= 0; --i)
    {
        close(x);
    }

    // Direct files to /dev/null
    freopen("/dev/null", "r", stdin);
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
}
