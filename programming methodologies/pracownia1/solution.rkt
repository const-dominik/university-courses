#lang racket

(provide (struct-out column-info)
         (struct-out table)
         (struct-out and-f)
         (struct-out or-f)
         (struct-out not-f)
         (struct-out eq-f)
         (struct-out eq2-f)
         (struct-out lt-f)
         table-insert
         table-project
         table-sort
         table-select
         table-rename
         table-cross-join
         table-natural-join)

(define-struct column-info (name type) #:transparent)

(define-struct table (schema rows) #:transparent)

(define cities
  (table
   (list (column-info 'city    'string)
         (column-info 'country 'string)
         (column-info 'area    'number)
         (column-info 'capital 'boolean))
   (list (list "Wrocław" "Poland"  293 #f)
         (list "Warsaw"  "Poland"  517 #t)
         (list "Poznań"  "Poland"  262 #f)
         (list "Berlin"  "Germany" 892 #t)
         (list "Munich"  "Germany" 310 #f)
         (list "Paris"   "France"  105 #t)
         (list "Rennes"  "France"   50 #f))))

(define countries
  (table
   (list (column-info 'country 'string)
         (column-info 'population 'number))
   (list (list "Poland" 38)
         (list "Germany" 83)
         (list "France" 67)
         (list "Spain" 47))))

(define (empty-table columns) (table columns '()))

(define (check-type value type)
  (or
    (and (string? value) (equal? 'string type))
    (and (number? value) (equal? 'number type))
    (and (boolean? value) (equal? 'boolean type))
    (and (symbol? value) (equal? 'symbol type))
  )
)

(define (schema-includes schema elem)
  (cond
    [(null? schema) #f]
    [(equal? elem (column-info-name (car schema))) #t]
    [else (schema-includes (cdr schema) elem)]
  )
)

(define (are-all-cols-in-schema my-cols schema)
    (if (null? my-cols)
        #t
        (if (schema-includes schema (car my-cols))
            (are-all-cols-in-schema (cdr my-cols) schema)
            #f
        )
    )
)

(define (get-elem elem row schema)
  (define (find-elem my-row my-schema)
    (if (equal? elem (column-info-name (car my-schema)))
      (car my-row)
      (find-elem (cdr my-row) (cdr my-schema)))
    )
    (find-elem row schema)
  )

(define (compare w1 w2)
  (cond [(string? w1) (string<? w1 w2)]
        [(symbol? w1) (symbol<? w1 w2)]
        [(number? w1) (< w1 w2)]
        [(boolean? w1) (and (equal? #f w1) (equal? #t w2))] ; #f < #t 
  )
)

(define (get-name-type name schema)
  (define (it my-schema)
    (if (null? my-schema)
      (error 'get-name-type "unknown column")
      (if (equal? (column-info-name (car my-schema)) name)
          (column-info-type (car my-schema))
          (it (cdr my-schema))
      )
    )
  )
  (it schema)
)

; Wstawianie
(define (table-insert row tab)
   (define (check-and-add my-row schema)
     (if (and (null? my-row) (null? schema))
          (cons row (table-rows tab))
          (if (or (null? my-row) (null? schema))
              (error 'table-insert "length of row and schema doesn't match")
              (if (check-type (car my-row) (column-info-type (car schema)))
                  (check-and-add (cdr my-row) (cdr schema))
                  (error 'table-insert "row doesnt match the table schema")))))
   (table (table-schema tab) (check-and-add row (table-schema tab)))
)

; (table-insert (list "Rzeszow" "Poland" 129 #f) cities)
; (table-insert (list "Rzeszow" 100 129 #f) cities)
; (table-insert (list "Warsaw"  "Poland"  517 #t) cities)
; (table-insert (list "Rzeszow" "Poland" 129 #f) (empty-table '()))
; (table-insert (list "Rzeszow" "Poland" 129 #f) (empty-table (table-schema cities)))
; (table-insert (list "Rzeszow" "Poland" 129 #f) countries)

; Projekcja
(define (table-project cols tab)
  (define (filter-schema schema filtered-schema)
      (if (null? schema)
          filtered-schema
          (if (member (column-info-name (car schema)) cols)
              (filter-schema (cdr schema) (append filtered-schema (list (car schema))))
              (filter-schema (cdr schema) filtered-schema))
      )
    )

  (define (filter-row row filtered-row schema)
    (if (null? row)
        filtered-row
        (if (member (column-info-name (car schema)) cols)
            (filter-row (cdr row) (append filtered-row (list (car row))) (cdr schema))
            (filter-row (cdr row) filtered-row (cdr schema)))
        )
    )

  (define (filter-rows rows filtered-rows schema)
    (if (null? rows)
        filtered-rows
        (filter-rows
          (cdr rows)
          (append filtered-rows (list (filter-row (car rows) null schema)))
          schema)
        )
    )
    
  (define filtered-schema (filter-schema (table-schema tab) null))
  (define filtered-rows (filter-rows (table-rows tab) null (table-schema tab)))
 
  (if (are-all-cols-in-schema cols (table-schema tab))
      (table filtered-schema filtered-rows)
      (error 'project-table "unknown column in given columns")
  )
)

; (table-project '(country city) cities)
; (table-project '(country country city) cities)  
; (table-project '(city country dog) cities)
; (table-project '() cities)
; (table-project '(city) (empty-table (table-schema cities)))

; Zmiana nazwy
(define (table-rename col ncol tab)
  (define (rename schema renamed-schema)
    (if (null? schema)
        renamed-schema
        (if (equal? col (column-info-name (car schema)))
            (rename (cdr schema) (append renamed-schema (list (column-info ncol (column-info-type (car schema))))))
            (rename (cdr schema) (append renamed-schema (list (car schema))))
        )
    )
  )
  (if (schema-includes (table-schema tab) col)
      (table (rename (table-schema tab) null) (table-rows tab))
      (error 'table-rename "unknown column")
  )
)

; (table-rename 'city 'name cities)
; (table-rename 'city 'country cities)
; (table-rename 'dog 'name cities)
; (table-rename 'city 'city cities)

; Sortowanie
(define (table-sort cols tab)
  (define (insert n sorted-rows key schema)
    (if (null? sorted-rows)
        (list n)
        (if (compare (get-elem key n schema) (get-elem key (car sorted-rows) schema))
            (cons n sorted-rows)
            (cons (car sorted-rows) (insert n (cdr sorted-rows) key schema))
        )
    )
  )

  (define (insertion-sort key rows schema)
    (define (it my-rows sorted-rows)
      (if (null? my-rows)
          sorted-rows
          (it (cdr my-rows) (insert (car my-rows) sorted-rows key schema))))
    (it rows null)
  )

  ;wykonuje sortowanie względem każdego elementu cols, zaczynając od tyłu (reverse cols jako argument it)
  (define (init-sorting-by-key order rows)
    (if (null? order)
        rows
        (init-sorting-by-key (cdr order) (insertion-sort (car order) rows (table-schema tab)))
    )
  )
  (define (sort cols)
    (if (are-all-cols-in-schema cols (table-schema tab))
      (table (table-schema tab) (init-sorting-by-key (reverse cols) (table-rows tab)))
      (error 'table-sort "unknown column")
    ))

  (sort (if (not (list? cols)) (list cols) cols))
)

; (table-sort '(country) (table-sort '(city) cities))
; (table-sort '(country) cities)
; (table-sort '(area) cities)
; (table-sort '(capital) cities)
; (table-sort 'capital cities)
; (table-sort '(country city) cities)
; (table-sort '(country city area capital) cities)
; (table-sort '(dog) cities)
; (table-sort '() cities)
; (table-sort '(country) (empty-table (table-schema cities)))

; Selekcja

(define-struct and-f (l r))
(define-struct or-f (l r))
(define-struct not-f (e))
(define-struct eq-f (name val))
(define-struct eq2-f (name name2))
(define-struct lt-f (name val))

(define (eval-cond condition row schema)
  (cond
    [(and-f? condition) (and (eval-cond (and-f-l condition) row schema) (eval-cond (and-f-r condition) row schema))]
    [(or-f? condition) (or (eval-cond (or-f-l condition) row schema) (eval-cond (or-f-r condition) row schema))]
    [(not-f? condition) (not (eval-cond (not-f-e condition) row schema))]
    [(eq-f? condition) (equal? (get-elem (eq-f-name condition) row schema) (eq-f-val condition))]
    [(eq2-f? condition) (equal? (get-elem (eq2-f-name condition) row schema) (get-elem (eq2-f-name2 condition) row schema))]
    [(lt-f? condition) (compare (get-elem (lt-f-name condition) row schema) (lt-f-val condition))]
  )
)

(define (check-if-correct-types condition schema)
  (cond
    [(and-f? condition) (and (check-if-correct-types (and-f-l condition) schema) (check-if-correct-types (and-f-r condition) schema))]
    [(or-f? condition) (and (check-if-correct-types (or-f-l condition) schema) (check-if-correct-types (or-f-r condition) schema))]
    [(not-f? condition) (check-if-correct-types (not-f-e condition) schema)]
    [(eq-f? condition) (check-type (eq-f-val condition) (get-name-type (eq-f-name condition) schema))]
    [(eq2-f? condition) (equal? (get-name-type (eq2-f-name condition) schema) (get-name-type (eq2-f-name2 condition) schema))]
    [(lt-f? condition) (check-type (lt-f-val condition) (get-name-type (lt-f-name condition) schema))]
  )
)

(define (table-select form tab)
  (define (pick-rows my-rows selected-rows)
    (if (null? my-rows)
      selected-rows
      (if (eval-cond form (car my-rows) (table-schema tab))
        (pick-rows (cdr my-rows) (append selected-rows (list (car my-rows))))
        (pick-rows (cdr my-rows) selected-rows))
    )
  )
  (if (check-if-correct-types form (table-schema tab))
      (table (table-schema tab) (pick-rows (table-rows tab) null))
      (error 'table-select "types in formula don't match")
  )
)

; (table-select (and-f (eq-f 'capital #t) (not-f (lt-f 'area 300))) cities)
; (table-select (lt-f 'area -1) cities)
; (table-select (eq2-f 'country 'city) cities)
; (table-select (eq2-f 'country 'dog) cities)
; (table-select (or-f (lt-f 'area -1) (not-f (lt-f 'area -1))) cities)
; (table-select (and-f (or-f (eq-f 'capital #t) (or (eq2-f 'country 'city)
; (lt-f 'country "France"))) (not-f (lt-f 'area 300))) cities)

; Złączenie kartezjańskie
(define (table-cross-join tab1 tab2)
  ;zwraca połączenie każdego wiersza z tab1 z każdym wierszem z tab2
  (define (get-cross-joined-rows my-tab1-rows new-rows)
    (if (null? my-tab1-rows)
        new-rows
        (get-cross-joined-rows (cdr my-tab1-rows) (append new-rows (join-tab2-rows (table-rows tab2) null (car my-tab1-rows)))))
  )

  ;zwaraca listę wierszy powstałych w skutek połączenia pojedynczego wiersza z tab1 z każdym z wierszy z tab2
  (define (join-tab2-rows my-tab2-rows new-rows row)
    (if (null? my-tab2-rows)
        new-rows
        (join-tab2-rows (cdr my-tab2-rows) (append new-rows (list (append row (car my-tab2-rows)))) row)))

    (if (or (null? (table-rows tab1)) (null? (table-rows tab2)))
        (table (append (table-schema tab1) (table-schema tab2)) null)
        (table (append (table-schema tab1) (table-schema tab2)) (get-cross-joined-rows (table-rows tab1) null))
  )
)

; (table-cross-join cities (table-rename 'country 'country2 countries))
; 7 x 4 = 28
; (display (length (table-rows cities))) (display " x ")
; (display (length (table-rows (table-rename 'country 'country2 countries)))) (display " = ")
; (display (length (table-rows (table-cross-join cities (table-rename 'country 'country2 countries)))))
; (table-cross-join cities cities)
; (table-cross-join cities (empty-table null))
; (table-cross-join cities (empty-table (table-schema cities)))
; (table-cross-join cities (empty-table (table-schema countries)))

; Złączenie
(define (rename-symbol str1)
  (string->symbol (string-append (symbol->string str1) "-renamed"))
)

(define (rename-repeating-rows schema tab)
  (define (it tab2-schema renamed-schema)
    (if (null? tab2-schema)
        renamed-schema
        (if (schema-includes schema (column-info-name (car tab2-schema)))
            (it (cdr tab2-schema)
                (append renamed-schema
                    (list (column-info (rename-symbol (column-info-name (car tab2-schema))) (column-info-type (car tab2-schema))))))
            (it (cdr tab2-schema) (append renamed-schema (list (car tab2-schema))))
        )
    )
  )
  (it (table-schema tab) null)
)

(define (table-natural-join tab1 tab2)
  (define tab2-edited-schema (table (rename-repeating-rows (table-schema tab1) tab2) (table-rows tab2)))
  (define cartesian-joined (table-cross-join tab1 tab2-edited-schema))
  (define (check-if-repeating-are-equal my-row schema whole-row)
    (cond 
      [(null? schema) #t]
      [(or (not (schema-includes 
                (table-schema tab2-edited-schema)
                (rename-symbol (column-info-name (car schema)))))
            (eval-cond (eq2-f (column-info-name (car schema)) 
                              (rename-symbol (column-info-name (car schema))))
                        whole-row
                        (table-schema cartesian-joined)))
        ;if column is not repeating or it is and values are equal
        (check-if-repeating-are-equal (cdr my-row) (cdr schema) whole-row)]
      [else #f]
    )
  )
  (define (filter-tab rows result) 
    (if (null? rows)
        result
        (if (check-if-repeating-are-equal (car rows) (table-schema tab1) (car rows))
          (filter-tab (cdr rows) (append result (list (car rows))))
          (filter-tab (cdr rows) result)))
  )
  (define filtered-cartesian (table (table-schema cartesian-joined) (filter-tab (table-rows cartesian-joined) null)))
  (define (filter-schema schema result)
    (if (null? schema)
      result
      (if (string-suffix? (symbol->string (column-info-name (car schema))) "-renamed")
          (filter-schema (cdr schema) result)
          (filter-schema (cdr schema) (append result (list (car schema))))            
      )
    )
  )
  (define filtered-schema (filter-schema (table-schema filtered-cartesian) null))
  (define (schema-names-to-list schema result)
    (if (null? schema)
        result
        (schema-names-to-list (cdr schema) (append result (list (column-info-name (car schema)))))))
  (table-project (schema-names-to-list filtered-schema null) filtered-cartesian)
)

; (table-natural-join cities cities)
; (table-natural-join cities countries)
; (table-natural-join countries cities)
; (table-natural-join countries (empty-table null))
; (table-natural-join countries (empty-table (table-schema countries)))
; ( table-project '( city country area capital population )
; ( table-select ( eq2-f 'country 'country1 )
; ( table-cross-join cities
; ( table-rename 'country 'country1
; countries ) ) ) )
; (table-natural-join (table-rename 'population 'area countries) cities)