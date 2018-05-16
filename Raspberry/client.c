// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT 1234
#define IPADRESS "192.168.1.26"

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    int gyro=0;
    char text[10];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, IPADRESS , &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    /**
     * OYUNU SIMULE EDEBILMEK ICIN GYRO DEGERINI 0 DAN 50 YE KADAR SANIYE DE 5 ER 5 ER
     * ARTIRIYORUZ. BUNU SERVER A GONDERIP SERVER MESAJINI EKRANA YAZDIRIYORUZ.
     */
    for(int i=0;i<10;i++){
        gyro +=5;
        sprintf(text, "%d", gyro);
        send(sock , text , strlen(text) , 0 );
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        sleep(1);
    }

    
    return 0;
}