#lang racket
(require data/heap)
(require rackunit)

(provide sim? wire?
         (contract-out
          [make-sim        (-> sim?)]
          [sim-wait!       (-> sim? positive? void?)]
          [sim-time        (-> sim? real?)]
          [sim-add-action! (-> sim? positive? (-> any/c) void?)]

          [make-wire       (-> sim? wire?)]
          [wire-on-change! (-> wire? (-> any/c) void?)]
          [wire-value      (-> wire? boolean?)]
          [wire-set!       (-> wire? boolean? void?)]

          [bus-value (-> (listof wire?) natural?)]
          [bus-set!  (-> (listof wire?) natural? void?)]

          [gate-not  (-> wire? wire? void?)]
          [gate-and  (-> wire? wire? wire? void?)]
          [gate-nand (-> wire? wire? wire? void?)]
          [gate-or   (-> wire? wire? wire? void?)]
          [gate-nor  (-> wire? wire? wire? void?)]
          [gate-xor  (-> wire? wire? wire? void?)]

          [wire-not  (-> wire? wire?)]
          [wire-and  (-> wire? wire? wire?)]
          [wire-nand (-> wire? wire? wire?)]
          [wire-or   (-> wire? wire? wire?)]
          [wire-nor  (-> wire? wire? wire?)]
          [wire-xor  (-> wire? wire? wire?)]

          [flip-flop (-> wire? wire? wire? void?)]))

;;simulation

; - sim-queue element - (cons invoke_time action)
(struct sim ([time #:mutable] [queue #:mutable]))

(define (compare-action a1 a2)
  (<= (car a1) (car a2)))

(define (heap-empty? h)
  (= (heap-count h) 0))

(define (make-sim) (sim 0 (make-heap compare-action)))

(define (sim-add-action! s time-segment action)
  (heap-add! (sim-queue s) (cons (+ time-segment (sim-time s)) action)))

(define (sim-wait! s time)
  (if (heap-empty? (sim-queue s))
        (set-sim-time! s (+ (sim-time s) time))
         (let* ([action (heap-min (sim-queue s))]
                [ac-time (car action)]
                [ac-proc (cdr action)]
                [diff (- ac-time (sim-time s))])
           (if (and (<= 0 diff) (<= diff time))
               (begin
                 (set-sim-time! s ac-time)
                 (heap-remove-min! (sim-queue s))
                 (ac-proc)
                 (sim-wait! s (- time diff)))
              (set-sim-time! s (+ (sim-time s) time))))))

;;wire
(struct wire ([value #:mutable] [actions #:mutable] [sim #:mutable]))

;;kod pana Polesiuka z wykładu 8
(define (call-actions xs)
  (if (null? xs)
      (void)
      (begin
        ((car xs))
        (call-actions (cdr xs)))))

(define (set-value! w v)
  (if (eq? v (wire-value w))
      (void)
      (begin
        (set-wire-value! w v)
        (call-actions (wire-actions w)))))

(define (add-action! w f)
  (set-wire-actions! w (cons f (wire-actions w))))
;;koniec kodu pana Polesiuka

(define (make-wire s) (wire #f '() s))
(define (wire-on-change! w f)
  (f)
  (add-action! w f))
(define wire-set! set-value!)

;;gates
(define (gate-not w1 w2)
  (define (not-procedure)
      (sim-add-action! (wire-sim w1) 1 (λ () (wire-set! w1 (not (wire-value w2))))))
  (wire-on-change! w2 not-procedure))

(define (gate-and w1 w2 w3)
  (define (and-procedure)
      (sim-add-action! (wire-sim w1) 1 (λ () (wire-set! w1 (and (wire-value w2) (wire-value w3))))))
  (wire-on-change! w2 and-procedure)
  (wire-on-change! w3 and-procedure))

(define (gate-nand w1 w2 w3)
  (define (nand-procedure)
      (sim-add-action! (wire-sim w1) 1 (λ () (wire-set! w1 (not (and (wire-value w2) (wire-value w3)))))))
  (wire-on-change! w2 nand-procedure)
  (wire-on-change! w3 nand-procedure))

(define (gate-or w1 w2 w3)
  (define (or-procedure)
      (sim-add-action! (wire-sim w1) 1 (λ () (wire-set! w1 (or (wire-value w2) (wire-value w3))))))
  (wire-on-change! w2 or-procedure)
  (wire-on-change! w3 or-procedure))

(define (gate-nor w1 w2 w3)
  (define (nor-procedure)
      (sim-add-action! (wire-sim w1) 1 (λ () (wire-set! w1 (not (or (wire-value w2) (wire-value w3)))))))
  (wire-on-change! w2 nor-procedure)
  (wire-on-change! w3 nor-procedure))

(define (gate-xor w1 w2 w3)
  (define (xor-procedure)
      (sim-add-action! (wire-sim w1) 2 (λ () (wire-set! w1 (xor (wire-value w2) (wire-value w3))))))
  (wire-on-change! w2 xor-procedure)
  (wire-on-change! w3 xor-procedure))

;;wire-gates
(define (wire-not w1)
  (let ((new-wire (make-wire (wire-sim w1))))
    (gate-not new-wire w1)
    new-wire))

(define (wire-and w1 w2)
  (let ((new-wire (make-wire (wire-sim w1))))
    (gate-and new-wire w1 w2)
    new-wire))

(define (wire-nand w1 w2)
  (let ((new-wire (make-wire (wire-sim w1))))
    (gate-nand new-wire w1 w2)
    new-wire))

(define (wire-or w1 w2)
  (let ((new-wire (make-wire (wire-sim w1))))
    (gate-or new-wire w1 w2)
    new-wire))

(define (wire-nor w1 w2)
  (let ((new-wire (make-wire (wire-sim w1))))
    (gate-nor new-wire w1 w2)
    new-wire))

(define (wire-xor w1 w2)
  (let ((new-wire (make-wire (wire-sim w1))))
    (gate-xor new-wire w1 w2)
    new-wire))

(define (bus-set! wires value)
  (match wires
    ['() (void)]
    [(cons w wires)
     (begin
       (wire-set! w (= (modulo value 2) 1))
       (bus-set! wires (quotient value 2)))]))

(define (bus-value ws)
  (foldr (lambda (w value) (+ (if (wire-value w) 1 0) (* 2 value)))
         0
         ws))

(define (flip-flop out clk data)
  (define sim (wire-sim data))
  (define w1  (make-wire sim))
  (define w2  (make-wire sim))
  (define w3  (wire-nand (wire-and w1 clk) w2))
  (gate-nand w1 clk (wire-nand w2 w1))
  (gate-nand w2 w3 data)
  (gate-nand out w1 (wire-nand out w3)))

  ;;test - half-adder circuit
  #|
(define (half-adder out1 out2 in1 in2)
  (define d (wire-or in1 in2))
  (gate-and out2 in1 in2)
  (define e (wire-not out2))
  (gate-and out1 d e))

(define my-sim (make-sim))
(define a (make-wire my-sim))
(define b (make-wire my-sim))
(define s (make-wire my-sim))
(define c (make-wire my-sim))
(half-adder s c a b)

(sim-wait! my-sim 4)

(check-equal? (wire-value s) #f)
(check-equal? (wire-value c) #f)

(wire-set! a #t)
(sim-wait! my-sim 1)

(check-equal? (wire-value s) #f)
(check-equal? (wire-value c) #f)

(sim-wait! my-sim 3)

(check-equal? (wire-value s) #t)
(check-equal? (wire-value c) #f)

(wire-set! b #t)
(sim-wait! my-sim 4)

(check-equal? (wire-value s) #f)
(check-equal? (wire-value c) #t)|#