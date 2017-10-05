all:
	gcc transport.c vehicule.c chauffeur.c test.c -o test.exe
	clear
	./test.exe
	     
