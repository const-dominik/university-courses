#lang plait
(define (append xs ys)
  (if (empty? xs)
      ys
      (cons (first xs) (append (rest xs) ys))))
#|
Zasada indukcji dla list:
Niech P będzie własnością list, taką, że:
i)  P(empty)
ii) Dla każdej wartości x i każdej listy xs,
    jeśli P(xs) to P((cons x xs))
Wówczas dla dowolnej listy xs zachodzi P(xs)


indukcja względem xs
P(xs) := dla każdego ys istnieje zs t.ż. (append xs ys) ≡ zs

Podstawa indukcji:
P(empty) := (append empty ys) ≡ ys

Krok indukcyjny:
Weźmy dowolne xs, ys i załóżmy, że istnieje takie zs, że (append xs ys) ≡ zs.
Pokażemy, że istnieje takie zs', że (append (cons x xs) ys) ≡ zs'

(append (cons x xs) ys) ≡ (cons x (append xs ys)) ≡ (cons x zs) (zatem istnieje takie zs',
w szczególności zs' ≡ (cons x zs)
|#