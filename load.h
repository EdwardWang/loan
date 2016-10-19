#ifndef _LOAD_H_
#define _LOAD_H_

struct loan_per_month_s{
    double return_capital;                     //每月还的本金
    double interest;                           //每月还的利息
    double left_total;                         //每月剩余总额
    double left_capital;                       //每月剩余本金
};

typedef struct loan_s loan_t;
typedef double (*calc_loan_per_month)(double,double,int);

loan_t *loan_init(double capital,double *year_rate,int term, calc_loan_per_month calc_pf);
void loan_free(loan_t *loan);
double get_total_until_n_term(loan_t *loan, int n, double *left_total);
void print_loan_info(loan_t *loan);
loan_t *prepayment(loan_t *loan, double money,int term, calc_loan_per_month calc_pf);
double loans_left_total(loan_t *loan, int term);
int loan_get_detail_info(loan_t *loan,struct loan_per_month_s **per_month_info, int *n);
#endif
