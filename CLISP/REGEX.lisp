(defun deltil(exp)
    (cond
        ((null exp) nil)
        ((eq '\| (car exp)) (cdr exp))
        (T (deltil (cdr exp)))
    )
)
(defun gettil(exp)
    (cond
        ((null exp) nil)
        ((eq '\| (car exp)) nil)
        (T (cons (car exp) (gettil (cdr exp))))
    )
)
(defun paral (exp)
    (cond
        ((null exp) nil)
        (T (cons (gettil exp) (paral (deltil exp))))
    )
)
;--------------------------------------------------------------------------------------------------------------------------
(defun makeauto(node1 symbol node2)
    (cond
        ((eq nil node2) (list node1 symbol))
        (T (list node1 symbol node2))
    )
)
(defun iteration (iter nodenum val)
    (cond
        ((null iter) (list (makeauto nodenum val (+ 1 nodenum))))
        ((eq '+ iter) (append (list (makeauto nodenum val (+ 1 nodenum))) (list (makeauto (+ 1 nodenum) val (+ 1 nodenum)))))
        ((eq '* iter) (append (list (makeauto nodenum 'eps (+ 1 nodenum))) (list (makeauto (+ 1 nodenum) val (+ 1 nodenum)))))
        (T nil)
    )
)
(defun ifchar(exp nodenum)
    (cond
        ((null exp)nil)
        ((characterp (cadr exp)) (append (list (makeauto nodenum (car exp) (+ 1 nodenum))) (ifchar (cdr exp) (+ 1 nodenum))))
        (T (append (iteration (cadr exp) nodenum (car exp)) (ifchar (cddr exp) (+ 1 nodenum))))
    )
)
(defun ifcharfirst(exp nodenum)
    (cond
        ((null exp)nil)
        ((characterp (cadr exp)) (append (list (makeauto 'S (car exp) (+ 1 nodenum))) (ifchar (cdr exp) (+ 1 nodenum))))
        (T (append (iteration (cadr exp) nodenum (car exp)) (ifchar (cddr exp) (+ 1 nodenum))))
    )
)
(defun start (exp nodenum)
    (cond
        ((null exp) nil)
        (T (append (ifcharfirst (car exp) nodenum) (start (cdr exp) (+ 100 nodenum))))
    )
)
;------------------------------------------------------------------------------------------------------------------------------
(defun searchset (node val auto)
    (cond
        ((null auto) nil)
        ((and (eq node (caar auto)) (eq val (cadr (car auto)))) (cons (caddr (car auto)) (searchset node val (cdr auto))))
        (T (searchset node val (cdr auto)))
    )
)
(defun getlasts (auto)

)
(defun combine-last(auto) (CL auto (getlasts auto)))
(defun CL(auto lastnodes)
    (cond
        ((null auto) nil)
        ((subset (list (caddr (car auto)) lastnodes) (append (list (makeauto (caar auto) (cadr auto) 'F)) (CL (cdr auto) lastnodes)))
        (T (append (list (car auto)) (CL (cdr auto) lastnodes)))
    )
)

(defun determinate (automate))
;--------------------------------------------------------------------------------------------------------------------------
(defun regex(expression)
    (start (paral expression) 0)
)

(print (regex '(#\a + #\b \| #\a #\b * #\a)))
; (print (determinate (regex '(#\a + #\b \| #\a #\b * #\a))))
(print (searchset '0 '#\a (regex '(#\a + #\b \| #\a #\b * #\a))))
(print (combine-last (regex '(#\a + #\b \| #\a #\b * #\a))))

; (print (regex '(#\a #\b + #\a * #\b \| #\a #\b + #\a + #\b + #\b)))
