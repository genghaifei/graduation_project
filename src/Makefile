ROOT_PATH=$(shell pwd)


CXX=g++
GCC=gcc
FLAG=-g
LINK_LIBS=-lpthread
LIB_PATH=
INCLUDE=

SER_BIN=tcp_server #gps_server

.PHONY:all clean

all:$(SER_BIN)

SER_OBJ=$(shell grep -R $(ROOT_PATH) *.o)
SER_FILE=$()

$(SER_BIN):$(SER_OBJ)
	@$(GXX) -g -o $@ $^ $(LIB_PATH) $(FLAG) $(LINK_LIB)
