#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <mqueue.h>
#include <time.h>
#include "config.h"
#include "daemon.h"
#include "file_manager.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid or no Command Line Argument Passed Other Than Program Name\n");
    }
    else
    {
        // shortcutting makes this code correct
        if (strlen(argv[1]) == strlen("start") && !strncmp(argv[1], "start", strlen("start")))
        {
            printf("Starting Singleton Daemon\n");
            // create log
            openlog("MattDaemonsLog", LOG_PID | LOG_CONS, LOG_USER);

            syslog(LOG_INFO, "Starting Singleton Daemon");
            daemonize();
            syslog(LOG_INFO, "Daemonized");

            // track file changes
            watch_dir();

            // Check if time for backup
            while (1)
            {
                syslog(LOG_INFO, "Checking if time for backup");
                if (is_time_for_backup())
                {
                    syslog(LOG_INFO, "Updating watched dir log file");
                    log_watched_dir();
                    backup_and_transfer();
                }
            }
        }
        else if (strlen(argv[1]) == strlen("backup") && !strncmp(argv[1], "backup", strlen("backup")))
        {
            printf("Backingup\n");
            backup();
            unlock_dir(INTRANET_DIR);
        }
        else if (strlen(argv[1]) == strlen("transfer") && !strncmp(argv[1], "transfer", strlen("transfer")))
        {
            printf("Transfering\n");
            log_watched_dir();
            transfer();
            unlock_dir(INTRANET_DIR);
        }
        else if (strlen(argv[1]) == strlen("btransfer") && !strncmp(argv[1], "btransfer", strlen("btransfer")))
        {
            printf("Backup and transfer\n");
            log_watched_dir();
            backup_and_transfer();
            unlock_dir(INTRANET_DIR);
        }
        else
        {
            printf("Error invalid Argument\n");
        }
    }
    return 0;
}
