#lang plait

(define (remove-duplicates xs)
  (letrec [(it (lambda (xs1 xs2)
                (if (empty? xs2)
                    xs1
                    (it (cons (first xs2) xs1)
                        (filter (lambda (x) (not (equal? x (first xs2)))) (rest xs2))))))]
    (it empty xs)))

( define-type Prop
( var [ v : String ])
( conj [ l : Prop ] [ r : Prop ])
( disj [ l : Prop ] [ r : Prop ])
( neg [ f : Prop ]) )

(define (free-vars form)
    (letrec [(it (lambda (f)
                  (cond [(var? f) (cons (var-v f) empty)]
                        [(conj? f) (append (it (conj-l f)) (it (conj-r f)))]
                        [(disj? f) (append (it (disj-l f)) (it (disj-r f)))]
                        [else (it (neg-f f))]
                        )))]
      (it form)))
(remove-duplicates (free-vars (disj (conj (var "a") (var "a")) (neg (var "f")))))