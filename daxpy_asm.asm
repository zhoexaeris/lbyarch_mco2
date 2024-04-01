section .text
bits 64
default rel

global daxpy_asm
extern printf
daxpy_asm:
    
    ; initialize the stack frame
    push rsi        
    push rbp    
    mov rbp, rsp    
    add rbp, 24                     ; add rbp, (16 and 8)
    xor rbx, rbx
    mov rsi, [rbp+32]
    
    ; xmm1 = A
    ; r8 = pointer to X
    ; r9 = pointer to Y
    ; rdi = ith element     

daxpy_loop: 

    cmp rbx, 10                     ; If rbx == 10, then end the program
    je daxpy_end

    movsd xmm10, [r8+rdi*8]         ; Initialize X[i] as xmm10
    mulsd xmm10, xmm1               ; A*X[i]
                
    movsd xmm11, [r9+rdi*8]         ; Initialize Y[i] as xmm11
    addsd xmm10, xmm11              ; A*X[i] + Y[i]
    
    movsd xmm0, xmm10               ; Move the resul (Z) to xmm0 (return)

    inc rbx
    jmp daxpy_loop

daxpy_end:  
    
    pop rbp
    pop rsi
    ret