import random
import string
import time

def upper(string):
    k = random.randint(1, 2)
    if k==1:
        return string
    else:
        a = []
        for i in range(len(string)):
            a.append(string[i])
        for i in range(random.randint(0,len(a))):
            j=random.randint(0,len(a)-1)
            a[j]=a[j].upper()
        return ''.join(a)

def gtalk():
    return upper('gtalk:')

def contact():
    ident = ['talk', 'chat']
    k = random.randint(0, 1)
    return upper(str(ident[k]))

def userorserver(a=-5, b=80):
    letters = random.randint(a, b)
    s = random.randint(1,3)
    if s == 1 :
        return ''.join(random.choices(string.ascii_letters + string.digits, k=letters))
    elif s == 2 :
        return ''.join(random.choices(string.ascii_letters, k=letters))
    else:
        return ''.join(random.choices(string.digits, k=letters))

def zona(a=-5, b=10):
    letters = random.randint(a, b)
    return ''.join(random.choices(string.ascii_letters, k=letters))

def jid():
    return upper('jid')

def mutate(self):
    gstring = self
    action = random.randint(0, 4)
    if action == 0:
        return gstring
    for k in range(random.randint(1, 3)):
        if len(gstring) != 0:
            if action == 1:
                k = (random.randint(1, 50) // 2 * action + 42) % (len(gstring)+1)
                child = gstring[k: k + k*k*k % len(gstring)]
            elif action == 2:
                for kk in range(10):
                    n = random.randint(1, len(gstring))
                    gstring = gstring[:n] + chr(random.randint(32, 126)) + gstring[n+1:]
            elif action == 3:
                a = len(gstring)
                gstring = gstring[random.randint(0, a//2): random.randint(a//2, a-1)] + gstring[random.randint(0, a//2):
                                                                                          random.randint(a//2, a-1)]
        action = (action + k*k) % 4
    return gstring

outFile = open('../gen_strings.txt', 'w', encoding='utf8')
print('Enter number of strings:')
n = int(input())
i = 0
n1 = time.time()
for i in range(n):
    address = gtalk()+contact()+'?'+jid()+'='+userorserver()+'@'+userorserver()+'.'+zona()
    outFile.write(mutate(address)+'\n')
n2 = time.time()
print(n2 - n1)
outFile.close()
