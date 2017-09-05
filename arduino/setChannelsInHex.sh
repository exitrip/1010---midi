#!/usr/bin/env bash
if [ $# -eq 3 ] && [ $1 -ne $2 ]
then
    if [ $1 -lt 13 ] && [ $1 -gt 0 ] && [ $2 -lt 13 ] && [ $2 -gt 0 ]
    then
        checksum=$(( ( ( $1 + $2 - 2 ) ^ 0xff ) + 1 ))
        hexCmd=$(printf ":02100000%02X%02X%02X\n" "$(( $1 - 1 ))" "$(( $2 - 1 ))" "$checksum")
        line= `sed -n '/:[0-1]\([0-9]\|[A-F]\)100000/ =' $3`
        if [ -z ${line+x} ]
        then
            echo "target hexfile already has a value at address 0x1000"
        else
            line=`sed -n '/:[0-1]\([0-9]\|[A-F]\)100200/ =' $3`
            echo "inserting $hexCmd into $3 at line $line"
            sed -i "/:[0-1]\([0-9]\|[A-F]\)100200/i $hexCmd" $3
        fi
    else
        echo
        echo 'channel out of range'
        echo 'please enter TWO channels between 1 and 12'
        echo
    fi
else
    echo
    echo 'incorrect arguments'
    echo 'please enter TWO DIFFERENT channels between 1 and 12'
    echo 'followed by the target hex file to modify'
    echo 'ex: ./setChannelsInHex.sh 1 12 ../Blinky.hex'
    echo
fi
#EOF
