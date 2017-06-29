CPPFLAGS = -std=gnu++11 -Wall -static-libgcc -static-libstdc++
LIBS = -lsimpleGL -Wl,-Bstatic -lglew32 -lglfw3 -lopengl32 -lgdi32 -lsupc++ -lws2_32 \
			-lfreetype -lharfbuzz -lfreetype -lgraphite2 -lglib-2.0 -lpng16 -lz -lm -lbz2

CPPS = main.cc

labyrinth: $(CPPS)
	g++ $(CPPFLAGS) -o $@ $(CPPS) $(LIBS)
