CC=cc
CFLAGS=-O -I../..
AR=libtool
AR_FLAGS=-o


UNZ_OBJS = miniunz.o unzip.o ioapi.o ../../libz.a
ZIP_OBJS = minizip.o zip.o   ioapi.o ../../libz.a

UNZ_LIB = libunz.a

.c.o:
	$(CC) -c $(CFLAGS) $*.c

all: miniunz minizip $(UNZ_LIB)

$(UNZ_LIB): $(UNZ_OBJS)
	$(AR) $(AR_FLAGS) $@ $(UNZ_OBJS)

miniunz:  $(UNZ_OBJS)
	$(CC) $(CFLAGS) -o $@ $(UNZ_OBJS)

minizip:  $(ZIP_OBJS)
	$(CC) $(CFLAGS) -o $@ $(ZIP_OBJS)

test:	miniunz minizip
	./minizip test readme.txt
	./miniunz -l test.zip
	mv readme.txt readme.old
	./miniunz test.zip

clean:
	/bin/rm -f *.o *~ minizip miniunz $(UNZ_LIB)
