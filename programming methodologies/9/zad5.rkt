#lang plait

(define (fib-cps n ct)
  (if (< n 2)
      (ct n)
      (fib-cps (- n 1)
               (λ (x) (fib-cps (- n 2)
                               (λ (y) (ct (+ x y))))))))