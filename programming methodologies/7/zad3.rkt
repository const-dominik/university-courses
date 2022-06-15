#lang racket

(define/contract (suffixes xs)
    (parametric->/c [a] (-> (listof a) (listof (listof a))))
    (define (it xs ys)
        (if (null? xs)
            (append ys (list xs))
            (it (rest xs) (append ys (list xs))))
    )
    (it xs null)
)
(suffixes '(1 2 3 4 5))
(suffixes '())