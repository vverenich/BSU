#include <stdlib.h>
#include <stdio.h>
#include "sqlite3.h"
#include "Windows.h";
#pragma warning(disable:4996)
struct sqlite3* db;

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf(" %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	}
	printf("\n");
	return 0;

}

int ImageLoadCallback(void* outFile, int argc, char** argv, char** azColName)
{
	fprintf((FILE*)outFile, "%s", argv[0]);
}

void PrintValueById(int id)
{
	char requestBuffer[60];
	sprintf(requestBuffer, "SELECT * from Companies where id=%d;", id);
	char* errorMsg=0;
	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK) {
		printf(errorMsg);
	}
}

void PrintValueByFieldPattern(char* field, char* pattern)
{
	char requestBuffer[150];
	char* errorMsg = 0;
	sprintf(requestBuffer, "SELECT * from Companies where %s like '%s';",field,pattern );
	if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)!=SQLITE_OK)
	{
		printf(errorMsg);
	}
}

void AddCompany(char** argv)
{
	char requestBuffer[500];
	char* errorMsg = 0;
	sprintf(requestBuffer, "insert into Companies (name,url,adress,startYear,age,employeesCount,departmentsCount,category_id) values ('%s','%s','%s',%d,%d,%d,%d,%d)",
		argv[0], argv[1], argv[2], atoi( argv[3]),atoi( argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK)
	{
		printf(errorMsg);
	}
}

void PrintValueByCategory(char* category)
{
	char requestBuffer[200];
	char* errorMsg = 0;
	sprintf(requestBuffer, "SELECT * from Companies INNER JOIN category ON category.id=Companies.category_id AND category.cat_name='%s';", category);

	if(sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg)!=SQLITE_OK)
	{
		printf(errorMsg);
	}
}

void DeleteValueById(int id)
{
	char requestBuffer[200];
	char* errorMsg = 0;
	sprintf(requestBuffer, "DELETE from Companies where id=%d;", id);

	if (sqlite3_exec(db, requestBuffer, callback, 0, &errorMsg) != SQLITE_OK)
	{
		printf(errorMsg);
	}
}

void PrintImageById(int id,FILE* outFile)
{
	char requestBuffer[200];
	char* errorMsg = 0;
	sprintf(requestBuffer, "SELECT picture from Companies where id=%d;", id);

	

	sqlite3_stmt* pStmt;
	sqlite3_prepare_v2(db, requestBuffer, -1, &pStmt, 0);

	int rc = sqlite3_step(pStmt);

	int bytes = 0;


	if (rc == SQLITE_ROW) {

		bytes = sqlite3_column_bytes(pStmt, 0);
	}

	fwrite(sqlite3_column_blob(pStmt, 0), bytes, 1, outFile);
	fclose(outFile);
	sqlite3_finalize(pStmt);
}

int main()
{
	int run = 1;
	int openResult = sqlite3_open("Mydatabase.db", &db);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if(openResult)
	{
		printf("Cant open db\n");
	}

	while (run)
	{
		printf("\n choose option\n");
		printf(" Print value by id: 1\n");
		printf(" Print value by field pattern: 2\n");
		printf(" Print value by category: 3\n");
		printf(" Add company: 4\n");
		printf(" Print all: 5\n");
		printf(" Delete by index: 6\n");
		printf(" Load image by index: 7\n");
		printf(" Exit: 0\n");

		int command;
		scanf("%d", &command);
		
			switch (command)
			{
			  case 1:
			  {
			  
			  	printf("  Insert required id \n");
			  	int id;
			  	scanf("%d", &id);
			  	PrintValueById(id);
			  	break;
			  
			  }
			  
			  case 2:
			  {
			  	printf("  Insert required field name \n");
			  	char field[30];
			  	scanf("%s", &field);
			  
			  	printf("  Insert required pattern \n");
			  	char pattern[30];
			  	scanf("%s", &pattern);
			  
			  	PrintValueByFieldPattern(field, pattern);
			  	break;
			  }
			  case 3:
			  {
				printf("  Insert required category name \n");
				char category[100];
				scanf(" %[^\n]s", &category);
				PrintValueByCategory(category);
				break;
			  }
			  case 4:
				  {
				  char name[30];
				  char url[30];
				  char adress[30];
				  char startYear[30];
				  char age[30];
				  char employeesCount[30];
				  char departmentsCount[30];
				  char category_id[30];

				  printf(" Insert name" );
				  scanf("%s", &name);
				  printf(" Insert url ");
				  scanf("%s", &url);
				  printf(" Insert adress ");
				  scanf("%s",&adress);
				  printf(" Insert startYear ");
				  scanf("%s", &startYear);
				  printf(" Insert age ");
				  scanf("%s", &age);
				  printf(" Insert employeesCount ");
				  scanf("%s", &employeesCount);
				  printf(" Insert departmentCount ");
				  scanf("%s", &departmentsCount);
				  printf(" Insert category_id ");
				  scanf("%s", &category_id);

				  char* argv[8];
				  argv[0] = name;
				  argv[1] = url;
				  argv[2] = adress;
				  argv[3] = startYear;
				  argv[4] = age;
				  argv[5] = employeesCount;
				  argv[6] = departmentsCount;
				  argv[7] = category_id;
				  AddCompany(argv);
			  		
				  break;
				  }

			  case 5:
				  {
				  PrintValueByFieldPattern("name", "%%");
				  break;
				  }
			  case 6:
				  {
				  int id;
				  printf("Insert id\n");
				  scanf("%d", &id);
				  DeleteValueById(id);
			  		break;
				  }
			  case 7:
				  {
				  int id;
				  printf("Insert id\n");
				  scanf("%d", &id);
				  char path[50];
					  printf("Insert path\n");
					  scanf("%s", &path);
				  FILE* outFile = fopen(path, "wb");
				  PrintImageById(id,outFile);
			  		break;
				  }
			  case 0:
				  {
				  run = 0;
				  break;
			  		
				  }

			  default:
				  {
				  printf(" Incorrect option!!!!\n");
				  continue;
				  }
			}

	}

}