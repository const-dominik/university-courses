**Multilevel feedback queues**

Użycie zwyczajnych wielopoziomowych kolejek zakłada, że zamiast pojedynczej kolejki `ready` mamy ich wiele. Każda z nich może mieć inny algorytm planowania procesów, potrzebujemy metody determinacji do której z kolejek powinien zostać dodany proces.

Używając kolejek wielopoziomowych ze sprzężeniem zwrotnym, główna różnica polega na tym, że proces może być przemieszczany pomiędzy różnymi poziomami. Aby zdefiniować MLFQ (multilevel feedback queue) potzebujemy:

-   liczby kolejek
-   algorytmu planowania dla każdej z kolejek
-   metody determinacji kiedy proces powinien zostać przemieszczony do wyższego/niższego poziomu
-   metody determinacji do której kolejki powinien zostać dodany nowy proces.

Obsługa różnych klas procesów odbywa się poprzez nadanie poszczególnym klasom priorytetów.

![](https://i.imgur.com/5rSLrsZ.png)

Reguły promocji i degradacji to nic innego jak metoda determinacji kiedy proces powinien zostać przemieszczony do innej kolejki. Zapobiega to sytuacjom, że bardzo długi proces może blokować kolejkę o wysokim priorytecie i sytuacjom, kiedy proces bardzo długo nie jest obsługiwany przez to, że znajduje się w kolejce o niskim priorytecie.

![](https://i.imgur.com/cbiIEFh.png)

Przykład z wykładu:
Mamy MLFQ o 3 poziomach, opisane jak na slajdzie. Kiedy nowy proces jest dodawany do kolejki $Q_0$, czeka na swoją kolej do użycia procesora. Kiedy uzyskuje dostęp, wykonuje swoje należne 8ms obliczeń. Jeśli w tym czasie proces zostanie ukończony to super, przechodzimy do kolejnego procesu z kolejki. W przeciwnym wypadku, proces jest przeniesiony na koniec kolejki $Q_1$ i kontynuujemy wykonywanie procesów z $Q_0$ aż będzie ona pusta. Wtedy przechodzimy do $Q_1$ i dzieje się to samo - proces jest wykonywany, jeśli nie zostaje ukończony to przerzucamy do niższej kolejki. Po przerobieniu procesów z $Q_1$ przechodzimy do ostatniej kolejki, w której już wszystkie procesy są wykonywane po kolei.
