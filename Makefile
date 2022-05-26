default:
	g++ visualsort.cpp -o vsort -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./vsort
