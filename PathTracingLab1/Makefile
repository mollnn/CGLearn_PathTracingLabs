bin/PathTracingLab1.exe: 		lib/Main.o lib/json/cJSON.o lib/json/CJsonObject.o
	g++ -o bin/PathTracingLab1.exe lib/Main.o lib/json/cJSON.o lib/json/CJsonObject.o

bin/moduleTest.exe:				lib/moduleTest.o lib/json/cJSON.o lib/json/CJsonObject.o
	g++ -o bin/moduleTest.exe lib/moduleTest.o lib/json/cJSON.o lib/json/CJsonObject.o

lib/moduleTest.o:				src/moduleTest.cpp
	g++ -o lib/moduleTest.o -c src/moduleTest.cpp

lib/Main.o:						src/Main.cpp
	g++ -o lib/Main.o -c src/Main.cpp

lib/json/cJSON.o:				src/json/cJSON.c 
	gcc -o lib/json/cJSON.o -c src/json/cJSON.c 

lib/json/CJsonObject.o:			src/json/CJsonObject.cpp
	g++ -o lib/json/CJsonObject.o -c src/json/CJsonObject.cpp

clean:
	rm bin/*.exe lib/*.o lib/json/*.o

run:							bin/PathTracingLab1.exe
	bin/PathTracingLab1.exe

test:							bin/moduleTest.exe
	bin/moduleTest.exe

simg:
	util/ppmviewer.exe test.ppm

x:
	make clean
	make
	make run
	make simg

ctest:
	make clean
	make test
	make simg
