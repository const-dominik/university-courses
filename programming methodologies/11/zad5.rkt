#lang plait

(module+ test
  (print-only-errors #t))

;; abstract syntax -------------------------------

(define-type Op
  (add) (sub) (mul) (div) (eql) (leq))

(define-type Exp
  (numE [n : Number])
  (opE [op : Op] [l : Exp] [r : Exp])
  (ifE [b : Exp] [l : Exp] [r : Exp])
  (varE [x : Symbol])
  (letE [vars : (Listof (Symbol * Exp))] [e2 : Exp]))

;; parse ----------------------------------------

(define (s-exp->pair s) ;<==========
  (let ([name (s-exp->symbol (first (s-exp->list s)))]
        [val (parse (second (s-exp->list s)))])
        (pair name val))
)

(define (get-list s)
  (s-exp->list (second (s-exp->list s))))

(define (parse [s : S-Exp]) : Exp
  (cond
    [(s-exp-match? `NUMBER s)
     (numE (s-exp->number s))]
    [(s-exp-match? `{let ([SYMBOL ANY] ...) ANY} s)                                    ;<===========
     (letE (map s-exp->pair (get-list s))
          (parse (third (s-exp->list s))))]             
    [(s-exp-match? `{let* ([SYMBOL ANY] ...) ANY} s)
      (cond 
        [(= 0 (length (get-list s))) (letE empty (parse (third (s-exp->list s))))]
        [(= 1 (length (get-list s))) (letE (list (s-exp->pair (first (get-list s)))) (parse (third (s-exp->list s))))]
        [else (letE (list (s-exp->pair (first (get-list s)))) 
              (parse (list->s-exp (list `let* (list->s-exp (rest (get-list s))) (third (s-exp->list s))))))])]
    [(s-exp-match? `{SYMBOL ANY ANY} s)
     (opE (parse-op (s-exp->symbol (first (s-exp->list s))))
          (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s))))]
    [(s-exp-match? `{if ANY ANY ANY} s)
     (ifE (parse (second (s-exp->list s)))
          (parse (third (s-exp->list s)))
          (parse (fourth (s-exp->list s))))]
    [(s-exp-match? `SYMBOL s)
     (varE (s-exp->symbol s))]
    [else (error 'parse "invalid input")]))

(define (parse-op [op : Symbol]) : Op
  (cond
    [(eq? op '+) (add)]
    [(eq? op '-) (sub)]
    [(eq? op '*) (mul)]
    [(eq? op '/) (div)]
    [(eq? op '=) (eql)]
    [(eq? op '<=) (leq)]
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
  (test/exn (parse `{{+ 1 2}})
            "invalid input")
  (test/exn (parse `{+ 1})
            "invalid input")
  (test/exn (parse `{^ 1 2})
            "unknown operator")
  (test (parse `{let ([x 1]) {+ x 1}})                                                ;<===========
        (letE (list (values 'x (numE 1))) (opE (add) (varE 'x) (numE 1))))
  (test (parse `{let ([x 5] [y 2]) {+ x y}})
        (letE (list (values 'x (numE 5)) (values 'y (numE 2))) (opE (add) (varE 'x) (varE 'y))))
  (test (parse `{let* () x})
        (letE '() (varE 'x)))
  (test (parse `{let* ([x 2]) x})
        (letE (list (values 'x (numE 2))) (varE 'x)))
  (test (parse `{let* ([x 2] [y x]) y})
        (letE (list (values 'x (numE 2))) (letE (list (values 'y (varE 'x))) (varE 'y))))
  (test (parse `{let* ([x 2] [y x] [y 2]) y})
        (letE (list (values 'x (numE 2))) (letE (list (values 'y (varE 'x))) (letE (list (values 'y (numE 2))) (varE 'y))))))
;; eval --------------------------------------

;; values

(define-type Value
  (numV [n : Number])
  (boolV [b : Boolean]))

;; primitive operations

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

(define (op->proc [op : Op]) : (Value Value -> Value)
  (type-case Op op
    [(add) (op-num-num->proc +)]
    [(sub) (op-num-num->proc -)]
    [(mul) (op-num-num->proc *)]
    [(div) (op-num-num->proc /)]
    [(eql) (op-num-bool->proc =)]
    [(leq) (op-num-bool->proc <=)]))

;; environments

(define-type Binding
  (bind [name : Symbol]
        [val : Value]))

(define-type-alias Env (Listof Binding))

(define mt-env empty)
(define (extend-env [env : Env] [x : Symbol] [v : Value]) : Env
  (cons (bind x v) env))
(define (lookup-env [n : Symbol] [env : Env]) : Value
  (type-case (Listof Binding) env
    [empty (error 'lookup "unbound variable")]
    [(cons b rst-env) (cond
                        [(eq? n (bind-name b))
                         (bind-val b)]
                        [else (lookup-env n rst-env)])]))

;; evaluation function

(define (extend-env-by-list [env : Env] [xs : (Listof (Symbol * Exp))]) : Env
  (if (empty? xs)
      env
      (let* ([p (first xs)]
             [sym (fst p)]
             [exp (snd p)]
             [v1 (eval exp env)])
       (extend-env-by-list (extend-env env sym v1) (rest xs))))
)

(define (eval [e : Exp] [env : Env]) : Value
  (type-case Exp e
    [(numE n) (numV n)]
    [(opE o l r) ((op->proc o) (eval l env) (eval r env))]
    [(ifE b l r)
     (type-case Value (eval b env)
       [(boolV v)
        (if v (eval l env) (eval r env))]
       [else
        (error 'eval "type error")])]
    [(varE x)
     (lookup-env x env)]
    [(letE l e2)                                  ;<===========
     (eval e2 (extend-env-by-list env l))]))      ;<===========

(define (run [e : S-Exp]) : Value
  (eval (parse e) mt-env))


(module+ test
  (test (run `2)
        (numV 2))
  (test (run `{+ 2 1})
        (numV 3))
  (test (run `{* 2 1})
        (numV 2))
  (test (run `{+ {* 2 3} {+ 5 8}})
        (numV 19))
  (test (run `{= 0 1})
        (boolV #f))
  (test (run `{if {= 0 1} {* 3 4} 8})
        (numV 8))
  (test (run `{let [(x 1)] {+ x 1}})
        (numV 2))
  (test (run `{let [(x 1)] {+ x {let [(y 2)] {* x y}}}})
        (numV 3))
  (test (run `{let [(x 1)]
                {+ x {let [(x {+ x 1})]
                       {* x 3}}}})
        (numV 7))
  (test (run `{let* ([x 2] [y x]) {+ y y}})
        (numV 4))
  (test (run `{let* () 2})
        (numV 7))
  (test (run `{let* ([x 2]) x})
        (numV 2))
  (test (run `{let* ([x 2] [y x]) y})
        (numV 2))
  (test (run `{let* ([x 2] [y x] [y 3]) y})
        (numV 3)))

;; printer ———————————————————————————————————-

(define (value->string [v : Value]) : String
  (type-case Value v
    [(numV n) (to-string n)]
    [(boolV b) (if b "true" "false")]))

(define (print-value [v : Value]) : Void
  (display (value->string v)))

(define (main [e : S-Exp]) : Void
  (print-value (eval (parse e) mt-env)))