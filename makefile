army:
	g++ -Wfatal-errors army.cpp -o a.out && ./a.out
complex:
	g++ -Wfatal-errors complex.cpp -o complex.out && ./complex.out
assign:
	g++ -Wfatal-errors assign.cpp -o assign.out && ./assign.out
stdcopy:
	g++ -std=c++11 -Wfatal-errors stdcopy.cpp -o stdcopy.out && ./stdcopy.out
getline:
	g++ -Wfatal-errors getline.cpp -o getline.out && ./getline.out
zoo:
	g++ -Wfatal-errors zoo.cpp -o zoo.out && ./zoo.out
std_function:
	g++ -Wfatal-errors -std=c++11 std_function.cpp -o std_function.out && ./std_function.out
pointer_to_function:
	gcc pointer_to_function.c -o pointer_to_function.out && ./pointer_to_function.out 4 3 1 5 6
valid_pointer_to_function:
	gcc valid_pointer_to_function.c -o valid_pointer_to_function.out && ./valid_pointer_to_function.out 4 3 1 5 6
