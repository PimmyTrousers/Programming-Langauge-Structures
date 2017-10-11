(define test_list (list 2 3 4 5))

(define (new_line)
    (display "\n")
)

(define (helper test_list empty_list)
    (cond
    ((null? test_list) empty_list)
        (else 
            ; (new_line)
            ; (display (car test_list))
            ; (new_line)
            ; (display empty_list)
            (helper (cdr test_list) (cons (car test_list) empty_list))
        )
    )
)

(define (reverse_list test_list)
    (define empty_list (list ))
    (new_line)
    (display "here is the reversed list")
    (helper test_list empty_list)
)

(define (new_line)
    (display "\n")
)
(display "IS IT REVERSED??")
(reverse_list test_list)




