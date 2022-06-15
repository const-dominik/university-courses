#lang plait

( define-type Prop
( var [ v : String ])
( conj [ l : Prop ] [ r : Prop ])
( disj [ l : Prop ] [ r : Prop ])
( neg [ f : Prop ]) )

(define (eval dict form)
  (letrec [(it (lambda (f)
                  (cond [(var? f) (if (none? (hash-ref dict (var-v f)))
                                             (error 'eval (string-append "Brak wartościowania dla " (to-string (var-v f))))
                                             (some-v (hash-ref dict (var-v f))))]
                        [(conj? f) (and (it (conj-l f)) (it (conj-r f)))]
                        [(disj? f) (or (it (disj-l f)) (it (disj-r f)))]
                        [else (not (it (neg-f f)))]
                        )))]
      (it form)))

(define some-dict (hash (list
         (pair "a" #t) (pair "b" #f) (pair "f" #t))))
 ;(a^b)v(~f)
(define some-formula (disj (conj (var "a") (var "b")) (neg (var "f"))))
(eval some-dict some-formula)
