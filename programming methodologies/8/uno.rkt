#lang racket

(define some-list (mcons 1 (mcons 2 (mcons 3 null))))
(define some-list2 (mcons 1 null))
(define some-list23 '())

(define (m-reverse! xs)
    (define (it prev curr)
        (if (null? curr)
            prev
            (let [(next (mcdr curr))]
                (set-mcdr! curr prev)
                (it curr next))
        ))
    (it null xs)
)

(m-reverse! some-list)
(m-reverse! some-list2)
(m-reverse! some-list23)