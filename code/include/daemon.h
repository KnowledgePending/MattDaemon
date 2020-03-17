#ifndef MD_DAEMON_H
#define MD_DAEMON_H

#include <stdbool.h>

bool is_singleton();
void daemonize();

#endif /* MD_DAEMON_H */