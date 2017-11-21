#include "mqttLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <MQTTClient.h>
#include "./timeStr.h"


static MQTTClient client;
static MQTTClient_connectOptions conn_opts;
static MQTTClient_message pubmsg;
static MQTTClient_deliveryToken token;

static const char* serverAdress;
static const char* clientID;
static int qos;
static long timeOut;

static void priv_connlost(void *context, char *cause);
static int  priv_msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
static void priv_delivered(void *context, MQTTClient_deliveryToken dt);

volatile MQTTClient_deliveryToken deliveredtoken;


void (*mqttOnConnectedHandeler)	     (void);
void (*mqttOnConnectionLostHandeler) (char *cause);
int  (*mqttOnMessageArivedHandeler ) (void *context, char *topicName, int topicLen, MQTTClient_message *message);
void (*mqttOnMessageDelivertHandeler)(void *context, MQTTClient_deliveryToken dt);
void mqttHandlerDefault(void);
void mqttArivedHandlerDefault();
void mqttArivedHandlerDefault();
void mqttArivedHandlerDefault();

int  my_mqttSetup(const char* serverAdress_setup, const char* clientID_setup, int qos_setup, long timeOut_setup)
{

	serverAdress=serverAdress_setup;
	clientID=clientID_setup;
	qos=qos_setup;
	timeOut=timeOut_setup;

    MQTTClient_connectOptions conn_opts_temp = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg_temp = MQTTClient_message_initializer;

	conn_opts=conn_opts_temp;
	pubmsg=pubmsg_temp;

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
	
	MQTTClient_create		(&client, serverAdress, clientID, MQTTCLIENT_PERSISTENCE_NONE, NULL);    // https://goo.gl/YQeMNQ
	MQTTClient_setCallbacks (client, NULL , priv_connlost, priv_msgarrvd, priv_delivered);					         // https://goo.gl/qT8zb7

	my_mqttSetOnConnectionLostHandeler(my_mqttAutoReconnect);
	//my_mqttSetOnConnectedHandeler(mqttHandlerDefault);
	// my_mqttSetOnConnectionLostHandeler(my_mqttAutoReconnect);
	// my_mqttSetOnMessageArivedHandeler(mqttArivedHandlerDefault);
	// my_mqttSetOnMessageDelivertHandeler(mqttHandlerDefault);
}
int my_mqttConnect()
{
	int rc = 0;
	if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        
    }
	else
	{
		if(mqttOnConnectedHandeler)
		{
			mqttOnConnectedHandeler();
		}

	}
		
	return rc;
}
void my_mqttDisconnect()
{
	MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
}
int my_mqttSendMessage(char* payload, const char* topic, int payload_size)
{
	int rc = 0;

	pubmsg.payload = payload;
    pubmsg.payloadlen = payload_size;
    pubmsg.qos = qos;
	pubmsg.retained = 0;
	MQTTClient_publishMessage(client, topic, &pubmsg, &token);
	
    return rc;
}
void my_mqttSubscribe(const char* topic)
{
	MQTTClient_subscribe(client, topic, qos);
}




void my_mqttSetOnConnectedHandeler		(void (* my_mqttHandler)(void))
{
	mqttOnConnectedHandeler=my_mqttHandler;
}
void my_mqttSetOnConnectionLostHandeler (void (* my_mqttHandler)(char *cause))
{
	mqttOnConnectionLostHandeler=my_mqttHandler;
}
void my_mqttSetOnMessageArivedHandeler  (int (* my_mqttHandler)(void *context, char *topicName, int topicLen, MQTTClient_message *message))
{
	mqttOnMessageArivedHandeler=my_mqttHandler;
}
void my_mqttSetOnMessageDelivertHandeler(void (* my_mqttHandler)(void *context, MQTTClient_deliveryToken dt))
{
	mqttOnMessageDelivertHandeler=my_mqttHandler;
}

void mqttHandlerDefault(void)
{

}
void mqttArivedHandlerDefault(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{

}
void my_mqttAutoReconnect(char *cause)
{
	int x=0;
	int rc=0;
	
	// struct MQTT_ALL_S *ccc;
	
	// ccc = (struct MQTT_ALL_S*) context;
	
	//while (MQTTCLIENT_SUCCESS!= mqttConnect((ccc->conn_opts), (ccc->pubmsg), (ccc->client), (ccc->token )));

	while (MQTTCLIENT_SUCCESS != my_mqttConnect()){
		printf("try reconn\n");
		sleep(1);
	}
	printf("connection fully regaint at %s\n",getTimeString());
	my_mqttSubscribe("hng12/kg/verteiler/home8");

}
	




//-------------------------------------------------------------
// privat functions






static void priv_connlost(void *context, char *cause)
{
	printf("Connection lost: cause: %s | at %s\n", cause, getTimeString());
	//my_mqttAutoReconnect();
	
	if(mqttOnConnectionLostHandeler)
    {
        mqttOnConnectionLostHandeler(cause);
    }
	
}
static int  priv_msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
	
	if(mqttOnMessageArivedHandeler)
    {
        mqttOnMessageArivedHandeler(context,topicName,topicLen,message);
    }
	
}
static void priv_delivered(void *context, MQTTClient_deliveryToken dt)
{
	if(mqttOnMessageDelivertHandeler)
    {
        mqttOnMessageDelivertHandeler(context, dt);
    }


}