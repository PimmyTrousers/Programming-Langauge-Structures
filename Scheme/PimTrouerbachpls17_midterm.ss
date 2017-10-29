
#|
                Instructions for
       Programming Languages Midterm, Fall 17

1. You may use your notes and old files but not the internet
   so disconnect yourself from the internet after downloading
   this file, pls17_midterm.ss, via

       sftp student@simpson1
       mget pls17_midterm.ss
       quit

   and any other files you might want.

2. Rename this file to something that includes your name
   and ends with pls17_midterm.ss

   Example :

   mv  pls17_midterm.ss  JoeSmith_pls17_midterm.ss


3. Write code in this file that answers both questions.

   You may use car, cdr, cons, null?, reverse, list, 
   simple arithemtic and other functions that have been
   discussed in class but no exotic scheme functions that
   have not been discussed in class (that you might have
   discovered on the internet).
      
|#



;====================================================================================

;  Question 1 : implement the intermix function to behave
					;  as described in these examples :

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


(define (intermix list_1 list_2)
  (cond
  ((null? list_1) list_2)
  ((null? list_2) list_1)
    (else
      (cons (car list_1) 
            (cons 
                (car list_2) 
                (intermix (cdr list_1) (cdr list_2))
            )
      )
    )
   )
  )


(define p (list 1 2 3 4 5 6 7 8))
(define q (list -1 -2 -3 -4 -5 -6 -7 -8 -9))
(define r (list 'a 'b 'c))


(intermix p q) 
(intermix q p) 
(intermix p r) 

;====================================================================================


;  Question 2 : implement the msum function to behave
;  as described in these examples :


(define b
  (list
     (list 1 2 3)
     (list 10 20 30 40 50)
     (list 5 6)
  )
)


(define c
  (list
     (list 1 2 3 4 5)
     (list -3 -5)
     (list 10)
     (list 8 7 5)
  )
)

(define (msum list_1 answer)
  (cond
   ((null? list_1) answer)
   (else 
    (msum (cdr list_1) (msum_helper (car list_1) answer))
    )
   )
  )
  
(define (msum_helper row answer)
  (cond
    ((null? row) answer)
    (else
      (msum_helper (cdr row) (+ answer (car row)))
    )
  )
)

(define test (list 1 2 3))

(msum_helper test 0)


(msum b 0)
(msum c 0)

