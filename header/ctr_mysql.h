#ifndef CTR_MYSQL_H
#define CTR_MYSQL_H

#include "db_info.h"
#include <mysql/mysql.h>


bool check_connection_mysql(MYSQL* conn);
bool check_execution_mysql(MYSQL* conn, int status);
bool check_store_mysql(MYSQL* conn, MYSQL_RES* res);

MYSQL* create_connection_mysql(DBInfo* info);
MYSQL_RES* fetch_data_mysql(MYSQL* conn, const char* query);
void close_connection_mysql(MYSQL* conn, MYSQL_RES* res);

#endif