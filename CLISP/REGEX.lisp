;---------------------------------------------------parallelize functions----------------------------------------------------
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
;----------------------------------------------------automatize functions------------------------------------------------------
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
        ((characterp (cadr exp)) (append (list (makeauto nodenum (car exp) (+ 1 nodenum))) (ifchar (cdr exp) (+ 1 nodenum))))
        (T (append (iteration (cadr exp) nodenum (car exp)) (ifchar (cddr exp) (+ 1 nodenum))))
    )
)
(defun start (exp nodenum)
    (cond
        ((null exp) nil)
        (T (append (ifcharfirst (car exp) nodenum) (start (cdr exp) (+ 100 nodenum))))
    )
)
;---------------------------------------------------end-combining functions----------------------------------------------------------
(defun check-end(x auto)
    (cond
        ((null auto) T)
        ((eq (+ 1 x) (caddr (car auto))) nil)
        (T (check-end x (cdr auto)))
    )
)
(defun get-ends (auto)
    (cond
        ((null auto) nil)
        ((check-end (caddr (car auto)) auto) (cons (caddr (car auto)) (get-ends (cdr auto))))
        (T (get-ends (cdr auto)))
    )
)

(defun combine-last(auto) (CL auto (get-ends auto)))
(defun CL(auto lastnodes)
    (cond
        ((null auto) nil)
        ((subsetp (list (caddr (car auto))) lastnodes) (append (list (makeauto (caar auto) (cadr (car auto)) 'F)) (CL (cdr auto) lastnodes)))
        (T (append (list (car auto)) (CL (cdr auto) lastnodes)))
    )
)
;--------------------------------------------------determinating functions--------------------------------------------------------
(defun search-set (node val auto)(append (list node val) (__search-set__ node val auto)))
(defun __search-set__ (node val auto)
    (cond
        ((null auto) nil)
        ((and (eq node (caar auto)) (eq val (cadr (car auto)))) (cons (caddr (car auto)) (__search-set__ node val (cdr auto))))
        (T (__search-set__ node val (cdr auto)))
    )
)
(defun determinate (automate))
;-----------------------------------------------------------main------------------------------------------------------------------
(defun regex(expression)
    (combine-last (start (paral expression) 0))
)

(print (regex '(#\a + #\b \| #\a #\b * #\a)))
; (print (determinate (regex '(#\a + #\b \| #\a #\b * #\a))))
(print (search-set '0 '#\a (regex '(#\a + #\b \| #\a #\b * #\a))))

; (print (regex '(#\a #\b + #\a * #\b \| #\a #\b + #\a + #\b + #\b)))
