# _*_ coding:utf-8 _*_
import Loan
import xlwt

rate = [0.059,0.049]
for i in range(0,28):
    rate.append(0.049)
loan = Loan.init(477000, rate, 360)
info = Loan.get_detail_info(loan)
#print info
#print Loan.loan_print(loan)
book = xlwt.Workbook()
sheet1 = book.add_sheet(u'贷款计算')
sheet1.write(0,0,u'每月还的本金')
sheet1.write(0,1,u'每月还的利息')
sheet1.write(0,2,u'每月剩余总额')
sheet1.write(0,3,u'每月剩余本金')

for i, item in enumerate(info):
    sheet1.write(i+1,0,item[0])
    sheet1.write(i+1,1,item[1])
    sheet1.write(i+1,2,item[2])
    sheet1.write(i+1,3,item[3])

book.save('test.xls')
