CC = gcc


OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = include/
BIN_DIR = bin/# Por si se quieren generar los ejecutables dentro de alguna carpeta

CFLAGS = -c -MMD -MF $(OBJ_DIR)$*.d -g -Wall -ansi -pedantic -DDEBUG

COMPILE.c = $(CC) $(CFLAGS) -I$(INC_DIR)

GAME_EXE           = $(BIN_DIR)game_loop
INVENTORY_TEST_EXE = $(BIN_DIR)inventory_test
LINK_TEST_EXE      = $(BIN_DIR)link_test
PLAYER_TEST_EXE    = $(BIN_DIR)player_test
SET_TEST_EXE       = $(BIN_DIR)set_test
SPACE_TEST_EXE     = $(BIN_DIR)space_test
DIE_TEST_EXE       = $(BIN_DIR)die_test

SRC = $(wildcard $(SRC_DIR)*.c)

EXES = $(GAME_EXE) $(INVENTORY_TEST_EXE) $(LINK_TEST_EXE) $(PLAYER_TEST_EXE) $(SET_TEST_EXE) $(SPACE_TEST_EXE) $(DIE_TEST_EXE)

GAME_OBJ           = $(patsubst %.o,$(OBJ_DIR)%.o, command.o game.o game_loop.o graphic_engine.o screen.o space.o player.o object.o die.o set.o link.o inventory.o game_management.o)
INVENTORY_TEST_OBJ = $(patsubst %.o,$(OBJ_DIR)%.o, inventory_test.o inventory.o set.o)
LINK_TEST_OBJ      = $(patsubst %.o,$(OBJ_DIR)%.o, link_test.o link.o)
PLAYER_TEST_OBJ    = $(patsubst %.o,$(OBJ_DIR)%.o, player_test.o player.o set.o inventory.o )
SET_TEST_OBJ       = $(patsubst %.o,$(OBJ_DIR)%.o, set_test.o set.o)
DIE_TEST_OBJ       = $(patsubst %.o,$(OBJ_DIR)%.o, die_test.o die.o)
SPACE_TEST_OBJ     = $(patsubst %.o,$(OBJ_DIR)%.o, space_test.o space.o link.o set.o)

$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

all: $(EXES)

tests: $(TESTS)

$(GAME_EXE): $(GAME_OBJ)
	gcc $^ -o $@

$(INVENTORY_TEST_EXE): $(INVENTORY_TEST_OBJ)
	gcc $^ -o $@

$(LINK_TEST_EXE): $(LINK_TEST_OBJ)
	gcc $^ -o $@

$(PLAYER_TEST_EXE): $(PLAYER_TEST_OBJ)
	gcc $^ -o $@

$(SET_TEST_EXE): $(SET_TEST_OBJ)
	gcc $^ -o $@

$(DIE_TEST_EXE): $(DIE_TEST_OBJ)
	gcc $^ -o $@

$(SPACE_TEST_EXE): $(SPACE_TEST_OBJ)
	gcc $^ -o $@
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJ_DIR)%.d
		$(COMPILE.c) $< -o $@

-include $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.d)

$(OBJ_DIR)%.d: ;

.PRECIOUS: $(OBJ_DIR)/%.d

.PHONY: clean clear doxygen dist runv

doxygen:
	doxygen Doxyfile

dist:
	tar -cvzf source.tar.gz src/*.c include/*.h *.dat reuniones/*.pdf *.pdf Makefile Doxyfile doc/

clean: 
	$(RM) -f $(OBJ_DIR)*.o $(OBJ_DIR)*.d $(EXES)

clear:
	$(RM) -f $(OBJ_DIR)*.o

runv:
	valgrind --leak-check=full --track-origins=yes -v ./$(GAME_EXE) spaces.dat objects.dat links.dat player.dat