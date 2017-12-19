(define  (constant? x)  (number? x))

(define  (variable? x)  (symbol? x))

(define  (same-variable?  v1 v2)
   (and (variable? v1) (variable? v2) (eq? v1 v2))
)

(define  (make-sum a1 a2)  (list '+ a1 a2))

(define  (make-sub a1 a2)  (list '- a1 a2))

(define  (make-product a1 a2)  (list '* a1 a2))

(define  (make-quotient a1 a2)  (list '/ a1 a2))

(define  (make-sin a1) (list 'cos a1))

(define  (make-cos a1) (make-product (list 'sin a1) -1))

(define  (make-exp a1) (list 'exp a1))

(define  (make-log a1) (list '/ '1 a1))

(define  (sum?  x)
     (and (pair? x) (eq? (car x) '+))
)

(define (addend s)  (cadr s))

(define (augend s)  (caddr s))


(define (sub?  x)
     (and (pair? x) (eq? (car x) '-))
)

(define (subtrahend s)  (cadr s))

(define (minuend s)     (caddr s))


(define  (product?  x)
     (and (pair? x) (eq? (car x) '*))
)

(define (multiplier s)  (cadr s))

(define (multiplicand s)  (caddr s))

(define (sin? x)
    (and (pair? x) (eq? (car x) 'sin))
)
(define (cos? x)
    (and (pair? x) (eq? (car x) 'cos))
)

(define (quotient? x)
     (and (pair? x) (eq? (car x) '/))
)

(define (dividend s) (cadr s))

(define (divisor s) (caddr s))

(define (exp? x)
     (and (pair? x) (eq? (car x) 'exp))
)

(define (log? x)
     (and (pair? x) (eq? (car x) 'log))
)

(define (first s) (cadr s))

(define (second s) (caddr s))


(define (math_is_dumb expr var)
  (cond
      ((constant? expr)
             0
      )

      ((variable? expr)
             (cond
                 ((same-variable? expr var)   1)
                 (else  0)
             )
      )

      ((sum? expr)
             (make-sum  (math_is_dumb  (addend expr) var)
                        (math_is_dumb  (augend expr) var)
             )
      )

      ((sub? expr)
            (make-sub  (math_is_dumb (subtrahend expr) var)
			(math_is_dumb (minuend    expr) var)
	     )
      )
      ((product? expr)
             (make-sum
                    (make-product  (multiplier   expr)
                                   (math_is_dumb  (multiplicand expr) var)
                    )
                    (make-product  (math_is_dumb  (multiplier   expr) var)
                                   (multiplicand expr)
                    )
             )
      )

      ((quotient? expr)
            (make-quotient
	            (make-sub
                          (make-product  (divisor   expr)
                                   (math_is_dumb  (dividend expr) var)
                          )
                          (make-product  (math_is_dumb  (divisor   expr) var)
                                   (dividend expr)
                          )
                    )

	            (make-product (divisor expr) (divisor expr))
             )
      )

      ((log?  expr) (make-product (make-log (first expr)) (math_is_dumb (first expr) var)))

      ((exp? expr) (make-product (make-exp (first expr)) (math_is_dumb (first expr) var)))
      ((sin? expr) (make-product (make-sin (first expr)) (math_is_dumb (first expr) var)))
      ((cos? expr) (make-product (make-cos (first expr)) (math_is_dumb (first expr) var)))

      (else 'Something_went_wrong)
  )
)

(define x 3)

(define expression1 (math_is_dumb '(log (* x x))   'x))
(eval expression1  user-initial-environment) ; the environment has x defined as 3

(define expression2 (math_is_dumb '(/ (cos (* x x)) (+ x 1))   'x) )
(eval expression2  user-initial-environment) ; the environment has x defined as 3

(define expression3 (math_is_dumb '(exp  (/ (sin (* x x)) (+ x 1)))   'x) )
(eval expression3  user-initial-environment) ; the environment has x defined as 3


(define x 5)
(define expression4 (math_is_dumb  (math_is_dumb '(log (* x x))   'x) 'x)  )
expression4
(eval expression4  user-initial-environment) ; the environment has x defined as 5
