#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "ename.c.inc"

#define BUF_SIZE 1000

void errExit(const char* format, ...);

static void outputError(bool useErr, int err, bool flushstd, const char* format, va_list ap);

long getLong(const char* arg, int flags, const char* name) {
    return getNum("getLong", arg, flags, name);
}

void errExit(const char* format, ...) {
va_list argList;

va_start(argList, format);
outputError(true, errno, true, format, argList);
va_end(argList);

exit(EXIT_FAILURE);
}

static void outputError(bool useErr, int err, bool flushstd, const char* format, va_list ap) {
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];

    vsnprintf(userMsg, BUF_SIZE, format, ap);

    if (useErr) {
        snprintf(errText, BUF_SIZE, " [%s %s]",
                (err > 0 && err <= MAX_ENAME) ?
                ename[err] : "?UNKNOWN?", strerror(err));
    } else {
        snprintf(errText, BUF_SIZE, ":");

        snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);
    }

    if (flushstd) {
        fflush(stdout);
    }
    fputs(buf, stderr);
    fflush(stderr);
}

#endif
