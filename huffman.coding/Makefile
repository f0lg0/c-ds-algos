huffman:
	$(CC) -Wall -Wextra -Werror -g3 main.c pqueue.c huffmantree.c -o huffman.out

clean:
	rm huffman.out

debug:
	valgrind --leak-check=yes --track-origins=yes --leak-check=full ./huffman.out 
