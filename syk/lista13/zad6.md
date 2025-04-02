![](https://i.imgur.com/CI4oeSP.png)

SJF - shortest job first
SRT - shortest remaining time first

SRT różni się od SJF tym, że kiedy przychodzi krótszy proces poprzedniemu jest odbierany procesor na rzecz krótszego procesu
![](https://i.imgur.com/SAIsQ2z.png)

a)
$ \alpha = 0, \tau*{0} = 100ms $
$\tau*{n+1} = \tau_n$

Nie zwracamy uwagi na rzeczywisty czas wykonania, zakładamy że każda faza trwa równie długo.

b)

$ \alpha = 0.99, \tau\_{0} = 10ms $

Nie zwracamy prawie w ogóle uwagi na przewidywany czas wykonania:

$\tau_{n_1} = 0.99*t_{0} + 0.01*\tau_{0}$
