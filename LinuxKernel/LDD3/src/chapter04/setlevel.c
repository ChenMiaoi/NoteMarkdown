#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __LIBRARY__
#include <linux/unistd.h>

/* 注册syslog命令， 覆盖了库函数中的syslog */
_syscall3(int, syslog, int, type, char *, bufp, int, len);

int main(int argc, char* argv[]) {
    int level;

    if (argc == 2) {
        level = atoi(argv[1]);
    } else {
        fprintf(stderr, "%s: need a single arg\n", argv[0]);
        exit(1);
    }
    /* 该syslog函数指定了等级为1~8，且传入等级为可显示等级最小值 */
    if (syslog(8, NULL, level) < 0) {
        fprintf(stderr, "%s: syslog(setlevel): %s\n", argv[0], strerror(errno));
        exit(1);
    }
    exit(0);
}