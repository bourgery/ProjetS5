CC = cc 
CFLAGS = -std=c99 -Wall -g
SDL = -lSDL -lSDL_ttf -lSDL_image
SRC4 = src/achievement4.c src/main_achievement4.c src/achievement3.c src/achievement2.c src/achievement1.c src/achievement0.c
OBJ4 = $(SRC4:.c=.o)
SRC3 = src/achievement3.c src/main_achievement3.c src/achievement2.c src/achievement1.c src/achievement0.c
OBJ3 = $(SRC3:.c=.o)
SRC2 = src/achievement2.c src/main_achievement2.c src/achievement1.c src/achievement0.c
OBJ2 = $(SRC2:.c=.o)
SRC1 = src/achievement1.c src/main_achievement1.c src/achievement0.c
OBJ1 = $(SRC1:.c=.o)
SRC0 = src/achievement0.c src/main_achievement0.c 
OBJ0 = $(SRC0:.c=.o)
TST4 = src/ach4.c src/achievement3.c src/achievement2.c src/achievement1.c src/achievement0.c
TST0 = $(TST4:.c=.o)


all: achievement4 achievement3 achievement2 achievement1 achievement0

ach: $(TST0)
	@$(CC) -o $@ $^ $(CFLAGS) $(SDL)

achievement4: $(OBJ4) 
	@$(CC) -o $@ $^ $(CFLAGS) $(SDL)

achievement3: $(OBJ3) 
	@$(CC) -o $@ $^ $(CFLAGS) $(SDL)

achievement2: $(OBJ2) 
	@$(CC) -o $@ $^ $(CFLAGS) $(SDL)

achievement1: $(OBJ1) 
	@$(CC) -o $@ $^ $(CFLAGS) $(SDL)

achievement0: $(OBJ0)
	@$(CC) -o $@ $^ $(CFLAGS) $(SDL) 

%.o: %.c %.h
	@$(CC) -o $@ -c $< $(CFLAGS) $(SDL)

execute4:
	@./achievement4

executeSDL3:
	@./achievement3 1

execute3:
	@./achievement3 0

executeSDL2:
	@./achievement2 1

execute2:
	@./achievement2 0

executeSDL1:
	@./achievement1 1

execute1: 
	@./achievement1 0

executeSDL0:
	@./achievement0 1

execute0: 
	@./achievement0 0


test: test4 test3 test2 test1 test0

test_achievement4: test4

test4:
	@$(CC) -c src/achievement4.c $(CFLAGS) $(SDL)
	@$(CC) -c src/achievement3.c $(CFLAGS) $(SDL)
	@$(CC) -c src/achievement2.c $(CFLAGS) $(SDL)
	@$(CC) -c src/achievement1.c $(CFLAGS) $(SDL)
	@$(CC) -c src/achievement0.c $(CFLAGS) $(SDL) 
	@$(CC) -c tst/test_achievement4.c $(CFLAGS) $(SDL)
	@$(CC) -o $@ test_achievement4.o achievement4.o achievement3.o achievement2.o achievement1.o achievement0.o $(CFLAGS) $(SDL)
	@./test4

test_achievement3: test3

test3:
	@$(CC) -c src/achievement3.c $(CFLAGS) $(SDL)
	@$(CC) -c src/achievement2.c $(CFLAGS) $(SDL)
	@$(CC) -c src/achievement1.c $(CFLAGS) $(SDL)
	@$(CC) -c src/achievement0.c $(CFLAGS) $(SDL) 
	@$(CC) -c tst/test_achievement3.c $(CFLAGS) $(SDL)
	@$(CC) -o $@ test_achievement3.o achievement3.o achievement2.o achievement1.o achievement0.o $(CFLAGS) $(SDL)
	@./test3

test_achievement2: test2

test2:
	@$(CC) -c src/achievement2.c $(CFLAGS) $(SDL)
	@$(CC) -c src/achievement1.c $(CFLAGS) $(SDL)
	@$(CC) -c src/achievement0.c $(CFLAGS) $(SDL)
	@$(CC) -c tst/test_achievement2.c $(CFLAGS) $(SDL) 
	@$(CC) -o $@ test_achievement2.o achievement2.o achievement1.o achievement0.o $(CFLAGS) $(SDL)
	@./test2

test_achievement1: test1

test1:
	@$(CC) -c src/achievement1.c $(CFLAGS) $(SDL)
	@$(CC) -c src/achievement0.c $(CFLAGS) $(SDL)
	@$(CC) -c tst/test_achievement1.c $(CFLAGS) $(SDL)
	@$(CC) -o $@ test_achievement1.o achievement1.o achievement0.o $(CFLAGS) $(SDL)
	@./test1

test_achievement0: test0

test0:
	@$(CC) -c src/achievement0.c $(CFLAGS) $(SDL)
	@$(CC) -c tst/test_achievement0.c $(CFLAGS) $(SDL)
	@$(CC) -o $@ test_achievement0.o achievement0.o $(CFLAGS) $(SDL)
	@./test0

clean:
	@rm -f src/*~ *.o tst/*~ src/*.o achievement4 test4 achievement3 test3 achievement2 test2 achievement1 test1 achievement0 test0

 
