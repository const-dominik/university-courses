s = input()
letters = [0]*26
counter = 0

for letter in list(s):
  letters[ord(letter)-97] += 1

for i in range(26):
  counter += letters[i] % 2

if (counter == 0) or ((counter-1) % 2 == 0):
  print("First")
else: print("Second")