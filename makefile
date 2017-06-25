CXX = g++
# Update these paths as necessary to match your installation
SDL_LIB = -LC:/Tool/Library/SDL2-devel-2.0.5-mingw/SDL2-2.0.5/i686-w64-mingw32/lib -lSDL2main -lSDL2 -lSDL2_image
SDL_INCLUDE = -IC:/Tool/Library/SDL2-devel-2.0.5-mingw/SDL2-2.0.5/i686-w64-mingw32/include -IC:/Tool/rapidxml-1.13
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
EXE = output.exe

all: $(EXE)

$(EXE): utility.o main.o window.o
	$(CXX) $< main.o window.o $(LDFLAGS) -o $@ 

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
utility.o:utility.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
window.o:window.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
clean:
	del *.o && del $(EXE)