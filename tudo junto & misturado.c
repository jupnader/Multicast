     /* Send Multicast Datagram code example. */

    #include <sys/types.h>

    #include <sys/socket.h>

    #include <arpa/inet.h>

    #include <netinet/in.h>

    #include <stdio.h>

    #include <stdlib.h>

    struct in_addr localInterface;

    struct sockaddr_in groupSock;

    int sd;

    char databuf[1024] = "Multicast test message lol!";

    int datalen = sizeof(databuf);

     

    int main (int argc, char *argv[ ])

    {

    /* Create a datagram socket on which to send. */

    sd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sd < 0)

    {

      perror("Opening datagram socket error");

      exit(1);

    }

    else

      printf("Opening the datagram socket...OK.\n");

     

    /* Initialize the group sockaddr structure with a */

    /* group address of 225.1.1.1 and port 5555. */

    memset((char *) &groupSock, 0, sizeof(groupSock));

    groupSock.sin_family = AF_INET;

    groupSock.sin_addr.s_addr = inet_addr("226.1.1.1");

    groupSock.sin_port = htons(4321);

     

    /* Disable loopback so you do not receive your own datagrams.

    {

    char loopch = 0;

    if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0)

    {

    perror("Setting IP_MULTICAST_LOOP error");

    close(sd);

    exit(1);

    }

    else

    printf("Disabling the loopback...OK.\n");

    }

    */

     

    /* Set local interface for outbound multicast datagrams. */

    /* The IP address specified must be associated with a local, */

    /* multicast capable interface. */

    localInterface.s_addr = inet_addr("203.106.93.94");

    if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)

    {

      perror("Setting local interface error");

      exit(1);

    }

    else

      printf("Setting the local interface...OK\n");

    /* Send a message to the multicast group specified by the*/

    /* groupSock sockaddr structure. */

    /*int datalen = 1024;*/

    if(sendto(sd, databuf, datalen, 0, (struct sockaddr*)&groupSock, sizeof(groupSock)) < 0)

    {perror("Sending datagram message error");}

    else

      printf("Sending datagram message...OK\n");

     

    /* Try the re-read from the socket if the loopback is not disable

    if(read(sd, databuf, datalen) < 0)

    {

    perror("Reading datagram message error\n");

    close(sd);

    exit(1);

    }

    else

    {

    printf("Reading datagram message from client...OK\n");

    printf("The message is: %s\n", databuf);

    }

    */

    return 0;

    }

    Compile and link the program.

    [bodo@bakawali testsocket]$ gcc -g mcastserver.c -o mcastserver

    Before running this multicaster program, you have to run the client program first as in the following.

Example: Receiving a multicast datagram, a client

    The following example enables a socket to perform the steps listed below and to receive multicast datagrams:

        Create an AF_INET, SOCK_DGRAM type socket.

        Set the SO_REUSEADDR option to allow multiple applications to receive datagrams that are destined to the same local port number.

        Use the bind() verb to specify the local port number.  Specify the IP address as INADDR_ANY in order to receive datagrams that are addressed to a multicast group.

        Use the IP_ADD_MEMBERSHIP socket option to join the multicast group that receives the datagrams.  When joining a group, specify the class D group address along with the IP address of a local interface.  The system must call the IP_ADD_MEMBERSHIP socket option for each local interface receiving the multicast datagrams.

        Receive the datagram.

	

    /* Receiver/client multicast Datagram example. */

    #include <sys/types.h>

    #include <sys/socket.h>

    #include <arpa/inet.h>

    #include <netinet/in.h>

    #include <stdio.h>

    #include <stdlib.h>

     

    struct sockaddr_in localSock;

    struct ip_mreq group;

    int sd;

    int datalen;

    char databuf[1024];

     

    int main(int argc, char *argv[])

    {

    /* Create a datagram socket on which to receive. */

    sd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sd < 0)

    {

    perror("Opening datagram socket error");

    exit(1);

    }

    else

    printf("Opening datagram socket....OK.\n");

     

    /* Enable SO_REUSEADDR to allow multiple instances of this */

    /* application to receive copies of the multicast datagrams. */

    {

    int reuse = 1;

    if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)

    {

    perror("Setting SO_REUSEADDR error");

    close(sd);

    exit(1);

    }

    else

    printf("Setting SO_REUSEADDR...OK.\n");

    }

     

    /* Bind to the proper port number with the IP address */

    /* specified as INADDR_ANY. */

    memset((char *) &localSock, 0, sizeof(localSock));

    localSock.sin_family = AF_INET;

    localSock.sin_port = htons(4321);

    localSock.sin_addr.s_addr = INADDR_ANY;

    if(bind(sd, (struct sockaddr*)&localSock, sizeof(localSock)))

    {

    perror("Binding datagram socket error");

    close(sd);

    exit(1);

    }

    else

    printf("Binding datagram socket...OK.\n");

     

    /* Join the multicast group 226.1.1.1 on the local 203.106.93.94 */

    /* interface. Note that this IP_ADD_MEMBERSHIP option must be */

    /* called for each local interface over which the multicast */

    /* datagrams are to be received. */

    group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");

    group.imr_interface.s_addr = inet_addr("203.106.93.94");

    if(setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)

    {

    perror("Adding multicast group error");

    close(sd);

    exit(1);

    }

    else

    printf("Adding multicast group...OK.\n");

     

    /* Read from the socket. */

    datalen = sizeof(databuf);

    if(read(sd, databuf, datalen) < 0)

    {

    perror("Reading datagram message error");

    close(sd);

    exit(1);

    }

    else

    {

    printf("Reading datagram message...OK.\n");

    printf("The message from multicast server is: \"%s\"\n", databuf);

    }

    return 0;

    }
