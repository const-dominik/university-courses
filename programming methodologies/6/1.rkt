#lang racket

#|
; Zasada indukcji dla list:
; Niech P będzie własnością list, taką, że:
; i)  P(empty)
; ii) Dla każdej wartości x i każdej listy xs,
;     jeśli P(xs) to P((cons x xs))
; Wówczas dla dowolnej listy xs zachodzi P(xs)

;zad1
(define (my-map f xs)
  (if (null? xs)
      null
      (cons (f (car xs))
            (my-map f (cdr xs)))))

(map f (map g xs)) ≡ (map (lambda (x) (f (g x))) xs)

P(xs) :≡ (map f (map g xs)) ≡ (map (lambda (x) (f (g x))) xs)

i) P(null)
L ≡ (map f (map g null)) ≡ (map f null) ≡ null
P ≡ (map (lambda (x) (f (g x))) null) ≡ null
L ≡ P

ii) weźmy dowolne xs i załóżmy, że (map f (map g xs)) ≡ (map (lambda (x) (f (g x))) xs) zachodzi,
    pokażemy że (map f (map g (cons x xs))) ≡ (map (lambda (x) (f (g x))) (cons x xs)) zachodzi

L ≡ (map f (map g (cons x xs))) ≡
    (map f (cons (g x) (map g xs)) ≡
    (cons (f (g x)) (map f (map g xs)))

P ≡ (map (lambda (x) (f (g x))) xs) ≡
    (cons ((lambda (x) (f (g x))) x) (map (lambda (x) (f (g x))) xs) ≡
    (cons (f (g x)) (map (lambda (x) (f (g x))) xs))

korzystając z założenia indukcyjnego,
L ≡ P
na mocy zasady indukcji, (map f (map g xs)) ≡ (map (lambda (x) (f (g x))) xs)
zachodzi dla każdego xs i dowolnych funkcji f i g
|#