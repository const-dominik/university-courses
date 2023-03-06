n = int(input())

while (n != 0):
  n -= 1
  s = input()
  
  used = []
  kbr = []
  index = 0
  length = 0
  isBad = False

  for c in s:
    if c in used:
      if index > 0 and kbr[index-1] == c: index -= 1
      elif index < length-1 and kbr[index+1] == c: index += 1
      else:
        print("NO")
        isBad = True
        break
    else:
      if index == 0:
        kbr.insert(index, c)
      elif index == length-1:
        index +=1
        kbr.insert(index, c)
      else:
        print("NO")
        isBad = True
        break
      used.append(c)
      length += 1
  
  if not isBad:
    print("YES")

    alphabet = list("abcdefghijklmnopqrstuvwxyz")
    unused = [x for x in alphabet if x not in used]

    print("".join(kbr) + "".join(unused))