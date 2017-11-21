
//extern void (*TMR0_InterruptHandler)(void);


void mqttSetupT();
void MqttMessageArived(void);
void setMqttMessageArivedHandler(void (* mqttMessageArivedHandler)(void));