;$NOMOD1
;#include <reg936.h>

NAME NOTOUCH
;values
SRST		EQU	8H
;sfr
AUXR1		EQU	0A2H
TAMOD		EQU	8FH		;timer aux mode register
;code
BOOTLOADER	EQU 3F00H
PGM_MTP EQU 0FF03H

?PR?no_touch?NOTOUCH	SEGMENT CODE
    PUBLIC no_touch
; void no_touch() {

RSEG    ?PR?no_touch?NOTOUCH

no_touch:
    clr EA
	;ljmp BOOTLOADER
    mov R0, #0FFH
    mov @R0, #96H
    mov A, #02H
    mov R5, #01H
    mov R7, #03H
    lcall PGM_MTP
	mov	AUXR1,#SRST
;}
END
