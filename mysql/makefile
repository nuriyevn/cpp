INC=-I/usr/include/mysql
LIB=-L/usr/lib64/mysql -lmysqlclient -lm

select: select.cpp
	g++ select.cpp -o select.out $(INC) $(LIB) && ./select.out
main:
	g++ main.cpp -o main.out $(INC) $(LIB)
clean:
	rm -f *.o *.obj *.exe *.out
