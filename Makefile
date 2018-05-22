install:
	g++ main.cpp -o main
	chmod +x main
run:
	./main
clean:
	rm main
build-and-run: install run
