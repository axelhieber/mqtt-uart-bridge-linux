#include <MQTTClient.h>

int  my_mqttSetup(const char* serverAdress, const char* clientID, int qos, long timeOut);
int  my_mqttConnect();
void my_mqttDisconnect();
int  my_mqttSendMessage(char* payload, const char* topic, int payload_size);

void my_mqttSubscribe(const char* topic);

void my_mqttSetOnConnectedHandeler		(void (* my_mqttHandler)(void));
void my_mqttSetOnConnectionLostHandeler (void (* my_mqttHandler)(char *cause));
void my_mqttSetOnMessageArivedHandeler  (int  (* my_mqttHandler)(void *context, char *topicName, int topicLen, MQTTClient_message *message));
void my_mqttSetOnMessageDelivertHandeler(void (* my_mqttHandler)(void *context, MQTTClient_deliveryToken dt));


void my_mqttAutoReconnect(char *cause);

// void mqttReconnected();
// void mqttMessageArived();
// void mqttMessageDelivert();
// 


// extern void (*TMR0_InterruptHandler)(void);
 // void TMR0_SetInterruptHandler(void (* InterruptHandler)(void));
 