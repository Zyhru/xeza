all:
	gcc -g main.c vendor/glad.c core/*.c core/util/*c -o xeza -lglfw -lGL
clean:
	rm -f xeza 
