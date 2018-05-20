/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32|64 size display using SPI or I2C to communicate
4 or 5 pins are required to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution

02/18/2013 	Charles-Henri Hallard (http://hallard.me)
						Modified for compiling and use on Raspberry ArduiPi Board
						LCD size and connection are now passed as arguments on 
						the command line (no more #define on compilation needed)
						ArduiPi project documentation http://hallard.me/arduipi

						
*********************************************************************/
#include <arpa/inet.h>
#include "ArduiPi_SSD1306.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <wiringPiI2C.h>
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

#define PRG_NAME        "ssd1306_demo"
#define PRG_VERSION     "1.1"

#define PORT 8081
#define IPADRESS "192.168.1.42"

// Instantiate the display
Adafruit_SSD1306 display;

// Config Option
struct s_opts
{
	int oled;
	int verbose;
} ;

// default options values
s_opts opts = {
	OLED_ADAFRUIT_SPI_128x32,	// Default oled
  false										// Not verbose
};

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static unsigned char logo16_glcd_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };
  
  /*gyro variables and functions*/


int map(float s, float a1, float a2, float b1, float b2)
{
    return (int)(b1 + (s-a1)*(b2-b1)/(a2-a1));
}
int calculate_gyro(int non_processed_value){

    int deger = map(non_processed_value,-17000,17000,0,180);
    if(deger > 140)
        deger = 140;
    else if(deger < 40)
        deger = 40;
    int modulo = (deger - 40)/2;
    return modulo;
}


int fd;
int acclX, acclY, acclZ;
int gyroX, gyroY, gyroZ;
double acclX_scaled, acclY_scaled, acclZ_scaled;
double gyroX_scaled, gyroY_scaled, gyroZ_scaled;
 
int read_word_2c(int addr)
{
int val;
val = wiringPiI2CReadReg8(fd, addr);
val = val << 8;
val += wiringPiI2CReadReg8(fd, addr+1);
if (val >= 0x8000)
val = -(65536 - val);
 
return val;
}
 
double dist(double a, double b)
{
return sqrt((a*a) + (b*b));
}
 
double get_y_rotation(double x, double y, double z)
{
double radians;
radians = atan2(x, dist(y, z));
return -(radians * (180.0 / M_PI));
}
 
double get_x_rotation(double x, double y, double z)
{
double radians;
radians = atan2(y, dist(x, z));
return (radians * (180.0 / M_PI));
}

/*gyro variables and functions end.*/

void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
  srandom(666);     // whatever seed
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random() % display.width();
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random() % 5 + 1;
    
    printf("x: %d", icons[f][XPOS]);
    printf("y: %d", icons[f][YPOS]);
    printf("dy: %d\n", icons[f][DELTAY]);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, WHITE);
    }
    display.display();
    usleep(100000);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
	icons[f][XPOS] = random() % display.width();
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random() % 5 + 1;
      }
    }
   }
}





/* ======================================================================
Function: usage
Purpose : display usage
Input 	: program name
Output	: -
Comments: 
====================================================================== */
void usage( char * name)
{
	printf("%s\n", name );
	printf("Usage is: %s --oled type [options]\n", name);
	printf("  --<o>led type\nOLED type are:\n");
	for (int i=0; i<OLED_LAST_OLED;i++)
		printf("  %1d %s\n", i, oled_type_str[i]);
	
	printf("Options are:\n");
	printf("  --<v>erbose  : speak more to user\n");
	printf("  --<h>elp\n");
	printf("<?> indicates the equivalent short option.\n");
	printf("Short options are prefixed by \"-\" instead of by \"--\".\n");
	printf("Example :\n");
	printf( "%s -o 1 use a %s OLED\n\n", name, oled_type_str[1]);
	printf( "%s -o 4 -v use a %s OLED being verbose\n", name, oled_type_str[4]);
}


/* ======================================================================
Function: parse_args
Purpose : parse argument passed to the program
Input 	: -
Output	: -
Comments: 
====================================================================== */
void parse_args(int argc, char *argv[])
{
	static struct option longOptions[] =
	{
		{"oled"	  , required_argument,0, 'o'},
		{"verbose", no_argument,	  	0, 'v'},
		{"help"		, no_argument, 			0, 'h'},
		{0, 0, 0, 0}
	};

	int optionIndex = 0;
	int c;

	while (1) 
	{
		/* no default error messages printed. */
		opterr = 0;

    c = getopt_long(argc, argv, "vho:", longOptions, &optionIndex);

		if (c < 0)
			break;

		switch (c) 
		{
			case 'v': opts.verbose = true	;	break;

			case 'o':
				opts.oled = (int) atoi(optarg);
				
				if (opts.oled < 0 || opts.oled >= OLED_LAST_OLED )
				{
						fprintf(stderr, "--oled %d ignored must be 0 to %d.\n", opts.oled, OLED_LAST_OLED-1);
						fprintf(stderr, "--oled set to 0 now\n");
						opts.oled = 0;
				}
			break;

			case 'h':
				usage(argv[0]);
				exit(EXIT_SUCCESS);
			break;
			
			case '?':
			default:
				fprintf(stderr, "Unrecognized option.\n");
				fprintf(stderr, "Run with '--help'.\n");
				exit(EXIT_FAILURE);
		}
	} /* while */

	if (opts.verbose)
	{
		printf("%s v%s\n", PRG_NAME, PRG_VERSION);
		printf("-- OLED params -- \n");
		printf("Oled is    : %s\n", oled_type_str[opts.oled]);
		printf("-- Other Stuff -- \n");
		printf("verbose is : %s\n", opts.verbose? "yes" : "no");
		printf("\n");
	}	
}


/* ======================================================================
Function: main
Purpose : Main entry Point
Input 	: -
Output	: -
Comments: 
====================================================================== */
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
    
	fcntl(sock,F_SETFL,O_NONBLOCK);
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
	
	// Oled supported display in ArduiPi_SSD1306.h
	// Get OLED type
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
	  

    /**
     * OYUNU SIMULE EDEBILMEK ICIN GYRO DEGERINI 0 DAN 50 YE KADAR SANIYE DE 5 ER 5 ER
     * ARTIRIYORUZ. BUNU SERVER A GONDERIP SERVER MESAJINI EKRANA YAZDIRIYORUZ.
     */
    fprintf(stderr,"deneme");
	int balanced_gyro;
	srand(time(NULL));  

    while(1){

		acclX = read_word_2c(0x3B);
		balanced_gyro = calculate_gyro(acclX);
		//balanced_gyro = rand();
		
		


        sprintf(text, "%d", balanced_gyro);
        send(sock , text , strlen(text) , 0 );
        valread = read( sock , buffer, 1024);
        fprintf(stderr,"serverdan okunan: %s\n",buffer );


		


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
	display.close();

}
