#include <iostream>
#include <iomanip> 
#include <string>
#include <fstream>

using namespace std;

int ma3in(int argc, char *argv[]) {

	ifstream in("input06.txt");
	ofstream out("actual_output06.txt");
	int T  = 1; in >> T;

	out << setiosflags(ios::uppercase);
	out << setw(0xf) << internal;
	while (T--) {
		double A; in >> A;
		double B; in >> B;
		double C; in >> C;
		// << nouppercase << left << showbase << 

		out << hex << nouppercase << left << showbase << (long long)std::trunc(A) << endl;
		out << right << setw(0xf) << setfill('_') << showpos  << std::fixed << setprecision(2) << B << endl;
		out << uppercase << noshowpos << std::scientific << setprecision(9) << C << endl;
	}
	return 0;
}
