dacompress: main.o
	@echo "Building dacompress tool"
	@g++ main.o -o dacompress
	
main.o: main.cpp
	@g++ -c main.cpp
	@echo "Installing dacompress..."
	@sudo cp dacompress /usr/local/bin/dacompress

clean:
	@rm -f *.o dacompress
	@sudo rm /usr/local/bin/dacompress