CC = g++
CFLAGS = -g -Wall
FSANITIZEFLAGS = -fsanitize=undefined -fsanitize=address
TRIETESTCCP = TrieTest.cpp
TRIECPP = Trie.cpp
C20FLAG = -std=c++2a
GOOGLETEST = ../googletest
LIBFLAG = -libgtest.a -libgtest_main.a -lpthread
LFLAG = -lgtest -lgtest_main -lpthread

test : TrieTest
	./TrieTest

TrieTest : TrieTest.o Trie.o
	$(CC) $(C20FLAG) $(CFLAGS) $(FSANITIZEFLAGS) -o TrieTest TrieTest.o Trie.o -L$(GOOGLETEST)/lib -I$(GOOGLETEST)/googletest/include $(LFLAG)

TrieTest.o : $(TRIETESTCCP) $(TRIECPP)
	$(CC) $(C20FLAG) $(CFLAGS) $(FSANITIZEFLAGS) -c $(TRIETESTCCP) $(TRIECPP) -L$(GOOGLETEST)/lib -I$(GOOGLETEST)/googletest/include $(LIBFLAG)

Trie.o : $(TRIECPP)
	$(CC) $(CFLAGS) $(FSANITIZEFLAGS) -c $(TRIECPP)

clean:
	rm -f TrieTest *.o