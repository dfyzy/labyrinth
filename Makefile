CPPFLAGS = -std=gnu++11 -Wall -static-libgcc -static-libstdc++
LIBS = -lsimpleGL -lglew32 -lglfw3 -lopengl32 -lgdi32 -lsupc++ -lws2_32 -lpng16 -lz -lm -lfreetype

CPPS = main.cc

labyrinth: $(CPPS)
	g++ $(CPPFLAGS) -o $@ $(CPPS) -lsimpleGL $(LIBS)
