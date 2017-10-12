(define test_list (list 2 3 4 5))
(define bin (list 1 1 0 1))
(define bin1 (list 1 1 1 1 1 1 1 1 1 1 0 1 0 1 1))
(define bin2 (list 1 1))
(define bin3 (list 0 0 0 0 1))

(define (new_line)
    (display "\n")
)



(define (helper test_list empty_list)
    (cond
    ((null? test_list) empty_list)
        (else 
            (helper (cdr test_list) (cons (car test_list) empty_list))
        )
    )
)

(define (reverse_list test_list)
    (define empty_list (list ))
    (new_line)
    (helper test_list empty_list)
)

(define (new_line)
    (display "\n")
)

(define (bintodec_helper bin)
    (bintodec bin 0 0)
)

(define (bintodec binary_list result place)
    (cond
    ((null? binary_list) result)
        (else
            (if (= (car binary_list) 1)

                ;; CASE IF WE ARE LOOKING AT A 1

                (bintodec (cdr binary_list) ; passes the tail of the list
                          (+ result (expt 2 place)) ; adds the operation to the result 
                          (+ place 1) ; moves the place over by one 
                )

                ;; CASE IF WE ARE LOOKING AT A 0

                (bintodec (cdr binary_list) ; passes the tail of the list
                          result ; since we found a 0 do nothing to the result 
                          (+ place 1) ; moves the place over by one 
                )
            )
        )
    )
)

(bintodec_helper (reverse_list bin))
(bintodec_helper (reverse_list bin1))
(bintodec_helper (reverse_list bin2))
(bintodec_helper (reverse_list bin3))







