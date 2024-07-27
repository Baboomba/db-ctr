#ifndef PYTHON_HANDLER_H
#define PYTHON_HANDLER_H

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <Python.h>
#include <numpy/arrayobject.h>
#include <mysql/mysql.h>

typedef struct {
    char localhost[16];
    char user[16];
    char password[16];
    char database[16];
    unsigned int port;
} DBInfo;

bool check_connection(MYSQL* conn);
bool check_execution(MYSQL* conn, int status);
bool check_store(MYSQL* conn, MYSQL_RES* res);

MYSQL* create_connection(DBInfo* info);
MYSQL_RES* fetch_data(MYSQL* conn, const char* query);
void close_connection(MYSQL* conn, MYSQL_RES* res);

#endif