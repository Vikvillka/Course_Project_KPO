.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/BVA_Lib.lib
ExitProcess PROTO : DWORD
_ConsoleWriteInt	PROTO : SDWORD
_ConsoleWriteHex	PROTO : SDWORD
iabs PROTO      :	  SDWORD
step PROTO    :   SDWORD,	 : SDWORD
output PROTO       :   SDWORD


.stack 4096
.const
	l0 SDWORD 4
	l1 SDWORD 6
	l2 SDWORD 1
	l3 SDWORD 0
	l4 BYTE '... func step ...', 0
	l5 SDWORD 2
	l6 BYTE '... summ 4 and 6 ...', 0
	l7 BYTE '... sub 4 and 6 ...', 0
	l8 BYTE '... func iabs ...', 0
	l9 BYTE '.. begin ..', 0
	l10 BYTE '.. later ..', 0
	l11 BYTE '... mul 4 and 6 ...', 0
	l12 BYTE '... summ hex ...', 0
	l13 SDWORD 10
	l14 SDWORD 31
	l15 BYTE '... AND 1 and 0 ...', 0
	l16 BYTE '... OR 1 and 0 ...', 0
	l17 BYTE '... NOT a ...', 0
	l18 BYTE ' ... func expression ...', 0
	l19 BYTE 'W', 0
	l20 BYTE '... Out symb ...', 0
	l21 BYTE '... If and else ...', 0
	l22 BYTE 'if true', 0
	l23 BYTE 'if zero bolshe', 0
	l24 BYTE 'if OR', 0
.data
	expresssummab			SDWORD 0
	expressionsm			SDWORD 0
	maina			SDWORD 0
	mainb			SDWORD 0
	mainc			SDWORD 0
	maind			SDWORD 0
	mainz			SDWORD 0
	mainone			SDWORD 0
	mainzero			SDWORD 0
	mainresult			SDWORD 0
	mainsa			SDWORD 0

.code
express PROC b: SDWORD, a: SDWORD
	push		a
	push		b
	;\/(ADD)+\/
	pop		eax
	pop		ebx
	ADD		eax, ebx
	push		eax
	;/\(ADD)+/\
	pop			expresssummab

	mov		eax, expresssummab
	ret
express ENDP

expression PROC b: SDWORD, a: SDWORD
	push		a
	push		a
	push		b
	call		express
	push		eax
	push		a
	push		b
	call		express
	push		eax
	;\/(ADD)+\/
	pop		eax
	pop		ebx
	ADD		eax, ebx
	push		eax
	;/\(ADD)+/\
	push		b
	push		a
	;\/(SUB)-\/
	pop		ebx
	pop		eax
	SUB		eax, ebx
	push		eax
	;/\SUB(-)/\
	;\/(ADD)+\/
	pop		eax
	pop		ebx
	ADD		eax, ebx
	push		eax
	;/\(ADD)+/\
	;\/(ADD)+\/
	pop		eax
	pop		ebx
	ADD		eax, ebx
	push		eax
	;/\(ADD)+/\
	push		b
	push		a
	;\/(MUL)*\/
	pop		eax
	pop		ebx
	MUL		ebx
	push		eax
	;/\(MUL)*/\
	;\/(SUB)-\/
	pop		ebx
	pop		eax
	SUB		eax, ebx
	push		eax
	;/\SUB(-)/\
	pop			expressionsm

	mov		eax, expressionsm
	ret
expression ENDP

main PROC
	push		l0
	pop			maina

	push		l1
	pop			mainb

	push		l2
	pop			mainone

	push		l3
	pop			mainzero

	push		offset l4
	call		output

	push		maina
	push		l5
	call		step
	push		eax
	pop			mainc

	push		mainc
	call		_ConsoleWriteInt
	push		offset l6
	call		output

	push		maina
	push		mainb
	;\/(ADD)+\/
	pop		eax
	pop		ebx
	ADD		eax, ebx
	push		eax
	;/\(ADD)+/\
	pop			mainc

	push		mainc
	call		_ConsoleWriteInt
	push		offset l7
	call		output

	push		maina
	push		mainb
	;\/(SUB)-\/
	pop		ebx
	pop		eax
	SUB		eax, ebx
	push		eax
	;/\SUB(-)/\
	pop			mainc

	push		mainc
	call		_ConsoleWriteInt
	push		offset l8
	call		output

	push		mainc
	call		iabs
	push		eax
	pop			maind

	push		offset l9
	call		output

	push		mainc
	call		_ConsoleWriteInt
	push		offset l10
	call		output

	push		maind
	call		_ConsoleWriteInt
	push		offset l11
	call		output

	push		mainb
	push		maina
	;\/(MUL)*\/
	pop		eax
	pop		ebx
	MUL		ebx
	push		eax
	;/\(MUL)*/\
	pop			mainc

	push		mainc
	call		_ConsoleWriteInt
	push		offset l12
	call		output

	push		l13
	pop			maina

	push		l14
	pop			mainb

	push		mainb
	push		maina
	;\/(ADD)+\/
	pop		eax
	pop		ebx
	ADD		eax, ebx
	push		eax
	;/\(ADD)+/\
	pop			mainc

	push		mainc
	call		_ConsoleWriteInt
	push		offset l15
	call		output

	push		mainzero
	push		mainone
	;\/AND(&)\/
	pop		eax
	pop		edx
	AND		eax, edx
	push		eax
	;/\AND(&)/\
	pop			mainz

	push		mainz
	call		_ConsoleWriteInt
	push		offset l16
	call		output

	push		mainzero
	push		mainone
	;\/(OR)|\/
	pop		eax
	pop		edx
	OR		eax, edx
	push		eax
	;/\(OR)|/\
	pop			mainz

	push		mainz
	call		_ConsoleWriteInt
	push		offset l17
	call		output

	push		maina
	push		l0
	;\/(INVERSE(NOT)):\/
	pop		eax
	NOT			eax
	push		eax
	;/\(INVERSE(NOT)):/\
	pop			mainz

	push		mainz
	call		_ConsoleWriteInt
	push		offset l18
	call		output

	push		l5
	push		l1
	call		expression
	push		eax
	pop			mainresult

	push		mainresult
	call		_ConsoleWriteInt
	push		offset l19
	pop			mainsa

	push		offset l20
	call		output

	push		mainsa
	call		output

	push		offset l21
	call		output

	push mainone
	pop eax
	test eax, eax
	jz skip_if_0
	push		offset l22
	call		output

	push mainzero
	push mainone
	pop ebx
	pop eax
	cmp eax, ebx
	jle skip_if_1
	push		offset l23
	call		output

skip_if_1:
	push mainzero
	push mainone
	pop ebx
	pop eax
	or eax, ebx
	test eax, eax
	jz skip_if_2
	push		offset l24
	call		output

skip_if_2:
skip_if_0:
	push		l3
	call		ExitProcess
main ENDP
end main
