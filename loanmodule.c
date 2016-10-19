#include <Python.h>
#include <stdlib.h>
#include "load.h"
extern double 
p_i(double capital,double year_rate,int term);

//释放空间接口函数
//所有注册的对象可能都放在一个hash表中或者树中
static void Loan_del(PyObject *obj)
{
    loan_free(PyCapsule_GetPointer(obj,"Loan"));
}

static loan_t *PyStruct_AsLoan_s(PyObject *obj)
{
    return (loan_t *)PyCapsule_GetPointer(obj,"Loan");
}

//从loan指针创建一个PyObject对象
static PyObject *Loan_fromLoan(loan_t *loan, int must_free)
{
    return PyCapsule_New(loan, "Loan", must_free ? Loan_del:NULL);
}

static PyObject *Loan_init(PyObject *self,PyObject *args)
{
    loan_t *loan;
    double capital;
    double *year_rate = NULL;
    int term;long length;
    int i;
    PyObject *listobj;

    if (!PyArg_ParseTuple(args,"dOi", &capital,&listobj,&term)) {
        return NULL;
    }
    length = PyList_Size(listobj);
    year_rate = (double *)malloc(sizeof(double) * length);
    if (!year_rate) return NULL;
    for (i = 0; i < length; i++) {
        PyObject *temp = PyList_GetItem(listobj, i);
        year_rate[i] = PyFloat_AsDouble(temp);
    }

    loan = loan_init(capital, year_rate, term, p_i);
    free(year_rate);
    return Loan_fromLoan(loan, 1);
    //return Py_BuildValue("i",17);
}

static PyObject *Loan_get_detail_info(PyObject *self, PyObject *args)
{
    struct loan_per_month_s *per_month_info; 
    int count, i;
    PyObject *obj = NULL;
    if (!PyArg_ParseTuple(args, "O", &obj)) {
        return NULL;
    }
    loan_t * loan = PyStruct_AsLoan_s(obj);
    if (!loan) return NULL;
    loan_get_detail_info(loan, &per_month_info, &count);
    if (count <= 0 || per_month_info == NULL ) return NULL;
    PyObject *listobj = PyList_New(count);
    for (i = 0; i < count; i++) {
        PyObject *temp = Py_BuildValue("(dddd)", per_month_info[i].return_capital,
                                per_month_info[i].interest,
                                per_month_info[i].left_total,
                                per_month_info[i].left_capital);
        PyList_SetItem(listobj, i, temp);
    }
    return listobj;
}

static PyObject *Loan_print(PyObject *self, PyObject *args)
{
    PyObject *obj = NULL;
    if (!PyArg_ParseTuple(args, "O", &obj)) {
        return NULL;
    }
    loan_t * loan = PyStruct_AsLoan_s(obj);
    if (!loan) return NULL;
    print_loan_info(loan);
    return Py_None;
}

static PyMethodDef LoanMethod[] = {
    {"init", Loan_init, METH_VARARGS,"init a loan object"},
    {"get_detail_info", Loan_get_detail_info, METH_VARARGS,"get loan per month info"},
    {"loan_print", Loan_print, METH_VARARGS,"print loan info per month"},
    {NULL,NULL},
};

void initLoan()
{
    Py_InitModule("Loan", LoanMethod);
}
