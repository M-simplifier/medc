
medc: ./src/*
	gcc-11 -I./include -o medc ./src/* -lncurses

clean:
	rm -f medc *.txt
