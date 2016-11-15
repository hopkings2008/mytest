.PHONY: all clean

TARGET=test

SOURCES=$(wildcard *.cc)

HEADERS=$(wildcard *.h)

CXXFLAGS=-Wall -Werror -I/home/zouyu/include -I/home/sq/include -std=c++11

GTEST_LIBS=-L/home/sq/lib -L/home/zouyu/lib

OBJS=$(patsubst %.cc,%.o,$(SOURCES))

#LIBS=-Wl,-rpath,/home/sq/lib -Wl,-Bstatic -lgtest -lgmock -Wl,-Bdynamic -laprutil-1 -lapr-1 -lcrypt -lstdc++ -lpthread -ldl
LIBS=-Wl,-rpath,/home/sq/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lstdc++ -lpthread -ldl

all: $(TARGET)
	@echo "build successfully. $(TARGET) has been generated."


$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(GTEST_LIBS) $(OBJS) $(LIBS)

%.o:%.cc
	gcc -g -O0 -c -Wint-to-pointer-cast $(CXXFLAGS) -o $@ $<


clean:
	-@rm -rf $(OBJS) $(TARGET)
