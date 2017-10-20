#include"i8042.h"

.global _asm_handler

.data

make: .string "Makecode: 0x%X\n"
break: .string "Breakcode: 0x%X\n"
maketb: .string "2 Bytes Makecode: 0xE0%X\n"
breaktb: .string "2 Bytes Breakcode: 0xE0%X\n"

.text
_asm_handler:
                                    //#vai verificar se o elemento mais recente da stack é o TWO_BYTE, se não for, salta para onebyte
        movl 4(%esp), %edx
        in $OUT_BUF, %eax
        push %eax
        mov $TWO_BYTE, %cl
        cmp %dl, %cl
        jne onebyte

        xor %ecx, %ecx
        mov $BIT(7), %cl
        test %al, %cl
        jz tbmakecode
        xor %ecx, %ecx
        mov %al, %cl
        push %ecx
        push $breaktb
                                    //# a função só chega aqui se o scancode for um breakcode de 2 bytes
        call _printf
        jmp end

tbmakecode:
                                    //# se for um makecode de 2 bytes a função chega aqui e imprime "Makecode: 0xE0..."
                                    //# se não for, nunca chega aqui
        xor %ecx, %ecx
        mov %al, %cl
        push %ecx
        push $maketb
        call _printf
        jmp end

onebyte:
                                    //# se o scancode for o TWO_BYTE termina para depois ver o byte seguinte, mantendo TWO_BYTE na stack para fazer a verificação do inicio deste codigo
        mov $TWO_BYTE, %cl
        cmp %al, %cl
        je end
        mov $BIT(7), %cl
        test %al, %cl
        jz obmakecode
                                    //# se o scancode for breakcode de 1 byte mantem-se nesta etiqueta e imprime-o
                                    //# se for um makecode de 1 byte salta para obmakecode e imprime-o
        xor %ecx, %ecx
        mov %al, %cl
        push %ecx
        push $break
        call _printf
        jmp end

obmakecode:
                                    //# se for um makecode de 1 byte imprime e continua para o end, terminando a função
        xor %ecx, %ecx
        mov %al, %cl
        push %ecx
        push $make
        call _printf

end:
                                    //# tira o ecx da stack e copia o scancode para o eax para ser feito o retorno
                                    //# soma 8 ao esp para chegar ao ecx, tendo em conta os push que foram feitos
        add $8, %esp
        pop %ecx
       	xor %eax, %eax
        mov %cl, %al
        ret


.end _asm_handler
