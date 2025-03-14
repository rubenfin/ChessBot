#include "../include/logger.hpp"
#include <stdarg.h>
#include <stdlib.h>

FILE *log_file = NULL;

int log_init(const char *filename) {
    log_file = fopen(filename, "w");
    if (!log_file) {
        perror("Failed to open log file");
        return 1;
    }
    return 0;
}

void log_close(void) {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

void log_write(const char *format, ...) {
    if (!log_file) return;

    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);

    fflush(log_file);
}
