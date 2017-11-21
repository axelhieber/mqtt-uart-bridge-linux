#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "./lib/timeStr.h"
#include "./lib/mqttLib.h"
/*********************************************************/
/*********************************************************/
/*                    UART INCLUDE/DEFINE                */

#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <errno.h>  /* ERROR Number Definitions          */
#include <unistd.h>
#include <sys/types.h>
#include <sys/signal.h>

 #define BAUDRATE B9600
 #define MODEMDEVICE "/dev/ttyS1"
 #define _POSIX_SOURCE 1 /* POSIX compliant source */
 #define FALSE 0
 #define TRUE 1
        
		
		
 volatile int STOP=FALSE; 
 void signal_handler_IO (int status);   /* definition of signal handler */
 int  wait_flag=TRUE;  
 
 

#define ADDRESS     "tcp://10.0.7.1:1883"
#define CLIENTID    "hng12/kg/verteiler/home8"
#define TOPIC       "hng12/kg/verteiler/home8"
#define TOPIC_IN    "hng12/kg/verteiler/home8"
#define TOPIC_OUT   "hng12/kg/verteiler/home8"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

volatile MQTTClient_deliveryToken deliveredtoken;

struct termios SerialPortSettings;
char write_buffer[] = "Hallo";
int  bytes_written  =  0 ;
int fd;

int c, res;
struct termios oldtio,newtio;
char buf[512];
struct sigaction saio;           /* definition of signal action */
		
int rc;
int ch;

	
	
		
		
		
		
void uartConnect();
void uartSetup();
void uartDisconnect();

void testPrint();




void delivered(void *context, MQTTClient_deliveryToken dt)
{
   // printf("Message %d\n", dt);
    deliveredtoken = dt;
}
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
	char write_buf[256] = "";
    char* payloadptr;
	printf(";");
    payloadptr = message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr);
		strncat(write_buf,payloadptr,1);
		payloadptr++;
    }

	printf(" MQTT %s",getTimeString());
	printf("\n");
	fflush(stdout);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
	//bytes_written = write(fd,write_buffer,sizeof(write_buffer));
	bytes_written = write(fd,write_buf,i);
	tcflush(fd, TCIFLUSH);

    return 1;
}

int main(int argc, char* argv[])
{
	const char* serverAdresse=	"tcp://10.0.7.1:1883";
	const char* clientID		="mqtt1";
	
	int  		qos				=1;
	int 		timeout			=1000L;
	

	my_mqttSetup(serverAdresse,clientID,qos,timeout);
	my_mqttSetOnMessageArivedHandeler(msgarrvd);
	my_mqttSetOnMessageDelivertHandeler(delivered);
	
	rc=my_mqttConnect();
	if(rc != MQTTCLIENT_SUCCESS)
		exit(EXIT_FAILURE);	
	
	my_mqttSubscribe(TOPIC);
	my_mqttSendMessage("hallo","MQTT Examples",sizeof("Hello World!"));
	
	

    uartConnect();

	
		
	printf("....\n");

	/* loop while waiting for input. normally we would do something useful here */ 
	while (STOP==FALSE) {
        /* after receiving SIGIO, wait_flag = FALSE, input is available and can be read */
        if (wait_flag==FALSE) { 
			res = read(fd,buf,255);
			if(res<=0)
			{
				//printf("Error reading serial\n");
				continue;
			}
			buf[res-1]=0;
			printf(":%s", buf);
			my_mqttSendMessage(buf,TOPIC ,strlen(buf));
			printf(" MQTT %s\n",getTimeString());
			fflush(stdout);
			memchr(buf,'\0',sizeof(buf)); /*clear buffer*/
			wait_flag = TRUE;      /* wait for new input */
		}
	}

	 
    tcsetattr(fd,TCSANOW,&oldtio);







    my_mqttDisconnect();
    return rc;
}


      /***************************************************************************
      * signal handler. sets wait_flag to FALSE, to indicate above loop that     *
      * characters have been received.                                           *
      ***************************************************************************/
        
      void signal_handler_IO (int status)
      {
		static int first =1;
        //printf("received SIGIO signal.\n");
		if(first==1)
		{
			first=0;
		}
		else
		{
			wait_flag = FALSE;
		}
      }
	  
	  
void uartConnect()
{
	    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY ); 
        if (fd <0) {perror(MODEMDEVICE); exit(-1); }
        
		/* install the signal handler before making the device asynchronous */
        saio.sa_handler = signal_handler_IO;
        //saio.sa_mask = 0;
        saio.sa_flags = 0;
        saio.sa_restorer = NULL;
        sigaction(SIGIO,&saio,NULL);
          
        /* allow the process to receive SIGIO */
        fcntl(fd, F_SETOWN, getpid());
        /* Make the file descriptor asynchronous (the manual page says only 
           O_APPEND and O_NONBLOCK, will work with F_SETFL...) */
        fcntl(fd, F_SETFL, FASYNC);
		
        tcgetattr(fd,&oldtio); /* save current port settings */
        
        bzero(&newtio, sizeof(newtio));
		cfsetispeed(&newtio,B9600); //cfsetispeed() for setting the input speed or read speed and
		cfsetospeed(&newtio,B9600); //cfsetospeed() for setting the output speed or write speed.
        //newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
        newtio.c_iflag = IGNPAR;
		//newtio.c_cflag &= ~PARENB;  // No Parity
		//newtio.c_cflag &= ~CSTOPB; //Stop bits = 1
		//newtio.c_cflag &= ~CRTSCTS; //Turn off hardware based flow control (RTS/CTS).
		newtio.c_cflag = BAUDRATE |CREAD | CLOCAL | CS8 | CRTSCTS; //Turn on the receiver of the serial port (CREAD),other wise reading from the serial port will not wo
        //newtio.c_oflag = 0;
		newtio.c_iflag &= ~(IXON | IXOFF | IXANY); //Turn off software based flow control (XON/XOFF).
		newtio.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); //NON Cannonical mode is recommended.
        
        /* set input mode (non-canonical, no echo,...) */
        newtio.c_lflag = ICANON;
         
        newtio.c_cc[VTIME]    = 2;   /* inter-character timer unused */ //VTIME is time measured in 0.1 second intervals
        newtio.c_cc[VMIN]     = 1;   /* blocking read until 5 chars received */
        
        tcflush(fd, TCIFLUSH);
        tcsetattr(fd,TCSANOW,&newtio);
}
	  
	




/*SOURCES*/
//http://xanthium.in/Serial-Port-Programming-on-Linux
//http://tldp.org/HOWTO/Serial-Programming-HOWTO/x115.html#AEN144
