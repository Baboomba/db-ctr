#ifndef CTR_MSSQL_H
#define CTR_MSSQL_H

#include "db_info.h"
#include <sybfront.h>
#include <sybdb.h>

typedef struct MSSQL_Conn {
    LOGINREC* login;
    DBPROCESS* dbproc;
} MSSQL_Conn;

typedef enum {
    NoError,
    SetError,
    ExecError,
    NoResError
} QueryErrorCode;

bool check_login_mssql(LOGINREC* login);
bool check_connection_mssql(DBPROCESS* dbproc);
QueryErrorCode check_query_execution_mssql(MSSQL_Conn* conn, const char* query);
LOGINREC* try_login(DBInfo* info);
DBPROCESS* try_connection(LOGINREC* login, DBInfo* info);
MSSQL_Conn* create_connection_mssql(DBInfo* info);
MSSQL_Conn* fetch_data_mssql(MSSQL_Conn* conn, const char* query);
void close_connection_mssql(MSSQL_Conn* conn);

#endif