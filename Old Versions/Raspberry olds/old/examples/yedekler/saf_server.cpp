#include <arpa/inet.h>
#include <wiringPi.h>
#include <stdio.h>
#include <math.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include <getopt.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 8081
#define IPADRESS "192.168.1.42"


int main(int argc, char **argv)
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    int gyro=0;
    char text[10];
	int other_gyro = 0;
	int topx = 0;
    int topy = 0;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("ERROR opening socket");
        return -1;
    }
    
	//fcntl(sock,F_SETFL,O_NONBLOCK);
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    int f = inet_pton(AF_INET, IPADRESS , &serv_addr.sin_addr);
    if(f<=0)
    {
        perror("Invalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection Failed \n");
        return -1;
    }
	int i;
	
	
	double x_rotation=0.0;
	double y_rotation=0.0;
	int x_to_gyro=0;

    fprintf(stderr,"deneme");
	int balanced_gyro;
	srand(time(NULL));  

    while(1){

		//acclX = read_word_2c(0x3B);
		//balanced_gyro = calculate_gyro(acclX);
		balanced_gyro = rand();
		
		


        sprintf(text, "%d", balanced_gyro);
        send(sock , text , strlen(text) , 0 );
        valread = read( sock , buffer, 1024);
        fprintf(stderr,"serverdan okunan: %s\n",buffer );


		/*


        //split string

        char * token = strtok(buffer, ";");
        other_gyro = atoi(token);
        token = strtok(NULL, ";");
		topx = atoi(token);
        token = strtok(NULL, ";");       
        topy = atoi(token);
        token = strtok(NULL, ";");  
        
		display.clearDisplay();
		display.fillCircle(topy, topx, 2, WHITE);
		display.drawFastVLine(0, balanced_gyro, 15, WHITE);
		display.display();
		delay(1);
        */
        
        /*
        while (token != NULL){
            fprintf(stderr,"%d\n", atoi(token));
            token = strtok(NULL, ";");
        }

*/



    }

/*
	// draw a single pixel
	display.drawPixel(10, 10, WHITE);

	display.display();
	sleep(2);
	display.clearDisplay();
  
	*/
  

	// Free PI GPIO ports
	//display.close();

}
