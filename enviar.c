#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>



struct sockaddr_in grupo;


int main(){



    unsigned char ttl = 1;


    /*Emissor cria um socket UDP*/
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
		perror("socket()");
		return -1;
	}

    /*Especifica o endereço (IP/Porta) de destino para multicast IP*/

    inet_pton(AF_INET, "225.0.0.10", &grupo.sin_addr);
    grupo.sin_port = htons(1234);
    grupo.sin_family = AF_INET;

    /*desabilita recebimento da propria mensagem*/
    char loopch = 0;
    if(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0)
    {
        perror("Setting IP_MULTICAST_LOOP error");
        close(sockfd);
        exit(1);
    }
    else printf("Disabling the loopback...OK.\n");




	/*configura socket*/
    if(setsockopt(sockfd,IPPROTO_IP, IP_MULTICAST_TTL, &ttl,sizeof(ttl))<0)
    {
        perror("setsocktop();");
		return -1;

    }


    /*Envia uma mensagem usando a primitiva sendto()*/
    char *msg = "bla bla bla ...";
    if(sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&grupo, sizeof(struct sockaddr_in))<0)
    {
        perror("sendto();");
		return -1;

    }

	return 0;
}
