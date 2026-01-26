CXX := g++
CXXFLAGS := -O2
override CXXFLAGS += -MMD -MP -fPIC -Isrc

LDFLAGS :=

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:src/%.cpp=build/%.o)
DEP := $(OBJ:.o=.d)

SFML_LINK = -lsfml-graphics -lsfml-window -lsfml-system

all: build/libphysics.so build/libphysics.a

examples: build/examples/bouncing-ball build/examples/collisions build/examples/spring build/examples/soft-body build/examples/rod

build/examples/bouncing-ball: build/examples/main.o build/examples/bouncing-ball.o build/libphysics.a
	$(CXX) $(LDFLAGS) -o $@ $^ $(SFML_LINK)

build/examples/collisions: build/examples/main.o build/examples/collisions.o build/libphysics.a
	$(CXX) $(LDFLAGS) -o $@ $^ $(SFML_LINK)

build/examples/spring: build/examples/main.o build/examples/spring.o build/libphysics.a
	$(CXX) $(LDFLAGS) -o $@ $^ $(SFML_LINK)

build/examples/soft-body: build/examples/main.o build/examples/soft-body.o build/libphysics.a
	$(CXX) $(LDFLAGS) -o $@ $^ $(SFML_LINK)

build/examples/rod: build/examples/main.o build/examples/rod.o build/libphysics.a
	$(CXX) $(LDFLAGS) -o $@ $^ $(SFML_LINK)

build/libphysics.so: $(OBJ)
	$(CXX) $(LDFLAGS) -shared -o $@ $^

build/libphysics.a: $(OBJ)
	ar rcs $@ $^

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/examples/%.o: examples/%.cpp | build/examples
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

-include $(DEP)

build:
	mkdir -p build

build/examples:
	mkdir -p build/examples

.PHONY: clean
clean:
	rm -rf build
