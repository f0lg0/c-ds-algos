huffman:
	$(CC) -Wall -Wextra -Werror -g3 -O2 main.c pqueue.c huffmantree.c -o huffman.out

clean:
	rm huffman.out

debug:
	valgrind --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./huffman.out 
