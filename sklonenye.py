def f(c):
    print('это',''.join(s for s in c));
    c[-1]='ы';
    print('нет',''.join(s for s in c));
    c[-1]='е';
    print('к',''.join(s for s in c));
    c[-1]='у';
    print('вижу',''.join(s for s in c));
    c[-1]='ой';
    print('чем?',''.join(s for s in c));
    c[-1]='е';
    print('о',''.join(s for s in c));
    c[-1]='ы';
    print('это',''.join(s for s in c));
    c[-1]='';
    print('нет',''.join(s for s in c));
    c[-1]='ам';
    print('к',''.join(s for s in c));
    c[-1]='ы';
    print('вижу',''.join(s for s in c));
    c[-1]='ами';
    print('чем?',''.join(s for s in c));
    c[-1]='ах';
    print('о',''.join(s for s in c));

def g(c):
    print('это',''.join(s for s in c));
    c[-2]='к';
    c[-1]='а';
    print('нет',''.join(s for s in c));
    c[-2]='к';
    c[-1]='у';
    print('к',''.join(s for s in c));
    c[-2]='о';
    c[-1]='к';
    print('вижу',''.join(s for s in c));
    c[-2]='к';
    c[-1]='ом';
    print('чем?',''.join(s for s in c));
    c[-2]='к';
    c[-1]='е';
    print('о',''.join(s for s in c));
    c[-2]='к';
    c[-1]='и';
    print('это',''.join(s for s in c));
    c[-2]='к';
    c[-1]='ов';
    print('много',''.join(s for s in c));
    c[-2]='к';
    c[-1]='ам';
    print('к',''.join(s for s in c));
    c[-2]='к';
    c[-1]='и';
    print('вижу',''.join(s for s in c));
    c[-2]='ка';
    c[-1]='ми';
    print('чем?',''.join(s for s in c));
    c[-2]='к';
    c[-1]='ах';
    print('о',''.join(s for s in c));

c=list(input());
if c[-1]=='а':
    f(c);
elif c[-1]=='к' and c[-2]=='о':
    g(c);
else:
    print("тип склонения незнаком");

#работает всегда