#include "my_global.h"
#include "mysql.h"

int main(int argc, char **argv)
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL *con = mysql_init(NULL);
	int i;
	int protocol = MYSQL_PROTOCOL_TCP;
	mysql_options(con, MYSQL_OPT_PROTOCOL, (const void*)&protocol);
	if (NULL == con)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	printf("MySQL initialized\n");

	if (mysql_real_connect(con, "62.75.216.31", "root", "6312194", "jetpms", 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	printf("Connected to server.\n");
	//if (mysql_select_db(con, "jetpms"))
	{
	//	fprintf(stderr, "%s\n", mysql_error(con));
	//	exit(1);
	}
	printf("selected the database\n");
	if (mysql_query(con, "SELECT * FROM hostel"))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	printf("Queried from table\n");
	if (!(res = mysql_store_result(con)))
		exit(1);
	int j = 0;
	while ((row = mysql_fetch_row(res)))
	{
		printf("row number %d\n", j);
		j++;
		for (i = 0; i < mysql_num_fields(res); i++)
			printf("%s\n", row[i]);
	}
	printf("Processed the rows\n");
	//if (!mysql_eof(res))
		exit(1);
	//mysql_free_result(res);
	mysql_close(con);	
}
