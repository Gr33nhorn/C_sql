#include <sqlite3.h>
#include <stdio.h>

int callback(void*data, int ncols, char** values, char** headers);

int main(void) {
    
	sqlite3 *db;
	char *err_msg = 0;
	
	int rc = sqlite3_open("test.db", &db);
	
	if(rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		
		return 1;
	}
		
		
	void* data = "Callback function called";
	
	
	char* sql = "DROP TABLE IF EXISTS Placila;"
				"CREATE TABLE Placila(Id INT, Name TEXT, Znesek DOUBLE);"
				"INSERT INTO Placila VALUES(1, 'REDNO DELO I. IZMENA - IZHODIŠČE PO KP', 453.32);"
  				"INSERT INTO Placila VALUES(2, 'REDNO DELO II. IZMENA - IZHODIŠČE PO KP', 442.12);"
  				"INSERT INTO Placila VALUES(3, 'LETNI DOPUST', 52.52);"
  				"INSERT INTO Placila VALUES(4, 'RAZLIKA DO MINIMALNE PLAČE', 80.03);"
  				"INSERT INTO Placila VALUES(5, '10% DODATEK - izmensko delo', 44.21);"
  				"INSERT INTO Placila VALUES(6, 'DELOVNA USPEŠNOST - znesek', 321.36);"
  				"SELECT * FROM Placila;";
  				
  	rc = sqlite3_exec(db, sql, callback, data, &err_msg);
  	
  	if(rc != SQLITE_OK){
  		fprintf(stderr, "SQL error: %s\n", err_msg);
  		
  		sqlite3_free(err_msg);
  		sqlite3_close(db);
  		
  		return 1;
  	}
  	
  	sqlite3_close(db);
  	
    return 0;
}

int callback(void* data, int ncols, char** values, char** headers)
{
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	for(i = 0; i < ncols; i++){
		fprintf(stdout, "%s=%s ", headers[i], values[i]);
	}
	fprintf(stderr, "\n");
	return 0;
	}
