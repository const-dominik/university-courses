#lang plait

; raco pkg install plait

#|
('a 'b - > 'a )
(('a 'b - > 'c ) ('a - > 'b ) 'a - > 'c )
((( 'a - > 'a ) - > 'a ) - > 'a )
(('a - > 'b ) ('a - > 'c ) - > ('a - > ('b * 'c ) ) )
(('a - > ( Optionof ('a * 'b ) ) ) 'a - > ( Listof 'b ) )
|#

;zad1
(define (1a a b) a)
(define (1b f g a) (f a (g a)))
(define (1c [f : (('a -> 'a) -> 'a)]) (f (lambda (x) x)))
(define (1d f g) (lambda (x) (pair (f x) (g x))))
(define (1e [f : ('a -> (Optionof ('a * 'b)))] [a : 'a]) (cons (snd (some-v (f a))) empty))



;zad2
;( define ( apply f x ) ( f x ) ) ;(('a -> 'b) 'a -> 'b)
;przyjmuje f i x, x typu 'a jest aplikowalny do f więc f przyjmuje 'a i zwraca jakieś 'b, które tez jest wynikiem całej funkcji
( define ( compose f g ) ( lambda ( x ) ( f ( g x ) ) ) ) ; (('a -> 'b) ('c -> 'a) -> ('c -> 'b))
;x jest typu 'c, jest aplikowalny do g więc g przyjmuje 'c, wynik jest aplikowalny do f więc f przyjmuje to co zwraca g
;g zwraca coś ('b), więc wynikiem całej funkcji jest ('c -> 'b)
( define ( flip f ) ( lambda ( x y ) ( f y x ) ) ) ;(('a 'b -> 'c) -> ('b 'a -> 'c))
;lambda przyjmuje dwa argumenty x ('b) i y ('a), sa aplikowalne do f więc f przyjmuje 'a 'b i zwraca coś ('c), lambda zwraca to samo ('c)
( define ( curry f ) ( lambda ( x ) ( lambda ( y ) ( f x y ) ) ) ) ;(('a 'b -> 'c) -> ('a -> ('b -> 'c)))
; zwraca lambde przyjmujaca x ('a) i zwracającą lambdę przyjmującą y ('b), aplikuje te dwa argumenty do f, więc f przyjmuje 'a 'b,
; f zwraca coś ('c) i to zwraca wewnetrzna lambda


;zad7
(define (remove-duplicates xs)
  (letrec [(it (lambda (xs1 xs2)
                (if (empty? xs2)
                    xs1
                    (it (cons (first xs2) xs1)
                        (filter (lambda (x) (not (equal? x (first xs2)))) (rest xs2))))))]
    (it empty xs)))

( define-type Prop
( var [ v : String ])
( conj [ l : Prop ] [ r : Prop ])
( disj [ l : Prop ] [ r : Prop ])
( neg [ f : Prop ]) )

(define (free-vars form)
    (letrec [(it (lambda (f)
                  (cond [(var? f) (cons (var-v f) empty)]
                        [(conj? f) (append (it (conj-l f)) (it (conj-r f)))]
                        [(disj? f) (append (it (disj-l f)) (it (disj-r f)))]
                        [else (it (neg-f f))]
                        )))]
      (it form)))
(remove-duplicates (free-vars (disj (conj (var "a") (var "a")) (neg (var "f")))))
;zad8

(define (eval dict form)
  (letrec [(it (lambda (f)
                  (cond [(var? f) (if (none? (hash-ref dict (var-v f)))
                                             (error 'eval (string-append "Brak wartościowania dla " (to-string (var-v f))))
                                             (some-v (hash-ref dict (var-v f))))]
                        [(conj? f) (and (it (conj-l f)) (it (conj-r f)))]
                        [(disj? f) (or (it (disj-l f)) (it (disj-r f)))]
                        [else (not (it (neg-f f)))]
                        )))]
      (it form)))

(define some-dict (hash (list
         (pair "a" #t) (pair "b" #f) (pair "f" #t))))
 ;(a^b)v(~f)
(define some-formula (disj (conj (var "a") (var "b")) (neg (var "f"))))
(eval some-dict some-formula)

;zad9
