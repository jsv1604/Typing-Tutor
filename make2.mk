a.exe: typing_tutor.o server2.o
	gcc typing_tutor.o server2.o
typing_tutor.o: typing_tutor.c header1.h
	gcc -c typing_tutor.c
server2.o: server2.c header1.h
	gcc -c server2.c