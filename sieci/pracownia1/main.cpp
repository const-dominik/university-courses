#include <iostream>
#ifdef _WIN32
    #include <Winsock2.h>
    #include <Ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    #define close closesocket
#else
    #include <arpa/inet.h>
    #include <netinet/ip_icmp.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
#endif

void send_icmp_request(const char *dest_ip) {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;

    if (inet_pton(AF_INET, dest_ip, &(dest_addr.sin_addr)) <= 0) {
        perror("inet_pton");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Create ICMP Echo Request packet
    struct icmphdr icmp_header;
    icmp_header.type = ICMP_ECHO;
    icmp_header.code = 0;
    icmp_header.un.echo.id = htons(getpid());
    icmp_header.un.echo.sequence = htons(1);
    icmp_header.checksum = 0; // Checksum is initially set to 0

    // Calculate ICMP checksum
    icmp_header.checksum = compute_icmp_checksum(&icmp_header, sizeof(icmp_header));

    // Send the packet
    if (sendto(sockfd, &icmp_header, sizeof(icmp_header), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    std::cout << "ICMP Echo Request sent to " << dest_ip << std::endl;

    close(sockfd);
}