.SUFFIXES:



CXX := g++
CXXFLAGS := -Wall -g
INCLUDES := -Iinclude
LIBS := -lm
TARGET := demo

SRCDIR := src
TESTDIR := test
SRCOBJS := $(patsubst %.cpp, %.o, $(wildcard $(SRCDIR)/*.cpp))
TESTOBJS := $(patsubst %.cpp, %.o, $(wildcard $(TESTDIR)/*.cpp))
OBJS := $(SRCOBJS) $(TESTOBJS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) $^ -o $@

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

clean:
	-@rm -f $(TARGET)
	-@rm -f $(OBJS)