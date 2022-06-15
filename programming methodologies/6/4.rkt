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

#|
Niech P będzie własnością NNF taka że:
1) P((nnf-lit polarity var)) 
2) Dla dowolnych wartości l i r, jeśli P(l) i P(r) to P((nnf-conj l r)) i P((nnf-disj l r))

P(φ) := (neg-nnf (neg-nnf φ)) ≡ φ

1. podstawa indukcji
    (neg-nnf (neg-nnf (nnf-lit polarity var))) ≡
    (neg-nnf (nnf-lit (not polarity) var) ≡
    (nnf-lit polarity var)

2. krok indukcyjny
    weźmy dowolną formułę f1 i f2 i załóżmy, że
    (neg-nnf (neg-nnf f1)) ≡ f1 oraz
    (neg-nnf (neg-nnf f2)) ≡ f2
    pokażemy, że
    (neg-nnf (neg-nnf (nnf-conj f1 f2)) ≡ (nnf-conj f1 f2) oraz
    (neg-nnf (neg-nnf (nnf-disj f1 f2)) ≡ (nnf-disj f1 f2)

    (neg-nnf (neg-nnf (nnf-conj f1 f2)) ≡ 
    (neg-nnf (nnf-disj (neg-nnf f1) (neg-nnf f2))) ≡
    (nnf-conj (neg-nnf (neg-nnf f1)) (neg-nnf (neg-nnf f2))) ≡
    (nnf-conj f1 f2)

    (neg-nnf (neg-nnf (nnf-disj f1 f2)) ≡
    (neg-nnf (nnf-conj (neg-nnf f1) (neg-nnf f2))) ≡
    (nnf-disj (neg-nnf (neg-nnf f1)) (neg-nnf (neg-nnf f2))) ≡
    (nnf-disj f1 f2)

na mocy zasady indukcji, dla dowolnej formuly φ zachodzi (neg-nnf (neg-nnf φ)) ≡ φ
|#