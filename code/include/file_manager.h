
#ifndef MD_FILE_MANAGER_H
#define MD_FILE_MANAGER_H
#include <stdbool.h>
bool is_time_for_backup();
void change_file_permissions(const char *dir, const char *mode);
void lock_dir(const char *dir);
void unlock_dir(const char *dir);
void backup_and_transfer();
void transfer();
void watch_dir();
void log_watched_dir();
void backup();

#endif /* MD_FILE_MANAGER_H */