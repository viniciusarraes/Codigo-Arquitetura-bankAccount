all:
	gcc mutualExclusion.c -o mutualExclusion -lpthread
	./mutualExclusion 5

clean:
	rm -f mutualExclusion
	rm -f log0.txt
	rm -f log1.txt
	rm -f log2.txt
	rm -f log3.txt
	rm -f log4.txt
