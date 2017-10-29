(define (power base pow)
  (cond
    ((= pow 0) 1)
    (else
      (* base (power
                base
                (- pow 1)
              )
      )
    )
  )
)

(power 5 3)
(power 3 5)
(power 1 1)
(power 2 1)
(power 1 0)
(power 200 0)
(power 0 200)
(power 1000 1000)
