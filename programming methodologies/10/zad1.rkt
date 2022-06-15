#lang plait

(module+ test
  (print-only-errors #t))

(define (apply p xs)
  (local
    [(define (it acc ys)
       (if (empty? ys)
           acc
           (it (p acc (first ys)) (rest ys))))]
    (if (empty? xs)
        (error 'invalid-input "cant apply procedure to empty list")
        (it (first xs) (rest xs)))    
))

;; abstract syntax -------------------------------

(define-type Op
  (add)
  (sub)
  (mul)
  (div))

(define-type Exp
  (numE [n : Number])
  (opE [op : Op] [v : (Listof Exp)]))

;; parse ----------------------------------------

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{SYMBOL ANY ...} s)
     (opE (parse-op (s-exp->symbol (first (s-exp->list s))))
          (map parse (s-exp->list (list->s-exp (rest (s-exp->list s))))))]
    [else (error 'parse "invalid input")]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '/) (div)]
    [else (error 'parse "unknown operator")]))

(module+ test
  (test (parse `2)
        (numE 2))
  (test (parse `{+ 2 1})
        (opE (add) (list (numE 2) (numE 1))))
  (test (parse `{* 3 4})
        (opE (mul) (list (numE 3) (numE 4))))
  (test (parse `{+ {* 3 4} 8})
        (opE (add)
             (list (opE (mul) (list (numE 3) (numE 4)))
             (numE 8))))
 (test/exn (parse `{{+ 1 2}})
            "invalid input")
  (test/exn (parse `{^ 1 2})
            "unknown operator"))

;; eval --------------------------------------

(define-type-alias Value Number)

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) +]
    [(sub) -]
    [(mul) *]
    [(div) /]))

(define (eval [e : Exp]) : Value
  (type-case Exp e
    [(numE n) n]
    [(opE o v) (apply (op->proc o) (map eval v))]))

(define (run [e : S-Exp]) : Value
  (eval (parse e)))

(module+ test
  (test (run `2)
        2)
  (test (run `{+ 2 1})
        3)
  (test (run `{* 2 1})
        2)
  (test (run `{+ {* 2 3} {+ 5 8}})
        19))