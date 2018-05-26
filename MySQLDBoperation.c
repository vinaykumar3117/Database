#include<stdio.h>
#include<mysql.h>

MYSQL *con;
MYSQL_RES *res;
MYSQL_ROW row;

void selectDB()
{
	unsigned int count = 0;
	char query[100];

	strcpy(query, "select * from employee");
	if(mysql_query(con, query))
	{
		printf("\nQuery Failed[%s] - %s\n\n", query, mysql_error(con));
		return;
	}
	res = mysql_use_result(con);
	printf("\n===========================================================================");
	printf("\n\t\t\t\t-:EMPLOYEE:-");
	printf("\n===========================================================================");
	printf("\nid\tname\tmobile\t\taddress\t\t\tdob");
	printf("\n---------------------------------------------------------------------------");
	while((row = mysql_fetch_row(res)) != NULL)
	{
		printf("\n%s\t%s\t%s\t%s\t%s", row[0], row[1], row[2], row[3], row[4]);
		count++;
	}
	if(count == 0)
		printf("\nNo records found.");
	printf("\n===========================================================================\n");
}

void insertDB()
{
	char query[100];

	sprintf(query, "insert into employee(id,name,mobile,address) values(\"%s\",\"%s\",\"%s\",\"%s\")", "5","RGF","9000000306","#7684 hbhg bhdjhg");
	if(mysql_query(con, query))
	{
		printf("\nQuery Failed[%s] - %s\n\n", query, mysql_error(con));
		return;
	}
	printf("\nQUERY OK - %s\n", query);
}

int main(int argc, char **argv)
{
	char *server = "127.0.0.1";
	char *user = "user";
	char *password = "paswd";
	char *database = "db";

	con = mysql_init(NULL);
	if(!mysql_real_connect(con, server, user, password, database, 0, NULL, 0))
	{
		printf("\nUnable to connect - %s\n\n", mysql_error(con));
		exit(1);
	}
	printf("\nConnected to %s DB...\n", database);
	insertDB();
	selectDB();
	mysql_free_result(res);
	mysql_close(con);
	printf("\nDisconnected from DB\n\n");
	return 0;
}
