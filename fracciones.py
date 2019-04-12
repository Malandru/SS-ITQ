def mcd(a, b):
    x = a % b
    if x == 0:
        return b
    else:
        return mcd(b, x)

def format(x):
    digs = len(x) - 2
    aux = 10 ** 4
    num = int(float(x) * aux)
    den = aux
    comun = mcd(num, den)
    print num / comun, '/', den / comun

def main():
    n = input()
    values = [raw_input() for v in range(n)]
    for v in values:
        format(v)

main()