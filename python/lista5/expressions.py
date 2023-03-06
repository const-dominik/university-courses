add_brackets = lambda s: f"({s})"
should_add_brackets = lambda w: not (isinstance(w, Zmienna) or isinstance(w, Stala))
get_part_exp = lambda w: add_brackets(w) if should_add_brackets(w) else str(w)
get_whole_exp = lambda w1, w2, x: f"{get_part_exp(w1)} {x} {get_part_exp(w2)}"

class Wyrazenie:
    def oblicz(self, zmienne):
        self.oblicz(zmienne)
    
    def __add__(self, w1, w2):
        return Wyrazenie(Dodaj(w1, w2))

    def __mul__(self, w1, w2):
        return Wyrazenie(Razy(w1, w2))

    @staticmethod
    def get_vars(w):
        vars = set()
        if isinstance(w, Zmienna):
            vars.add(w.key)
        elif not isinstance(w, Stala):
            vars.update(Wyrazenie.get_vars(w.w1), Wyrazenie.get_vars(w.w2))
        return vars


    @staticmethod
    def derivative(w):
        vars = Wyrazenie.get_vars(w)
        if len(vars) > 1:
            raise NotAFunction()
        if isinstance(w, Dodaj) or isinstance(w, Odejmij):
            return Dodaj(Wyrazenie.derivative(w.w1), Wyrazenie.derivative(w.w2))
        if isinstance(w, Razy):
            return Dodaj(Razy(Wyrazenie.derivative(w.w1), w.w2), Razy(w.w1, Wyrazenie.derivative(w.w2)))
        if isinstance(w, Podziel):
            return Podziel(Odejmij(Razy(Wyrazenie.derivative(w.w1), w.w2), Razy(w.w1, Wyrazenie.derivative(w.w2))), Razy(w.w2, w.w2))
        if isinstance(w, Stala):
            return Stala(0)
        if isinstance(w, Zmienna):
            return Stala(1)

class Razy(Wyrazenie):
    def __init__(self, w1, w2):
        self.w1 = w1
        self.w2 = w2

    def __str__(self):
        return get_whole_exp(self.w1, self.w2, "*")

    def oblicz(self, zmienne):
        return self.w1.oblicz(zmienne) * self.w2.oblicz(zmienne)

class Podziel(Wyrazenie):
    def __init__(self, w1, w2):
        self.w1 = w1
        self.w2 = w2

    def __str__(self):
        return get_whole_exp(self.w1, self.w2, "/")

    def oblicz(self, zmienne):
        mianownik = self.w2.oblicz(zmienne)
        if mianownik == 0:
            raise DivideByZero()
        return self.w1.oblicz(zmienne) / mianownik

class Dodaj(Wyrazenie):
    def __init__(self, w1, w2):
        self.w1 = w1
        self.w2 = w2

    def __str__(self):
        return get_whole_exp(self.w1, self.w2, "+")

    def oblicz(self, zmienne):
        return self.w1.oblicz(zmienne) + self.w2.oblicz(zmienne)

class Odejmij(Wyrazenie):
    def __init__(self, w1, w2):
        self.w1 = w1
        self.w2 = w2

    def __str__(self):
        return get_whole_exp(self.w1, self.w2, "-")

    def oblicz(self, zmienne):
        return self.w1.oblicz(zmienne) - self.w2.oblicz(zmienne)

class Zmienna(Wyrazenie):
    def __init__(self, key):
        if isinstance(key, str):
            self.key = key
        else:
            raise NonStringKeyValue()

    def __str__(self):
        return self.key

    def oblicz(self, zmienne):
        if self.key in zmienne:
            return zmienne[self.key]
        raise NonExistingVariable(self.key)

class Stala(Wyrazenie):
    def __init__(self, val):
        if isinstance(val, int) or isinstance(val, float):
            self.val = val
        else:
            raise NonNumberConstantValue()

    def __str__(self):
        return str(self.val)

    def oblicz(self, zmienne):
        return self.val

class NonNumberConstantValue(Exception):
    def __init__(self):
        print("Your constant has to be a number.")

class NonStringKeyValue(Exception):
    def __init__(self):
        print("Your variable name has to be a a string.")

class NonExistingVariable(Exception):
    def __init__(self, key):
        print(f"Variable {key} doesn't have a defined value.")

class NotAFunction(Exception):
    def __init__(self):
        print("Expression has more than one variable.")

class DivideByZero(Exception):
    def __init__(self):
        print("Can't divide by 0.")

#some examples
expr1 = Dodaj(Stala(5), Zmienna("x"))
expr2 = Dodaj(Zmienna("y"), Zmienna("x"))
expr3 = Odejmij(Zmienna("x"), Stala(20))
expr4 = Razy(expr1, expr3)
expr5 = Podziel(expr4, expr2)

wart = { "x": 5, "y": 1 }

def print_nicely(exp):
    print(f"{exp} = {exp.oblicz(wart)}, pochodna: { Wyrazenie.derivative(exp) }")

for exp in [expr1, expr3, expr4]:
    print_nicely(exp)

print(expr2)
print(expr5)

#cant print nicely e2 and e5 cause those have more than one variable and we get an exception