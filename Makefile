#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= schultz4

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14

RM= /bin/rm -f

all: characterserver testclient namelookupclient PutCGI PutHTML

#Compiles Files

fifo.o:	fifo.cpp fifo.h
	$(CC) fifo.cpp -c

testclient.o: testclient.cpp fifo.h
	$(CC) $(CFLAGS) testclient.cpp -c

CharacterProfile.o: CharacterProfile.cpp CharacterProfile.h
	$(CC) $(CFLAGS) CharacterProfile.cpp -c

CharacterNameMap.o: CharacterNameMap.cpp CharacterNameMap.h
	$(CC) $(CFLAGS) CharacterNameMap.cpp -c
	
CharacterYearMap.o: CharacterYearMap.cpp CharacterYearMap.h
	$(CC) $(CFLAGS) CharacterYearMap.cpp -c

main.o: main.cpp fifo.h CharacterNameMap.h CharacterYearMap.h CharacterProfile.h
	$(CC) $(CFLAGS) main.cpp -c

namelookupclient.o: namelookupclient.cpp fifo.h
	$(CC) $(CFLAGS) namelookupclient.cpp -c

#Links Files

testclient: testclient.o fifo.o
	$(CC) testclient.o fifo.o -o testclient

characterserver: main.o fifo.o CharacterProfile.o CharacterNameMap.o CharacterYearMap.o
	$(CC) main.o CharacterProfile.o CharacterNameMap.o CharacterYearMap.o fifo.o -o characterserver

namelookupclient: namelookupclient.o  fifo.h
	$(CC) namelookupclient.o  fifo.o -o namelookupclient -L/usr/local/lib -lcgicc

#Puts files into directories

PutCGI: namelookupclient
	chmod 757 namelookupclient
	cp namelookupclient /usr/lib/cgi-bin/$(USER)_namelookupclient.cgi 

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp namelookupCS.html /var/www/html/class/softdev/$(USER)/Names/
	cp namelookupCS.css /var/www/html/class/softdev/$(USER)/Names/
	cp namelookupCS.js /var/www/html/class/softdev/$(USER)/Names/

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)/Names/

clean:
	rm -f *.o namelookupclient nameserver testclient
