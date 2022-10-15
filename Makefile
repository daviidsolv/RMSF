compile: rmsf.c
	gcc rmsf.c -o rmsf
	echo "RMSF Compiled!"

install:
	cp ./rmsf /usr/bin
	rm ./rmsf
	echo "Successfully installed RMSF in /usr/bin!"

test:
	echo "Testing RMSF..."
	./test.sh