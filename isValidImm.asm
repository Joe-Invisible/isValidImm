CODE
isValidImm PROC
	MOV		RAX, 1
	MOV		R8D, 0
	MOV		EDX, ECX
	XOR		R9D, R9D		; rotation count
	CMP		ECX, 0FFH
	JB		done
rollagain:
	INC		R9D
	ROL		EDX, 2
	CMP		EDX, 0FFH
	JBE		done
	CMP		ECX, EDX
	JNE		rollagain
	CMOVE	EAX, R8D
done:
	SHL		R9D, 4			; align after isValid
	OR		EAX, R9D
	SHL		RDX, 8			; align after rotate
	OR		EAX, EDX
 	RET		
isValidImm ENDP
END