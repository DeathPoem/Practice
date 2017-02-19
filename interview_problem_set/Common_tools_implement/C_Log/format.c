#include <stdarg.h>
#include <stdlib.h>
#include <execinfo.h>
#include <stdio.h>

void foo(char* s) {

}
void foofmt(char* fmt, ...) {
    char buf[100];

    va_list v1;
    va_start(v1, fmt);
    vsnprintf(buf, sizeof(buf), fmt, v1);

    va_end(v1);
    foo(buf);
}

int run() {
    void *array[10];
    char** strings;
    int frames = backtrace(array, 8);
    strings = backtrace_symbols(array, frames);
    printf("%s\n", strings[0]);
    free(strings);
    return 0;
}

int main() {
    return run();
}
