import random

def only_alpha(txt):
    return "".join([x for x in txt if x.isalpha()])

def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    words = tekst.split()
    short_words = [word for word in words if len(only_alpha(word)) <= dl_slowa]

    while len(short_words) > liczba_slow:
        short_words.pop(random.randrange(len(short_words)))
    
    if short_words[-1][-1] != ".":
        short_words[-1] = short_words[-1] + "."

    short_words[-1] = short_words[-1] + " "
    short_words[0] = short_words[0][0].upper() + short_words[0][1:]

    return " ".join(short_words)

f = open("text.txt", "r")
lines = f.readlines()
sentences = lines[0].split(". ")
simplified = map(lambda s: uprosc_zdanie(s, 10, 5), sentences)
simplified_text = "".join(simplified)
print(simplified_text)