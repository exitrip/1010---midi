;$NOMOD1
;#include <reg936.h>

NAME NOTOUCH

PGM_MTP EQU 0FF03H
SRST		EQU	8H
AUXR1		EQU	0A2H

?PR?no_touch?NOTOUCH	SEGMENT CODE
    PUBLIC no_touch
; void no_touch() {

RSEG    ?PR?no_touch?NOTOUCH

no_touch:
    clr EA
    mov R0, 0FFH
    mov @R0, 6H
    mov A, 02
    mov R5, 01
    mov R7, 03
    lcall PGM_MTP
	ORL	AUXR1,#SRST
;}
END
