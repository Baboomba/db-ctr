#include "../header/db_connection.h"


bool check_connection(MYSQL* conn) {
    if (conn == NULL) {
        fprintf(stderr, "failed to initialize connection...\n");
        return false;
    }
    return true;
}

bool check_execution(MYSQL* conn, int status) {
    if (status) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return false;
    }
    return true;
}

bool check_store(MYSQL* conn, MYSQL_RES* res) {
    if (res == NULL) {
        fprintf(stderr, "failed to store the result : %s\n", mysql_error(conn));
        mysql_close(conn);
        return false;
    }
    return true;
}

MYSQL* create_connection(DBInfo* info) {
    MYSQL* conn = mysql_init(NULL);
    if (!check_connection(conn)) return NULL;
    
    conn = mysql_real_connect(
        conn,
        info->localhost,
        info->user,
        info->password,
        info->database,
        info->port,
        NULL,
        0
    );
    if (!check_connection(conn)) return NULL;
    
    return conn;
}

MYSQL_RES* fetch_data(MYSQL* conn, const char* query) {
    int status = mysql_query(conn, query);
    if (!check_execution(conn, status)) return NULL;

    MYSQL_RES* result = mysql_store_result(conn);
    if (!check_store(conn, result)) return NULL;

    return result;
}

void close_connection(MYSQL* conn, MYSQL_RES* res) {
    if (res != NULL) {
        mysql_free_result(res);
    }
    
    if (conn != NULL) {
        mysql_close(conn);
    }

    printf("closed mysql connection...\n");
}