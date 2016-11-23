#ifndef CSAPP_H
#define CSAPP_H
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;

#define DEF_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
#define DEF_UMASK S_IWGRP|S_IWOTH

#define MAXLINE 8192
#define MAXBUF 8192
#define LISTENQ 1024

#define RIO_BUFSIZE 8192
typedef struct {
    int rio_fd;
    int rio_cnt;
    char* rio_bufptr;
    char rio_buf[RIO_BUFSIZE];
} rio_t;

extern int h_errno;
extern char** environ;

// error_handling function
void unix_error(char* msg);
void posix_error(int code, char* msg);
void dns_error(char* msg);
void app_error(char* msg);

// Process control wrappers
pid_t Fork(void);
void Execve(const char* filename, char *const argv[], char *const envp[]);
pid_t Wait(int* status);
pid_t Waitpid(pid_t pid, int* iptr, int options);
void Kill(pid_t pid, int signum);
unsigned int Sleep(unsigned int secs);
void Pause(void);
unsigned int Alarm(unsigned int seconds);
void Setpgid(pid_t pid, pid_t pgid);
pid_t Getpgrp();

// signal wrapper
typedef void handler_t(int);
handler_t* Signal(int signum, handler_t* handler);
void Sigprocmask(int how, const sigset_t* set, sigset_t* oldset);
void Sigemptyset(sigset_t* set);
void Sigfillset(sigset_t* set);
void Sigaddset(sigset_t* set, int signum);
void Sigdelset(sigset_t* set, int signum);
int Sigismember(const sigset_t* set, int signum);

//unix i/o wrappers
int Open(const char* pathname, int flags, mode_t mode);
ssize_t Read(int fd, void* buf, size_t count);
ssize_t Writre(int fd, const void* buf, size_t count);
off_t Lseek(int fildes, off_t offset, int whence);
void Close(int fd);
int Select(int n, fd_set* readfds, fd_set* writefds, fd_set* exceptfds,
        struct timeval* timeout);
int Dup2(int fd1, int fd2);
void Stat(const char* filename, struct stat* buf);
void Fstat(int fd, struct stat* buf);

// memory mapping wrappers
void* Mmap(void* addr, size_t len, int prot, int flags, int fd, off_t offset);
void Munmap(void* start, size_t length);

//standard i/o wrappers
void Fclose(FILE* fp);
FILE* Fdopen(int fd, const char* type);
char* Fgets(char* ptr, int n, FILE* stream);
FILE* Fopen(const char* filename, const char* mode);
void Fputs(const char* ptr, FILE* stream);
size_t Fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
void Fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);

//Dynamic storage allocation wrappers
void* Malloc(size_t size);
void* Realloc(void* ptr, size_t size);
void* Calloc(size_t nmemb, size_t size);
void Free(void* ptr);

// Sockets interface wrappers
int Socket(int domain, int type, int protocol);
void Setsockopt(int s, int level, int optname, const void* optval, int optlen);
void Bind(int sockfd, struct sockaddr* my_addr, int addrlen);
void Listen(int s, int backlog);
int Accept(int s, struct sockaddr* addr, socklen_t* addrlen);
void Connect(int sockfd, struct sockaddr* serv_addr, int addrlen);

//DNS wrappers
struct hostent* Gethostbyname(const char* name);
struct hostent* Gethostbyaddr(const char* addr, int len, int type);

//pthread thread control wrappers
void Pthread_create(pthread_t* tidp, pthread_attr_t* attrp, void* (*routine)(void* ),  void* argp);
void Pthread_join(pthread_t tid, void** thread_return);
void Pthread_cancel(pthread_t tid);
void Pthread_detach(pthread_t tid);
void Pthread_exit(void* retval);
pthread_t Pthread_self(void);
void Pthread_once(pthread_once_t* once_control, void (*init_function)());

//Posix semaphore wrappers
void Sem_init(sem_t* sem, int pshared, unsigned int value);
void P(sem_t* sem);
void V(sem_t* sem);

//Rio (Robust i/o) package
ssize_t rio_readn(int fd, void* usrbuf, size_t n);
ssize_t rio_writen(int fd, void* usrbuf, size_t n);
void rio_readinitb(rio_t* rp, int fd);
ssize_t rio_readnb(rio_t* rp, void* usrbuf, size_t n);
ssize_t rio_readlineb(rio_t* rp, void* usrbuf, size_t maxlen);

//wrapper for Rio package
ssize_t Rio_readn(int fd, void* usrbuf, size_t n);
void Rio_writen(int fd, void* usrbuf, size_t n);
void Rio_readinitb(rio_t* rp, int fd);
ssize_t Rio_readnb(rio_t* rp, void* usrbuf, size_t n);
ssize_t Rio_readlineb(rio_t* rp, void* usrbuf, size_t maxlen);

//client/server helper functions
int open_clientfd(char* hostname, int portno);
int open_listenfd(int portno);

//wrapper for client/server helper functions
int Open_clientfd(char* hostname, int port);
int OPen_listenfd(int port);

 

#endif
