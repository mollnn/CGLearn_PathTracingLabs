bin/CubeCreator.exe: 		lib/CubeCreator.o lib/json/cJSON.o lib/json/CJsonObject.o
	g++ -o bin/CubeCreator.exe lib/CubeCreator.o lib/json/cJSON.o lib/json/CJsonObject.o 

lib/CubeCreator.o:						src/CubeCreator.cpp
	g++ -o lib/CubeCreator.o -c src/CubeCreator.cpp  

lib/json/cJSON.o:				src/json/cJSON.c 
	gcc -o lib/json/cJSON.o -c src/json/cJSON.c 

lib/json/CJsonObject.o:			src/json/CJsonObject.cpp
	g++ -o lib/json/CJsonObject.o -c src/json/CJsonObject.cpp

clean:
	rm bin/*.exe lib/*.o lib/json/*.o

run:							bin/CubeCreator.exe
	bin/CubeCreator.exe test.ppm scene.json camera.json sensor.json

test:							bin/moduleTest.exe
	bin/moduleTest.exe

simg:
	util/ppmviewer.exe test.ppm

x:
	make clean
	make

y:
	make clean
	make
	make run

z:
	make
	make run