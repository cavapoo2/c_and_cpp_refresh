CC=g++
INCLUDE=-I/usr/include/i386-linux-gnu
LIBS=-lcurl
CFLAGS=-c -Wall -std=c++2a $(INCLUDE)
LDFLAGS=-lcurl
SOURCES=main.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=simpcurl

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -rf *.o ${EXECUTABLE}	
