
; trivial symbolic differentiation program
; enhance with   -, /, sin, cos, exp, log

;; -    DONE
;; /    IN PROGRESS
;; sin
;; cos
;; exp
;; log


(define  (constant? x)  (number? x))

(define  (variable? x)  (symbol? x))

(define  (same-variable?  v1 v2)
   (and (variable? v1) (variable? v2) (eq? v1 v2))
)

; make a sum expression from two sub-expressions :
(define  (make-sum e1 e2)  (list '+ e1 e2))

(define  (make-diff e1 e2)  (list '- e1 e2))

(define  (make-product e1 e2)  (list '* e1 e2))

(define (make-sin e1) (list 'cos e1))

(define  (sum?  e)
     (and (list? e) (= (length e) 3) (eq? (car e) '+)) 
)

(define  (diff?  e)
     (and (list? e) (= (length e) 3) (eq? (car e) '-)) 
)

(define  (product?  e)
    (and (list? e) (= (length e) 3) (eq? (car e) '*)) 
)


(define  (div?  e)
    (and (list? e) (= (length e) 3) (eq? (car e) '/)) 
)

(define  (sin?  e)
    (and (list? e) (= (length e) 2) (eq? (car e) 'sin)) 
)

(define (cos? e)
    (and (list? e) (= (length e) 2) (eq? (car e) 'cos))
)


; to extract first and second operands from a binary expression :
(define (first_operand e)  (cadr e))

(define (second_operand e)  (caddr e))






; compute the symbolic derivative of the expression e with respect to the variable v :
(define (deriv e v)
  (cond
      ((constant? e)
             0
      )

      ((variable? e)    
             (cond
                 ((same-variable? e v)   1)
                 (else  0)
             )
      )

      ((sum? e)     
             (make-sum  (deriv  (first_operand e) v)
                        (deriv  (second_operand e) v)
             )
      )

      ((product? e)     
             (make-sum
                    (make-product  (first_operand   e)
                                   (deriv  (second_operand e) v)
                    )
                    (make-product  (deriv  (first_operand   e) v)
                                   (second_operand e) 
                    )
             )
      )
      ((diff? e)     
             (make-diff  (deriv  (first_operand e) v)
                        (deriv  (second_operand e) v)
             )
      )
      ((sin? e)
        (make-sin deriv e v)
      )

      ( else 'screwup)
  )
)

(deriv '(+ x 3) 'x)
(deriv '(* x y) 'x)
(deriv '(* (* x x) (+ x 3))  'x)
(deriv '(* (* x y) (+ x 3))  'x)
(deriv '(+ x ) 'x)
(deriv '(- x 3) 'x)
(deriv '(sin x) 'x)