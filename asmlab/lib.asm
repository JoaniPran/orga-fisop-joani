
global strClone
global strPrint
global strCmp
global strLen
global strDelete

global arrayNew
global arrayDelete
global arrayPrint
global arrayGetSize
global arrayAddLast
global arrayGet
global arrayRemove
global arraySwap

global cardCmp
global cardClone
global cardAddStacked
global cardDelete
global cardGetSuit
global cardGetNumber
global cardGetStacked
global cardPrint
global cardNew

section .data
null: db "NULL",0
formato: db "%s\n", 0

section .text
extern malloc
extern free
extern fprintf

; ** String **
;char* strClone(char* a);
strClone:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, rdi ;r12 guarda la misma direccion de memoria del char* a
    xor r13, r13 ;limpio r13, ahora r13 guarda 0

    .loop1:
        cmp byte [r12 + r13], 0
        je .fin1
        inc r13
        jmp .loop1
    .fin1:
        
    inc r13 ;rcx guarda la longitud del string
    mov rdi, r13
    call malloc ;ahora en rax tenemos el char* nuevo

    xor rcx, rcx

    .loop2:
        cmp rcx, r13
        je .fin2
        mov dl, [r12 + rcx]
        mov [rax + rcx], dl
        inc rcx
        jmp .loop2
    .fin2:

    pop r13
    pop r12
    pop rbp
ret

;void strPrint(char* a, FILE* pFile)
strPrint:
    push rbp
    mov rbp, rsp
    push r12
    sub rsp, 8

    mov r12, rdi
    mov r13, rsi

    cmp byte [rdi], 0
    je .fin

    mov rdi, rsi
    mov rsi, formato
    mov rdx, r12
    call fprintf
    jmp .final

    .fin:
    mov rdi, rsi
    mov rsi, formato
    mov rdx, null
    call fprintf

    .final:

    add rsp, 8
    pop r12
    pop rbp
ret

;uint32_t strLen(char* a);
strLen:
    push rbp
    mov rbp, rsp

    xor rcx, rcx

    .loop:
        cmp byte [rdi + rcx], 0
        je .fin
        inc rcx
        jmp .loop
    .fin:

    mov eax, ecx
    pop rbp
ret

;int32_t strCmp(char* a, char* b);
strCmp:
    push rbp
    mov rbp, rsp

    xor rcx, rcx
    xor rdx, rdx

    .loop:
        mov dl, [rdi + rcx]

        cmp dl, 0
        je .aVacio
        cmp byte [rsi + rcx], 0
        je .bVacio

        cmp dl, [rsi + rcx]
        jne .comparacion

        inc rcx
        jmp .loop
    
    .comparacion:
        cmp dl, [rsi + rcx]
        jl .aMenor
        jg .bMenor

    .aMenor:
        mov rax, 1
        jmp .fin

    .bMenor:
        mov rax, -1
        jmp .fin

    .aVacio:
        cmp dl, [rsi + rcx]
        je .abIguales

    .bVacio:
        jmp .bMenor
    
    .abIguales:
        mov rax, 0
        jmp .fin

    .fin:

    pop rbp
ret

;void strDelete(char* a);
strDelete:
    push rbp
    mov rbp, rsp

    call free

    pop rbp
ret


; ** Array **

; uint8_t arrayGetSize(array_t* a)
arrayGetSize:
ret

; void arrayAddLast(array_t* a, void* data)
arrayAddLast:
ret

; void* arrayGet(array_t* a, uint8_t i)
arrayGet:
ret

; array_t* arrayNew(type_t t, uint8_t capacity)
arrayNew:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    sub rsp, 8

    mov r12, rdi
    mov r13, rsi

    mov rdi, 16
    call malloc
    mov r14, rax

    mov dword [r14], r12d
    mov byte [r14 + 4], 0
    mov byte [r14 + 5], r13b

    mov rdi, 8
    imul rdi, r13
    call malloc

    mov [r14 + 8], rax

    mov rax, r14

    add rsp, 8
    pop r14
    pop r13
    pop r12
    pop rbp
ret

; void* arrayRemove(array_t* a, uint8_t i)
arrayRemove:
ret

; void arraySwap(array_t* a, uint8_t i, uint8_t j)
arraySwap:
ret

; void arrayDelete(array_t* a) {
arrayDelete:
ret

;void arrayPrint(array_t* a, FILE* pFile)
arrayPrint:
ret

; ** Card **

; card_t* cardNew(char* suit, int32_t* number)
cardNew:
ret

;char* cardGetSuit(card_t* c)
cardGetSuit:
ret

;int32_t* cardGetNumber(card_t* c)
cardGetNumber:
ret

;list_t* cardGetStacked(card_t* c)
cardGetStacked:
ret


;void cardPrint(card_t* c, FILE* pFile)
cardPrint:
ret


;int32_t cardCmp(card_t* a, card_t* b)
cardCmp:
ret

;card_t* cardClone(card_t* c)
cardClone:
ret

;void cardAddStacked(card_t* c, card_t* card)
cardAddStacked:
ret

;void cardDelete(card_t* c)
cardDelete:
ret

