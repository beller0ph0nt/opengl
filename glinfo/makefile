GLINFO_OBJ = glinfo.o \
             wrap-gl.o \
             wrap-glx.o

CFLAGS = -Wall \
         -g \
         -DGLX_ARB_create_context \
         -I.

CC = $(CROSS_COMPILE)gcc

LIB = -lGL -lX11

.PHONY: all

all: glinfo

glinfo: $(GLINFO_OBJ)
	$(CC) -o $@ $^ $(LIB) $(LIBPATH)

glinfo.o: glinfo.c
	$(CC) -c $(CFLAGS) -o $@ $<
wrap-gl.o: wrap-gl.c
	$(CC) -c $(CFLAGS) -o $@ $<
wrap-glx.o: wrap-glx.c
	$(CC) -c $(CFLAGS) -o $@ $<

clear:
	rm -f *.o glinfo