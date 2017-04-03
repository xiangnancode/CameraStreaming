objects = INIReaderTest.o INIReader.o ini.o

CFLAG = -c -O2 -Wall -DHI_OS_LINUX -lpthread

proj: INIReaderTest.o INIReader.o ini.o 
	g++ -m32 -o test INIReaderTest.o INIReader.o ini.o


INIReaderTest.o: INIReaderTest.cpp INIReader.h 
	g++ -m32 -std=c++0x -c INIReaderTest.cpp

INIReader.o: INIReader.cpp INIReader.h ini.h
	g++ -m32 -c INIReader.cpp

ini.o: ini.c ini.h
	g++ -m32 -c ini.c

clean:
	rm proj *.o
