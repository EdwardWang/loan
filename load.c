#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load.h"

struct loan_per_month_s{
    double return_capital;                     //每月还的本金
    double interest;                           //每月还的利息
    double left_total;                         //每月剩余总额
    double left_capital;                       //每月剩余本金
};

struct loan_s{
    double capital;                            //贷款总额
    int term;                                  //期数，每个月为1期
    double *year_rate;                         //年利率，有多少年就生成多少个数据
    struct loan_per_month_s *loan_per_month;   //每期对应的还款数据,期数时连续的，
                                               //所以使用数组比较方便，而且数组的下标代表当前期数
};

static void payment(loan_t *loan,calc_loan_per_month calc_pf);
//year就是年利率数组的个数
//第四个参数是计算贷款信息的函数
loan_t *loan_init(double capital,double *year_rate,int year, calc_loan_per_month calc_pf)
{
    struct loan_s *l = NULL;
    int term = year * 12;

    l = (struct loan_s*)malloc(sizeof(struct loan_s) + 
                sizeof(struct loan_per_month_s) * term + sizeof(double) * year);
    if (l != NULL) {
        l->capital = capital;
        l->term = term;
        l->year_rate = (double *)(l->loan_per_month+sizeof(struct loan_per_month_s)*term);
        memcpy(l->year_rate,year_rate,sizeof(double)*year);
        memset(l->loan_per_month,0,sizeof(struct loan_per_month_s)*term);
        payment(l,calc_pf);
    }
    return l;
}

static void payment(loan_t *loan,calc_loan_per_month calc_pf)
{
    int i;
    double pay_per_month = 0, capital;
    double cur_month_interest,cur_month_capital;

    capital = loan->capital;
    cur_month_interest = cur_month_capital = 0;
    for (i = 0; i < loan->term; i++) {
        pay_per_month = calc_pf(capital, loan->year_rate[i/12],loan->term-i);
        //计算当月利息，当月本金,剩余本金
        cur_month_interest = capital*(loan->year_rate[i/12]/12);
        cur_month_capital = pay_per_month-cur_month_interest;
        capital -= cur_month_capital;

        loan->loan_per_month[i].return_capital = cur_month_capital;
        loan->loan_per_month[i].interest = cur_month_interest;
        loan->loan_per_month[i].left_capital = capital;
        loan->loan_per_month[i].left_total = calc_pf(capital,loan->year_rate[(i+1)/12], loan->term-i-1);
    }
}

//获取到多少期为止还款总额
double get_total_until_n_term(loan_t *loan, int n, double *left_total)
{
    int i;double sum = 0;
    if (n > loan->term) return 0;

    for (i = 0; i < n; i++) {
        sum += loan->loan_per_month[i].interest + loan->loan_per_month[i].return_capital;
    }
    *left_total = loan->loan_per_month[n-1].left_total;
    return sum;
}

//打印所有期的相关信息
void print_loan_info(loan_t *loan)
{
    int i;
    printf("%20s%20s%20s%20s%20s%20s\n", "term","month pay", "month interest",
            "month capital", "left capital", "left total");
    for (i = 0; i < loan->term; i++) {
        printf("%20d%20f%20f%20f%20f%20f\n",(i+1), loan->loan_per_month[i].interest+loan->loan_per_month[i].return_capital,
               loan->loan_per_month[i].interest, loan->loan_per_month[i].return_capital,
               loan->loan_per_month[i].left_capital, loan->loan_per_month[i].left_total);
    }    
}
