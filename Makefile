default: main.c
	gcc main.c -ggdb -lX11 -Wall -Wextra -Wpedantic -o grabcolor
