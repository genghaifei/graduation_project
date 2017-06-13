ROOT_PATH=$(shell pwd)
GXX=g++
GCC=gcc
FLAG=-g -std=c++11
LINK_LIBS=-lpthread -ljson_linux-gcc-4.8.5_libmt -l:libjson_linux-gcc-4.8.5_libmt.a -lmysqlcppconn
LIB_PATH=-L/home/tools/jsoncpp-src-0.5.0/libs/linux-gcc-4.8.5/
INCLUDE= -I${ROOT_PATH}/mysql_lib/include -I/home/tools/jsoncpp-src-0.5.0/include/ -I.

SER_BIN=server_main #gps_server

.PHONY:all clean

all:$(SER_BIN)

SRC:=$(shell ls )
PPP=$(filter %.cpp,$(SRC))
SER_OBJ=$(PPP:.cpp=.o)

$(SER_BIN):$(SER_OBJ)
	$(GXX) -g -o $@ $^ $(LIB_PATH)  $(FLAG) $(LINK_LIBS) 

define run-yacc
echo "Compiling [ $< ] to [ $@ ] ... done"
$(GXX) -c $< $(INCLUDE) $(FLAG)
endef

%.o:$(ROOT_PATH)/%.cpp
	$(run-yacc)

clean:
	-rm -rf *.o ${SER_BIN} output

output:all
.PHONY:output
output:
	-mkdir -p output/


