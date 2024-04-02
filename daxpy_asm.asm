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
      
    mov rsi, [rbp+32]               ; rsi = Z
    xor rdi, rdi                    ; rdi = ith element 
    
    ; xmm1 = A
    ; r8 = pointer to X
    ; r9 = pointer to Y   

daxpy_loop: 

    cmp rdi, rcx                     ; If rdi == 10, then end the program
    je daxpy_end

    movsd xmm10, [r8+rdi*8]         ; Initialize X[i] as xmm10
    mulsd xmm10, xmm1               ; A*X[i]
                
    movsd xmm11, [r9+rdi*8]         ; Initialize Y[i] as xmm11
    addsd xmm10, xmm11              ; A*X[i] + Y[i]
    
    movsd [rsi+rdi*8], xmm10               ; Move the result (Z) to xmm0 (return)

    inc rdi
    jmp daxpy_loop

daxpy_end:  
    
    pop rbp
    pop rsi
    ret