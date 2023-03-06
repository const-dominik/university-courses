def transform_word(word):
    letters = []
    i = 0
    counter = 0

    while i < len(word):
        counter += 1
        if i + 1 < len(word) and word[i+1] != word[i]:
            letters.append((counter, word[i]))
            counter = 0
        i += 1
    
    letters.append((counter, word[-1]))

    return letters

def dekompresja(l):
    word = ""

    for i in range(len(l)):
        counter, letter = l[i]
        word += letter*counter

    return word

f = open("text.txt", "r")
lines = f.readlines()
text = lines[0]
comp = transform_word(text)
decomp = dekompresja(comp)
print(comp)
print(text == decomp)