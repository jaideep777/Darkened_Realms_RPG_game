LDFLAGS = -lpthread
CPPFLAGS = -c

all: clean server

server: classes.o utils.o creator.o functions.o networkengine.o ai.o main.o
	g++ -o server classes.o creator.o utils.o functions.o networkengine.o ai.o main.o $(LDFLAGS)

classes.o: classes.cpp
	g++ $(CPPFLAGS) classes.cpp
creator.o: creator.cpp
	g++ $(CPPFLAGS) creator.cpp
utils.o: utils.cpp
	g++ $(CPPFLAGS) utils.cpp
functions.o: functions.cpp
	g++ $(CPPFLAGS) functions.cpp
networkengine.o: networkengine.cpp
	g++ $(CPPFLAGS) networkengine.cpp
ai.o: ai.cpp
	g++ $(CPPFLAGS) ai.cpp
main.o: main.cpp
	g++ $(CPPFLAGS) main.cpp
	
clean:
	rm -Rf *.o

re: clean all

