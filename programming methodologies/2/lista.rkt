#lang racket


;zad 1
(define (fib n)
  (cond
    [(= n 0) 0]
    [(= n 1) 1]
    [else (+ (fib (- n 1)) (fib (- n 2)))])
  )

(define (fib-iter n)
  (define (iter n prev1 prev2)
    (if (= n 0)
        prev1
        (iter (- n 1) prev2 (+ prev1 prev2))))
  (iter n 0 1))
(fib 5)
;rekurencja wolniejsza - przy kazdym wywolaniu na stack zostaja dodane kolejne dwa wywolania

;zad 2
(define-struct matrix (a b c d))

;|a b|
;|c d|

(define (dot-product a b c d)
  (+ (* a c) (* b d)))

(define matrix-id (matrix 1 0 0 1))

(define (matrix-mult m n)
      (let
          ([a (dot-product (matrix-a m) (matrix-b m) (matrix-a n) (matrix-c n))]
           [b (dot-product (matrix-a m) (matrix-b m) (matrix-b n) (matrix-d n))]
           [c (dot-product (matrix-c m) (matrix-d m) (matrix-a n) (matrix-c n))]
           [d (dot-product (matrix-c m) (matrix-d m) (matrix-b n) (matrix-d n))])
        (matrix a b c d)))

(define (matrix-expt m k)
  (define (loop m2 n)
    (if (= n 1)
        m2
        (loop (matrix-mult m2 m) (- n 1))))
  (if (= k 0) matrix-id (loop m k)))

(define (fib-matrix k)
  (let ([m (matrix 1 1 1 0)])
    (let ([n (matrix-expt m k)])
      (matrix-b n))))

;zad 3
(define (matrix-squared m) (matrix-mult m m))
(define (matrix-expt-fast m k)
  (cond
    [(= k 0) matrix-id]
    [(odd? k) (matrix-mult m (matrix-squared (matrix-expt-fast m (/ (- k 1) 2))))]
    [else (matrix-squared (matrix-expt-fast m (/ k 2)))]
  ))

(define (fib-fast k)
  (let ([m (matrix 1 1 1 0)])
    (let ([n (matrix-expt-fast m k)])
      (matrix-b n))))

;zad 4
(define (elem? x xs)
  (define (it x xs)
    (if (null? xs)
        #f
        (if (equal? (car xs) x)
            #t
            (it x (cdr xs)))))
  (it x xs))

;zad 5
(define (maximum xs)
  (define (it curr_max curr_list)
    (if (null? curr_list)
        curr_max
        (if (> (car curr_list) curr_max)
            (it (car curr_list) (cdr curr_list))
            (it curr_max (cdr curr_list)))))
    (it -inf.0 xs))

;zad 6
(define (suffixes xs)
  (define (it result curr_list)
    (let ([new_list (append result (list curr_list))])
    (if (null? curr_list)
        new_list
        (it new_list (cdr curr_list)))))
  (it (list) xs))

(suffixes '(1 2 3 4 5))

;zad 7
(define (sorted? xs)
  (define (it last curr_list)
    (if (null? curr_list)
        #t
        (if (< (car curr_list) last)
            #f
            (it (car curr_list) (cdr curr_list)))))
  (if (null? xs)
      #t
      (it (car xs) (cdr xs))))

;zad 8
(define (minimum xs)
  (define (it curr_min curr_list)
    (if (null? curr_list)
        curr_min
        (if (< (car curr_list) curr_min)
            (it (car curr_list) (cdr curr_list))
            (it curr_min (cdr curr_list)))))
    (it +inf.0 xs))

(define (select xs)
  (let ([min (minimum xs)])
    (cons min (remove min xs))))

(define (select-sort xs)
  (define (it sorted rest)
    (let ([selected (select rest)])
      (if (null? rest)
          sorted
          (it (append sorted (list (car selected))) (cdr selected)))))
  (it null xs))