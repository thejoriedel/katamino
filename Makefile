CFLAGS   = -g `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lSDL2_gfx -lm -ggdb3
PROG = katamino
CXX = gcc

OBJS   = graphics.o game.o main.o

all: $(PROG)

%.o: src/%.c src/%.h src/defs.h
	$(CXX) $(CFLAGS) -c $<

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) $(LDFLAGS)

clean:
	rm $(PROG) *.o

wasm:
	rm -rf dist && \
	mkdir -p dist && \
	emcc -o dist/index.html --shell-file static/template.html src/*.c -Wall -g -lm -s USE_SDL=2 -s USE_SDL_GFX=2
