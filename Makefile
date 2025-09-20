all:
	gcc -Wall -O2 -g main.c vendor/glad.c core/*.c core/util/*c -o xeza -lglfw -lGL -lm

run:
	./xeza cube.obj

clean:
	rm -f xeza 
