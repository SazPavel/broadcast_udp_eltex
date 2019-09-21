#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock;
    char buf[16];
    struct sockaddr_in addr;
    socklen_t size = 1;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("sock");
        exit(-1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = inet_addr("10.0.2.255");

    if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(-1);
    }

    recvfrom(sock, buf, 16, MSG_WAITALL, (struct sockaddr*)&addr, &size);
    printf("%s\n", buf);

    close(sock);
    exit(0);
}
