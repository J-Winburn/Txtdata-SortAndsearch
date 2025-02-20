CC = /usr/bin/g++ 
FLAGS = -Wall 

SOURCES = PA2.cpp autocomplete.cpp term.cpp SortingList.cpp

EXEC = Sorter

OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(FLAGS) -c $<

clean:
	rm -i `find ./ -type f -executable`
	rm -i *.o
