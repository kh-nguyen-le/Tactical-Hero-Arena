CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ~/CADMIUM/Cadmium-Simulation-Environment/cadmium/include
INCLUDEDESTIMES=-I ~/CADMIUM/Cadmium-Simulation-Environment/DESTimes/include
INCLUDEJSON=-I ~/CADMIUM/Cadmium-Simulation-Environment/CadmiumModelJSONExporter/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

#TARGET TO COMPILE ALL THE TESTS TOGETHER (NOT SIMULATOR)
skillinfo.o: data_structures/skillinfo.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) data_structures/skillinfo.cpp -o build/skillinfo.o

heroinfo.o: data_structures/heroinfo.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) data_structures/heroinfo.cpp -o build/heroinfo.o

teamcombo.o: data_structures/teamcombo.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) data_structures/teamcombo.cpp -o build/teamcombo.o

skill.o: data_structures/skill.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) data_structures/skill.cpp -o build/skill.o

attribute.o: data_structures/attribute.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) data_structures/attribute.cpp -o build/attribute.o

# main_top.o: top_model/main.cpp
# 	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) top_model/main.cpp -o build/main_top.o
	
main_hero_test.o: test/main_hero_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) $(INCLUDEJSON) test/main_hero_test.cpp -o build/main_hero_test.o


tests: main_hero_test.o skillinfo.o heroinfo.o teamcombo.o skill.o attribute.o
		$(CC) -g -o bin/HERO_TEST build/main_hero_test.o build/skillinfo.o build/heroinfo.o build/teamcombo.o build/skill.o build/attribute.o
		
# #TARGET TO COMPILE ONLY ABP SIMULATOR
# simulator: main_top.o message.o 
# 	$(CC) -g -o bin/ABP build/main_top.o build/message.o 
	
# #TARGET TO COMPILE EVERYTHING (ABP SIMULATOR + TESTS TOGETHER)
# all: simulator tests

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*