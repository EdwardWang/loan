#ifndef _LOAD_H_
#define _LOAD_H_
typedef struct loan_s loan_t;
typedef double (*calc_loan_per_month)(double,double,int);

loan_t *loan_init(double capital,double *year_rate,int term, calc_loan_per_month calc_pf);
double get_total_until_n_term(loan_t *loan, int n, double *left_total);
void print_loan_info(loan_t *loan);
loan_t *prepayment(loan_t *loan, double money,int term, calc_loan_per_month calc_pf);
double loans_left_total(loan_t *loan, int term);
#endif
