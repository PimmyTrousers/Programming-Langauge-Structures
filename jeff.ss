(define test_list (list 2 3 4 5))

(define (reverse_list test_list)
    (car test_list)
    (reverse_list (cdr test_list))
)

(reverse_list test_list)



