; ---------------------------------make automate from regulare expression-------------------------------------------------------------
(defun makeauto(node1 symbol node2)
    (cond
        ((eq nil node2) (list node1 symbol))
        (T (list node1 symbol node2))
    )
)

(defun iteration (iter nodenum val)
    (cond
        ((null iter) (list (makeauto nodenum val (+ 1 nodenum))))
        ((eq '+ iter) (append (list (makeauto nodenum val nodenum)) (list (makeauto nodenum val (+ 1 nodenum)))))
        ((eq '* iter) (append (list (makeauto nodenum val nodenum)) (list (makeauto nodenum 'eps (+ 1 nodenum)))))
        (T nil)
    )
)

(defun listiter (iter nodenum val)
    (cond
        ((null iter) nil)
        ; ((eq '+ iter) (append (list makeauto nodenum val (getlastnode )) (list makeauto)))
    )
)

(defun ifchar(exp nodenum)
    (cond
        ((characterp (cadr exp)) (append (list (makeauto nodenum (car exp) (+ 1 nodenum))) (start (cdr exp) (+ 1 nodenum))))
        ((eq '\| (cadr exp)) (append (list (makeauto nodenum (car exp) (+ 1 nodenum))) (start (cddr exp) nodenum)))
        (T (append (iteration (cadr exp) nodenum (car exp)) (start (cddr exp) (+ 1 nodenum))))
    )
)

(defun ifcharinlist(exp nodenum)
    (cond
        ((characterp (cadr exp)) (append (list (makeauto nodenum (car exp) (+ 1 nodenum))) (iflist (cdr exp) (+ 1 nodenum))))
        ((eq '\| (cadr exp)) (append (list (makeauto nodenum (car exp) (+ 1 nodenum))) (iflist (cddr exp) nodenum)))
        (T (append (iteration (cadr exp) nodenum (car exp)) (iflist (cddr exp) (+ 1 nodenum))))
    )
)

(defun iflist (exp nodenum)
    (cond
        ((null exp) nil)
        ((listp (car exp)) (append (iflist (car exp) nodenum) (iflist (cdr exp) (+ nodenum 1))))
        ((characterp (car exp)) (ifcharinlist exp nodenum))
        (T (iflist (cdr exp) nodenum))
    )
)
(defun start (exp nodenum)
    (cond
        ((null exp) (list (makeauto nodenum 'eps nil)))
        ((listp (car exp)) (append (iflist (car exp) nodenum) (start (cdr exp) (+ nodenum 1))))
        ((characterp (car exp)) (ifchar exp nodenum))
        (T (start (cdr exp) nodenum))
    )
)

(defun regex(expression)
    (start expression 0)
)
; ------------------------------------determinate automate-----------------------------------------------------------------
(defun getvalue(automate)
    (cadr automate)
)
(defun getfirstnode(exp)
    (car exp)
)
(defun getlastnode(exp)
    (caddr exp)
)
(defun deleps(automate)
    (cond
        ((null (cdr automate)) (list (car automate)))
        (T (list (makeauto (getfirstnode (car automate)) (getvalue (cadr automate)) (getlastnode (cadr automate)))))
    )
)

(defun determinate (automate)
    (cond
        ((null automate) nil)
        ((eq 'eps (getvalue (car automate))) (append (deleps automate) (determinate (cddr automate))))
        (T (append (list (car automate)) (determinate (cdr automate))))
    )
)

; (print (regex '(#\a + \| #\a #\b (#\x \| #\y)*)))
; (print (regex '((#\a \| #\b) +)))
(print (regex '(#\a + #\b \| #\a #\b * #\a)))
(print (determinate (regex '(#\a + #\b \| #\a #\b * #\a))))
