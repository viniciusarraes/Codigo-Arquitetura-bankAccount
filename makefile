all:
	gcc mutualExclusion.c -o mutualExclusion -lpthread
	./mutualExclusion

clean:
	rm -f mutualExclusion
	rm -f log.txt