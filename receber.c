#include <sys/socket.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>




int main()
{


    unsigned char ttl = 1;
    setsockopt(sockfd,IPPROTO_IP, IP_MULTICAST_TTL, &ttl,sizeof(ttl));


    /*Cria um socket UDP */
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    /*Habilita opção de socket para reuse de endereço/porta */
    int sim = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sim, sizeof(sim));
    /*Faz bind do socket criado.*/
    struct sockaddr_in my_addr;
    my_addr.sin_port = grupo.sin_port;
    my_addr.sin_family = grupo.sin_family;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in));
    /*Adiciona o socket criado a um grupo multicast.*/
    struct ip_mreq mreq;
    mreq.imr_multiaddr = grupo.sin_addr;
    mreq.imr_interface.s_addr = INADDR_ANY;
    setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    /*Recebe mensagens endereçada ao grupo sobre o socket.*/
    memset(msg_rcv, 0, MSG_LEN);
    addrlen = sizeof(struct sockaddr_in);
    recvfrom(sockfd, msg_rcv, MSG_LEN, 0, (struct sockaddr *)&addr, (socklen_t*)&addrlen);

}
