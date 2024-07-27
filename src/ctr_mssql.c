#include "../header/ctr_mssql.h"


bool check_login_mssql(LOGINREC* login) {
    if (login == NULL) {
        fprintf(stderr, "failed to allocate login record...\n");
        return false;
    }
    return true;
}

bool check_connection_mssql(DBPROCESS* dbproc) {
    if (dbproc == NULL) {
        fprintf(stderr, "failed to connect to MSSQL Server...\n");
        return false;
    }
    return true;
}

QueryErrorCode check_query_execution_mssql(MSSQL_Conn* conn, const char* query) {
    QueryErrorCode errCode;

    if (dbcmd(conn->dbproc, query) == FAIL) {
        return SetError;
        
    }

    if (dbsqlexec(conn->dbproc) == FAIL) {
        return ExecError;
    }

    if (dbresults(conn->dbproc) != SUCCEED) {
        return NoResError;
    }
    
    return NoError;
}

LOGINREC* try_login(DBInfo* info) {
    LOGINREC* login = dblogin();
    if (!check_login_mssql(login)) return NULL;
    
    dbsetluser(login, info->user);
    dbsetlpwd(login, info->password);
    dbsetlname(login, info->database, DBSETDBNAME);
    return login;
}

DBPROCESS* try_connection(LOGINREC* login, DBInfo* info) {
    DBPROCESS* dbproc = dbopen(login, info->host);
    if (!check_connection_mssql(dbproc)) {
        dbloginfree(login);
        return NULL;
    }
    return dbproc;
}

MSSQL_Conn* create_connection_mssql(DBInfo* info) {
    LOGINREC* login;
    DBPROCESS* dbproc;

    login = try_login(info);
    if (login == NULL) return NULL;

    dbproc = try_connection(login, info);
    if (dbproc == NULL) return NULL;
    
    MSSQL_Conn* conn = (MSSQL_Conn*)malloc(sizeof(MSSQL_Conn));
    if (conn == NULL) {
        fprintf(stderr, "failed to allocate memory for connection...");
        dbclose(dbproc);
        dbloginfree(login);
        return NULL;
    }

    conn->login = login;
    conn->dbproc = dbproc;

    return conn;
}

MSSQL_Conn* fetch_data_mssql(MSSQL_Conn* conn, const char* query) {
    QueryErrorCode errCode = check_query_execution_mssql(conn, query);

    if (errCode != NoError) {
        fprintf(stderr, "failed to fetch data : ");
        switch (errCode) {
            case SetError:
                fprintf(stderr, "Error setting query command.\n");
                break;
            case ExecError:
                fprintf(stderr, "Error executing query.\n");
                break;
            case NoResError:
                fprintf(stderr, "No results returned.\n");
                break;
            default:
                fprintf(stderr, "Unknown error.\n");
                break;
        }
        close_connection_mssql(conn);
        return NULL;
    }
    return conn;
}

void close_connection_mssql(MSSQL_Conn* conn) {
    if (conn->dbproc != NULL) dbclose(conn->dbproc);
    if (conn->login != NULL) dbloginfree(conn->login);
}