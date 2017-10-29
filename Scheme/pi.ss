(define (pi_work answer n)
  (cond
    ((= n -1) answer)
    (else (pi_work (/ (* n n) (+ 2 answer)) (- n 2) ) )
  )
)

(define (pi n)
  (/ 4 (+ 1 (pi_work -1 n)))
)

(pi 5.0)
c
