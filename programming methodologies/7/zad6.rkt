#lang racket

(define/contract (foldl-map f a xs)
    (parametric->/c [a b] (-> (-> a b (cons/c a b)) b (listof a) (cons/c (listof a) b)))
    (define (it a xs ys)
        (if (null? xs)
            (cons (reverse ys) a)
            (let [(p (f (car xs) a))]
                (it (cdr p)
                    (cdr xs)
                    (cons (car p) ys)))))
(it a xs null))

(foldl-map (lambda (x a) (cons a (+ a x))) 0 '(1 2 3 4))