#include "../header/ctr_python.h"

unsigned short TABLE_DIMENSION = 2;

static int map_types(enum enum_field_types mysql_type) {
    switch (mysql_type) {
        case MYSQL_TYPE_TINY:
        case MYSQL_TYPE_SHORT:
            return NPY_SHORT;
        case MYSQL_TYPE_LONG:
            return NPY_INT;
        case MYSQL_TYPE_FLOAT:
            return NPY_FLOAT;
        case MYSQL_TYPE_DOUBLE:
            return NPY_DOUBLE;
        case MYSQL_TYPE_STRING:
        case MYSQL_TYPE_VAR_STRING:
            return NPY_STRING;
        default:
            return NPY_OBJECT;
    }
}

int* get_field_types(MYSQL_RES* data) {
    unsigned short num_fields = mysql_num_fields(data);
    
    MYSQL_FIELD* fields = mysql_fetch_field(data);

    int* np_dtype = (int*)malloc(sizeof(int) * num_fields);
    if (np_dtype == NULL) return NULL;

    for (int i = 0; i < num_fields; i++) {
        np_dtype[i] = map_types(fields[i].type);
    }
    return np_dtype;
}

PyObject* mysql_to_nparaay(MYSQL_RES* data) {
    unsigned short num_fields = mysql_num_fields(data);
    unsigned int num_rows = mysql_num_rows(data);
    
    npy_intp dims[TABLE_DIMENSION] = {num_rows, num_fields};

    int* np_dtype = get_field_types(data);

    for (int i = 0; i < num_fields; i++) {
        if (np_dtype[i] == NPY_STRING) {
            
        }

        PyObject* nparray = PyArray_SimpleNew(TABLE_DIMENSION, dims, NPY_INT);
    }

    



    for (unsigned int row = 0; row < num_rows; row++) {
        MYSQL_ROW mysql_row = mysql_fetch_row(data);
        unsigned long* lengths = mysql_fetch_lengths(data);

        for (unsigned short col = 0; col < num_fields; col++) {
            PyObject* py_value;
            if (mysql_row[col] == NULL) {
                py_value = Py_None;
                Py_INCREF(Py_None);
            } else {
                switch (np_dtype[col]) {
                    case NPY_SHORT:
                        py_value = PyLong_FromLong((long)*(short*)mysql_row[col]);
                        break;
                    case NPY_INT:
                        py_value = PyLong_FromLong(*(int*)mysql_row[col]);
                        break;
                    case NPY_FLOAT:
                        py_value = PyFloat_FromDouble(*(float*)mysql_row[col]);
                        break;
                    case NPY_DOUBLE:
                        py_value = PyFloat_FromDouble(*(double*)mysql_row[col]);
                        break;
                    case NPY_STRING:
                        py_value = PyUnicode_FromStringAndSize(mysql_row[col], lengths[col]);
                        break;
                    default:
                        py_value = Py_None;
                        Py_INCREF(Py_None);
                        break;
                }
            }
            PyArray_SETITEM((PyArrayObject*)nparray, PyArray_GETPTR2((PyArrayObject*)nparray, row, col), py_value);
            Py_DECREF(py_value);
        }
    }

    
}