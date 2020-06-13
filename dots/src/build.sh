gcc -c getchar_unblock.c
g++ -c Cdots.cpp dots.cpp
g++ -o dots  dots.o  getchar_unblock.o Cdots.o

#g++ -o dots dots.cpp Cdots.cpp getch_unblock.o
echo output: dots