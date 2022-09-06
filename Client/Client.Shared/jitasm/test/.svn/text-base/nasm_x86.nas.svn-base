section .text
;align	16

global	_nasm_test_mov_disp
_nasm_test_mov_disp:
	mov al, [1]
	mov cl, [1]
	mov ax, [1]
	mov cx, [1]
	mov eax, [1]
	mov ecx, [1]
	mov [1], al
	mov [1], cl
	mov [1], ax
	mov [1], cx
	mov [1], eax
	mov [1], ecx

global	_nasm_test_fma
_nasm_test_fma:
	vfmadd132pd xmm1, xmm3, xmm5
	vfmadd132pd xmm1, xmm3, oword [edi]
	vfmadd132pd ymm1, ymm3, ymm5
	vfmadd132pd ymm1, ymm3, yword [edi]
	vfmadd213pd xmm1, xmm3, xmm5
	vfmadd213pd xmm1, xmm3, oword [edi]
	vfmadd213pd ymm1, ymm3, ymm5
	vfmadd213pd ymm1, ymm3, yword [edi]
	vfmadd231pd xmm1, xmm3, xmm5
	vfmadd231pd xmm1, xmm3, oword [edi]
	vfmadd231pd ymm1, ymm3, ymm5
	vfmadd231pd ymm1, ymm3, yword [edi]
	vfmadd132ps xmm1, xmm3, xmm5
	vfmadd132ps xmm1, xmm3, oword [edi]
	vfmadd132ps ymm1, ymm3, ymm5
	vfmadd132ps ymm1, ymm3, yword [edi]
	vfmadd213ps xmm1, xmm3, xmm5
	vfmadd213ps xmm1, xmm3, oword [edi]
	vfmadd213ps ymm1, ymm3, ymm5
	vfmadd213ps ymm1, ymm3, yword [edi]
	vfmadd231ps xmm1, xmm3, xmm5
	vfmadd231ps xmm1, xmm3, oword [edi]
	vfmadd231ps ymm1, ymm3, ymm5
	vfmadd231ps ymm1, ymm3, yword [edi]
	vfmadd132sd xmm1, xmm3, xmm5
	vfmadd132sd xmm1, xmm3, [edi]
	vfmadd213sd xmm1, xmm3, xmm5
	vfmadd213sd xmm1, xmm3, [edi]
	vfmadd231sd xmm1, xmm3, xmm5
	vfmadd231sd xmm1, xmm3, [edi]
	vfmadd132ss xmm1, xmm3, xmm5
	vfmadd132ss xmm1, xmm3, [edi]
	vfmadd213ss xmm1, xmm3, xmm5
	vfmadd213ss xmm1, xmm3, [edi]
	vfmadd231ss xmm1, xmm3, xmm5
	vfmadd231ss xmm1, xmm3, [edi]
	vfmaddsub132pd xmm1, xmm3, xmm5
	vfmaddsub132pd xmm1, xmm3, oword [edi]
	vfmaddsub132pd ymm1, ymm3, ymm5
	vfmaddsub132pd ymm1, ymm3, yword [edi]
	vfmaddsub213pd xmm1, xmm3, xmm5
	vfmaddsub213pd xmm1, xmm3, oword [edi]
	vfmaddsub213pd ymm1, ymm3, ymm5
	vfmaddsub213pd ymm1, ymm3, yword [edi]
	vfmaddsub231pd xmm1, xmm3, xmm5
	vfmaddsub231pd xmm1, xmm3, oword [edi]
	vfmaddsub231pd ymm1, ymm3, ymm5
	vfmaddsub231pd ymm1, ymm3, yword [edi]
	vfmaddsub132ps xmm1, xmm3, xmm5
	vfmaddsub132ps xmm1, xmm3, oword [edi]
	vfmaddsub132ps ymm1, ymm3, ymm5
	vfmaddsub132ps ymm1, ymm3, yword [edi]
	vfmaddsub213ps xmm1, xmm3, xmm5
	vfmaddsub213ps xmm1, xmm3, oword [edi]
	vfmaddsub213ps ymm1, ymm3, ymm5
	vfmaddsub213ps ymm1, ymm3, yword [edi]
	vfmaddsub231ps xmm1, xmm3, xmm5
	vfmaddsub231ps xmm1, xmm3, oword [edi]
	vfmaddsub231ps ymm1, ymm3, ymm5
	vfmaddsub231ps ymm1, ymm3, yword [edi]
	vfmsubadd132pd xmm1, xmm3, xmm5
	vfmsubadd132pd xmm1, xmm3, oword [edi]
	vfmsubadd132pd ymm1, ymm3, ymm5
	vfmsubadd132pd ymm1, ymm3, yword [edi]
	vfmsubadd213pd xmm1, xmm3, xmm5
	vfmsubadd213pd xmm1, xmm3, oword [edi]
	vfmsubadd213pd ymm1, ymm3, ymm5
	vfmsubadd213pd ymm1, ymm3, yword [edi]
	vfmsubadd231pd xmm1, xmm3, xmm5
	vfmsubadd231pd xmm1, xmm3, oword [edi]
	vfmsubadd231pd ymm1, ymm3, ymm5
	vfmsubadd231pd ymm1, ymm3, yword [edi]
	vfmsubadd132ps xmm1, xmm3, xmm5
	vfmsubadd132ps xmm1, xmm3, oword [edi]
	vfmsubadd132ps ymm1, ymm3, ymm5
	vfmsubadd132ps ymm1, ymm3, yword [edi]
	vfmsubadd213ps xmm1, xmm3, xmm5
	vfmsubadd213ps xmm1, xmm3, oword [edi]
	vfmsubadd213ps ymm1, ymm3, ymm5
	vfmsubadd213ps ymm1, ymm3, yword [edi]
	vfmsubadd231ps xmm1, xmm3, xmm5
	vfmsubadd231ps xmm1, xmm3, oword [edi]
	vfmsubadd231ps ymm1, ymm3, ymm5
	vfmsubadd231ps ymm1, ymm3, yword [edi]
	vfmsub132pd xmm1, xmm3, xmm5
	vfmsub132pd xmm1, xmm3, oword [edi]
	vfmsub132pd ymm1, ymm3, ymm5
	vfmsub132pd ymm1, ymm3, yword [edi]
	vfmsub213pd xmm1, xmm3, xmm5
	vfmsub213pd xmm1, xmm3, oword [edi]
	vfmsub213pd ymm1, ymm3, ymm5
	vfmsub213pd ymm1, ymm3, yword [edi]
	vfmsub231pd xmm1, xmm3, xmm5
	vfmsub231pd xmm1, xmm3, oword [edi]
	vfmsub231pd ymm1, ymm3, ymm5
	vfmsub231pd ymm1, ymm3, yword [edi]
	vfmsub132ps xmm1, xmm3, xmm5
	vfmsub132ps xmm1, xmm3, oword [edi]
	vfmsub132ps ymm1, ymm3, ymm5
	vfmsub132ps ymm1, ymm3, yword [edi]
	vfmsub213ps xmm1, xmm3, xmm5
	vfmsub213ps xmm1, xmm3, oword [edi]
	vfmsub213ps ymm1, ymm3, ymm5
	vfmsub213ps ymm1, ymm3, yword [edi]
	vfmsub231ps xmm1, xmm3, xmm5
	vfmsub231ps xmm1, xmm3, oword [edi]
	vfmsub231ps ymm1, ymm3, ymm5
	vfmsub231ps ymm1, ymm3, yword [edi]
	vfmsub132sd xmm1, xmm3, xmm5
	vfmsub132sd xmm1, xmm3, [edi]
	vfmsub213sd xmm1, xmm3, xmm5
	vfmsub213sd xmm1, xmm3, [edi]
	vfmsub231sd xmm1, xmm3, xmm5
	vfmsub231sd xmm1, xmm3, [edi]
	vfmsub132ss xmm1, xmm3, xmm5
	vfmsub132ss xmm1, xmm3, [edi]
	vfmsub213ss xmm1, xmm3, xmm5
	vfmsub213ss xmm1, xmm3, [edi]
	vfmsub231ss xmm1, xmm3, xmm5
	vfmsub231ss xmm1, xmm3, [edi]
	vfnmadd132pd xmm1, xmm3, xmm5
	vfnmadd132pd xmm1, xmm3, oword [edi]
	vfnmadd132pd ymm1, ymm3, ymm5
	vfnmadd132pd ymm1, ymm3, yword [edi]
	vfnmadd213pd xmm1, xmm3, xmm5
	vfnmadd213pd xmm1, xmm3, oword [edi]
	vfnmadd213pd ymm1, ymm3, ymm5
	vfnmadd213pd ymm1, ymm3, yword [edi]
	vfnmadd231pd xmm1, xmm3, xmm5
	vfnmadd231pd xmm1, xmm3, oword [edi]
	vfnmadd231pd ymm1, ymm3, ymm5
	vfnmadd231pd ymm1, ymm3, yword [edi]
	vfnmadd132ps xmm1, xmm3, xmm5
	vfnmadd132ps xmm1, xmm3, oword [edi]
	vfnmadd132ps ymm1, ymm3, ymm5
	vfnmadd132ps ymm1, ymm3, yword [edi]
	vfnmadd213ps xmm1, xmm3, xmm5
	vfnmadd213ps xmm1, xmm3, oword [edi]
	vfnmadd213ps ymm1, ymm3, ymm5
	vfnmadd213ps ymm1, ymm3, yword [edi]
	vfnmadd231ps xmm1, xmm3, xmm5
	vfnmadd231ps xmm1, xmm3, oword [edi]
	vfnmadd231ps ymm1, ymm3, ymm5
	vfnmadd231ps ymm1, ymm3, yword [edi]
	vfnmadd132sd xmm1, xmm3, xmm5
	vfnmadd132sd xmm1, xmm3, [edi]
	vfnmadd213sd xmm1, xmm3, xmm5
	vfnmadd213sd xmm1, xmm3, [edi]
	vfnmadd231sd xmm1, xmm3, xmm5
	vfnmadd231sd xmm1, xmm3, [edi]
	vfnmadd132ss xmm1, xmm3, xmm5
	vfnmadd132ss xmm1, xmm3, [edi]
	vfnmadd213ss xmm1, xmm3, xmm5
	vfnmadd213ss xmm1, xmm3, [edi]
	vfnmadd231ss xmm1, xmm3, xmm5
	vfnmadd231ss xmm1, xmm3, [edi]
	vfnmsub132pd xmm1, xmm3, xmm5
	vfnmsub132pd xmm1, xmm3, oword [edi]
	vfnmsub132pd ymm1, ymm3, ymm5
	vfnmsub132pd ymm1, ymm3, yword [edi]
	vfnmsub213pd xmm1, xmm3, xmm5
	vfnmsub213pd xmm1, xmm3, oword [edi]
	vfnmsub213pd ymm1, ymm3, ymm5
	vfnmsub213pd ymm1, ymm3, yword [edi]
	vfnmsub231pd xmm1, xmm3, xmm5
	vfnmsub231pd xmm1, xmm3, oword [edi]
	vfnmsub231pd ymm1, ymm3, ymm5
	vfnmsub231pd ymm1, ymm3, yword [edi]
	vfnmsub132ps xmm1, xmm3, xmm5
	vfnmsub132ps xmm1, xmm3, oword [edi]
	vfnmsub132ps ymm1, ymm3, ymm5
	vfnmsub132ps ymm1, ymm3, yword [edi]
	vfnmsub213ps xmm1, xmm3, xmm5
	vfnmsub213ps xmm1, xmm3, oword [edi]
	vfnmsub213ps ymm1, ymm3, ymm5
	vfnmsub213ps ymm1, ymm3, yword [edi]
	vfnmsub231ps xmm1, xmm3, xmm5
	vfnmsub231ps xmm1, xmm3, oword [edi]
	vfnmsub231ps ymm1, ymm3, ymm5
	vfnmsub231ps ymm1, ymm3, yword [edi]
	vfnmsub132sd xmm1, xmm3, xmm5
	vfnmsub132sd xmm1, xmm3, [edi]
	vfnmsub213sd xmm1, xmm3, xmm5
	vfnmsub213sd xmm1, xmm3, [edi]
	vfnmsub231sd xmm1, xmm3, xmm5
	vfnmsub231sd xmm1, xmm3, [edi]
	vfnmsub132ss xmm1, xmm3, xmm5
	vfnmsub132ss xmm1, xmm3, [edi]
	vfnmsub213ss xmm1, xmm3, xmm5
	vfnmsub213ss xmm1, xmm3, [edi]
	vfnmsub231ss xmm1, xmm3, xmm5
	vfnmsub231ss xmm1, xmm3, [edi]

global	_nasm_test_f16c
_nasm_test_f16c:
	;rdfsbase ecx
	;rdfsbase rcx
	;rdgsbase ecx
	;rdgsbase rcx
	rdrand cx
	rdrand ecx
	;rdrand rcx
	;wrfsbase ecx
	;wrfsbase rcx
	;wrgsbase ecx
	;wrgsbase rcx
	vcvtph2ps ymm1, xmm3
	vcvtph2ps ymm1, oword[edx]
	vcvtph2ps xmm1, xmm3
	vcvtph2ps xmm1, qword[edx]
	vcvtps2ph xmm1, ymm3, 5
	vcvtps2ph oword[edx], ymm3, 5
	vcvtps2ph xmm1, xmm3, 5
	vcvtps2ph qword[edx], xmm3, 5

global	_nasm_test_xop
_nasm_test_xop:
	vfrczpd xmm1, xmm3
	vfrczpd xmm1, oword [edx]
	vfrczpd ymm1, ymm3
	vfrczpd ymm1, yword [edx]
	vfrczps xmm1, xmm3
	vfrczps xmm1, oword [edx]
	vfrczps ymm1, ymm3
	vfrczps ymm1, yword [edx]
	vfrczsd xmm1, xmm3
	vfrczsd xmm1, qword [edx]
	vfrczss xmm1, xmm3
	vfrczss xmm1, dword [edx]
	vpcmov xmm1, xmm3, xmm5, xmm7
	vpcmov xmm1, xmm3, oword [esp], xmm7
	vpcmov xmm1, xmm3, xmm5, oword [esi]
	vpcmov ymm1, ymm3, ymm5, ymm7
	vpcmov ymm1, ymm3, yword [esp], ymm7
	vpcmov ymm1, ymm3, ymm5, yword [esi]
	vpcomb xmm1, xmm3, xmm5, 2
	vpcomb xmm1, xmm3, oword [esp], 2
	vpcomd xmm1, xmm3, xmm5, 2
	vpcomd xmm1, xmm3, oword [esp], 2
	vpcomq xmm1, xmm3, xmm5, 2
	vpcomq xmm1, xmm3, oword [esp], 2
	;vpcomub xmm1, xmm3, xmm5, 2
	;vpcomub xmm1, xmm3, oword [esp], 2 
	;vpcomud xmm1, xmm3, xmm5, 2
	;vpcomud xmm1, xmm3, oword [esp], 2
	;vpcomuq xmm1, xmm3, xmm5, 2
	;vpcomuq xmm1, xmm3, oword [esp], 2
	;vpcomuw xmm1, xmm3, xmm5, 2
	;vpcomuw xmm1, xmm3, oword [esp], 2
	;vpcomw xmm1, xmm3, xmm5, 2
	;vpcomw xmm1, xmm3, oword [esp], 2
	;vpermil2pd xmm1, xmm3, xmm5, xmm7
	;vpermil2pd xmm1, xmm3, oword [esp], xmm7
	;vpermil2pd xmm1, xmm3, xmm5, oword [esi]
	;vpermil2pd ymm1, ymm3, ymm5, ymm7
	;vpermil2pd ymm1, ymm3, yword [esp], ymm7
	;vpermil2pd ymm1, ymm3, ymm5, yword [esi]
	;vpermil2ps xmm1, xmm3, xmm5, xmm7
	;vpermil2ps xmm1, xmm3, oword [esp], xmm7
	;vpermil2ps xmm1, xmm3, xmm5, oword [esi]
	;vpermil2ps ymm1, ymm3, ymm5, ymm7
	;vpermil2ps ymm1, ymm3, yword [esp], ymm7
	;vpermil2ps ymm1, ymm3, ymm5, yword [esi]
	vphaddbd xmm1, xmm3
	vphaddbd xmm1, oword [edx]
	vphaddbq xmm1, xmm3
	vphaddbq xmm1, oword [edx]
	vphaddbw xmm1, xmm3
	vphaddbw xmm1, oword [edx]
	vphadddq xmm1, xmm3
	vphadddq xmm1, oword [edx]
	vphaddubd xmm1, xmm3
	vphaddubd xmm1, oword [edx]
	vphaddubq xmm1, xmm3
	vphaddubq xmm1, oword [edx]
	vphaddubw xmm1, xmm3
	vphaddubw xmm1, oword [edx]
	;vphaddudq xmm1, xmm3
	;vphaddudq xmm1, oword [edx]
	vphadduwd xmm1, xmm3
	vphadduwd xmm1, oword [edx]
	vphadduwq xmm1, xmm3
	vphadduwq xmm1, oword [edx]
	vphaddwd xmm1, xmm3
	vphaddwd xmm1, oword [edx]
	vphaddwq xmm1, xmm3
	vphaddwq xmm1, oword [edx]
	vphsubbw xmm1, xmm3
	vphsubbw xmm1, oword [edx]
	;vphsubdq xmm1, xmm3
	;vphsubdq xmm1, oword [edx]
	vphsubwd xmm1, xmm3
	vphsubwd xmm1, oword [edx]
	vpmacsdd xmm1, xmm3, xmm5, xmm7
	vpmacsdd xmm1, xmm3, oword [esp], xmm7
	vpmacsdqh xmm1, xmm3, xmm5, xmm7
	vpmacsdqh xmm1, xmm3, oword [esp], xmm7
	vpmacsdql xmm1, xmm3, xmm5, xmm7
	vpmacsdql xmm1, xmm3, oword [esp], xmm7
	vpmacssdd xmm1, xmm3, xmm5, xmm7
	vpmacssdd xmm1, xmm3, oword [esp], xmm7
	vpmacssdqh xmm1, xmm3, xmm5, xmm7
	vpmacssdqh xmm1, xmm3, oword [esp], xmm7
	vpmacssdql xmm1, xmm3, xmm5, xmm7
	vpmacssdql xmm1, xmm3, oword [esp], xmm7
	vpmacsswd xmm1, xmm3, xmm5, xmm7
	vpmacsswd xmm1, xmm3, oword [esp], xmm7
	vpmacssww xmm1, xmm3, xmm5, xmm7
	vpmacssww xmm1, xmm3, oword [esp], xmm7
	vpmacswd xmm1, xmm3, xmm5, xmm7
	vpmacswd xmm1, xmm3, oword [esp], xmm7
	vpmacsww xmm1, xmm3, xmm5, xmm7
	vpmacsww xmm1, xmm3, oword [esp], xmm7
	vpmadcsswd xmm1, xmm3, xmm5, xmm7
	vpmadcsswd xmm1, xmm3, oword [esp], xmm7
	vpmadcswd xmm1, xmm3, xmm5, xmm7
	vpmadcswd xmm1, xmm3, oword [esp], xmm7
	vpperm xmm1, xmm3, xmm5, xmm7
	vpperm xmm1, xmm3, oword [esp], xmm7
	vpperm xmm1, xmm3, xmm5, oword [esi]
	vprotb xmm1, xmm3, xmm5
	vprotb xmm1, oword [edx], xmm5
	vprotb xmm1, xmm3, oword [esp]
	vprotb xmm1, xmm3, 2
	vprotb xmm1, oword [edx], 2
	vprotd xmm1, xmm3, xmm5
	vprotd xmm1, oword [edx], xmm5
	vprotd xmm1, xmm3, oword [esp]
	vprotd xmm1, xmm3, 2
	vprotd xmm1, oword [edx], 2
	vprotq xmm1, xmm3, xmm5
	vprotq xmm1, oword [edx], xmm5
	vprotq xmm1, xmm3, oword [esp]
	vprotq xmm1, xmm3, 2
	vprotq xmm1, oword [edx], 2
	vprotw xmm1, xmm3, xmm5
	vprotw xmm1, oword [edx], xmm5
	vprotw xmm1, xmm3, oword [esp]
	vprotw xmm1, xmm3, 2
	vprotw xmm1, oword [edx], 2
	vpshab xmm1, xmm3, xmm5
	vpshab xmm1, oword [edx], xmm5
	vpshab xmm1, xmm3, oword [esp]
	vpshad xmm1, xmm3, xmm5
	vpshad xmm1, oword [edx], xmm5
	vpshad xmm1, xmm3, oword [esp]
	vpshaq xmm1, xmm3, xmm5
	vpshaq xmm1, oword [edx], xmm5
	vpshaq xmm1, xmm3, oword [esp]
	vpshaw xmm1, xmm3, xmm5
	vpshaw xmm1, oword [edx], xmm5
	vpshaw xmm1, xmm3, oword [esp]
	vpshlb xmm1, xmm3, xmm5
	vpshlb xmm1, oword [edx], xmm5
	vpshlb xmm1, xmm3, oword [esp]
	vpshld xmm1, xmm3, xmm5
	vpshld xmm1, oword [edx], xmm5
	vpshld xmm1, xmm3, oword [esp]
	vpshlq xmm1, xmm3, xmm5
	vpshlq xmm1, oword [edx], xmm5
	vpshlq xmm1, xmm3, oword [esp]
	vpshlw xmm1, xmm3, xmm5
	vpshlw xmm1, oword [edx], xmm5
	vpshlw xmm1, xmm3, oword [esp]

global	_nasm_test_fma4
_nasm_test_fma4:
	vfmaddpd xmm1, xmm3, xmm5, xmm7
	vfmaddpd xmm1, xmm3, oword [esp], xmm7
	vfmaddpd xmm1, xmm3, xmm5, oword [esi]
	vfmaddpd ymm1, ymm3, ymm5, ymm7
	vfmaddpd ymm1, ymm3, yword [esp], ymm7
	vfmaddpd ymm1, ymm3, ymm5, yword [esi]
	vfmaddps xmm1, xmm3, xmm5, xmm7
	vfmaddps xmm1, xmm3, oword [esp], xmm7
	vfmaddps xmm1, xmm3, xmm5, oword [esi]
	vfmaddps ymm1, ymm3, ymm5, ymm7
	vfmaddps ymm1, ymm3, yword [esp], ymm7
	vfmaddps ymm1, ymm3, ymm5, yword [esi]
	vfmaddsd xmm1, xmm3, xmm5, xmm7
	vfmaddsd xmm1, xmm3, qword [esp], xmm7
	vfmaddsd xmm1, xmm3, xmm5, qword [esi]
	vfmaddss xmm1, xmm3, xmm5, xmm7
	vfmaddss xmm1, xmm3, dword [esp], xmm7
	vfmaddss xmm1, xmm3, xmm5, dword [esi]
	vfmaddsubpd xmm1, xmm3, xmm5, xmm7
	vfmaddsubpd xmm1, xmm3, oword [esp], xmm7
	vfmaddsubpd xmm1, xmm3, xmm5, oword [esi]
	vfmaddsubpd ymm1, ymm3, ymm5, ymm7
	vfmaddsubpd ymm1, ymm3, yword [esp], ymm7
	vfmaddsubpd ymm1, ymm3, ymm5, yword [esi]
	vfmaddsubps xmm1, xmm3, xmm5, xmm7
	vfmaddsubps xmm1, xmm3, oword [esp], xmm7
	vfmaddsubps xmm1, xmm3, xmm5, oword [esi]
	vfmaddsubps ymm1, ymm3, ymm5, ymm7
	vfmaddsubps ymm1, ymm3, yword [esp], ymm7
	vfmaddsubps ymm1, ymm3, ymm5, yword [esi]
	vfmsubaddpd xmm1, xmm3, xmm5, xmm7
	vfmsubaddpd xmm1, xmm3, oword [esp], xmm7
	vfmsubaddpd xmm1, xmm3, xmm5, oword [esi]
	vfmsubaddpd ymm1, ymm3, ymm5, ymm7
	vfmsubaddpd ymm1, ymm3, yword [esp], ymm7
	vfmsubaddpd ymm1, ymm3, ymm5, yword [esi]
	vfmsubaddps xmm1, xmm3, xmm5, xmm7
	vfmsubaddps xmm1, xmm3, oword [esp], xmm7
	vfmsubaddps xmm1, xmm3, xmm5, oword [esi]
	vfmsubaddps ymm1, ymm3, ymm5, ymm7
	vfmsubaddps ymm1, ymm3, yword [esp], ymm7
	vfmsubaddps ymm1, ymm3, ymm5, yword [esi]
	vfmsubpd xmm1, xmm3, xmm5, xmm7
	vfmsubpd xmm1, xmm3, oword [esp], xmm7
	vfmsubpd xmm1, xmm3, xmm5, oword [esi]
	vfmsubpd ymm1, ymm3, ymm5, ymm7
	vfmsubpd ymm1, ymm3, yword [esp], ymm7
	vfmsubpd ymm1, ymm3, ymm5, yword [esi]
	vfmsubps xmm1, xmm3, xmm5, xmm7
	vfmsubps xmm1, xmm3, oword [esp], xmm7
	vfmsubps xmm1, xmm3, xmm5, oword [esi]
	vfmsubps ymm1, ymm3, ymm5, ymm7
	vfmsubps ymm1, ymm3, yword [esp], ymm7
	vfmsubps ymm1, ymm3, ymm5, yword [esi]
	vfmsubsd xmm1, xmm3, xmm5, xmm7
	vfmsubsd xmm1, xmm3, qword [esp], xmm7
	vfmsubsd xmm1, xmm3, xmm5, qword [esi]
	vfmsubss xmm1, xmm3, xmm5, xmm7
	vfmsubss xmm1, xmm3, dword [esp], xmm7
	vfmsubss xmm1, xmm3, xmm5, dword [esi]
	vfnmaddpd xmm1, xmm3, xmm5, xmm7
	vfnmaddpd xmm1, xmm3, oword [esp], xmm7
	vfnmaddpd xmm1, xmm3, xmm5, oword [esi]
	vfnmaddpd ymm1, ymm3, ymm5, ymm7
	vfnmaddpd ymm1, ymm3, yword [esp], ymm7
	vfnmaddpd ymm1, ymm3, ymm5, yword [esi]
	vfnmaddps xmm1, xmm3, xmm5, xmm7
	vfnmaddps xmm1, xmm3, oword [esp], xmm7
	vfnmaddps xmm1, xmm3, xmm5, oword [esi]
	vfnmaddps ymm1, ymm3, ymm5, ymm7
	vfnmaddps ymm1, ymm3, yword [esp], ymm7
	vfnmaddps ymm1, ymm3, ymm5, yword [esi]
	vfnmaddsd xmm1, xmm3, xmm5, xmm7
	vfnmaddsd xmm1, xmm3, qword [esp], xmm7
	vfnmaddsd xmm1, xmm3, xmm5, qword [esi]
	vfnmaddss xmm1, xmm3, xmm5, xmm7
	vfnmaddss xmm1, xmm3, dword [esp], xmm7
	vfnmaddss xmm1, xmm3, xmm5, dword [esi]
	vfnmsubpd xmm1, xmm3, xmm5, xmm7
	vfnmsubpd xmm1, xmm3, oword [esp], xmm7
	vfnmsubpd xmm1, xmm3, xmm5, oword [esi]
	vfnmsubpd ymm1, ymm3, ymm5, ymm7
	vfnmsubpd ymm1, ymm3, yword [esp], ymm7
	vfnmsubpd ymm1, ymm3, ymm5, yword [esi]
	vfnmsubps xmm1, xmm3, xmm5, xmm7
	vfnmsubps xmm1, xmm3, oword [esp], xmm7
	vfnmsubps xmm1, xmm3, xmm5, oword [esi]
	vfnmsubps ymm1, ymm3, ymm5, ymm7
	vfnmsubps ymm1, ymm3, yword [esp], ymm7
	vfnmsubps ymm1, ymm3, ymm5, yword [esi]
	vfnmsubsd xmm1, xmm3, xmm5, xmm7
	vfnmsubsd xmm1, xmm3, qword [esp], xmm7
	vfnmsubsd xmm1, xmm3, xmm5, qword [esi]
	vfnmsubss xmm1, xmm3, xmm5, xmm7
	vfnmsubss xmm1, xmm3, dword [esp], xmm7
	vfnmsubss xmm1, xmm3, xmm5, dword [esi]

global _nasm_test_bmi
_nasm_test_bmi:
	andn edi, ecx, eax
	andn edi, ecx, dword [eax]
	;andn rdi, rcx, rax
	;andn rdi, rcx, qword [rax]
	bextr edi, ecx, eax
	bextr edi, dword [ecx], eax
	;bextr rdi, rcx, rax
	;bextr rdi, qword [rcx], rax
	blsi edi, ecx
	blsi edi, dword [ecx]
	;blsi rdi, rcx
	;blsi rdi, qword [rcx]
	blsmsk edi, ecx
	blsmsk edi, dword [ecx]
	;blsmsk rdi, rcx
	;blsmsk rdi, qword [rcx]
	blsr edi, ecx
	blsr edi, dword [ecx]
	;blsr rdi, rcx
	;blsr rdi, qword [rcx]
	bzhi edi, ecx, eax
	bzhi edi, dword [ecx], eax
	;bzhi rdi, rcx, rax
	;bzhi rdi, qword [rcx], rax
;	lzcnt di, cx
;	lzcnt di, word [ecx]
	lzcnt edi, ecx
	lzcnt edi, dword [ecx]
	;lzcnt rdi, rcx
	;lzcnt rdi, qword [rcx]
	mulx edi, ecx, eax
	mulx edi, ecx, dword [eax]
	;mulx rdi, rcx, rax
	;mulx rdi, rcx, qword [rax]
	pdep edi, ecx, eax
	pdep edi, ecx, dword [eax]
	;pdep rdi, rcx, rax
	;pdep rdi, rcx, qword [rax]
	pext edi, ecx, eax
	pext edi, ecx, dword [eax]
	;pext rdi, rcx, rax
	;pext rdi, rcx, qword [rax]
	rorx edi, ecx, 1
	rorx edi, dword [ecx], 1
	;rorx rdi, rcx, 1
	;rorx rdi, qword [rcx], 1
	sarx edi, ecx, eax
	sarx edi, dword [ecx], eax
	;sarx rdi, rcx, rax
	;sarx rdi, qword [rcx], rax
	shlx edi, ecx, eax
	shlx edi, dword [ecx], eax
	;shlx rdi, rcx, rax
	;shlx rdi, qword [rcx], rax
	shrx edi, ecx, eax
	shrx edi, dword [ecx], eax
	;shrx rdi, rcx, rax
	;shrx rdi, qword [rcx], rax
;	tzcnt di, cx
;	tzcnt di, word [ecx]
	tzcnt edi, ecx
	tzcnt edi, dword [ecx]
	;tzcnt rdi, rcx
	;tzcnt rdi, qword [rcx]
	invpcid edi, oword [ecx]
	;invpcid rdi, oword [rcx]

global	_nasm_test_avx2_gather
_nasm_test_avx2_gather:
	vgatherdps xmm2, dword [ebp + xmm5 * 2 + 1], xmm3
	vgatherdps ymm5, dword [ebp + ymm5 * 2 + 1], ymm4
	vgatherqps xmm2, dword [ebp + xmm6 * 2 + 1], xmm3
	vgatherqps xmm2, dword [ebp + ymm6 * 2 + 1], xmm3
	vgatherdpd xmm2, qword [ebp + xmm5 * 2 + 1], xmm3
	vgatherdpd ymm5, qword [ebp + xmm5 * 2 + 1], ymm4
	vgatherqpd xmm2, qword [ebp + xmm6 * 2 + 1], xmm3
	vgatherqpd ymm5, qword [ebp + ymm6 * 2 + 1], ymm4
	vpgatherdd xmm2, dword [ebp + xmm5 * 2 + 1], xmm3
	vpgatherdd ymm5, dword [ebp + ymm5 * 2 + 1], ymm4
	vpgatherqd xmm2, dword [ebp + xmm6 * 2 + 1], xmm3
	vpgatherqd xmm2, dword [ebp + ymm6 * 2 + 1], xmm3
	vpgatherdq xmm2, qword [ebp + xmm5 * 2 + 1], xmm3
	vpgatherdq ymm5, qword [ebp + xmm5 * 2 + 1], ymm4
	vpgatherqq xmm2, qword [ebp + xmm6 * 2 + 1], xmm3
	vpgatherqq ymm5, qword [ebp + ymm6 * 2 + 1], ymm4

global	_nasm_test_regalloc_vsib
_nasm_test_regalloc_vsib:
	vpxor xmm3, xmm3, xmm3
	vgatherdps xmm0, dword [ebp + xmm3 * 2 + 1], xmm2
	vgatherqps xmm0, dword [ebp + xmm3 * 2 + 1], xmm2
	vxorps ymm2, ymm2, ymm2
	vgatherdps ymm1, dword [ebp + ymm2 * 2 + 1], ymm0
	vgatherqps xmm1, dword [ebp + ymm2 * 2 + 1], xmm0
