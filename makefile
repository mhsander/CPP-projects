all:
	g++ -g -o proj5 song.cpp song.h songList.cpp songList.h main.cpp

clean:
	rm proj5
