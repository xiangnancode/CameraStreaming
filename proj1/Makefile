hiheaders = hi_type.h hi_net_dev_errors.h hi_net_dev_sdk.h

CFLAG = -c -O2 -Wall -DHI_OS_LINUX -lpthread

proj: main.o INIReader.o ini.o 
	g++ -m32 -o proj -L. main.o INIReader.o ini.o -lNetLib

main.o: main.cpp ${hiheaders}
	g++ -m32 -std=c++0x ${CFLAG} main.cpp

INIReader.o: INIReader.cpp INIReader.h ini.h
	g++ -m32 -c INIReader.cpp

ini.o: ini.c ini.h
	g++ -m32 -c ini.c

clean:
	rm proj *.o
