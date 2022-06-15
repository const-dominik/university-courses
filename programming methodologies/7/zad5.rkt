#lang racket

(define/contract (x1 a b)
    (parametric->/c [a b] (-> a b a)) ;nnp
    a
)
(x1 1 2)

(define/contract (x2 x y z)
    (parametric->/c [a b c] (-> (-> a b c) (-> a b) a c)) ; ppn pn n p
    (x z (y z))
)

(x2 (lambda (x y) (+ x y)) (lambda (x) x) 4)

(define/contract (x3 x y)
    (parametric->/c [a b c] (-> (-> b c) (-> a b) (-> a c))) ; pn pn np
    (lambda (a) (x (y a)))
)

(x3 (lambda (x) x) (lambda (x) x))

(define/contract (x4 f)
    (parametric->/c [a] (-> (-> (-> a a) a) a)) ;npnp
    (f (lambda (x) x))
)

(x4 (lambda (x) x))