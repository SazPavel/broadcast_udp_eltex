#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>

void SigintHandler(int sig)
{
    printf("\nServer out\n");
    exit(0);
}

int main()
{
    struct sigaction sigint;
    sigint.sa_handler = SigintHandler;
    sigint.sa_flags = 0;
    sigemptyset(&sigint.sa_mask);
    sigaddset(&sigint.sa_mask, SIGINT);
    sigaction(SIGINT, &sigint, 0);
    char buf[] = "Broadcast test\n";
    int sock, val = 1;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(-1);
    }
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = inet_addr("10.0.2.255");

    sendto(sock, buf, sizeof(buf), MSG_CONFIRM, (struct sockaddr *)&addr, sizeof(addr));

    close(sock);
    exit(0);
}
