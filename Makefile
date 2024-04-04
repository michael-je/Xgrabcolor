default: main.c
	gcc main.c -lX11 -Wall -Wextra -Wpedantic -o grabcolor

debug: main.c
	gcc main.c -ggdb -lX11 -Wall -Wextra -Wpedantic -o grabcolor
