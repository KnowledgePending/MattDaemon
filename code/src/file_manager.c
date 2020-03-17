#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include "file_manager.h"
#include "config.h"

bool is_time_for_backup()
{
    time_t now;
    struct tm target_time;
    double seconds;
    time(&now);
    target_time = *localtime(&now);

    target_time.tm_hour = NIGHTLY_BACKUP_TIME_HOUR;
    target_time.tm_min = NIGHTLY_BACKUP_TIME_MIN;
    target_time.tm_sec = NIGHTLY_BACKUP_TIME_SEC;

    // Change to check purely for hour
    seconds = difftime(now, mktime(&target_time));
    return (seconds == 0);
}

void change_file_permissions(const char *dir, const char *mode)
{
    char string_exec[5024];
    char result[1024];
    syslog(LOG_INFO, "%s", "Attempting to change file permissions");
    sprintf(string_exec, "sudo chmod -R %s %s", mode, dir);

    FILE *fp = popen(string_exec, "r");

    while (fgets(result, 1024, fp) != NULL)
    {
        syslog(LOG_ERR, "Change file permissions failed: %s", result);
    }
}

void lock_dir(const char *dir)
{
    const char mode[] = "0700";
    change_file_permissions(dir, mode);
}

void unlock_dir(const char *dir)
{
    const char mode[] = "0775";
    change_file_permissions(dir, mode);
}

void sync_folders(const char* src, const char* dest, const char* completion_message)
{
    char string_exec[5024];

    // Sync folders
    // Only copying/deleting files that have changed 
    sprintf(string_exec, "sudo rsync -avu --delete %s/ %s", src, dest);

    // execute string exec
    FILE *fp = popen(string_exec, "r");

    // Output resulting pipe
    char result[1024];
    while (fgets(result, 1024, fp) != NULL)
    {
        syslog(LOG_ERR, "%s", result);
    }

    // Signify completion
    syslog(LOG_INFO, "%s", completion_message);
}

void backup()
{
    lock_dir(INTRANET_DIR);
    lock_dir(BACKUP_DIR);
    lock_dir(LIVE_DIR);
    char string_exec[5024];
    char result[1024];

    sprintf(string_exec, "sudo cp -r %s/ %s", LIVE_DIR, BACKUP_DIR);
    

    FILE *fp = popen(string_exec, "r");

    while (fgets(result, 1024, fp) != NULL)
    {
        syslog(LOG_ERR, "%s", result);
    }

    syslog(LOG_INFO, "%s", "Completed Backup");
}

void transfer()
{
    lock_dir(INTRANET_DIR);
    lock_dir(BACKUP_DIR);
    lock_dir(LIVE_DIR);
    char string_exec[5024];
    char result[1024];

    // Sync folders
    // Only copying/deleting files that have changed 
    sprintf(string_exec, "sudo rsync -avu --delete %s/ %s", INTRANET_DIR, LIVE_DIR);

    FILE *fp = popen(string_exec, "r");

    while (fgets(result, 1024, fp) != NULL)
    {
        syslog(LOG_ERR, "%s", result);
    }
    syslog(LOG_INFO, "%s", "Completed Transfer");
}

void backup_and_transfer()
{
    backup();
    transfer();
}

void watch_dir()
{
    char string_exec[5024];

    char result[1024];

    // Start Watching directory
    sprintf(string_exec, "auditctl -w %s -p wrxa -k %s", INTRANET_DIR, AUDIT_KEY);

    FILE *fp = popen(string_exec, "r");

    while (fgets(result, 1024, fp) != NULL)
    {
        syslog(LOG_ERR, "%s", result);
    }
}

void log_watched_dir()
{
    char string_exec[5024];
    char result[1024];

    // Search File Watch Logs from Yesterday to Now.
    // Format data using aureport
    // Create/Append data to File Monitoring Log
    sprintf(string_exec, "ausearch -ts %s -te %s -k %s | aureport -f -i > %s", START_WATCH_TIME, END_WATCH_TIME, AUDIT_KEY, FILE_MONITORING_LOG_FILE);

    FILE *fp = popen(string_exec, "r");

    while (fgets(result, 1024, fp) != NULL)
    {
        syslog(LOG_ERR, "%s", result);
    }
    syslog(LOG_INFO, "%s", "Stored File Watch Logs from Yesterday to Now");
}