.PHONY: all clean

TARGET=test

SOURCES=$(wildcard *.cc)

HEADERS=$(wildcard *.h)

CFLAGS=-g -O0 -c -Wint-to-pointer-cast -std=gnu++11

CXXFLAGS=-Wall -Werror -I/home/sq/include -I./

LDFLAGS=-Wl,-rpath,/home/sq/lib -Wl,-rpath,/home/sq/lib64

GTEST_LIBS=/home/sq/lib

OBJS=$(patsubst %.cc,%.o,$(SOURCES))

LIBS=-Wl,-Bstatic -lgtest -lgmock -Wl,-Bdynamic -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lstdc++ -lpthread -lc

all: $(TARGET)
	@echo "build successfully. $(TARGET) has been generated."


$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(LDFLAGS) -L$(GTEST_LIBS) $(OBJS) $(LIBS)

%.o:%.cc
	gcc $(CFLAGS) $(CXXFLAGS) -o $@ $<


clean:
	-@rm -rf $(OBJS) $(TARGET)
