from calendar import c
import re

c=input()
print("\nrussian phone number. Posible format: +7(123)456 78 90|+7(123)456-78-90|+7(123)4567890|+71234567890 (8)")
tele=re.compile("(?:((?:\+7|7|8?)(?:\(| |-?)(?:495|499)(?:\)|-| ?)(?: )?(?:\d{3})(?: |-?)(?:\d{2})(?: |-?)(?:\d{2})))")
m=tele.findall(c)
print(m,'\n')

print("datas. Posible format:dd/mm/yyyy|dd.mm.yyyy|dd mm yyyy|d m yy(/,-,.)")
data=re.compile("(?:\d{2}|\d{1})(?:/|\.|-| )(?:\d{2}|\d{1})(?:/|\.|-| )(?:\d{4}|\d{2})")
m=data.findall(c)
print(m,'\n')

print("times. Posible format: AM,PM hh:mm|hh:mm")
time=re.compile("(?:PM|AM)?[ ]?[\d]+[ ]?[:][ ]?[\d][\d]?")
m=time.findall(c)
print(m,'\n')

print("card number. Posible format: фыва xxxx-xxxx-xxxx-xxxx|фыва xxxx xxxx xxxx xxxx")
card=re.compile("[\w]+[' ']?[0-9]{4}[- ][0-9]{4}[- ][0-9]{4}[- ][0-9]{4}",re.UNICODE)
m=card.findall(c)
print(m)
