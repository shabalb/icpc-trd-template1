from decimal import Decimal, getcontext

getcontext().prec = 50 
a = Decimal('0.1')
b = Decimal('0.2')
c = Decimal('3')

s = a + b               
d = c / Decimal('7')    
e = a ** 2             

# НИКОГДА не делай так 
# bad = Decimal(0.1)    

# Сравнение
print(a + b == Decimal('0.3'))  # True

# Совместимость: Decimal и float нельзя смешивать
# print(a + 0.2)  # Ошибка! TypeError

# Пример: 1/3 с высокой точностью
one_third = Decimal(1) / Decimal(3)
print(one_third) 
from fractions import Fraction

# Создание дробей: из целых, из строки, из пары (числитель, знаменатель)
a = Fraction(1, 3)          
b = Fraction('2/5')         
c = Fraction(0.25)          
d = Fraction(6, 9)          

s = a + b                   # 11/15
p = a * b                   # 2/15
q = a / b                   # 5/6
r = a ** 2                  # 1/9

# Доступ к числителю и знаменателю
print(d.numerator)          # 2
print(d.denominator)        # 3

x = float(a)               

print(a == Fraction('1/3')) # True

# Важно: Fraction — неявно не создаётся из float без явного вызова!
# Fraction(0.1) != Fraction('1/10'), т.к. 0.1 как float неточен
# Всегда передавай дробь как строку или два int