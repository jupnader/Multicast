#include <sys/socket.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


struct sockaddr_in my_addr;

int main()
{

    
    /*Cria um socket UDP */
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sd < 0){
         perror("socket()");
        return -1;
    }
    
    /*Habilita opção de socket para reuse de endereço/porta */
    int sim = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sim, sizeof(sim)) < 0) {
        perror("SO_REUSEADDR error");
        close(sockfd);
        return -1;    
    }    
    
    /*Faz bind do socket criado.*/
    struct sockaddr_in my_addr;
    my_addr.sin_port = grupo.sin_port;
    my_addr.sin_family = grupo.sin_family;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in)) < 0){
        perror("Bind ()");
        close(sockfd);
        return -1;     
    }
    /*Adiciona o socket criado a um grupo multicast.*/
    struct ip_mreq mreq;
    mreq.imr_multiaddr = grupo.sin_addr;
    mreq.imr_interface.s_addr = INADDR_ANY;
    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("IP_ADD_Membership ()");
        close(sockfd);
        return -1;               
    }
    
    char msg_rcv [1024];
    /*Recebe mensagens endereçada ao grupo sobre o socket.*/
    memset(msg_rcv, 0, MSG_LEN);
    int addrlen = sizeof(struct sockaddr_in);
    recvfrom(sockfd, msg_rcv, MSG_LEN, 0, (struct sockaddr *)&addr, (socklen_t*)&addrlen);

    printf("Voce recebeu uma msg: \"%s\"\n", msg_rcv);

    
    
    return 0;
    
}
   


