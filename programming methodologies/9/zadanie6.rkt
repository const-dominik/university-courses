#lang plait

(define (concat xs)
  (if (empty? xs)
      empty
      (append (first xs) (concat (rest xs)))))

(define (visited? p visited)
  (if (empty? visited)
      #f
      (if (equal? p (first visited))
          #t
          (visited? p (rest visited)))))


(define (on-board? p n)
  (and (<= 1 (fst p)) (>= n (fst p))
       (<= 1 (snd p)) (>= n (snd p))))

(define (add-p p a b)
  (pair (+ (fst p) a)
        (+ (snd p) b)))

(define (square p n visited a b)
  (let [(p (add-p p a b))]
    (if (and (on-board? p n)
             (not (visited? p visited)))
        (list p)
        (list))))

(define (possible-moves p n visited)
  (concat (filter cons?
                  (list (square p n visited -1  2)
                        (square p n visited  1  2)
                        (square p n visited -1 -2)
                        (square p n visited  1 -2)
                        (square p n visited  2  1)
                        (square p n visited -2  1)
                        (square p n visited  2 -1)
                        (square p n visited -2 -1)))))

(define (pom n tvisited moves)
  (if (= (* n n) (length (snd tvisited)))
      tvisited
      (if (empty? moves)
          (pair #f (snd tvisited))
          [let ([tab (pom n
                          (pair #t (cons (first moves) (snd tvisited)))
                          (possible-moves (first moves) n (cons (first moves) (snd tvisited))))])
            (if (fst tab)
                tab
                (pom n tvisited (rest moves)))])))

(define (search n)
  (pom n
       (pair #t (list (pair 1 1)))
       (possible-moves (pair 1 1) n (list (pair 1 1)))))

(define (number->letter x)
  (cond
    [(= x  1) "a"]
    [(= x  2) "b"]
    [(= x  3) "c"]
    [(= x  4) "d"]
    [(= x  5) "e"]
    [(= x  6) "f"]
    [(= x  7) "g"]
    [(= x  8) "h"]
    [(= x  9) "i"]
    [(= x 10) "j"]))
    
(define (alternative-names xs ys)
  (if (empty? xs)
      ys
      (alternative-names (rest xs)
                        (cons (string-append (number->letter (fst (first xs)))
                                             (to-string      (snd (first xs))))
                              ys))))

(define (knights-tour n)
  (let ([tab (search n)])
    (if (fst tab)
        (alternative-names (snd tab) '())
        (error 'knights-tour "brak rozw"))))
