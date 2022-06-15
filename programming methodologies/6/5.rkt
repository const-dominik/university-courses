#lang plait

( define-type ( NNF 'v )
( nnf-lit [ polarity : Boolean ] [ var : 'v ])
( nnf-conj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ])
( nnf-disj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ]) )

(define (neg-nnf form)
    (cond
        [(nnf-lit? form) (nnf-lit (not (nnf-lit-polarity form)) (nnf-lit-var form))]
        [(nnf-conj? form) (nnf-disj (neg-nnf (nnf-conj-l form)) (neg-nnf (nnf-conj-r form)))]
        [(nnf-disj? form) (nnf-conj (neg-nnf (nnf-disj-l form)) (neg-nnf (nnf-disj-r form)))]
    )
)

(define (eval-nnf eval form)
    (cond
        [(nnf-lit? form) (not (equal? (nnf-lit-polarity form) (eval (nnf-lit-var form))))]
        [(nnf-conj? form) (and (eval-nnf eval (nnf-conj-l form)) (eval-nnf eval (nnf-conj-r form)))]
        [(nnf-disj? form) (or (eval-nnf eval (nnf-disj-l form)) (eval-nnf eval (nnf-disj-r form)))]
    )
)

#|
Niech P będzie własnością NNF taka że:
1) P((nnf-lit polarity var)) 
2) Dla dowolnych wartości l i r, jeśli P(l) i P(r) to P((nnf-conj l r)) i P((nnf-disj l r))

P(φ) := (eval-nnf σ (neg-nnf φ)) ≡ (not (eval-nnf σ φ))

1. podstawa indukcji
P((nnf-lit pol var))
L ≡ (eval-nnf σ (neg-nnf (nnf-lit pol var))) ≡ 
    (eval-nnf σ (nnf-lit (not (nnf-lit-polarity (nnf-lit pol var))) (nnf-lit-var (nnf-lit pol var)))) ≡ 
    (eval-nnf σ (nnf-lit (not pol) var)) ≡ 
    (not (equal? (nnf-lit-polarity (nnf-lit (not pol) var)) (σ (nnf-lit-var (nnf-lit (not pol) var))))) ≡
    (not (equal? (not pol) (σ var))

P ≡ (not (eval-nnf σ (nnf-lit pol var))) ≡
    (not (not (equal? pol (σ var)))) ≡
    (equal? pol (σ var))
~(p <=> q) <=> (~p <=> q)
L ≡ P

2. krok indukcyjny
    weźmy dowolną formułę f1, f2 i dowolne wartościowanie σ i załóżmy, że
    (eval-nnf σ (neg-nnf f1)) ≡ (not (eval-nnf σ f1)) oraz
    (eval-nnf σ (neg-nnf f2)) ≡ (not (eval-nnf σ f2))
    pokażemy, że 
    (eval-nnf σ (neg-nnf (nnf-conj f1 f2))) ≡ (not (eval-nnf σ (nnf-conj f1 f2))) oraz
    (eval-nnf σ (neg-nnf (nnf-disj f1 f2))) ≡ (not (eval-nnf σ (nnf-disj f1 f2)))

    L ≡ (eval-nnf σ (neg-nnf (nnf-conj f1 f2))) ≡ 
    (eval-nnf σ (nnf-disj (neg-nnf f1) (neg-nnf f2)))) ≡
    (or (eval-nnf σ (neg-nnf f1)) (eval-nnf σ (neg-nnf f2)))

    P ≡ (not (eval-nnf σ (nnf-conj f1 f2))) ≡
        (not (and (eval-nnf σ f1) (eval-nnf σ f2)))
    z praw de'Morgana (~f1 v ~f2) ≡ ~(f1 ^ f2),
    L ≡ P

    dysjunkcja analogicznie

    L ≡ (eval-nnf σ (neg-nnf (nnf-disj f1 f2))) ≡ 
    (eval-nnf σ (nnf-conj (neg-nnf f1) (neg-nnf f2)))) ≡
    (and (eval-nnf σ (neg-nnf f1)) (eval-nnf σ (neg-nnf f2)))

    P ≡ (not (eval-nnf σ (nnf-disj f1 f2))) ≡
        (not (or (eval-nnf σ f1) (eval-nnf σ f2)))
    z praw de'Morgana (~f1 ^ ~f2) ≡ ~(f1 v f2),
    L ≡ P

    na mocy zasady indukcji, dla dowolnej formuly φ zachodzi
    (eval-nnf σ (neg-nnf φ)) ≡ (not (eval-nnf σ φ))
|#