debug:
	gcc -Wall -Wextra -O2 -DDEBUG -g main.c vendor/glad.c core/*.c core/util/*c -o xeza_debug -lglfw -lGL -lm

release:
	gcc -Wall -Wextra -O2 -DRELEASE -g main.c vendor/glad.c core/*.c core/util/*c -o xeza_release -lglfw -lGL -lm

clean_debug:
	rm -f xeza_debug

clean_release:
	rm -f xeza_release
