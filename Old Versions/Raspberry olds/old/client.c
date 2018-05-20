// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT 8081
#define IPADRESS "192.168.1.34"

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    int gyro=0;
    char text[10];

    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("ERROR opening socket");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, IPADRESS , &serv_addr.sin_addr)<=0) 
    {
        perror("Invalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection Failed \n");
        return -1;
    }
    
    /**
     * OYUNU SIMULE EDEBILMEK ICIN GYRO DEGERINI 0 DAN 50 YE KADAR SANIYE DE 5 ER 5 ER
     * ARTIRIYORUZ. BUNU SERVER A GONDERIP SERVER MESAJINI EKRANA YAZDIRIYORUZ.
     */
    while(1){
        gyro +=2;
        gyro= gyro%50;
        sprintf(text, "%d", gyro);
        send(sock , text , strlen(text) , 0 );
        valread = read( sock , buffer, 1024);
        fprintf(stderr,"serverdan okunan: %s\n",buffer );

        //split string

        fprintf(stderr,"%d\n", atoi(token));
        while (token != NULL){
            fprintf(stderr,"%d\n", atoi(token));
            token = strtok(NULL, ";");
        }

    }

    
    return 0;
}