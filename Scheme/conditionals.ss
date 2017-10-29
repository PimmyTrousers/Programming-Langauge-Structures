(define (sum n)
  (cond
    ((= n 0) 0)
    (else (+ n (sum( - n 1))))
    )
  )

(sum 4)
(sum 100)

(define (factorial n)
  (cond
   ((= n 0) 1)
   (else (* n (factorial(- n 1))))
   )
  )

(factorial 5)
(factorial 10)

(define (choose n k)
  (define new_n (factorial n))
  (define new_k (factorial k))
  (define new_n_k (factorial (- n k)))
  (/ new_n (* new_k new_n_k))
  )

(choose 5 3) ;; 10
(choose 6 2) ;; 15
(choose 5 5) ;; 1
(choose 1 0) ;; 1
(choose 1 1) ;; 1
(choose 0 0) ;; 1
(choose 5 1) ;; 5
(choose 4 1) ;; 4
(choose 3 1) ;; 3

;; (n k) = ((n-1) (k-1)) + ((n-1) k)

(define (recursive_choose n k)
  (cond
         ((= k 1) n) ;; approved
         ((= k 0) 1) ;; approved
         ((= k n) 1) ;; approved
         ((> k n) 0) ;; approved
        (else
         (+ (recursive_choose (- n 1) (- k 1))
            (recursive_choose (- n 1) k))
         )
        )
  )

(recursive_choose 5 5)
(recursive_choose 1 3)
(recursive_choose 6 2)
(recursive_choose 5 3)
