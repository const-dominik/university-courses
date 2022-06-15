#lang racket


;zad1
;'(( car ( a . b ) ) (* 2) )
(list (list 'car (cons 'a 'b)) (list '* 2))
;`( ,( car '( a . b ) ) ,(* 2) )
(list (`,car (cons 'a 'b)) (`,* 2))
;'((+ 1 2 3) ( cons ) ( cons a b ) )
(list (list '+ 1 2 3) (list 'cons) (list 'cons 'a 'b))


;zad2
(define (product xs)
    (foldl * 1 xs))

;zad3

;1.
;(( lambda ( x y ) (+ x (* x y ) ) ) 1 2)
;(+ 1 (* 1 2))
;(+ 1 2)
;3

;2.
;(( lambda ( x ) x ) ( lambda ( x ) x ) )
;(lambda (x) x)

;3.
;(( lambda ( x ) ( x x ) ) ( lambda ( x ) x ) )
;((lambda (x) x) (lambda (x) x))
;(lambda (x) x)

;4.
;((lambda (x) (x x)) (lambda (x) (x x)))
;((lambda (x) (x x)) (lambda (x) (x x)))
;......



;zad4
(define (square x)
  (* x x))

(define (inc x)
  (+ x 1))

(define (my-compose a b)
  (lambda (x) (a (b x))))

((my-compose square inc) 5)
;((lambda (x) (square (inc x))) 5)
;(square (inc 5))
;(square 6)
;36

((my-compose inc square) 5)
;((lambda (x) (inc (square x))) 5)
;(inc (square 5))
;(inc 25)
;26

;zad5
(define (negatives n)
  (build-list n (lambda (x) (* -1 (+ x 1)))))

(define (reciprocals n)
  (build-list n (lambda (x) (/ 1 (+ x 1)))))

(define (evens n)
  (build-list n (lambda (x) (* x 2))))

(define (identityM n)
  (build-list n
              (lambda (x)
                  (build-list n
                              (lambda (y) (if (= x y) 1 0))))))

;zad7
( define ( foldr-reverse xs )
( foldr ( lambda ( y ys ) ( append ys ( list y ) ) ) null xs ) )
;np (foldr-reverse '(4 3 2 1))
;(append null 4) - 1 cons
;(append (append null 4) 3) - 2 cons
;(append (append (append null 4) 3) 2) - 3 cons
;(append (append (append (append null 4) 3) 2) 1) - 4 cons
;(n*(n+1)/2) consow, z czego (n*(n+1)/2 - n) to nieuzytki
;zlozonosc O(n^2)