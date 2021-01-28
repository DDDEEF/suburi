INCS = include/fastsin.h
OBJS = fastsin.o init.o
TARGET ?= libfastsin.a
CC ?= gcc
AR ?= ar
CFLAGS += -O
CFLAGS += -Wall
INSTALL_DIR ?= /usr/local
INCLUDE_DIR ?= $(INSTALL_DIR)/include/fastsin
LIBRARY_DIR ?= $(INCLUDE_DIR)/lib

.SUFFIXES: .c .o

all :		$(TARGET)

$(TARGET) :	$(OBJS)
	$(AR) ruc $(TARGET) $(OBJS)

.c.o :		$<
	$(CC) -c $< $(CFLAGS)

install :	all
	mkdir -p $(INCLUDE_DIR)
	cp $(INCS) $(INCLUDE_DIR)
	cp $(TARGET) $(LIBRARY_DIR)

uninstall :	
	rm $(LIBRARY_DIR)/$(TARGET)
	rm -fR $(INCLUDE_DIR)

clean :
	rm -f $(OBJS) $(TARGET)