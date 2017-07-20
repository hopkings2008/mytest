.PHONY: all clean

TARGET=test

SOURCES=$(wildcard *.cc)

HEADERS=$(wildcard *.h)

CXXFLAGS=-Wall -Werror -I/home/sq/include

GTEST_LIBS=/home/sq/lib

OBJS=$(patsubst %.cc,%.o,$(SOURCES))

LIBS=-Wl,-Bstatic -lgtest -lgmock -Wl,-Bdynamic -lstdc++ -lpthread -lc

all: $(TARGET)
	@echo "build successfully. $(TARGET) has been generated."


$(TARGET): $(OBJS)
	gcc -o $(TARGET) -L$(GTEST_LIBS) $(OBJS) $(LIBS)

%.o:%.cc
	gcc -g -O0 -c -Wint-to-pointer-cast $(CXXFLAGS) -o $@ $<


clean:
	-@rm -rf $(OBJS) $(TARGET)
