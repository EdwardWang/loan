#include <stdio.h>
#include "load.h"

extern double 
p_i(double capital,double year_rate,int term);

int main(int argc, char *argv[])
{
    double left_total16,left_total_tiqian,left_total_tiqian17;
    loan_t *loan = NULL;
    loan_t *loan16 = NULL;
    loan_t *loan17 = NULL;
    double rate[] = { 0.0615, 0.049, 0.049, 0.049, 0.049,
                        0.049, 0.049, 0.049, 0.049, 0.049,
                        0.049, 0.049, 0.049, 0.049, 0.049,
                        0.049, 0.049, 0.049, 0.049, 0.049,
                        0.049, 0.049, 0.049, 0.049, 0.049,
                        0.049, 0.049, 0.049, 0.049, 0.049};
    loan = loan_init(477000,rate,(sizeof(rate)/sizeof(double))*12,p_i);
    //print_loan_info(loan);
    loan16 = prepayment(loan,10000, 16,p_i);
    loan17 = prepayment(loan,20000, 16,p_i);
    left_total16 = loans_left_total(loan, 16);
    left_total_tiqian = loans_left_total(loan16, 1);
    left_total_tiqian17 = loans_left_total(loan17, 1);
    printf("%.2f\n", left_total16-left_total_tiqian);
    printf("%.2f\n", left_total16-left_total_tiqian17);
    printf("-----------------------------\n");
    print_loan_info(loan16);
    printf("-----------------------------\n");
    print_loan_info(loan);
    return 0;
}
