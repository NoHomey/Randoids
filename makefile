all: clean output input wiringPiSetup transpile run

output:
	cd driver/output && make

input:
	cd driver/input && make
    
wiringPiSetup:
	cd driver/wiringPiSetup && make

transpile:
	tsc

run:
	node main.js
    
clean:
	rm -Rf ./driver/*/build main.js ./game/*.js
