PROJECT = battleship
OBJECTS = master.o battleshipHelper.o gameModes.o gameModesHelper.o computerAI.o
HEADERS = battleshipHelper.h gameModes.h gameModesHelper.h computerAI.h constGlobalVars.h
CPP = master.cpp battleshipHelper.cpp gameModes.cpp gameModesHelper.cpp computerAI.cpp
battleship: $(OBJECTS)
	g++ $^ -o $@
%.o: %.cpp $(HEADERS)
	g++ -std=c++11 -c $< -o $@
clean:
	rm -i *.o battleship
submit: $(PROJECT).cpp makefile 
	tar -czf $(PROJECT).tgz makefile $(CPP) $(HEADERS) battleship