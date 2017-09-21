
(define a 2)
(define b 5)
(define c -3)


(define a 1)
(define b -6)
(define c 25)

(define d (sqrt (- (* b b) (* 4 a c))))
(define x (/ (+ (- 0 b) d) (* 2 a)))
(define y (/ (- (- 0 b) d) (* 2 a)))

a
b
c
d
x
y
(+ (* a x x) (* b x) c)
(+ (* a x x) (* b x) c)

(define (inc x)
  (+ x 1)
  )

(inc 1236)
(inc (inc 9))

(define (stupid_line x1 y1 x2 y2)
  (define a (expt (- x2 x1) 2))
  (define b (expt (- y2 y1) 2))
  (sqrt(+ a b))
  )

(stupid_line 200 100 204 103)
