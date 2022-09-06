MODE			:= 32
ifeq ($(shell uname -m), x86_64)
	MODE		:= 64
endif
ifeq ($(shell uname -s), Darwin)
	MODE		:= 64
endif

JITASM_INCLUDE	:= ../
JITASM_H		:= $(JITASM_INCLUDE)jitasm.h
TARGET			:= test
OBJS			:= test.o test_backend.o
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

test.o: test.cpp $(JITASM_H)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

test_backend.o: test_backend.cpp $(JITASM_H)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY : clean
clean:
	$(RM) $(TARGET) $(OBJS)
