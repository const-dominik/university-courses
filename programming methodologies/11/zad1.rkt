#lang plait

(define-syntax my-and
  (syntax-rules ()
    [(my-and) #t]
    [(my-and x1) x1]
    [(my-and x1 x2 ...)
     (if x1
         (my-and x2 ...)
         #f)])) 

(define-syntax my-or
  (syntax-rules ()
    [(my-or) #f]
    [(my-or x1) x1]
    [(my-or x1 x2 ...)
     (if x1
         #t
         (my-or x2 ...))])) 

(define-syntax my-let
  (syntax-rules ()
    [(my-let () body) body]
    [(my-let ([x1 v1] [x2 v2] ...) body)
     (my-let ([x2 v2] ...) ((lambda (x1) body) v1))]))

(define-syntax my-let*
  (syntax-rules ()
    [(my-let* () body) body]
    [(my-let* ([x1 v1] [x2 v2] ...) body)
     (my-let ([x1 v1]) (my-let* ([x2 v2] ...) body))]))

(my-let* ([x 1] [y x] [z y]) z)