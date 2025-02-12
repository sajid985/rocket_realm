OBJ = main.o rocket.o rocket_collection.o
TEST_OBJ = test_rocketsys.o rocket.o rocket_collection.o

rocket_game: $(OBJ)
	gcc -o rocket_game $(OBJ)

main.o: main.c rocket.h
	gcc -c main.c

rocket.o: rocket.c
	gcc -c rocket.c

rocket_collection.o: rocket_collection.c
	gcc -c rocket_collection.c

clean:
	rm -f $(OBJ) $(TEST_OBJ) rocket_game test_rocketsys test_results.xml test

run: rocket_game
	./rocket_game

test: $(TEST_OBJ)
	gcc -o test_rocketsys $(TEST_OBJ) -lcunit

test_rocketsys.o: test_rocketsys.c rocket.h
	gcc -c test_rocketsys.c

runtest: test
	./test_rocketsys
