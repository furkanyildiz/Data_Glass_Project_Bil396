#include <arpa/inet.h>
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
#include "oled.h"
#define PORT 8081
#define IPADRESS "192.168.43.72"
#include <pthread.h>

int sock = 0;
void *readSocket(void *vargp)
{
	int numBytesRcvd;
	char buffer[50] = {0};
	char * readed ;
    while(1){
		
		numBytesRcvd = recv(sock , buffer, 50,0);
		buffer[numBytesRcvd] = '\0';
		readed = strtok(buffer, "\n");
		fprintf(stderr,"serverdan okunan: %s\n",readed );
		//usleep(1);
		
	}
}
void *writeSocket(void *vargp)
{
	int rand_;
	char text[10];

    while(1){
		
		
		rand_ = rand()%50;
		//fprintf(stderr,"%d",rand_);
		sprintf(text, "%d\n", rand_);
		send(sock , text , strlen(text) , 0 );
		//usleep(1);

	}
}

int main(int argc, char **argv)
{
    struct sockaddr_in address;
    int valread;
    struct sockaddr_in serv_addr;
    char buffer[50] = {0};
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
	fd = wiringPiI2CSetup (0x69);
	wiringPiI2CWriteReg8 (fd,0x6B,0x00);//disable sleep mode

	parse_args(argc, argv);

	// SPI
	if (display.oled_is_spi_proto(opts.oled))
	{
		// SPI change parameters to fit to your LCD
		if ( !display.init(OLED_SPI_DC,OLED_SPI_RESET,OLED_SPI_CS, opts.oled) )
			exit(EXIT_FAILURE);
	}
	else
	{
		// I2C change parameters to fit to your LCD
		if ( !display.init(OLED_I2C_RESET,opts.oled) )
			exit(EXIT_FAILURE);
	}

	display.begin();
	
	double x_rotation=0.0;
	double y_rotation=0.0;
	int x_to_gyro=0;
	
	  // init done
	  display.clearDisplay();   // clears the screen and buffer
	  

    fprintf(stderr,"deneme");
	int balanced_gyro;
	srand(time(NULL));  
	
	int flag_second_ball; //if second ball in game its 1, otherwise its 0.
	int second_ball_x;
	int second_ball_y;
	int flag_token;      //if token in game its 1, otherwise its 0.
	int token_x;
	int token_y;
	int flag_block;      //iki topun çıkması için bulunan duvar
	int block_x;
	int block_y;
    int numBytesRcvd;
    
    pthread_t thread_id_read,thread_id_write;
	pthread_create(&thread_id_write, NULL, writeSocket, NULL);
	pthread_create(&thread_id_read, NULL, readSocket, NULL);

    pthread_join(thread_id_write, NULL);
	pthread_join(thread_id_read, NULL);

    printf("After Thread\n");
    exit(0);

    
    /*
	while(1){

		//acclX = read_word_2c(0x3B);
		//balanced_gyro = calculate_gyro(acclX);
		balanced_gyro = rand();
		fprintf(stderr,"%d",balanced_gyro);



		sprintf(text, "%d", balanced_gyro);
		send(sock , text , strlen(text) , 0 );
		//numBytesRcvd = read( sock , buffer, 50);
		numBytesRcvd = recv(sock , buffer, 50,0);
		buffer[numBytesRcvd] = '\0';
		//fprintf(stderr,"size: %d\n",numBytesRcvd );
		fprintf(stderr,"serverdan okunan: %s\n",buffer );
*/


/*
		buffer[numBytesRcvd] = '\0';
		if (numBytesRcvd > 0){
			fprintf(stderr,"serverdan okunan: %s\n",buffer );


			char * token = strtok(buffer, ";");
			other_gyro = atoi(token);
			token = strtok(NULL, ";");
			topx = atoi(token);
			token = strtok(NULL, ";");       
			topy = atoi(token);
			token = strtok(NULL, ";");  

			flag_second_ball = atoi(token);
			token = strtok(NULL, ";");  

			second_ball_x = atoi(token);
			token = strtok(NULL, ";");  

			second_ball_y = atoi(token);
			token = strtok(NULL, ";");  

			flag_token = atoi(token);
			token = strtok(NULL, ";");  

			token_x = atoi(token);
			token = strtok(NULL, ";");  

			token_y = atoi(token);
			token = strtok(NULL, ";");  

			flag_block = atoi(token);
			token = strtok(NULL, ";");  

			block_x = atoi(token);
			token = strtok(NULL, ";");  

			block_y = atoi(token);
			token = strtok(NULL, ";");  	    

			display.clearDisplay();
			display.fillCircle(topy, topx, 2, WHITE);
			display.drawFastVLine(2, balanced_gyro, 15, WHITE);
			display.drawFastVLine(126, other_gyro, 15, WHITE);
			display.drawRect(0,0,128,64,WHITE);
			display.display();
			//delay(1);

		}*/
    //}

/*
	// draw a single pixel
	display.drawPixel(10, 10, WHITE);
	display.display();
	sleep(2);
	display.clearDisplay();
  
	*/
  

	// Free PI GPIO ports
	display.close();
}
