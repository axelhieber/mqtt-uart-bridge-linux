#MQTTLIB_C = paho-mqtt3c <---!
#MQTTLIB_CS = paho-mqtt3cs
#MQTTLIB_A = paho-mqtt3a
#MQTTLIB_AS = paho-mqtt3as
.PHONY: clean  


prog: ./build/main.o ./build/timeStr.o ./build/mqttLib.o	
	gcc -Wall -Wextra  -o ./mqqtbridge ./build/main.o ./build/timeStr.o ./build/mqttLib.o -l paho-mqtt3c

install:
	rm ../../mqqtbridge
	cp ./mqqtbridge ../../mqqtbridge
	chmod 777 ../../mqqtbridge
	
all: 
	make main.o
	make timeStr.o
	make prog
	./mqqtbridge
	
  
clean:
	make main.o
	make timeStr.o
	make uartLib.o
	make mqttLib.o
	make mqttLib.o
	
	
run:
	make
	./mqqtbridge
	
timeStr.o: ./lib/timeStr.c
	gcc -c -o ./build/timeStr.o ./lib/timeStr.c	
	
main.o: main.c
	
	gcc -c -o ./build/main.o ./main.c
	
uartLib.o: ./lib/uartLib.c
	gcc -c -o ./build/uartLib.o ./lib/uartLib.c
	
mqttLib.o: ./lib/mqttLib.c
	gcc -c -o ./build/mqttLib.o ./lib/mqttLib.c
	
test.o: ./lib/test.c
	gcc -c -o ./build/test.o ./lib/test.c
	
	
	
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	