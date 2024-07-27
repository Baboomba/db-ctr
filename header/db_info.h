#ifndef DB_INFO_H
#define DB_INFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char host[16];
    char user[16];
    char password[16];
    char database[16];
    unsigned int port;
    char encoding[8];
    char driver[32];
} DBInfo;

typedef enum {
    DB_MYSQL,
    DB_MSSQL
} DBType;

#endif