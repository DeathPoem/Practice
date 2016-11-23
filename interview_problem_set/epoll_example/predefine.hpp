#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <termios.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "infrastructure.h"

using std::string;
using std::vector;

/* Place terminal referred to by 'fd' in cbreak mode (noncanonical mode
   with echoing turned off). This function assumes that the terminal is
   currently in cooked mode (i.e., we shouldn't call it if the terminal
   is currently in raw mode, since it does not undo all of the changes
   made by the ttySetRaw() function below). Return 0 on success, or -1
   on error. If 'prevTermios' is non-NULL, then use the buffer to which
   it points to return the previous terminal settings. */

int
ttySetCbreak(int fd, struct termios *prevTermios)
{
    struct termios t;

    if (tcgetattr(fd, &t) == -1)
        return -1;

    if (prevTermios != NULL)
        *prevTermios = t;

    t.c_lflag &= ~(ICANON | ECHO);
    t.c_lflag |= ISIG;

    t.c_iflag &= ~ICRNL;

    t.c_cc[VMIN] = 1;                   /* Character-at-a-time input */
    t.c_cc[VTIME] = 0;                  /* with blocking */

    if (tcsetattr(fd, TCSAFLUSH, &t) == -1)
        return -1;

    return 0;
}

static void usageError(const char* progName) {
    fprintf(stderr, "Usage : %s {timeout|-} fd-num[rw]...\n", progName);
    fprintf(stderr, "   - means infinite timeout; \n");
    fprintf(stderr, "   r = monitor for read\n");
    fprintf(stderr, "   w = monitor for write\n\n");
    fprintf(stderr, "   e.g.: %s - Orw 1w\n", progName);
    exit(EXIT_FAILURE);
}

// wrapper of these three kinds of I/O
//
class Solution {

    private :

    vector<string> file_name_list_ {
        "mylog.log",
            "myfile",
            "startup",
            "other_for_nj",
            "other_for_read",
            "other_for_write",
            "other_for_except"
    };

    string path_name_;

    public :

    void get_pathname(string s);        

    int CallOpen();

    int CallFopen();

    int CallOpenNonBlocking();

    int CallSelet();

    int CallSignalDriven();

    int CallEpoll();

};

void Solution::get_pathname(string s) {
    path_name_ = s;
}

//try to open a file and write
int Solution::CallOpen() {
    int fd;
    fd = open((path_name_ + file_name_list_[0]).c_str(), O_RDONLY);
    if (fd == -1) {
        errExit("open");
    }

    fd = open((path_name_ + file_name_list_[1]).c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        errExit("open");
    }

    fd = open((path_name_ + file_name_list_[2]).c_str(), O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,
            S_IRUSR | S_IWUSR);

    if (fd == -1) {
        errExit("open");
    }

    //write something 
    char write_buf[100];
    snprintf(write_buf, 100, "this is just some nonsence");

    write(fd, write_buf, 100);

    close(fd);
}

// try to open file and write
int Solution::CallFopen() {
    FILE* fp;
    fp = fopen((path_name_ + file_name_list_[0]).c_str(), "rw");
    if (!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    int c;
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }

    if (ferror(fp)) {
        puts("I/O error when reading");
    } else if (feof(fp)) {
        puts("End of file reached successfully");
    }

    fclose(fp);
}

//try to open file and write
int Solution::CallOpenNonBlocking() {

    int fd = open((path_name_ + file_name_list_[0]).c_str(), O_RDWR | O_CREAT | O_TRUNC | O_NONBLOCK, S_IRUSR | S_IWUSR);

    //write something 
    char write_buf[100];
    snprintf(write_buf, 100, "this is just some nonsence");

    write(fd, write_buf, 100);

    close(fd);
}

bool isselected(int fd, fd_set* fdsp) {
    if (FD_ISSET(fd, fdsp)) {
        std::cout << "one fd is selected " << std::endl;
    }
    return true;
}

//try to open file and write
int Solution::CallSelet() {

    fd_set* fds;
    FD_ZERO(fds);

    int fd_1 = open((path_name_ + file_name_list_[3]).c_str(), O_RDWR | O_CREAT | O_TRUNC | O_NONBLOCK, S_IRUSR | S_IWUSR);
    int fd_2 = open((path_name_ + file_name_list_[4]).c_str(), O_RDWR | O_CREAT | O_TRUNC | O_NONBLOCK, S_IRUSR | S_IWUSR);
    int fd_3 = open((path_name_ + file_name_list_[5]).c_str(), O_RDWR | O_CREAT | O_TRUNC | O_NONBLOCK, S_IRUSR | S_IWUSR);
    int fd_4 = open((path_name_ + file_name_list_[6]).c_str(), O_RDWR | O_CREAT | O_TRUNC | O_NONBLOCK, S_IRUSR | S_IWUSR);

    FD_SET(fd_1, fds);
    FD_SET(fd_2, fds);
    FD_SET(fd_3, fds);
    FD_SET(fd_4, fds);

    isselected(fd_1, fds);
    isselected(fd_2, fds);
    isselected(fd_3, fds);
    isselected(fd_4, fds);

    int nfds = std::max({fd_1, fd_2, fd_3, fd_4});
    timeval t = {1, 0};

    int ready_num = select(nfds, fds, NULL, fds, &t);

    if (ready_num == -1) {
        errExit("select");
    }

    printf("ready_num = %d\n", ready_num);

    printf("%d : %s %s\n", fd_1, FD_ISSET(fd_1, fds) ? "r" : "", FD_ISSET(fd_1, fds) ? "w" : "");
    printf("%d : %s %s\n", fd_2, FD_ISSET(fd_2, fds) ? "r" : "", FD_ISSET(fd_2, fds) ? "w" : "");
    printf("%d : %s %s\n", fd_3, FD_ISSET(fd_3, fds) ? "r" : "", FD_ISSET(fd_3, fds) ? "w" : "");
    printf("%d : %s %s\n", fd_4, FD_ISSET(fd_4, fds) ? "r" : "", FD_ISSET(fd_4, fds) ? "w" : "");

    printf("timeout after select(): %ld.%03ld\n",
            (long) t.tv_sec, (long) t.tv_usec / 10000);

    //write something
    char write_buf[100];
    snprintf(write_buf, 100, "this is just some nonsence");

    write(fd_1, write_buf, 100);

    exit(EXIT_SUCCESS);
}

static volatile sig_atomic_t gotSigio = 0;
static void sigioHandler(int sig) {
    gotSigio = 1;
}

int Solution::CallSignalDriven() {

    // Establish handler for "I/O possible" signal

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sigioHandler;

    if (sigaction(SIGIO, &sa, NULL) == -1) {
        errExit("sigaction");
    }
    // set owner process that is to receive "I/O possible" signal
    if (fcntl(STDIN_FILENO, F_SETOWN, getpid()) == -1) {
        errExit("fcntl(F_sETOWN)");
    }

    //enable "I/O possible" signaling and make I/O nonblocking for file descriptor
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    if (fcntl(STDIN_FILENO, F_SETFL, flags | O_ASYNC | O_NONBLOCK) == -1) {
        errExit("fcntl(F_SETFL)");
    }

    //place terminal in cbreak mode

    struct termios origTermios;
    if (ttySetCbreak(STDIN_FILENO, &origTermios) == -1) {
        errExit("ttySetCbreak");
    }

    int cnt = 0;
    char ch;
    for (bool done = false; !done ; ++cnt) {
        for (int j = 0; j < 100000000; ++j) {
            continue;
        }

        if (gotSigio) {
            gotSigio = 0;

            while (read(STDIN_FILENO, &ch, 1) > 0 && !done) {
                printf("cnt=%d; read %c\n", cnt, ch);
                done = ch == '#';
            }
        }

    }
}

int Solution::CallEpoll() {

    int epfd;
    struct epoll_event ev;
    struct epoll_event evlist[5];
    epfd = epoll_create(5);
    if (epfd == -1) {
        errExit("epoll_create");
    }
    for (int j = 0; j < 5; ++j) {
        int fd = open((path_name_ + file_name_list_[j]).c_str(), O_RDONLY);
        if (fd == -1) {
            errExit("open");
        }
        printf("Opened \" %s \" on fd %d \n", file_name_list_[j].c_str(), fd);
        ev.data.fd = fd;
        ev.events = EPOLLIN;
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
            errExit("epoll_ctl");
        }
    }

    int num_open_fds = 5;

    while (num_open_fds > 0) {
        printf("About to epoll_wait()\n");
        int ready = epoll_wait(epfd, evlist, 5, -1);
        if (ready == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                errExit("epoll_wait");
            }
        }
    }
}
