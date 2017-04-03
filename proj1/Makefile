hiheaders = hi_type.h hi_net_dev_errors.h hi_net_dev_sdk.h getconfig.h

CFLAG = -c -O2 -Wall -DHI_OS_LINUX -lpthread

proj: main.o
	g++ -m32 -o proj -L. main.o -lNetLib

main.o: main.cpp ${hiheaders}
	g++ -m32 ${CFLAG} main.cpp

clean:
	rm proj *.o
