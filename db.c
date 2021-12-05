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
char* sql = "CREATE TABLE IF NOT EXISTS Place(id int PRIMARY_KEY, ime text, znesek float)";

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
sql = "INSERT INTO Place (id, ime, znesek) VALUES(?1, ?2, ?3)";

r = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

if(r != SQLITE_OK){
	printf("Po prepare!\n");
	printf("%s\n", sqlite3_errmsg(db));
	exit(-1);
}

int txt;
int idx;
int dbl;
int i;
char* a = malloc(sizeof(char)*10); 
scanf("%d  %s", &i, a);

idx = sqlite3_bind_int(stmt, 1, i);
txt = sqlite3_bind_text(stmt, 2, a, -1, NULL);
dbl = sqlite3_bind_int(stmt, 3, 950.0);

if(txt != SQLITE_OK){
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
while(sqlite3_step(stmt) != SQLITE_DONE){
	const char* data;
	for(int i = 0; i < sqlite3_column_count(stmt); i++){
	data = (const char*)sqlite3_column_text(stmt, i);
	printf("%s: %s\n",sqlite3_column_name(stmt, i), data ? data : "[NULL]");
	}

}
sqlite3_finalize(stmt);






sqlite3_close(db);
sqlite3_shutdown();

return 0;
}
