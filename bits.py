def count_bits(num):
    binario = '{0:b}'.format(num) #solo lo hace binario
    return binario.count('1')

def find_next(num):
    bits = count_bits(num)
    while True:
        num += 1
        if count_bits(num) == bits:
            print num
            break

def main():
    while True:
        num = input()
        if num == 0:
            break
        find_next(num)

main()