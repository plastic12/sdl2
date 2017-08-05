CXX = g++
# Update these paths as necessary to match your installation
SDL_LIB = -LC:/Tool/Library/SDL2-devel-2.0.5-mingw/SDL2-2.0.5/i686-w64-mingw32/lib -lSDL2main -lSDL2 -lSDL2_image
SDL_INCLUDE = -IC:/Tool/Library/SDL2-devel-2.0.5-mingw/SDL2-2.0.5/i686-w64-mingw32/include -IC:/Tool/rapidxml-1.13
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
EXE = release/output.exe
EXE2 = release/textureShow.exe

all: $(EXE) $(EXE2)

$(EXE): utility.o main.o window.o
	$(CXX) $^ $(LDFLAGS) -o $@
$(EXE2) : textureShow.o utility.o window.o game.o
	$(CXX) $^ $(LDFLAGS) -std=c++11 -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

utility.o:utility.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
window.o:window.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
textureShow.o:textureShow.cpp
		$(CXX) $(CXXFLAGS) $< -o $@
game.o:game.cpp
		$(CXX) $(CXXFLAGS) $< -o $@

clean:
	del *.o && del $(EXE)
