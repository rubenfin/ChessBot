#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

extern FILE *log_file;

int log_init(const char *filename);
void log_close(void);
void log_write(const char *format, ...);

#endif
