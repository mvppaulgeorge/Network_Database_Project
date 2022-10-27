CC = g++
CFLAGS = -std=c++11
main: test_network.cpp person.cpp Date.cpp contact.cpp network.h network.cpp misc.cpp
	$(CC) $(CFLAGS) -g -o main test_network.cpp person.cpp Date.cpp contact.cpp network.h network.cpp misc.cpp