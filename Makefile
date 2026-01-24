CXX := g++
CXXFLAGS := -O2
override CXXFLAGS += -MMD -MP -fPIC

LDFLAGS :=

SRC := $(wildcard src/*.cpp)
SRC := $(filter-out src/demo.cpp,$(SRC))
OBJ := $(SRC:src/%.cpp=build/%.o)
DEP := $(OBJ:.o=.d)

all: build/libphysics.so build/libphysics.a

demo: build/demo

build/demo: build/demo.o build/libphysics.a
	$(CXX) $(LDFLAGS) -o $@ $< -lsfml-graphics -lsfml-window -lsfml-system build/libphysics.a

build/libphysics.so: $(OBJ)
	$(CXX) $(LDFLAGS) -shared -o $@ $^

build/libphysics.a: $(OBJ)
	ar rcs $@ $^

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

build:
	mkdir -p build

.PHONY: clean
clean:
	rm -rf build/libphysics.so build/libphysics.a build/demo build/*.o build/*.d
