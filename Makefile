all:
	gcc -o fetchme fetchme.c -Wall -Wextra -lm

clean:
	rm fetchme
