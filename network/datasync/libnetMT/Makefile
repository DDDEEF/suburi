PROGRAM=libnet.a
OBJS=sock.o token.o log.o jconv.o lockf.o
SRCS=$(OBJS:%.o=%.c)
CFLAGS=-g -Wall -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -liconv
LDFLAGS=-I /usr/local/include/ -L /usr/local/lib/
LDLIBS= -lresolv -lpthread
$(PROGRAM):$(OBJS)
	ar r libnet.a $(OBJS)
