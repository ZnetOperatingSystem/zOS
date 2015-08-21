;
; Summary: inportb.asm
; *inportb implementation for libx86*
;
; Author:
;     Marcel Sondaar
;
; License:
;     Public Domain
;
 
SECTION .text
 
global inportb
 
;
; Function: inportb
; reads a byte from an x86 i/o port
;
; in:
;     - Stack(1) = port to access
;
; out:
;     Return = read value
;
 
inportb:    MOV DX, [ESP+1*4]           ; DX = stack(1)
            IN byte AL, DX              ; AL = result
            RET
