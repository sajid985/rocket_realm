OBJ = main.o rocket.o rocket_collection.o

rocket_game: $(OBJ)
	gcc -o rocket_game $(OBJ)

main.o: main.c rocket.h
	gcc -c main.c

rocket.o: rocket.c
	gcc -c rocket.c

rocket_collection.o: rocket_collection.c
	gcc -c rocket_collection.c

clean:
	rm -f $(OBJ) rocket_game

run: rocket_game
	./rocket_game