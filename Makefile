xeza:
	gcc -Wall -Wextra -O2 -DRELEASE -g main.c vendor/glad.c core/*.c core/util/*c -o xeza -lglfw -lGL -lm

clean:
	rm -f xeza
