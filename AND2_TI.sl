(set-logic BV)

(define-fun Spec ((i00 Bool) (i01 Bool) (i02 Bool) (i10 Bool) (i11 Bool) (i12 Bool)) Bool
   (and (xor (xor i00 i01) i02) (xor (xor i10 i11) i12) ) 
)

(synth-fun Tree ((i0 Bool) (i1 Bool) (i2 Bool) (i3 Bool)) Bool
( ( Start Bool ((and d1 d1)
			  	(xor d1 d1)
				(not d1)
           	  	(or d1 d1) ) )
	(d1 Bool   ((and d2 d2)
			  	(xor d2 d2)
				(not d2)
           	  	(or d2 d2) ) )
	(d2 Bool   ((and d3 d3)
			  	(xor d3 d3)
				(not d3)
           	  	(or d3 d3) ) )
	(d3 Bool   (i0 i1 i2 i3) ) )
)


(declare-var i00 Bool)
(declare-var i01 Bool)
(declare-var i02 Bool)
(declare-var i10 Bool)
(declare-var i11 Bool)
(declare-var i12 Bool)

;; Pay attention to the order of input parameters
;; (i00 i01) = (i01 i02) = (i02 i00)
(constraint (= 	
				(Spec  i00 i01 i02 i10 i11 i12)
				(xor 
					( xor (Tree i00 i01 i10 i11) (Tree i02 i00 i12 i10) ) 
					( Tree i01 i02 i11 i12 ) 
				) 
			) 
)

(check-synth)
