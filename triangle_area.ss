(define (triangle_area x1 y1 x2 y2 x3 y3)
  (define length1 (stupid_line x1 y1 x2 y2))
  (define length2 (stupid_line x2 y2 x3 y3))
  (define length3 (stupid_line x3 y3 x1 y1))
  (define total_length (+ length1 length2 length3))
  (define s (/ total_length 2))
  (define area (sqrt (* s (- s length1) (- s length2) (- s length3))))
area
)

(define (stupid_line x1 y1 x2 y2)
  (define a (expt (- x2 x1) 2))
  (define b (expt (- y2 y1) 2))
  (sqrt(+ a b))
)

(triangle_area 100 200 120 205 110 230)

