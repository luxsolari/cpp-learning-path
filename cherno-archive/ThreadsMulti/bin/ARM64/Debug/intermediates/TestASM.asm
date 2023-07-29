; Listing generated by Microsoft (R) Optimizing Compiler Version 19.35.32215.0 

	TTL	D:\data\code\gaming-studio-practices\ThreadsMulti\bin\ARM64\Debug\intermediates\TestASM.obj
	;ARM64

	AREA	|.drectve|, DRECTVE

	EXPORT	|main|

	AREA	|.pdata|, PDATA
|$pdata$main| DCD |$LN6|
	DCD	0x800069
	;Flags[SingleProEpi] functionLength[104] RegF[0] RegI[0] H[0] frameChainReturn[UnChained] frameSize[16]
; Function compile flags: /Odtp
; File D:\data\code\gaming-studio-practices\ThreadsMulti\src\TestASM.cpp

	AREA	|.text$mn|, CODE, ARM64

|main|	PROC

; 3    : {

|$LN6|
	sub         sp,sp,#0x10

; 4    : 	int x {0}, y {0};	// x and y are initialized to 0. this are braced initialization. 

	mov         w8,#0
	str         w8,[sp,#4]
	mov         w8,#0
	str         w8,[sp,#8]

; 5    : 						// this kind of initialization is more efficient than the other kind of initialization.
; 6    : 						// it was introduced in C++11.
; 7    : 
; 8    : 	for (int i{0}; i < 100; i++)	// this is a for loop with braced initialization

	mov         w8,#0
	str         w8,[sp]
	b           |$LN4@main|
|$LN2@main|
	ldr         w8,[sp]
	add         w8,w8,#1
	str         w8,[sp]
|$LN4@main|
	ldr         w8,[sp]
	cmp         w8,#0x64
	bge         |$LN3@main|

; 9    : 	{
; 10   : 		x += i;

	ldr         w9,[sp,#4]
	ldr         w8,[sp]
	add         w8,w9,w8
	str         w8,[sp,#4]

; 11   : 		y += i;

	ldr         w9,[sp,#8]
	ldr         w8,[sp]
	add         w8,w9,w8
	str         w8,[sp,#8]

; 12   : 	}

	b           |$LN2@main|
|$LN3@main|

; 13   : 
; 14   : 	
; 15   : }

	mov         w0,#0
	add         sp,sp,#0x10
	ret

	ENDP  ; |main|

	END
