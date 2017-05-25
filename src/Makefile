ROOT_PATH=$(shell pwd)
GXX=g++
GCC=gcc
FLAG=-g -std=c++11
LINK_LIBS=-lpthread
LIB_PATH=
INCLUDE= -I${ROOT_PATH}/mysql_lib/include -I.

SER_BIN=server_main #gps_server

.PHONY:all clean

all:$(SER_BIN)

SRC:=$(shell ls )
PPP=$(filter %.cpp,$(SRC))
SER_OBJ=$(PPP:.cpp=.o)

$(SER_BIN):$(SER_OBJ)
	$(GXX) -g -o $@ $^ $(LIB_PATH) $(FLAG) $(LINK_LIB)

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


