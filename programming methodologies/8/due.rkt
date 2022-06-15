#lang racket
(provide
 mqueue?
 nonempty-mqueue/c
 (contract-out
  [mqueue-empty?      (-> mqueue? boolean?)]
  [mqueue-make        (-> mqueue?)]
  [mqueue-push-front  (-> mqueue? any/c any/c)]
  [mqueue-push-back   (-> mqueue? any/c any/c)]
  [mqueue-pop-front   (-> nonempty-mqueue/c any/c)]
  [mqueue-pop-back    (-> nonempty-mqueue/c any/c)]
  [mqueue-peek        (-> nonempty-mqueue/c any/c)]
  [mqueue-join        (-> nonempty-mqueue/c nonempty-mqueue/c any/c)]))

(struct node ([prev #:mutable] val [next #:mutable]))

(struct mqueue
  ([front #:mutable] [back #:mutable]))

(define (mqueue-empty? q)
  (null? (mqueue-front q)))

(define nonempty-mqueue/c
  (and/c mqueue? (not/c mqueue-empty?)))

(define (mqueue-make)
  (mqueue null null))

(define (insert-after p1 p2)
    (define p3 (node-next p1))
    (set-node-next! p2 p3)
    (set-node-prev! p3 p2)
    (set-node-next! p1 p2)
    (set-node-prev! p2 p1)
)

(define (mqueue-push-front q x)
    (define p (node null x null))
    (cond
      [(mqueue-empty? q) (set-mqueue-back! q p)]
      [else (set-node-next! p (mqueue-front q))
            (set-node-prev! (mqueue-front q) p)])
    (set-mqueue-front! q p)
)

(define (mqueue-push-back q x)
    (define p (node null x null))
    (cond
      [(mqueue-empty? q) (set-mqueue-front! q p)]
      [else (set-node-prev! p (mqueue-back q))
            (set-node-next! (mqueue-back q) p)])
    (set-mqueue-back! q p)
)

(define/contract (mqueue-pop-front q)
    (-> nonempty-mqueue/c any/c)
    (define p (mqueue-front q))
    (set-mqueue-front! q (node-next p))
    (cond
      [(null? (mqueue-front q)) (set-mqueue-back! q null)]
      [else (set-node-prev! (mqueue-front q) null)])
    (node-val p)
)

(define/contract (mqueue-pop-back q)
    (-> nonempty-mqueue/c any/c)
    (define p (mqueue-back q))
    (set-mqueue-back! q (node-prev p))
    (cond
      [(null? (mqueue-back q)) (set-mqueue-front! q null)]
      [else (set-node-next! (mqueue-back q) null)])
    (node-val p)
)

(define (mqueue-peek q)
  (node-val (mqueue-front q)))

(define (mqueue-join q1 q2)
  (set-node-next! (mqueue-back q1) (mqueue-front q2))
  (set-node-prev! (mqueue-front q2) (mqueue-back q1))
  (set-mqueue-back! q1 (mqueue-back q2))
  (set-mqueue-front! q2 null))

