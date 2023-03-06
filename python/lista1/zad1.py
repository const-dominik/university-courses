import decimal as d

def vat_faktura(lista):
    return sum(lista) * 0.23

def vat_paragon(lista):
    return sum(map(lambda x: x * 0.23, lista))

zakupy = [0.2, 0.5, 4.59, 6]
print(vat_faktura(zakupy) == vat_paragon(zakupy))



def vat_faktura(lista):
    return sum(lista) * d.Decimal('0.23')

def vat_paragon(lista):
    return sum(map(lambda x: x * d.Decimal('0.23'), lista))
zakupy_d = [d.Decimal('0.2'), d.Decimal('0.5'), d.Decimal('4.59'), d.Decimal('6')]
print(vat_faktura(zakupy_d) == vat_paragon(zakupy_d))
