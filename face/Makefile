.PHONY: all clean

TARGET=face

SOURCES=$(wildcard *.cc)

HEADERS=$(wildcard *.h)

CXXFLAGS=-Wall -Werror -I/home/zouyu/include -I/home/sq/include -fopenmp -ffast-math -msse4.1 -msse4.2 -std=c++11

GTEST_LIBS=-L/home/sq/lib -L/home/sq/lib64 -L/home/zouyu/lib

OBJS=$(patsubst %.cc,%.o,$(SOURCES))

#LIBS=-Wl,-rpath,/home/sq/lib -Wl,-Bstatic -lgtest -lgmock -Wl,-Bdynamic -laprutil-1 -lapr-1 -lcrypt -lstdc++ -lpthread -ldl
LIBS=-Wl,-rpath,/home/sq/lib -Wl,-rpath,/home/sq/lib64 -ldlib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lstdc++ -lpthread -ldl -lm -fopenmp -ffast-math -msse4.1 -msse4.2 -lopenblas_pthreads -lstdc++

all: $(TARGET)
	@echo "build successfully. $(TARGET) has been generated."


$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(GTEST_LIBS) $(OBJS) $(LIBS)

%.o:%.cc
	gcc -g -O0 -c -Wint-to-pointer-cast $(CXXFLAGS) -o $@ $<


clean:
	-@rm -rf $(OBJS) $(TARGET)
