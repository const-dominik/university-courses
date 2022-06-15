#lang plait 

(define-type (Tree 'a)
  (leaf)
  (node-1 [elem : 'a] [l : (Tree 'a)] [r : (Tree 'a)])
  (node-2 [elem : ('a * 'a)] [l : (Tree 'a)] [m : (Tree 'a)]  [r : (Tree 'a)]))

(define (height tree)
    (cond
        [(leaf? tree) 0]
        [(node-1? tree) (+ 1 (max (height (node-1-l tree)) (height (node-1-r tree))))]
        [(node-2? tree) (+ 1 (max 
                            (max (height (node-2-l tree)) (height (node-2-m tree)))
                            (height (node-2-l tree))))]
    )    
)

(define (is-balanced tree)
    (cond
        [(leaf? tree) #t]
        [(node-1? tree) (and 
            (= 0 (- (height (node-1-l tree)) (height (node-1-r tree))))
            (is-balanced (node-1-l tree))
            (is-balanced (node-1-r tree))
        )]
        [(node-2? tree) (and
            (= 0 (- (height (node-2-l tree)) (height (node-2-r tree))))
            (= 0 (- (height (node-2-l tree)) (height (node-2-m tree))))
            (is-balanced (node-2-l tree))
            (is-balanced (node-2-r tree))
            (is-balanced (node-2-m tree))
        )]
    )
)

(define (2-3tree-min-max tree min max)
    (cond
        [(leaf? tree) #t]
        [(node-1? tree) (cond
            [(or (< (node-1-elem tree) min) (> (node-1-elem tree) max)) #f]
            [else (and
                (2-3tree-min-max (node-1-l tree) min (- (node-1-elem tree) 1))
                (2-3tree-min-max (node-1-r tree) (+ (node-1-elem tree) 1) max))]
        )]
        [(node-2? tree) (cond
            [(< (snd (node-2-elem tree)) (fst (node-2-elem tree))) #f]
            [(or (< (fst (node-2-elem tree)) min) (> (snd (node-2-elem tree)) max)) #f]
            [else (and
                (2-3tree-min-max (node-2-l tree) min (- (fst (node-2-elem tree)) 1))
                (2-3tree-min-max (node-2-r tree) (+ (snd (node-2-elem tree)) 1) max)
                (2-3tree-min-max (node-2-m tree) (+ (fst (node-2-elem tree)) 1) (- (snd (node-2-elem tree)) 1)))]
        )]
    )
)

(define (2-3Tree? tree)
    (cond
        [(leaf? tree) #t]
        [(or (node-1? tree) (node-2? tree)) (and (is-balanced tree) (2-3tree-min-max tree -inf.0 +inf.0))]
        [else #f]
    )
)

(define example-tree
    (node-1 5 (node-1 4 (leaf) (leaf)) (node-1 6 (leaf) (leaf)))
)
(define example-tree2
    (node-1 4 (node-1 2 (node-1 1 (leaf) (leaf)) (node-1 3 (leaf) (leaf)))
     (node-1 6 (node-1 5 (leaf) (leaf)) (node-1 7 (leaf) (leaf))))
)
; (define example-tree3
;     (node-1 7 (node-1 2 (node-1 1 (leaf) (leaf)) (node-1 3 (leaf) (leaf)))
;      (node-2 (pair 10 12) (node-1 8 (leaf) (leaf)) (node-1 11 (leaf) (leaf)) (node-1 13 (leaf) (leaf))))
; )
(define example-tree3
    (node-1 7 (node-1 2 (node-1 1 (leaf) (leaf)) (node-1 3 (leaf) (leaf)))
     (node-2 (pair 10 12) (node-1 8 (leaf) (leaf)) (node-1 11 (leaf) (leaf)) (node-1 13 (leaf) (node-1 15 (leaf) (leaf)))))
)

(2-3Tree? example-tree)
(2-3Tree? example-tree2)
(2-3Tree? example-tree3)
