EXTRA_FLAG=-DJVM_DEBUG

CC=g++
CFLAGS=-c -Wall --std=c++11 -g $(EXTRA_FLAG)
LDFLAGS=

EXECUTABLE=jvm

SOURCES=class.cc           \
        class_loader.cc    \
        jvm.cc             \
        utils.cc           \


OBJECTS=$(SOURCES:.cc=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cc %.h $(EXTRA_HEADERS)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS)
