#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {

if( sqlite3_initialize() != SQLITE_OK )
	exit(-1);
		

char* ime = "Place.db";
sqlite3* db;
int r;


r = sqlite3_open_v2(ime, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL );

if( r != SQLITE_OK ){
	printf("%s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	exit(-1);
}	
	
sqlite3_stmt* stmt = NULL;
char* sql = "CREATE TABLE IF NOT EXISTS Place(id int, ime text, znesek float)";

r = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

if(r != SQLITE_OK){
	printf("%s\n", sqlite3_errmsg(db));
	exit(-1);
}

r = sqlite3_step(stmt);	
if(r != SQLITE_DONE){
	printf("%s\n", sqlite3_errmsg(db));
	exit(-1);
}

sqlite3_finalize(stmt);


stmt = NULL;
sql = "INSERT INTO Place VALUES(0, 'placa', 950.0)";

r = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

if(r != SQLITE_OK){
	printf("%s\n", sqlite3_errmsg(db));
	exit(-1);
}

r = sqlite3_step(stmt);	
if(r != SQLITE_DONE){
	printf("%s\n", sqlite3_errmsg(db));
	exit(-1);
}

sqlite3_finalize(stmt);



stmt = NULL;
sql = "SELECT * FROM Place";

r = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

if(r != SQLITE_OK){
	printf("%s\n", sqlite3_errmsg(db));
	exit(-1);
}

r = sqlite3_step(stmt);	
if(r == SQLITE_ROW){
	const char* data;
	const char* data2;
	for(int i = 0; i < 3; i++){
	data = (const char*)sqlite3_column_text(stmt, i);
	printf("%s\n", data ? data : "[NULL]");
	}
	exit(-1);
}

sqlite3_finalize(stmt);






sqlite3_close(db);
sqlite3_shutdown();

return 0;
}
