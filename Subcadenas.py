import sys

def getStringDivitions(s,n,stringDivitions):
    for x in range(len(s)):
        if (x+n) <= len(s):
            try:
                stringDivitions[s[x:(x+n)]] += 1
            except:
                stringDivitions[s[x:(x+n)]] = 1
    return stringDivitions

n = int(input())
data = []
randomString = input()
while(randomString != 'FIN'):
    data.append(randomString)
    randomString = input()

for x in data:
    if len(x) < n:
        print('Sin solucion')
    else:
        stringDivitions = getStringDivitions(x,n,{})
        print(stringDivitions)
        lisTitle = []
        listNumber = []
        for x in stringDivitions:
            lisTitle.append(x)
            listNumber.append(stringDivitions[x])

        if len(lisTitle) == 1:
            print('{} {}'.format(lisTitle[0],listNumber[0]))
        else:
            tempNumber = 0
            tempTitle = ''
            c = 0
            for x in range(len(lisTitle)):
                if listNumber[x] > tempNumber:
                    tempNumber = listNumber[x]
                    tempTitle = lisTitle[x]
                elif listNumber[x] == tempNumber:
                    c += 1
            if c > 0:
                print('varias soluciones')
            else:
                print('{} {}'.format(tempTitle,tempNumber))
