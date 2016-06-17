#include <math.h>
//等额本息计算公式
double p_i(double capital,double year_rate,int term)
{
    double month_rate = year_rate/12;
    return ( capital * month_rate * pow(1+month_rate, term) / (pow(1+month_rate,term)-1) );
}
