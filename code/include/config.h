#ifndef MD_CONFIG_H
#define MD_CONFIG_H


// Time at which nightly backup and transfer occurs
#define NIGHTLY_BACKUP_TIME_SEC 0
#define NIGHTLY_BACKUP_TIME_MIN 22
#define NIGHTLY_BACKUP_TIME_HOUR 15


// Relevant Directories
#define INTRANET_DIR "/var/www/html/intranet"
#define BACKUP_DIR "/var/www/html/backup"
#define LIVE_DIR "/var/www/html/live"

// Audit Key
#define AUDIT_KEY "MATTDAEMONKEY"
#define FILE_MONITORING_LOG_FILE "/var/www/html/log/audit_log.txt"
#define START_WATCH_TIME "yesterday"
#define END_WATCH_TIME "now"

#endif /* MD_CONFIG_H */