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

;zle, trzeba przechowywac czy zmienna jest zanegowana czy nie w jakiejs fladze ktora jest argumentem funkcji
;bo takie cos nie zachowuje tej rekursji strukturalnej costam costam
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
;~(p ^ (~p ^ q))
(to-nnf (neg (conj (var 'p) (conj (neg (var 'p)) (var 'q)))))
;(~p v (p v ~q))