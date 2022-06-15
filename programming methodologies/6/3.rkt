#lang plait
#|
( define-type ( NNF 'v )
( nnf-lit [ polarity : Boolean ] [ var : 'v ])
( nnf-conj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ])
( nnf-disj [ l : ( NNF 'v ) ] [ r : ( NNF 'v ) ]) )

Niech P będzie własnością NNF taka że:
1) P((nnf-lit polarity var))
2) Dla dowolnych wartości l i r, jeśli P(l) i P(r) to P((nnf-conj l r)) i P((nnf-disj l r))
|#