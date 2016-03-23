all: clean output input transpile run

output:
	cd driver/output && make

input:
	cd driver/input && make 

transpile:
	tsc -m commonjs main.ts

run:
	node main.js
    
clean:
	rm -Rf ./driver/*/build main.js