install:
	g++ scanner/scan.cpp main.cpp
	# chmod +x a.op
run:
	./a.out
clean:
	rm a.out
build-and-run: install run
