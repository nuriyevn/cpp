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
shared_ptr:
	g++ -Wfatal-errors -std=c++11 shared_ptr.cpp -o shared_ptr.out && ./shared_ptr.out
template_class:
	g++ -Wfatal-errors -std=c++11 template_class.cpp -o template_class.out && ./template_class.out
std_move:
	g++ -Wfatal-errors -std=c++11 std_move.cpp -o std_move.out && ./std_move.out
template_function:
	g++ -Wfatal-errors -std=c++11 template_function.cpp -o template_function.out && ./template_function.out
NoArgFunction:
	g++ -Wfatal-errors -std=c++11 NoArgFunction.cpp -o NoArgFunction.out && ./NoArgFunction.out
sp2:
	g++ -Wfatal-errors -std=c++11 sp2.cpp -o sp2.out && ./sp2.out
observer:
	g++ -Wfatal-errors observer.cpp -o observer.out && ./observer.out
myobserver:
	g++ -Wfatal-errors myobserver.cpp -o myobserver.out && ./myobserver.out
chain_of_resp:
	g++ -Wfatal-errors chain_of_resp.cpp -o chain_of_resp && ./chain_of_resp
