![](https://i.imgur.com/JCOHwpq.png)

Scheduler UNIXowy to round robin with multilevel feedback.
Ogólny przebieg algorytmu:

1. wybieramy proces z kolejki o najwyższym priorytecie
2. jeżeli mamy wiele procesów o tym samym priorytecie, wybieramy ten, który najdłużej był w kolejce `ready`
3. jeżeli nie mamy żadnego procesu do wykonania, zamrażamy algorytm do czasu gdy wystąpi przerwanie

![](https://i.imgur.com/ZFcoF8W.png)

Parametry planowania:
Każdy proces ma przypisane pole priorytetu. Priorytet procesu w trybie użytkownika jest funkcją jego ostatniego użycia CPU - im więcej CPU użył ostatnio, tym niższy priorytet.
Priorytety procesów możemy podzielić na dwie klasy: użytkownika i jądra

![](https://i.imgur.com/lvOqptj.png)

Klasy te są rozdzielone pewnym progiem. Procesy klasy użytkownika są poniżej tego progu, a procesy z priorytetami jądra powyżej, jak widać to na obrazku 8.2.
Priorytety jądra są dalej podzielone: procesy o niskim priorytecie jądra budzą się po otrzymaniu sygnału, podczas gdy procesy o wysokim priorytecie jądra nadal śpią. (np. niski priorytet - oczekiwanie na wejście z terminala TTY, zakończenie pracy dziecka, wysoki priorytet śpi, czekając aż będą w pełni gotowe do wznowienia pracy, np. aż zwolni się buffer). Priorytety w jądrze są jakoś logicznie ustawione; przykładowo `waiting for Disk IO` ma wyższy priorytet niż `waiting for Buffer`, bo buffer może być zajęty przez proces `waiting for disk IO`, więc wykonanie tego procesu może zwolnić potrzebne nam zasoby.
Procesy, które śpią, otrzymują priorytet zależny od powodu uśpienia.
Jądro odpowiednio dopasowuje priorytet procesu przechodzącego z kernel mode do user mode. Priorytet jest obniżany, jako że dopiero co skorzystał z cennych zasobów jądra.
Co więcej, obsługa zegara dopasowuje priorytety w user mode co sekundę i wymusza na jądrze wywołanie algorytmu planowania, aby zapobiec monopolizacji CPU przez pojedynczy proces. Ostatnie użycie procesora przez proces jest dostosowywanie zgodnie z funkcją
$decay(CPU) = CPU/2$,
natomiast sam priorytet zgodnie ze wzorem
priority = ("recent CPU usage"/2) + (base level user priority)

Proces z uprawnieniami superuser może także kontrolować priorytety poprzez funkcję `nice(value)`, wtedy do powyższego wzoru dodajemy jeszcze `nice value`.

**Przykład**
![](https://i.imgur.com/H2lMQfW.png)

Im niższa liczba `priority`, tym wyższy priorytet. Zaczynamy od time 0, proces A. Zegar przerywa 60 razy na sekundę, inkrementując licznik CPU. Po sekundzie, która jest tutaj kwantem czasu, jądro rekalkuluje priorytety. CPU count jest decayowany, priorytet dostostosowany przez wzór priority = "recent CPU usage"/2 (CPU count zdecayowany = 30, recent usage/2 = 15) + base priorty = 15 + 60 = 75. Teraz mamy dwa procesy do wyboru - B i C, z tym samym priorytetem. Proces B czeka dłużej, więc jest wybierany i wszystko się powtarza, aż procesy zostaną wykonane.
