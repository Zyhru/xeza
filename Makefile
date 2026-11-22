xeza_linux:
	gcc -Wall -Wextra -O2 -DRELEASE -g main.c vendor/glad.c core/*.c core/util/*c tests/math_test.c -o xeza -lglfw -lGL -lm

xeza_win:
	x86_64-w64-mingw32-gcc -Wall -Wextra -O2 -DRELEASE -g main.c vendor/glad.c core/*.c core/util/*.c -Ivendor -Ivendor/glfw-win/include -Lvendor/glfw-win/lib-mingw-w64 -o xeza.exe -lglfw3 -lopengl32 -lgdi32 -lm -static

test:
	gcc -Wall -Wextra -g tests/math_test.c -o math_test -lm

clean:
	rm -f xeza
