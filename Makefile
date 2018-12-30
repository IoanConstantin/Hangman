build:
	gcc -Wall hangman.c -o hangman -lncurses -lmenu
clean:
	rm -f hangman
