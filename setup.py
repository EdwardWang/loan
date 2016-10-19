# _*_ conding:utf-8 _*_
from distutils.core import setup,Extension
module1 = Extension('Loan',sources=['loanmodule.c', 'formula.c', 'load.c'])
setup(name='Loan',
      version = '1.0',
      description = 'This is a Loan package',
      ext_modules = [module1])
