MODE			:= 32
ifeq ($(shell uname -m), x86_64)
	MODE		:= 64
endif
ifeq ($(shell uname -s), Darwin)
	MODE		:= 64
endif

JITASM_INCLUDE	:= ../../
JITASM_H		:= $(JITASM_INCLUDE)jitasm.h
TARGET			:= tutorial1
OBJS			:= tutorial1.o
CXX				:= g++
CXXFLAGS		:= -fno-operator-names -Wall -I$(JITASM_INCLUDE)
ifeq ($(MODE), 64)
	CXXFLAGS	+= -m64
	LDFLAGS		+= -m64
else
	CXXFLAGS	+= -m32 -march=i686 -mmmx -msse -msse2
	LDFLAGS		+= -m32
endif
ifeq ($(DEBUG), 1)
	CXXFLAGS	+= -g
endif

.PHONY : all
all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

tutorial1.o: tutorial1.cpp $(JITASM_H)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY : clean
clean:
	$(RM) $(TARGET) $(OBJS)
