#include <iostream>
#include <pqxx/pqxx>
using namespace std;
int main()
{
	pqxx::connection c(
		"dbname=jetpms "
		"user=jetuser "
		"password=qwerty123 "
		"host=localhost");
	pqxx::work txn(c);

	// INSERT INTO "room" (room_name, bed_count) VALUES ('red', 10);
	pqxx::result r = txn.exec(
		"INSERT INTO \"room\" (room_name, bed_count) VALUES ('red', 10);"
	);
	txn.commit();
	
	cout << "Row count; " << r.size() << endl;


	return 0;
}
