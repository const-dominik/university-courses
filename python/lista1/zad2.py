def only_alpha(str):
    return "".join([x for x in str if x.isalpha()])

def is_palindrom(text):
    transformed = only_alpha(text).lower()
    return transformed == transformed[::-1]

print(is_palindrom("rotor"))
print(is_palindrom("oko"))
print(is_palindrom("kot"))
print(is_palindrom("kamil ślimak"))
print(is_palindrom("Kobyła ma mały bok."))
print(is_palindrom("Eine güldne, gute Tugend: Lüge nie!"))
print(is_palindrom("Míč omočím."))
