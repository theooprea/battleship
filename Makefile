build: battleship.c
	gcc battleship.c -o battleship -lncurses
run: battleship
	./battleship harta1.txt harta2.txt harta3.txt harta4.txt harta5.txt harta6.txt
clean: battleship
	rm battleship
