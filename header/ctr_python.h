#ifndef CTR_PYTHON_H
#define CTR_PYTHON_H

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include "db_info.h"
#include "ctr_mysql.h"

#include <Python.h>
#include <numpy/arrayobject.h>

#define TABLE_DIMENSION 2

int map_types(enum enum_field_types mysql_type);
int* get_field_types(MYSQL_RES* data);
PyObject* mysql_to_nparaay(MYSQL_RES* data);

#endif