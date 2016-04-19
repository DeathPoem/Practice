#include <netdb.h>
#include "is_seqnum.h"

int main(int argc, char* argv[]) {
    char* reqLenStr;
    char seqNumStr[INT_LEN];
    int cfd;
    ssize_t numRead;
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s server-host [sequence-len]\n", argv[0]);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;

    if (getaddrinfo(argv[1], PORT_NUM, &hints, &result) != 0) {
        errExit("getaddrinfo");
    }

    for (rp =result; rp != NULL; rp = rp->ai_next) {
        cfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (cfd == -1) {
            continue;
        }

        if (connect(cfd, rp->ai_addr, rp->ai_addrlen) != -1) {
            break;
        }

        close(cfd);
    }

    if (rp == NULL) {
        fatal("Could not connect socke to any address");

        freeaddrinfo(result);

        reqLenStr = (argc > 2) ? argv[2] : "1";
        if (write(cfd, reqLenStr, strlen(reqLenStr)) != strlen(reqLenStr)) {
            fatal("Partial/failed write (reqLenStr)");
        }

        if (write(cfd, "\n", 1) != 1) {
            fatal("Partial/failed write (newline)");
        }

        numRead = readLine(cfd, seqNumStr, INT_LEN);
        if (numRead == -1) {
            errExit("readLine");
        }
        if (numRead == 0) {
            fatal("Unexpected EOF from server" );
        }

        printf("Sequence number:%s", seqNumStr);

        exit(EXIT_SUCCESS);
    }
}
