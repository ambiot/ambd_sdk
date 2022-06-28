
/cygdrive/e/0code/v03slave/submit/project/realtek_amebaD_va0_example/GCC-RELEASE/project_lp/asdk/image/target_rom2.axf:     file format elf32-littlearm


Disassembly of section .rom2.text:

0000f000 <BOOT_ROM_KM0_Patch>:
    f000:	f641 4220 	movw	r2, #7200	; 0x1c20
    f004:	f641 4020 	movw	r0, #7200	; 0x1c20
    f008:	f246 63ad 	movw	r3, #26285	; 0x66ad
    f00c:	f2c0 0008 	movt	r0, #8
    f010:	f2c0 0208 	movt	r2, #8
    f014:	b570      	push	{r4, r5, r6, lr}
    f016:	1a12      	subs	r2, r2, r0
    f018:	2100      	movs	r1, #0
    f01a:	f2c0 0300 	movt	r3, #0
    f01e:	4798      	blx	r3
    f020:	f641 4220 	movw	r2, #7200	; 0x1c20
    f024:	f641 4020 	movw	r0, #7200	; 0x1c20
    f028:	f24f 6140 	movw	r1, #63040	; 0xf640
    f02c:	f246 5391 	movw	r3, #26001	; 0x6591
    f030:	f2c0 0008 	movt	r0, #8
    f034:	f2c0 0208 	movt	r2, #8
    f038:	f2c0 0300 	movt	r3, #0
    f03c:	1a12      	subs	r2, r2, r0
    f03e:	f2c0 0100 	movt	r1, #0
    f042:	4798      	blx	r3
    f044:	f644 7409 	movw	r4, #20233	; 0x4f09
    f048:	f240 1100 	movw	r1, #256	; 0x100
    f04c:	f240 1000 	movw	r0, #256	; 0x100
    f050:	f2c0 0400 	movt	r4, #0
    f054:	2200      	movs	r2, #0
    f056:	f2c4 0100 	movt	r1, #16384	; 0x4000
    f05a:	f2c8 0000 	movt	r0, #32768	; 0x8000
    f05e:	47a0      	blx	r4
    f060:	2101      	movs	r1, #1
    f062:	2001      	movs	r0, #1
    f064:	2201      	movs	r2, #1
    f066:	f2c4 0100 	movt	r1, #16384	; 0x4000
    f06a:	f2c8 0000 	movt	r0, #32768	; 0x8000
    f06e:	47a0      	blx	r4
    f070:	f240 2398 	movw	r3, #664	; 0x298
    f074:	2601      	movs	r6, #1
    f076:	f240 1100 	movw	r1, #256	; 0x100
    f07a:	f240 1000 	movw	r0, #256	; 0x100
    f07e:	f6c4 0300 	movt	r3, #18432	; 0x4800
    f082:	681a      	ldr	r2, [r3, #0]
    f084:	f2c4 0100 	movt	r1, #16384	; 0x4000
    f088:	4332      	orrs	r2, r6
    f08a:	601a      	str	r2, [r3, #0]
    f08c:	f2c8 0000 	movt	r0, #32768	; 0x8000
    f090:	2201      	movs	r2, #1
    f092:	47a0      	blx	r4
    f094:	2140      	movs	r1, #64	; 0x40
    f096:	2000      	movs	r0, #0
    f098:	2201      	movs	r2, #1
    f09a:	f2c8 0100 	movt	r1, #32768	; 0x8000
    f09e:	f2c4 0040 	movt	r0, #16448	; 0x4040
    f0a2:	2528      	movs	r5, #40	; 0x28
    f0a4:	47a0      	blx	r4
    f0a6:	f000 f8e5 	bl	f274 <app_gen_random_seed_rom>
    f0aa:	2300      	movs	r3, #0
    f0ac:	f24f 40e0 	movw	r0, #62688	; 0xf4e0
    f0b0:	f6c4 0500 	movt	r5, #18432	; 0x4800
    f0b4:	602b      	str	r3, [r5, #0]
    f0b6:	f2c0 0000 	movt	r0, #0
    f0ba:	f7f5 f99d 	bl	43f8 <UART_WaitBusy+0x23>
    f0be:	f240 33f8 	movw	r3, #1016	; 0x3f8
    f0c2:	2280      	movs	r2, #128	; 0x80
    f0c4:	f24f 30d0 	movw	r0, #62416	; 0xf3d0
    f0c8:	f6c4 0300 	movt	r3, #18432	; 0x4800
    f0cc:	6819      	ldr	r1, [r3, #0]
    f0ce:	0492      	lsls	r2, r2, #18
    f0d0:	430a      	orrs	r2, r1
    f0d2:	601a      	str	r2, [r3, #0]
    f0d4:	f2c0 0000 	movt	r0, #0
    f0d8:	f7f5 f98e 	bl	43f8 <UART_WaitBusy+0x23>
    f0dc:	682b      	ldr	r3, [r5, #0]
    f0de:	421e      	tst	r6, r3
    f0e0:	d111      	bne.n	f106 <BOOT_ROM_KM0_Patch+0x106>
    f0e2:	f241 5405 	movw	r4, #5381	; 0x1505
    f0e6:	682b      	ldr	r3, [r5, #0]
    f0e8:	f2c0 0400 	movt	r4, #0
    f0ec:	079b      	lsls	r3, r3, #30
    f0ee:	d449      	bmi.n	f184 <BOOT_ROM_KM0_Patch+0x184>
    f0f0:	2601      	movs	r6, #1
    f0f2:	e002      	b.n	f0fa <BOOT_ROM_KM0_Patch+0xfa>
    f0f4:	682b      	ldr	r3, [r5, #0]
    f0f6:	079b      	lsls	r3, r3, #30
    f0f8:	d444      	bmi.n	f184 <BOOT_ROM_KM0_Patch+0x184>
    f0fa:	2002      	movs	r0, #2
    f0fc:	47a0      	blx	r4
    f0fe:	682b      	ldr	r3, [r5, #0]
    f100:	421e      	tst	r6, r3
    f102:	d0f7      	beq.n	f0f4 <BOOT_ROM_KM0_Patch+0xf4>
    f104:	e003      	b.n	f10e <BOOT_ROM_KM0_Patch+0x10e>
    f106:	f241 5405 	movw	r4, #5381	; 0x1505
    f10a:	f2c0 0400 	movt	r4, #0
    f10e:	f242 0500 	movw	r5, #8192	; 0x2000
    f112:	2320      	movs	r3, #32
    f114:	f2c0 0508 	movt	r5, #8
    f118:	5ceb      	ldrb	r3, [r5, r3]
    f11a:	2b23      	cmp	r3, #35	; 0x23
    f11c:	d115      	bne.n	f14a <BOOT_ROM_KM0_Patch+0x14a>
    f11e:	f24f 32c8 	movw	r2, #62408	; 0xf3c8
    f122:	3b22      	subs	r3, #34	; 0x22
    f124:	2179      	movs	r1, #121	; 0x79
    f126:	f2c0 0200 	movt	r2, #0
    f12a:	e003      	b.n	f134 <BOOT_ROM_KM0_Patch+0x134>
    f12c:	3301      	adds	r3, #1
    f12e:	5cd1      	ldrb	r1, [r2, r3]
    f130:	29ff      	cmp	r1, #255	; 0xff
    f132:	d03a      	beq.n	f1aa <BOOT_ROM_KM0_Patch+0x1aa>
    f134:	f242 0600 	movw	r6, #8192	; 0x2000
    f138:	0018      	movs	r0, r3
    f13a:	f2c0 0608 	movt	r6, #8
    f13e:	46b4      	mov	ip, r6
    f140:	3020      	adds	r0, #32
    f142:	4460      	add	r0, ip
    f144:	7800      	ldrb	r0, [r0, #0]
    f146:	4288      	cmp	r0, r1
    f148:	d0f0      	beq.n	f12c <BOOT_ROM_KM0_Patch+0x12c>
    f14a:	f240 15cc 	movw	r5, #460	; 0x1cc
    f14e:	f2c0 0508 	movt	r5, #8
    f152:	682b      	ldr	r3, [r5, #0]
    f154:	039a      	lsls	r2, r3, #14
    f156:	d506      	bpl.n	f166 <BOOT_ROM_KM0_Patch+0x166>
    f158:	f24f 50a0 	movw	r0, #62880	; 0xf5a0
    f15c:	f2c0 0000 	movt	r0, #0
    f160:	f7f1 f988 	bl	474 <DiagVSprintf+0x35f>
    f164:	682b      	ldr	r3, [r5, #0]
    f166:	2680      	movs	r6, #128	; 0x80
    f168:	02b6      	lsls	r6, r6, #10
    f16a:	e002      	b.n	f172 <BOOT_ROM_KM0_Patch+0x172>
    f16c:	2064      	movs	r0, #100	; 0x64
    f16e:	47a0      	blx	r4
    f170:	682b      	ldr	r3, [r5, #0]
    f172:	4233      	tst	r3, r6
    f174:	d0fa      	beq.n	f16c <BOOT_ROM_KM0_Patch+0x16c>
    f176:	f24f 50c4 	movw	r0, #62916	; 0xf5c4
    f17a:	f2c0 0000 	movt	r0, #0
    f17e:	f7f1 f979 	bl	474 <DiagVSprintf+0x35f>
    f182:	e7f3      	b.n	f16c <BOOT_ROM_KM0_Patch+0x16c>
    f184:	f240 15cc 	movw	r5, #460	; 0x1cc
    f188:	2680      	movs	r6, #128	; 0x80
    f18a:	f2c0 0508 	movt	r5, #8
    f18e:	02b6      	lsls	r6, r6, #10
    f190:	f240 30e8 	movw	r0, #1000	; 0x3e8
    f194:	47a0      	blx	r4
    f196:	682b      	ldr	r3, [r5, #0]
    f198:	4233      	tst	r3, r6
    f19a:	d0f9      	beq.n	f190 <BOOT_ROM_KM0_Patch+0x190>
    f19c:	f24f 6014 	movw	r0, #62996	; 0xf614
    f1a0:	f2c0 0000 	movt	r0, #0
    f1a4:	f7f1 f966 	bl	474 <DiagVSprintf+0x35f>
    f1a8:	e7f2      	b.n	f190 <BOOT_ROM_KM0_Patch+0x190>
    f1aa:	f240 13cc 	movw	r3, #460	; 0x1cc
    f1ae:	f2c0 0308 	movt	r3, #8
    f1b2:	681b      	ldr	r3, [r3, #0]
    f1b4:	039b      	lsls	r3, r3, #14
    f1b6:	d519      	bpl.n	f1ec <BOOT_ROM_KM0_Patch+0x1ec>
    f1b8:	f24f 6000 	movw	r0, #62976	; 0xf600
    f1bc:	786b      	ldrb	r3, [r5, #1]
    f1be:	782a      	ldrb	r2, [r5, #0]
    f1c0:	021b      	lsls	r3, r3, #8
    f1c2:	4313      	orrs	r3, r2
    f1c4:	78aa      	ldrb	r2, [r5, #2]
    f1c6:	7d29      	ldrb	r1, [r5, #20]
    f1c8:	0412      	lsls	r2, r2, #16
    f1ca:	4313      	orrs	r3, r2
    f1cc:	78ea      	ldrb	r2, [r5, #3]
    f1ce:	f2c0 0000 	movt	r0, #0
    f1d2:	0612      	lsls	r2, r2, #24
    f1d4:	431a      	orrs	r2, r3
    f1d6:	7d6b      	ldrb	r3, [r5, #21]
    f1d8:	021b      	lsls	r3, r3, #8
    f1da:	430b      	orrs	r3, r1
    f1dc:	7da9      	ldrb	r1, [r5, #22]
    f1de:	0409      	lsls	r1, r1, #16
    f1e0:	430b      	orrs	r3, r1
    f1e2:	7de9      	ldrb	r1, [r5, #23]
    f1e4:	0609      	lsls	r1, r1, #24
    f1e6:	4319      	orrs	r1, r3
    f1e8:	f7f1 f944 	bl	474 <DiagVSprintf+0x35f>
    f1ec:	7d6a      	ldrb	r2, [r5, #21]
    f1ee:	7d2b      	ldrb	r3, [r5, #20]
    f1f0:	0212      	lsls	r2, r2, #8
    f1f2:	431a      	orrs	r2, r3
    f1f4:	7dab      	ldrb	r3, [r5, #22]
    f1f6:	041b      	lsls	r3, r3, #16
    f1f8:	431a      	orrs	r2, r3
    f1fa:	7deb      	ldrb	r3, [r5, #23]
    f1fc:	061b      	lsls	r3, r3, #24
    f1fe:	4313      	orrs	r3, r2
    f200:	b10b      	cbz	r3, f206 <BOOT_ROM_KM0_Patch+0x206>
    f202:	4798      	blx	r3
    f204:	e7fe      	b.n	f204 <BOOT_ROM_KM0_Patch+0x204>
    f206:	786a      	ldrb	r2, [r5, #1]
    f208:	782b      	ldrb	r3, [r5, #0]
    f20a:	0212      	lsls	r2, r2, #8
    f20c:	431a      	orrs	r2, r3
    f20e:	78ab      	ldrb	r3, [r5, #2]
    f210:	041b      	lsls	r3, r3, #16
    f212:	431a      	orrs	r2, r3
    f214:	78eb      	ldrb	r3, [r5, #3]
    f216:	061b      	lsls	r3, r3, #24
    f218:	4313      	orrs	r3, r2
    f21a:	4798      	blx	r3
    f21c:	e7f2      	b.n	f204 <BOOT_ROM_KM0_Patch+0x204>
    f21e:	bf00      	nop

0000f220 <ADC_SWTrigCmd_rom>:
    f220:	f64c 0100 	movw	r1, #51200	; 0xc800
    f224:	23ac      	movs	r3, #172	; 0xac
    f226:	220c      	movs	r2, #12
    f228:	b510      	push	{r4, lr}
    f22a:	f6c4 0101 	movt	r1, #18433	; 0x4801
    f22e:	b082      	sub	sp, #8
    f230:	58cc      	ldr	r4, [r1, r3]
    f232:	ab01      	add	r3, sp, #4
    f234:	701a      	strb	r2, [r3, #0]
    f236:	3204      	adds	r2, #4
    f238:	705a      	strb	r2, [r3, #1]
    f23a:	3210      	adds	r2, #16
    f23c:	709a      	strb	r2, [r3, #2]
    f23e:	3220      	adds	r2, #32
    f240:	70da      	strb	r2, [r3, #3]
    f242:	b950      	cbnz	r0, f25a <ADC_SWTrigCmd_rom+0x3a>
    f244:	64c8      	str	r0, [r1, #76]	; 0x4c
    f246:	22ff      	movs	r2, #255	; 0xff
    f248:	4022      	ands	r2, r4
    f24a:	5c98      	ldrb	r0, [r3, r2]
    f24c:	f241 43c3 	movw	r3, #5315	; 0x14c3
    f250:	f2c0 0300 	movt	r3, #0
    f254:	4798      	blx	r3
    f256:	b002      	add	sp, #8
    f258:	bd10      	pop	{r4, pc}
    f25a:	3a3f      	subs	r2, #63	; 0x3f
    f25c:	64ca      	str	r2, [r1, #76]	; 0x4c
    f25e:	e7f2      	b.n	f246 <ADC_SWTrigCmd_rom+0x26>

0000f260 <ADC_Readable_rom>:
    f260:	f64c 0300 	movw	r3, #51200	; 0xc800
    f264:	2001      	movs	r0, #1
    f266:	f6c4 0301 	movt	r3, #18433	; 0x4801
    f26a:	6d5b      	ldr	r3, [r3, #84]	; 0x54
    f26c:	089b      	lsrs	r3, r3, #2
    f26e:	4398      	bics	r0, r3
    f270:	4770      	bx	lr
    f272:	bf00      	nop

0000f274 <app_gen_random_seed_rom>:
    f274:	f24c 0300 	movw	r3, #49152	; 0xc000
    f278:	f240 4104 	movw	r1, #1028	; 0x404
    f27c:	b5f0      	push	{r4, r5, r6, r7, lr}
    f27e:	46de      	mov	lr, fp
    f280:	464e      	mov	r6, r9
    f282:	4645      	mov	r5, r8
    f284:	4657      	mov	r7, sl
    f286:	f6c4 0301 	movt	r3, #18433	; 0x4801
    f28a:	585a      	ldr	r2, [r3, r1]
    f28c:	b5e0      	push	{r5, r6, r7, lr}
    f28e:	0010      	movs	r0, r2
    f290:	4691      	mov	r9, r2
    f292:	22c0      	movs	r2, #192	; 0xc0
    f294:	f64c 0500 	movw	r5, #51200	; 0xc800
    f298:	4302      	orrs	r2, r0
    f29a:	505a      	str	r2, [r3, r1]
    f29c:	f6c4 0501 	movt	r5, #18433	; 0x4801
    f2a0:	682b      	ldr	r3, [r5, #0]
    f2a2:	4a3f      	ldr	r2, [pc, #252]	; (f3a0 <app_gen_random_seed_rom+0x12c>)
    f2a4:	2101      	movs	r1, #1
    f2a6:	4013      	ands	r3, r2
    f2a8:	f64f 72ff 	movw	r2, #65535	; 0xffff
    f2ac:	602b      	str	r3, [r5, #0]
    f2ae:	2300      	movs	r3, #0
    f2b0:	f2c0 0207 	movt	r2, #7
    f2b4:	65ab      	str	r3, [r5, #88]	; 0x58
    f2b6:	662a      	str	r2, [r5, #96]	; 0x60
    f2b8:	22a8      	movs	r2, #168	; 0xa8
    f2ba:	50a9      	str	r1, [r5, r2]
    f2bc:	f240 7100 	movw	r1, #1792	; 0x700
    f2c0:	f240 0b00 	movw	fp, #0
    f2c4:	50ab      	str	r3, [r5, r2]
    f2c6:	3204      	adds	r2, #4
    f2c8:	50ab      	str	r3, [r5, r2]
    f2ca:	3aa4      	subs	r2, #164	; 0xa4
    f2cc:	602b      	str	r3, [r5, #0]
    f2ce:	606b      	str	r3, [r5, #4]
    f2d0:	63ea      	str	r2, [r5, #60]	; 0x3c
    f2d2:	3298      	adds	r2, #152	; 0x98
    f2d4:	642b      	str	r3, [r5, #64]	; 0x40
    f2d6:	666b      	str	r3, [r5, #100]	; 0x64
    f2d8:	66ab      	str	r3, [r5, #104]	; 0x68
    f2da:	50a9      	str	r1, [r5, r2]
    f2dc:	3210      	adds	r2, #16
    f2de:	50ab      	str	r3, [r5, r2]
    f2e0:	682b      	ldr	r3, [r5, #0]
    f2e2:	3251      	adds	r2, #81	; 0x51
    f2e4:	32ff      	adds	r2, #255	; 0xff
    f2e6:	4313      	orrs	r3, r2
    f2e8:	b083      	sub	sp, #12
    f2ea:	602b      	str	r3, [r5, #0]
    f2ec:	2604      	movs	r6, #4
    f2ee:	2700      	movs	r7, #0
    f2f0:	f240 0800 	movw	r8, #0
    f2f4:	f240 0a9c 	movw	sl, #156	; 0x9c
    f2f8:	2001      	movs	r0, #1
    f2fa:	f7ff ff91 	bl	f220 <ADC_SWTrigCmd_rom>
    f2fe:	6d6c      	ldr	r4, [r5, #84]	; 0x54
    f300:	4034      	ands	r4, r6
    f302:	2c00      	cmp	r4, #0
    f304:	d1fb      	bne.n	f2fe <app_gen_random_seed_rom+0x8a>
    f306:	2000      	movs	r0, #0
    f308:	f7ff ff8a 	bl	f220 <ADC_SWTrigCmd_rom>
    f30c:	4653      	mov	r3, sl
    f30e:	2201      	movs	r2, #1
    f310:	4641      	mov	r1, r8
    f312:	58eb      	ldr	r3, [r5, r3]
    f314:	f240 0c01 	movw	ip, #1
    f318:	4013      	ands	r3, r2
    f31a:	408b      	lsls	r3, r1
    f31c:	44e0      	add	r8, ip
    f31e:	431f      	orrs	r7, r3
    f320:	4643      	mov	r3, r8
    f322:	b2ff      	uxtb	r7, r7
    f324:	2b08      	cmp	r3, #8
    f326:	d1e7      	bne.n	f2f8 <app_gen_random_seed_rom+0x84>
    f328:	1e7b      	subs	r3, r7, #1
    f32a:	b2db      	uxtb	r3, r3
    f32c:	2bfd      	cmp	r3, #253	; 0xfd
    f32e:	d8de      	bhi.n	f2ee <app_gen_random_seed_rom+0x7a>
    f330:	466b      	mov	r3, sp
    f332:	4659      	mov	r1, fp
    f334:	3304      	adds	r3, #4
    f336:	44e3      	add	fp, ip
    f338:	545f      	strb	r7, [r3, r1]
    f33a:	465b      	mov	r3, fp
    f33c:	2b04      	cmp	r3, #4
    f33e:	d1d5      	bne.n	f2ec <app_gen_random_seed_rom+0x78>
    f340:	682b      	ldr	r3, [r5, #0]
    f342:	4917      	ldr	r1, [pc, #92]	; (f3a0 <app_gen_random_seed_rom+0x12c>)
    f344:	4648      	mov	r0, r9
    f346:	400b      	ands	r3, r1
    f348:	602b      	str	r3, [r5, #0]
    f34a:	23a8      	movs	r3, #168	; 0xa8
    f34c:	50ea      	str	r2, [r5, r3]
    f34e:	50ec      	str	r4, [r5, r3]
    f350:	f24c 0300 	movw	r3, #49152	; 0xc000
    f354:	f240 4104 	movw	r1, #1028	; 0x404
    f358:	f6c4 0301 	movt	r3, #18433	; 0x4801
    f35c:	5058      	str	r0, [r3, r1]
    f35e:	f240 13dc 	movw	r3, #476	; 0x1dc
    f362:	f2c0 0308 	movt	r3, #8
    f366:	601a      	str	r2, [r3, #0]
    f368:	466b      	mov	r3, sp
    f36a:	466a      	mov	r2, sp
    f36c:	795b      	ldrb	r3, [r3, #5]
    f36e:	7911      	ldrb	r1, [r2, #4]
    f370:	021b      	lsls	r3, r3, #8
    f372:	4319      	orrs	r1, r3
    f374:	f240 13e0 	movw	r3, #480	; 0x1e0
    f378:	f2c0 0308 	movt	r3, #8
    f37c:	6019      	str	r1, [r3, #0]
    f37e:	6059      	str	r1, [r3, #4]
    f380:	6099      	str	r1, [r3, #8]
    f382:	60d9      	str	r1, [r3, #12]
    f384:	f241 4311 	movw	r3, #5137	; 0x1411
    f388:	2006      	movs	r0, #6
    f38a:	f2c0 0300 	movt	r3, #0
    f38e:	4798      	blx	r3
    f390:	b003      	add	sp, #12
    f392:	bc3c      	pop	{r2, r3, r4, r5}
    f394:	4690      	mov	r8, r2
    f396:	4699      	mov	r9, r3
    f398:	46a2      	mov	sl, r4
    f39a:	46ab      	mov	fp, r5
    f39c:	bdf0      	pop	{r4, r5, r6, r7, pc}
    f39e:	bf00      	nop
    f3a0:	fffffdff 	.word	0xfffffdff

0000f3a4 <km4_boot_on>:
    f3a4:	f240 33f8 	movw	r3, #1016	; 0x3f8
    f3a8:	2280      	movs	r2, #128	; 0x80
    f3aa:	f24f 30d0 	movw	r0, #62416	; 0xf3d0
    f3ae:	b510      	push	{r4, lr}
    f3b0:	f6c4 0300 	movt	r3, #18432	; 0x4800
    f3b4:	6819      	ldr	r1, [r3, #0]
    f3b6:	0492      	lsls	r2, r2, #18
    f3b8:	430a      	orrs	r2, r1
    f3ba:	601a      	str	r2, [r3, #0]
    f3bc:	f2c0 0000 	movt	r0, #0
    f3c0:	f7f5 f81a 	bl	43f8 <UART_WaitBusy+0x23>
    f3c4:	bd10      	pop	{r4, pc}
    f3c6:	bf00      	nop

0000f3c8 <ROM_IMG1_VALID_PATTEN>:
    f3c8:	7923 8816 ffff ffff                         #y......

0000f3d0 <HSPWR_ON_SEQ>:
    f3d0:	021c 4800 ff01 ffff 0011 0000 0000 0000     ...H............
    f3e0:	0000 0000 ff08 ffff 0000 0000 0000 0000     ................
    f3f0:	0200 4800 ff01 ffff 0000 0000 0002 0000     ...H............
    f400:	0200 4800 ff01 ffff 0000 0000 0004 0000     ...H............
    f410:	0000 0000 ff03 ffff 0000 0000 00c8 0000     ................
    f420:	0200 4800 ff01 ffff 0000 0000 0008 0000     ...H............
    f430:	0200 4800 ff01 ffff 0000 0006 0000 0000     ...H............
    f440:	021c 4800 ff01 ffff 0000 0000 0001 0000     ...H............
    f450:	021c 4800 ff01 ffff 0000 0000 0010 0000     ...H............
    f460:	021c 4800 ff01 ffff 0000 01ff 0000 0101     ...H............
    f470:	021c 4800 ff01 ffff 0000 0000 000e 0000     ...H............
    f480:	021c 4800 ff01 ffff 0000 0e00 0000 0000     ...H............
    f490:	0b08 4800 ff01 ffff ffff ffff 0000 0000     ...H............
    f4a0:	0314 4800 ff01 ffff 0000 0000 0001 0000     ...H............
    f4b0:	0200 4000 ff01 ffff 0000 0000 0000 0002     ...@............
    f4c0:	0210 4000 ff01 ffff 0000 0000 0000 0002     ...@............
    f4d0:	ffff ffff ffff ffff 0000 0000 0000 0000     ................

0000f4e0 <SYSPLL_ON_SEQ>:
    f4e0:	0208 4800 ff01 ffff 0000 0000 0000 1000     ...H............
    f4f0:	0280 4800 ff01 ffff 0000 0000 0003 0000     ...H............
    f500:	0000 0000 ff03 ffff 0000 0000 0004 0000     ................
    f510:	0280 4800 ff01 ffff 0000 0000 0004 0000     ...H............
    f520:	02b0 4800 ff01 ffff 0000 0000 0000 8000     ...H............
    f530:	0000 0000 ff03 ffff 0000 0000 0004 0000     ................
    f540:	0264 4800 ff01 ffff 0000 2000 0000 0000     d..H....... ....
    f550:	02b0 4800 ff01 ffff 0000 0000 0000 6000     ...H...........`
    f560:	0200 4800 ff01 ffff 0000 0020 0000 0000     ...H...... .....
    f570:	03f4 4800 ff02 ffff 1000 0000 1000 0000     ...H............
    f580:	02b0 4800 ff01 ffff 0000 0000 0100 0000     ...H............
    f590:	ffff ffff ffff ffff 0000 0000 0000 0000     ................
    f5a0:	490d 616d 6567 2031 6156 696c 6164 6974     .Image1 Validati
    f5b0:	6e6f 4920 636e 726f 6572 7463 2120 2121     on Incorrect !!!
    f5c0:	000a 0000 500d 656c 7361 2065 6552 622d     .....Please Re-b
    f5d0:	6f6f 2074 6e61 2064 7274 2079 6761 6961     oot and try agai
    f5e0:	2c6e 6f20 2072 6572 622d 7275 206e 6874     n, or re-burn th
    f5f0:	2065 6c66 7361 2068 6d69 6761 0a65 0000     e flash image...
    f600:	490d 474d 2031 4e45 5254 5b59 7825 253a     .IMG1 ENTRY[%x:%
    f610:	5d78 000a 490d 474d 2031 4253 4f4f 2054     x]...IMG1 SBOOT 
    f620:	4146 4c49 000a 0000 0000 0000 0000 0000     FAIL............
	...
