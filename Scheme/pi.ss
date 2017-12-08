(define (pi n i upper mult)
(cond
((= n i) (/ 2 mult))
(else
 (pi n (+ i 1) (sqrt (+ 2 upper)) (* mult (/ (sqrt (+ 2 upper)) 2)) ) )

)
)

(pi 1 0 0 1) 
(pi 2 0 0 1)
(pi 3 0 0 1)
(pi 4 0 0 1)
(pi 5 0 0 1)