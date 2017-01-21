INCPATH = C:/Libs/C++/include
CPPFLAGS = -std=gnu++11
LIBPATH = C:/Libs/C++/lib
LIBS = -lsimpleGL -lglew32 -lglfw3 -lopengl32 -lgdi32 -lsupc++ -lws2_32 -lpng16 -lz -lm -lfreetype

CPPS = main.cpp

labyrinth: $(CPPS)
	g++ $(CPPFLAGS) -o $@ $(CPPS) -I$(INCPATH) -L$(LIBPATH) -lsimpleGL $(LIBS)
