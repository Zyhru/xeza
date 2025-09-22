all:
	gcc -Wall -Wextra -O2 -DEBUG -g main.c vendor/glad.c core/*.c core/util/*c -o xeza -lglfw -lGL -lm

clean:
	rm -f xeza 
