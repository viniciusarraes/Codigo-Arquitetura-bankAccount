all:
	gcc mutualExclusion.c -o mutualExclusion -lpthread
	./mutualExclusion 5

clean:
	rm -f mutualExclusion

	rm -f log.txt
