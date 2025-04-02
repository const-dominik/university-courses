![](https://i.imgur.com/hYKcftY.png)

Najwięskza - 100, wszystko działa jak należy

Najmniejsza - chcemy zcancelować jak najwięcej operacji dodawania jedynek

operacja counter = counter + 1 jest podzielna

temp = counter // odczyt
temp = temp + 1 // modyfikacja
counter = temp // zapis

najgorszy przypadek:

P1 i P2 wczytują Counter - wartość 0
P1 dodaje 49 razy jedynkę (z 50), wtedy aktywuje się P2. Ma on wczytaną wartość countera 0.
P2 zwiększa counter o 1 i zapisuje go. Counter = 1. P1 wczytuje tą wartość.
P2 dodaje 49 razy jedynkę. Pętla dla P2 zostaje zakończona, wartość countera to 50.
P1 musi przejść przez ciało pętli ostatni raz. Ma wczytaną wartość 1, zwiększa ją o 1 i kończy pętlę.
Końcowa wartość countera to 2.
