#include "csapp.h"

void doit(int);
void read_requesthdrs(rio_t *rp);
int parse_uri(char* uri, char* filename, char* cgiargs);
void serve_static(int fd, char* filename, int filesize);
void get_filetype(char* filename, char* filetype);
void serve_dynamic(int fd, char* filename, char* cgiargs);
void clienterror(int fd, char* cause, char* errnum, char* shortmsg, char* longmsg);

void runtimeLog(char* buf) {
    int fd = open("./runtimelog.txt", O_WRONLY | O_CREAT | O_APPEND,
            S_IRUSR | S_IWUSR);
    printf("log str len = %zu\n", strlen(buf));
    Rio_writen(fd, buf, strlen(buf));
}

void runtimeLogFmt(char* fmt, ...) {
    char buf[200], newbuf[200];
    void* array[10];
    char** backtrace_strings;
    va_list v1;
    va_start(v1, fmt);

    vsnprintf(buf, sizeof(buf), fmt, v1);

    int tmp_size = backtrace(array, 10);
    backtrace_strings = backtrace_symbols(array, tmp_size);
    sprintf(newbuf, "in function: %s : %s\n", backtrace_strings[1], buf);
    free(backtrace_strings);
    va_end(v1);

    runtimeLog(newbuf);
}

void doit(int fd) {
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;

    // read request line and headers
    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
    sscanf(buf, "%s %s %s", method, uri, version);
    if (strcasecmp(method, "GET")) {
        clienterror(fd, method, "501", "Not Implemented", "Tiny does not implement this method");
        return;
    }
    Rio_writen(rio.rio_fd, "OK!\n", 4);
    read_requesthdrs(&rio);
    Rio_writen(rio.rio_fd, "OK!\n", 4);
    // parse uri from GET request
    is_static = parse_uri(uri, filename, cgiargs);
    if (stat(filename, &sbuf) < 0) {
        clienterror(fd, filename, "404", "Not found", "Tiny couldn't find the file");
        return;
    }
    if (is_static) {
    // server static content
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
            clienterror(fd, filename, "403", "Forbidden", "Tiny could't read the file");
            return;
        }
        runtimeLogFmt("arrive line : %d", __LINE__);
        serve_static(fd, filename, sbuf.st_size);
    } else {
        // serve dynamic content
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
            clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't run the CGI program");
            return;
            serve_dynamic(fd, filename, cgiargs);
        }
    }
}

void clienterror(int fd, char* cause, char* errnum, char* shortmsg, char* longmsg) {
    char buf[MAXLINE], body[MAXLINE];

    // build http response body
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    //print the http response
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}

void read_requesthdrs(rio_t *rp) {
    char buf[MAXLINE];
    runtimeLogFmt("arrive line : %d", __LINE__);
    printf("in read_requesthdrs\n");
    Rio_readlineb(rp, buf, MAXLINE);
    runtimeLogFmt("arrive line : %d, buf is : %s\n", __LINE__, buf);
    while(strcmp(buf, "\r\n")) {
        Rio_readlineb(rp, buf, MAXLINE);
        printf("in strcmp");
        runtimeLogFmt("arrive line : %d", __LINE__);
        printf("%s", buf);
    }
    runtimeLogFmt("arrive line : %d", __LINE__);
    return;
}

int parse_uri(char* uri, char* filename, char* cgiargs) {
    char* ptr;
    if (!strstr(uri, "cgi-bin")) {
        //static content
        strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        if (uri[strlen(uri) - 1] == '/') {
            strcat(filename, "home.html");
        }
        return 1;
    } else {
        // dynamic content
        ptr = index(uri, '?');
        if (ptr) {
            strcpy(cgiargs, ptr + 1);
            *ptr = '\0';
        } else {
            strcpy(cgiargs, "");
        }
        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;
    }
}

void serve_static(int fd, char* filename, int filesize) {
    int srcfd;
    char* srcp, filetype[MAXLINE], buf[MAXLINE];
    //send response headers to client
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));

    //send response body to client
    srcfd = Open(filename, O_RDONLY, 0);
    srcp = (char*)Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);
}

void get_filetype(char* filename, char* filetype) {
    if (strstr(filename, ".html")) {
        strcpy(filetype, "text/html");
    } else if (strstr(filename, ".gif:")) {
        strcpy(filetype, "image/gif");
    } else if (strstr(filename, ".jpg")) {
        strcpy(filetype, "image/jpeg");
    } else {
        strcpy(filetype, "text/plain");
    }
}

void serve_dynamic(int fd, char* filename, char* cgiargs) {
    char buf[MAXLINE], *emptylist[] = {NULL};
    //return first part of HTTP response
    sprintf(buf, "HTTP/1.0 200 0k\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));

    if (Fork() == 0) {
        //child
        //real server would set all cgi vars here
        setenv("QUERY_STRING", cgiargs, 1);
        Dup2(fd, STDOUT_FILENO); // redirect stdout to client
        Execve(filename, emptylist, environ); //Run cgi program
    }
    Wait(NULL); //parent waits for and reaps child
}

int tinyHttpServer(int argc, char** argv) {
    int listenfd, connfd, port, clientlen, logfd;
    struct sockaddr_in clientaddr;
    logfd = open("./runtimelog.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRWXO);
    runtimeLogFmt("logfd is %d\n", logfd);

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    port = atoi(argv[1]);

    listenfd = Open_listenfd(port);
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *)&clientlen);
        runtimeLogFmt("enter doit()\n");
        doit(connfd);
        Close(connfd);
    }
}

// call(2, localhost)
int retrievesAndPrintsDNSHostEntry(int argc, char** argv) {
    char** pp;
    struct in_addr addr;
    struct hostent *hostp;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name or dotted-decimal>\n", argv[0]);
        exit(0);
    }

    if (inet_aton(argv[1], &addr) != 0) {
        hostp = Gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET);
    } else {
        hostp = Gethostbyname(argv[1]);
    }

    printf("official hostname: %s\n", hostp->h_name);

    for (pp = hostp->h_aliases; *pp != NULL; pp++) {
        printf("alias: %s\n", *pp);
    }

    for (pp = hostp->h_addr_list; *pp != NULL; pp++) {
        addr.s_addr = ((struct in_addr *) *pp)->s_addr;
        printf("address: %s\n", inet_ntoa(addr));
    }
}

int echoClient(int argc, char** argv) {
    int clientfd, port;
    char* host, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    while (Fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));
        // get response from server
        Rio_readlineb(&rio, buf, MAXLINE);
        //Fputs(buf, stdout);
    }

    Close(clientfd);
    exit(0);
}

void echo(int connfd) {
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        printf("server received %d bytes\n", n);
        Rio_writen(connfd, buf, n);
    }
}

int echoServer(int argc, char** argv) {
    int listenfd, connfd, port, clientlen;
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char* haddrp;
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = atoi(argv[1]);

    listenfd = Open_listenfd(port);
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *)&clientlen);

        hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        haddrp = inet_ntoa(clientaddr.sin_addr);
        printf("server connected to %s (%s)\n", hp->h_name, haddrp);
        echo(connfd);
        Close(connfd);
    }
    exit(0);
}

int tinyhttpClient(int argc, char** argv) {
    int clientfd, port;
    char* host, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    fprintf(stdout, "GET /../ 1.0\r\n");
    sprintf(buf, "GET /../ 1.0\r\n");
    Fputs(buf, stdout);
    Rio_writen(clientfd, buf, strlen(buf));
    // get response from server
    Rio_readlineb(&rio, buf, MAXLINE);

    fprintf(stdout, "asdaz..0\r\n");
    sprintf(buf, "asdaz..0\r\n");
    Fputs(buf, stdout);
    Rio_writen(clientfd, buf, strlen(buf));

    fprintf(stdout, "\r\n");
    sprintf(buf, "\r\n");
    Fputs(buf, stdout);
    Rio_writen(clientfd, buf, strlen(buf));
    // get response from server
    Rio_readlineb(&rio, buf, MAXLINE);

    Close(clientfd);
    exit(0);
}
