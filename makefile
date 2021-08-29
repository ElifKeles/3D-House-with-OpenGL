hw:	clean compile


compile:
	g++ 161044033.cpp -lGL -lGLU -lglut -o program


run: 
	./program 


clear:
	clear


clean: clear
	rm -f *.o program
