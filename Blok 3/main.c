#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) // Error handling
{
    perror(msg);
    exit(0);
}

char com_digit(const char *buffer) { // Súčet prvých 5 číslic AIS ID modulo 6. číslo
    int sum = 0;
    for (int i = 0; i< 5; i++) {
        sum += buffer[i] - '0';
    }
    sum = sum % (buffer[5]-'0');
    return sum + '0';
}

int is_prime(int num) { // Funkcia vypočíta či číslo je prvočíslo
    if (num == 1) return 0;
    if (num == 2) return 1;
    for (int i = 2; i < num; i++) {
        if (num%i == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n; // Socket a port
    struct sockaddr_in serv_addr;
    struct hostent *server;
    FILE * fp;
    fp = fopen("output.txt", "w"); // Zapisovanie outputu

    char buffer[256]; // Buffer pre ziskanie packetu
    if (argc < 3) { // Málo argumentov pre pripojenie
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]); // Argument 3 je port
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // Otvorenie socketu
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) { // Zlá IP
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    for (int i = 0; i < 2; i++) { // Prvé pripojenie a AIS ID
    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);

    n = write(sockfd, buffer, strlen(buffer)); // Poslanie packety serveru
    if (n < 0)
        error("ERROR writing to socket");
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
        error("ERROR reading from socket");
    char *p = strchr(buffer, '\n'); // Zistí či sa končí správa newline charakterom
    if (p == NULL) {
        strcat(buffer, "\0");
    } else *p = '\0';
    fprintf(fp, "MORPHEUS: %s", buffer);
    printf("%s\n\n", buffer); } // Výpis pre server

    // Nepodstatná správa
    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    int do_again;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            strcat(buffer, "\0");
            do_again = 1;
        } else {
            *p = '\0';
            do_again = 0;
        }
        char temp = buffer[0];
        int i = 0;
        while (temp != '\0') {
            printf("%c", temp);
            i++;
            temp = buffer[i];
            usleep(10000);
            fflush(stdout);
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Farbičky BLUE (me) vs GREEN (server)
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            strcat(buffer, "\0");
            do_again = 1;
        } else {
            *p = '\0';
            do_again = 0;
        }
        char temp = buffer[0];
        int i = 0;
        while (temp != '\0') {
            printf("\x1B[32m" "%c", temp);
            i++;
            temp = buffer[i];
            usleep(10000);
            fflush(stdout);
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Písanie charakter po charakteru
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            strcat(buffer, "\0");
            do_again = 1;
        } else {
            *p = '\0';
            do_again = 0;
        }
        char temp = buffer[0];
        int i = 0;
        while (temp != '\0') {
            printf("\x1B[32m" "%c", temp);
            i++;
            temp = buffer[i];
            usleep(10000);
            fflush(stdout);
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Vypočítanie čísla podľa AIS ID
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    char foo = com_digit(buffer);
    buffer[0] = foo;
    buffer[1] = '\0';
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    int j = 0, k = 0;
    char tmp[999];
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Ľavá (me) vs Pravá (server)
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Šifrovaná správa XOR 55
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        for (int g = 0; g < 148; g++) {
            buffer[g] = buffer[g]^55;
        }
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Nepodstatná správa
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // X súradnica
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Y súradnica
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Pozri sa na google maps a zisti kde si formát X.Y.
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Napíš string PRIMENUMBER a pokračuj
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Vráť string s charaktermi na indexoch, ktoré sú prvočísla
    printf("\x1B[34m" "Please enter the message: \n");
    char tmp_buffer[256];
    bzero(tmp_buffer, 256); // Temporary buffer na charakteri
    for (int g = 0, bar = 0; buffer[g] != '\0'; g++) {
        if (is_prime(g+1)) {
            tmp_buffer[bar] = buffer[g];
            bar++;
        }
    }
    fprintf(fp, "NEO: %s", tmp_buffer);
    n = write(sockfd, tmp_buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Napíš string Trinity
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Trivia - baud rate
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    // Trivia - 32
    printf("\x1B[34m" "Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    fprintf(fp, "\n\nNEO: %s", buffer);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    printf("%-40c ", ' ');
    j = 0, k = 0;
    do {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        char *p = strchr(buffer, '\n');
        if (p == NULL) {
            do_again = 1;
        } else {
            *p = ' ';
            do_again = 0;
        }
        strcat(buffer, "\0");
        char temp = buffer[0];
        bzero(tmp, 999);
        int i = 0;
        while (temp != '\0') {
            if (temp == ' ') {
                tmp[k] = '\0';
                int x = 0;
                while (tmp[x] != '\0') {
                    printf("\x1B[32m" "%c", tmp[x]);
                    usleep(10000);
                    fflush(stdout);
                    x++;
                }
                k = 0;
            }
            i++;
            if (j > 39) {
                printf("\n");
                printf("%-40c", ' ');
                j = 0;
            } else j++;
            tmp[k] = temp;
            k++;
            temp = buffer[i];
        }
        fprintf(fp, "MORPHEUS: %s", buffer);
    } while (do_again);
    printf("\n\n");

    fclose(fp); // Zavri zapisovací súbor
    close(sockfd); // Zavri socket
    return 0;
}
