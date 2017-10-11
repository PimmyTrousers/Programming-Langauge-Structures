
; Tail recursion occurs when the function has nothing
; to do when his child returns an answer other than
; to also return the answer to his parent.
; It turns out this can be detected and done in constant space.
; The first version of factorial below is NOT tail recursive
; since the child's answer must be mutliplied by n before
; returning an answer to the parent.  The second version IS
; tail recursive.


(define  (factorial n)

   (cond
     ((= n 0) 1)
     (else  (*  n  (factorial (- n 1))))
   )

)




(define  (tail-recursive-fac   answer  n)

   (cond
     ((= n 0)   answer)
     (else  (tail-recursive-fac    (*  answer n)  (- n 1)))
   )

)


; now test it

(factorial 5)
(tail-recursive-fac   1  5)
(+  (tail-recursive-fac   1  30)  (tail-recursive-fac  1 7))


