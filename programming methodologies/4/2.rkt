#lang racket

(require rackunit)

(define-struct leaf () #:transparent)
(define-struct node (l elem r) #:transparent)

(define (tree? x)
  (cond [(leaf? x) #t]
        [(node? x) (and (tree? (node-l x)) (tree? (node-r x)))]
        [else #f]))

(define example-tree (node (node (leaf) 1 (leaf))
                           2
                           (node (node (leaf) 3 (leaf))
                                 4
                                 (node (leaf) 5 (leaf)))))

(define example-treev2 (node (node (leaf) 1 (leaf))
                           2
                           (node (node (leaf) 3 (leaf))
                                 4
                                 (node (leaf) 5 (node (leaf) 7 (node (leaf) 8 (leaf)))))))

(define (find-bst x t)
  (cond [(leaf? t) #f]
        [(node? t)
         (cond [(= x (node-elem t)) #t]
               [(< x (node-elem t))
                (find-bst x (node-l t))]
               [else
                (find-bst x (node-r t))])]))

(define (insert-bst x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
         (cond [(= x (node-elem t)) t]
               [(< x (node-elem t))
                (node
                 (insert-bst x (node-l t))
                 (node-elem t)
                 (node-r t))]
               [else
                (node
                 (node-l t)
                 (node-elem t)
                 (insert-bst x (node-r t)))])]))

;zad2

(define (fold-tree proc x tree)
  (if (leaf? tree)
      x
      (proc (node-elem tree) (fold-tree proc x (node-l tree)) (fold-tree proc x (node-r tree)))))

(define (tree-sum t)
  (fold-tree + 0 t))

(define (tree-flip t)
  (fold-tree
   (lambda (elem left right) (node right elem left))
    (leaf)
    t))

(define (tree-height t)
  (fold-tree
   (lambda (elem left right) (+ 1 (max left right)))
   0
   t))

(define (tree-span t)
  (fold-tree
   (lambda (elem left right) (cons (min (car left) elem) (max elem (cdr right))))
   (cons +inf.0 -inf.0)
   t))

(define (flatten t)
  (fold-tree
   (lambda (elem left right) (append left (cons elem right)))
   null
   t))

;zad3
(define (bst? t)
  (define (bst-min-max t min max)
    (cond
      [(leaf? t) #t]
      [(or (< (node-elem t) min) (> (node-elem t) max)) #f]
      [else (and
             (bst-min-max (node-l t) min (- (node-elem t) 1))
             (bst-min-max (node-r t) (+ (node-elem t) 1) max))]
      )
    )
  (bst-min-max t -inf.0 +inf.0))

(define (sum-paths t)
  (define (sum-side t val)
    (if (leaf? t)
        t
        (node (sum-side (node-l t) (+ val (node-elem t)))
              (+ val (node-elem t))
              (sum-side (node-r t) (+ val (node-elem t)))
              )
        )
    )
  (sum-side t 0))

;zad4
(define (flat-append t xs)
  (if (leaf? t)
      xs
      (flat-append (node-l t)
                   (cons (node-elem t)
                         (flat-append (node-r t) xs)))))

(define (flatten2 t) (flat-append t null))

;zad5
(define (insert-bst-d x t)
  (cond [(leaf? t) (node (leaf) x (leaf))]
        [(node? t)
         (cond [(= x (node-elem t))
                (node
                 (node (node-l t) x (leaf))
                 x
                 (node-r t))]
               [(< x (node-elem t))
                (node
                 (insert-bst-d x (node-l t))
                 (node-elem t)
                 (node-r t))]
               [else
                (node
                 (node-l t)
                 (node-elem t)
                 (insert-bst-d x (node-r t)))])]))

(define (treesort xs)
  (define (it tree list)
    (if (null? list)
        tree
        (it (insert-bst-d (car list) tree) (cdr list))))
  (flatten2 (it (leaf) xs)))

;zad6
(define (min t)
  (cond [(leaf? t) -inf.0]
        [(leaf? (node-l t)) (node-elem t)]
        [else (min (node-l t))]
     )
  )

(define (delete x t)
  (cond [(leaf? t) t]
        [(< x (node-elem t)) (node (delete x (node-l t)) (node-elem t) (node-r t))]
        [(> x (node-elem t)) (node (node-l t) (node-elem t) (delete x (node-r t)))]
        [(leaf? (node-l t)) (node-r t)]
        [(leaf? (node-r t)) (node-l t)]
        [else
         (node (node-l t) (min (node-r t)) (delete (min (node-r t)) (node-r t)))]
        ))

;zad7
(define empty-queue (cons null null))

(define (empty? q)
  (null? (car q)))

(define (front q)
  (caar q))

(define (push-back x q)
  (if (empty? q)
      (cons (list x) null)
      (cons (car q) (cons x (cdr q)))))

(define (pop q)
  (if (empty? q)
      q
      (if (null? (cdr (car q)))
          (cons (reverse (cdr q)) null)
          (cons (cdr (car q)) (cdr q)))
      )
  )
      