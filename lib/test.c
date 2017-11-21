
#include "test.h"

void (*mqttMessageArivedHandler)(void);

void mqttSetupT()
{
	 setMqttMessageArivedHandler(mqttMessageArivedHandler);
}

void MqttMessageArived(void)
{
	if(mqttMessageArivedHandler)
    {
        mqttMessageArivedHandler();
    }
}

void setMqttMessageArivedHandler(void (* ArivedHandler)(void))
{
	 mqttMessageArivedHandler = ArivedHandler;
}

void mqttMessageArivedDefaultHandler(void)
{
    // add your TMR0 interrupt custom code
    // or set custom function using TMR0_SetInterruptHandler()
}