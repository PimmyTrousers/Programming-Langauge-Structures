

(define a  (list  100 130 160 180))

a
; a = (100 130 160 180)

(car a)
; (car a) = 100
(cdr a)
; (cdr a) = 130 160 180
(car (cdr a))
; (car (cdr a)) = 130
(cdr (cdr a))
; (cdr (cdr a)) = 160 180
(car (cdr (cdr a)))
; (car (cdr (cdr a))) = 160
(cdr (cdr (cdr a)))
; (cdr (cdr (cdr a))) = 180
(car (cdr (cdr (cdr a))))
; (car (cdr (cdr (cdr a)))) = 180
(cdr (cdr (cdr (cdr a))))
; (cdr (cdr (cdr (cdr a)))) = ( )


(cons -5  a)
(list )
(cons  9 (list ))
(cons  8 (cons  9 (list )))
(cons  7 (cons  8 (cons  9 (list ))))



(define b  (list ))
b

(null?  a)
(null?  b)
(length a)
(length b)
