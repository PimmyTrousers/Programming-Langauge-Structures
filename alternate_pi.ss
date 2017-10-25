
(define (viete_helper prod v i n)
   (cond
     ((> i n)  prod)
     (else     (viete_helper  (* prod  0.5  v)   (sqrt (+ 2 v))  (+ i 1)  n))
   )
)

(/  2  (viete_helper  1  (sqrt 2)  1  1) )
(/  2  (viete_helper  1  (sqrt 2)  1  2) )
(/  2  (viete_helper  1  (sqrt 2)  1  3) )
(/  2  (viete_helper  1  (sqrt 2)  1  12) )
(/  2  (viete_helper  1  (sqrt 2)  1  1000) )

