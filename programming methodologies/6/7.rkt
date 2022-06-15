#lang plait

( define-type ( Formula 'v )
( var [ var : 'v ])
( neg [ f : ( Formula 'v ) ])
( conj [ l : ( Formula 'v ) ] [ r : ( Formula 'v ) ])
( disj [ l : ( Formula 'v ) ] [ r : ( Formula 'v ) ]) )

( define-type ( NNF 'v )
( nnf-lit [ polarity : Boolean ] [ var : 'v ])
( nnf-conj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ])
( nnf-disj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ]) )

(define (to-nnf form)
    (if (neg? form)
        (cond
            [(var? (neg-f form)) (nnf-lit #t (var-var (neg-f form)))]
            [(neg? (neg-f form)) (to-nnf (neg-f (neg-f form)))]
            [(conj? (neg-f form)) (nnf-disj (to-nnf (neg (conj-l (neg-f form)))) (to-nnf (neg (conj-r (neg-f form)))))]
            [(disj? (neg-f form)) (nnf-conj (to-nnf (neg (disj-l (neg-f form)))) (to-nnf (neg (disj-r (neg-f form)))))])
        (cond
            [(var? form) (nnf-lit #f (var-var form))]
            [(disj? form) (nnf-disj (to-nnf (conj-l form)) (to-nnf (conj-r form)))]
            [(conj? form) (nnf-conj (to-nnf (disj-l form)) (to-nnf (disj-r form)))])
    )
)

(define (eval-nnf eval form)
    (cond
        [(nnf-lit? form) (not (equal? (nnf-lit-polarity form) (eval (nnf-lit-var form))))]
        [(nnf-conj? form) (and (eval-nnf eval (nnf-conj-l form)) (eval-nnf eval (nnf-conj-r form)))]
        [(nnf-disj? form) (or (eval-nnf eval (nnf-disj-l form)) (eval-nnf eval (nnf-disj-r form)))]
    )
)

(define (eval-formula eval form)
    (cond
        [(var? form) (eval (var-var form))]
        [(neg? form) (not (eval-formula eval (neg-f form)))]
        [(conj? form) (and (eval-formula eval (conj-l form)) (eval-formula eval (conj-r form)))]
        [(disj? form) (or (eval-formula eval (disj-l form)) (eval-formula eval (disj-r form)))]
    )
)

#|

zasada indukcji dla typu Formula:

Niech P będzie taką własnościa Formula, że:
1 podstawa
P zachodzi dla dowolnej zmiennej zdaniowej p
P((var p))

2 krok
dla dowolnych wartości l, r typu Formula zachodzi:
P(l), P(r), to P((neg l)), P((conj l r)), P((disj l r))
to P zachodzi dla każdej formuły



P(φ) := (eval-nnf σ (to-nnf φ)) ≡ (eval-formula σ φ)

1. podstawa
    P((var p))

L = (eval-nnf σ (to-nnf (var p))) =
    (eval-nnf σ (nnf-lit #f p)) =
    (not (equal? #f (σ p))) =
    (equal? #t (σ p))
    1. (σ p) = #t
        (equal? #t (σ p)) = #t
    2. (σ p) = #f
        (equal? #t (σ p)) = #f
    (equal? #t (σ p)) =
    (σ p)

P = (eval-formula σ (var p)) =
    (σ p)

L = P

2. krok
    weźmy dowolne l i r typu Formula i załóżmy, że:
    (eval-nnf σ (to-nnf l)) ≡ (eval-formula σ l) i
    (eval-nnf σ (to-nnf r)) ≡ (eval-formula σ r)
    
     pokażemy że
    (eval-nnf σ (to-nnf (conj l r))) ≡ (eval-formula σ (conj l r)),
    (eval-nnf σ (to-nnf (disj l r))) ≡ (eval-formula σ (disj l r)),
    (eval-nnf σ (to-nnf (neg l))) ≡ (eval-formula σ (neg l)),

    a) (eval-nnf σ (to-nnf (conj l r))) ≡ (eval-formula σ (conj l r))

L = (eval-nnf σ (to-nnf (conj l r))) = 
    (eval-nnf σ (nnf-conj (to-nnf l) (to-nnf r)) = 
    (and (eval-nnf σ (to-nnf l)) (eval-nnf σ (to-nnf r))) = 

P = (eval-formula σ (conj l r)) =
    (and (eval-formula σ l) (eval-formula σ r))

korzystając z założenia, L = P

    b) (eval-nnf σ (to-nnf (disj l r))) ≡ (eval-formula σ (disj l r))
    
L = (eval-nnf σ (to-nnf (disj l r))) =
    (eval-nnf σ (nnf-disj (to-nnf l) (to-nnf r)) = 
    (or (eval-nnf σ (to-nnf l)) (eval-nnf σ (to-nnf r))) = 

P = (eval-formula σ (disj l r)) =
    (or (eval-formula σ l) (eval-formula σ r))

korzystając z założenia, L = P
    
    c) (eval-nnf σ (to-nnf (neg l))) ≡ (eval-formula σ (neg l));niestety niedokonczone:)
        1. (var? l)
        
        (eval-nnf σ (nnf-lit #t (var-var l))) =
        (not (equal? #t (σ (var-var l)))) =
        (equal? #f (σ (var-var l))) =
        (not (σ (var-var l)))

        (eval-formula σ (neg l)) =
        (not (eval-formula σ l)) =
        (not (σ (var-var l))

        2. (neg? l)
        (eval-nnf σ (to-nnf (neg l))) =
        (eval-nnf σ (to-nnf (neg-f l)))

        (eval-formula σ (neg l)) =
        (not (eval-formula σ l)) =
        (not (not (eval-formula σ (neg-f l)))) =
        (eval-formula σ (neg-f l))

        3. (conj? l)
        (eval-nnf σ (to-nnf (neg l))) =
        (eval-nnf σ (nnf-disj (to-nnf (neg (conj-l l))) (to-nnf (neg (conj-r l))))) =
        (or (eval-nnf eval (to-nnf (neg (conj-l l)))) (eval-nnf eval (to-nnf (neg (conj-r l)))))

        (eval-formula σ (neg l)) =
        (not (eval-formula σ l)) =
        (not (and (eval-formula eval (conj-l l)) (eval-formula eval (conj-r l)))) =

|#