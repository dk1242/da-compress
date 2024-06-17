dacompress: main.o
	@echo "Building dacompress tool"
	@g++ main.o -o dacompress
	
main.o: main.cpp
	@g++ -c main.cpp
	# @echo "Installing dkwc..."
	# @sudo cp dkwc /usr/local/bin/dkwc

clean:
	@rm -f *.o dkwc