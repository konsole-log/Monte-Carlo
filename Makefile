APP = app

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc

SRC = $(shell find src -name "*.cpp")

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:
	$(CXX) $(SRC) -o $(APP) $(CXXFLAGS) $(LIBS)

run: all
	./$(APP)

clean:
	rm -f $(APP)

