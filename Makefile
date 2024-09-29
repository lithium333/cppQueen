CXX = g++
CXXFLAGS = -std=c++17 `sdl2-config --cflags` 
LDFLAGS = `sdl2-config --libs` -lSDL2_image
SRC = main.cpp
OUT = cppQueens

# Make all
all: $(OUT)

# Make executable
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

# Clean
clean:
	rm -f $(OUT)

