#lang plait

(define-type-alias (Stream 'a) (-> (StreamData 'a)))
(define-type (StreamData 'a)
(sempty)
(scons [head : 'a] [tail : (Stream 'a)]))

(define (valid-pos? i board)
  (local
    [(define (valid-it i j k board)
       (type-case (Listof Number) board
         [empty #t]
         [(cons x board)
          (and (not (= i x))
               (not (= j x))
               (not (= k x))
               (valid-it (- i 1) j (+ k 1) board))]))]
    (valid-it (- i 1) i (+ i 1) board)))

;;;queens 1 z wykladu
(define (concat xs)
  (if (empty? xs)
      empty
      (append (first xs) (concat (rest xs)))))

(define (queens1 n)
  (local
    [(define (queens-it board left)
       (if (= left 0)
           (list board)
           (concat (build-list n (lambda (i)
              (if (valid-pos? i board)
                  (queens-it (cons i board) (- left 1))
                  '()))))))]
    (queens-it '() n)))


;;;queens 2 z wykladu
(define (select xs cont)
  (type-case (Listof 'a) xs
    [empty (none)]
    [(cons x xs)
     (type-case (Optionof 'b) (cont x)
       [(none)   (select xs cont)]
       [(some v) (some v)])]))

(define (fail cont)
  (none))

(define (init-cont x) (some x))

(define (select-number n cont)
  (select (build-list n (lambda (i) i)) cont))

(define (queens2 n)
  (local
    [(define (queens-it board left cont)
       (if (= left 0)
           (cont board)
           (select-number n (lambda (i)
             (if (valid-pos? i board)
                 (queens-it (cons i board) (- left 1) cont)
                 (fail cont))))))]
    (queens-it '() n init-cont)))

;;;squeens
(define (sappend xs ys)
  (lambda () (type-case (StreamData 'a) (xs)
                 [(sempty) (ys)]
                 [(scons h t) (scons h (sappend t ys))])))

(define (sconcat xs)
  (lambda () (type-case (StreamData (Stream 'a)) (xs)
               [(sempty) (sempty)]
               [(scons ys zs) ((sappend ys (sconcat zs)))])))

(define (sbuild-list n f)
  (lambda () (if (= n 0)
                 (sempty)
                 (scons (f (- n 1)) (sbuild-list (- n 1) f)))))

(define (queens3 n)
  (local
    [(define (queens-it board left)
       (if (= left 0)
           (λ () (scons board (λ () (sempty))))
           (sconcat (sbuild-list n (lambda (i)
                                     (if (valid-pos? i board)
                                         (queens-it (cons i board) (- left 1))
                                         (lambda () (sempty))))))))]
    (queens-it '() n)))

(time (begin (queens1 10)))
(time (begin (queens2 15)))
(time (begin ((queens3 15))))