
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
extern getCloneFunction
extern getDeleteFunction
extern intClone
extern listNew
extern listDelete
extern listClone
extern listAddFirst

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
    push rbp
    mov rbp, rsp

    movzx eax, byte [rdi + 4] ; Mueve un valor de 8 bits a eax y extiende a 32 bits con ceros

    pop rbp
    ret
ret

; void arrayAddLast(array_t* a, void* data)
arrayAddLast:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov rcx, [rdi + 4]
    cmp [rdi + 5], cl
    je .fin

    mov r12, rdi
    mov r13, rsi

    mov rdi, [r12]
    call getCloneFunction

    mov rdi, r13
    call rax

    mov rcx, [r12 + 8]
    xor rdx, rdx

    .loop :
        cmp dword [rcx + 8*rdx], 0
        je .finloop
        inc rdx
        jmp .loop
    .finloop: 

    mov [rcx + 8*rdx], rax

    inc byte [r12 + 4]

    .fin:

    pop r13
    pop r12
    pop rbp
ret

; void* arrayGet(array_t* a, uint8_t i)
arrayGet:
    push rbp
    mov rbp, rsp

    ; Verificar si i está fuera de rango (i >= size)
    movzx rcx, byte [rdi + 4] ; Mover el tamaño del array (size) a rcx y extenderlo a 64 bits
    cmp rsi, rcx              ; Comparar el índice i (rsi) con el tamaño del array (rcx)
    jae .fueraRango           ; Saltar a .fueraRango si i >= size

    ; Obtener el puntero al array de datos
    mov rcx, [rdi + 8]        ; Mover el puntero al array de datos a rcx

    ; Obtener el elemento del array en la posición i
    mov rax, [rcx + rsi*8]    ; Mover el elemento en la posición i a rax

    jmp .fin                  ; Saltar a .fin

    .fueraRango:
        xor rax, rax              ; Establecer rax a 0 (NULL) si fuera de rango

    .fin:
        pop rbp
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

    xor rcx, rcx
    .loop:
        cmp rcx, r13
        je .fin
        mov rdx, [r14 + 8]
        mov qword [rdx + 8*rcx], 0
        inc rcx
        jmp .loop
    .fin:

    mov rax, r14

    add rsp, 8
    pop r14
    pop r13
    pop r12
    pop rbp
ret

; void* arrayRemove(array_t* a, uint8_t i)
arrayRemove:
    push rbp
    mov rbp, rsp

    cmp byte [rdi + 5], sil
    jle .fueraRango

    mov rdx, [rdi + 8]
    mov qword rcx, [rdx + 8*rsi]
    mov qword [rdx + 8*rsi], 0
    dec byte [rdi + 4]
    jmp .fin
    
    .fueraRango:
        xor rcx, rcx

    .fin: 
        mov rax, rcx  

    pop rbp
ret

; void arraySwap(array_t* a, uint8_t i, uint8_t j)
arraySwap:
ret

; void arrayDelete(array_t* a) {
arrayDelete:
    push rbp
    mov rbp, rsp
    push r12 
    push r13 
  
    xor r13, r13
    xor r12, r12
    xor rcx, rcx

    mov r13, rdi 
    call getDeleteFunction

    mov rdi, [r13 + 8]

    .loop :
        cmp qword [rdi + 8*rcx], 0
        je .finloop
        mov [rdi + 8*rcx], rax
        inc rcx
        jmp .loop
    .finloop: 
    
    ;en el loop solo elimino a lo que apunta cada posicion del array osea el contenido, 
    ;con el call free me aseguro de eliminar el array cada posicion suceciva donde almacenaba los datos

    call free  ; Liberar la memoria del array

    mov dword [r13 + 4], 0  ; Restablecer size
    mov dword [r13 + 5], 0  ; Restablecer capacity

    pop r13
    pop r12
    pop rbp
ret

;void arrayPrint(array_t* a, FILE* pFile)
arrayPrint:
ret

; ** Card **

; card_t* cardNew(char* suit, int32_t* number)
cardNew:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    sub rsp, 8

    mov r12, rdi
    mov r13, rsi

    mov rdi, 24
    call malloc   ;rax guarda el puntero que tiene 24 bytes de espacio, puntero a la estructura array
    mov r14, rax

    mov rdi, r12  ;muevo a rdi el registro r12 strClone(suit)
    call strClone
    mov qword [r14], rax

    mov rdi, r13
    call intClone
    mov qword [r14 + 8], rax

    mov rdi, 3
    call listNew
    mov qword [r14 + 16], rax

    mov rax, r14

    add rsp, 8
    pop r14
    pop r13
    pop r12
    pop rbp
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
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, rdi

    mov qword rdi, [r12]
    mov qword rsi, [r12 + 8]
    call cardNew
    mov r13, rax

    mov qword rdi, [r13 + 16]
    call listDelete

    mov qword rdi, [r12 + 16]
    call listClone
    mov qword [r13 + 16], rax

    mov rax, r13

    pop r13
    pop r12
    pop rbp
ret

;void cardAddStacked(card_t* c, card_t* card)
cardAddStacked:
    push rbp
    mov rbp, rsp
    push r12

    mov r12, rdi

    mov rdi, [r12 + 16]
    call listAddFirst 

    pop r12
    pop rbp
ret

;void cardDelete(card_t* c)
cardDelete:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, rdi

    mov rdi, 2
    call getDeleteFunction
    mov qword rdi, [r12]
    call rax

    mov rdi, 1
    call getDeleteFunction
    mov qword rdi, [r12 + 8]
    call rax

    mov qword rdi, [r12 + 16]
    call listDelete

    mov rdi, r12
    call free

    pop r13
    pop r12
    pop rbp
ret

