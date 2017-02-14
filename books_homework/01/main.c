#include "csapp.h"

int tinyHttpServer(int argc, char** argv) {
    int listenfd, connfd, port, clientlen;
    struct sockaddr_in clientaddr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    port = atoi(argv[1]);

    listenfd = Open_listenfd(port);
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *)&clientlen);
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
        Rio_readlineb(&rio, buf, MAXLINE);
        Fputs(buf, stdout);
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
