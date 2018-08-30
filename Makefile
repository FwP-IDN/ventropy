GCC = g++
INC = -I ./include
EXE = ent
LIB = -L /usr/foo/lib
SRC    := $(wildcard *.cpp)
OBJ    := $(SRC:.cpp=.o)
CFLAGS := -O2 -std=c++11 -Wall -lstdc++ -lpng -m32

ifeq ($(LINK), static)
	CFLAGS += -static-libstdc++ -static-libgcc -lpng -m32
endif

all:$(OBJ)
	$(GCC) $(CFLAGS) -o $(EXE) $(OBJ)  

%.o:%.cpp
	$(GCC) $(INC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJ) $(EXE)

.PHONY:clean all
