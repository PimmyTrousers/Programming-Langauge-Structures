(define matrix1 (list (list 1 2 3) (list 1 2 3) (list 1 2 3)))
(define matrix2 (list (list 1 2) (list 1 2) (list 1 2)))
(define matrix3 (list (list 12 2 3 4 5 6 7) (list 1 2 3 4 5 6 7)))
(define matrix4 (list (list 12 2 3 4 5 6 7) (list 1 2 3 4 5 6 7) (list 12 2 3 4 5 6 7) (list 12 2 3 4 5 6 7) (list 12 2 3 4 5 6 7) (list 12 2 3 4 5 6 7) (list 12 2 3 4 5 6 7) (list 12 2 3 4 5 6 7) (list 12 2 3 4 5 6 7) (list 12 2 3 4 5 6 7) (list 12 2 3 4 5 6 7) (list 12 2 3 4 5 6 7) (list 12 2 3 4 5 6 7)))

(define (transpose matrix)
    (transpose_helper (list ) matrix)
)

(define (transpose_helper transposed matrix1)
    (cond
    ((null? (car matrix1)) (reverse_list transposed)) ;; if the first list is empty returned the transposed list
        (else           
            (transpose_helper (cons (map car matrix1) transposed) (map cdr matrix1)) ;; add the first elements to the transposed array and pass the tail of each list as matrix1
        )
    )
)

(define (reverse_list test_list)
    (reverse_list_helper test_list (list ))
)

(define (reverse_list_helper test_list empty_list)
    (cond
    ((null? test_list) empty_list)
        (else 
            (reverse_list_helper (cdr test_list) (cons (car test_list) empty_list))
        )
    )
)

(define (new_line test)
    (if (= test 0)
        (
            (display "\n")
        )
        (
            (display " ")
        )
    )
)

(define (pretty_print matrix test)
    (display matrix)
   ;; (new_line test)
    (cond
    ((null? matrix1) matrix)
        (else 
            (display (car matrix))
            (display "\n")
            (pretty_print (cdr matrix) 1)
        )
    )
)

(transpose matrix1)
(transpose matrix2)
(transpose matrix3)
(transpose matrix4)

