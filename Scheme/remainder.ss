(define (remainder x y)
  (cond
    ((< x y) x)
    (else (remainder (- x y) y))
  )
)

(remainder 37 10)
(remainder 20 10)
(remainder 30 40)
