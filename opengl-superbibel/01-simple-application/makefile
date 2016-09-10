APP_OBJ = ogg-player.o \
             wrap-ogg.o \
             wrap-theora.o \
             ogg-skeleton.o

CFLAGS = -Wall -g

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

LIB = -lGL -lglut

.PHONY: all

all: simple-application

simple-application: $(APP_OBJ)
	$(CC) -o $@ $^ $(LIB) $(LIBPATH)

ogg-player.o: ogg-player.c
	$(CC) -c $(CFLAGS) -o $@ $^

clear:
	rm -f *.o simple-application