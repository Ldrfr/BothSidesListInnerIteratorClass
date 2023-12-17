prog: main.o exception.o
	g++ main.o exception.o -o prog

main.o: main.cpp both_sides_list.h exception.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c main.cpp

exception.o: exception.cpp exception.h
	g++ -g -Wall -Wextra -Wfloat-equal -Werror -pedantic -std=c++11 -c exception.cpp

clean:
	rm -f *.gch *.o pr*