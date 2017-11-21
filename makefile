#MQTTLIB_C = paho-mqtt3c <---!
#MQTTLIB_CS = paho-mqtt3cs
#MQTTLIB_A = paho-mqtt3a
#MQTTLIB_AS = paho-mqtt3as

prog: main.o timeStr.o mqttLib.o	
	gcc -Wall -Wextra  -o mqqtbridge main.o timeStr.o mqttLib.o -l paho-mqtt3c

all: 
	make main15.o
	make timeStr.o
	make prog
	./mqqtbridge
	
run:
	make
	./mqqtbridge
	
timeStr.o: ./lib/timeStr.c
	gcc -c  ./lib/timeStr.c	
	
main15.o: main.c
	gcc -c  main.c
	
uartLib.o: ./lib/uartLib.c
	gcc -c  ./lib/uartLib.c
	
mqttLib.o: ./lib/mqttLib.c
	gcc -c  ./lib/mqttLib.c
	
test.o: ./lib/test.c
	gcc -c  ./lib/test.c
	
	
	
	
	
	
	
	
	

progg: main2.c
	gcc -o main2 main2.c  -l paho-mqtt3ac

main3: main3.c
	gcc -o main3 main3.c

main4: main4.c
	gcc -o main4 main4.c  -l paho-mqtt3as

main5: main5.c
	gcc -o main5 main5.c  -l paho-mqtt3c
main6: main6.c
	gcc -o main main6.c  -l paho-mqtt3c
main7: main7.c
	gcc -o main7 main7.c -l paho-mqtt3c
main8: main8.c
	gcc -o main8 main8.c 
main9: main9.c
	gcc -o main9 main9.c 
main10: main10.c
	gcc -o main10 main10.c  -l paho-mqtt3c

main11: main11.c
	gcc -o main11 main11.c  -l paho-mqtt3c

	
main12: main12.c
	gcc -o main12 main12.c  -l paho-mqtt3c
		
main13: main13.c
	gcc -o main13 main13.c  -l paho-mqtt3c
	
main14: main14.c
	gcc -o main14 main14.c  -l paho-mqtt3c
	
main15: main15.c
	gcc -o main15 main15.c  -l paho-mqtt3c	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	