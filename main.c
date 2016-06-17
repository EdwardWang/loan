#include <stdio.h>
#include "load.h"

extern double 
p_i(double capital,double year_rate,int term);

int main(int argc, char *argv[])
{
    loan_t *loan = NULL;
    double rate[] = { 0.059, 0.049, 0.049, 0.049, 0.049,
                        0.049, 0.049, 0.049, 0.049, 0.049,
                        0.049, 0.049, 0.049, 0.049, 0.049,
                        0.049, 0.049, 0.049, 0.049, 0.049,
                        0.049, 0.049, 0.049, 0.049, 0.049,
                        0.049, 0.049, 0.049, 0.049, 0.049};
    loan = loan_init(477000,rate,sizeof(rate)/sizeof(double),p_i);
    print_loan_info(loan);
    return 0;
}
