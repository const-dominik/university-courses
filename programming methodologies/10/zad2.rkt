#lang plait

(module+ test
  (print-only-errors #t))

;; abstract syntax -------------------------------

(define-type Op
  (add)
  (sub)
  (mul)
  (div)
  (eql)
  (leq)
  (con)
  (alt)
  (neg)
  )

(define-type Exp
  (numE [n : Number])
  (unOpE [op : Op]
         [v : Exp])
  (opE [op : Op]
       [l : Exp]
       [r : Exp])
  (ifE [b : Exp]
       [l : Exp]
       [r : Exp])
  (condE [cs : (Listof (Exp * Exp))]))

;; parse ----------------------------------------

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{if ANY ANY ANY} s)
     (ifE (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s)))
          (parse (fourth (s-exp->list s))))]
    [(s-exp-match? `{cond ANY ...} s)
     (condE (parse-cond (rest (s-exp->list s))))]
    [(s-exp-match? `{SYMBOL ANY ANY} s)
     (opE (parse-op (s-exp->symbol (first (s-exp->list s))))
          (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s))))]
    [(s-exp-match? `{- ANY} s)
     (unOpE (parse-unOp (s-exp->symbol (first (s-exp->list s))))
            (parse (second (s-exp->list s))))]
    [(s-exp-match? `{SYMBOL ANY} s)
     (unOpE (parse-unOp (s-exp->symbol (first (s-exp->list s))))
          (parse (second (s-exp->list s))))]
    [else (error 'parse "invalid input")]))

(define (parse-cond [ss : (Listof S-Exp)]) : (Listof (Exp * Exp))
  (type-case (Listof S-Exp) ss
    [empty
     empty]
    [(cons s ss)
     (if (s-exp-match? `{ANY ANY} s)
         (cons (pair (parse (first (s-exp->list s)))
                     (parse (second (s-exp->list s))))
               (parse-cond ss))
         (error 'parse "invalid input: cond"))]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '/) (div)]
    [(eq? op '=) (eql)]
    [(eq? op '<=) (leq)]
    [(eq? op 'and) (con)]
    [(eq? op 'or) (alt)]
    [else (error 'parse "unknown operator")]))

(define (parse-unOp [op : Symbol]) : Op
  (cond
    [(eq? op '-) (sub)]
    [(eq? op 'not) (neg)]
    [else (error 'parse "unknown operator")]))

(module+ test
  (test (parse `2)
        (numE 2))
  (test (parse `{+ 2 1})
        (opE (add) (numE 2) (numE 1)))
  (test (parse `{* 3 4})
        (opE (mul) (numE 3) (numE 4)))
  (test (parse `{+ {* 3 4} 8})
        (opE (add)
             (opE (mul) (numE 3) (numE 4))
             (numE 8)))
  (test (parse `{if {= 0 1} {* 3 4} 8})
        (ifE (opE (eql) (numE 0) (numE 1))
             (opE (mul) (numE 3) (numE 4))
             (numE 8)))
  (test (parse `{not {= 0 1}})
        (unOpE (neg) (opE (eql) (numE 0) (numE 1))))
   (test/exn (parse `{{+ 1 2}})
            "invalid input")
  (test/exn (parse `{+ 1})
            "unknown operator")
  (test/exn (parse `{^ 1 2})
            "unknown operator")
  (test (parse `{cond {{= 0 1} {* 3 4}}
                      {{= 1 1} 8}})
        (condE (list (pair (opE (eql) (numE 0) (numE 1))
                           (opE (mul) (numE 3) (numE 4)))
                     (pair (opE (eql) (numE 1) (numE 1))
                           (numE 8))))))
  
;; eval --------------------------------------

(define-type Value
  (numV [n : Number])
  (boolV [b : Boolean]))

(define (op-num-num->proc [f : (Number Number -> Number)]) : (Value Value -> Value)
  (λ (v1 v2)
    (type-case Value v1
      [(numV n1)
       (type-case Value v2
         [(numV n2)
          (numV (f n1 n2))]
         [else
          (error 'eval "type error")])]
      [else
       (error 'eval "type error")])))

(define (op-num-bool->proc [f : (Number Number -> Boolean)]) : (Value Value -> Value)
  (λ (v1 v2)
    (type-case Value v1
      [(numV n1)
       (type-case Value v2
         [(numV n2)
          (boolV (f n1 n2))]
         [else
          (error 'eval "type error")])]
      [else
       (error 'eval "type error")])))

(define (op-bool-bool1->proc [f : (Boolean Boolean -> Boolean)]) : (Value Value -> Value)
  (λ (v1 v2)
    (type-case Value v1
      [(boolV n1)
       (type-case Value v2
         [(boolV n2)
          (boolV (f n1 n2))]
         [else
          (error 'eval "type error")])]
      [else
       (error 'eval "type error")])))

(define (op-bool-bool2->proc [f : (Boolean -> Boolean)]) : (Value -> Value)
  (λ (v1)
    (type-case Value v1
      [(boolV n1)
       (boolV (f n1))]
      [else
       (error 'eval "type error")])))

(define (op-num-num2->proc [f : (Number -> Number)]) : (Value -> Value)
  (λ (v1)
    (type-case Value v1
      [(numV n1)
       (numV (f n1))]
      [else
       (error 'eval "type error")])))

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) (op-num-num->proc +)]
    [(sub) (op-num-num->proc -)]
    [(mul) (op-num-num->proc *)]
    [(div) (op-num-num->proc /)]
    [(eql) (op-num-bool->proc =)]
    [(leq) (op-num-bool->proc <=)]
    [(con) (op-bool-bool1->proc (λ ([v1 : Boolean] [v2 : Boolean]) (and v1 v2)))]
    [(alt) (op-bool-bool1->proc (λ ([v1 : Boolean] [v2 : Boolean]) (or v1 v2)))]
    [else (error 'eval "not a binary operator")]
    ))

(define (unOp->proc [op : Op]) : (Value -> Value)
  (type-case Op op
    [(sub) (op-num-num2->proc (λ ([v1 : Number]) (- 0 v1)))]
    [(neg) (op-bool-bool2->proc (λ ([v1 : Boolean]) (not v1)))]
    [else (error 'eval "not a unary operator")]
    ))

(define (eval [e : Exp]) : Value
  (type-case Exp e
    [(numE n) (numV n)]
    [(opE o l r) ((op->proc o) (eval l) (eval r))]
    [(unOpE o v) ((unOp->proc o) (eval v))]
    [(ifE b l r)
     (type-case Value (eval b)
       [(boolV v)
        (if v (eval l) (eval r))]
       [else
        (error 'eval "type error")])]
    [(condE cs)
     (eval (cond->if cs))])
  )

(define (cond->if [cs : (Listof (Exp * Exp))]) : Exp
  (type-case (Listof (Exp * Exp)) cs
    [empty
     (numE 42)]
    [(cons c cs)
     (ifE (fst c)
          (snd c )
          (cond->if cs))]))

(define (run [e : S-Exp]) : Value
  (eval (parse e)))

(module+ test
  (test (run `2)
        (numV 2))
  (test (run `{+ 2 1})
        (numV 3))
  (test (run `{* 2 1})
        (numV 2))
  (test (run `{+ {* 2 3} {+ 5 8}})
        (numV 19))
  (test (run `{- {* 2 3}})
        (numV -6))
  (test (run `{+ {- 4} 6})
        (numV 2))
  (test (run `{= 0 1})
        (boolV #f))
  (test (run `{if {= 0 1} {* 3 4} 8})
        (numV 8))
  (test (run `{cond {{and {= 0 1} {= 0 1}} {* 3 4}}
                    {{= 1 1} 8}})
        (numV 8))
  (test (run `{cond {{not {= 0 1}} {* 3 4}}
                    {{= 1 1} 8}})
        (numV 12)))

;; printer ———————————————————————————————————-

(define (value->string [v : Value]) : String
  (type-case Value v
    [(numV n) (to-string n)]
    [(boolV b) (if b "true" "false")]))

(define (print-value [v : Value]) : Void
  (display (value->string v)))

(define (main [e : S-Exp]) : Void
  (print-value (eval (parse e))))