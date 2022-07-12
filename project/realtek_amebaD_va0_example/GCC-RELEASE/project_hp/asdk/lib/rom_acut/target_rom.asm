
/cygdrive/E/AmebaD/sdk/svn_new/project/realtek_amebaD_cm4_gcc_verification/asdk/image/target_rom.axf:     file format elf32-littlearm


Disassembly of section .rom.text:

10100000 <__vectors_table>:
10100000:	1007effc 	.word	0x1007effc
10100004:	10100101 	.word	0x10100101
10100008:	10100111 	.word	0x10100111
1010000c:	10100115 	.word	0x10100115
10100010:	10100119 	.word	0x10100119
10100014:	1010011d 	.word	0x1010011d
10100018:	10100121 	.word	0x10100121
1010001c:	10100125 	.word	0x10100125
	...

10100100 <Reset_Handler>:
10100100:	f8df 0024 	ldr.w	r0, [pc, #36]	; 10100128 <SecureFault_Handler+0x4>
10100104:	6801      	ldr	r1, [r0, #0]
10100106:	f441 0170 	orr.w	r1, r1, #15728640	; 0xf00000
1010010a:	6001      	str	r1, [r0, #0]
1010010c:	f004 b94c 	b.w	101043a8 <BOOT_ROM_ResetVsr>

10100110 <NMI_Handler>:
10100110:	f006 ba90 	b.w	10106634 <INT_NMI>

10100114 <HardFault_Handler>:
10100114:	f006 b856 	b.w	101061c4 <INT_HardFault>

10100118 <MemManage_Handler>:
10100118:	f006 b864 	b.w	101061e4 <INT_MemManage>

1010011c <BusFault_Handler>:
1010011c:	f006 b872 	b.w	10106204 <INT_BusFault>

10100120 <UsageFault_Handler>:
10100120:	f006 b880 	b.w	10106224 <INT_UsageFault>

10100124 <SecureFault_Handler>:
10100124:	f006 b88e 	b.w	10106244 <INT_SecureFault>
10100128:	e000ed88 	.word	0xe000ed88

1010012c <DiagVSprintf>:
1010012c:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10100130:	780b      	ldrb	r3, [r1, #0]
10100132:	b087      	sub	sp, #28
10100134:	4607      	mov	r7, r0
10100136:	2b00      	cmp	r3, #0
10100138:	f000 813e 	beq.w	101003b8 <DiagVSprintf+0x28c>
1010013c:	4605      	mov	r5, r0
1010013e:	460e      	mov	r6, r1
10100140:	4691      	mov	r9, r2
10100142:	f8df 82a8 	ldr.w	r8, [pc, #680]	; 101003ec <DiagVSprintf+0x2c0>
10100146:	4618      	mov	r0, r3
10100148:	e009      	b.n	1010015e <DiagVSprintf+0x32>
1010014a:	2f00      	cmp	r7, #0
1010014c:	f000 80cf 	beq.w	101002ee <DiagVSprintf+0x1c2>
10100150:	7028      	strb	r0, [r5, #0]
10100152:	3501      	adds	r5, #1
10100154:	7870      	ldrb	r0, [r6, #1]
10100156:	3601      	adds	r6, #1
10100158:	2800      	cmp	r0, #0
1010015a:	f000 8095 	beq.w	10100288 <DiagVSprintf+0x15c>
1010015e:	2825      	cmp	r0, #37	; 0x25
10100160:	d1f3      	bne.n	1010014a <DiagVSprintf+0x1e>
10100162:	7874      	ldrb	r4, [r6, #1]
10100164:	2c73      	cmp	r4, #115	; 0x73
10100166:	f106 0601 	add.w	r6, r6, #1
1010016a:	f000 8094 	beq.w	10100296 <DiagVSprintf+0x16a>
1010016e:	f8d9 0000 	ldr.w	r0, [r9]
10100172:	280f      	cmp	r0, #15
10100174:	dd6b      	ble.n	1010024e <DiagVSprintf+0x122>
10100176:	f1a0 0310 	sub.w	r3, r0, #16
1010017a:	2bef      	cmp	r3, #239	; 0xef
1010017c:	f240 80a0 	bls.w	101002c0 <DiagVSprintf+0x194>
10100180:	f5a0 7380 	sub.w	r3, r0, #256	; 0x100
10100184:	f5b3 6f70 	cmp.w	r3, #3840	; 0xf00
10100188:	f080 80a0 	bcs.w	101002cc <DiagVSprintf+0x1a0>
1010018c:	f1a4 0230 	sub.w	r2, r4, #48	; 0x30
10100190:	2a09      	cmp	r2, #9
10100192:	f04f 0308 	mov.w	r3, #8
10100196:	d85f      	bhi.n	10100258 <DiagVSprintf+0x12c>
10100198:	2300      	movs	r3, #0
1010019a:	eb03 0383 	add.w	r3, r3, r3, lsl #2
1010019e:	eb04 0243 	add.w	r2, r4, r3, lsl #1
101001a2:	f816 4f01 	ldrb.w	r4, [r6, #1]!
101001a6:	f1a4 0130 	sub.w	r1, r4, #48	; 0x30
101001aa:	2909      	cmp	r1, #9
101001ac:	f1a2 0330 	sub.w	r3, r2, #48	; 0x30
101001b0:	d9f3      	bls.n	1010019a <DiagVSprintf+0x6e>
101001b2:	f1a2 0331 	sub.w	r3, r2, #49	; 0x31
101001b6:	2c78      	cmp	r4, #120	; 0x78
101001b8:	ea4f 0383 	mov.w	r3, r3, lsl #2
101001bc:	d14e      	bne.n	1010025c <DiagVSprintf+0x130>
101001be:	f10d 0e04 	add.w	lr, sp, #4
101001c2:	46f3      	mov	fp, lr
101001c4:	f04f 0c20 	mov.w	ip, #32
101001c8:	f109 0904 	add.w	r9, r9, #4
101001cc:	2800      	cmp	r0, #0
101001ce:	f000 809b 	beq.w	10100308 <DiagVSprintf+0x1dc>
101001d2:	4602      	mov	r2, r0
101001d4:	2100      	movs	r1, #0
101001d6:	e000      	b.n	101001da <DiagVSprintf+0xae>
101001d8:	4621      	mov	r1, r4
101001da:	0912      	lsrs	r2, r2, #4
101001dc:	f101 0401 	add.w	r4, r1, #1
101001e0:	d1fa      	bne.n	101001d8 <DiagVSprintf+0xac>
101001e2:	008a      	lsls	r2, r1, #2
101001e4:	4293      	cmp	r3, r2
101001e6:	bfb8      	it	lt
101001e8:	4613      	movlt	r3, r2
101001ea:	2b00      	cmp	r3, #0
101001ec:	db14      	blt.n	10100218 <DiagVSprintf+0xec>
101001ee:	4619      	mov	r1, r3
101001f0:	fa4f fc8c 	sxtb.w	ip, ip
101001f4:	f10b 32ff 	add.w	r2, fp, #4294967295
101001f8:	fa20 f401 	lsr.w	r4, r0, r1
101001fc:	f004 040f 	and.w	r4, r4, #15
10100200:	f818 4004 	ldrb.w	r4, [r8, r4]
10100204:	3904      	subs	r1, #4
10100206:	ea4c 0404 	orr.w	r4, ip, r4
1010020a:	f802 4f01 	strb.w	r4, [r2, #1]!
1010020e:	d5f3      	bpl.n	101001f8 <DiagVSprintf+0xcc>
10100210:	eb0b 0393 	add.w	r3, fp, r3, lsr #2
10100214:	f103 0b01 	add.w	fp, r3, #1
10100218:	45f3      	cmp	fp, lr
1010021a:	d99b      	bls.n	10100154 <DiagVSprintf+0x28>
1010021c:	f89d 4004 	ldrb.w	r4, [sp, #4]
10100220:	f10d 0a05 	add.w	sl, sp, #5
10100224:	b157      	cbz	r7, 1010023c <DiagVSprintf+0x110>
10100226:	2c0a      	cmp	r4, #10
10100228:	702c      	strb	r4, [r5, #0]
1010022a:	f105 0501 	add.w	r5, r5, #1
1010022e:	d00a      	beq.n	10100246 <DiagVSprintf+0x11a>
10100230:	45d3      	cmp	fp, sl
10100232:	d98f      	bls.n	10100154 <DiagVSprintf+0x28>
10100234:	f81a 4b01 	ldrb.w	r4, [sl], #1
10100238:	2f00      	cmp	r7, #0
1010023a:	d1f4      	bne.n	10100226 <DiagVSprintf+0xfa>
1010023c:	4620      	mov	r0, r4
1010023e:	4b6a      	ldr	r3, [pc, #424]	; (101003e8 <DiagVSprintf+0x2bc>)
10100240:	4798      	blx	r3
10100242:	2c0a      	cmp	r4, #10
10100244:	d1f4      	bne.n	10100230 <DiagVSprintf+0x104>
10100246:	200d      	movs	r0, #13
10100248:	4b67      	ldr	r3, [pc, #412]	; (101003e8 <DiagVSprintf+0x2bc>)
1010024a:	4798      	blx	r3
1010024c:	e7f0      	b.n	10100230 <DiagVSprintf+0x104>
1010024e:	f1a4 0330 	sub.w	r3, r4, #48	; 0x30
10100252:	2b09      	cmp	r3, #9
10100254:	d9a0      	bls.n	10100198 <DiagVSprintf+0x6c>
10100256:	2300      	movs	r3, #0
10100258:	2c78      	cmp	r4, #120	; 0x78
1010025a:	d0b0      	beq.n	101001be <DiagVSprintf+0x92>
1010025c:	2c58      	cmp	r4, #88	; 0x58
1010025e:	d049      	beq.n	101002f4 <DiagVSprintf+0x1c8>
10100260:	2c70      	cmp	r4, #112	; 0x70
10100262:	d054      	beq.n	1010030e <DiagVSprintf+0x1e2>
10100264:	2c50      	cmp	r4, #80	; 0x50
10100266:	d062      	beq.n	1010032e <DiagVSprintf+0x202>
10100268:	2c64      	cmp	r4, #100	; 0x64
1010026a:	d065      	beq.n	10100338 <DiagVSprintf+0x20c>
1010026c:	2c63      	cmp	r4, #99	; 0x63
1010026e:	bf08      	it	eq
10100270:	b2c4      	uxtbeq	r4, r0
10100272:	f10d 0a05 	add.w	sl, sp, #5
10100276:	bf06      	itte	eq
10100278:	f88d 4004 	strbeq.w	r4, [sp, #4]
1010027c:	f109 0904 	addeq.w	r9, r9, #4
10100280:	f88d 4004 	strbne.w	r4, [sp, #4]
10100284:	46d3      	mov	fp, sl
10100286:	e7cd      	b.n	10100224 <DiagVSprintf+0xf8>
10100288:	1be8      	subs	r0, r5, r7
1010028a:	b10f      	cbz	r7, 10100290 <DiagVSprintf+0x164>
1010028c:	2300      	movs	r3, #0
1010028e:	702b      	strb	r3, [r5, #0]
10100290:	b007      	add	sp, #28
10100292:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10100296:	f8d9 4000 	ldr.w	r4, [r9]
1010029a:	7820      	ldrb	r0, [r4, #0]
1010029c:	f109 0904 	add.w	r9, r9, #4
101002a0:	2800      	cmp	r0, #0
101002a2:	f43f af57 	beq.w	10100154 <DiagVSprintf+0x28>
101002a6:	b147      	cbz	r7, 101002ba <DiagVSprintf+0x18e>
101002a8:	7028      	strb	r0, [r5, #0]
101002aa:	3501      	adds	r5, #1
101002ac:	f814 0f01 	ldrb.w	r0, [r4, #1]!
101002b0:	2800      	cmp	r0, #0
101002b2:	f43f af4f 	beq.w	10100154 <DiagVSprintf+0x28>
101002b6:	2f00      	cmp	r7, #0
101002b8:	d1f6      	bne.n	101002a8 <DiagVSprintf+0x17c>
101002ba:	4b4b      	ldr	r3, [pc, #300]	; (101003e8 <DiagVSprintf+0x2bc>)
101002bc:	4798      	blx	r3
101002be:	e7f5      	b.n	101002ac <DiagVSprintf+0x180>
101002c0:	2304      	movs	r3, #4
101002c2:	f1a4 0230 	sub.w	r2, r4, #48	; 0x30
101002c6:	2a09      	cmp	r2, #9
101002c8:	d8c6      	bhi.n	10100258 <DiagVSprintf+0x12c>
101002ca:	e765      	b.n	10100198 <DiagVSprintf+0x6c>
101002cc:	f5a0 5380 	sub.w	r3, r0, #4096	; 0x1000
101002d0:	f5b3 4f70 	cmp.w	r3, #61440	; 0xf000
101002d4:	d36e      	bcc.n	101003b4 <DiagVSprintf+0x288>
101002d6:	f5a0 3380 	sub.w	r3, r0, #65536	; 0x10000
101002da:	f5b3 2f70 	cmp.w	r3, #983040	; 0xf0000
101002de:	d36e      	bcc.n	101003be <DiagVSprintf+0x292>
101002e0:	f5a0 1380 	sub.w	r3, r0, #1048576	; 0x100000
101002e4:	f5b3 0f70 	cmp.w	r3, #15728640	; 0xf00000
101002e8:	d26b      	bcs.n	101003c2 <DiagVSprintf+0x296>
101002ea:	2314      	movs	r3, #20
101002ec:	e7e9      	b.n	101002c2 <DiagVSprintf+0x196>
101002ee:	4b3e      	ldr	r3, [pc, #248]	; (101003e8 <DiagVSprintf+0x2bc>)
101002f0:	4798      	blx	r3
101002f2:	e72f      	b.n	10100154 <DiagVSprintf+0x28>
101002f4:	f10d 0e04 	add.w	lr, sp, #4
101002f8:	f109 0904 	add.w	r9, r9, #4
101002fc:	46f3      	mov	fp, lr
101002fe:	f04f 0c00 	mov.w	ip, #0
10100302:	2800      	cmp	r0, #0
10100304:	f47f af65 	bne.w	101001d2 <DiagVSprintf+0xa6>
10100308:	f06f 0203 	mvn.w	r2, #3
1010030c:	e76a      	b.n	101001e4 <DiagVSprintf+0xb8>
1010030e:	f04f 0c20 	mov.w	ip, #32
10100312:	f109 0904 	add.w	r9, r9, #4
10100316:	2130      	movs	r1, #48	; 0x30
10100318:	f04c 0258 	orr.w	r2, ip, #88	; 0x58
1010031c:	f88d 1004 	strb.w	r1, [sp, #4]
10100320:	f88d 2005 	strb.w	r2, [sp, #5]
10100324:	f10d 0b06 	add.w	fp, sp, #6
10100328:	f10d 0e04 	add.w	lr, sp, #4
1010032c:	e74e      	b.n	101001cc <DiagVSprintf+0xa0>
1010032e:	f109 0904 	add.w	r9, r9, #4
10100332:	f04f 0c00 	mov.w	ip, #0
10100336:	e7ee      	b.n	10100316 <DiagVSprintf+0x1ea>
10100338:	2800      	cmp	r0, #0
1010033a:	f109 0904 	add.w	r9, r9, #4
1010033e:	db48      	blt.n	101003d2 <DiagVSprintf+0x2a6>
10100340:	f10d 0e04 	add.w	lr, sp, #4
10100344:	4671      	mov	r1, lr
10100346:	f04f 0c00 	mov.w	ip, #0
1010034a:	468b      	mov	fp, r1
1010034c:	4604      	mov	r4, r0
1010034e:	f8df a0a0 	ldr.w	sl, [pc, #160]	; 101003f0 <DiagVSprintf+0x2c4>
10100352:	ebac 0c01 	sub.w	ip, ip, r1
10100356:	fb8a 2004 	smull	r2, r0, sl, r4
1010035a:	17e2      	asrs	r2, r4, #31
1010035c:	ebc2 02a0 	rsb	r2, r2, r0, asr #2
10100360:	eb02 0082 	add.w	r0, r2, r2, lsl #2
10100364:	eba4 0040 	sub.w	r0, r4, r0, lsl #1
10100368:	4614      	mov	r4, r2
1010036a:	3030      	adds	r0, #48	; 0x30
1010036c:	f80b 0b01 	strb.w	r0, [fp], #1
10100370:	eb0b 020c 	add.w	r2, fp, ip
10100374:	2c00      	cmp	r4, #0
10100376:	d1ee      	bne.n	10100356 <DiagVSprintf+0x22a>
10100378:	2b00      	cmp	r3, #0
1010037a:	db0d      	blt.n	10100398 <DiagVSprintf+0x26c>
1010037c:	ea6f 0393 	mvn.w	r3, r3, lsr #2
10100380:	2030      	movs	r0, #48	; 0x30
10100382:	4413      	add	r3, r2
10100384:	2a00      	cmp	r2, #0
10100386:	f102 32ff 	add.w	r2, r2, #4294967295
1010038a:	bfdc      	itt	le
1010038c:	f88b 0000 	strble.w	r0, [fp]
10100390:	f10b 0b01 	addle.w	fp, fp, #1
10100394:	4293      	cmp	r3, r2
10100396:	d1f5      	bne.n	10100384 <DiagVSprintf+0x258>
10100398:	f10b 33ff 	add.w	r3, fp, #4294967295
1010039c:	4299      	cmp	r1, r3
1010039e:	f4bf af3b 	bcs.w	10100218 <DiagVSprintf+0xec>
101003a2:	781a      	ldrb	r2, [r3, #0]
101003a4:	7808      	ldrb	r0, [r1, #0]
101003a6:	f803 0901 	strb.w	r0, [r3], #-1
101003aa:	f801 2b01 	strb.w	r2, [r1], #1
101003ae:	4299      	cmp	r1, r3
101003b0:	d3f7      	bcc.n	101003a2 <DiagVSprintf+0x276>
101003b2:	e731      	b.n	10100218 <DiagVSprintf+0xec>
101003b4:	230c      	movs	r3, #12
101003b6:	e784      	b.n	101002c2 <DiagVSprintf+0x196>
101003b8:	4618      	mov	r0, r3
101003ba:	463d      	mov	r5, r7
101003bc:	e765      	b.n	1010028a <DiagVSprintf+0x15e>
101003be:	2310      	movs	r3, #16
101003c0:	e77f      	b.n	101002c2 <DiagVSprintf+0x196>
101003c2:	f100 437f 	add.w	r3, r0, #4278190080	; 0xff000000
101003c6:	f1b3 6f70 	cmp.w	r3, #251658240	; 0xf000000
101003ca:	bf2c      	ite	cs
101003cc:	231c      	movcs	r3, #28
101003ce:	2318      	movcc	r3, #24
101003d0:	e777      	b.n	101002c2 <DiagVSprintf+0x196>
101003d2:	222d      	movs	r2, #45	; 0x2d
101003d4:	4240      	negs	r0, r0
101003d6:	f88d 2004 	strb.w	r2, [sp, #4]
101003da:	f04f 0c01 	mov.w	ip, #1
101003de:	f10d 0105 	add.w	r1, sp, #5
101003e2:	f10d 0e04 	add.w	lr, sp, #4
101003e6:	e7b0      	b.n	1010034a <DiagVSprintf+0x21e>
101003e8:	10102af5 	.word	0x10102af5
101003ec:	101d404c 	.word	0x101d404c
101003f0:	66666667 	.word	0x66666667

101003f4 <DiagPrintf>:
101003f4:	b40f      	push	{r0, r1, r2, r3}
101003f6:	b508      	push	{r3, lr}
101003f8:	4b11      	ldr	r3, [pc, #68]	; (10100440 <DiagPrintf+0x4c>)
101003fa:	681a      	ldr	r2, [r3, #0]
101003fc:	2a01      	cmp	r2, #1
101003fe:	d01a      	beq.n	10100436 <DiagPrintf+0x42>
10100400:	685a      	ldr	r2, [r3, #4]
10100402:	2a01      	cmp	r2, #1
10100404:	d008      	beq.n	10100418 <DiagPrintf+0x24>
10100406:	aa03      	add	r2, sp, #12
10100408:	9902      	ldr	r1, [sp, #8]
1010040a:	2000      	movs	r0, #0
1010040c:	f7ff fe8e 	bl	1010012c <DiagVSprintf>
10100410:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
10100414:	b004      	add	sp, #16
10100416:	4770      	bx	lr
10100418:	689b      	ldr	r3, [r3, #8]
1010041a:	2b00      	cmp	r3, #0
1010041c:	d0f3      	beq.n	10100406 <DiagPrintf+0x12>
1010041e:	9802      	ldr	r0, [sp, #8]
10100420:	4798      	blx	r3
10100422:	2800      	cmp	r0, #0
10100424:	d0ef      	beq.n	10100406 <DiagPrintf+0x12>
10100426:	aa03      	add	r2, sp, #12
10100428:	9902      	ldr	r1, [sp, #8]
1010042a:	f7ff fe7f 	bl	1010012c <DiagVSprintf>
1010042e:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
10100432:	b004      	add	sp, #16
10100434:	4770      	bx	lr
10100436:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
1010043a:	2000      	movs	r0, #0
1010043c:	b004      	add	sp, #16
1010043e:	4770      	bx	lr
10100440:	10000000 	.word	0x10000000

10100444 <DiagPrintfD>:
10100444:	b40f      	push	{r0, r1, r2, r3}
10100446:	b508      	push	{r3, lr}
10100448:	4b08      	ldr	r3, [pc, #32]	; (1010046c <DiagPrintfD+0x28>)
1010044a:	681b      	ldr	r3, [r3, #0]
1010044c:	2b01      	cmp	r3, #1
1010044e:	d008      	beq.n	10100462 <DiagPrintfD+0x1e>
10100450:	aa03      	add	r2, sp, #12
10100452:	9902      	ldr	r1, [sp, #8]
10100454:	2000      	movs	r0, #0
10100456:	f7ff fe69 	bl	1010012c <DiagVSprintf>
1010045a:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
1010045e:	b004      	add	sp, #16
10100460:	4770      	bx	lr
10100462:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
10100466:	2000      	movs	r0, #0
10100468:	b004      	add	sp, #16
1010046a:	4770      	bx	lr
1010046c:	10000000 	.word	0x10000000

10100470 <DiagSPrintf>:
10100470:	b40e      	push	{r1, r2, r3}
10100472:	4b09      	ldr	r3, [pc, #36]	; (10100498 <DiagSPrintf+0x28>)
10100474:	681b      	ldr	r3, [r3, #0]
10100476:	2b01      	cmp	r3, #1
10100478:	b500      	push	{lr}
1010047a:	d007      	beq.n	1010048c <DiagSPrintf+0x1c>
1010047c:	aa02      	add	r2, sp, #8
1010047e:	9901      	ldr	r1, [sp, #4]
10100480:	f7ff fe54 	bl	1010012c <DiagVSprintf>
10100484:	f85d eb04 	ldr.w	lr, [sp], #4
10100488:	b003      	add	sp, #12
1010048a:	4770      	bx	lr
1010048c:	f85d eb04 	ldr.w	lr, [sp], #4
10100490:	2000      	movs	r0, #0
10100492:	b003      	add	sp, #12
10100494:	4770      	bx	lr
10100496:	bf00      	nop
10100498:	10000000 	.word	0x10000000

1010049c <DiagSnPrintf>:
1010049c:	b310      	cbz	r0, 101004e4 <DiagSnPrintf+0x48>
1010049e:	b40c      	push	{r2, r3}
101004a0:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
101004a4:	b087      	sub	sp, #28
101004a6:	ac11      	add	r4, sp, #68	; 0x44
101004a8:	9400      	str	r4, [sp, #0]
101004aa:	b9e1      	cbnz	r1, 101004e6 <DiagSnPrintf+0x4a>
101004ac:	f04f 31ff 	mov.w	r1, #4294967295
101004b0:	9b10      	ldr	r3, [sp, #64]	; 0x40
101004b2:	781a      	ldrb	r2, [r3, #0]
101004b4:	2a00      	cmp	r2, #0
101004b6:	f000 813e 	beq.w	10100736 <DiagSnPrintf+0x29a>
101004ba:	46a6      	mov	lr, r4
101004bc:	4607      	mov	r7, r0
101004be:	f04f 0930 	mov.w	r9, #48	; 0x30
101004c2:	f8df c29c 	ldr.w	ip, [pc, #668]	; 10100760 <DiagSnPrintf+0x2c4>
101004c6:	f10d 0804 	add.w	r8, sp, #4
101004ca:	2a25      	cmp	r2, #37	; 0x25
101004cc:	d017      	beq.n	101004fe <DiagSnPrintf+0x62>
101004ce:	1c7c      	adds	r4, r7, #1
101004d0:	42a1      	cmp	r1, r4
101004d2:	703a      	strb	r2, [r7, #0]
101004d4:	d809      	bhi.n	101004ea <DiagSnPrintf+0x4e>
101004d6:	1a20      	subs	r0, r4, r0
101004d8:	2300      	movs	r3, #0
101004da:	7023      	strb	r3, [r4, #0]
101004dc:	b007      	add	sp, #28
101004de:	e8bd 4ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
101004e2:	b002      	add	sp, #8
101004e4:	4770      	bx	lr
101004e6:	4401      	add	r1, r0
101004e8:	e7e2      	b.n	101004b0 <DiagSnPrintf+0x14>
101004ea:	4627      	mov	r7, r4
101004ec:	9b10      	ldr	r3, [sp, #64]	; 0x40
101004ee:	785a      	ldrb	r2, [r3, #1]
101004f0:	3301      	adds	r3, #1
101004f2:	9310      	str	r3, [sp, #64]	; 0x40
101004f4:	2a00      	cmp	r2, #0
101004f6:	d1e8      	bne.n	101004ca <DiagSnPrintf+0x2e>
101004f8:	1a38      	subs	r0, r7, r0
101004fa:	463c      	mov	r4, r7
101004fc:	e7ec      	b.n	101004d8 <DiagSnPrintf+0x3c>
101004fe:	785e      	ldrb	r6, [r3, #1]
10100500:	3301      	adds	r3, #1
10100502:	9310      	str	r3, [sp, #64]	; 0x40
10100504:	2e73      	cmp	r6, #115	; 0x73
10100506:	f8de 5000 	ldr.w	r5, [lr]
1010050a:	d072      	beq.n	101005f2 <DiagSnPrintf+0x156>
1010050c:	2d0f      	cmp	r5, #15
1010050e:	dc2f      	bgt.n	10100570 <DiagSnPrintf+0xd4>
10100510:	f1a6 0230 	sub.w	r2, r6, #48	; 0x30
10100514:	2a09      	cmp	r2, #9
10100516:	d959      	bls.n	101005cc <DiagSnPrintf+0x130>
10100518:	2200      	movs	r2, #0
1010051a:	2e78      	cmp	r6, #120	; 0x78
1010051c:	d07f      	beq.n	1010061e <DiagSnPrintf+0x182>
1010051e:	2e58      	cmp	r6, #88	; 0x58
10100520:	f000 80ae 	beq.w	10100680 <DiagSnPrintf+0x1e4>
10100524:	2e70      	cmp	r6, #112	; 0x70
10100526:	f000 80b4 	beq.w	10100692 <DiagSnPrintf+0x1f6>
1010052a:	2e50      	cmp	r6, #80	; 0x50
1010052c:	f000 80bf 	beq.w	101006ae <DiagSnPrintf+0x212>
10100530:	2e64      	cmp	r6, #100	; 0x64
10100532:	f000 80c2 	beq.w	101006ba <DiagSnPrintf+0x21e>
10100536:	2e63      	cmp	r6, #99	; 0x63
10100538:	bf05      	ittet	eq
1010053a:	b2ee      	uxtbeq	r6, r5
1010053c:	f88d 6004 	strbeq.w	r6, [sp, #4]
10100540:	f88d 6004 	strbne.w	r6, [sp, #4]
10100544:	f10e 0e04 	addeq.w	lr, lr, #4
10100548:	f10d 0a05 	add.w	sl, sp, #5
1010054c:	1c7a      	adds	r2, r7, #1
1010054e:	4291      	cmp	r1, r2
10100550:	703e      	strb	r6, [r7, #0]
10100552:	d932      	bls.n	101005ba <DiagSnPrintf+0x11e>
10100554:	f10d 0305 	add.w	r3, sp, #5
10100558:	e005      	b.n	10100566 <DiagSnPrintf+0xca>
1010055a:	f813 4b01 	ldrb.w	r4, [r3], #1
1010055e:	f802 4b01 	strb.w	r4, [r2], #1
10100562:	4291      	cmp	r1, r2
10100564:	d02a      	beq.n	101005bc <DiagSnPrintf+0x120>
10100566:	459a      	cmp	sl, r3
10100568:	d8f7      	bhi.n	1010055a <DiagSnPrintf+0xbe>
1010056a:	4617      	mov	r7, r2
1010056c:	9b10      	ldr	r3, [sp, #64]	; 0x40
1010056e:	e7be      	b.n	101004ee <DiagSnPrintf+0x52>
10100570:	f1a5 0210 	sub.w	r2, r5, #16
10100574:	2aef      	cmp	r2, #239	; 0xef
10100576:	d924      	bls.n	101005c2 <DiagSnPrintf+0x126>
10100578:	f5a5 7280 	sub.w	r2, r5, #256	; 0x100
1010057c:	f5b2 6f70 	cmp.w	r2, #3840	; 0xf00
10100580:	f0c0 8085 	bcc.w	1010068e <DiagSnPrintf+0x1f2>
10100584:	f5a5 5280 	sub.w	r2, r5, #4096	; 0x1000
10100588:	f5b2 4f70 	cmp.w	r2, #61440	; 0xf000
1010058c:	f0c0 80d1 	bcc.w	10100732 <DiagSnPrintf+0x296>
10100590:	4c71      	ldr	r4, [pc, #452]	; (10100758 <DiagSnPrintf+0x2bc>)
10100592:	f5a5 3280 	sub.w	r2, r5, #65536	; 0x10000
10100596:	42a2      	cmp	r2, r4
10100598:	f240 80d2 	bls.w	10100740 <DiagSnPrintf+0x2a4>
1010059c:	f5a5 1280 	sub.w	r2, r5, #1048576	; 0x100000
101005a0:	f504 0461 	add.w	r4, r4, #14745600	; 0xe10000
101005a4:	42a2      	cmp	r2, r4
101005a6:	f240 80d5 	bls.w	10100754 <DiagSnPrintf+0x2b8>
101005aa:	f105 427f 	add.w	r2, r5, #4278190080	; 0xff000000
101005ae:	f1b2 6f70 	cmp.w	r2, #251658240	; 0xf000000
101005b2:	bf2c      	ite	cs
101005b4:	221c      	movcs	r2, #28
101005b6:	2218      	movcc	r2, #24
101005b8:	e004      	b.n	101005c4 <DiagSnPrintf+0x128>
101005ba:	4611      	mov	r1, r2
101005bc:	1a08      	subs	r0, r1, r0
101005be:	460c      	mov	r4, r1
101005c0:	e78a      	b.n	101004d8 <DiagSnPrintf+0x3c>
101005c2:	2204      	movs	r2, #4
101005c4:	f1a6 0430 	sub.w	r4, r6, #48	; 0x30
101005c8:	2c09      	cmp	r4, #9
101005ca:	d8a6      	bhi.n	1010051a <DiagSnPrintf+0x7e>
101005cc:	2200      	movs	r2, #0
101005ce:	eb02 0282 	add.w	r2, r2, r2, lsl #2
101005d2:	eb06 0442 	add.w	r4, r6, r2, lsl #1
101005d6:	f813 6f01 	ldrb.w	r6, [r3, #1]!
101005da:	f1a6 0a30 	sub.w	sl, r6, #48	; 0x30
101005de:	f1ba 0f09 	cmp.w	sl, #9
101005e2:	f1a4 0230 	sub.w	r2, r4, #48	; 0x30
101005e6:	d9f2      	bls.n	101005ce <DiagSnPrintf+0x132>
101005e8:	f1a4 0231 	sub.w	r2, r4, #49	; 0x31
101005ec:	9310      	str	r3, [sp, #64]	; 0x40
101005ee:	0092      	lsls	r2, r2, #2
101005f0:	e793      	b.n	1010051a <DiagSnPrintf+0x7e>
101005f2:	782a      	ldrb	r2, [r5, #0]
101005f4:	f10e 0e04 	add.w	lr, lr, #4
101005f8:	2a00      	cmp	r2, #0
101005fa:	f43f af78 	beq.w	101004ee <DiagSnPrintf+0x52>
101005fe:	1c7c      	adds	r4, r7, #1
10100600:	428c      	cmp	r4, r1
10100602:	703a      	strb	r2, [r7, #0]
10100604:	f4bf af67 	bcs.w	101004d6 <DiagSnPrintf+0x3a>
10100608:	4627      	mov	r7, r4
1010060a:	f815 2f01 	ldrb.w	r2, [r5, #1]!
1010060e:	2a00      	cmp	r2, #0
10100610:	f43f af6d 	beq.w	101004ee <DiagSnPrintf+0x52>
10100614:	f807 2b01 	strb.w	r2, [r7], #1
10100618:	42b9      	cmp	r1, r7
1010061a:	d1f6      	bne.n	1010060a <DiagSnPrintf+0x16e>
1010061c:	e7ce      	b.n	101005bc <DiagSnPrintf+0x120>
1010061e:	462b      	mov	r3, r5
10100620:	f04f 0b20 	mov.w	fp, #32
10100624:	46c2      	mov	sl, r8
10100626:	f10e 0e04 	add.w	lr, lr, #4
1010062a:	2d00      	cmp	r5, #0
1010062c:	d07e      	beq.n	1010072c <DiagSnPrintf+0x290>
1010062e:	2600      	movs	r6, #0
10100630:	f013 040f 	ands.w	r4, r3, #15
10100634:	bf18      	it	ne
10100636:	2401      	movne	r4, #1
10100638:	091b      	lsrs	r3, r3, #4
1010063a:	4426      	add	r6, r4
1010063c:	d1f8      	bne.n	10100630 <DiagSnPrintf+0x194>
1010063e:	3e01      	subs	r6, #1
10100640:	00b4      	lsls	r4, r6, #2
10100642:	42a2      	cmp	r2, r4
10100644:	bfb8      	it	lt
10100646:	4622      	movlt	r2, r4
10100648:	2a00      	cmp	r2, #0
1010064a:	db14      	blt.n	10100676 <DiagSnPrintf+0x1da>
1010064c:	4613      	mov	r3, r2
1010064e:	fa4f fb8b 	sxtb.w	fp, fp
10100652:	f10a 34ff 	add.w	r4, sl, #4294967295
10100656:	fa45 f603 	asr.w	r6, r5, r3
1010065a:	f006 060f 	and.w	r6, r6, #15
1010065e:	f81c 6006 	ldrb.w	r6, [ip, r6]
10100662:	3b04      	subs	r3, #4
10100664:	ea4b 0606 	orr.w	r6, fp, r6
10100668:	f804 6f01 	strb.w	r6, [r4, #1]!
1010066c:	d5f3      	bpl.n	10100656 <DiagSnPrintf+0x1ba>
1010066e:	eb0a 0292 	add.w	r2, sl, r2, lsr #2
10100672:	f102 0a01 	add.w	sl, r2, #1
10100676:	45c2      	cmp	sl, r8
10100678:	d960      	bls.n	1010073c <DiagSnPrintf+0x2a0>
1010067a:	f89d 6004 	ldrb.w	r6, [sp, #4]
1010067e:	e765      	b.n	1010054c <DiagSnPrintf+0xb0>
10100680:	f10e 0e04 	add.w	lr, lr, #4
10100684:	462b      	mov	r3, r5
10100686:	f04f 0b00 	mov.w	fp, #0
1010068a:	46c2      	mov	sl, r8
1010068c:	e7cd      	b.n	1010062a <DiagSnPrintf+0x18e>
1010068e:	2208      	movs	r2, #8
10100690:	e798      	b.n	101005c4 <DiagSnPrintf+0x128>
10100692:	462b      	mov	r3, r5
10100694:	f04f 0b20 	mov.w	fp, #32
10100698:	f10e 0e04 	add.w	lr, lr, #4
1010069c:	f04b 0458 	orr.w	r4, fp, #88	; 0x58
101006a0:	f88d 9004 	strb.w	r9, [sp, #4]
101006a4:	f88d 4005 	strb.w	r4, [sp, #5]
101006a8:	f10d 0a06 	add.w	sl, sp, #6
101006ac:	e7bd      	b.n	1010062a <DiagSnPrintf+0x18e>
101006ae:	f10e 0e04 	add.w	lr, lr, #4
101006b2:	462b      	mov	r3, r5
101006b4:	f04f 0b00 	mov.w	fp, #0
101006b8:	e7f0      	b.n	1010069c <DiagSnPrintf+0x200>
101006ba:	2d00      	cmp	r5, #0
101006bc:	f10e 0e04 	add.w	lr, lr, #4
101006c0:	db40      	blt.n	10100744 <DiagSnPrintf+0x2a8>
101006c2:	2600      	movs	r6, #0
101006c4:	4644      	mov	r4, r8
101006c6:	4693      	mov	fp, r2
101006c8:	46a2      	mov	sl, r4
101006ca:	462a      	mov	r2, r5
101006cc:	1b36      	subs	r6, r6, r4
101006ce:	4b23      	ldr	r3, [pc, #140]	; (1010075c <DiagSnPrintf+0x2c0>)
101006d0:	fb83 3502 	smull	r3, r5, r3, r2
101006d4:	17d3      	asrs	r3, r2, #31
101006d6:	ebc3 03a5 	rsb	r3, r3, r5, asr #2
101006da:	eb03 0583 	add.w	r5, r3, r3, lsl #2
101006de:	eba2 0545 	sub.w	r5, r2, r5, lsl #1
101006e2:	461a      	mov	r2, r3
101006e4:	3530      	adds	r5, #48	; 0x30
101006e6:	f80a 5b01 	strb.w	r5, [sl], #1
101006ea:	eb0a 0306 	add.w	r3, sl, r6
101006ee:	2a00      	cmp	r2, #0
101006f0:	d1ed      	bne.n	101006ce <DiagSnPrintf+0x232>
101006f2:	465a      	mov	r2, fp
101006f4:	2a00      	cmp	r2, #0
101006f6:	db0c      	blt.n	10100712 <DiagSnPrintf+0x276>
101006f8:	ea6f 029b 	mvn.w	r2, fp, lsr #2
101006fc:	441a      	add	r2, r3
101006fe:	2b00      	cmp	r3, #0
10100700:	f103 33ff 	add.w	r3, r3, #4294967295
10100704:	bfdc      	itt	le
10100706:	f88a 9000 	strble.w	r9, [sl]
1010070a:	f10a 0a01 	addle.w	sl, sl, #1
1010070e:	4293      	cmp	r3, r2
10100710:	d1f5      	bne.n	101006fe <DiagSnPrintf+0x262>
10100712:	f10a 33ff 	add.w	r3, sl, #4294967295
10100716:	429c      	cmp	r4, r3
10100718:	d2ad      	bcs.n	10100676 <DiagSnPrintf+0x1da>
1010071a:	781a      	ldrb	r2, [r3, #0]
1010071c:	7825      	ldrb	r5, [r4, #0]
1010071e:	f803 5901 	strb.w	r5, [r3], #-1
10100722:	f804 2b01 	strb.w	r2, [r4], #1
10100726:	429c      	cmp	r4, r3
10100728:	d3f7      	bcc.n	1010071a <DiagSnPrintf+0x27e>
1010072a:	e7a4      	b.n	10100676 <DiagSnPrintf+0x1da>
1010072c:	f06f 0403 	mvn.w	r4, #3
10100730:	e787      	b.n	10100642 <DiagSnPrintf+0x1a6>
10100732:	220c      	movs	r2, #12
10100734:	e746      	b.n	101005c4 <DiagSnPrintf+0x128>
10100736:	4604      	mov	r4, r0
10100738:	4610      	mov	r0, r2
1010073a:	e6cd      	b.n	101004d8 <DiagSnPrintf+0x3c>
1010073c:	463a      	mov	r2, r7
1010073e:	e714      	b.n	1010056a <DiagSnPrintf+0xce>
10100740:	2210      	movs	r2, #16
10100742:	e73f      	b.n	101005c4 <DiagSnPrintf+0x128>
10100744:	232d      	movs	r3, #45	; 0x2d
10100746:	426d      	negs	r5, r5
10100748:	f88d 3004 	strb.w	r3, [sp, #4]
1010074c:	2601      	movs	r6, #1
1010074e:	f10d 0405 	add.w	r4, sp, #5
10100752:	e7b8      	b.n	101006c6 <DiagSnPrintf+0x22a>
10100754:	2214      	movs	r2, #20
10100756:	e735      	b.n	101005c4 <DiagSnPrintf+0x128>
10100758:	000effff 	.word	0x000effff
1010075c:	66666667 	.word	0x66666667
10100760:	101d404c 	.word	0x101d404c

10100764 <Rand>:
10100764:	4b1a      	ldr	r3, [pc, #104]	; (101007d0 <Rand+0x6c>)
10100766:	681a      	ldr	r2, [r3, #0]
10100768:	b5f0      	push	{r4, r5, r6, r7, lr}
1010076a:	b962      	cbnz	r2, 10100786 <Rand+0x22>
1010076c:	2101      	movs	r1, #1
1010076e:	f24c 02e0 	movw	r2, #49376	; 0xc0e0
10100772:	6019      	str	r1, [r3, #0]
10100774:	4817      	ldr	r0, [pc, #92]	; (101007d4 <Rand+0x70>)
10100776:	4918      	ldr	r1, [pc, #96]	; (101007d8 <Rand+0x74>)
10100778:	4c18      	ldr	r4, [pc, #96]	; (101007dc <Rand+0x78>)
1010077a:	4d19      	ldr	r5, [pc, #100]	; (101007e0 <Rand+0x7c>)
1010077c:	605d      	str	r5, [r3, #4]
1010077e:	609a      	str	r2, [r3, #8]
10100780:	60dc      	str	r4, [r3, #12]
10100782:	6119      	str	r1, [r3, #16]
10100784:	bdf0      	pop	{r4, r5, r6, r7, pc}
10100786:	689a      	ldr	r2, [r3, #8]
10100788:	685e      	ldr	r6, [r3, #4]
1010078a:	4d16      	ldr	r5, [pc, #88]	; (101007e4 <Rand+0x80>)
1010078c:	0091      	lsls	r1, r2, #2
1010078e:	68df      	ldr	r7, [r3, #12]
10100790:	4c15      	ldr	r4, [pc, #84]	; (101007e8 <Rand+0x84>)
10100792:	ea82 0001 	eor.w	r0, r2, r1
10100796:	ea86 1e86 	eor.w	lr, r6, r6, lsl #6
1010079a:	f021 021f 	bic.w	r2, r1, #31
1010079e:	ea05 4586 	and.w	r5, r5, r6, lsl #18
101007a2:	4912      	ldr	r1, [pc, #72]	; (101007ec <Rand+0x88>)
101007a4:	691e      	ldr	r6, [r3, #16]
101007a6:	ea45 355e 	orr.w	r5, r5, lr, lsr #13
101007aa:	ea04 14c7 	and.w	r4, r4, r7, lsl #7
101007ae:	ea87 3e47 	eor.w	lr, r7, r7, lsl #13
101007b2:	ea42 62d0 	orr.w	r2, r2, r0, lsr #27
101007b6:	ea85 0002 	eor.w	r0, r5, r2
101007ba:	ea44 545e 	orr.w	r4, r4, lr, lsr #21
101007be:	ea86 07c6 	eor.w	r7, r6, r6, lsl #3
101007c2:	ea01 3146 	and.w	r1, r1, r6, lsl #13
101007c6:	4060      	eors	r0, r4
101007c8:	ea41 3117 	orr.w	r1, r1, r7, lsr #12
101007cc:	4048      	eors	r0, r1
101007ce:	e7d5      	b.n	1010077c <Rand+0x18>
101007d0:	1000001c 	.word	0x1000001c
101007d4:	c6f8d8aa 	.word	0xc6f8d8aa
101007d8:	0600001b 	.word	0x0600001b
101007dc:	00181830 	.word	0x00181830
101007e0:	c0e00061 	.word	0xc0e00061
101007e4:	fff80000 	.word	0xfff80000
101007e8:	fffff800 	.word	0xfffff800
101007ec:	fff00000 	.word	0xfff00000

101007f0 <Rand_Arc4>:
101007f0:	b510      	push	{r4, lr}
101007f2:	4b08      	ldr	r3, [pc, #32]	; (10100814 <Rand_Arc4+0x24>)
101007f4:	4798      	blx	r3
101007f6:	4908      	ldr	r1, [pc, #32]	; (10100818 <Rand_Arc4+0x28>)
101007f8:	4a08      	ldr	r2, [pc, #32]	; (1010081c <Rand_Arc4+0x2c>)
101007fa:	694c      	ldr	r4, [r1, #20]
101007fc:	4b08      	ldr	r3, [pc, #32]	; (10100820 <Rand_Arc4+0x30>)
101007fe:	ea02 12c4 	and.w	r2, r2, r4, lsl #7
10100802:	ea03 2314 	and.w	r3, r3, r4, lsr #8
10100806:	4053      	eors	r3, r2
10100808:	ea83 3340 	eor.w	r3, r3, r0, lsl #13
1010080c:	ea83 2050 	eor.w	r0, r3, r0, lsr #9
10100810:	6148      	str	r0, [r1, #20]
10100812:	bd10      	pop	{r4, pc}
10100814:	10103215 	.word	0x10103215
10100818:	1000001c 	.word	0x1000001c
1010081c:	3f807f80 	.word	0x3f807f80
10100820:	000f80ff 	.word	0x000f80ff

10100824 <RandBytes_Get>:
10100824:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
10100828:	088e      	lsrs	r6, r1, #2
1010082a:	b082      	sub	sp, #8
1010082c:	460f      	mov	r7, r1
1010082e:	4680      	mov	r8, r0
10100830:	d00c      	beq.n	1010084c <RandBytes_Get+0x28>
10100832:	2400      	movs	r4, #0
10100834:	1f05      	subs	r5, r0, #4
10100836:	f7ff ffdb 	bl	101007f0 <Rand_Arc4>
1010083a:	3401      	adds	r4, #1
1010083c:	42a6      	cmp	r6, r4
1010083e:	f845 0f04 	str.w	r0, [r5, #4]!
10100842:	d1f8      	bne.n	10100836 <RandBytes_Get+0x12>
10100844:	ebc6 7386 	rsb	r3, r6, r6, lsl #30
10100848:	eb07 0783 	add.w	r7, r7, r3, lsl #2
1010084c:	b14f      	cbz	r7, 10100862 <RandBytes_Get+0x3e>
1010084e:	f7ff ffcf 	bl	101007f0 <Rand_Arc4>
10100852:	a902      	add	r1, sp, #8
10100854:	f841 0d04 	str.w	r0, [r1, #-4]!
10100858:	463a      	mov	r2, r7
1010085a:	eb08 0086 	add.w	r0, r8, r6, lsl #2
1010085e:	4b03      	ldr	r3, [pc, #12]	; (1010086c <RandBytes_Get+0x48>)
10100860:	4798      	blx	r3
10100862:	2000      	movs	r0, #0
10100864:	b002      	add	sp, #8
10100866:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
1010086a:	bf00      	nop
1010086c:	10106d15 	.word	0x10106d15

10100870 <io_assert_failed>:
10100870:	b508      	push	{r3, lr}
10100872:	4b05      	ldr	r3, [pc, #20]	; (10100888 <io_assert_failed+0x18>)
10100874:	681b      	ldr	r3, [r3, #0]
10100876:	039b      	lsls	r3, r3, #14
10100878:	d400      	bmi.n	1010087c <io_assert_failed+0xc>
1010087a:	e7fe      	b.n	1010087a <io_assert_failed+0xa>
1010087c:	460a      	mov	r2, r1
1010087e:	4601      	mov	r1, r0
10100880:	4802      	ldr	r0, [pc, #8]	; (1010088c <io_assert_failed+0x1c>)
10100882:	f7ff fdb7 	bl	101003f4 <DiagPrintf>
10100886:	e7f8      	b.n	1010087a <io_assert_failed+0xa>
10100888:	1000000c 	.word	0x1000000c
1010088c:	101d4060 	.word	0x101d4060

10100890 <BKUP_Write>:
10100890:	2807      	cmp	r0, #7
10100892:	b538      	push	{r3, r4, r5, lr}
10100894:	4604      	mov	r4, r0
10100896:	460d      	mov	r5, r1
10100898:	d903      	bls.n	101008a2 <BKUP_Write+0x12>
1010089a:	211f      	movs	r1, #31
1010089c:	4803      	ldr	r0, [pc, #12]	; (101008ac <BKUP_Write+0x1c>)
1010089e:	f7ff ffe7 	bl	10100870 <io_assert_failed>
101008a2:	4b03      	ldr	r3, [pc, #12]	; (101008b0 <BKUP_Write+0x20>)
101008a4:	f843 5024 	str.w	r5, [r3, r4, lsl #2]
101008a8:	bd38      	pop	{r3, r4, r5, pc}
101008aa:	bf00      	nop
101008ac:	101d4f48 	.word	0x101d4f48
101008b0:	480003c0 	.word	0x480003c0

101008b4 <BKUP_Read>:
101008b4:	2807      	cmp	r0, #7
101008b6:	b510      	push	{r4, lr}
101008b8:	4604      	mov	r4, r0
101008ba:	d903      	bls.n	101008c4 <BKUP_Read+0x10>
101008bc:	212e      	movs	r1, #46	; 0x2e
101008be:	4803      	ldr	r0, [pc, #12]	; (101008cc <BKUP_Read+0x18>)
101008c0:	f7ff ffd6 	bl	10100870 <io_assert_failed>
101008c4:	4b02      	ldr	r3, [pc, #8]	; (101008d0 <BKUP_Read+0x1c>)
101008c6:	f853 0024 	ldr.w	r0, [r3, r4, lsl #2]
101008ca:	bd10      	pop	{r4, pc}
101008cc:	101d4f54 	.word	0x101d4f54
101008d0:	480003c0 	.word	0x480003c0

101008d4 <BKUP_Set>:
101008d4:	2807      	cmp	r0, #7
101008d6:	b538      	push	{r3, r4, r5, lr}
101008d8:	4604      	mov	r4, r0
101008da:	460d      	mov	r5, r1
101008dc:	d903      	bls.n	101008e6 <BKUP_Set+0x12>
101008de:	213e      	movs	r1, #62	; 0x3e
101008e0:	4805      	ldr	r0, [pc, #20]	; (101008f8 <BKUP_Set+0x24>)
101008e2:	f7ff ffc5 	bl	10100870 <io_assert_failed>
101008e6:	00a4      	lsls	r4, r4, #2
101008e8:	f104 4490 	add.w	r4, r4, #1207959552	; 0x48000000
101008ec:	f8d4 33c0 	ldr.w	r3, [r4, #960]	; 0x3c0
101008f0:	431d      	orrs	r5, r3
101008f2:	f8c4 53c0 	str.w	r5, [r4, #960]	; 0x3c0
101008f6:	bd38      	pop	{r3, r4, r5, pc}
101008f8:	101d4f6c 	.word	0x101d4f6c

101008fc <BKUP_Clear>:
101008fc:	2807      	cmp	r0, #7
101008fe:	b538      	push	{r3, r4, r5, lr}
10100900:	4604      	mov	r4, r0
10100902:	460d      	mov	r5, r1
10100904:	d903      	bls.n	1010090e <BKUP_Clear+0x12>
10100906:	214e      	movs	r1, #78	; 0x4e
10100908:	4806      	ldr	r0, [pc, #24]	; (10100924 <BKUP_Clear+0x28>)
1010090a:	f7ff ffb1 	bl	10100870 <io_assert_failed>
1010090e:	00a4      	lsls	r4, r4, #2
10100910:	f104 4490 	add.w	r4, r4, #1207959552	; 0x48000000
10100914:	f8d4 13c0 	ldr.w	r1, [r4, #960]	; 0x3c0
10100918:	ea21 0105 	bic.w	r1, r1, r5
1010091c:	f8c4 13c0 	str.w	r1, [r4, #960]	; 0x3c0
10100920:	bd38      	pop	{r3, r4, r5, pc}
10100922:	bf00      	nop
10100924:	101d4f60 	.word	0x101d4f60

10100928 <BOOT_Reason>:
10100928:	4b02      	ldr	r3, [pc, #8]	; (10100934 <BOOT_Reason+0xc>)
1010092a:	6818      	ldr	r0, [r3, #0]
1010092c:	f400 107c 	and.w	r0, r0, #4128768	; 0x3f0000
10100930:	4770      	bx	lr
10100932:	bf00      	nop
10100934:	480003f8 	.word	0x480003f8

10100938 <DelayNop>:
10100938:	b120      	cbz	r0, 10100944 <DelayNop+0xc>
1010093a:	2300      	movs	r3, #0
1010093c:	bf00      	nop
1010093e:	3301      	adds	r3, #1
10100940:	4298      	cmp	r0, r3
10100942:	d1fb      	bne.n	1010093c <DelayNop+0x4>
10100944:	4770      	bx	lr
10100946:	bf00      	nop

10100948 <DelayUs>:
10100948:	b510      	push	{r4, lr}
1010094a:	4b0d      	ldr	r3, [pc, #52]	; (10100980 <DelayUs+0x38>)
1010094c:	4604      	mov	r4, r0
1010094e:	2000      	movs	r0, #0
10100950:	4798      	blx	r3
10100952:	4b0c      	ldr	r3, [pc, #48]	; (10100984 <DelayUs+0x3c>)
10100954:	fba3 3000 	umull	r3, r0, r3, r0
10100958:	0c80      	lsrs	r0, r0, #18
1010095a:	fb04 f000 	mul.w	r0, r4, r0
1010095e:	4c0a      	ldr	r4, [pc, #40]	; (10100988 <DelayUs+0x40>)
10100960:	fba4 3000 	umull	r3, r0, r4, r0
10100964:	4b09      	ldr	r3, [pc, #36]	; (1010098c <DelayUs+0x44>)
10100966:	681b      	ldr	r3, [r3, #0]
10100968:	0880      	lsrs	r0, r0, #2
1010096a:	b133      	cbz	r3, 1010097a <DelayUs+0x32>
1010096c:	0c1a      	lsrs	r2, r3, #16
1010096e:	b29b      	uxth	r3, r3
10100970:	bf18      	it	ne
10100972:	4350      	mulne	r0, r2
10100974:	b10b      	cbz	r3, 1010097a <DelayUs+0x32>
10100976:	fbb0 f0f3 	udiv	r0, r0, r3
1010097a:	4b05      	ldr	r3, [pc, #20]	; (10100990 <DelayUs+0x48>)
1010097c:	4798      	blx	r3
1010097e:	bd10      	pop	{r4, pc}
10100980:	10104515 	.word	0x10104515
10100984:	431bde83 	.word	0x431bde83
10100988:	cccccccd 	.word	0xcccccccd
1010098c:	10000034 	.word	0x10000034
10100990:	10100939 	.word	0x10100939

10100994 <DelayMs>:
10100994:	f44f 727a 	mov.w	r2, #1000	; 0x3e8
10100998:	b508      	push	{r3, lr}
1010099a:	fb02 f000 	mul.w	r0, r2, r0
1010099e:	4b01      	ldr	r3, [pc, #4]	; (101009a4 <DelayMs+0x10>)
101009a0:	4798      	blx	r3
101009a2:	bd08      	pop	{r3, pc}
101009a4:	10100949 	.word	0x10100949

101009a8 <EFUSEPowerSwitch>:
101009a8:	2901      	cmp	r1, #1
101009aa:	d00e      	beq.n	101009ca <EFUSEPowerSwitch+0x22>
101009ac:	4a1c      	ldr	r2, [pc, #112]	; (10100a20 <EFUSEPowerSwitch+0x78>)
101009ae:	6813      	ldr	r3, [r2, #0]
101009b0:	2801      	cmp	r0, #1
101009b2:	f423 437f 	bic.w	r3, r3, #65280	; 0xff00
101009b6:	6013      	str	r3, [r2, #0]
101009b8:	d000      	beq.n	101009bc <EFUSEPowerSwitch+0x14>
101009ba:	4770      	bx	lr
101009bc:	f852 3c94 	ldr.w	r3, [r2, #-148]
101009c0:	f023 0301 	bic.w	r3, r3, #1
101009c4:	f842 3c94 	str.w	r3, [r2, #-148]
101009c8:	4770      	bx	lr
101009ca:	4915      	ldr	r1, [pc, #84]	; (10100a20 <EFUSEPowerSwitch+0x78>)
101009cc:	680b      	ldr	r3, [r1, #0]
101009ce:	f423 437f 	bic.w	r3, r3, #65280	; 0xff00
101009d2:	f443 43d2 	orr.w	r3, r3, #26880	; 0x6900
101009d6:	600b      	str	r3, [r1, #0]
101009d8:	f851 3cdc 	ldr.w	r3, [r1, #-220]
101009dc:	f013 0f02 	tst.w	r3, #2
101009e0:	bf08      	it	eq
101009e2:	f043 0302 	orreq.w	r3, r3, #2
101009e6:	f1a1 01dc 	sub.w	r1, r1, #220	; 0xdc
101009ea:	bf08      	it	eq
101009ec:	600b      	streq	r3, [r1, #0]
101009ee:	490d      	ldr	r1, [pc, #52]	; (10100a24 <EFUSEPowerSwitch+0x7c>)
101009f0:	680b      	ldr	r3, [r1, #0]
101009f2:	f013 0f02 	tst.w	r3, #2
101009f6:	bf04      	itt	eq
101009f8:	f043 0302 	orreq.w	r3, r3, #2
101009fc:	600b      	streq	r3, [r1, #0]
101009fe:	2801      	cmp	r0, #1
10100a00:	d1db      	bne.n	101009ba <EFUSEPowerSwitch+0x12>
10100a02:	4909      	ldr	r1, [pc, #36]	; (10100a28 <EFUSEPowerSwitch+0x80>)
10100a04:	680b      	ldr	r3, [r1, #0]
10100a06:	0212      	lsls	r2, r2, #8
10100a08:	f423 6370 	bic.w	r3, r3, #3840	; 0xf00
10100a0c:	f043 0301 	orr.w	r3, r3, #1
10100a10:	f402 6270 	and.w	r2, r2, #3840	; 0xf00
10100a14:	431a      	orrs	r2, r3
10100a16:	600a      	str	r2, [r1, #0]
10100a18:	2019      	movs	r0, #25
10100a1a:	4b04      	ldr	r3, [pc, #16]	; (10100a2c <EFUSEPowerSwitch+0x84>)
10100a1c:	4718      	bx	r3
10100a1e:	bf00      	nop
10100a20:	480002e4 	.word	0x480002e4
10100a24:	48000210 	.word	0x48000210
10100a28:	48000250 	.word	0x48000250
10100a2c:	10100949 	.word	0x10100949

10100a30 <EFUSERead8>:
10100a30:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
10100a34:	4689      	mov	r9, r1
10100a36:	4690      	mov	r8, r2
10100a38:	492e      	ldr	r1, [pc, #184]	; (10100af4 <EFUSERead8+0xc4>)
10100a3a:	e841 f100 	tt	r1, r1
10100a3e:	024a      	lsls	r2, r1, #9
10100a40:	4604      	mov	r4, r0
10100a42:	d547      	bpl.n	10100ad4 <EFUSERead8+0xa4>
10100a44:	4d2c      	ldr	r5, [pc, #176]	; (10100af8 <EFUSERead8+0xc8>)
10100a46:	4a2d      	ldr	r2, [pc, #180]	; (10100afc <EFUSERead8+0xcc>)
10100a48:	f5a9 71a8 	sub.w	r1, r9, #336	; 0x150
10100a4c:	292f      	cmp	r1, #47	; 0x2f
10100a4e:	bf88      	it	hi
10100a50:	4615      	movhi	r5, r2
10100a52:	b904      	cbnz	r4, 10100a56 <EFUSERead8+0x26>
10100a54:	682c      	ldr	r4, [r5, #0]
10100a56:	f5b9 7f00 	cmp.w	r9, #512	; 0x200
10100a5a:	d30a      	bcc.n	10100a72 <EFUSERead8+0x42>
10100a5c:	f242 62ae 	movw	r2, #9902	; 0x26ae
10100a60:	b2a1      	uxth	r1, r4
10100a62:	4291      	cmp	r1, r2
10100a64:	d005      	beq.n	10100a72 <EFUSERead8+0x42>
10100a66:	23ff      	movs	r3, #255	; 0xff
10100a68:	f888 3000 	strb.w	r3, [r8]
10100a6c:	2000      	movs	r0, #0
10100a6e:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
10100a72:	461a      	mov	r2, r3
10100a74:	2101      	movs	r1, #1
10100a76:	2000      	movs	r0, #0
10100a78:	f7ff ff96 	bl	101009a8 <EFUSEPowerSwitch>
10100a7c:	4820      	ldr	r0, [pc, #128]	; (10100b00 <EFUSERead8+0xd0>)
10100a7e:	4921      	ldr	r1, [pc, #132]	; (10100b04 <EFUSERead8+0xd4>)
10100a80:	4b21      	ldr	r3, [pc, #132]	; (10100b08 <EFUSERead8+0xd8>)
10100a82:	6802      	ldr	r2, [r0, #0]
10100a84:	ea01 2109 	and.w	r1, r1, r9, lsl #8
10100a88:	4023      	ands	r3, r4
10100a8a:	430b      	orrs	r3, r1
10100a8c:	f422 6280 	bic.w	r2, r2, #1024	; 0x400
10100a90:	6002      	str	r2, [r0, #0]
10100a92:	602b      	str	r3, [r5, #0]
10100a94:	682b      	ldr	r3, [r5, #0]
10100a96:	2b00      	cmp	r3, #0
10100a98:	db11      	blt.n	10100abe <EFUSERead8+0x8e>
10100a9a:	2400      	movs	r4, #0
10100a9c:	f644 6720 	movw	r7, #20000	; 0x4e20
10100aa0:	4e1a      	ldr	r6, [pc, #104]	; (10100b0c <EFUSERead8+0xdc>)
10100aa2:	e001      	b.n	10100aa8 <EFUSERead8+0x78>
10100aa4:	42bc      	cmp	r4, r7
10100aa6:	d017      	beq.n	10100ad8 <EFUSERead8+0xa8>
10100aa8:	2005      	movs	r0, #5
10100aaa:	47b0      	blx	r6
10100aac:	682b      	ldr	r3, [r5, #0]
10100aae:	2b00      	cmp	r3, #0
10100ab0:	f104 0401 	add.w	r4, r4, #1
10100ab4:	daf6      	bge.n	10100aa4 <EFUSERead8+0x74>
10100ab6:	f644 6320 	movw	r3, #20000	; 0x4e20
10100aba:	429c      	cmp	r4, r3
10100abc:	d00c      	beq.n	10100ad8 <EFUSERead8+0xa8>
10100abe:	2001      	movs	r0, #1
10100ac0:	682b      	ldr	r3, [r5, #0]
10100ac2:	f888 3000 	strb.w	r3, [r8]
10100ac6:	4a12      	ldr	r2, [pc, #72]	; (10100b10 <EFUSERead8+0xe0>)
10100ac8:	6813      	ldr	r3, [r2, #0]
10100aca:	f423 437f 	bic.w	r3, r3, #65280	; 0xff00
10100ace:	6013      	str	r3, [r2, #0]
10100ad0:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
10100ad4:	4d09      	ldr	r5, [pc, #36]	; (10100afc <EFUSERead8+0xcc>)
10100ad6:	e7bc      	b.n	10100a52 <EFUSERead8+0x22>
10100ad8:	22ff      	movs	r2, #255	; 0xff
10100ada:	4b0e      	ldr	r3, [pc, #56]	; (10100b14 <EFUSERead8+0xe4>)
10100adc:	f888 2000 	strb.w	r2, [r8]
10100ae0:	6818      	ldr	r0, [r3, #0]
10100ae2:	f410 3000 	ands.w	r0, r0, #131072	; 0x20000
10100ae6:	d0ee      	beq.n	10100ac6 <EFUSERead8+0x96>
10100ae8:	4649      	mov	r1, r9
10100aea:	480b      	ldr	r0, [pc, #44]	; (10100b18 <EFUSERead8+0xe8>)
10100aec:	f7ff fc82 	bl	101003f4 <DiagPrintf>
10100af0:	2000      	movs	r0, #0
10100af2:	e7e8      	b.n	10100ac6 <EFUSERead8+0x96>
10100af4:	101003f5 	.word	0x101003f5
10100af8:	50000810 	.word	0x50000810
10100afc:	480002e8 	.word	0x480002e8
10100b00:	480002ec 	.word	0x480002ec
10100b04:	0003ff00 	.word	0x0003ff00
10100b08:	7ffc0000 	.word	0x7ffc0000
10100b0c:	10100949 	.word	0x10100949
10100b10:	480002e4 	.word	0x480002e4
10100b14:	1000000c 	.word	0x1000000c
10100b18:	101d4098 	.word	0x101d4098

10100b1c <EFUSEWrite8>:
10100b1c:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
10100b20:	4688      	mov	r8, r1
10100b22:	4616      	mov	r6, r2
10100b24:	4935      	ldr	r1, [pc, #212]	; (10100bfc <EFUSEWrite8+0xe0>)
10100b26:	e841 f100 	tt	r1, r1
10100b2a:	024a      	lsls	r2, r1, #9
10100b2c:	4604      	mov	r4, r0
10100b2e:	d555      	bpl.n	10100bdc <EFUSEWrite8+0xc0>
10100b30:	4d33      	ldr	r5, [pc, #204]	; (10100c00 <EFUSEWrite8+0xe4>)
10100b32:	4a34      	ldr	r2, [pc, #208]	; (10100c04 <EFUSEWrite8+0xe8>)
10100b34:	f5a8 71a8 	sub.w	r1, r8, #336	; 0x150
10100b38:	292f      	cmp	r1, #47	; 0x2f
10100b3a:	bf88      	it	hi
10100b3c:	4615      	movhi	r5, r2
10100b3e:	b904      	cbnz	r4, 10100b42 <EFUSEWrite8+0x26>
10100b40:	682c      	ldr	r4, [r5, #0]
10100b42:	f5b8 7f00 	cmp.w	r8, #512	; 0x200
10100b46:	d307      	bcc.n	10100b58 <EFUSEWrite8+0x3c>
10100b48:	f241 529d 	movw	r2, #5533	; 0x159d
10100b4c:	b2a1      	uxth	r1, r4
10100b4e:	4291      	cmp	r1, r2
10100b50:	d002      	beq.n	10100b58 <EFUSEWrite8+0x3c>
10100b52:	2000      	movs	r0, #0
10100b54:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
10100b58:	2101      	movs	r1, #1
10100b5a:	461a      	mov	r2, r3
10100b5c:	4608      	mov	r0, r1
10100b5e:	f7ff ff23 	bl	101009a8 <EFUSEPowerSwitch>
10100b62:	4f29      	ldr	r7, [pc, #164]	; (10100c08 <EFUSEWrite8+0xec>)
10100b64:	4829      	ldr	r0, [pc, #164]	; (10100c0c <EFUSEWrite8+0xf0>)
10100b66:	4a2a      	ldr	r2, [pc, #168]	; (10100c10 <EFUSEWrite8+0xf4>)
10100b68:	6839      	ldr	r1, [r7, #0]
10100b6a:	f046 4300 	orr.w	r3, r6, #2147483648	; 0x80000000
10100b6e:	ea00 2008 	and.w	r0, r0, r8, lsl #8
10100b72:	4303      	orrs	r3, r0
10100b74:	4022      	ands	r2, r4
10100b76:	4313      	orrs	r3, r2
10100b78:	f441 6280 	orr.w	r2, r1, #1024	; 0x400
10100b7c:	603a      	str	r2, [r7, #0]
10100b7e:	2014      	movs	r0, #20
10100b80:	602b      	str	r3, [r5, #0]
10100b82:	4e24      	ldr	r6, [pc, #144]	; (10100c14 <EFUSEWrite8+0xf8>)
10100b84:	47b0      	blx	r6
10100b86:	682b      	ldr	r3, [r5, #0]
10100b88:	2b00      	cmp	r3, #0
10100b8a:	da10      	bge.n	10100bae <EFUSEWrite8+0x92>
10100b8c:	2400      	movs	r4, #0
10100b8e:	f644 6720 	movw	r7, #20000	; 0x4e20
10100b92:	e001      	b.n	10100b98 <EFUSEWrite8+0x7c>
10100b94:	42bc      	cmp	r4, r7
10100b96:	d023      	beq.n	10100be0 <EFUSEWrite8+0xc4>
10100b98:	2005      	movs	r0, #5
10100b9a:	47b0      	blx	r6
10100b9c:	682b      	ldr	r3, [r5, #0]
10100b9e:	2b00      	cmp	r3, #0
10100ba0:	f104 0401 	add.w	r4, r4, #1
10100ba4:	dbf6      	blt.n	10100b94 <EFUSEWrite8+0x78>
10100ba6:	f644 6320 	movw	r3, #20000	; 0x4e20
10100baa:	429c      	cmp	r4, r3
10100bac:	d018      	beq.n	10100be0 <EFUSEWrite8+0xc4>
10100bae:	2401      	movs	r4, #1
10100bb0:	4a15      	ldr	r2, [pc, #84]	; (10100c08 <EFUSEWrite8+0xec>)
10100bb2:	6813      	ldr	r3, [r2, #0]
10100bb4:	f423 6380 	bic.w	r3, r3, #1024	; 0x400
10100bb8:	6013      	str	r3, [r2, #0]
10100bba:	f852 3c08 	ldr.w	r3, [r2, #-8]
10100bbe:	f423 437f 	bic.w	r3, r3, #65280	; 0xff00
10100bc2:	f842 3c08 	str.w	r3, [r2, #-8]
10100bc6:	f852 3c9c 	ldr.w	r3, [r2, #-156]
10100bca:	f023 0301 	bic.w	r3, r3, #1
10100bce:	f842 3c9c 	str.w	r3, [r2, #-156]
10100bd2:	20c8      	movs	r0, #200	; 0xc8
10100bd4:	47b0      	blx	r6
10100bd6:	4620      	mov	r0, r4
10100bd8:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
10100bdc:	4d09      	ldr	r5, [pc, #36]	; (10100c04 <EFUSEWrite8+0xe8>)
10100bde:	e7ae      	b.n	10100b3e <EFUSEWrite8+0x22>
10100be0:	4b0d      	ldr	r3, [pc, #52]	; (10100c18 <EFUSEWrite8+0xfc>)
10100be2:	6818      	ldr	r0, [r3, #0]
10100be4:	f410 3000 	ands.w	r0, r0, #131072	; 0x20000
10100be8:	bf08      	it	eq
10100bea:	4604      	moveq	r4, r0
10100bec:	d0e0      	beq.n	10100bb0 <EFUSEWrite8+0x94>
10100bee:	4641      	mov	r1, r8
10100bf0:	480a      	ldr	r0, [pc, #40]	; (10100c1c <EFUSEWrite8+0x100>)
10100bf2:	f7ff fbff 	bl	101003f4 <DiagPrintf>
10100bf6:	2400      	movs	r4, #0
10100bf8:	e7da      	b.n	10100bb0 <EFUSEWrite8+0x94>
10100bfa:	bf00      	nop
10100bfc:	101003f5 	.word	0x101003f5
10100c00:	50000810 	.word	0x50000810
10100c04:	480002e8 	.word	0x480002e8
10100c08:	480002ec 	.word	0x480002ec
10100c0c:	0003ff00 	.word	0x0003ff00
10100c10:	7ffc0000 	.word	0x7ffc0000
10100c14:	10100949 	.word	0x10100949
10100c18:	1000000c 	.word	0x1000000c
10100c1c:	101d40b0 	.word	0x101d40b0

10100c20 <EFUSE_PG_Packet>:
10100c20:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10100c24:	f001 070f 	and.w	r7, r1, #15
10100c28:	2f0f      	cmp	r7, #15
10100c2a:	b085      	sub	sp, #20
10100c2c:	d070      	beq.n	10100d10 <EFUSE_PG_Packet+0xf0>
10100c2e:	4d92      	ldr	r5, [pc, #584]	; (10100e78 <EFUSE_PG_Packet+0x258>)
10100c30:	68ab      	ldr	r3, [r5, #8]
10100c32:	f413 4300 	ands.w	r3, r3, #32768	; 0x8000
10100c36:	4616      	mov	r6, r2
10100c38:	4681      	mov	r9, r0
10100c3a:	4688      	mov	r8, r1
10100c3c:	f040 8094 	bne.w	10100d68 <EFUSE_PG_Packet+0x148>
10100c40:	f04f 0a00 	mov.w	sl, #0
10100c44:	4c8d      	ldr	r4, [pc, #564]	; (10100e7c <EFUSE_PG_Packet+0x25c>)
10100c46:	b94b      	cbnz	r3, 10100c5c <EFUSE_PG_Packet+0x3c>
10100c48:	f10a 0a01 	add.w	sl, sl, #1
10100c4c:	f1ba 0f08 	cmp.w	sl, #8
10100c50:	d00f      	beq.n	10100c72 <EFUSE_PG_Packet+0x52>
10100c52:	68ab      	ldr	r3, [r5, #8]
10100c54:	f403 4300 	and.w	r3, r3, #32768	; 0x8000
10100c58:	2b00      	cmp	r3, #0
10100c5a:	d0f5      	beq.n	10100c48 <EFUSE_PG_Packet+0x28>
10100c5c:	f816 200a 	ldrb.w	r2, [r6, sl]
10100c60:	4651      	mov	r1, sl
10100c62:	4620      	mov	r0, r4
10100c64:	f10a 0a01 	add.w	sl, sl, #1
10100c68:	f7ff fbc4 	bl	101003f4 <DiagPrintf>
10100c6c:	f1ba 0f08 	cmp.w	sl, #8
10100c70:	d1ef      	bne.n	10100c52 <EFUSE_PG_Packet+0x32>
10100c72:	2400      	movs	r4, #0
10100c74:	2307      	movs	r3, #7
10100c76:	f10d 020e 	add.w	r2, sp, #14
10100c7a:	4621      	mov	r1, r4
10100c7c:	2000      	movs	r0, #0
10100c7e:	f7ff fed7 	bl	10100a30 <EFUSERead8>
10100c82:	f89d 300e 	ldrb.w	r3, [sp, #14]
10100c86:	2bff      	cmp	r3, #255	; 0xff
10100c88:	d010      	beq.n	10100cac <EFUSE_PG_Packet+0x8c>
10100c8a:	f003 020f 	and.w	r2, r3, #15
10100c8e:	2a0f      	cmp	r2, #15
10100c90:	d042      	beq.n	10100d18 <EFUSE_PG_Packet+0xf8>
10100c92:	43db      	mvns	r3, r3
10100c94:	f013 030f 	ands.w	r3, r3, #15
10100c98:	d004      	beq.n	10100ca4 <EFUSE_PG_Packet+0x84>
10100c9a:	07d8      	lsls	r0, r3, #31
10100c9c:	bf48      	it	mi
10100c9e:	3402      	addmi	r4, #2
10100ca0:	085b      	lsrs	r3, r3, #1
10100ca2:	d1fa      	bne.n	10100c9a <EFUSE_PG_Packet+0x7a>
10100ca4:	3401      	adds	r4, #1
10100ca6:	f5b4 7f8f 	cmp.w	r4, #286	; 0x11e
10100caa:	d3e3      	bcc.n	10100c74 <EFUSE_PG_Packet+0x54>
10100cac:	f018 0f01 	tst.w	r8, #1
10100cb0:	bf0c      	ite	eq
10100cb2:	f04f 0a02 	moveq.w	sl, #2
10100cb6:	f04f 0a00 	movne.w	sl, #0
10100cba:	f018 0f02 	tst.w	r8, #2
10100cbe:	bf08      	it	eq
10100cc0:	f10a 0a02 	addeq.w	sl, sl, #2
10100cc4:	68ab      	ldr	r3, [r5, #8]
10100cc6:	f018 0f04 	tst.w	r8, #4
10100cca:	bf08      	it	eq
10100ccc:	f10a 0a02 	addeq.w	sl, sl, #2
10100cd0:	f018 0f08 	tst.w	r8, #8
10100cd4:	bf08      	it	eq
10100cd6:	f10a 0a02 	addeq.w	sl, sl, #2
10100cda:	0419      	lsls	r1, r3, #16
10100cdc:	d43d      	bmi.n	10100d5a <EFUSE_PG_Packet+0x13a>
10100cde:	eb0a 0304 	add.w	r3, sl, r4
10100ce2:	f5b3 7f8f 	cmp.w	r3, #286	; 0x11e
10100ce6:	d22f      	bcs.n	10100d48 <EFUSE_PG_Packet+0x128>
10100ce8:	f1b9 0f0e 	cmp.w	r9, #14
10100cec:	68ab      	ldr	r3, [r5, #8]
10100cee:	d944      	bls.n	10100d7a <EFUSE_PG_Packet+0x15a>
10100cf0:	ea4f 1849 	mov.w	r8, r9, lsl #5
10100cf4:	041a      	lsls	r2, r3, #16
10100cf6:	f048 080f 	orr.w	r8, r8, #15
10100cfa:	f100 8099 	bmi.w	10100e30 <EFUSE_PG_Packet+0x210>
10100cfe:	f008 02ef 	and.w	r2, r8, #239	; 0xef
10100d02:	2307      	movs	r3, #7
10100d04:	4621      	mov	r1, r4
10100d06:	2000      	movs	r0, #0
10100d08:	f7ff ff08 	bl	10100b1c <EFUSEWrite8>
10100d0c:	2801      	cmp	r0, #1
10100d0e:	d074      	beq.n	10100dfa <EFUSE_PG_Packet+0x1da>
10100d10:	2000      	movs	r0, #0
10100d12:	b005      	add	sp, #20
10100d14:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10100d18:	3401      	adds	r4, #1
10100d1a:	2307      	movs	r3, #7
10100d1c:	4621      	mov	r1, r4
10100d1e:	f10d 020f 	add.w	r2, sp, #15
10100d22:	2000      	movs	r0, #0
10100d24:	f7ff fe84 	bl	10100a30 <EFUSERead8>
10100d28:	f89d 300f 	ldrb.w	r3, [sp, #15]
10100d2c:	43db      	mvns	r3, r3
10100d2e:	f013 030f 	ands.w	r3, r3, #15
10100d32:	d0b7      	beq.n	10100ca4 <EFUSE_PG_Packet+0x84>
10100d34:	07da      	lsls	r2, r3, #31
10100d36:	bf48      	it	mi
10100d38:	3402      	addmi	r4, #2
10100d3a:	085b      	lsrs	r3, r3, #1
10100d3c:	d1fa      	bne.n	10100d34 <EFUSE_PG_Packet+0x114>
10100d3e:	3401      	adds	r4, #1
10100d40:	f5b4 7f8f 	cmp.w	r4, #286	; 0x11e
10100d44:	d396      	bcc.n	10100c74 <EFUSE_PG_Packet+0x54>
10100d46:	e7b1      	b.n	10100cac <EFUSE_PG_Packet+0x8c>
10100d48:	682b      	ldr	r3, [r5, #0]
10100d4a:	041b      	lsls	r3, r3, #16
10100d4c:	d5e0      	bpl.n	10100d10 <EFUSE_PG_Packet+0xf0>
10100d4e:	4652      	mov	r2, sl
10100d50:	4621      	mov	r1, r4
10100d52:	484b      	ldr	r0, [pc, #300]	; (10100e80 <EFUSE_PG_Packet+0x260>)
10100d54:	f7ff fb4e 	bl	101003f4 <DiagPrintf>
10100d58:	e7da      	b.n	10100d10 <EFUSE_PG_Packet+0xf0>
10100d5a:	463b      	mov	r3, r7
10100d5c:	4652      	mov	r2, sl
10100d5e:	4949      	ldr	r1, [pc, #292]	; (10100e84 <EFUSE_PG_Packet+0x264>)
10100d60:	4849      	ldr	r0, [pc, #292]	; (10100e88 <EFUSE_PG_Packet+0x268>)
10100d62:	f7ff fb47 	bl	101003f4 <DiagPrintf>
10100d66:	e7ba      	b.n	10100cde <EFUSE_PG_Packet+0xbe>
10100d68:	460a      	mov	r2, r1
10100d6a:	4601      	mov	r1, r0
10100d6c:	4847      	ldr	r0, [pc, #284]	; (10100e8c <EFUSE_PG_Packet+0x26c>)
10100d6e:	f7ff fb41 	bl	101003f4 <DiagPrintf>
10100d72:	68ab      	ldr	r3, [r5, #8]
10100d74:	f403 4300 	and.w	r3, r3, #32768	; 0x8000
10100d78:	e762      	b.n	10100c40 <EFUSE_PG_Packet+0x20>
10100d7a:	0418      	lsls	r0, r3, #16
10100d7c:	ea47 1909 	orr.w	r9, r7, r9, lsl #4
10100d80:	d44f      	bmi.n	10100e22 <EFUSE_PG_Packet+0x202>
10100d82:	fa5f f289 	uxtb.w	r2, r9
10100d86:	2307      	movs	r3, #7
10100d88:	4621      	mov	r1, r4
10100d8a:	2000      	movs	r0, #0
10100d8c:	f7ff fec6 	bl	10100b1c <EFUSEWrite8>
10100d90:	2801      	cmp	r0, #1
10100d92:	d1bd      	bne.n	10100d10 <EFUSE_PG_Packet+0xf0>
10100d94:	3401      	adds	r4, #1
10100d96:	f04f 0800 	mov.w	r8, #0
10100d9a:	f8df b0e8 	ldr.w	fp, [pc, #232]	; 10100e84 <EFUSE_PG_Packet+0x264>
10100d9e:	46b1      	mov	r9, r6
10100da0:	3601      	adds	r6, #1
10100da2:	fa47 f308 	asr.w	r3, r7, r8
10100da6:	f013 0f01 	tst.w	r3, #1
10100daa:	f104 0a01 	add.w	sl, r4, #1
10100dae:	d117      	bne.n	10100de0 <EFUSE_PG_Packet+0x1c0>
10100db0:	68ab      	ldr	r3, [r5, #8]
10100db2:	0419      	lsls	r1, r3, #16
10100db4:	d44d      	bmi.n	10100e52 <EFUSE_PG_Packet+0x232>
10100db6:	2307      	movs	r3, #7
10100db8:	f899 2000 	ldrb.w	r2, [r9]
10100dbc:	4621      	mov	r1, r4
10100dbe:	2000      	movs	r0, #0
10100dc0:	f7ff feac 	bl	10100b1c <EFUSEWrite8>
10100dc4:	2801      	cmp	r0, #1
10100dc6:	d1a3      	bne.n	10100d10 <EFUSE_PG_Packet+0xf0>
10100dc8:	68ab      	ldr	r3, [r5, #8]
10100dca:	041a      	lsls	r2, r3, #16
10100dcc:	d437      	bmi.n	10100e3e <EFUSE_PG_Packet+0x21e>
10100dce:	4651      	mov	r1, sl
10100dd0:	2307      	movs	r3, #7
10100dd2:	7832      	ldrb	r2, [r6, #0]
10100dd4:	2000      	movs	r0, #0
10100dd6:	f7ff fea1 	bl	10100b1c <EFUSEWrite8>
10100dda:	2801      	cmp	r0, #1
10100ddc:	d198      	bne.n	10100d10 <EFUSE_PG_Packet+0xf0>
10100dde:	3402      	adds	r4, #2
10100de0:	f108 0801 	add.w	r8, r8, #1
10100de4:	f1b8 0f04 	cmp.w	r8, #4
10100de8:	f106 0602 	add.w	r6, r6, #2
10100dec:	f109 0902 	add.w	r9, r9, #2
10100df0:	d1d7      	bne.n	10100da2 <EFUSE_PG_Packet+0x182>
10100df2:	2001      	movs	r0, #1
10100df4:	b005      	add	sp, #20
10100df6:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10100dfa:	68ab      	ldr	r3, [r5, #8]
10100dfc:	041b      	lsls	r3, r3, #16
10100dfe:	f104 0801 	add.w	r8, r4, #1
10100e02:	ea4f 0949 	mov.w	r9, r9, lsl #1
10100e06:	d42e      	bmi.n	10100e66 <EFUSE_PG_Packet+0x246>
10100e08:	f009 02f0 	and.w	r2, r9, #240	; 0xf0
10100e0c:	433a      	orrs	r2, r7
10100e0e:	4641      	mov	r1, r8
10100e10:	2307      	movs	r3, #7
10100e12:	2000      	movs	r0, #0
10100e14:	f7ff fe82 	bl	10100b1c <EFUSEWrite8>
10100e18:	2801      	cmp	r0, #1
10100e1a:	f47f af79 	bne.w	10100d10 <EFUSE_PG_Packet+0xf0>
10100e1e:	3402      	adds	r4, #2
10100e20:	e7b9      	b.n	10100d96 <EFUSE_PG_Packet+0x176>
10100e22:	464b      	mov	r3, r9
10100e24:	4622      	mov	r2, r4
10100e26:	4917      	ldr	r1, [pc, #92]	; (10100e84 <EFUSE_PG_Packet+0x264>)
10100e28:	4819      	ldr	r0, [pc, #100]	; (10100e90 <EFUSE_PG_Packet+0x270>)
10100e2a:	f7ff fae3 	bl	101003f4 <DiagPrintf>
10100e2e:	e7a8      	b.n	10100d82 <EFUSE_PG_Packet+0x162>
10100e30:	4643      	mov	r3, r8
10100e32:	4622      	mov	r2, r4
10100e34:	4913      	ldr	r1, [pc, #76]	; (10100e84 <EFUSE_PG_Packet+0x264>)
10100e36:	4816      	ldr	r0, [pc, #88]	; (10100e90 <EFUSE_PG_Packet+0x270>)
10100e38:	f7ff fadc 	bl	101003f4 <DiagPrintf>
10100e3c:	e75f      	b.n	10100cfe <EFUSE_PG_Packet+0xde>
10100e3e:	f899 3001 	ldrb.w	r3, [r9, #1]
10100e42:	4652      	mov	r2, sl
10100e44:	f8cd 8000 	str.w	r8, [sp]
10100e48:	4659      	mov	r1, fp
10100e4a:	4812      	ldr	r0, [pc, #72]	; (10100e94 <EFUSE_PG_Packet+0x274>)
10100e4c:	f7ff fad2 	bl	101003f4 <DiagPrintf>
10100e50:	e7bd      	b.n	10100dce <EFUSE_PG_Packet+0x1ae>
10100e52:	f816 3c01 	ldrb.w	r3, [r6, #-1]
10100e56:	4622      	mov	r2, r4
10100e58:	f8cd 8000 	str.w	r8, [sp]
10100e5c:	4659      	mov	r1, fp
10100e5e:	480d      	ldr	r0, [pc, #52]	; (10100e94 <EFUSE_PG_Packet+0x274>)
10100e60:	f7ff fac8 	bl	101003f4 <DiagPrintf>
10100e64:	e7a7      	b.n	10100db6 <EFUSE_PG_Packet+0x196>
10100e66:	f009 03f0 	and.w	r3, r9, #240	; 0xf0
10100e6a:	433b      	orrs	r3, r7
10100e6c:	4642      	mov	r2, r8
10100e6e:	4905      	ldr	r1, [pc, #20]	; (10100e84 <EFUSE_PG_Packet+0x264>)
10100e70:	4807      	ldr	r0, [pc, #28]	; (10100e90 <EFUSE_PG_Packet+0x270>)
10100e72:	f7ff fabf 	bl	101003f4 <DiagPrintf>
10100e76:	e7c7      	b.n	10100e08 <EFUSE_PG_Packet+0x1e8>
10100e78:	1000000c 	.word	0x1000000c
10100e7c:	101d410c 	.word	0x101d410c
10100e80:	101d41e4 	.word	0x101d41e4
10100e84:	101d4f78 	.word	0x101d4f78
10100e88:	101d4140 	.word	0x101d4140
10100e8c:	101d40c8 	.word	0x101d40c8
10100e90:	101d4178 	.word	0x101d4178
10100e94:	101d41a0 	.word	0x101d41a0

10100e98 <EFUSE_LogicalMap_Read>:
10100e98:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10100e9c:	f44f 6280 	mov.w	r2, #1024	; 0x400
10100ea0:	b083      	sub	sp, #12
10100ea2:	21ff      	movs	r1, #255	; 0xff
10100ea4:	4b3d      	ldr	r3, [pc, #244]	; (10100f9c <EFUSE_LogicalMap_Read+0x104>)
10100ea6:	4682      	mov	sl, r0
10100ea8:	f04f 0800 	mov.w	r8, #0
10100eac:	4798      	blx	r3
10100eae:	f8df b0f4 	ldr.w	fp, [pc, #244]	; 10100fa4 <EFUSE_LogicalMap_Read+0x10c>
10100eb2:	4641      	mov	r1, r8
10100eb4:	2307      	movs	r3, #7
10100eb6:	f10d 0205 	add.w	r2, sp, #5
10100eba:	2000      	movs	r0, #0
10100ebc:	f7ff fdb8 	bl	10100a30 <EFUSERead8>
10100ec0:	f89d 5005 	ldrb.w	r5, [sp, #5]
10100ec4:	2dff      	cmp	r5, #255	; 0xff
10100ec6:	f108 0101 	add.w	r1, r8, #1
10100eca:	d05c      	beq.n	10100f86 <EFUSE_LogicalMap_Read+0xee>
10100ecc:	f005 031f 	and.w	r3, r5, #31
10100ed0:	2b0f      	cmp	r3, #15
10100ed2:	d03a      	beq.n	10100f4a <EFUSE_LogicalMap_Read+0xb2>
10100ed4:	4688      	mov	r8, r1
10100ed6:	092c      	lsrs	r4, r5, #4
10100ed8:	f005 050f 	and.w	r5, r5, #15
10100edc:	2600      	movs	r6, #0
10100ede:	2701      	movs	r7, #1
10100ee0:	00e4      	lsls	r4, r4, #3
10100ee2:	fa07 f006 	lsl.w	r0, r7, r6
10100ee6:	ea10 0905 	ands.w	r9, r0, r5
10100eea:	f106 0601 	add.w	r6, r6, #1
10100eee:	d00a      	beq.n	10100f06 <EFUSE_LogicalMap_Read+0x6e>
10100ef0:	3402      	adds	r4, #2
10100ef2:	2e04      	cmp	r6, #4
10100ef4:	b2a4      	uxth	r4, r4
10100ef6:	d1f4      	bne.n	10100ee2 <EFUSE_LogicalMap_Read+0x4a>
10100ef8:	f5b8 7f8f 	cmp.w	r8, #286	; 0x11e
10100efc:	d3d9      	bcc.n	10100eb2 <EFUSE_LogicalMap_Read+0x1a>
10100efe:	2001      	movs	r0, #1
10100f00:	b003      	add	sp, #12
10100f02:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10100f06:	4641      	mov	r1, r8
10100f08:	f10d 0207 	add.w	r2, sp, #7
10100f0c:	2307      	movs	r3, #7
10100f0e:	4648      	mov	r0, r9
10100f10:	f7ff fd8e 	bl	10100a30 <EFUSERead8>
10100f14:	f89d 3007 	ldrb.w	r3, [sp, #7]
10100f18:	f108 0101 	add.w	r1, r8, #1
10100f1c:	4648      	mov	r0, r9
10100f1e:	f80a 3004 	strb.w	r3, [sl, r4]
10100f22:	f10d 0207 	add.w	r2, sp, #7
10100f26:	2307      	movs	r3, #7
10100f28:	f7ff fd82 	bl	10100a30 <EFUSERead8>
10100f2c:	2c10      	cmp	r4, #16
10100f2e:	f108 0802 	add.w	r8, r8, #2
10100f32:	eb0a 0904 	add.w	r9, sl, r4
10100f36:	d803      	bhi.n	10100f40 <EFUSE_LogicalMap_Read+0xa8>
10100f38:	f8db 3008 	ldr.w	r3, [fp, #8]
10100f3c:	041b      	lsls	r3, r3, #16
10100f3e:	d419      	bmi.n	10100f74 <EFUSE_LogicalMap_Read+0xdc>
10100f40:	f89d 3007 	ldrb.w	r3, [sp, #7]
10100f44:	f889 3001 	strb.w	r3, [r9, #1]
10100f48:	e7d2      	b.n	10100ef0 <EFUSE_LogicalMap_Read+0x58>
10100f4a:	2307      	movs	r3, #7
10100f4c:	f10d 0206 	add.w	r2, sp, #6
10100f50:	2000      	movs	r0, #0
10100f52:	f7ff fd6d 	bl	10100a30 <EFUSERead8>
10100f56:	f89d 3006 	ldrb.w	r3, [sp, #6]
10100f5a:	f003 020f 	and.w	r2, r3, #15
10100f5e:	2a0f      	cmp	r2, #15
10100f60:	f108 0802 	add.w	r8, r8, #2
10100f64:	d0c8      	beq.n	10100ef8 <EFUSE_LogicalMap_Read+0x60>
10100f66:	105c      	asrs	r4, r3, #1
10100f68:	f004 0478 	and.w	r4, r4, #120	; 0x78
10100f6c:	ea44 1455 	orr.w	r4, r4, r5, lsr #5
10100f70:	4615      	mov	r5, r2
10100f72:	e7b3      	b.n	10100edc <EFUSE_LogicalMap_Read+0x44>
10100f74:	f89d 3007 	ldrb.w	r3, [sp, #7]
10100f78:	f899 2000 	ldrb.w	r2, [r9]
10100f7c:	4621      	mov	r1, r4
10100f7e:	4808      	ldr	r0, [pc, #32]	; (10100fa0 <EFUSE_LogicalMap_Read+0x108>)
10100f80:	f7ff fa38 	bl	101003f4 <DiagPrintf>
10100f84:	e7dc      	b.n	10100f40 <EFUSE_LogicalMap_Read+0xa8>
10100f86:	4b07      	ldr	r3, [pc, #28]	; (10100fa4 <EFUSE_LogicalMap_Read+0x10c>)
10100f88:	689b      	ldr	r3, [r3, #8]
10100f8a:	041a      	lsls	r2, r3, #16
10100f8c:	d5b7      	bpl.n	10100efe <EFUSE_LogicalMap_Read+0x66>
10100f8e:	4806      	ldr	r0, [pc, #24]	; (10100fa8 <EFUSE_LogicalMap_Read+0x110>)
10100f90:	f7ff fa30 	bl	101003f4 <DiagPrintf>
10100f94:	2001      	movs	r0, #1
10100f96:	b003      	add	sp, #12
10100f98:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10100f9c:	10106e89 	.word	0x10106e89
10100fa0:	101d4268 	.word	0x101d4268
10100fa4:	1000000c 	.word	0x1000000c
10100fa8:	101d421c 	.word	0x101d421c

10100fac <EFUSE_LogicalMap_Write>:
10100fac:	1843      	adds	r3, r0, r1
10100fae:	f5b3 6f80 	cmp.w	r3, #1024	; 0x400
10100fb2:	d901      	bls.n	10100fb8 <EFUSE_LogicalMap_Write+0xc>
10100fb4:	2000      	movs	r0, #0
10100fb6:	4770      	bx	lr
10100fb8:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10100fbc:	f2ad 4d1c 	subw	sp, sp, #1052	; 0x41c
10100fc0:	9003      	str	r0, [sp, #12]
10100fc2:	a806      	add	r0, sp, #24
10100fc4:	9202      	str	r2, [sp, #8]
10100fc6:	460f      	mov	r7, r1
10100fc8:	f7ff ff66 	bl	10100e98 <EFUSE_LogicalMap_Read>
10100fcc:	4680      	mov	r8, r0
10100fce:	b920      	cbnz	r0, 10100fda <EFUSE_LogicalMap_Write+0x2e>
10100fd0:	2000      	movs	r0, #0
10100fd2:	f20d 4d1c 	addw	sp, sp, #1052	; 0x41c
10100fd6:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10100fda:	f10d 0a10 	add.w	sl, sp, #16
10100fde:	2208      	movs	r2, #8
10100fe0:	21ff      	movs	r1, #255	; 0xff
10100fe2:	4650      	mov	r0, sl
10100fe4:	4b63      	ldr	r3, [pc, #396]	; (10101174 <EFUSE_LogicalMap_Write+0x1c8>)
10100fe6:	4798      	blx	r3
10100fe8:	9a03      	ldr	r2, [sp, #12]
10100fea:	f012 0401 	ands.w	r4, r2, #1
10100fee:	ea4f 09d2 	mov.w	r9, r2, lsr #3
10100ff2:	f002 0507 	and.w	r5, r2, #7
10100ff6:	4611      	mov	r1, r2
10100ff8:	f000 809f 	beq.w	1010113a <EFUSE_LogicalMap_Write+0x18e>
10100ffc:	9b02      	ldr	r3, [sp, #8]
10100ffe:	aa06      	add	r2, sp, #24
10101000:	781b      	ldrb	r3, [r3, #0]
10101002:	5c52      	ldrb	r2, [r2, r1]
10101004:	429a      	cmp	r2, r3
10101006:	f000 80b3 	beq.w	10101170 <EFUSE_LogicalMap_Write+0x1c4>
1010100a:	2601      	movs	r6, #1
1010100c:	fa25 f206 	lsr.w	r2, r5, r6
10101010:	4096      	lsls	r6, r2
10101012:	43f6      	mvns	r6, r6
10101014:	4a58      	ldr	r2, [pc, #352]	; (10101178 <EFUSE_LogicalMap_Write+0x1cc>)
10101016:	ac06      	add	r4, sp, #24
10101018:	1861      	adds	r1, r4, r1
1010101a:	f811 0c01 	ldrb.w	r0, [r1, #-1]
1010101e:	6892      	ldr	r2, [r2, #8]
10101020:	1e69      	subs	r1, r5, #1
10101022:	f80a 0001 	strb.w	r0, [sl, r1]
10101026:	0410      	lsls	r0, r2, #16
10101028:	f006 060f 	and.w	r6, r6, #15
1010102c:	f80a 3005 	strb.w	r3, [sl, r5]
10101030:	f100 8098 	bmi.w	10101164 <EFUSE_LogicalMap_Write+0x1b8>
10101034:	2401      	movs	r4, #1
10101036:	3501      	adds	r5, #1
10101038:	2d07      	cmp	r5, #7
1010103a:	f8df b13c 	ldr.w	fp, [pc, #316]	; 10101178 <EFUSE_LogicalMap_Write+0x1cc>
1010103e:	d824      	bhi.n	1010108a <EFUSE_LogicalMap_Write+0xde>
10101040:	42bc      	cmp	r4, r7
10101042:	d040      	beq.n	101010c6 <EFUSE_LogicalMap_Write+0x11a>
10101044:	1b3a      	subs	r2, r7, r4
10101046:	9b03      	ldr	r3, [sp, #12]
10101048:	2a01      	cmp	r2, #1
1010104a:	4423      	add	r3, r4
1010104c:	d04c      	beq.n	101010e8 <EFUSE_LogicalMap_Write+0x13c>
1010104e:	9802      	ldr	r0, [sp, #8]
10101050:	aa06      	add	r2, sp, #24
10101052:	5cd1      	ldrb	r1, [r2, r3]
10101054:	5d02      	ldrb	r2, [r0, r4]
10101056:	4291      	cmp	r1, r2
10101058:	d05e      	beq.n	10101118 <EFUSE_LogicalMap_Write+0x16c>
1010105a:	4603      	mov	r3, r0
1010105c:	4423      	add	r3, r4
1010105e:	785b      	ldrb	r3, [r3, #1]
10101060:	2101      	movs	r1, #1
10101062:	fa25 f001 	lsr.w	r0, r5, r1
10101066:	4081      	lsls	r1, r0
10101068:	f8db 0008 	ldr.w	r0, [fp, #8]
1010106c:	f80a 2005 	strb.w	r2, [sl, r5]
10101070:	0400      	lsls	r0, r0, #16
10101072:	eb0a 0205 	add.w	r2, sl, r5
10101076:	ea26 0601 	bic.w	r6, r6, r1
1010107a:	7053      	strb	r3, [r2, #1]
1010107c:	d455      	bmi.n	1010112a <EFUSE_LogicalMap_Write+0x17e>
1010107e:	3402      	adds	r4, #2
10101080:	42a7      	cmp	r7, r4
10101082:	d020      	beq.n	101010c6 <EFUSE_LogicalMap_Write+0x11a>
10101084:	3502      	adds	r5, #2
10101086:	2d07      	cmp	r5, #7
10101088:	d9da      	bls.n	10101040 <EFUSE_LogicalMap_Write+0x94>
1010108a:	2e0f      	cmp	r6, #15
1010108c:	d00c      	beq.n	101010a8 <EFUSE_LogicalMap_Write+0xfc>
1010108e:	f8db 3008 	ldr.w	r3, [fp, #8]
10101092:	0419      	lsls	r1, r3, #16
10101094:	d41b      	bmi.n	101010ce <EFUSE_LogicalMap_Write+0x122>
10101096:	b2f1      	uxtb	r1, r6
10101098:	4652      	mov	r2, sl
1010109a:	fa5f f089 	uxtb.w	r0, r9
1010109e:	f7ff fdbf 	bl	10100c20 <EFUSE_PG_Packet>
101010a2:	4680      	mov	r8, r0
101010a4:	2800      	cmp	r0, #0
101010a6:	d04a      	beq.n	1010113e <EFUSE_LogicalMap_Write+0x192>
101010a8:	42a7      	cmp	r7, r4
101010aa:	d00e      	beq.n	101010ca <EFUSE_LogicalMap_Write+0x11e>
101010ac:	2208      	movs	r2, #8
101010ae:	21ff      	movs	r1, #255	; 0xff
101010b0:	4650      	mov	r0, sl
101010b2:	4b30      	ldr	r3, [pc, #192]	; (10101174 <EFUSE_LogicalMap_Write+0x1c8>)
101010b4:	4798      	blx	r3
101010b6:	42bc      	cmp	r4, r7
101010b8:	f109 0901 	add.w	r9, r9, #1
101010bc:	f04f 0500 	mov.w	r5, #0
101010c0:	f04f 060f 	mov.w	r6, #15
101010c4:	d1be      	bne.n	10101044 <EFUSE_LogicalMap_Write+0x98>
101010c6:	2e0f      	cmp	r6, #15
101010c8:	d1e1      	bne.n	1010108e <EFUSE_LogicalMap_Write+0xe2>
101010ca:	4640      	mov	r0, r8
101010cc:	e781      	b.n	10100fd2 <EFUSE_LogicalMap_Write+0x26>
101010ce:	4649      	mov	r1, r9
101010d0:	482a      	ldr	r0, [pc, #168]	; (1010117c <EFUSE_LogicalMap_Write+0x1d0>)
101010d2:	f7ff f98f 	bl	101003f4 <DiagPrintf>
101010d6:	f8db 3008 	ldr.w	r3, [fp, #8]
101010da:	041a      	lsls	r2, r3, #16
101010dc:	d5db      	bpl.n	10101096 <EFUSE_LogicalMap_Write+0xea>
101010de:	4631      	mov	r1, r6
101010e0:	4827      	ldr	r0, [pc, #156]	; (10101180 <EFUSE_LogicalMap_Write+0x1d4>)
101010e2:	f7ff f987 	bl	101003f4 <DiagPrintf>
101010e6:	e7d6      	b.n	10101096 <EFUSE_LogicalMap_Write+0xea>
101010e8:	a906      	add	r1, sp, #24
101010ea:	5cc8      	ldrb	r0, [r1, r3]
101010ec:	9902      	ldr	r1, [sp, #8]
101010ee:	5d09      	ldrb	r1, [r1, r4]
101010f0:	4288      	cmp	r0, r1
101010f2:	d00f      	beq.n	10101114 <EFUSE_LogicalMap_Write+0x168>
101010f4:	a806      	add	r0, sp, #24
101010f6:	4403      	add	r3, r0
101010f8:	0868      	lsrs	r0, r5, #1
101010fa:	4082      	lsls	r2, r0
101010fc:	f8db 0008 	ldr.w	r0, [fp, #8]
10101100:	785b      	ldrb	r3, [r3, #1]
10101102:	f80a 1005 	strb.w	r1, [sl, r5]
10101106:	ea26 0602 	bic.w	r6, r6, r2
1010110a:	eb0a 0105 	add.w	r1, sl, r5
1010110e:	0402      	lsls	r2, r0, #16
10101110:	704b      	strb	r3, [r1, #1]
10101112:	d41f      	bmi.n	10101154 <EFUSE_LogicalMap_Write+0x1a8>
10101114:	3401      	adds	r4, #1
10101116:	e7b8      	b.n	1010108a <EFUSE_LogicalMap_Write+0xde>
10101118:	a906      	add	r1, sp, #24
1010111a:	440b      	add	r3, r1
1010111c:	9902      	ldr	r1, [sp, #8]
1010111e:	4421      	add	r1, r4
10101120:	7858      	ldrb	r0, [r3, #1]
10101122:	784b      	ldrb	r3, [r1, #1]
10101124:	4298      	cmp	r0, r3
10101126:	d19b      	bne.n	10101060 <EFUSE_LogicalMap_Write+0xb4>
10101128:	e7a9      	b.n	1010107e <EFUSE_LogicalMap_Write+0xd2>
1010112a:	f81a 2005 	ldrb.w	r2, [sl, r5]
1010112e:	4629      	mov	r1, r5
10101130:	9600      	str	r6, [sp, #0]
10101132:	4814      	ldr	r0, [pc, #80]	; (10101184 <EFUSE_LogicalMap_Write+0x1d8>)
10101134:	f7ff f95e 	bl	101003f4 <DiagPrintf>
10101138:	e7a1      	b.n	1010107e <EFUSE_LogicalMap_Write+0xd2>
1010113a:	260f      	movs	r6, #15
1010113c:	e77c      	b.n	10101038 <EFUSE_LogicalMap_Write+0x8c>
1010113e:	f8db 3000 	ldr.w	r3, [fp]
10101142:	039b      	lsls	r3, r3, #14
10101144:	f57f af44 	bpl.w	10100fd0 <EFUSE_LogicalMap_Write+0x24>
10101148:	4621      	mov	r1, r4
1010114a:	480f      	ldr	r0, [pc, #60]	; (10101188 <EFUSE_LogicalMap_Write+0x1dc>)
1010114c:	f7ff f952 	bl	101003f4 <DiagPrintf>
10101150:	4640      	mov	r0, r8
10101152:	e73e      	b.n	10100fd2 <EFUSE_LogicalMap_Write+0x26>
10101154:	f81a 2005 	ldrb.w	r2, [sl, r5]
10101158:	4629      	mov	r1, r5
1010115a:	9600      	str	r6, [sp, #0]
1010115c:	480b      	ldr	r0, [pc, #44]	; (1010118c <EFUSE_LogicalMap_Write+0x1e0>)
1010115e:	f7ff f949 	bl	101003f4 <DiagPrintf>
10101162:	e7d7      	b.n	10101114 <EFUSE_LogicalMap_Write+0x168>
10101164:	f81a 2001 	ldrb.w	r2, [sl, r1]
10101168:	4809      	ldr	r0, [pc, #36]	; (10101190 <EFUSE_LogicalMap_Write+0x1e4>)
1010116a:	f7ff f943 	bl	101003f4 <DiagPrintf>
1010116e:	e761      	b.n	10101034 <EFUSE_LogicalMap_Write+0x88>
10101170:	260f      	movs	r6, #15
10101172:	e75f      	b.n	10101034 <EFUSE_LogicalMap_Write+0x88>
10101174:	10106e89 	.word	0x10106e89
10101178:	1000000c 	.word	0x1000000c
1010117c:	101d4314 	.word	0x101d4314
10101180:	101d433c 	.word	0x101d433c
10101184:	101d42e8 	.word	0x101d42e8
10101188:	101d4364 	.word	0x101d4364
1010118c:	101d42bc 	.word	0x101d42bc
10101190:	101d4290 	.word	0x101d4290

10101194 <FLASH_RxData>:
10101194:	b5f0      	push	{r4, r5, r6, r7, lr}
10101196:	4f3f      	ldr	r7, [pc, #252]	; (10101294 <FLASH_RxData+0x100>)
10101198:	b900      	cbnz	r0, 1010119c <FLASH_RxData+0x8>
1010119a:	7a38      	ldrb	r0, [r7, #8]
1010119c:	f04f 0e00 	mov.w	lr, #0
101011a0:	4c3d      	ldr	r4, [pc, #244]	; (10101298 <FLASH_RxData+0x104>)
101011a2:	f8c4 e008 	str.w	lr, [r4, #8]
101011a6:	6826      	ldr	r6, [r4, #0]
101011a8:	b295      	uxth	r5, r2
101011aa:	f446 7640 	orr.w	r6, r6, #768	; 0x300
101011ae:	6026      	str	r6, [r4, #0]
101011b0:	6065      	str	r5, [r4, #4]
101011b2:	f897 605a 	ldrb.w	r6, [r7, #90]	; 0x5a
101011b6:	2e00      	cmp	r6, #0
101011b8:	d03a      	beq.n	10101230 <FLASH_RxData+0x9c>
101011ba:	f897 5059 	ldrb.w	r5, [r7, #89]	; 0x59
101011be:	2d03      	cmp	r5, #3
101011c0:	d047      	beq.n	10101252 <FLASH_RxData+0xbe>
101011c2:	2d00      	cmp	r5, #0
101011c4:	d160      	bne.n	10101288 <FLASH_RxData+0xf4>
101011c6:	2701      	movs	r7, #1
101011c8:	f04f 0e04 	mov.w	lr, #4
101011cc:	f8c4 e118 	str.w	lr, [r4, #280]	; 0x118
101011d0:	6127      	str	r7, [r4, #16]
101011d2:	61e5      	str	r5, [r4, #28]
101011d4:	0e0f      	lsrs	r7, r1, #24
101011d6:	0c0d      	lsrs	r5, r1, #16
101011d8:	0a0c      	lsrs	r4, r1, #8
101011da:	022d      	lsls	r5, r5, #8
101011dc:	f405 457f 	and.w	r5, r5, #65280	; 0xff00
101011e0:	0424      	lsls	r4, r4, #16
101011e2:	ea47 6101 	orr.w	r1, r7, r1, lsl #24
101011e6:	4329      	orrs	r1, r5
101011e8:	f404 057f 	and.w	r5, r4, #16711680	; 0xff0000
101011ec:	4c2a      	ldr	r4, [pc, #168]	; (10101298 <FLASH_RxData+0x104>)
101011ee:	430d      	orrs	r5, r1
101011f0:	f884 0060 	strb.w	r0, [r4, #96]	; 0x60
101011f4:	6625      	str	r5, [r4, #96]	; 0x60
101011f6:	b11e      	cbz	r6, 10101200 <FLASH_RxData+0x6c>
101011f8:	2000      	movs	r0, #0
101011fa:	4927      	ldr	r1, [pc, #156]	; (10101298 <FLASH_RxData+0x104>)
101011fc:	f881 0060 	strb.w	r0, [r1, #96]	; 0x60
10101200:	4925      	ldr	r1, [pc, #148]	; (10101298 <FLASH_RxData+0x104>)
10101202:	2401      	movs	r4, #1
10101204:	4608      	mov	r0, r1
10101206:	608c      	str	r4, [r1, #8]
10101208:	6a81      	ldr	r1, [r0, #40]	; 0x28
1010120a:	f011 0101 	ands.w	r1, r1, #1
1010120e:	d1fb      	bne.n	10101208 <FLASH_RxData+0x74>
10101210:	4c21      	ldr	r4, [pc, #132]	; (10101298 <FLASH_RxData+0x104>)
10101212:	3b01      	subs	r3, #1
10101214:	4291      	cmp	r1, r2
10101216:	d007      	beq.n	10101228 <FLASH_RxData+0x94>
10101218:	6aa0      	ldr	r0, [r4, #40]	; 0x28
1010121a:	0700      	lsls	r0, r0, #28
1010121c:	d42e      	bmi.n	1010127c <FLASH_RxData+0xe8>
1010121e:	6aa0      	ldr	r0, [r4, #40]	; 0x28
10101220:	0705      	lsls	r5, r0, #28
10101222:	d42b      	bmi.n	1010127c <FLASH_RxData+0xe8>
10101224:	4291      	cmp	r1, r2
10101226:	d3fa      	bcc.n	1010121e <FLASH_RxData+0x8a>
10101228:	2200      	movs	r2, #0
1010122a:	4b1b      	ldr	r3, [pc, #108]	; (10101298 <FLASH_RxData+0x104>)
1010122c:	609a      	str	r2, [r3, #8]
1010122e:	bdf0      	pop	{r4, r5, r6, r7, pc}
10101230:	2501      	movs	r5, #1
10101232:	f897 7059 	ldrb.w	r7, [r7, #89]	; 0x59
10101236:	2f03      	cmp	r7, #3
10101238:	f8c4 7118 	str.w	r7, [r4, #280]	; 0x118
1010123c:	6125      	str	r5, [r4, #16]
1010123e:	61e6      	str	r6, [r4, #28]
10101240:	ea4f 4511 	mov.w	r5, r1, lsr #16
10101244:	ea4f 2411 	mov.w	r4, r1, lsr #8
10101248:	d00b      	beq.n	10101262 <FLASH_RxData+0xce>
1010124a:	2f00      	cmp	r7, #0
1010124c:	d1d8      	bne.n	10101200 <FLASH_RxData+0x6c>
1010124e:	0e0f      	lsrs	r7, r1, #24
10101250:	e7c3      	b.n	101011da <FLASH_RxData+0x46>
10101252:	2501      	movs	r5, #1
10101254:	f8c4 e118 	str.w	lr, [r4, #280]	; 0x118
10101258:	6125      	str	r5, [r4, #16]
1010125a:	f8c4 e01c 	str.w	lr, [r4, #28]
1010125e:	0c0d      	lsrs	r5, r1, #16
10101260:	0a0c      	lsrs	r4, r1, #8
10101262:	022d      	lsls	r5, r5, #8
10101264:	ea40 6001 	orr.w	r0, r0, r1, lsl #24
10101268:	f405 457f 	and.w	r5, r5, #65280	; 0xff00
1010126c:	0421      	lsls	r1, r4, #16
1010126e:	4305      	orrs	r5, r0
10101270:	f401 017f 	and.w	r1, r1, #16711680	; 0xff0000
10101274:	4808      	ldr	r0, [pc, #32]	; (10101298 <FLASH_RxData+0x104>)
10101276:	4329      	orrs	r1, r5
10101278:	6601      	str	r1, [r0, #96]	; 0x60
1010127a:	e7bc      	b.n	101011f6 <FLASH_RxData+0x62>
1010127c:	f894 0060 	ldrb.w	r0, [r4, #96]	; 0x60
10101280:	3101      	adds	r1, #1
10101282:	f803 0f01 	strb.w	r0, [r3, #1]!
10101286:	e7c5      	b.n	10101214 <FLASH_RxData+0x80>
10101288:	2101      	movs	r1, #1
1010128a:	6121      	str	r1, [r4, #16]
1010128c:	f8c4 e01c 	str.w	lr, [r4, #28]
10101290:	e7b2      	b.n	101011f8 <FLASH_RxData+0x64>
10101292:	bf00      	nop
10101294:	10000038 	.word	0x10000038
10101298:	48080000 	.word	0x48080000

1010129c <FLASH_TxCmd>:
1010129c:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
101012a0:	4f1f      	ldr	r7, [pc, #124]	; (10101320 <FLASH_TxCmd+0x84>)
101012a2:	290c      	cmp	r1, #12
101012a4:	f8d7 5118 	ldr.w	r5, [r7, #280]	; 0x118
101012a8:	460e      	mov	r6, r1
101012aa:	4680      	mov	r8, r0
101012ac:	4691      	mov	r9, r2
101012ae:	683c      	ldr	r4, [r7, #0]
101012b0:	d824      	bhi.n	101012fc <FLASH_TxCmd+0x60>
101012b2:	2300      	movs	r3, #0
101012b4:	60bb      	str	r3, [r7, #8]
101012b6:	683b      	ldr	r3, [r7, #0]
101012b8:	f423 137c 	bic.w	r3, r3, #4128768	; 0x3f0000
101012bc:	f423 7340 	bic.w	r3, r3, #768	; 0x300
101012c0:	2903      	cmp	r1, #3
101012c2:	603b      	str	r3, [r7, #0]
101012c4:	d826      	bhi.n	10101314 <FLASH_TxCmd+0x78>
101012c6:	f8c7 1118 	str.w	r1, [r7, #280]	; 0x118
101012ca:	4815      	ldr	r0, [pc, #84]	; (10101320 <FLASH_TxCmd+0x84>)
101012cc:	f880 8060 	strb.w	r8, [r0, #96]	; 0x60
101012d0:	b13e      	cbz	r6, 101012e2 <FLASH_TxCmd+0x46>
101012d2:	464a      	mov	r2, r9
101012d4:	1991      	adds	r1, r2, r6
101012d6:	f812 3b01 	ldrb.w	r3, [r2], #1
101012da:	428a      	cmp	r2, r1
101012dc:	f880 3060 	strb.w	r3, [r0, #96]	; 0x60
101012e0:	d1f9      	bne.n	101012d6 <FLASH_TxCmd+0x3a>
101012e2:	2301      	movs	r3, #1
101012e4:	4a0e      	ldr	r2, [pc, #56]	; (10101320 <FLASH_TxCmd+0x84>)
101012e6:	6093      	str	r3, [r2, #8]
101012e8:	6a93      	ldr	r3, [r2, #40]	; 0x28
101012ea:	f013 0301 	ands.w	r3, r3, #1
101012ee:	d1fb      	bne.n	101012e8 <FLASH_TxCmd+0x4c>
101012f0:	6093      	str	r3, [r2, #8]
101012f2:	f8c2 5118 	str.w	r5, [r2, #280]	; 0x118
101012f6:	6014      	str	r4, [r2, #0]
101012f8:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
101012fc:	21f1      	movs	r1, #241	; 0xf1
101012fe:	4809      	ldr	r0, [pc, #36]	; (10101324 <FLASH_TxCmd+0x88>)
10101300:	f7ff fab6 	bl	10100870 <io_assert_failed>
10101304:	2300      	movs	r3, #0
10101306:	60bb      	str	r3, [r7, #8]
10101308:	683b      	ldr	r3, [r7, #0]
1010130a:	f423 137c 	bic.w	r3, r3, #4128768	; 0x3f0000
1010130e:	f423 7340 	bic.w	r3, r3, #768	; 0x300
10101312:	603b      	str	r3, [r7, #0]
10101314:	2100      	movs	r1, #0
10101316:	4b02      	ldr	r3, [pc, #8]	; (10101320 <FLASH_TxCmd+0x84>)
10101318:	f8c3 1118 	str.w	r1, [r3, #280]	; 0x118
1010131c:	e7d5      	b.n	101012ca <FLASH_TxCmd+0x2e>
1010131e:	bf00      	nop
10101320:	48080000 	.word	0x48080000
10101324:	101d4fa8 	.word	0x101d4fa8

10101328 <FLASH_SW_CS_Control>:
10101328:	b570      	push	{r4, r5, r6, lr}
1010132a:	4b10      	ldr	r3, [pc, #64]	; (1010136c <FLASH_SW_CS_Control+0x44>)
1010132c:	f893 305b 	ldrb.w	r3, [r3, #91]	; 0x5b
10101330:	b143      	cbz	r3, 10101344 <FLASH_SW_CS_Control+0x1c>
10101332:	2530      	movs	r5, #48	; 0x30
10101334:	462e      	mov	r6, r5
10101336:	b148      	cbz	r0, 1010134c <FLASH_SW_CS_Control+0x24>
10101338:	4628      	mov	r0, r5
1010133a:	2106      	movs	r1, #6
1010133c:	4b0c      	ldr	r3, [pc, #48]	; (10101370 <FLASH_SW_CS_Control+0x48>)
1010133e:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10101342:	4718      	bx	r3
10101344:	2532      	movs	r5, #50	; 0x32
10101346:	462e      	mov	r6, r5
10101348:	2800      	cmp	r0, #0
1010134a:	d1f5      	bne.n	10101338 <FLASH_SW_CS_Control+0x10>
1010134c:	4604      	mov	r4, r0
1010134e:	2101      	movs	r1, #1
10101350:	4630      	mov	r0, r6
10101352:	4b08      	ldr	r3, [pc, #32]	; (10101374 <FLASH_SW_CS_Control+0x4c>)
10101354:	4798      	blx	r3
10101356:	4621      	mov	r1, r4
10101358:	4630      	mov	r0, r6
1010135a:	4b07      	ldr	r3, [pc, #28]	; (10101378 <FLASH_SW_CS_Control+0x50>)
1010135c:	4798      	blx	r3
1010135e:	4621      	mov	r1, r4
10101360:	4628      	mov	r0, r5
10101362:	4b03      	ldr	r3, [pc, #12]	; (10101370 <FLASH_SW_CS_Control+0x48>)
10101364:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10101368:	4718      	bx	r3
1010136a:	bf00      	nop
1010136c:	10000038 	.word	0x10000038
10101370:	10102fb9 	.word	0x10102fb9
10101374:	10102721 	.word	0x10102721
10101378:	10102871 	.word	0x10102871

1010137c <FLASH_SetSpiMode>:
1010137c:	b470      	push	{r4, r5, r6}
1010137e:	2400      	movs	r4, #0
10101380:	7943      	ldrb	r3, [r0, #5]
10101382:	1842      	adds	r2, r0, r1
10101384:	7f95      	ldrb	r5, [r2, #30]
10101386:	7f42      	ldrb	r2, [r0, #29]
10101388:	005b      	lsls	r3, r3, #1
1010138a:	fb05 2303 	mla	r3, r5, r3, r2
1010138e:	4a20      	ldr	r2, [pc, #128]	; (10101410 <FLASH_SetSpiMode+0x94>)
10101390:	6094      	str	r4, [r2, #8]
10101392:	f890 5059 	ldrb.w	r5, [r0, #89]	; 0x59
10101396:	f8d2 611c 	ldr.w	r6, [r2, #284]	; 0x11c
1010139a:	f5a4 3444 	sub.w	r4, r4, #200704	; 0x31000
1010139e:	042d      	lsls	r5, r5, #16
101013a0:	f405 3540 	and.w	r5, r5, #196608	; 0x30000
101013a4:	4034      	ands	r4, r6
101013a6:	432c      	orrs	r4, r5
101013a8:	f3c3 030b 	ubfx	r3, r3, #0, #12
101013ac:	4323      	orrs	r3, r4
101013ae:	f8c2 311c 	str.w	r3, [r2, #284]	; 0x11c
101013b2:	6814      	ldr	r4, [r2, #0]
101013b4:	f8d2 3120 	ldr.w	r3, [r2, #288]	; 0x120
101013b8:	f423 43ff 	bic.w	r3, r3, #32640	; 0x7f80
101013bc:	f023 037f 	bic.w	r3, r3, #127	; 0x7f
101013c0:	2901      	cmp	r1, #1
101013c2:	f424 147c 	bic.w	r4, r4, #4128768	; 0x3f0000
101013c6:	f8c2 3120 	str.w	r3, [r2, #288]	; 0x120
101013ca:	d011      	beq.n	101013f0 <FLASH_SetSpiMode+0x74>
101013cc:	2902      	cmp	r1, #2
101013ce:	d10b      	bne.n	101013e8 <FLASH_SetSpiMode+0x6c>
101013d0:	6c81      	ldr	r1, [r0, #72]	; 0x48
101013d2:	f8d2 3120 	ldr.w	r3, [r2, #288]	; 0x120
101013d6:	430b      	orrs	r3, r1
101013d8:	f8c2 3120 	str.w	r3, [r2, #288]	; 0x120
101013dc:	070b      	lsls	r3, r1, #28
101013de:	bf4c      	ite	mi
101013e0:	f444 2400 	orrmi.w	r4, r4, #524288	; 0x80000
101013e4:	f444 2420 	orrpl.w	r4, r4, #655360	; 0xa0000
101013e8:	4b09      	ldr	r3, [pc, #36]	; (10101410 <FLASH_SetSpiMode+0x94>)
101013ea:	601c      	str	r4, [r3, #0]
101013ec:	bc70      	pop	{r4, r5, r6}
101013ee:	4770      	bx	lr
101013f0:	6c41      	ldr	r1, [r0, #68]	; 0x44
101013f2:	f8d2 3120 	ldr.w	r3, [r2, #288]	; 0x120
101013f6:	430b      	orrs	r3, r1
101013f8:	f8c2 3120 	str.w	r3, [r2, #288]	; 0x120
101013fc:	078a      	lsls	r2, r1, #30
101013fe:	4b04      	ldr	r3, [pc, #16]	; (10101410 <FLASH_SetSpiMode+0x94>)
10101400:	bf4c      	ite	mi
10101402:	f444 2480 	orrmi.w	r4, r4, #262144	; 0x40000
10101406:	f444 24a0 	orrpl.w	r4, r4, #327680	; 0x50000
1010140a:	601c      	str	r4, [r3, #0]
1010140c:	bc70      	pop	{r4, r5, r6}
1010140e:	4770      	bx	lr
10101410:	48080000 	.word	0x48080000

10101414 <FLASH_RxCmd>:
10101414:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
10101418:	2700      	movs	r7, #0
1010141a:	460e      	mov	r6, r1
1010141c:	4680      	mov	r8, r0
1010141e:	4639      	mov	r1, r7
10101420:	4813      	ldr	r0, [pc, #76]	; (10101470 <FLASH_RxCmd+0x5c>)
10101422:	4614      	mov	r4, r2
10101424:	f7ff ffaa 	bl	1010137c <FLASH_SetSpiMode>
10101428:	2201      	movs	r2, #1
1010142a:	4d12      	ldr	r5, [pc, #72]	; (10101474 <FLASH_RxCmd+0x60>)
1010142c:	b2b3      	uxth	r3, r6
1010142e:	60af      	str	r7, [r5, #8]
10101430:	606b      	str	r3, [r5, #4]
10101432:	682b      	ldr	r3, [r5, #0]
10101434:	f423 2370 	bic.w	r3, r3, #983040	; 0xf0000
10101438:	f423 7340 	bic.w	r3, r3, #768	; 0x300
1010143c:	f443 7340 	orr.w	r3, r3, #768	; 0x300
10101440:	602b      	str	r3, [r5, #0]
10101442:	4638      	mov	r0, r7
10101444:	f885 8060 	strb.w	r8, [r5, #96]	; 0x60
10101448:	60aa      	str	r2, [r5, #8]
1010144a:	f000 f815 	bl	10101478 <FLASH_WaitBusy>
1010144e:	60af      	str	r7, [r5, #8]
10101450:	b146      	cbz	r6, 10101464 <FLASH_RxCmd+0x50>
10101452:	4622      	mov	r2, r4
10101454:	4628      	mov	r0, r5
10101456:	19a1      	adds	r1, r4, r6
10101458:	f890 3060 	ldrb.w	r3, [r0, #96]	; 0x60
1010145c:	f802 3b01 	strb.w	r3, [r2], #1
10101460:	428a      	cmp	r2, r1
10101462:	d1f9      	bne.n	10101458 <FLASH_RxCmd+0x44>
10101464:	4802      	ldr	r0, [pc, #8]	; (10101470 <FLASH_RxCmd+0x5c>)
10101466:	e8bd 41f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, lr}
1010146a:	7901      	ldrb	r1, [r0, #4]
1010146c:	f7ff bf86 	b.w	1010137c <FLASH_SetSpiMode>
10101470:	10000038 	.word	0x10000038
10101474:	48080000 	.word	0x48080000

10101478 <FLASH_WaitBusy>:
10101478:	2300      	movs	r3, #0
1010147a:	b5f0      	push	{r4, r5, r6, r7, lr}
1010147c:	4604      	mov	r4, r0
1010147e:	b083      	sub	sp, #12
10101480:	f88d 3007 	strb.w	r3, [sp, #7]
10101484:	4f1a      	ldr	r7, [pc, #104]	; (101014f0 <FLASH_WaitBusy+0x78>)
10101486:	4d1b      	ldr	r5, [pc, #108]	; (101014f4 <FLASH_WaitBusy+0x7c>)
10101488:	1e46      	subs	r6, r0, #1
1010148a:	b99c      	cbnz	r4, 101014b4 <FLASH_WaitBusy+0x3c>
1010148c:	6aab      	ldr	r3, [r5, #40]	; 0x28
1010148e:	f003 0301 	and.w	r3, r3, #1
10101492:	2b00      	cmp	r3, #0
10101494:	d1f9      	bne.n	1010148a <FLASH_WaitBusy+0x12>
10101496:	b003      	add	sp, #12
10101498:	bdf0      	pop	{r4, r5, r6, r7, pc}
1010149a:	f10d 0207 	add.w	r2, sp, #7
1010149e:	2101      	movs	r1, #1
101014a0:	f897 004e 	ldrb.w	r0, [r7, #78]	; 0x4e
101014a4:	f7ff ffb6 	bl	10101414 <FLASH_RxCmd>
101014a8:	f89d 3007 	ldrb.w	r3, [sp, #7]
101014ac:	697a      	ldr	r2, [r7, #20]
101014ae:	4213      	tst	r3, r2
101014b0:	d115      	bne.n	101014de <FLASH_WaitBusy+0x66>
101014b2:	2301      	movs	r3, #1
101014b4:	2e01      	cmp	r6, #1
101014b6:	d904      	bls.n	101014c2 <FLASH_WaitBusy+0x4a>
101014b8:	2c03      	cmp	r4, #3
101014ba:	d0ee      	beq.n	1010149a <FLASH_WaitBusy+0x22>
101014bc:	2b00      	cmp	r3, #0
101014be:	d1e4      	bne.n	1010148a <FLASH_WaitBusy+0x12>
101014c0:	e7e9      	b.n	10101496 <FLASH_WaitBusy+0x1e>
101014c2:	f10d 0207 	add.w	r2, sp, #7
101014c6:	2101      	movs	r1, #1
101014c8:	f897 004e 	ldrb.w	r0, [r7, #78]	; 0x4e
101014cc:	f7ff ffa2 	bl	10101414 <FLASH_RxCmd>
101014d0:	f89d 2007 	ldrb.w	r2, [sp, #7]
101014d4:	693b      	ldr	r3, [r7, #16]
101014d6:	4013      	ands	r3, r2
101014d8:	2b00      	cmp	r3, #0
101014da:	d1d6      	bne.n	1010148a <FLASH_WaitBusy+0x12>
101014dc:	e7db      	b.n	10101496 <FLASH_WaitBusy+0x1e>
101014de:	693a      	ldr	r2, [r7, #16]
101014e0:	4213      	tst	r3, r2
101014e2:	bf14      	ite	ne
101014e4:	2301      	movne	r3, #1
101014e6:	2300      	moveq	r3, #0
101014e8:	2b00      	cmp	r3, #0
101014ea:	d1ce      	bne.n	1010148a <FLASH_WaitBusy+0x12>
101014ec:	e7d3      	b.n	10101496 <FLASH_WaitBusy+0x1e>
101014ee:	bf00      	nop
101014f0:	10000038 	.word	0x10000038
101014f4:	48080000 	.word	0x48080000

101014f8 <FLASH_WriteEn>:
101014f8:	b508      	push	{r3, lr}
101014fa:	2001      	movs	r0, #1
101014fc:	f7ff ffbc 	bl	10101478 <FLASH_WaitBusy>
10101500:	2200      	movs	r2, #0
10101502:	4b05      	ldr	r3, [pc, #20]	; (10101518 <FLASH_WriteEn+0x20>)
10101504:	4611      	mov	r1, r2
10101506:	f893 004c 	ldrb.w	r0, [r3, #76]	; 0x4c
1010150a:	f7ff fec7 	bl	1010129c <FLASH_TxCmd>
1010150e:	2003      	movs	r0, #3
10101510:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
10101514:	f7ff bfb0 	b.w	10101478 <FLASH_WaitBusy>
10101518:	10000038 	.word	0x10000038

1010151c <FLASH_TxData256B>:
1010151c:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
1010151e:	4b38      	ldr	r3, [pc, #224]	; (10101600 <FLASH_TxData256B+0xe4>)
10101520:	f5b1 7f80 	cmp.w	r1, #256	; 0x100
10101524:	460d      	mov	r5, r1
10101526:	4607      	mov	r7, r0
10101528:	4614      	mov	r4, r2
1010152a:	681e      	ldr	r6, [r3, #0]
1010152c:	d854      	bhi.n	101015d8 <FLASH_TxData256B+0xbc>
1010152e:	07aa      	lsls	r2, r5, #30
10101530:	d14c      	bne.n	101015cc <FLASH_TxData256B+0xb0>
10101532:	07bb      	lsls	r3, r7, #30
10101534:	d144      	bne.n	101015c0 <FLASH_TxData256B+0xa4>
10101536:	fa55 f387 	uxtab	r3, r5, r7
1010153a:	f5b3 7f80 	cmp.w	r3, #256	; 0x100
1010153e:	d839      	bhi.n	101015b4 <FLASH_TxData256B+0x98>
10101540:	f7ff ffda 	bl	101014f8 <FLASH_WriteEn>
10101544:	2300      	movs	r3, #0
10101546:	4a2e      	ldr	r2, [pc, #184]	; (10101600 <FLASH_TxData256B+0xe4>)
10101548:	6093      	str	r3, [r2, #8]
1010154a:	492e      	ldr	r1, [pc, #184]	; (10101604 <FLASH_TxData256B+0xe8>)
1010154c:	6813      	ldr	r3, [r2, #0]
1010154e:	f891 1059 	ldrb.w	r1, [r1, #89]	; 0x59
10101552:	f423 137c 	bic.w	r3, r3, #4128768	; 0x3f0000
10101556:	f423 7340 	bic.w	r3, r3, #768	; 0x300
1010155a:	2903      	cmp	r1, #3
1010155c:	6013      	str	r3, [r2, #0]
1010155e:	ea4f 2017 	mov.w	r0, r7, lsr #8
10101562:	ea4f 4317 	mov.w	r3, r7, lsr #16
10101566:	f8c2 1118 	str.w	r1, [r2, #280]	; 0x118
1010156a:	d03b      	beq.n	101015e4 <FLASH_TxData256B+0xc8>
1010156c:	b1e1      	cbz	r1, 101015a8 <FLASH_TxData256B+0x8c>
1010156e:	2000      	movs	r0, #0
10101570:	f7ff feda 	bl	10101328 <FLASH_SW_CS_Control>
10101574:	2301      	movs	r3, #1
10101576:	4822      	ldr	r0, [pc, #136]	; (10101600 <FLASH_TxData256B+0xe4>)
10101578:	6083      	str	r3, [r0, #8]
1010157a:	b13d      	cbz	r5, 1010158c <FLASH_TxData256B+0x70>
1010157c:	2300      	movs	r3, #0
1010157e:	1f22      	subs	r2, r4, #4
10101580:	f852 1f04 	ldr.w	r1, [r2, #4]!
10101584:	3304      	adds	r3, #4
10101586:	429d      	cmp	r5, r3
10101588:	6601      	str	r1, [r0, #96]	; 0x60
1010158a:	d8f9      	bhi.n	10101580 <FLASH_TxData256B+0x64>
1010158c:	2001      	movs	r0, #1
1010158e:	f7ff fecb 	bl	10101328 <FLASH_SW_CS_Control>
10101592:	4c1b      	ldr	r4, [pc, #108]	; (10101600 <FLASH_TxData256B+0xe4>)
10101594:	6aa3      	ldr	r3, [r4, #40]	; 0x28
10101596:	f013 0301 	ands.w	r3, r3, #1
1010159a:	d1fb      	bne.n	10101594 <FLASH_TxData256B+0x78>
1010159c:	60a3      	str	r3, [r4, #8]
1010159e:	2002      	movs	r0, #2
101015a0:	f7ff ff6a 	bl	10101478 <FLASH_WaitBusy>
101015a4:	6026      	str	r6, [r4, #0]
101015a6:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
101015a8:	2302      	movs	r3, #2
101015aa:	ba3f      	rev	r7, r7
101015ac:	f882 3060 	strb.w	r3, [r2, #96]	; 0x60
101015b0:	6617      	str	r7, [r2, #96]	; 0x60
101015b2:	e7dc      	b.n	1010156e <FLASH_TxData256B+0x52>
101015b4:	f240 1145 	movw	r1, #325	; 0x145
101015b8:	4813      	ldr	r0, [pc, #76]	; (10101608 <FLASH_TxData256B+0xec>)
101015ba:	f7ff f959 	bl	10100870 <io_assert_failed>
101015be:	e7bf      	b.n	10101540 <FLASH_TxData256B+0x24>
101015c0:	f44f 71a2 	mov.w	r1, #324	; 0x144
101015c4:	4810      	ldr	r0, [pc, #64]	; (10101608 <FLASH_TxData256B+0xec>)
101015c6:	f7ff f953 	bl	10100870 <io_assert_failed>
101015ca:	e7b4      	b.n	10101536 <FLASH_TxData256B+0x1a>
101015cc:	f240 1143 	movw	r1, #323	; 0x143
101015d0:	480d      	ldr	r0, [pc, #52]	; (10101608 <FLASH_TxData256B+0xec>)
101015d2:	f7ff f94d 	bl	10100870 <io_assert_failed>
101015d6:	e7ac      	b.n	10101532 <FLASH_TxData256B+0x16>
101015d8:	f44f 71a1 	mov.w	r1, #322	; 0x142
101015dc:	480a      	ldr	r0, [pc, #40]	; (10101608 <FLASH_TxData256B+0xec>)
101015de:	f7ff f947 	bl	10100870 <io_assert_failed>
101015e2:	e7a4      	b.n	1010152e <FLASH_TxData256B+0x12>
101015e4:	021b      	lsls	r3, r3, #8
101015e6:	f403 437f 	and.w	r3, r3, #65280	; 0xff00
101015ea:	ea43 6707 	orr.w	r7, r3, r7, lsl #24
101015ee:	0400      	lsls	r0, r0, #16
101015f0:	f047 0702 	orr.w	r7, r7, #2
101015f4:	f400 007f 	and.w	r0, r0, #16711680	; 0xff0000
101015f8:	4307      	orrs	r7, r0
101015fa:	6617      	str	r7, [r2, #96]	; 0x60
101015fc:	e7b7      	b.n	1010156e <FLASH_TxData256B+0x52>
101015fe:	bf00      	nop
10101600:	48080000 	.word	0x48080000
10101604:	10000038 	.word	0x10000038
10101608:	101d4f94 	.word	0x101d4f94

1010160c <FLASH_TxData12B>:
1010160c:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
1010160e:	4b34      	ldr	r3, [pc, #208]	; (101016e0 <FLASH_TxData12B+0xd4>)
10101610:	290c      	cmp	r1, #12
10101612:	460e      	mov	r6, r1
10101614:	4607      	mov	r7, r0
10101616:	4614      	mov	r4, r2
10101618:	681d      	ldr	r5, [r3, #0]
1010161a:	d84e      	bhi.n	101016ba <FLASH_TxData12B+0xae>
1010161c:	07b2      	lsls	r2, r6, #30
1010161e:	d146      	bne.n	101016ae <FLASH_TxData12B+0xa2>
10101620:	07bb      	lsls	r3, r7, #30
10101622:	d13e      	bne.n	101016a2 <FLASH_TxData12B+0x96>
10101624:	fa56 f387 	uxtab	r3, r6, r7
10101628:	f5b3 7f80 	cmp.w	r3, #256	; 0x100
1010162c:	d833      	bhi.n	10101696 <FLASH_TxData12B+0x8a>
1010162e:	f7ff ff63 	bl	101014f8 <FLASH_WriteEn>
10101632:	2300      	movs	r3, #0
10101634:	4a2a      	ldr	r2, [pc, #168]	; (101016e0 <FLASH_TxData12B+0xd4>)
10101636:	6093      	str	r3, [r2, #8]
10101638:	492a      	ldr	r1, [pc, #168]	; (101016e4 <FLASH_TxData12B+0xd8>)
1010163a:	6813      	ldr	r3, [r2, #0]
1010163c:	f891 1059 	ldrb.w	r1, [r1, #89]	; 0x59
10101640:	f423 137c 	bic.w	r3, r3, #4128768	; 0x3f0000
10101644:	f423 7340 	bic.w	r3, r3, #768	; 0x300
10101648:	2903      	cmp	r1, #3
1010164a:	6013      	str	r3, [r2, #0]
1010164c:	ea4f 2017 	mov.w	r0, r7, lsr #8
10101650:	ea4f 4317 	mov.w	r3, r7, lsr #16
10101654:	f8c2 1118 	str.w	r1, [r2, #280]	; 0x118
10101658:	d035      	beq.n	101016c6 <FLASH_TxData12B+0xba>
1010165a:	b1b1      	cbz	r1, 1010168a <FLASH_TxData12B+0x7e>
1010165c:	b146      	cbz	r6, 10101670 <FLASH_TxData12B+0x64>
1010165e:	4622      	mov	r2, r4
10101660:	481f      	ldr	r0, [pc, #124]	; (101016e0 <FLASH_TxData12B+0xd4>)
10101662:	19a1      	adds	r1, r4, r6
10101664:	f812 3b01 	ldrb.w	r3, [r2], #1
10101668:	428a      	cmp	r2, r1
1010166a:	f880 3060 	strb.w	r3, [r0, #96]	; 0x60
1010166e:	d1f9      	bne.n	10101664 <FLASH_TxData12B+0x58>
10101670:	2301      	movs	r3, #1
10101672:	4c1b      	ldr	r4, [pc, #108]	; (101016e0 <FLASH_TxData12B+0xd4>)
10101674:	60a3      	str	r3, [r4, #8]
10101676:	6aa3      	ldr	r3, [r4, #40]	; 0x28
10101678:	f013 0301 	ands.w	r3, r3, #1
1010167c:	d1fb      	bne.n	10101676 <FLASH_TxData12B+0x6a>
1010167e:	60a3      	str	r3, [r4, #8]
10101680:	2002      	movs	r0, #2
10101682:	f7ff fef9 	bl	10101478 <FLASH_WaitBusy>
10101686:	6025      	str	r5, [r4, #0]
10101688:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
1010168a:	2302      	movs	r3, #2
1010168c:	ba3f      	rev	r7, r7
1010168e:	f882 3060 	strb.w	r3, [r2, #96]	; 0x60
10101692:	6617      	str	r7, [r2, #96]	; 0x60
10101694:	e7e2      	b.n	1010165c <FLASH_TxData12B+0x50>
10101696:	f44f 71c8 	mov.w	r1, #400	; 0x190
1010169a:	4813      	ldr	r0, [pc, #76]	; (101016e8 <FLASH_TxData12B+0xdc>)
1010169c:	f7ff f8e8 	bl	10100870 <io_assert_failed>
101016a0:	e7c5      	b.n	1010162e <FLASH_TxData12B+0x22>
101016a2:	f240 118f 	movw	r1, #399	; 0x18f
101016a6:	4810      	ldr	r0, [pc, #64]	; (101016e8 <FLASH_TxData12B+0xdc>)
101016a8:	f7ff f8e2 	bl	10100870 <io_assert_failed>
101016ac:	e7ba      	b.n	10101624 <FLASH_TxData12B+0x18>
101016ae:	f44f 71c7 	mov.w	r1, #398	; 0x18e
101016b2:	480d      	ldr	r0, [pc, #52]	; (101016e8 <FLASH_TxData12B+0xdc>)
101016b4:	f7ff f8dc 	bl	10100870 <io_assert_failed>
101016b8:	e7b2      	b.n	10101620 <FLASH_TxData12B+0x14>
101016ba:	f240 118d 	movw	r1, #397	; 0x18d
101016be:	480a      	ldr	r0, [pc, #40]	; (101016e8 <FLASH_TxData12B+0xdc>)
101016c0:	f7ff f8d6 	bl	10100870 <io_assert_failed>
101016c4:	e7aa      	b.n	1010161c <FLASH_TxData12B+0x10>
101016c6:	021b      	lsls	r3, r3, #8
101016c8:	f403 437f 	and.w	r3, r3, #65280	; 0xff00
101016cc:	ea43 6707 	orr.w	r7, r3, r7, lsl #24
101016d0:	0400      	lsls	r0, r0, #16
101016d2:	f047 0702 	orr.w	r7, r7, #2
101016d6:	f400 007f 	and.w	r0, r0, #16711680	; 0xff0000
101016da:	4307      	orrs	r7, r0
101016dc:	6617      	str	r7, [r2, #96]	; 0x60
101016de:	e7bd      	b.n	1010165c <FLASH_TxData12B+0x50>
101016e0:	48080000 	.word	0x48080000
101016e4:	10000038 	.word	0x10000038
101016e8:	101d4fb4 	.word	0x101d4fb4

101016ec <FLASH_SetStatus>:
101016ec:	b570      	push	{r4, r5, r6, lr}
101016ee:	4604      	mov	r4, r0
101016f0:	460d      	mov	r5, r1
101016f2:	4616      	mov	r6, r2
101016f4:	f7ff ff00 	bl	101014f8 <FLASH_WriteEn>
101016f8:	4620      	mov	r0, r4
101016fa:	4632      	mov	r2, r6
101016fc:	b2e9      	uxtb	r1, r5
101016fe:	f7ff fdcd 	bl	1010129c <FLASH_TxCmd>
10101702:	2002      	movs	r0, #2
10101704:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10101708:	f7ff beb6 	b.w	10101478 <FLASH_WaitBusy>

1010170c <FLASH_Erase>:
1010170c:	b5f0      	push	{r4, r5, r6, r7, lr}
1010170e:	2802      	cmp	r0, #2
10101710:	b083      	sub	sp, #12
10101712:	4604      	mov	r4, r0
10101714:	460d      	mov	r5, r1
10101716:	d833      	bhi.n	10101780 <FLASH_Erase+0x74>
10101718:	4e25      	ldr	r6, [pc, #148]	; (101017b0 <FLASH_Erase+0xa4>)
1010171a:	f896 3059 	ldrb.w	r3, [r6, #89]	; 0x59
1010171e:	b9bb      	cbnz	r3, 10101750 <FLASH_Erase+0x44>
10101720:	0e29      	lsrs	r1, r5, #24
10101722:	0c2a      	lsrs	r2, r5, #16
10101724:	0a2b      	lsrs	r3, r5, #8
10101726:	f88d 5007 	strb.w	r5, [sp, #7]
1010172a:	f88d 1004 	strb.w	r1, [sp, #4]
1010172e:	f88d 2005 	strb.w	r2, [sp, #5]
10101732:	f88d 3006 	strb.w	r3, [sp, #6]
10101736:	2704      	movs	r7, #4
10101738:	f7ff fede 	bl	101014f8 <FLASH_WriteEn>
1010173c:	b1ac      	cbz	r4, 1010176a <FLASH_Erase+0x5e>
1010173e:	2c01      	cmp	r4, #1
10101740:	d02f      	beq.n	101017a2 <FLASH_Erase+0x96>
10101742:	2c02      	cmp	r4, #2
10101744:	d022      	beq.n	1010178c <FLASH_Erase+0x80>
10101746:	2002      	movs	r0, #2
10101748:	f7ff fe96 	bl	10101478 <FLASH_WaitBusy>
1010174c:	b003      	add	sp, #12
1010174e:	bdf0      	pop	{r4, r5, r6, r7, pc}
10101750:	0c2a      	lsrs	r2, r5, #16
10101752:	0a2b      	lsrs	r3, r5, #8
10101754:	2703      	movs	r7, #3
10101756:	f88d 5006 	strb.w	r5, [sp, #6]
1010175a:	f88d 2004 	strb.w	r2, [sp, #4]
1010175e:	f88d 3005 	strb.w	r3, [sp, #5]
10101762:	f7ff fec9 	bl	101014f8 <FLASH_WriteEn>
10101766:	2c00      	cmp	r4, #0
10101768:	d1e9      	bne.n	1010173e <FLASH_Erase+0x32>
1010176a:	f896 0052 	ldrb.w	r0, [r6, #82]	; 0x52
1010176e:	4622      	mov	r2, r4
10101770:	4621      	mov	r1, r4
10101772:	f7ff fd93 	bl	1010129c <FLASH_TxCmd>
10101776:	2002      	movs	r0, #2
10101778:	f7ff fe7e 	bl	10101478 <FLASH_WaitBusy>
1010177c:	b003      	add	sp, #12
1010177e:	bdf0      	pop	{r4, r5, r6, r7, pc}
10101780:	f240 2113 	movw	r1, #531	; 0x213
10101784:	480b      	ldr	r0, [pc, #44]	; (101017b4 <FLASH_Erase+0xa8>)
10101786:	f7ff f873 	bl	10100870 <io_assert_failed>
1010178a:	e7c5      	b.n	10101718 <FLASH_Erase+0xc>
1010178c:	4639      	mov	r1, r7
1010178e:	f896 0054 	ldrb.w	r0, [r6, #84]	; 0x54
10101792:	aa01      	add	r2, sp, #4
10101794:	f7ff fd82 	bl	1010129c <FLASH_TxCmd>
10101798:	2002      	movs	r0, #2
1010179a:	f7ff fe6d 	bl	10101478 <FLASH_WaitBusy>
1010179e:	b003      	add	sp, #12
101017a0:	bdf0      	pop	{r4, r5, r6, r7, pc}
101017a2:	4639      	mov	r1, r7
101017a4:	f896 0053 	ldrb.w	r0, [r6, #83]	; 0x53
101017a8:	aa01      	add	r2, sp, #4
101017aa:	f7ff fd77 	bl	1010129c <FLASH_TxCmd>
101017ae:	e7ca      	b.n	10101746 <FLASH_Erase+0x3a>
101017b0:	10000038 	.word	0x10000038
101017b4:	101d4f88 	.word	0x101d4f88

101017b8 <FLASH_DeepPowerDown>:
101017b8:	2801      	cmp	r0, #1
101017ba:	b508      	push	{r3, lr}
101017bc:	d00e      	beq.n	101017dc <FLASH_DeepPowerDown+0x24>
101017be:	2200      	movs	r2, #0
101017c0:	4b0e      	ldr	r3, [pc, #56]	; (101017fc <FLASH_DeepPowerDown+0x44>)
101017c2:	4611      	mov	r1, r2
101017c4:	f893 0055 	ldrb.w	r0, [r3, #85]	; 0x55
101017c8:	f7ff fd68 	bl	1010129c <FLASH_TxCmd>
101017cc:	2064      	movs	r0, #100	; 0x64
101017ce:	4b0c      	ldr	r3, [pc, #48]	; (10101800 <FLASH_DeepPowerDown+0x48>)
101017d0:	4798      	blx	r3
101017d2:	2001      	movs	r0, #1
101017d4:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
101017d8:	f7ff be4e 	b.w	10101478 <FLASH_WaitBusy>
101017dc:	4b09      	ldr	r3, [pc, #36]	; (10101804 <FLASH_DeepPowerDown+0x4c>)
101017de:	681b      	ldr	r3, [r3, #0]
101017e0:	031b      	lsls	r3, r3, #12
101017e2:	d400      	bmi.n	101017e6 <FLASH_DeepPowerDown+0x2e>
101017e4:	bd08      	pop	{r3, pc}
101017e6:	f7ff fe87 	bl	101014f8 <FLASH_WriteEn>
101017ea:	2200      	movs	r2, #0
101017ec:	4b03      	ldr	r3, [pc, #12]	; (101017fc <FLASH_DeepPowerDown+0x44>)
101017ee:	4611      	mov	r1, r2
101017f0:	f893 0056 	ldrb.w	r0, [r3, #86]	; 0x56
101017f4:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
101017f8:	f7ff bd50 	b.w	1010129c <FLASH_TxCmd>
101017fc:	10000038 	.word	0x10000038
10101800:	10100949 	.word	0x10100949
10101804:	4800022c 	.word	0x4800022c

10101808 <FLASH_SetStatusBits>:
10101808:	b5f0      	push	{r4, r5, r6, r7, lr}
1010180a:	460e      	mov	r6, r1
1010180c:	4605      	mov	r5, r0
1010180e:	4c32      	ldr	r4, [pc, #200]	; (101018d8 <FLASH_SetStatusBits+0xd0>)
10101810:	b083      	sub	sp, #12
10101812:	f894 004e 	ldrb.w	r0, [r4, #78]	; 0x4e
10101816:	aa01      	add	r2, sp, #4
10101818:	2101      	movs	r1, #1
1010181a:	f7ff fdfb 	bl	10101414 <FLASH_RxCmd>
1010181e:	2e01      	cmp	r6, #1
10101820:	ea4f 2715 	mov.w	r7, r5, lsr #8
10101824:	d032      	beq.n	1010188c <FLASH_SetStatusBits+0x84>
10101826:	f89d 3004 	ldrb.w	r3, [sp, #4]
1010182a:	69a2      	ldr	r2, [r4, #24]
1010182c:	ea23 0505 	bic.w	r5, r3, r5
10101830:	f88d 5004 	strb.w	r5, [sp, #4]
10101834:	2a00      	cmp	r2, #0
10101836:	d13f      	bne.n	101018b8 <FLASH_SetStatusBits+0xb0>
10101838:	2501      	movs	r5, #1
1010183a:	f894 3051 	ldrb.w	r3, [r4, #81]	; 0x51
1010183e:	b1c3      	cbz	r3, 10101872 <FLASH_SetStatusBits+0x6a>
10101840:	f7ff fe5a 	bl	101014f8 <FLASH_WriteEn>
10101844:	aa01      	add	r2, sp, #4
10101846:	2101      	movs	r1, #1
10101848:	f894 0050 	ldrb.w	r0, [r4, #80]	; 0x50
1010184c:	f7ff fd26 	bl	1010129c <FLASH_TxCmd>
10101850:	2002      	movs	r0, #2
10101852:	f7ff fe11 	bl	10101478 <FLASH_WaitBusy>
10101856:	f7ff fe4f 	bl	101014f8 <FLASH_WriteEn>
1010185a:	f894 0051 	ldrb.w	r0, [r4, #81]	; 0x51
1010185e:	f10d 0205 	add.w	r2, sp, #5
10101862:	2101      	movs	r1, #1
10101864:	f7ff fd1a 	bl	1010129c <FLASH_TxCmd>
10101868:	2002      	movs	r0, #2
1010186a:	f7ff fe05 	bl	10101478 <FLASH_WaitBusy>
1010186e:	b003      	add	sp, #12
10101870:	bdf0      	pop	{r4, r5, r6, r7, pc}
10101872:	f7ff fe41 	bl	101014f8 <FLASH_WriteEn>
10101876:	aa01      	add	r2, sp, #4
10101878:	4629      	mov	r1, r5
1010187a:	f894 0050 	ldrb.w	r0, [r4, #80]	; 0x50
1010187e:	f7ff fd0d 	bl	1010129c <FLASH_TxCmd>
10101882:	2002      	movs	r0, #2
10101884:	f7ff fdf8 	bl	10101478 <FLASH_WaitBusy>
10101888:	b003      	add	sp, #12
1010188a:	bdf0      	pop	{r4, r5, r6, r7, pc}
1010188c:	f89d 2004 	ldrb.w	r2, [sp, #4]
10101890:	69a3      	ldr	r3, [r4, #24]
10101892:	4315      	orrs	r5, r2
10101894:	f88d 5004 	strb.w	r5, [sp, #4]
10101898:	2b00      	cmp	r3, #0
1010189a:	d0cd      	beq.n	10101838 <FLASH_SetStatusBits+0x30>
1010189c:	4631      	mov	r1, r6
1010189e:	f10d 0205 	add.w	r2, sp, #5
101018a2:	f894 004f 	ldrb.w	r0, [r4, #79]	; 0x4f
101018a6:	f7ff fdb5 	bl	10101414 <FLASH_RxCmd>
101018aa:	f89d 3005 	ldrb.w	r3, [sp, #5]
101018ae:	431f      	orrs	r7, r3
101018b0:	f88d 7005 	strb.w	r7, [sp, #5]
101018b4:	2502      	movs	r5, #2
101018b6:	e7c0      	b.n	1010183a <FLASH_SetStatusBits+0x32>
101018b8:	f10d 0205 	add.w	r2, sp, #5
101018bc:	2101      	movs	r1, #1
101018be:	f894 004f 	ldrb.w	r0, [r4, #79]	; 0x4f
101018c2:	f7ff fda7 	bl	10101414 <FLASH_RxCmd>
101018c6:	f89d 3005 	ldrb.w	r3, [sp, #5]
101018ca:	ea23 0707 	bic.w	r7, r3, r7
101018ce:	f88d 7005 	strb.w	r7, [sp, #5]
101018d2:	2502      	movs	r5, #2
101018d4:	e7b1      	b.n	1010183a <FLASH_SetStatusBits+0x32>
101018d6:	bf00      	nop
101018d8:	10000038 	.word	0x10000038

101018dc <FLASH_StructInit_Micron>:
101018dc:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
101018e0:	2602      	movs	r6, #2
101018e2:	6146      	str	r6, [r0, #20]
101018e4:	26a2      	movs	r6, #162	; 0xa2
101018e6:	6346      	str	r6, [r0, #52]	; 0x34
101018e8:	26d2      	movs	r6, #210	; 0xd2
101018ea:	6386      	str	r6, [r0, #56]	; 0x38
101018ec:	263b      	movs	r6, #59	; 0x3b
101018ee:	6246      	str	r6, [r0, #36]	; 0x24
101018f0:	f44f 7601 	mov.w	r6, #516	; 0x204
101018f4:	6446      	str	r6, [r0, #68]	; 0x44
101018f6:	2612      	movs	r6, #18
101018f8:	6406      	str	r6, [r0, #64]	; 0x40
101018fa:	26eb      	movs	r6, #235	; 0xeb
101018fc:	6306      	str	r6, [r0, #48]	; 0x30
101018fe:	266b      	movs	r6, #107	; 0x6b
10101900:	62c6      	str	r6, [r0, #44]	; 0x2c
10101902:	f44f 7644 	mov.w	r6, #784	; 0x310
10101906:	6486      	str	r6, [r0, #72]	; 0x48
10101908:	f04f 0606 	mov.w	r6, #6
1010190c:	2300      	movs	r3, #0
1010190e:	2201      	movs	r2, #1
10101910:	2103      	movs	r1, #3
10101912:	2505      	movs	r5, #5
10101914:	24bb      	movs	r4, #187	; 0xbb
10101916:	f880 604c 	strb.w	r6, [r0, #76]	; 0x4c
1010191a:	f04f 0a09 	mov.w	sl, #9
1010191e:	2732      	movs	r7, #50	; 0x32
10101920:	f04f 0b9f 	mov.w	fp, #159	; 0x9f
10101924:	f04f 09c7 	mov.w	r9, #199	; 0xc7
10101928:	f04f 08d8 	mov.w	r8, #216	; 0xd8
1010192c:	f04f 0c20 	mov.w	ip, #32
10101930:	f04f 0eab 	mov.w	lr, #171	; 0xab
10101934:	f06f 0646 	mvn.w	r6, #70	; 0x46
10101938:	f880 a020 	strb.w	sl, [r0, #32]
1010193c:	63c7      	str	r7, [r0, #60]	; 0x3c
1010193e:	f880 b04d 	strb.w	fp, [r0, #77]	; 0x4d
10101942:	f880 9052 	strb.w	r9, [r0, #82]	; 0x52
10101946:	f880 8053 	strb.w	r8, [r0, #83]	; 0x53
1010194a:	f880 c054 	strb.w	ip, [r0, #84]	; 0x54
1010194e:	f880 e055 	strb.w	lr, [r0, #85]	; 0x55
10101952:	f880 6056 	strb.w	r6, [r0, #86]	; 0x56
10101956:	6001      	str	r1, [r0, #0]
10101958:	7142      	strb	r2, [r0, #5]
1010195a:	6102      	str	r2, [r0, #16]
1010195c:	7742      	strb	r2, [r0, #29]
1010195e:	f880 2050 	strb.w	r2, [r0, #80]	; 0x50
10101962:	60c3      	str	r3, [r0, #12]
10101964:	6183      	str	r3, [r0, #24]
10101966:	7783      	strb	r3, [r0, #30]
10101968:	f880 304f 	strb.w	r3, [r0, #79]	; 0x4f
1010196c:	f880 3051 	strb.w	r3, [r0, #81]	; 0x51
10101970:	f880 3058 	strb.w	r3, [r0, #88]	; 0x58
10101974:	77c5      	strb	r5, [r0, #31]
10101976:	f880 504e 	strb.w	r5, [r0, #78]	; 0x4e
1010197a:	6284      	str	r4, [r0, #40]	; 0x28
1010197c:	65c4      	str	r4, [r0, #92]	; 0x5c
1010197e:	f880 1059 	strb.w	r1, [r0, #89]	; 0x59
10101982:	f880 305a 	strb.w	r3, [r0, #90]	; 0x5a
10101986:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
1010198a:	bf00      	nop

1010198c <FLASH_StructInit_MXIC>:
1010198c:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10101990:	2540      	movs	r5, #64	; 0x40
10101992:	60c5      	str	r5, [r0, #12]
10101994:	2502      	movs	r5, #2
10101996:	6145      	str	r5, [r0, #20]
10101998:	253b      	movs	r5, #59	; 0x3b
1010199a:	6245      	str	r5, [r0, #36]	; 0x24
1010199c:	f44f 7501 	mov.w	r5, #516	; 0x204
101019a0:	6445      	str	r5, [r0, #68]	; 0x44
101019a2:	2538      	movs	r5, #56	; 0x38
101019a4:	6405      	str	r5, [r0, #64]	; 0x40
101019a6:	256b      	movs	r5, #107	; 0x6b
101019a8:	62c5      	str	r5, [r0, #44]	; 0x2c
101019aa:	f44f 7544 	mov.w	r5, #784	; 0x310
101019ae:	2300      	movs	r3, #0
101019b0:	2201      	movs	r2, #1
101019b2:	2406      	movs	r4, #6
101019b4:	21bb      	movs	r1, #187	; 0xbb
101019b6:	6485      	str	r5, [r0, #72]	; 0x48
101019b8:	f04f 0904 	mov.w	r9, #4
101019bc:	27eb      	movs	r7, #235	; 0xeb
101019be:	f04f 0b05 	mov.w	fp, #5
101019c2:	f04f 0a60 	mov.w	sl, #96	; 0x60
101019c6:	f04f 08d8 	mov.w	r8, #216	; 0xd8
101019ca:	f04f 0c20 	mov.w	ip, #32
101019ce:	f04f 0eab 	mov.w	lr, #171	; 0xab
101019d2:	26b9      	movs	r6, #185	; 0xb9
101019d4:	f06f 0560 	mvn.w	r5, #96	; 0x60
101019d8:	6183      	str	r3, [r0, #24]
101019da:	7783      	strb	r3, [r0, #30]
101019dc:	6343      	str	r3, [r0, #52]	; 0x34
101019de:	6383      	str	r3, [r0, #56]	; 0x38
101019e0:	63c3      	str	r3, [r0, #60]	; 0x3c
101019e2:	f880 304f 	strb.w	r3, [r0, #79]	; 0x4f
101019e6:	f880 3051 	strb.w	r3, [r0, #81]	; 0x51
101019ea:	f880 3058 	strb.w	r3, [r0, #88]	; 0x58
101019ee:	f880 901f 	strb.w	r9, [r0, #31]
101019f2:	6307      	str	r7, [r0, #48]	; 0x30
101019f4:	f880 504d 	strb.w	r5, [r0, #77]	; 0x4d
101019f8:	f880 b04e 	strb.w	fp, [r0, #78]	; 0x4e
101019fc:	f880 a052 	strb.w	sl, [r0, #82]	; 0x52
10101a00:	f880 8053 	strb.w	r8, [r0, #83]	; 0x53
10101a04:	f880 c054 	strb.w	ip, [r0, #84]	; 0x54
10101a08:	f880 e055 	strb.w	lr, [r0, #85]	; 0x55
10101a0c:	f880 6056 	strb.w	r6, [r0, #86]	; 0x56
10101a10:	6002      	str	r2, [r0, #0]
10101a12:	7142      	strb	r2, [r0, #5]
10101a14:	6102      	str	r2, [r0, #16]
10101a16:	7742      	strb	r2, [r0, #29]
10101a18:	f880 2050 	strb.w	r2, [r0, #80]	; 0x50
10101a1c:	f880 4020 	strb.w	r4, [r0, #32]
10101a20:	f880 404c 	strb.w	r4, [r0, #76]	; 0x4c
10101a24:	6281      	str	r1, [r0, #40]	; 0x28
10101a26:	f880 305a 	strb.w	r3, [r0, #90]	; 0x5a
10101a2a:	f04f 0303 	mov.w	r3, #3
10101a2e:	65c1      	str	r1, [r0, #92]	; 0x5c
10101a30:	f880 3059 	strb.w	r3, [r0, #89]	; 0x59
10101a34:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}

10101a38 <FLASH_StructInit_GD>:
10101a38:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10101a3c:	f44f 7600 	mov.w	r6, #512	; 0x200
10101a40:	60c6      	str	r6, [r0, #12]
10101a42:	2602      	movs	r6, #2
10101a44:	6146      	str	r6, [r0, #20]
10101a46:	263b      	movs	r6, #59	; 0x3b
10101a48:	6246      	str	r6, [r0, #36]	; 0x24
10101a4a:	f44f 7601 	mov.w	r6, #516	; 0x204
10101a4e:	6446      	str	r6, [r0, #68]	; 0x44
10101a50:	2632      	movs	r6, #50	; 0x32
10101a52:	6406      	str	r6, [r0, #64]	; 0x40
10101a54:	266b      	movs	r6, #107	; 0x6b
10101a56:	62c6      	str	r6, [r0, #44]	; 0x2c
10101a58:	f44f 7644 	mov.w	r6, #784	; 0x310
10101a5c:	6486      	str	r6, [r0, #72]	; 0x48
10101a5e:	f06f 0660 	mvn.w	r6, #96	; 0x60
10101a62:	2300      	movs	r3, #0
10101a64:	2201      	movs	r2, #1
10101a66:	2505      	movs	r5, #5
10101a68:	2406      	movs	r4, #6
10101a6a:	21bb      	movs	r1, #187	; 0xbb
10101a6c:	f880 604d 	strb.w	r6, [r0, #77]	; 0x4d
10101a70:	f04f 0904 	mov.w	r9, #4
10101a74:	27eb      	movs	r7, #235	; 0xeb
10101a76:	f04f 0b60 	mov.w	fp, #96	; 0x60
10101a7a:	f04f 0ad8 	mov.w	sl, #216	; 0xd8
10101a7e:	f04f 0820 	mov.w	r8, #32
10101a82:	f04f 0cab 	mov.w	ip, #171	; 0xab
10101a86:	f04f 0eb9 	mov.w	lr, #185	; 0xb9
10101a8a:	f04f 0635 	mov.w	r6, #53	; 0x35
10101a8e:	7783      	strb	r3, [r0, #30]
10101a90:	6343      	str	r3, [r0, #52]	; 0x34
10101a92:	6383      	str	r3, [r0, #56]	; 0x38
10101a94:	63c3      	str	r3, [r0, #60]	; 0x3c
10101a96:	f880 3051 	strb.w	r3, [r0, #81]	; 0x51
10101a9a:	f880 3058 	strb.w	r3, [r0, #88]	; 0x58
10101a9e:	f880 901f 	strb.w	r9, [r0, #31]
10101aa2:	6307      	str	r7, [r0, #48]	; 0x30
10101aa4:	f880 604f 	strb.w	r6, [r0, #79]	; 0x4f
10101aa8:	f880 b052 	strb.w	fp, [r0, #82]	; 0x52
10101aac:	f880 a053 	strb.w	sl, [r0, #83]	; 0x53
10101ab0:	f880 8054 	strb.w	r8, [r0, #84]	; 0x54
10101ab4:	f880 c055 	strb.w	ip, [r0, #85]	; 0x55
10101ab8:	f880 e056 	strb.w	lr, [r0, #86]	; 0x56
10101abc:	6005      	str	r5, [r0, #0]
10101abe:	f880 504e 	strb.w	r5, [r0, #78]	; 0x4e
10101ac2:	7142      	strb	r2, [r0, #5]
10101ac4:	6102      	str	r2, [r0, #16]
10101ac6:	6182      	str	r2, [r0, #24]
10101ac8:	7742      	strb	r2, [r0, #29]
10101aca:	f880 2050 	strb.w	r2, [r0, #80]	; 0x50
10101ace:	f880 4020 	strb.w	r4, [r0, #32]
10101ad2:	f880 404c 	strb.w	r4, [r0, #76]	; 0x4c
10101ad6:	6281      	str	r1, [r0, #40]	; 0x28
10101ad8:	f880 305a 	strb.w	r3, [r0, #90]	; 0x5a
10101adc:	f04f 0303 	mov.w	r3, #3
10101ae0:	65c1      	str	r1, [r0, #92]	; 0x5c
10101ae2:	f880 3059 	strb.w	r3, [r0, #89]	; 0x59
10101ae6:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10101aea:	bf00      	nop

10101aec <FLASH_StructInit>:
10101aec:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10101af0:	f44f 7600 	mov.w	r6, #512	; 0x200
10101af4:	60c6      	str	r6, [r0, #12]
10101af6:	263b      	movs	r6, #59	; 0x3b
10101af8:	6246      	str	r6, [r0, #36]	; 0x24
10101afa:	f44f 7601 	mov.w	r6, #516	; 0x204
10101afe:	6446      	str	r6, [r0, #68]	; 0x44
10101b00:	2632      	movs	r6, #50	; 0x32
10101b02:	6406      	str	r6, [r0, #64]	; 0x40
10101b04:	26eb      	movs	r6, #235	; 0xeb
10101b06:	6306      	str	r6, [r0, #48]	; 0x30
10101b08:	f44f 7644 	mov.w	r6, #784	; 0x310
10101b0c:	6486      	str	r6, [r0, #72]	; 0x48
10101b0e:	f06f 0660 	mvn.w	r6, #96	; 0x60
10101b12:	f880 604d 	strb.w	r6, [r0, #77]	; 0x4d
10101b16:	f04f 0605 	mov.w	r6, #5
10101b1a:	2300      	movs	r3, #0
10101b1c:	2201      	movs	r2, #1
10101b1e:	2502      	movs	r5, #2
10101b20:	2406      	movs	r4, #6
10101b22:	21bb      	movs	r1, #187	; 0xbb
10101b24:	f880 604e 	strb.w	r6, [r0, #78]	; 0x4e
10101b28:	f04f 0a04 	mov.w	sl, #4
10101b2c:	276b      	movs	r7, #107	; 0x6b
10101b2e:	f04f 0b60 	mov.w	fp, #96	; 0x60
10101b32:	f04f 09d8 	mov.w	r9, #216	; 0xd8
10101b36:	f04f 0820 	mov.w	r8, #32
10101b3a:	f04f 0cab 	mov.w	ip, #171	; 0xab
10101b3e:	f04f 0eb9 	mov.w	lr, #185	; 0xb9
10101b42:	f04f 0635 	mov.w	r6, #53	; 0x35
10101b46:	7783      	strb	r3, [r0, #30]
10101b48:	6343      	str	r3, [r0, #52]	; 0x34
10101b4a:	6383      	str	r3, [r0, #56]	; 0x38
10101b4c:	63c3      	str	r3, [r0, #60]	; 0x3c
10101b4e:	f880 3051 	strb.w	r3, [r0, #81]	; 0x51
10101b52:	f880 3058 	strb.w	r3, [r0, #88]	; 0x58
10101b56:	f880 a01f 	strb.w	sl, [r0, #31]
10101b5a:	62c7      	str	r7, [r0, #44]	; 0x2c
10101b5c:	f880 604f 	strb.w	r6, [r0, #79]	; 0x4f
10101b60:	f880 b052 	strb.w	fp, [r0, #82]	; 0x52
10101b64:	f880 9053 	strb.w	r9, [r0, #83]	; 0x53
10101b68:	f880 8054 	strb.w	r8, [r0, #84]	; 0x54
10101b6c:	f880 c055 	strb.w	ip, [r0, #85]	; 0x55
10101b70:	f880 e056 	strb.w	lr, [r0, #86]	; 0x56
10101b74:	6005      	str	r5, [r0, #0]
10101b76:	6145      	str	r5, [r0, #20]
10101b78:	7142      	strb	r2, [r0, #5]
10101b7a:	6102      	str	r2, [r0, #16]
10101b7c:	6182      	str	r2, [r0, #24]
10101b7e:	7742      	strb	r2, [r0, #29]
10101b80:	f880 2050 	strb.w	r2, [r0, #80]	; 0x50
10101b84:	f880 4020 	strb.w	r4, [r0, #32]
10101b88:	f880 404c 	strb.w	r4, [r0, #76]	; 0x4c
10101b8c:	6281      	str	r1, [r0, #40]	; 0x28
10101b8e:	f880 305a 	strb.w	r3, [r0, #90]	; 0x5a
10101b92:	f04f 0303 	mov.w	r3, #3
10101b96:	65c1      	str	r1, [r0, #92]	; 0x5c
10101b98:	f880 3059 	strb.w	r3, [r0, #89]	; 0x59
10101b9c:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}

10101ba0 <FLASH_Init>:
10101ba0:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
10101ba2:	2600      	movs	r6, #0
10101ba4:	2401      	movs	r4, #1
10101ba6:	4605      	mov	r5, r0
10101ba8:	2004      	movs	r0, #4
10101baa:	4b1c      	ldr	r3, [pc, #112]	; (10101c1c <FLASH_Init+0x7c>)
10101bac:	4a1c      	ldr	r2, [pc, #112]	; (10101c20 <FLASH_Init+0x80>)
10101bae:	7951      	ldrb	r1, [r2, #5]
10101bb0:	6dd7      	ldr	r7, [r2, #92]	; 0x5c
10101bb2:	609e      	str	r6, [r3, #8]
10101bb4:	6a96      	ldr	r6, [r2, #40]	; 0x28
10101bb6:	6159      	str	r1, [r3, #20]
10101bb8:	6b51      	ldr	r1, [r2, #52]	; 0x34
10101bba:	611c      	str	r4, [r3, #16]
10101bbc:	f8c3 70e0 	str.w	r7, [r3, #224]	; 0xe0
10101bc0:	f8c3 60e8 	str.w	r6, [r3, #232]	; 0xe8
10101bc4:	6a57      	ldr	r7, [r2, #36]	; 0x24
10101bc6:	6b96      	ldr	r6, [r2, #56]	; 0x38
10101bc8:	f8c3 70e4 	str.w	r7, [r3, #228]	; 0xe4
10101bcc:	6bd7      	ldr	r7, [r2, #60]	; 0x3c
10101bce:	f8c3 10f8 	str.w	r1, [r3, #248]	; 0xf8
10101bd2:	6c11      	ldr	r1, [r2, #64]	; 0x40
10101bd4:	f8c3 60fc 	str.w	r6, [r3, #252]	; 0xfc
10101bd8:	6b16      	ldr	r6, [r2, #48]	; 0x30
10101bda:	f8c3 7100 	str.w	r7, [r3, #256]	; 0x100
10101bde:	6ad7      	ldr	r7, [r2, #44]	; 0x2c
10101be0:	f8c3 1104 	str.w	r1, [r3, #260]	; 0x104
10101be4:	f8c3 60f0 	str.w	r6, [r3, #240]	; 0xf0
10101be8:	f8c3 70ec 	str.w	r7, [r3, #236]	; 0xec
10101bec:	f8d3 1110 	ldr.w	r1, [r3, #272]	; 0x110
10101bf0:	4321      	orrs	r1, r4
10101bf2:	f8c3 1110 	str.w	r1, [r3, #272]	; 0x110
10101bf6:	f8d3 1110 	ldr.w	r1, [r3, #272]	; 0x110
10101bfa:	f892 6059 	ldrb.w	r6, [r2, #89]	; 0x59
10101bfe:	f021 0102 	bic.w	r1, r1, #2
10101c02:	f8c3 1110 	str.w	r1, [r3, #272]	; 0x110
10101c06:	6058      	str	r0, [r3, #4]
10101c08:	4629      	mov	r1, r5
10101c0a:	4610      	mov	r0, r2
10101c0c:	f8c3 6118 	str.w	r6, [r3, #280]	; 0x118
10101c10:	7115      	strb	r5, [r2, #4]
10101c12:	f7ff fbb3 	bl	1010137c <FLASH_SetSpiMode>
10101c16:	4620      	mov	r0, r4
10101c18:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10101c1a:	bf00      	nop
10101c1c:	48080000 	.word	0x48080000
10101c20:	10000038 	.word	0x10000038

10101c24 <GDMA_StructInit>:
10101c24:	b510      	push	{r4, lr}
10101c26:	2254      	movs	r2, #84	; 0x54
10101c28:	4b05      	ldr	r3, [pc, #20]	; (10101c40 <GDMA_StructInit+0x1c>)
10101c2a:	2100      	movs	r1, #0
10101c2c:	4604      	mov	r4, r0
10101c2e:	4798      	blx	r3
10101c30:	2302      	movs	r3, #2
10101c32:	2200      	movs	r2, #0
10101c34:	60e3      	str	r3, [r4, #12]
10101c36:	6522      	str	r2, [r4, #80]	; 0x50
10101c38:	60a3      	str	r3, [r4, #8]
10101c3a:	61e3      	str	r3, [r4, #28]
10101c3c:	61a3      	str	r3, [r4, #24]
10101c3e:	bd10      	pop	{r4, pc}
10101c40:	10106e89 	.word	0x10106e89

10101c44 <GDMA_SetLLP>:
10101c44:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
10101c46:	f8df e08c 	ldr.w	lr, [pc, #140]	; 10101cd4 <GDMA_SetLLP+0x90>
10101c4a:	4c1f      	ldr	r4, [pc, #124]	; (10101cc8 <GDMA_SetLLP+0x84>)
10101c4c:	e844 f400 	tt	r4, r4
10101c50:	f414 0f80 	tst.w	r4, #4194304	; 0x400000
10101c54:	4f1d      	ldr	r7, [pc, #116]	; (10101ccc <GDMA_SetLLP+0x88>)
10101c56:	460e      	mov	r6, r1
10101c58:	4615      	mov	r5, r2
10101c5a:	461c      	mov	r4, r3
10101c5c:	bf08      	it	eq
10101c5e:	4677      	moveq	r7, lr
10101c60:	bb68      	cbnz	r0, 10101cbe <GDMA_SetLLP+0x7a>
10101c62:	2e05      	cmp	r6, #5
10101c64:	d826      	bhi.n	10101cb4 <GDMA_SetLLP+0x70>
10101c66:	2158      	movs	r1, #88	; 0x58
10101c68:	fb01 7106 	mla	r1, r1, r6, r7
10101c6c:	69a6      	ldr	r6, [r4, #24]
10101c6e:	698f      	ldr	r7, [r1, #24]
10101c70:	69ca      	ldr	r2, [r1, #28]
10101c72:	f3c6 000b 	ubfx	r0, r6, #0, #12
10101c76:	4302      	orrs	r2, r0
10101c78:	61ca      	str	r2, [r1, #28]
10101c7a:	610c      	str	r4, [r1, #16]
10101c7c:	b95d      	cbnz	r5, 10101c96 <GDMA_SetLLP+0x52>
10101c7e:	e018      	b.n	10101cb2 <GDMA_SetLLP+0x6e>
10101c80:	69e3      	ldr	r3, [r4, #28]
10101c82:	f360 020b 	bfi	r2, r0, #0, #12
10101c86:	699e      	ldr	r6, [r3, #24]
10101c88:	6122      	str	r2, [r4, #16]
10101c8a:	60e7      	str	r7, [r4, #12]
10101c8c:	60a3      	str	r3, [r4, #8]
10101c8e:	461c      	mov	r4, r3
10101c90:	3d01      	subs	r5, #1
10101c92:	f3c6 000b 	ubfx	r0, r6, #0, #12
10101c96:	2d01      	cmp	r5, #1
10101c98:	d1f2      	bne.n	10101c80 <GDMA_SetLLP+0x3c>
10101c9a:	f422 627f 	bic.w	r2, r2, #4080	; 0xff0
10101c9e:	f022 020f 	bic.w	r2, r2, #15
10101ca2:	69e3      	ldr	r3, [r4, #28]
10101ca4:	4302      	orrs	r2, r0
10101ca6:	f027 57c0 	bic.w	r7, r7, #402653184	; 0x18000000
10101caa:	6122      	str	r2, [r4, #16]
10101cac:	60e7      	str	r7, [r4, #12]
10101cae:	60a3      	str	r3, [r4, #8]
10101cb0:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10101cb2:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10101cb4:	21b8      	movs	r1, #184	; 0xb8
10101cb6:	4806      	ldr	r0, [pc, #24]	; (10101cd0 <GDMA_SetLLP+0x8c>)
10101cb8:	f7fe fdda 	bl	10100870 <io_assert_failed>
10101cbc:	e7d3      	b.n	10101c66 <GDMA_SetLLP+0x22>
10101cbe:	21b7      	movs	r1, #183	; 0xb7
10101cc0:	4803      	ldr	r0, [pc, #12]	; (10101cd0 <GDMA_SetLLP+0x8c>)
10101cc2:	f7fe fdd5 	bl	10100870 <io_assert_failed>
10101cc6:	e7cc      	b.n	10101c62 <GDMA_SetLLP+0x1e>
10101cc8:	101003f5 	.word	0x101003f5
10101ccc:	5002a000 	.word	0x5002a000
10101cd0:	101d5040 	.word	0x101d5040
10101cd4:	4002a000 	.word	0x4002a000

10101cd8 <GDMA_ClearINTPendingBit>:
10101cd8:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
10101cda:	4f2e      	ldr	r7, [pc, #184]	; (10101d94 <GDMA_ClearINTPendingBit+0xbc>)
10101cdc:	4b2e      	ldr	r3, [pc, #184]	; (10101d98 <GDMA_ClearINTPendingBit+0xc0>)
10101cde:	e843 f300 	tt	r3, r3
10101ce2:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
10101ce6:	4c2d      	ldr	r4, [pc, #180]	; (10101d9c <GDMA_ClearINTPendingBit+0xc4>)
10101ce8:	460e      	mov	r6, r1
10101cea:	4615      	mov	r5, r2
10101cec:	bf08      	it	eq
10101cee:	463c      	moveq	r4, r7
10101cf0:	2800      	cmp	r0, #0
10101cf2:	d143      	bne.n	10101d7c <GDMA_ClearINTPendingBit+0xa4>
10101cf4:	2e05      	cmp	r6, #5
10101cf6:	d847      	bhi.n	10101d88 <GDMA_ClearINTPendingBit+0xb0>
10101cf8:	f035 031f 	bics.w	r3, r5, #31
10101cfc:	d100      	bne.n	10101d00 <GDMA_ClearINTPendingBit+0x28>
10101cfe:	b91d      	cbnz	r5, 10101d08 <GDMA_ClearINTPendingBit+0x30>
10101d00:	21fb      	movs	r1, #251	; 0xfb
10101d02:	4827      	ldr	r0, [pc, #156]	; (10101da0 <GDMA_ClearINTPendingBit+0xc8>)
10101d04:	f7fe fdb4 	bl	10100870 <io_assert_failed>
10101d08:	2001      	movs	r0, #1
10101d0a:	f8d4 32c0 	ldr.w	r3, [r4, #704]	; 0x2c0
10101d0e:	40b0      	lsls	r0, r6
10101d10:	4203      	tst	r3, r0
10101d12:	bf18      	it	ne
10101d14:	f8d4 32e8 	ldrne.w	r3, [r4, #744]	; 0x2e8
10101d18:	f8d4 32c8 	ldr.w	r3, [r4, #712]	; 0x2c8
10101d1c:	4218      	tst	r0, r3
10101d1e:	bf18      	it	ne
10101d20:	f8d4 32f0 	ldrne.w	r3, [r4, #752]	; 0x2f0
10101d24:	f8d4 32d0 	ldr.w	r3, [r4, #720]	; 0x2d0
10101d28:	4218      	tst	r0, r3
10101d2a:	bf18      	it	ne
10101d2c:	f8d4 32f8 	ldrne.w	r3, [r4, #760]	; 0x2f8
10101d30:	f8d4 32d8 	ldr.w	r3, [r4, #728]	; 0x2d8
10101d34:	4218      	tst	r0, r3
10101d36:	bf18      	it	ne
10101d38:	f8d4 3300 	ldrne.w	r3, [r4, #768]	; 0x300
10101d3c:	f8d4 32e0 	ldr.w	r3, [r4, #736]	; 0x2e0
10101d40:	4218      	tst	r0, r3
10101d42:	bf18      	it	ne
10101d44:	f8d4 3308 	ldrne.w	r3, [r4, #776]	; 0x308
10101d48:	2301      	movs	r3, #1
10101d4a:	3608      	adds	r6, #8
10101d4c:	fa03 f606 	lsl.w	r6, r3, r6
10101d50:	4330      	orrs	r0, r6
10101d52:	07ef      	lsls	r7, r5, #31
10101d54:	bf48      	it	mi
10101d56:	f8c4 0338 	strmi.w	r0, [r4, #824]	; 0x338
10101d5a:	07ae      	lsls	r6, r5, #30
10101d5c:	bf48      	it	mi
10101d5e:	f8c4 0340 	strmi.w	r0, [r4, #832]	; 0x340
10101d62:	0769      	lsls	r1, r5, #29
10101d64:	bf48      	it	mi
10101d66:	f8c4 0348 	strmi.w	r0, [r4, #840]	; 0x348
10101d6a:	072a      	lsls	r2, r5, #28
10101d6c:	bf48      	it	mi
10101d6e:	f8c4 0350 	strmi.w	r0, [r4, #848]	; 0x350
10101d72:	06eb      	lsls	r3, r5, #27
10101d74:	bf48      	it	mi
10101d76:	f8c4 0358 	strmi.w	r0, [r4, #856]	; 0x358
10101d7a:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10101d7c:	21f9      	movs	r1, #249	; 0xf9
10101d7e:	4808      	ldr	r0, [pc, #32]	; (10101da0 <GDMA_ClearINTPendingBit+0xc8>)
10101d80:	f7fe fd76 	bl	10100870 <io_assert_failed>
10101d84:	2e05      	cmp	r6, #5
10101d86:	d9b7      	bls.n	10101cf8 <GDMA_ClearINTPendingBit+0x20>
10101d88:	21fa      	movs	r1, #250	; 0xfa
10101d8a:	4805      	ldr	r0, [pc, #20]	; (10101da0 <GDMA_ClearINTPendingBit+0xc8>)
10101d8c:	f7fe fd70 	bl	10100870 <io_assert_failed>
10101d90:	e7b2      	b.n	10101cf8 <GDMA_ClearINTPendingBit+0x20>
10101d92:	bf00      	nop
10101d94:	4002a000 	.word	0x4002a000
10101d98:	101003f5 	.word	0x101003f5
10101d9c:	5002a000 	.word	0x5002a000
10101da0:	101d504c 	.word	0x101d504c

10101da4 <GDMA_ClearINT>:
10101da4:	4a2f      	ldr	r2, [pc, #188]	; (10101e64 <GDMA_ClearINT+0xc0>)
10101da6:	b538      	push	{r3, r4, r5, lr}
10101da8:	4b2f      	ldr	r3, [pc, #188]	; (10101e68 <GDMA_ClearINT+0xc4>)
10101daa:	e843 f300 	tt	r3, r3
10101dae:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
10101db2:	4c2e      	ldr	r4, [pc, #184]	; (10101e6c <GDMA_ClearINT+0xc8>)
10101db4:	460d      	mov	r5, r1
10101db6:	bf08      	it	eq
10101db8:	4614      	moveq	r4, r2
10101dba:	2800      	cmp	r0, #0
10101dbc:	d145      	bne.n	10101e4a <GDMA_ClearINT+0xa6>
10101dbe:	2d05      	cmp	r5, #5
10101dc0:	d84a      	bhi.n	10101e58 <GDMA_ClearINT+0xb4>
10101dc2:	2301      	movs	r3, #1
10101dc4:	f8d4 02c0 	ldr.w	r0, [r4, #704]	; 0x2c0
10101dc8:	40ab      	lsls	r3, r5
10101dca:	4018      	ands	r0, r3
10101dcc:	d005      	beq.n	10101dda <GDMA_ClearINT+0x36>
10101dce:	f8d4 22e8 	ldr.w	r2, [r4, #744]	; 0x2e8
10101dd2:	4213      	tst	r3, r2
10101dd4:	bf14      	ite	ne
10101dd6:	2001      	movne	r0, #1
10101dd8:	2000      	moveq	r0, #0
10101dda:	f8d4 22c8 	ldr.w	r2, [r4, #712]	; 0x2c8
10101dde:	4213      	tst	r3, r2
10101de0:	d005      	beq.n	10101dee <GDMA_ClearINT+0x4a>
10101de2:	f8d4 22f0 	ldr.w	r2, [r4, #752]	; 0x2f0
10101de6:	4213      	tst	r3, r2
10101de8:	bf18      	it	ne
10101dea:	f040 0002 	orrne.w	r0, r0, #2
10101dee:	f8d4 22d0 	ldr.w	r2, [r4, #720]	; 0x2d0
10101df2:	4213      	tst	r3, r2
10101df4:	d005      	beq.n	10101e02 <GDMA_ClearINT+0x5e>
10101df6:	f8d4 22f8 	ldr.w	r2, [r4, #760]	; 0x2f8
10101dfa:	4213      	tst	r3, r2
10101dfc:	bf18      	it	ne
10101dfe:	f040 0004 	orrne.w	r0, r0, #4
10101e02:	f8d4 22d8 	ldr.w	r2, [r4, #728]	; 0x2d8
10101e06:	4213      	tst	r3, r2
10101e08:	d005      	beq.n	10101e16 <GDMA_ClearINT+0x72>
10101e0a:	f8d4 2300 	ldr.w	r2, [r4, #768]	; 0x300
10101e0e:	4213      	tst	r3, r2
10101e10:	bf18      	it	ne
10101e12:	f040 0008 	orrne.w	r0, r0, #8
10101e16:	f8d4 22e0 	ldr.w	r2, [r4, #736]	; 0x2e0
10101e1a:	4213      	tst	r3, r2
10101e1c:	d005      	beq.n	10101e2a <GDMA_ClearINT+0x86>
10101e1e:	f8d4 2308 	ldr.w	r2, [r4, #776]	; 0x308
10101e22:	4213      	tst	r3, r2
10101e24:	bf18      	it	ne
10101e26:	f040 0010 	orrne.w	r0, r0, #16
10101e2a:	2201      	movs	r2, #1
10101e2c:	3508      	adds	r5, #8
10101e2e:	fa02 f505 	lsl.w	r5, r2, r5
10101e32:	432b      	orrs	r3, r5
10101e34:	f8c4 3338 	str.w	r3, [r4, #824]	; 0x338
10101e38:	f8c4 3340 	str.w	r3, [r4, #832]	; 0x340
10101e3c:	f8c4 3348 	str.w	r3, [r4, #840]	; 0x348
10101e40:	f8c4 3350 	str.w	r3, [r4, #848]	; 0x350
10101e44:	f8c4 3358 	str.w	r3, [r4, #856]	; 0x358
10101e48:	bd38      	pop	{r3, r4, r5, pc}
10101e4a:	f240 1137 	movw	r1, #311	; 0x137
10101e4e:	4808      	ldr	r0, [pc, #32]	; (10101e70 <GDMA_ClearINT+0xcc>)
10101e50:	f7fe fd0e 	bl	10100870 <io_assert_failed>
10101e54:	2d05      	cmp	r5, #5
10101e56:	d9b4      	bls.n	10101dc2 <GDMA_ClearINT+0x1e>
10101e58:	f44f 719c 	mov.w	r1, #312	; 0x138
10101e5c:	4804      	ldr	r0, [pc, #16]	; (10101e70 <GDMA_ClearINT+0xcc>)
10101e5e:	f7fe fd07 	bl	10100870 <io_assert_failed>
10101e62:	e7ae      	b.n	10101dc2 <GDMA_ClearINT+0x1e>
10101e64:	4002a000 	.word	0x4002a000
10101e68:	101003f5 	.word	0x101003f5
10101e6c:	5002a000 	.word	0x5002a000
10101e70:	101d50cc 	.word	0x101d50cc

10101e74 <GDMA_INTConfig>:
10101e74:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
10101e76:	f8df e114 	ldr.w	lr, [pc, #276]	; 10101f8c <GDMA_INTConfig+0x118>
10101e7a:	4d41      	ldr	r5, [pc, #260]	; (10101f80 <GDMA_INTConfig+0x10c>)
10101e7c:	e845 f500 	tt	r5, r5
10101e80:	f415 0f80 	tst.w	r5, #4194304	; 0x400000
10101e84:	4c3f      	ldr	r4, [pc, #252]	; (10101f84 <GDMA_INTConfig+0x110>)
10101e86:	460e      	mov	r6, r1
10101e88:	4615      	mov	r5, r2
10101e8a:	461f      	mov	r7, r3
10101e8c:	bf08      	it	eq
10101e8e:	4674      	moveq	r4, lr
10101e90:	2800      	cmp	r0, #0
10101e92:	d16e      	bne.n	10101f72 <GDMA_INTConfig+0xfe>
10101e94:	2e05      	cmp	r6, #5
10101e96:	d866      	bhi.n	10101f66 <GDMA_INTConfig+0xf2>
10101e98:	f035 031f 	bics.w	r3, r5, #31
10101e9c:	d12e      	bne.n	10101efc <GDMA_INTConfig+0x88>
10101e9e:	b36d      	cbz	r5, 10101efc <GDMA_INTConfig+0x88>
10101ea0:	b39f      	cbz	r7, 10101f0a <GDMA_INTConfig+0x96>
10101ea2:	2101      	movs	r1, #1
10101ea4:	f106 0308 	add.w	r3, r6, #8
10101ea8:	fa01 f203 	lsl.w	r2, r1, r3
10101eac:	07ef      	lsls	r7, r5, #31
10101eae:	fa01 f306 	lsl.w	r3, r1, r6
10101eb2:	ea43 0302 	orr.w	r3, r3, r2
10101eb6:	d504      	bpl.n	10101ec2 <GDMA_INTConfig+0x4e>
10101eb8:	f8d4 2310 	ldr.w	r2, [r4, #784]	; 0x310
10101ebc:	431a      	orrs	r2, r3
10101ebe:	f8c4 2310 	str.w	r2, [r4, #784]	; 0x310
10101ec2:	07ae      	lsls	r6, r5, #30
10101ec4:	d504      	bpl.n	10101ed0 <GDMA_INTConfig+0x5c>
10101ec6:	f8d4 2318 	ldr.w	r2, [r4, #792]	; 0x318
10101eca:	431a      	orrs	r2, r3
10101ecc:	f8c4 2318 	str.w	r2, [r4, #792]	; 0x318
10101ed0:	0768      	lsls	r0, r5, #29
10101ed2:	d504      	bpl.n	10101ede <GDMA_INTConfig+0x6a>
10101ed4:	f8d4 2320 	ldr.w	r2, [r4, #800]	; 0x320
10101ed8:	431a      	orrs	r2, r3
10101eda:	f8c4 2320 	str.w	r2, [r4, #800]	; 0x320
10101ede:	0729      	lsls	r1, r5, #28
10101ee0:	d504      	bpl.n	10101eec <GDMA_INTConfig+0x78>
10101ee2:	f8d4 2328 	ldr.w	r2, [r4, #808]	; 0x328
10101ee6:	431a      	orrs	r2, r3
10101ee8:	f8c4 2328 	str.w	r2, [r4, #808]	; 0x328
10101eec:	06ea      	lsls	r2, r5, #27
10101eee:	d539      	bpl.n	10101f64 <GDMA_INTConfig+0xf0>
10101ef0:	f8d4 2330 	ldr.w	r2, [r4, #816]	; 0x330
10101ef4:	4313      	orrs	r3, r2
10101ef6:	f8c4 3330 	str.w	r3, [r4, #816]	; 0x330
10101efa:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10101efc:	f240 116f 	movw	r1, #367	; 0x16f
10101f00:	4821      	ldr	r0, [pc, #132]	; (10101f88 <GDMA_INTConfig+0x114>)
10101f02:	f7fe fcb5 	bl	10100870 <io_assert_failed>
10101f06:	2f00      	cmp	r7, #0
10101f08:	d1cb      	bne.n	10101ea2 <GDMA_INTConfig+0x2e>
10101f0a:	2201      	movs	r2, #1
10101f0c:	f106 0308 	add.w	r3, r6, #8
10101f10:	fa02 f103 	lsl.w	r1, r2, r3
10101f14:	fa02 f306 	lsl.w	r3, r2, r6
10101f18:	430b      	orrs	r3, r1
10101f1a:	07ef      	lsls	r7, r5, #31
10101f1c:	ea6f 0303 	mvn.w	r3, r3
10101f20:	d504      	bpl.n	10101f2c <GDMA_INTConfig+0xb8>
10101f22:	f8d4 2310 	ldr.w	r2, [r4, #784]	; 0x310
10101f26:	401a      	ands	r2, r3
10101f28:	f8c4 2310 	str.w	r2, [r4, #784]	; 0x310
10101f2c:	07ae      	lsls	r6, r5, #30
10101f2e:	d504      	bpl.n	10101f3a <GDMA_INTConfig+0xc6>
10101f30:	f8d4 2318 	ldr.w	r2, [r4, #792]	; 0x318
10101f34:	401a      	ands	r2, r3
10101f36:	f8c4 2318 	str.w	r2, [r4, #792]	; 0x318
10101f3a:	0768      	lsls	r0, r5, #29
10101f3c:	d504      	bpl.n	10101f48 <GDMA_INTConfig+0xd4>
10101f3e:	f8d4 2320 	ldr.w	r2, [r4, #800]	; 0x320
10101f42:	401a      	ands	r2, r3
10101f44:	f8c4 2320 	str.w	r2, [r4, #800]	; 0x320
10101f48:	0729      	lsls	r1, r5, #28
10101f4a:	d504      	bpl.n	10101f56 <GDMA_INTConfig+0xe2>
10101f4c:	f8d4 2328 	ldr.w	r2, [r4, #808]	; 0x328
10101f50:	401a      	ands	r2, r3
10101f52:	f8c4 2328 	str.w	r2, [r4, #808]	; 0x328
10101f56:	06ea      	lsls	r2, r5, #27
10101f58:	d504      	bpl.n	10101f64 <GDMA_INTConfig+0xf0>
10101f5a:	f8d4 2330 	ldr.w	r2, [r4, #816]	; 0x330
10101f5e:	4013      	ands	r3, r2
10101f60:	f8c4 3330 	str.w	r3, [r4, #816]	; 0x330
10101f64:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10101f66:	f44f 71b7 	mov.w	r1, #366	; 0x16e
10101f6a:	4807      	ldr	r0, [pc, #28]	; (10101f88 <GDMA_INTConfig+0x114>)
10101f6c:	f7fe fc80 	bl	10100870 <io_assert_failed>
10101f70:	e792      	b.n	10101e98 <GDMA_INTConfig+0x24>
10101f72:	f240 116d 	movw	r1, #365	; 0x16d
10101f76:	4804      	ldr	r0, [pc, #16]	; (10101f88 <GDMA_INTConfig+0x114>)
10101f78:	f7fe fc7a 	bl	10100870 <io_assert_failed>
10101f7c:	e78a      	b.n	10101e94 <GDMA_INTConfig+0x20>
10101f7e:	bf00      	nop
10101f80:	101003f5 	.word	0x101003f5
10101f84:	5002a000 	.word	0x5002a000
10101f88:	101d5094 	.word	0x101d5094
10101f8c:	4002a000 	.word	0x4002a000

10101f90 <GDMA_Cmd>:
10101f90:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
10101f92:	4f15      	ldr	r7, [pc, #84]	; (10101fe8 <GDMA_Cmd+0x58>)
10101f94:	4b15      	ldr	r3, [pc, #84]	; (10101fec <GDMA_Cmd+0x5c>)
10101f96:	e843 f300 	tt	r3, r3
10101f9a:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
10101f9e:	4c14      	ldr	r4, [pc, #80]	; (10101ff0 <GDMA_Cmd+0x60>)
10101fa0:	460d      	mov	r5, r1
10101fa2:	4616      	mov	r6, r2
10101fa4:	bf18      	it	ne
10101fa6:	463c      	movne	r4, r7
10101fa8:	b980      	cbnz	r0, 10101fcc <GDMA_Cmd+0x3c>
10101faa:	2d05      	cmp	r5, #5
10101fac:	d815      	bhi.n	10101fda <GDMA_Cmd+0x4a>
10101fae:	2101      	movs	r1, #1
10101fb0:	f105 0308 	add.w	r3, r5, #8
10101fb4:	428e      	cmp	r6, r1
10101fb6:	fa01 f303 	lsl.w	r3, r1, r3
10101fba:	bf0b      	itete	eq
10101fbc:	fa06 f105 	lsleq.w	r1, r6, r5
10101fc0:	40a9      	lslne	r1, r5
10101fc2:	430b      	orreq	r3, r1
10101fc4:	438b      	bicne	r3, r1
10101fc6:	f8c4 33a0 	str.w	r3, [r4, #928]	; 0x3a0
10101fca:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10101fcc:	f44f 71da 	mov.w	r1, #436	; 0x1b4
10101fd0:	4808      	ldr	r0, [pc, #32]	; (10101ff4 <GDMA_Cmd+0x64>)
10101fd2:	f7fe fc4d 	bl	10100870 <io_assert_failed>
10101fd6:	2d05      	cmp	r5, #5
10101fd8:	d9e9      	bls.n	10101fae <GDMA_Cmd+0x1e>
10101fda:	f240 11b5 	movw	r1, #437	; 0x1b5
10101fde:	4805      	ldr	r0, [pc, #20]	; (10101ff4 <GDMA_Cmd+0x64>)
10101fe0:	f7fe fc46 	bl	10100870 <io_assert_failed>
10101fe4:	e7e3      	b.n	10101fae <GDMA_Cmd+0x1e>
10101fe6:	bf00      	nop
10101fe8:	5002a000 	.word	0x5002a000
10101fec:	101003f5 	.word	0x101003f5
10101ff0:	4002a000 	.word	0x4002a000
10101ff4:	101d5088 	.word	0x101d5088

10101ff8 <GDMA_Init>:
10101ff8:	2301      	movs	r3, #1
10101ffa:	e92d 43f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
10101ffe:	4614      	mov	r4, r2
10102000:	f101 0908 	add.w	r9, r1, #8
10102004:	fa03 f909 	lsl.w	r9, r3, r9
10102008:	4a47      	ldr	r2, [pc, #284]	; (10102128 <GDMA_Init+0x130>)
1010200a:	408b      	lsls	r3, r1
1010200c:	f8b4 8028 	ldrh.w	r8, [r4, #40]	; 0x28
10102010:	ea49 0903 	orr.w	r9, r9, r3
10102014:	4b45      	ldr	r3, [pc, #276]	; (1010212c <GDMA_Init+0x134>)
10102016:	e843 f300 	tt	r3, r3
1010201a:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
1010201e:	4e44      	ldr	r6, [pc, #272]	; (10102130 <GDMA_Init+0x138>)
10102020:	b083      	sub	sp, #12
10102022:	460d      	mov	r5, r1
10102024:	bf18      	it	ne
10102026:	4616      	movne	r6, r2
10102028:	4607      	mov	r7, r0
1010202a:	2800      	cmp	r0, #0
1010202c:	d172      	bne.n	10102114 <GDMA_Init+0x11c>
1010202e:	2d05      	cmp	r5, #5
10102030:	d86b      	bhi.n	1010210a <GDMA_Init+0x112>
10102032:	6d23      	ldr	r3, [r4, #80]	; 0x50
10102034:	2b00      	cmp	r3, #0
10102036:	d060      	beq.n	101020fa <GDMA_Init+0x102>
10102038:	2358      	movs	r3, #88	; 0x58
1010203a:	fb03 6305 	mla	r3, r3, r5, r6
1010203e:	6c5a      	ldr	r2, [r3, #68]	; 0x44
10102040:	f022 0208 	bic.w	r2, r2, #8
10102044:	645a      	str	r2, [r3, #68]	; 0x44
10102046:	2301      	movs	r3, #1
10102048:	f8c6 3398 	str.w	r3, [r6, #920]	; 0x398
1010204c:	f8d6 33a0 	ldr.w	r3, [r6, #928]	; 0x3a0
10102050:	ea19 0f03 	tst.w	r9, r3
10102054:	d008      	beq.n	10102068 <GDMA_Init+0x70>
10102056:	4b37      	ldr	r3, [pc, #220]	; (10102134 <GDMA_Init+0x13c>)
10102058:	685b      	ldr	r3, [r3, #4]
1010205a:	075b      	lsls	r3, r3, #29
1010205c:	d45f      	bmi.n	1010211e <GDMA_Init+0x126>
1010205e:	2200      	movs	r2, #0
10102060:	4629      	mov	r1, r5
10102062:	4638      	mov	r0, r7
10102064:	4b34      	ldr	r3, [pc, #208]	; (10102138 <GDMA_Init+0x140>)
10102066:	4798      	blx	r3
10102068:	4629      	mov	r1, r5
1010206a:	4638      	mov	r0, r7
1010206c:	4b33      	ldr	r3, [pc, #204]	; (1010213c <GDMA_Init+0x144>)
1010206e:	4798      	blx	r3
10102070:	2058      	movs	r0, #88	; 0x58
10102072:	fb00 f005 	mul.w	r0, r0, r5
10102076:	f104 0208 	add.w	r2, r4, #8
1010207a:	ca0c      	ldmia	r2, {r2, r3}
1010207c:	011b      	lsls	r3, r3, #4
1010207e:	6921      	ldr	r1, [r4, #16]
10102080:	ea43 0342 	orr.w	r3, r3, r2, lsl #1
10102084:	f043 0301 	orr.w	r3, r3, #1
10102088:	6962      	ldr	r2, [r4, #20]
1010208a:	ea43 13c1 	orr.w	r3, r3, r1, lsl #7
1010208e:	69a1      	ldr	r1, [r4, #24]
10102090:	ea43 2342 	orr.w	r3, r3, r2, lsl #9
10102094:	69e2      	ldr	r2, [r4, #28]
10102096:	ea43 23c1 	orr.w	r3, r3, r1, lsl #11
1010209a:	6861      	ldr	r1, [r4, #4]
1010209c:	ea43 3382 	orr.w	r3, r3, r2, lsl #14
101020a0:	6ba2      	ldr	r2, [r4, #56]	; 0x38
101020a2:	ea43 5301 	orr.w	r3, r3, r1, lsl #20
101020a6:	6be1      	ldr	r1, [r4, #60]	; 0x3c
101020a8:	ea43 63c2 	orr.w	r3, r3, r2, lsl #27
101020ac:	ea43 7e01 	orr.w	lr, r3, r1, lsl #28
101020b0:	6a23      	ldr	r3, [r4, #32]
101020b2:	6a61      	ldr	r1, [r4, #36]	; 0x24
101020b4:	f3c8 020b 	ubfx	r2, r8, #0, #12
101020b8:	5033      	str	r3, [r6, r0]
101020ba:	4406      	add	r6, r0
101020bc:	60b1      	str	r1, [r6, #8]
101020be:	f8c6 e018 	str.w	lr, [r6, #24]
101020c2:	61f2      	str	r2, [r6, #28]
101020c4:	6c61      	ldr	r1, [r4, #68]	; 0x44
101020c6:	6c73      	ldr	r3, [r6, #68]	; 0x44
101020c8:	9101      	str	r1, [sp, #4]
101020ca:	6c21      	ldr	r1, [r4, #64]	; 0x40
101020cc:	6b62      	ldr	r2, [r4, #52]	; 0x34
101020ce:	f423 43ff 	bic.w	r3, r3, #32640	; 0x7f80
101020d2:	6b20      	ldr	r0, [r4, #48]	; 0x30
101020d4:	ea43 13c1 	orr.w	r3, r3, r1, lsl #7
101020d8:	9901      	ldr	r1, [sp, #4]
101020da:	07d2      	lsls	r2, r2, #31
101020dc:	ea42 7280 	orr.w	r2, r2, r0, lsl #30
101020e0:	ea43 23c1 	orr.w	r3, r3, r1, lsl #11
101020e4:	6432      	str	r2, [r6, #64]	; 0x40
101020e6:	4638      	mov	r0, r7
101020e8:	6ae2      	ldr	r2, [r4, #44]	; 0x2c
101020ea:	4629      	mov	r1, r5
101020ec:	6473      	str	r3, [r6, #68]	; 0x44
101020ee:	4c14      	ldr	r4, [pc, #80]	; (10102140 <GDMA_Init+0x148>)
101020f0:	2301      	movs	r3, #1
101020f2:	47a0      	blx	r4
101020f4:	b003      	add	sp, #12
101020f6:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
101020fa:	2358      	movs	r3, #88	; 0x58
101020fc:	fb03 6305 	mla	r3, r3, r5, r6
10102100:	6c5a      	ldr	r2, [r3, #68]	; 0x44
10102102:	f042 0208 	orr.w	r2, r2, #8
10102106:	645a      	str	r2, [r3, #68]	; 0x44
10102108:	e79d      	b.n	10102046 <GDMA_Init+0x4e>
1010210a:	2162      	movs	r1, #98	; 0x62
1010210c:	480d      	ldr	r0, [pc, #52]	; (10102144 <GDMA_Init+0x14c>)
1010210e:	f7fe fbaf 	bl	10100870 <io_assert_failed>
10102112:	e78e      	b.n	10102032 <GDMA_Init+0x3a>
10102114:	2161      	movs	r1, #97	; 0x61
10102116:	480b      	ldr	r0, [pc, #44]	; (10102144 <GDMA_Init+0x14c>)
10102118:	f7fe fbaa 	bl	10100870 <io_assert_failed>
1010211c:	e787      	b.n	1010202e <GDMA_Init+0x36>
1010211e:	480a      	ldr	r0, [pc, #40]	; (10102148 <GDMA_Init+0x150>)
10102120:	f7fe f968 	bl	101003f4 <DiagPrintf>
10102124:	e79b      	b.n	1010205e <GDMA_Init+0x66>
10102126:	bf00      	nop
10102128:	5002a000 	.word	0x5002a000
1010212c:	101003f5 	.word	0x101003f5
10102130:	4002a000 	.word	0x4002a000
10102134:	1000000c 	.word	0x1000000c
10102138:	10101f91 	.word	0x10101f91
1010213c:	10101da5 	.word	0x10101da5
10102140:	10101e75 	.word	0x10101e75
10102144:	101d5004 	.word	0x101d5004
10102148:	101d437c 	.word	0x101d437c

1010214c <GDMA_ChCleanAutoReload>:
1010214c:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
1010214e:	4f1c      	ldr	r7, [pc, #112]	; (101021c0 <GDMA_ChCleanAutoReload+0x74>)
10102150:	4b1c      	ldr	r3, [pc, #112]	; (101021c4 <GDMA_ChCleanAutoReload+0x78>)
10102152:	e843 f300 	tt	r3, r3
10102156:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
1010215a:	4d1b      	ldr	r5, [pc, #108]	; (101021c8 <GDMA_ChCleanAutoReload+0x7c>)
1010215c:	460c      	mov	r4, r1
1010215e:	4616      	mov	r6, r2
10102160:	bf18      	it	ne
10102162:	463d      	movne	r5, r7
10102164:	b990      	cbnz	r0, 1010218c <GDMA_ChCleanAutoReload+0x40>
10102166:	2c05      	cmp	r4, #5
10102168:	d817      	bhi.n	1010219a <GDMA_ChCleanAutoReload+0x4e>
1010216a:	2358      	movs	r3, #88	; 0x58
1010216c:	fb03 5304 	mla	r3, r3, r4, r5
10102170:	2e01      	cmp	r6, #1
10102172:	6c1b      	ldr	r3, [r3, #64]	; 0x40
10102174:	d01c      	beq.n	101021b0 <GDMA_ChCleanAutoReload+0x64>
10102176:	2258      	movs	r2, #88	; 0x58
10102178:	fb02 5404 	mla	r4, r2, r4, r5
1010217c:	2e02      	cmp	r6, #2
1010217e:	bf0c      	ite	eq
10102180:	f023 4300 	biceq.w	r3, r3, #2147483648	; 0x80000000
10102184:	f023 4340 	bicne.w	r3, r3, #3221225472	; 0xc0000000
10102188:	6423      	str	r3, [r4, #64]	; 0x40
1010218a:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
1010218c:	f240 11d9 	movw	r1, #473	; 0x1d9
10102190:	480e      	ldr	r0, [pc, #56]	; (101021cc <GDMA_ChCleanAutoReload+0x80>)
10102192:	f7fe fb6d 	bl	10100870 <io_assert_failed>
10102196:	2c05      	cmp	r4, #5
10102198:	d9e7      	bls.n	1010216a <GDMA_ChCleanAutoReload+0x1e>
1010219a:	f44f 71ed 	mov.w	r1, #474	; 0x1da
1010219e:	480b      	ldr	r0, [pc, #44]	; (101021cc <GDMA_ChCleanAutoReload+0x80>)
101021a0:	f7fe fb66 	bl	10100870 <io_assert_failed>
101021a4:	2358      	movs	r3, #88	; 0x58
101021a6:	fb03 5304 	mla	r3, r3, r4, r5
101021aa:	2e01      	cmp	r6, #1
101021ac:	6c1b      	ldr	r3, [r3, #64]	; 0x40
101021ae:	d1e2      	bne.n	10102176 <GDMA_ChCleanAutoReload+0x2a>
101021b0:	2258      	movs	r2, #88	; 0x58
101021b2:	fb02 5404 	mla	r4, r2, r4, r5
101021b6:	f023 4380 	bic.w	r3, r3, #1073741824	; 0x40000000
101021ba:	6423      	str	r3, [r4, #64]	; 0x40
101021bc:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
101021be:	bf00      	nop
101021c0:	5002a000 	.word	0x5002a000
101021c4:	101003f5 	.word	0x101003f5
101021c8:	4002a000 	.word	0x4002a000
101021cc:	101d50a4 	.word	0x101d50a4

101021d0 <GDMA_SetSrcAddr>:
101021d0:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
101021d2:	4f0f      	ldr	r7, [pc, #60]	; (10102210 <GDMA_SetSrcAddr+0x40>)
101021d4:	4b0f      	ldr	r3, [pc, #60]	; (10102214 <GDMA_SetSrcAddr+0x44>)
101021d6:	e843 f300 	tt	r3, r3
101021da:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
101021de:	4c0e      	ldr	r4, [pc, #56]	; (10102218 <GDMA_SetSrcAddr+0x48>)
101021e0:	460d      	mov	r5, r1
101021e2:	4616      	mov	r6, r2
101021e4:	bf18      	it	ne
101021e6:	463c      	movne	r4, r7
101021e8:	b958      	cbnz	r0, 10102202 <GDMA_SetSrcAddr+0x32>
101021ea:	2d05      	cmp	r5, #5
101021ec:	d904      	bls.n	101021f8 <GDMA_SetSrcAddr+0x28>
101021ee:	f44f 71fe 	mov.w	r1, #508	; 0x1fc
101021f2:	480a      	ldr	r0, [pc, #40]	; (1010221c <GDMA_SetSrcAddr+0x4c>)
101021f4:	f7fe fb3c 	bl	10100870 <io_assert_failed>
101021f8:	2158      	movs	r1, #88	; 0x58
101021fa:	fb01 f105 	mul.w	r1, r1, r5
101021fe:	5066      	str	r6, [r4, r1]
10102200:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10102202:	f240 11fb 	movw	r1, #507	; 0x1fb
10102206:	4805      	ldr	r0, [pc, #20]	; (1010221c <GDMA_SetSrcAddr+0x4c>)
10102208:	f7fe fb32 	bl	10100870 <io_assert_failed>
1010220c:	e7ed      	b.n	101021ea <GDMA_SetSrcAddr+0x1a>
1010220e:	bf00      	nop
10102210:	5002a000 	.word	0x5002a000
10102214:	101003f5 	.word	0x101003f5
10102218:	4002a000 	.word	0x4002a000
1010221c:	101d5078 	.word	0x101d5078

10102220 <GDMA_GetSrcAddr>:
10102220:	4a0e      	ldr	r2, [pc, #56]	; (1010225c <GDMA_GetSrcAddr+0x3c>)
10102222:	b538      	push	{r3, r4, r5, lr}
10102224:	4b0e      	ldr	r3, [pc, #56]	; (10102260 <GDMA_GetSrcAddr+0x40>)
10102226:	e843 f300 	tt	r3, r3
1010222a:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
1010222e:	4c0d      	ldr	r4, [pc, #52]	; (10102264 <GDMA_GetSrcAddr+0x44>)
10102230:	460d      	mov	r5, r1
10102232:	bf18      	it	ne
10102234:	4614      	movne	r4, r2
10102236:	b958      	cbnz	r0, 10102250 <GDMA_GetSrcAddr+0x30>
10102238:	2d05      	cmp	r5, #5
1010223a:	d904      	bls.n	10102246 <GDMA_GetSrcAddr+0x26>
1010223c:	f240 2112 	movw	r1, #530	; 0x212
10102240:	4809      	ldr	r0, [pc, #36]	; (10102268 <GDMA_GetSrcAddr+0x48>)
10102242:	f7fe fb15 	bl	10100870 <io_assert_failed>
10102246:	2158      	movs	r1, #88	; 0x58
10102248:	fb01 f105 	mul.w	r1, r1, r5
1010224c:	5860      	ldr	r0, [r4, r1]
1010224e:	bd38      	pop	{r3, r4, r5, pc}
10102250:	f240 2111 	movw	r1, #529	; 0x211
10102254:	4804      	ldr	r0, [pc, #16]	; (10102268 <GDMA_GetSrcAddr+0x48>)
10102256:	f7fe fb0b 	bl	10100870 <io_assert_failed>
1010225a:	e7ed      	b.n	10102238 <GDMA_GetSrcAddr+0x18>
1010225c:	5002a000 	.word	0x5002a000
10102260:	101003f5 	.word	0x101003f5
10102264:	4002a000 	.word	0x4002a000
10102268:	101d4fd4 	.word	0x101d4fd4

1010226c <GDMA_GetDstAddr>:
1010226c:	4a0e      	ldr	r2, [pc, #56]	; (101022a8 <GDMA_GetDstAddr+0x3c>)
1010226e:	b538      	push	{r3, r4, r5, lr}
10102270:	4b0e      	ldr	r3, [pc, #56]	; (101022ac <GDMA_GetDstAddr+0x40>)
10102272:	e843 f300 	tt	r3, r3
10102276:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
1010227a:	4d0d      	ldr	r5, [pc, #52]	; (101022b0 <GDMA_GetDstAddr+0x44>)
1010227c:	460c      	mov	r4, r1
1010227e:	bf18      	it	ne
10102280:	4615      	movne	r5, r2
10102282:	b958      	cbnz	r0, 1010229c <GDMA_GetDstAddr+0x30>
10102284:	2c05      	cmp	r4, #5
10102286:	d904      	bls.n	10102292 <GDMA_GetDstAddr+0x26>
10102288:	f44f 710a 	mov.w	r1, #552	; 0x228
1010228c:	4809      	ldr	r0, [pc, #36]	; (101022b4 <GDMA_GetDstAddr+0x48>)
1010228e:	f7fe faef 	bl	10100870 <io_assert_failed>
10102292:	2358      	movs	r3, #88	; 0x58
10102294:	fb03 5404 	mla	r4, r3, r4, r5
10102298:	68a0      	ldr	r0, [r4, #8]
1010229a:	bd38      	pop	{r3, r4, r5, pc}
1010229c:	f240 2127 	movw	r1, #551	; 0x227
101022a0:	4804      	ldr	r0, [pc, #16]	; (101022b4 <GDMA_GetDstAddr+0x48>)
101022a2:	f7fe fae5 	bl	10100870 <io_assert_failed>
101022a6:	e7ed      	b.n	10102284 <GDMA_GetDstAddr+0x18>
101022a8:	5002a000 	.word	0x5002a000
101022ac:	101003f5 	.word	0x101003f5
101022b0:	4002a000 	.word	0x4002a000
101022b4:	101d4fe4 	.word	0x101d4fe4

101022b8 <GDMA_SetDstAddr>:
101022b8:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
101022ba:	4f0f      	ldr	r7, [pc, #60]	; (101022f8 <GDMA_SetDstAddr+0x40>)
101022bc:	4b0f      	ldr	r3, [pc, #60]	; (101022fc <GDMA_SetDstAddr+0x44>)
101022be:	e843 f300 	tt	r3, r3
101022c2:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
101022c6:	4d0e      	ldr	r5, [pc, #56]	; (10102300 <GDMA_SetDstAddr+0x48>)
101022c8:	460c      	mov	r4, r1
101022ca:	4616      	mov	r6, r2
101022cc:	bf18      	it	ne
101022ce:	463d      	movne	r5, r7
101022d0:	b958      	cbnz	r0, 101022ea <GDMA_SetDstAddr+0x32>
101022d2:	2c05      	cmp	r4, #5
101022d4:	d904      	bls.n	101022e0 <GDMA_SetDstAddr+0x28>
101022d6:	f240 213f 	movw	r1, #575	; 0x23f
101022da:	480a      	ldr	r0, [pc, #40]	; (10102304 <GDMA_SetDstAddr+0x4c>)
101022dc:	f7fe fac8 	bl	10100870 <io_assert_failed>
101022e0:	2358      	movs	r3, #88	; 0x58
101022e2:	fb03 5404 	mla	r4, r3, r4, r5
101022e6:	60a6      	str	r6, [r4, #8]
101022e8:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
101022ea:	f240 213e 	movw	r1, #574	; 0x23e
101022ee:	4805      	ldr	r0, [pc, #20]	; (10102304 <GDMA_SetDstAddr+0x4c>)
101022f0:	f7fe fabe 	bl	10100870 <io_assert_failed>
101022f4:	e7ed      	b.n	101022d2 <GDMA_SetDstAddr+0x1a>
101022f6:	bf00      	nop
101022f8:	5002a000 	.word	0x5002a000
101022fc:	101003f5 	.word	0x101003f5
10102300:	4002a000 	.word	0x4002a000
10102304:	101d4ff4 	.word	0x101d4ff4

10102308 <GDMA_SetBlkSize>:
10102308:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
1010230a:	4f13      	ldr	r7, [pc, #76]	; (10102358 <GDMA_SetBlkSize+0x50>)
1010230c:	4b13      	ldr	r3, [pc, #76]	; (1010235c <GDMA_SetBlkSize+0x54>)
1010230e:	e843 f300 	tt	r3, r3
10102312:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
10102316:	4e12      	ldr	r6, [pc, #72]	; (10102360 <GDMA_SetBlkSize+0x58>)
10102318:	460c      	mov	r4, r1
1010231a:	4615      	mov	r5, r2
1010231c:	bf18      	it	ne
1010231e:	463e      	movne	r6, r7
10102320:	b998      	cbnz	r0, 1010234a <GDMA_SetBlkSize+0x42>
10102322:	2c05      	cmp	r4, #5
10102324:	d904      	bls.n	10102330 <GDMA_SetBlkSize+0x28>
10102326:	f240 2157 	movw	r1, #599	; 0x257
1010232a:	480e      	ldr	r0, [pc, #56]	; (10102364 <GDMA_SetBlkSize+0x5c>)
1010232c:	f7fe faa0 	bl	10100870 <io_assert_failed>
10102330:	2358      	movs	r3, #88	; 0x58
10102332:	fb03 6404 	mla	r4, r3, r4, r6
10102336:	69e3      	ldr	r3, [r4, #28]
10102338:	f423 637f 	bic.w	r3, r3, #4080	; 0xff0
1010233c:	f3c5 050b 	ubfx	r5, r5, #0, #12
10102340:	f023 030f 	bic.w	r3, r3, #15
10102344:	432b      	orrs	r3, r5
10102346:	61e3      	str	r3, [r4, #28]
10102348:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
1010234a:	f240 2156 	movw	r1, #598	; 0x256
1010234e:	4805      	ldr	r0, [pc, #20]	; (10102364 <GDMA_SetBlkSize+0x5c>)
10102350:	f7fe fa8e 	bl	10100870 <io_assert_failed>
10102354:	e7e5      	b.n	10102322 <GDMA_SetBlkSize+0x1a>
10102356:	bf00      	nop
10102358:	5002a000 	.word	0x5002a000
1010235c:	101003f5 	.word	0x101003f5
10102360:	4002a000 	.word	0x4002a000
10102364:	101d5020 	.word	0x101d5020

10102368 <GDMA_GetBlkSize>:
10102368:	4a0f      	ldr	r2, [pc, #60]	; (101023a8 <GDMA_GetBlkSize+0x40>)
1010236a:	b538      	push	{r3, r4, r5, lr}
1010236c:	4b0f      	ldr	r3, [pc, #60]	; (101023ac <GDMA_GetBlkSize+0x44>)
1010236e:	e843 f300 	tt	r3, r3
10102372:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
10102376:	4d0e      	ldr	r5, [pc, #56]	; (101023b0 <GDMA_GetBlkSize+0x48>)
10102378:	460c      	mov	r4, r1
1010237a:	bf18      	it	ne
1010237c:	4615      	movne	r5, r2
1010237e:	b968      	cbnz	r0, 1010239c <GDMA_GetBlkSize+0x34>
10102380:	2c05      	cmp	r4, #5
10102382:	d904      	bls.n	1010238e <GDMA_GetBlkSize+0x26>
10102384:	f240 2173 	movw	r1, #627	; 0x273
10102388:	480a      	ldr	r0, [pc, #40]	; (101023b4 <GDMA_GetBlkSize+0x4c>)
1010238a:	f7fe fa71 	bl	10100870 <io_assert_failed>
1010238e:	2358      	movs	r3, #88	; 0x58
10102390:	fb03 5404 	mla	r4, r3, r4, r5
10102394:	69e0      	ldr	r0, [r4, #28]
10102396:	f3c0 000b 	ubfx	r0, r0, #0, #12
1010239a:	bd38      	pop	{r3, r4, r5, pc}
1010239c:	f240 2172 	movw	r1, #626	; 0x272
101023a0:	4804      	ldr	r0, [pc, #16]	; (101023b4 <GDMA_GetBlkSize+0x4c>)
101023a2:	f7fe fa65 	bl	10100870 <io_assert_failed>
101023a6:	e7eb      	b.n	10102380 <GDMA_GetBlkSize+0x18>
101023a8:	5002a000 	.word	0x5002a000
101023ac:	101003f5 	.word	0x101003f5
101023b0:	4002a000 	.word	0x4002a000
101023b4:	101d5030 	.word	0x101d5030

101023b8 <GDMA_ChnlRegister>:
101023b8:	b538      	push	{r3, r4, r5, lr}
101023ba:	460c      	mov	r4, r1
101023bc:	4605      	mov	r5, r0
101023be:	b9a8      	cbnz	r0, 101023ec <GDMA_ChnlRegister+0x34>
101023c0:	2c05      	cmp	r4, #5
101023c2:	d80d      	bhi.n	101023e0 <GDMA_ChnlRegister+0x28>
101023c4:	4a0c      	ldr	r2, [pc, #48]	; (101023f8 <GDMA_ChnlRegister+0x40>)
101023c6:	5d53      	ldrb	r3, [r2, r5]
101023c8:	fa43 f104 	asr.w	r1, r3, r4
101023cc:	07c9      	lsls	r1, r1, #31
101023ce:	d405      	bmi.n	101023dc <GDMA_ChnlRegister+0x24>
101023d0:	2001      	movs	r0, #1
101023d2:	fa00 f404 	lsl.w	r4, r0, r4
101023d6:	431c      	orrs	r4, r3
101023d8:	5554      	strb	r4, [r2, r5]
101023da:	bd38      	pop	{r3, r4, r5, pc}
101023dc:	2000      	movs	r0, #0
101023de:	bd38      	pop	{r3, r4, r5, pc}
101023e0:	f240 2186 	movw	r1, #646	; 0x286
101023e4:	4805      	ldr	r0, [pc, #20]	; (101023fc <GDMA_ChnlRegister+0x44>)
101023e6:	f7fe fa43 	bl	10100870 <io_assert_failed>
101023ea:	e7eb      	b.n	101023c4 <GDMA_ChnlRegister+0xc>
101023ec:	f240 2185 	movw	r1, #645	; 0x285
101023f0:	4802      	ldr	r0, [pc, #8]	; (101023fc <GDMA_ChnlRegister+0x44>)
101023f2:	f7fe fa3d 	bl	10100870 <io_assert_failed>
101023f6:	e7e3      	b.n	101023c0 <GDMA_ChnlRegister+0x8>
101023f8:	10000098 	.word	0x10000098
101023fc:	101d5064 	.word	0x101d5064

10102400 <GDMA_ChnlUnRegister>:
10102400:	b538      	push	{r3, r4, r5, lr}
10102402:	460d      	mov	r5, r1
10102404:	4604      	mov	r4, r0
10102406:	b970      	cbnz	r0, 10102426 <GDMA_ChnlUnRegister+0x26>
10102408:	2d05      	cmp	r5, #5
1010240a:	d904      	bls.n	10102416 <GDMA_ChnlUnRegister+0x16>
1010240c:	f240 219a 	movw	r1, #666	; 0x29a
10102410:	4808      	ldr	r0, [pc, #32]	; (10102434 <GDMA_ChnlUnRegister+0x34>)
10102412:	f7fe fa2d 	bl	10100870 <io_assert_failed>
10102416:	2301      	movs	r3, #1
10102418:	4a07      	ldr	r2, [pc, #28]	; (10102438 <GDMA_ChnlUnRegister+0x38>)
1010241a:	5d11      	ldrb	r1, [r2, r4]
1010241c:	40ab      	lsls	r3, r5
1010241e:	ea21 0103 	bic.w	r1, r1, r3
10102422:	5511      	strb	r1, [r2, r4]
10102424:	bd38      	pop	{r3, r4, r5, pc}
10102426:	f240 2199 	movw	r1, #665	; 0x299
1010242a:	4802      	ldr	r0, [pc, #8]	; (10102434 <GDMA_ChnlUnRegister+0x34>)
1010242c:	f7fe fa20 	bl	10100870 <io_assert_failed>
10102430:	e7ea      	b.n	10102408 <GDMA_ChnlUnRegister+0x8>
10102432:	bf00      	nop
10102434:	101d50dc 	.word	0x101d50dc
10102438:	10000098 	.word	0x10000098

1010243c <GDMA_ChnlAlloc>:
1010243c:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
10102440:	4c1d      	ldr	r4, [pc, #116]	; (101024b8 <GDMA_ChnlAlloc+0x7c>)
10102442:	6925      	ldr	r5, [r4, #16]
10102444:	4c1d      	ldr	r4, [pc, #116]	; (101024bc <GDMA_ChnlAlloc+0x80>)
10102446:	e844 f400 	tt	r4, r4
1010244a:	f414 0f80 	tst.w	r4, #4194304	; 0x400000
1010244e:	460f      	mov	r7, r1
10102450:	4690      	mov	r8, r2
10102452:	4699      	mov	r9, r3
10102454:	bf18      	it	ne
10102456:	2502      	movne	r5, #2
10102458:	4682      	mov	sl, r0
1010245a:	b970      	cbnz	r0, 1010247a <GDMA_ChnlAlloc+0x3e>
1010245c:	2400      	movs	r4, #0
1010245e:	4b18      	ldr	r3, [pc, #96]	; (101024c0 <GDMA_ChnlAlloc+0x84>)
10102460:	f813 000a 	ldrb.w	r0, [r3, sl]
10102464:	fa40 f104 	asr.w	r1, r0, r4
10102468:	07cb      	lsls	r3, r1, #31
1010246a:	d50c      	bpl.n	10102486 <GDMA_ChnlAlloc+0x4a>
1010246c:	3401      	adds	r4, #1
1010246e:	2c06      	cmp	r4, #6
10102470:	d1f8      	bne.n	10102464 <GDMA_ChnlAlloc+0x28>
10102472:	26ff      	movs	r6, #255	; 0xff
10102474:	4630      	mov	r0, r6
10102476:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
1010247a:	f240 21b3 	movw	r1, #691	; 0x2b3
1010247e:	4811      	ldr	r0, [pc, #68]	; (101024c4 <GDMA_ChnlAlloc+0x88>)
10102480:	f7fe f9f6 	bl	10100870 <io_assert_failed>
10102484:	e7ea      	b.n	1010245c <GDMA_ChnlAlloc+0x20>
10102486:	b2e6      	uxtb	r6, r4
10102488:	4631      	mov	r1, r6
1010248a:	fa5f f08a 	uxtb.w	r0, sl
1010248e:	4b0e      	ldr	r3, [pc, #56]	; (101024c8 <GDMA_ChnlAlloc+0x8c>)
10102490:	4798      	blx	r3
10102492:	b2ed      	uxtb	r5, r5
10102494:	4b0d      	ldr	r3, [pc, #52]	; (101024cc <GDMA_ChnlAlloc+0x90>)
10102496:	eb05 0545 	add.w	r5, r5, r5, lsl #1
1010249a:	eb03 0545 	add.w	r5, r3, r5, lsl #1
1010249e:	5d2c      	ldrb	r4, [r5, r4]
101024a0:	464b      	mov	r3, r9
101024a2:	4642      	mov	r2, r8
101024a4:	4621      	mov	r1, r4
101024a6:	4638      	mov	r0, r7
101024a8:	4d09      	ldr	r5, [pc, #36]	; (101024d0 <GDMA_ChnlAlloc+0x94>)
101024aa:	47a8      	blx	r5
101024ac:	4620      	mov	r0, r4
101024ae:	4b09      	ldr	r3, [pc, #36]	; (101024d4 <GDMA_ChnlAlloc+0x98>)
101024b0:	4798      	blx	r3
101024b2:	4630      	mov	r0, r6
101024b4:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
101024b8:	48006000 	.word	0x48006000
101024bc:	101003f5 	.word	0x101003f5
101024c0:	10000098 	.word	0x10000098
101024c4:	101d50bc 	.word	0x101d50bc
101024c8:	101023b9 	.word	0x101023b9
101024cc:	101d4008 	.word	0x101d4008
101024d0:	10106aa9 	.word	0x10106aa9
101024d4:	101069b9 	.word	0x101069b9

101024d8 <GDMA_ChnlFree>:
101024d8:	4b1b      	ldr	r3, [pc, #108]	; (10102548 <GDMA_ChnlFree+0x70>)
101024da:	b570      	push	{r4, r5, r6, lr}
101024dc:	460d      	mov	r5, r1
101024de:	691c      	ldr	r4, [r3, #16]
101024e0:	4606      	mov	r6, r0
101024e2:	bb58      	cbnz	r0, 1010253c <GDMA_ChnlFree+0x64>
101024e4:	2d05      	cmp	r5, #5
101024e6:	d823      	bhi.n	10102530 <GDMA_ChnlFree+0x58>
101024e8:	4b18      	ldr	r3, [pc, #96]	; (1010254c <GDMA_ChnlFree+0x74>)
101024ea:	e843 f300 	tt	r3, r3
101024ee:	025b      	lsls	r3, r3, #9
101024f0:	d51c      	bpl.n	1010252c <GDMA_ChnlFree+0x54>
101024f2:	2258      	movs	r2, #88	; 0x58
101024f4:	2302      	movs	r3, #2
101024f6:	fb02 f205 	mul.w	r2, r2, r5
101024fa:	f102 42a0 	add.w	r2, r2, #1342177280	; 0x50000000
101024fe:	f502 3228 	add.w	r2, r2, #172032	; 0x2a000
10102502:	6c51      	ldr	r1, [r2, #68]	; 0x44
10102504:	f041 0108 	orr.w	r1, r1, #8
10102508:	6451      	str	r1, [r2, #68]	; 0x44
1010250a:	4a11      	ldr	r2, [pc, #68]	; (10102550 <GDMA_ChnlFree+0x78>)
1010250c:	eb03 0343 	add.w	r3, r3, r3, lsl #1
10102510:	eb02 0343 	add.w	r3, r2, r3, lsl #1
10102514:	5d5c      	ldrb	r4, [r3, r5]
10102516:	4b0f      	ldr	r3, [pc, #60]	; (10102554 <GDMA_ChnlFree+0x7c>)
10102518:	4620      	mov	r0, r4
1010251a:	4798      	blx	r3
1010251c:	4620      	mov	r0, r4
1010251e:	4b0e      	ldr	r3, [pc, #56]	; (10102558 <GDMA_ChnlFree+0x80>)
10102520:	4798      	blx	r3
10102522:	4629      	mov	r1, r5
10102524:	4630      	mov	r0, r6
10102526:	4b0d      	ldr	r3, [pc, #52]	; (1010255c <GDMA_ChnlFree+0x84>)
10102528:	4798      	blx	r3
1010252a:	bd70      	pop	{r4, r5, r6, pc}
1010252c:	b2e3      	uxtb	r3, r4
1010252e:	e7ec      	b.n	1010250a <GDMA_ChnlFree+0x32>
10102530:	f240 21d9 	movw	r1, #729	; 0x2d9
10102534:	480a      	ldr	r0, [pc, #40]	; (10102560 <GDMA_ChnlFree+0x88>)
10102536:	f7fe f99b 	bl	10100870 <io_assert_failed>
1010253a:	e7d5      	b.n	101024e8 <GDMA_ChnlFree+0x10>
1010253c:	f44f 7136 	mov.w	r1, #728	; 0x2d8
10102540:	4807      	ldr	r0, [pc, #28]	; (10102560 <GDMA_ChnlFree+0x88>)
10102542:	f7fe f995 	bl	10100870 <io_assert_failed>
10102546:	e7cd      	b.n	101024e4 <GDMA_ChnlFree+0xc>
10102548:	48006000 	.word	0x48006000
1010254c:	101003f5 	.word	0x101003f5
10102550:	101d4008 	.word	0x101d4008
10102554:	101069d5 	.word	0x101069d5
10102558:	10106af5 	.word	0x10106af5
1010255c:	10102401 	.word	0x10102401
10102560:	101d4fc4 	.word	0x101d4fc4

10102564 <GDMA_GetIrqNum>:
10102564:	b538      	push	{r3, r4, r5, lr}
10102566:	4b0c      	ldr	r3, [pc, #48]	; (10102598 <GDMA_GetIrqNum+0x34>)
10102568:	460d      	mov	r5, r1
1010256a:	691c      	ldr	r4, [r3, #16]
1010256c:	b968      	cbnz	r0, 1010258a <GDMA_GetIrqNum+0x26>
1010256e:	4b0b      	ldr	r3, [pc, #44]	; (1010259c <GDMA_GetIrqNum+0x38>)
10102570:	e843 f300 	tt	r3, r3
10102574:	025b      	lsls	r3, r3, #9
10102576:	bf4c      	ite	mi
10102578:	2302      	movmi	r3, #2
1010257a:	b2e3      	uxtbpl	r3, r4
1010257c:	4a08      	ldr	r2, [pc, #32]	; (101025a0 <GDMA_GetIrqNum+0x3c>)
1010257e:	eb03 0343 	add.w	r3, r3, r3, lsl #1
10102582:	eb02 0343 	add.w	r3, r2, r3, lsl #1
10102586:	5d58      	ldrb	r0, [r3, r5]
10102588:	bd38      	pop	{r3, r4, r5, pc}
1010258a:	f44f 713e 	mov.w	r1, #760	; 0x2f8
1010258e:	4805      	ldr	r0, [pc, #20]	; (101025a4 <GDMA_GetIrqNum+0x40>)
10102590:	f7fe f96e 	bl	10100870 <io_assert_failed>
10102594:	e7eb      	b.n	1010256e <GDMA_GetIrqNum+0xa>
10102596:	bf00      	nop
10102598:	48006000 	.word	0x48006000
1010259c:	101003f5 	.word	0x101003f5
101025a0:	101d4008 	.word	0x101d4008
101025a4:	101d5010 	.word	0x101d5010

101025a8 <GPIO_INTMode>:
101025a8:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
101025ac:	4e22      	ldr	r6, [pc, #136]	; (10102638 <GPIO_INTMode+0x90>)
101025ae:	b2c5      	uxtb	r5, r0
101025b0:	f3c0 1441 	ubfx	r4, r0, #5, #2
101025b4:	2901      	cmp	r1, #1
101025b6:	f856 4024 	ldr.w	r4, [r6, r4, lsl #2]
101025ba:	f005 071f 	and.w	r7, r5, #31
101025be:	d007      	beq.n	101025d0 <GPIO_INTMode+0x28>
101025c0:	2201      	movs	r2, #1
101025c2:	6b23      	ldr	r3, [r4, #48]	; 0x30
101025c4:	40ba      	lsls	r2, r7
101025c6:	ea23 0302 	bic.w	r3, r3, r2
101025ca:	6323      	str	r3, [r4, #48]	; 0x30
101025cc:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
101025d0:	4698      	mov	r8, r3
101025d2:	4616      	mov	r6, r2
101025d4:	4628      	mov	r0, r5
101025d6:	b31b      	cbz	r3, 10102620 <GPIO_INTMode+0x78>
101025d8:	4b18      	ldr	r3, [pc, #96]	; (1010263c <GPIO_INTMode+0x94>)
101025da:	4798      	blx	r3
101025dc:	2e02      	cmp	r6, #2
101025de:	f04f 0301 	mov.w	r3, #1
101025e2:	d021      	beq.n	10102628 <GPIO_INTMode+0x80>
101025e4:	40bb      	lsls	r3, r7
101025e6:	43da      	mvns	r2, r3
101025e8:	6ea1      	ldr	r1, [r4, #104]	; 0x68
101025ea:	4011      	ands	r1, r2
101025ec:	66a1      	str	r1, [r4, #104]	; 0x68
101025ee:	4619      	mov	r1, r3
101025f0:	6ba0      	ldr	r0, [r4, #56]	; 0x38
101025f2:	40be      	lsls	r6, r7
101025f4:	4010      	ands	r0, r2
101025f6:	4306      	orrs	r6, r0
101025f8:	63a6      	str	r6, [r4, #56]	; 0x38
101025fa:	6be0      	ldr	r0, [r4, #60]	; 0x3c
101025fc:	fa08 f507 	lsl.w	r5, r8, r7
10102600:	ea00 0302 	and.w	r3, r0, r2
10102604:	432b      	orrs	r3, r5
10102606:	63e3      	str	r3, [r4, #60]	; 0x3c
10102608:	6ca3      	ldr	r3, [r4, #72]	; 0x48
1010260a:	401a      	ands	r2, r3
1010260c:	9b06      	ldr	r3, [sp, #24]
1010260e:	2b01      	cmp	r3, #1
10102610:	bf08      	it	eq
10102612:	430a      	orreq	r2, r1
10102614:	64a2      	str	r2, [r4, #72]	; 0x48
10102616:	6b23      	ldr	r3, [r4, #48]	; 0x30
10102618:	430b      	orrs	r3, r1
1010261a:	6323      	str	r3, [r4, #48]	; 0x30
1010261c:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
10102620:	2102      	movs	r1, #2
10102622:	4b06      	ldr	r3, [pc, #24]	; (1010263c <GPIO_INTMode+0x94>)
10102624:	4798      	blx	r3
10102626:	e7d9      	b.n	101025dc <GPIO_INTMode+0x34>
10102628:	fa03 f107 	lsl.w	r1, r3, r7
1010262c:	6ea3      	ldr	r3, [r4, #104]	; 0x68
1010262e:	430b      	orrs	r3, r1
10102630:	43ca      	mvns	r2, r1
10102632:	66a3      	str	r3, [r4, #104]	; 0x68
10102634:	e7e1      	b.n	101025fa <GPIO_INTMode+0x52>
10102636:	bf00      	nop
10102638:	101d401c 	.word	0x101d401c
1010263c:	10102f6d 	.word	0x10102f6d

10102640 <GPIO_INTConfig>:
10102640:	2301      	movs	r3, #1
10102642:	4a0c      	ldr	r2, [pc, #48]	; (10102674 <GPIO_INTConfig+0x34>)
10102644:	b410      	push	{r4}
10102646:	f3c0 1441 	ubfx	r4, r0, #5, #2
1010264a:	f852 2024 	ldr.w	r2, [r2, r4, lsl #2]
1010264e:	f000 001f 	and.w	r0, r0, #31
10102652:	fa03 f000 	lsl.w	r0, r3, r0
10102656:	64d0      	str	r0, [r2, #76]	; 0x4c
10102658:	6b53      	ldr	r3, [r2, #52]	; 0x34
1010265a:	b129      	cbz	r1, 10102668 <GPIO_INTConfig+0x28>
1010265c:	ea23 0000 	bic.w	r0, r3, r0
10102660:	6350      	str	r0, [r2, #52]	; 0x34
10102662:	f85d 4b04 	ldr.w	r4, [sp], #4
10102666:	4770      	bx	lr
10102668:	4318      	orrs	r0, r3
1010266a:	6350      	str	r0, [r2, #52]	; 0x34
1010266c:	f85d 4b04 	ldr.w	r4, [sp], #4
10102670:	4770      	bx	lr
10102672:	bf00      	nop
10102674:	101d401c 	.word	0x101d401c

10102678 <GPIO_INTHandler>:
10102678:	4b24      	ldr	r3, [pc, #144]	; (1010270c <GPIO_INTHandler+0x94>)
1010267a:	4298      	cmp	r0, r3
1010267c:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
10102680:	6d06      	ldr	r6, [r0, #80]	; 0x50
10102682:	4681      	mov	r9, r0
10102684:	f8d0 a040 	ldr.w	sl, [r0, #64]	; 0x40
10102688:	f04f 0400 	mov.w	r4, #0
1010268c:	d01e      	beq.n	101026cc <GPIO_INTHandler+0x54>
1010268e:	4d20      	ldr	r5, [pc, #128]	; (10102710 <GPIO_INTHandler+0x98>)
10102690:	f8df 8088 	ldr.w	r8, [pc, #136]	; 1010271c <GPIO_INTHandler+0xa4>
10102694:	f105 0780 	add.w	r7, r5, #128	; 0x80
10102698:	2301      	movs	r3, #1
1010269a:	40a3      	lsls	r3, r4
1010269c:	ea1a 0f03 	tst.w	sl, r3
101026a0:	d00c      	beq.n	101026bc <GPIO_INTHandler+0x44>
101026a2:	f855 2024 	ldr.w	r2, [r5, r4, lsl #2]
101026a6:	491b      	ldr	r1, [pc, #108]	; (10102714 <GPIO_INTHandler+0x9c>)
101026a8:	00a0      	lsls	r0, r4, #2
101026aa:	b13a      	cbz	r2, 101026bc <GPIO_INTHandler+0x44>
101026ac:	421e      	tst	r6, r3
101026ae:	bf14      	ite	ne
101026b0:	ea41 4104 	orrne.w	r1, r1, r4, lsl #16
101026b4:	ea48 4104 	orreq.w	r1, r8, r4, lsl #16
101026b8:	5838      	ldr	r0, [r7, r0]
101026ba:	4790      	blx	r2
101026bc:	3401      	adds	r4, #1
101026be:	2c20      	cmp	r4, #32
101026c0:	d1ea      	bne.n	10102698 <GPIO_INTHandler+0x20>
101026c2:	f8c9 a04c 	str.w	sl, [r9, #76]	; 0x4c
101026c6:	2000      	movs	r0, #0
101026c8:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
101026cc:	f04f 0801 	mov.w	r8, #1
101026d0:	4d11      	ldr	r5, [pc, #68]	; (10102718 <GPIO_INTHandler+0xa0>)
101026d2:	f105 0780 	add.w	r7, r5, #128	; 0x80
101026d6:	fa08 f304 	lsl.w	r3, r8, r4
101026da:	ea1a 0f03 	tst.w	sl, r3
101026de:	d00d      	beq.n	101026fc <GPIO_INTHandler+0x84>
101026e0:	f855 2024 	ldr.w	r2, [r5, r4, lsl #2]
101026e4:	0421      	lsls	r1, r4, #16
101026e6:	00a0      	lsls	r0, r4, #2
101026e8:	b142      	cbz	r2, 101026fc <GPIO_INTHandler+0x84>
101026ea:	421e      	tst	r6, r3
101026ec:	bf0a      	itet	eq
101026ee:	0421      	lsleq	r1, r4, #16
101026f0:	f041 0101 	orrne.w	r1, r1, #1
101026f4:	f041 0102 	orreq.w	r1, r1, #2
101026f8:	5838      	ldr	r0, [r7, r0]
101026fa:	4790      	blx	r2
101026fc:	3401      	adds	r4, #1
101026fe:	2c20      	cmp	r4, #32
10102700:	d1e9      	bne.n	101026d6 <GPIO_INTHandler+0x5e>
10102702:	f8c9 a04c 	str.w	sl, [r9, #76]	; 0x4c
10102706:	2000      	movs	r0, #0
10102708:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
1010270c:	48014000 	.word	0x48014000
10102710:	1000019c 	.word	0x1000019c
10102714:	00200001 	.word	0x00200001
10102718:	1000009c 	.word	0x1000009c
1010271c:	00200002 	.word	0x00200002

10102720 <GPIO_Direction>:
10102720:	4b0b      	ldr	r3, [pc, #44]	; (10102750 <GPIO_Direction+0x30>)
10102722:	f3c0 1241 	ubfx	r2, r0, #5, #2
10102726:	f853 3022 	ldr.w	r3, [r3, r2, lsl #2]
1010272a:	f000 001f 	and.w	r0, r0, #31
1010272e:	b131      	cbz	r1, 1010273e <GPIO_Direction+0x1e>
10102730:	2101      	movs	r1, #1
10102732:	685a      	ldr	r2, [r3, #4]
10102734:	fa01 f000 	lsl.w	r0, r1, r0
10102738:	4310      	orrs	r0, r2
1010273a:	6058      	str	r0, [r3, #4]
1010273c:	4770      	bx	lr
1010273e:	2101      	movs	r1, #1
10102740:	685a      	ldr	r2, [r3, #4]
10102742:	fa01 f000 	lsl.w	r0, r1, r0
10102746:	ea22 0000 	bic.w	r0, r2, r0
1010274a:	6058      	str	r0, [r3, #4]
1010274c:	4770      	bx	lr
1010274e:	bf00      	nop
10102750:	101d401c 	.word	0x101d401c

10102754 <GPIO_Init>:
10102754:	b530      	push	{r4, r5, lr}
10102756:	6803      	ldr	r3, [r0, #0]
10102758:	2b02      	cmp	r3, #2
1010275a:	b083      	sub	sp, #12
1010275c:	4604      	mov	r4, r0
1010275e:	d81d      	bhi.n	1010279c <GPIO_Init+0x48>
10102760:	4b1a      	ldr	r3, [pc, #104]	; (101027cc <GPIO_Init+0x78>)
10102762:	2100      	movs	r1, #0
10102764:	7d20      	ldrb	r0, [r4, #20]
10102766:	4798      	blx	r3
10102768:	6823      	ldr	r3, [r4, #0]
1010276a:	2b02      	cmp	r3, #2
1010276c:	d01b      	beq.n	101027a6 <GPIO_Init+0x52>
1010276e:	2300      	movs	r3, #0
10102770:	6960      	ldr	r0, [r4, #20]
10102772:	4619      	mov	r1, r3
10102774:	9300      	str	r3, [sp, #0]
10102776:	461a      	mov	r2, r3
10102778:	4d15      	ldr	r5, [pc, #84]	; (101027d0 <GPIO_Init+0x7c>)
1010277a:	47a8      	blx	r5
1010277c:	6821      	ldr	r1, [r4, #0]
1010277e:	2901      	cmp	r1, #1
10102780:	d020      	beq.n	101027c4 <GPIO_Init+0x70>
10102782:	b109      	cbz	r1, 10102788 <GPIO_Init+0x34>
10102784:	b003      	add	sp, #12
10102786:	bd30      	pop	{r4, r5, pc}
10102788:	6960      	ldr	r0, [r4, #20]
1010278a:	4b12      	ldr	r3, [pc, #72]	; (101027d4 <GPIO_Init+0x80>)
1010278c:	4798      	blx	r3
1010278e:	7921      	ldrb	r1, [r4, #4]
10102790:	7d20      	ldrb	r0, [r4, #20]
10102792:	4b11      	ldr	r3, [pc, #68]	; (101027d8 <GPIO_Init+0x84>)
10102794:	b003      	add	sp, #12
10102796:	e8bd 4030 	ldmia.w	sp!, {r4, r5, lr}
1010279a:	4718      	bx	r3
1010279c:	21fd      	movs	r1, #253	; 0xfd
1010279e:	480f      	ldr	r0, [pc, #60]	; (101027dc <GPIO_Init+0x88>)
101027a0:	f7fe f866 	bl	10100870 <io_assert_failed>
101027a4:	e7dc      	b.n	10102760 <GPIO_Init+0xc>
101027a6:	6960      	ldr	r0, [r4, #20]
101027a8:	2100      	movs	r1, #0
101027aa:	4b0a      	ldr	r3, [pc, #40]	; (101027d4 <GPIO_Init+0x80>)
101027ac:	4798      	blx	r3
101027ae:	6921      	ldr	r1, [r4, #16]
101027b0:	f104 0208 	add.w	r2, r4, #8
101027b4:	6960      	ldr	r0, [r4, #20]
101027b6:	ca0c      	ldmia	r2, {r2, r3}
101027b8:	4c05      	ldr	r4, [pc, #20]	; (101027d0 <GPIO_Init+0x7c>)
101027ba:	9100      	str	r1, [sp, #0]
101027bc:	2101      	movs	r1, #1
101027be:	47a0      	blx	r4
101027c0:	b003      	add	sp, #12
101027c2:	bd30      	pop	{r4, r5, pc}
101027c4:	6960      	ldr	r0, [r4, #20]
101027c6:	4b03      	ldr	r3, [pc, #12]	; (101027d4 <GPIO_Init+0x80>)
101027c8:	4798      	blx	r3
101027ca:	e7db      	b.n	10102784 <GPIO_Init+0x30>
101027cc:	10102fb9 	.word	0x10102fb9
101027d0:	101025a9 	.word	0x101025a9
101027d4:	10102721 	.word	0x10102721
101027d8:	10102f6d 	.word	0x10102f6d
101027dc:	101d50f0 	.word	0x101d50f0

101027e0 <GPIO_DeInit>:
101027e0:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
101027e4:	2701      	movs	r7, #1
101027e6:	b2c1      	uxtb	r1, r0
101027e8:	f001 061f 	and.w	r6, r1, #31
101027ec:	40b7      	lsls	r7, r6
101027ee:	ea6f 0807 	mvn.w	r8, r7
101027f2:	4b13      	ldr	r3, [pc, #76]	; (10102840 <GPIO_DeInit+0x60>)
101027f4:	f3c0 1441 	ubfx	r4, r0, #5, #2
101027f8:	f853 5024 	ldr.w	r5, [r3, r4, lsl #2]
101027fc:	686a      	ldr	r2, [r5, #4]
101027fe:	ea02 0208 	and.w	r2, r2, r8
10102802:	4608      	mov	r0, r1
10102804:	4b0f      	ldr	r3, [pc, #60]	; (10102844 <GPIO_DeInit+0x64>)
10102806:	606a      	str	r2, [r5, #4]
10102808:	2100      	movs	r1, #0
1010280a:	4798      	blx	r3
1010280c:	6b2b      	ldr	r3, [r5, #48]	; 0x30
1010280e:	ea08 0303 	and.w	r3, r8, r3
10102812:	632b      	str	r3, [r5, #48]	; 0x30
10102814:	64ef      	str	r7, [r5, #76]	; 0x4c
10102816:	b14c      	cbz	r4, 1010282c <GPIO_DeInit+0x4c>
10102818:	2200      	movs	r2, #0
1010281a:	4b0b      	ldr	r3, [pc, #44]	; (10102848 <GPIO_DeInit+0x68>)
1010281c:	eb03 0386 	add.w	r3, r3, r6, lsl #2
10102820:	f8c3 2100 	str.w	r2, [r3, #256]	; 0x100
10102824:	f8c3 2180 	str.w	r2, [r3, #384]	; 0x180
10102828:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
1010282c:	4b06      	ldr	r3, [pc, #24]	; (10102848 <GPIO_DeInit+0x68>)
1010282e:	eb03 0286 	add.w	r2, r3, r6, lsl #2
10102832:	f843 4026 	str.w	r4, [r3, r6, lsl #2]
10102836:	f8c2 4080 	str.w	r4, [r2, #128]	; 0x80
1010283a:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
1010283e:	bf00      	nop
10102840:	101d401c 	.word	0x101d401c
10102844:	10102f6d 	.word	0x10102f6d
10102848:	1000009c 	.word	0x1000009c

1010284c <GPIO_ReadDataBit>:
1010284c:	2301      	movs	r3, #1
1010284e:	4a07      	ldr	r2, [pc, #28]	; (1010286c <GPIO_ReadDataBit+0x20>)
10102850:	f3c0 1141 	ubfx	r1, r0, #5, #2
10102854:	f852 2021 	ldr.w	r2, [r2, r1, lsl #2]
10102858:	f000 001f 	and.w	r0, r0, #31
1010285c:	6d12      	ldr	r2, [r2, #80]	; 0x50
1010285e:	fa03 f000 	lsl.w	r0, r3, r0
10102862:	4210      	tst	r0, r2
10102864:	bf14      	ite	ne
10102866:	4618      	movne	r0, r3
10102868:	2000      	moveq	r0, #0
1010286a:	4770      	bx	lr
1010286c:	101d401c 	.word	0x101d401c

10102870 <GPIO_WriteBit>:
10102870:	4b0a      	ldr	r3, [pc, #40]	; (1010289c <GPIO_WriteBit+0x2c>)
10102872:	f3c0 1241 	ubfx	r2, r0, #5, #2
10102876:	f853 2022 	ldr.w	r2, [r3, r2, lsl #2]
1010287a:	f000 001f 	and.w	r0, r0, #31
1010287e:	6813      	ldr	r3, [r2, #0]
10102880:	b129      	cbz	r1, 1010288e <GPIO_WriteBit+0x1e>
10102882:	2101      	movs	r1, #1
10102884:	fa01 f000 	lsl.w	r0, r1, r0
10102888:	4303      	orrs	r3, r0
1010288a:	6013      	str	r3, [r2, #0]
1010288c:	4770      	bx	lr
1010288e:	2101      	movs	r1, #1
10102890:	fa01 f000 	lsl.w	r0, r1, r0
10102894:	ea23 0300 	bic.w	r3, r3, r0
10102898:	6013      	str	r3, [r2, #0]
1010289a:	4770      	bx	lr
1010289c:	101d401c 	.word	0x101d401c

101028a0 <GPIO_PortDirection>:
101028a0:	4b07      	ldr	r3, [pc, #28]	; (101028c0 <GPIO_PortDirection+0x20>)
101028a2:	f853 3020 	ldr.w	r3, [r3, r0, lsl #2]
101028a6:	eb00 0040 	add.w	r0, r0, r0, lsl #1
101028aa:	eb03 0080 	add.w	r0, r3, r0, lsl #2
101028ae:	6840      	ldr	r0, [r0, #4]
101028b0:	b112      	cbz	r2, 101028b8 <GPIO_PortDirection+0x18>
101028b2:	4301      	orrs	r1, r0
101028b4:	6059      	str	r1, [r3, #4]
101028b6:	4770      	bx	lr
101028b8:	ea20 0101 	bic.w	r1, r0, r1
101028bc:	6059      	str	r1, [r3, #4]
101028be:	4770      	bx	lr
101028c0:	101d401c 	.word	0x101d401c

101028c4 <GPIO_PortRead>:
101028c4:	4b02      	ldr	r3, [pc, #8]	; (101028d0 <GPIO_PortRead+0xc>)
101028c6:	f853 3020 	ldr.w	r3, [r3, r0, lsl #2]
101028ca:	6d18      	ldr	r0, [r3, #80]	; 0x50
101028cc:	4770      	bx	lr
101028ce:	bf00      	nop
101028d0:	101d401c 	.word	0x101d401c

101028d4 <GPIO_PortWrite>:
101028d4:	4b04      	ldr	r3, [pc, #16]	; (101028e8 <GPIO_PortWrite+0x14>)
101028d6:	f853 3020 	ldr.w	r3, [r3, r0, lsl #2]
101028da:	6818      	ldr	r0, [r3, #0]
101028dc:	4042      	eors	r2, r0
101028de:	4011      	ands	r1, r2
101028e0:	ea80 0201 	eor.w	r2, r0, r1
101028e4:	601a      	str	r2, [r3, #0]
101028e6:	4770      	bx	lr
101028e8:	101d401c 	.word	0x101d401c

101028ec <GPIO_UserRegIrq>:
101028ec:	f010 0f60 	tst.w	r0, #96	; 0x60
101028f0:	b410      	push	{r4}
101028f2:	4b0b      	ldr	r3, [pc, #44]	; (10102920 <GPIO_UserRegIrq+0x34>)
101028f4:	f000 041f 	and.w	r4, r0, #31
101028f8:	d008      	beq.n	1010290c <GPIO_UserRegIrq+0x20>
101028fa:	eb03 0384 	add.w	r3, r3, r4, lsl #2
101028fe:	f8c3 1100 	str.w	r1, [r3, #256]	; 0x100
10102902:	f8c3 2180 	str.w	r2, [r3, #384]	; 0x180
10102906:	f85d 4b04 	ldr.w	r4, [sp], #4
1010290a:	4770      	bx	lr
1010290c:	eb03 0084 	add.w	r0, r3, r4, lsl #2
10102910:	f843 1024 	str.w	r1, [r3, r4, lsl #2]
10102914:	f8c0 2080 	str.w	r2, [r0, #128]	; 0x80
10102918:	f85d 4b04 	ldr.w	r4, [sp], #4
1010291c:	4770      	bx	lr
1010291e:	bf00      	nop
10102920:	1000009c 	.word	0x1000009c

10102924 <IPC_INTConfig>:
10102924:	2a01      	cmp	r2, #1
10102926:	d004      	beq.n	10102932 <IPC_INTConfig+0xe>
10102928:	2201      	movs	r2, #1
1010292a:	fa02 f101 	lsl.w	r1, r2, r1
1010292e:	6041      	str	r1, [r0, #4]
10102930:	4770      	bx	lr
10102932:	408a      	lsls	r2, r1
10102934:	6002      	str	r2, [r0, #0]
10102936:	4770      	bx	lr

10102938 <IPC_IERSet>:
10102938:	6001      	str	r1, [r0, #0]
1010293a:	4770      	bx	lr

1010293c <IPC_IERGet>:
1010293c:	69c0      	ldr	r0, [r0, #28]
1010293e:	4770      	bx	lr

10102940 <IPC_INTRequest>:
10102940:	2301      	movs	r3, #1
10102942:	fa03 f101 	lsl.w	r1, r3, r1
10102946:	6081      	str	r1, [r0, #8]
10102948:	4770      	bx	lr
1010294a:	bf00      	nop

1010294c <IPC_INTClear>:
1010294c:	2301      	movs	r3, #1
1010294e:	fa03 f101 	lsl.w	r1, r3, r1
10102952:	60c1      	str	r1, [r0, #12]
10102954:	4770      	bx	lr
10102956:	bf00      	nop

10102958 <IPC_INTGet>:
10102958:	6940      	ldr	r0, [r0, #20]
1010295a:	4770      	bx	lr

1010295c <IPC_CPUID>:
1010295c:	4b01      	ldr	r3, [pc, #4]	; (10102964 <IPC_CPUID+0x8>)
1010295e:	6918      	ldr	r0, [r3, #16]
10102960:	4770      	bx	lr
10102962:	bf00      	nop
10102964:	48006000 	.word	0x48006000

10102968 <IPC_SEMGet>:
10102968:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
1010296c:	4b0f      	ldr	r3, [pc, #60]	; (101029ac <IPC_SEMGet+0x44>)
1010296e:	2501      	movs	r5, #1
10102970:	461c      	mov	r4, r3
10102972:	691e      	ldr	r6, [r3, #16]
10102974:	fa00 f705 	lsl.w	r7, r0, r5
10102978:	f8df 8038 	ldr.w	r8, [pc, #56]	; 101029b4 <IPC_SEMGet+0x4c>
1010297c:	40ae      	lsls	r6, r5
1010297e:	40bd      	lsls	r5, r7
10102980:	69a3      	ldr	r3, [r4, #24]
10102982:	422b      	tst	r3, r5
10102984:	d1fc      	bne.n	10102980 <IPC_SEMGet+0x18>
10102986:	61a5      	str	r5, [r4, #24]
10102988:	69a3      	ldr	r3, [r4, #24]
1010298a:	40fb      	lsrs	r3, r7
1010298c:	f003 0302 	and.w	r3, r3, #2
10102990:	429e      	cmp	r6, r3
10102992:	d008      	beq.n	101029a6 <IPC_SEMGet+0x3e>
10102994:	f8d8 3008 	ldr.w	r3, [r8, #8]
10102998:	015b      	lsls	r3, r3, #5
1010299a:	d5f1      	bpl.n	10102980 <IPC_SEMGet+0x18>
1010299c:	4631      	mov	r1, r6
1010299e:	4804      	ldr	r0, [pc, #16]	; (101029b0 <IPC_SEMGet+0x48>)
101029a0:	f7fd fd28 	bl	101003f4 <DiagPrintf>
101029a4:	e7ec      	b.n	10102980 <IPC_SEMGet+0x18>
101029a6:	2001      	movs	r0, #1
101029a8:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
101029ac:	48006000 	.word	0x48006000
101029b0:	101d43bc 	.word	0x101d43bc
101029b4:	1000000c 	.word	0x1000000c

101029b8 <IPC_SEMFree>:
101029b8:	b538      	push	{r3, r4, r5, lr}
101029ba:	4c15      	ldr	r4, [pc, #84]	; (10102a10 <IPC_SEMFree+0x58>)
101029bc:	6921      	ldr	r1, [r4, #16]
101029be:	69a3      	ldr	r3, [r4, #24]
101029c0:	0045      	lsls	r5, r0, #1
101029c2:	40eb      	lsrs	r3, r5
101029c4:	4602      	mov	r2, r0
101029c6:	07d8      	lsls	r0, r3, #31
101029c8:	ea4f 0141 	mov.w	r1, r1, lsl #1
101029cc:	d405      	bmi.n	101029da <IPC_SEMFree+0x22>
101029ce:	4b11      	ldr	r3, [pc, #68]	; (10102a14 <IPC_SEMFree+0x5c>)
101029d0:	681b      	ldr	r3, [r3, #0]
101029d2:	015b      	lsls	r3, r3, #5
101029d4:	d40b      	bmi.n	101029ee <IPC_SEMFree+0x36>
101029d6:	2001      	movs	r0, #1
101029d8:	bd38      	pop	{r3, r4, r5, pc}
101029da:	f003 0002 	and.w	r0, r3, #2
101029de:	4281      	cmp	r1, r0
101029e0:	d00b      	beq.n	101029fa <IPC_SEMFree+0x42>
101029e2:	480c      	ldr	r0, [pc, #48]	; (10102a14 <IPC_SEMFree+0x5c>)
101029e4:	6804      	ldr	r4, [r0, #0]
101029e6:	f014 6080 	ands.w	r0, r4, #67108864	; 0x4000000
101029ea:	d10b      	bne.n	10102a04 <IPC_SEMFree+0x4c>
101029ec:	bd38      	pop	{r3, r4, r5, pc}
101029ee:	0849      	lsrs	r1, r1, #1
101029f0:	4809      	ldr	r0, [pc, #36]	; (10102a18 <IPC_SEMFree+0x60>)
101029f2:	f7fd fcff 	bl	101003f4 <DiagPrintf>
101029f6:	2001      	movs	r0, #1
101029f8:	bd38      	pop	{r3, r4, r5, pc}
101029fa:	2001      	movs	r0, #1
101029fc:	fa00 f505 	lsl.w	r5, r0, r5
10102a00:	61a5      	str	r5, [r4, #24]
10102a02:	bd38      	pop	{r3, r4, r5, pc}
10102a04:	0849      	lsrs	r1, r1, #1
10102a06:	4805      	ldr	r0, [pc, #20]	; (10102a1c <IPC_SEMFree+0x64>)
10102a08:	f7fd fcf4 	bl	101003f4 <DiagPrintf>
10102a0c:	2000      	movs	r0, #0
10102a0e:	bd38      	pop	{r3, r4, r5, pc}
10102a10:	48006000 	.word	0x48006000
10102a14:	1000000c 	.word	0x1000000c
10102a18:	101d43f0 	.word	0x101d43f0
10102a1c:	101d4434 	.word	0x101d4434

10102a20 <IPC_INTHandler>:
10102a20:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
10102a24:	4681      	mov	r9, r0
10102a26:	2400      	movs	r4, #0
10102a28:	2701      	movs	r7, #1
10102a2a:	f8df 8030 	ldr.w	r8, [pc, #48]	; 10102a5c <IPC_INTHandler+0x3c>
10102a2e:	6945      	ldr	r5, [r0, #20]
10102a30:	f108 0a80 	add.w	sl, r8, #128	; 0x80
10102a34:	fa07 f304 	lsl.w	r3, r7, r4
10102a38:	421d      	tst	r5, r3
10102a3a:	d009      	beq.n	10102a50 <IPC_INTHandler+0x30>
10102a3c:	f858 6024 	ldr.w	r6, [r8, r4, lsl #2]
10102a40:	b136      	cbz	r6, 10102a50 <IPC_INTHandler+0x30>
10102a42:	f8c9 300c 	str.w	r3, [r9, #12]
10102a46:	4622      	mov	r2, r4
10102a48:	4629      	mov	r1, r5
10102a4a:	f85a 0024 	ldr.w	r0, [sl, r4, lsl #2]
10102a4e:	47b0      	blx	r6
10102a50:	3401      	adds	r4, #1
10102a52:	2c20      	cmp	r4, #32
10102a54:	d1ee      	bne.n	10102a34 <IPC_INTHandler+0x14>
10102a56:	2000      	movs	r0, #0
10102a58:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
10102a5c:	1000029c 	.word	0x1000029c

10102a60 <IPC_INTUserHandler>:
10102a60:	b470      	push	{r4, r5, r6}
10102a62:	4c0b      	ldr	r4, [pc, #44]	; (10102a90 <IPC_INTUserHandler+0x30>)
10102a64:	4d0b      	ldr	r5, [pc, #44]	; (10102a94 <IPC_INTUserHandler+0x34>)
10102a66:	eb04 0680 	add.w	r6, r4, r0, lsl #2
10102a6a:	692b      	ldr	r3, [r5, #16]
10102a6c:	f8c6 2080 	str.w	r2, [r6, #128]	; 0x80
10102a70:	f844 1020 	str.w	r1, [r4, r0, lsl #2]
10102a74:	b131      	cbz	r1, 10102a84 <IPC_INTUserHandler+0x24>
10102a76:	b2db      	uxtb	r3, r3
10102a78:	2b01      	cmp	r3, #1
10102a7a:	d005      	beq.n	10102a88 <IPC_INTUserHandler+0x28>
10102a7c:	2301      	movs	r3, #1
10102a7e:	4a06      	ldr	r2, [pc, #24]	; (10102a98 <IPC_INTUserHandler+0x38>)
10102a80:	4083      	lsls	r3, r0
10102a82:	6013      	str	r3, [r2, #0]
10102a84:	bc70      	pop	{r4, r5, r6}
10102a86:	4770      	bx	lr
10102a88:	4083      	lsls	r3, r0
10102a8a:	602b      	str	r3, [r5, #0]
10102a8c:	bc70      	pop	{r4, r5, r6}
10102a8e:	4770      	bx	lr
10102a90:	1000029c 	.word	0x1000029c
10102a94:	48006000 	.word	0x48006000
10102a98:	40006000 	.word	0x40006000

10102a9c <LOGUART_StructInit>:
10102a9c:	2300      	movs	r3, #0
10102a9e:	2201      	movs	r2, #1
10102aa0:	6003      	str	r3, [r0, #0]
10102aa2:	6083      	str	r3, [r0, #8]
10102aa4:	60c3      	str	r3, [r0, #12]
10102aa6:	6103      	str	r3, [r0, #16]
10102aa8:	6143      	str	r3, [r0, #20]
10102aaa:	6183      	str	r3, [r0, #24]
10102aac:	61c3      	str	r3, [r0, #28]
10102aae:	6042      	str	r2, [r0, #4]
10102ab0:	6202      	str	r2, [r0, #32]
10102ab2:	4770      	bx	lr

10102ab4 <LOGUART_Init>:
10102ab4:	b510      	push	{r4, lr}
10102ab6:	4c0a      	ldr	r4, [pc, #40]	; (10102ae0 <LOGUART_Init+0x2c>)
10102ab8:	4601      	mov	r1, r0
10102aba:	4b0a      	ldr	r3, [pc, #40]	; (10102ae4 <LOGUART_Init+0x30>)
10102abc:	4620      	mov	r0, r4
10102abe:	4798      	blx	r3
10102ac0:	4620      	mov	r0, r4
10102ac2:	f44f 31e1 	mov.w	r1, #115200	; 0x1c200
10102ac6:	4b08      	ldr	r3, [pc, #32]	; (10102ae8 <LOGUART_Init+0x34>)
10102ac8:	4798      	blx	r3
10102aca:	2201      	movs	r2, #1
10102acc:	4620      	mov	r0, r4
10102ace:	4611      	mov	r1, r2
10102ad0:	4b06      	ldr	r3, [pc, #24]	; (10102aec <LOGUART_Init+0x38>)
10102ad2:	4798      	blx	r3
10102ad4:	4620      	mov	r0, r4
10102ad6:	2101      	movs	r1, #1
10102ad8:	4b05      	ldr	r3, [pc, #20]	; (10102af0 <LOGUART_Init+0x3c>)
10102ada:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
10102ade:	4718      	bx	r3
10102ae0:	48012000 	.word	0x48012000
10102ae4:	10103b3d 	.word	0x10103b3d
10102ae8:	101038bd 	.word	0x101038bd
10102aec:	10103bf1 	.word	0x10103bf1
10102af0:	101039f5 	.word	0x101039f5

10102af4 <LOGUART_PutChar>:
10102af4:	4b0a      	ldr	r3, [pc, #40]	; (10102b20 <LOGUART_PutChar+0x2c>)
10102af6:	681b      	ldr	r3, [r3, #0]
10102af8:	2b01      	cmp	r3, #1
10102afa:	d010      	beq.n	10102b1e <LOGUART_PutChar+0x2a>
10102afc:	f641 138b 	movw	r3, #6539	; 0x198b
10102b00:	4908      	ldr	r1, [pc, #32]	; (10102b24 <LOGUART_PutChar+0x30>)
10102b02:	e001      	b.n	10102b08 <LOGUART_PutChar+0x14>
10102b04:	3b01      	subs	r3, #1
10102b06:	d002      	beq.n	10102b0e <LOGUART_PutChar+0x1a>
10102b08:	694a      	ldr	r2, [r1, #20]
10102b0a:	0692      	lsls	r2, r2, #26
10102b0c:	d5fa      	bpl.n	10102b04 <LOGUART_PutChar+0x10>
10102b0e:	280a      	cmp	r0, #10
10102b10:	bf08      	it	eq
10102b12:	220d      	moveq	r2, #13
10102b14:	4b03      	ldr	r3, [pc, #12]	; (10102b24 <LOGUART_PutChar+0x30>)
10102b16:	6258      	str	r0, [r3, #36]	; 0x24
10102b18:	bf08      	it	eq
10102b1a:	625a      	streq	r2, [r3, #36]	; 0x24
10102b1c:	4770      	bx	lr
10102b1e:	4770      	bx	lr
10102b20:	10000000 	.word	0x10000000
10102b24:	48012000 	.word	0x48012000

10102b28 <LOGUART_GetChar>:
10102b28:	b130      	cbz	r0, 10102b38 <LOGUART_GetChar+0x10>
10102b2a:	4a05      	ldr	r2, [pc, #20]	; (10102b40 <LOGUART_GetChar+0x18>)
10102b2c:	6953      	ldr	r3, [r2, #20]
10102b2e:	07db      	lsls	r3, r3, #31
10102b30:	d5fc      	bpl.n	10102b2c <LOGUART_GetChar+0x4>
10102b32:	6a50      	ldr	r0, [r2, #36]	; 0x24
10102b34:	b2c0      	uxtb	r0, r0
10102b36:	4770      	bx	lr
10102b38:	4b01      	ldr	r3, [pc, #4]	; (10102b40 <LOGUART_GetChar+0x18>)
10102b3a:	6a58      	ldr	r0, [r3, #36]	; 0x24
10102b3c:	b2c0      	uxtb	r0, r0
10102b3e:	4770      	bx	lr
10102b40:	48012000 	.word	0x48012000

10102b44 <LOGUART_Readable>:
10102b44:	b508      	push	{r3, lr}
10102b46:	4802      	ldr	r0, [pc, #8]	; (10102b50 <LOGUART_Readable+0xc>)
10102b48:	4b02      	ldr	r3, [pc, #8]	; (10102b54 <LOGUART_Readable+0x10>)
10102b4a:	4798      	blx	r3
10102b4c:	b2c0      	uxtb	r0, r0
10102b4e:	bd08      	pop	{r3, pc}
10102b50:	48012000 	.word	0x48012000
10102b54:	10103a11 	.word	0x10103a11

10102b58 <LOGUART_GetIMR>:
10102b58:	4b01      	ldr	r3, [pc, #4]	; (10102b60 <LOGUART_GetIMR+0x8>)
10102b5a:	6858      	ldr	r0, [r3, #4]
10102b5c:	4770      	bx	lr
10102b5e:	bf00      	nop
10102b60:	48012000 	.word	0x48012000

10102b64 <LOGUART_SetIMR>:
10102b64:	4b01      	ldr	r3, [pc, #4]	; (10102b6c <LOGUART_SetIMR+0x8>)
10102b66:	6058      	str	r0, [r3, #4]
10102b68:	4770      	bx	lr
10102b6a:	bf00      	nop
10102b6c:	48012000 	.word	0x48012000

10102b70 <LOGUART_WaitBusy>:
10102b70:	b538      	push	{r3, r4, r5, lr}
10102b72:	4c05      	ldr	r4, [pc, #20]	; (10102b88 <LOGUART_WaitBusy+0x18>)
10102b74:	6963      	ldr	r3, [r4, #20]
10102b76:	065a      	lsls	r2, r3, #25
10102b78:	d405      	bmi.n	10102b86 <LOGUART_WaitBusy+0x16>
10102b7a:	4d04      	ldr	r5, [pc, #16]	; (10102b8c <LOGUART_WaitBusy+0x1c>)
10102b7c:	2064      	movs	r0, #100	; 0x64
10102b7e:	47a8      	blx	r5
10102b80:	6963      	ldr	r3, [r4, #20]
10102b82:	065b      	lsls	r3, r3, #25
10102b84:	d5fa      	bpl.n	10102b7c <LOGUART_WaitBusy+0xc>
10102b86:	bd38      	pop	{r3, r4, r5, pc}
10102b88:	48012000 	.word	0x48012000
10102b8c:	10100949 	.word	0x10100949

10102b90 <LOGUART_SetBaud>:
10102b90:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
10102b92:	4607      	mov	r7, r0
10102b94:	4c0b      	ldr	r4, [pc, #44]	; (10102bc4 <LOGUART_SetBaud+0x34>)
10102b96:	2200      	movs	r2, #0
10102b98:	4620      	mov	r0, r4
10102b9a:	4e0b      	ldr	r6, [pc, #44]	; (10102bc8 <LOGUART_SetBaud+0x38>)
10102b9c:	2105      	movs	r1, #5
10102b9e:	47b0      	blx	r6
10102ba0:	4d0a      	ldr	r5, [pc, #40]	; (10102bcc <LOGUART_SetBaud+0x3c>)
10102ba2:	4620      	mov	r0, r4
10102ba4:	2100      	movs	r1, #0
10102ba6:	47a8      	blx	r5
10102ba8:	4b09      	ldr	r3, [pc, #36]	; (10102bd0 <LOGUART_SetBaud+0x40>)
10102baa:	4639      	mov	r1, r7
10102bac:	4620      	mov	r0, r4
10102bae:	4798      	blx	r3
10102bb0:	4620      	mov	r0, r4
10102bb2:	2201      	movs	r2, #1
10102bb4:	2105      	movs	r1, #5
10102bb6:	47b0      	blx	r6
10102bb8:	4620      	mov	r0, r4
10102bba:	2101      	movs	r1, #1
10102bbc:	47a8      	blx	r5
10102bbe:	2001      	movs	r0, #1
10102bc0:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10102bc2:	bf00      	nop
10102bc4:	48012000 	.word	0x48012000
10102bc8:	10103bf1 	.word	0x10103bf1
10102bcc:	101039f5 	.word	0x101039f5
10102bd0:	101038bd 	.word	0x101038bd

10102bd4 <mpu_enable>:
10102bd4:	4a04      	ldr	r2, [pc, #16]	; (10102be8 <mpu_enable+0x14>)
10102bd6:	6853      	ldr	r3, [r2, #4]
10102bd8:	f043 0301 	orr.w	r3, r3, #1
10102bdc:	6053      	str	r3, [r2, #4]
10102bde:	f3bf 8f4f 	dsb	sy
10102be2:	f3bf 8f6f 	isb	sy
10102be6:	4770      	bx	lr
10102be8:	e000ed90 	.word	0xe000ed90

10102bec <mpu_disable>:
10102bec:	f3bf 8f5f 	dmb	sy
10102bf0:	4a02      	ldr	r2, [pc, #8]	; (10102bfc <mpu_disable+0x10>)
10102bf2:	6853      	ldr	r3, [r2, #4]
10102bf4:	f023 0301 	bic.w	r3, r3, #1
10102bf8:	6053      	str	r3, [r2, #4]
10102bfa:	4770      	bx	lr
10102bfc:	e000ed90 	.word	0xe000ed90

10102c00 <mpu_init>:
10102c00:	f3bf 8f5f 	dmb	sy
10102c04:	2100      	movs	r1, #0
10102c06:	4b0b      	ldr	r3, [pc, #44]	; (10102c34 <mpu_init+0x34>)
10102c08:	685a      	ldr	r2, [r3, #4]
10102c0a:	480b      	ldr	r0, [pc, #44]	; (10102c38 <mpu_init+0x38>)
10102c0c:	f022 0201 	bic.w	r2, r2, #1
10102c10:	605a      	str	r2, [r3, #4]
10102c12:	6059      	str	r1, [r3, #4]
10102c14:	6318      	str	r0, [r3, #48]	; 0x30
10102c16:	6359      	str	r1, [r3, #52]	; 0x34
10102c18:	685a      	ldr	r2, [r3, #4]
10102c1a:	f042 0204 	orr.w	r2, r2, #4
10102c1e:	605a      	str	r2, [r3, #4]
10102c20:	685a      	ldr	r2, [r3, #4]
10102c22:	f042 0201 	orr.w	r2, r2, #1
10102c26:	605a      	str	r2, [r3, #4]
10102c28:	f3bf 8f4f 	dsb	sy
10102c2c:	f3bf 8f6f 	isb	sy
10102c30:	4770      	bx	lr
10102c32:	bf00      	nop
10102c34:	e000ed90 	.word	0xe000ed90
10102c38:	00772244 	.word	0x00772244

10102c3c <mpu_set_mem_attr>:
10102c3c:	2807      	cmp	r0, #7
10102c3e:	b538      	push	{r3, r4, r5, lr}
10102c40:	4604      	mov	r4, r0
10102c42:	460d      	mov	r5, r1
10102c44:	d82b      	bhi.n	10102c9e <mpu_set_mem_attr+0x62>
10102c46:	f3bf 8f5f 	dmb	sy
10102c4a:	22ff      	movs	r2, #255	; 0xff
10102c4c:	4b16      	ldr	r3, [pc, #88]	; (10102ca8 <mpu_set_mem_attr+0x6c>)
10102c4e:	6858      	ldr	r0, [r3, #4]
10102c50:	f004 0103 	and.w	r1, r4, #3
10102c54:	00c9      	lsls	r1, r1, #3
10102c56:	f020 0001 	bic.w	r0, r0, #1
10102c5a:	2c03      	cmp	r4, #3
10102c5c:	fa02 f201 	lsl.w	r2, r2, r1
10102c60:	6058      	str	r0, [r3, #4]
10102c62:	d912      	bls.n	10102c8a <mpu_set_mem_attr+0x4e>
10102c64:	6b58      	ldr	r0, [r3, #52]	; 0x34
10102c66:	ea20 0202 	bic.w	r2, r0, r2
10102c6a:	635a      	str	r2, [r3, #52]	; 0x34
10102c6c:	6b5a      	ldr	r2, [r3, #52]	; 0x34
10102c6e:	fa05 f101 	lsl.w	r1, r5, r1
10102c72:	4311      	orrs	r1, r2
10102c74:	6359      	str	r1, [r3, #52]	; 0x34
10102c76:	4a0c      	ldr	r2, [pc, #48]	; (10102ca8 <mpu_set_mem_attr+0x6c>)
10102c78:	6853      	ldr	r3, [r2, #4]
10102c7a:	f043 0301 	orr.w	r3, r3, #1
10102c7e:	6053      	str	r3, [r2, #4]
10102c80:	f3bf 8f4f 	dsb	sy
10102c84:	f3bf 8f6f 	isb	sy
10102c88:	bd38      	pop	{r3, r4, r5, pc}
10102c8a:	6b18      	ldr	r0, [r3, #48]	; 0x30
10102c8c:	ea20 0202 	bic.w	r2, r0, r2
10102c90:	631a      	str	r2, [r3, #48]	; 0x30
10102c92:	6b1a      	ldr	r2, [r3, #48]	; 0x30
10102c94:	fa05 f101 	lsl.w	r1, r5, r1
10102c98:	4311      	orrs	r1, r2
10102c9a:	6319      	str	r1, [r3, #48]	; 0x30
10102c9c:	e7eb      	b.n	10102c76 <mpu_set_mem_attr+0x3a>
10102c9e:	2160      	movs	r1, #96	; 0x60
10102ca0:	4802      	ldr	r0, [pc, #8]	; (10102cac <mpu_set_mem_attr+0x70>)
10102ca2:	f7fd fde5 	bl	10100870 <io_assert_failed>
10102ca6:	e7ce      	b.n	10102c46 <mpu_set_mem_attr+0xa>
10102ca8:	e000ed90 	.word	0xe000ed90
10102cac:	101d50fc 	.word	0x101d50fc

10102cb0 <mpu_region_cfg>:
10102cb0:	b5f0      	push	{r4, r5, r6, r7, lr}
10102cb2:	2807      	cmp	r0, #7
10102cb4:	b083      	sub	sp, #12
10102cb6:	4607      	mov	r7, r0
10102cb8:	460d      	mov	r5, r1
10102cba:	d844      	bhi.n	10102d46 <mpu_region_cfg+0x96>
10102cbc:	6829      	ldr	r1, [r5, #0]
10102cbe:	06ca      	lsls	r2, r1, #27
10102cc0:	4e34      	ldr	r6, [pc, #208]	; (10102d94 <mpu_region_cfg+0xe4>)
10102cc2:	d006      	beq.n	10102cd2 <mpu_region_cfg+0x22>
10102cc4:	6833      	ldr	r3, [r6, #0]
10102cc6:	039b      	lsls	r3, r3, #14
10102cc8:	d460      	bmi.n	10102d8c <mpu_region_cfg+0xdc>
10102cca:	2184      	movs	r1, #132	; 0x84
10102ccc:	4832      	ldr	r0, [pc, #200]	; (10102d98 <mpu_region_cfg+0xe8>)
10102cce:	f7fd fdcf 	bl	10100870 <io_assert_failed>
10102cd2:	6869      	ldr	r1, [r5, #4]
10102cd4:	06cc      	lsls	r4, r1, #27
10102cd6:	d007      	beq.n	10102ce8 <mpu_region_cfg+0x38>
10102cd8:	6833      	ldr	r3, [r6, #0]
10102cda:	0398      	lsls	r0, r3, #14
10102cdc:	d452      	bmi.n	10102d84 <mpu_region_cfg+0xd4>
10102cde:	2189      	movs	r1, #137	; 0x89
10102ce0:	482d      	ldr	r0, [pc, #180]	; (10102d98 <mpu_region_cfg+0xe8>)
10102ce2:	f7fd fdc5 	bl	10100870 <io_assert_failed>
10102ce6:	6869      	ldr	r1, [r5, #4]
10102ce8:	682b      	ldr	r3, [r5, #0]
10102cea:	4419      	add	r1, r3
10102cec:	f3bf 8f5f 	dmb	sy
10102cf0:	4c2a      	ldr	r4, [pc, #168]	; (10102d9c <mpu_region_cfg+0xec>)
10102cf2:	6863      	ldr	r3, [r4, #4]
10102cf4:	f023 0301 	bic.w	r3, r3, #1
10102cf8:	6063      	str	r3, [r4, #4]
10102cfa:	60a7      	str	r7, [r4, #8]
10102cfc:	682a      	ldr	r2, [r5, #0]
10102cfe:	7aa8      	ldrb	r0, [r5, #10]
10102d00:	f022 031f 	bic.w	r3, r2, #31
10102d04:	7a6a      	ldrb	r2, [r5, #9]
10102d06:	4318      	orrs	r0, r3
10102d08:	7a2b      	ldrb	r3, [r5, #8]
10102d0a:	4302      	orrs	r2, r0
10102d0c:	4313      	orrs	r3, r2
10102d0e:	60e3      	str	r3, [r4, #12]
10102d10:	7aeb      	ldrb	r3, [r5, #11]
10102d12:	005b      	lsls	r3, r3, #1
10102d14:	f003 030e 	and.w	r3, r3, #14
10102d18:	f021 011f 	bic.w	r1, r1, #31
10102d1c:	f043 0301 	orr.w	r3, r3, #1
10102d20:	430b      	orrs	r3, r1
10102d22:	6123      	str	r3, [r4, #16]
10102d24:	6863      	ldr	r3, [r4, #4]
10102d26:	f043 0301 	orr.w	r3, r3, #1
10102d2a:	6063      	str	r3, [r4, #4]
10102d2c:	6863      	ldr	r3, [r4, #4]
10102d2e:	f043 0301 	orr.w	r3, r3, #1
10102d32:	6063      	str	r3, [r4, #4]
10102d34:	f3bf 8f4f 	dsb	sy
10102d38:	f3bf 8f6f 	isb	sy
10102d3c:	68b3      	ldr	r3, [r6, #8]
10102d3e:	0399      	lsls	r1, r3, #14
10102d40:	d406      	bmi.n	10102d50 <mpu_region_cfg+0xa0>
10102d42:	b003      	add	sp, #12
10102d44:	bdf0      	pop	{r4, r5, r6, r7, pc}
10102d46:	217f      	movs	r1, #127	; 0x7f
10102d48:	4813      	ldr	r0, [pc, #76]	; (10102d98 <mpu_region_cfg+0xe8>)
10102d4a:	f7fd fd91 	bl	10100870 <io_assert_failed>
10102d4e:	e7b5      	b.n	10102cbc <mpu_region_cfg+0xc>
10102d50:	7ae9      	ldrb	r1, [r5, #11]
10102d52:	4813      	ldr	r0, [pc, #76]	; (10102da0 <mpu_region_cfg+0xf0>)
10102d54:	f7fd fb4e 	bl	101003f4 <DiagPrintf>
10102d58:	68b3      	ldr	r3, [r6, #8]
10102d5a:	039a      	lsls	r2, r3, #14
10102d5c:	d5f1      	bpl.n	10102d42 <mpu_region_cfg+0x92>
10102d5e:	68a1      	ldr	r1, [r4, #8]
10102d60:	4810      	ldr	r0, [pc, #64]	; (10102da4 <mpu_region_cfg+0xf4>)
10102d62:	68e2      	ldr	r2, [r4, #12]
10102d64:	6923      	ldr	r3, [r4, #16]
10102d66:	f7fd fb45 	bl	101003f4 <DiagPrintf>
10102d6a:	68b3      	ldr	r3, [r6, #8]
10102d6c:	039b      	lsls	r3, r3, #14
10102d6e:	d5e8      	bpl.n	10102d42 <mpu_region_cfg+0x92>
10102d70:	6b21      	ldr	r1, [r4, #48]	; 0x30
10102d72:	6b62      	ldr	r2, [r4, #52]	; 0x34
10102d74:	6863      	ldr	r3, [r4, #4]
10102d76:	6820      	ldr	r0, [r4, #0]
10102d78:	9000      	str	r0, [sp, #0]
10102d7a:	480b      	ldr	r0, [pc, #44]	; (10102da8 <mpu_region_cfg+0xf8>)
10102d7c:	f7fd fb3a 	bl	101003f4 <DiagPrintf>
10102d80:	b003      	add	sp, #12
10102d82:	bdf0      	pop	{r4, r5, r6, r7, pc}
10102d84:	4809      	ldr	r0, [pc, #36]	; (10102dac <mpu_region_cfg+0xfc>)
10102d86:	f7fd fb35 	bl	101003f4 <DiagPrintf>
10102d8a:	e7a8      	b.n	10102cde <mpu_region_cfg+0x2e>
10102d8c:	4808      	ldr	r0, [pc, #32]	; (10102db0 <mpu_region_cfg+0x100>)
10102d8e:	f7fd fb31 	bl	101003f4 <DiagPrintf>
10102d92:	e79a      	b.n	10102cca <mpu_region_cfg+0x1a>
10102d94:	1000000c 	.word	0x1000000c
10102d98:	101d5110 	.word	0x101d5110
10102d9c:	e000ed90 	.word	0xe000ed90
10102da0:	101d44f0 	.word	0x101d44f0
10102da4:	101d4530 	.word	0x101d4530
10102da8:	101d4574 	.word	0x101d4574
10102dac:	101d44bc 	.word	0x101d44bc
10102db0:	101d4488 	.word	0x101d4488

10102db4 <mpu_entry_free>:
10102db4:	2200      	movs	r2, #0
10102db6:	4b01      	ldr	r3, [pc, #4]	; (10102dbc <mpu_entry_free+0x8>)
10102db8:	541a      	strb	r2, [r3, r0]
10102dba:	4770      	bx	lr
10102dbc:	1007c340 	.word	0x1007c340

10102dc0 <mpu_entry_alloc>:
10102dc0:	b410      	push	{r4}
10102dc2:	4c08      	ldr	r4, [pc, #32]	; (10102de4 <mpu_entry_alloc+0x24>)
10102dc4:	7820      	ldrb	r0, [r4, #0]
10102dc6:	4603      	mov	r3, r0
10102dc8:	b138      	cbz	r0, 10102dda <mpu_entry_alloc+0x1a>
10102dca:	4622      	mov	r2, r4
10102dcc:	2300      	movs	r3, #0
10102dce:	f812 1f01 	ldrb.w	r1, [r2, #1]!
10102dd2:	3301      	adds	r3, #1
10102dd4:	2900      	cmp	r1, #0
10102dd6:	d1fa      	bne.n	10102dce <mpu_entry_alloc+0xe>
10102dd8:	b2d8      	uxtb	r0, r3
10102dda:	2201      	movs	r2, #1
10102ddc:	54e2      	strb	r2, [r4, r3]
10102dde:	f85d 4b04 	ldr.w	r4, [sp], #4
10102de2:	4770      	bx	lr
10102de4:	1007c340 	.word	0x1007c340

10102de8 <RSIP_Cmd>:
10102de8:	4b05      	ldr	r3, [pc, #20]	; (10102e00 <RSIP_Cmd+0x18>)
10102dea:	681b      	ldr	r3, [r3, #0]
10102dec:	2801      	cmp	r0, #1
10102dee:	4a04      	ldr	r2, [pc, #16]	; (10102e00 <RSIP_Cmd+0x18>)
10102df0:	bf0c      	ite	eq
10102df2:	f443 6380 	orreq.w	r3, r3, #1024	; 0x400
10102df6:	f423 6380 	bicne.w	r3, r3, #1024	; 0x400
10102dfa:	6013      	str	r3, [r2, #0]
10102dfc:	4770      	bx	lr
10102dfe:	bf00      	nop
10102e00:	48000204 	.word	0x48000204

10102e04 <RSIP_OTF_init>:
10102e04:	2300      	movs	r3, #0
10102e06:	b430      	push	{r4, r5}
10102e08:	7841      	ldrb	r1, [r0, #1]
10102e0a:	7804      	ldrb	r4, [r0, #0]
10102e0c:	78c2      	ldrb	r2, [r0, #3]
10102e0e:	0409      	lsls	r1, r1, #16
10102e10:	ea41 6104 	orr.w	r1, r1, r4, lsl #24
10102e14:	7884      	ldrb	r4, [r0, #2]
10102e16:	430a      	orrs	r2, r1
10102e18:	4912      	ldr	r1, [pc, #72]	; (10102e64 <RSIP_OTF_init+0x60>)
10102e1a:	ea42 2204 	orr.w	r2, r2, r4, lsl #8
10102e1e:	60ca      	str	r2, [r1, #12]
10102e20:	7944      	ldrb	r4, [r0, #5]
10102e22:	7905      	ldrb	r5, [r0, #4]
10102e24:	79c2      	ldrb	r2, [r0, #7]
10102e26:	0424      	lsls	r4, r4, #16
10102e28:	ea44 6405 	orr.w	r4, r4, r5, lsl #24
10102e2c:	7985      	ldrb	r5, [r0, #6]
10102e2e:	4322      	orrs	r2, r4
10102e30:	ea42 2205 	orr.w	r2, r2, r5, lsl #8
10102e34:	608a      	str	r2, [r1, #8]
10102e36:	7a44      	ldrb	r4, [r0, #9]
10102e38:	7a05      	ldrb	r5, [r0, #8]
10102e3a:	7ac2      	ldrb	r2, [r0, #11]
10102e3c:	0424      	lsls	r4, r4, #16
10102e3e:	ea44 6405 	orr.w	r4, r4, r5, lsl #24
10102e42:	7a85      	ldrb	r5, [r0, #10]
10102e44:	ea44 0002 	orr.w	r0, r4, r2
10102e48:	4a07      	ldr	r2, [pc, #28]	; (10102e68 <RSIP_OTF_init+0x64>)
10102e4a:	ea40 2005 	orr.w	r0, r0, r5, lsl #8
10102e4e:	6048      	str	r0, [r1, #4]
10102e50:	bc30      	pop	{r4, r5}
10102e52:	614b      	str	r3, [r1, #20]
10102e54:	610b      	str	r3, [r1, #16]
10102e56:	6153      	str	r3, [r2, #20]
10102e58:	6113      	str	r3, [r2, #16]
10102e5a:	61d3      	str	r3, [r2, #28]
10102e5c:	6193      	str	r3, [r2, #24]
10102e5e:	6253      	str	r3, [r2, #36]	; 0x24
10102e60:	6213      	str	r3, [r2, #32]
10102e62:	4770      	bx	lr
10102e64:	48000600 	.word	0x48000600
10102e68:	48000608 	.word	0x48000608

10102e6c <RSIP_OTF_Cmd>:
10102e6c:	2801      	cmp	r0, #1
10102e6e:	bf0c      	ite	eq
10102e70:	220d      	moveq	r2, #13
10102e72:	2200      	movne	r2, #0
10102e74:	4b01      	ldr	r3, [pc, #4]	; (10102e7c <RSIP_OTF_Cmd+0x10>)
10102e76:	601a      	str	r2, [r3, #0]
10102e78:	4770      	bx	lr
10102e7a:	bf00      	nop
10102e7c:	48000600 	.word	0x48000600

10102e80 <RSIP_OTF_Mask>:
10102e80:	b1b3      	cbz	r3, 10102eb0 <RSIP_OTF_Mask+0x30>
10102e82:	f032 03ff 	bics.w	r3, r2, #255	; 0xff
10102e86:	b570      	push	{r4, r5, r6, lr}
10102e88:	4615      	mov	r5, r2
10102e8a:	460e      	mov	r6, r1
10102e8c:	4604      	mov	r4, r0
10102e8e:	d100      	bne.n	10102e92 <RSIP_OTF_Mask+0x12>
10102e90:	b91a      	cbnz	r2, 10102e9a <RSIP_OTF_Mask+0x1a>
10102e92:	2162      	movs	r1, #98	; 0x62
10102e94:	480b      	ldr	r0, [pc, #44]	; (10102ec4 <RSIP_OTF_Mask+0x44>)
10102e96:	f7fd fceb 	bl	10100870 <io_assert_failed>
10102e9a:	00e0      	lsls	r0, r4, #3
10102e9c:	022d      	lsls	r5, r5, #8
10102e9e:	f100 4090 	add.w	r0, r0, #1207959552	; 0x48000000
10102ea2:	f045 0501 	orr.w	r5, r5, #1
10102ea6:	f8c0 6614 	str.w	r6, [r0, #1556]	; 0x614
10102eaa:	f8c0 5610 	str.w	r5, [r0, #1552]	; 0x610
10102eae:	bd70      	pop	{r4, r5, r6, pc}
10102eb0:	00c0      	lsls	r0, r0, #3
10102eb2:	f100 4090 	add.w	r0, r0, #1207959552	; 0x48000000
10102eb6:	f8d0 3610 	ldr.w	r3, [r0, #1552]	; 0x610
10102eba:	f023 0301 	bic.w	r3, r3, #1
10102ebe:	f8c0 3610 	str.w	r3, [r0, #1552]	; 0x610
10102ec2:	4770      	bx	lr
10102ec4:	101d5120 	.word	0x101d5120

10102ec8 <RSIP_KEY_Request>:
10102ec8:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
10102eca:	4d0e      	ldr	r5, [pc, #56]	; (10102f04 <RSIP_KEY_Request+0x3c>)
10102ecc:	682b      	ldr	r3, [r5, #0]
10102ece:	4303      	orrs	r3, r0
10102ed0:	602b      	str	r3, [r5, #0]
10102ed2:	682b      	ldr	r3, [r5, #0]
10102ed4:	4218      	tst	r0, r3
10102ed6:	d013      	beq.n	10102f00 <RSIP_KEY_Request+0x38>
10102ed8:	4606      	mov	r6, r0
10102eda:	2401      	movs	r4, #1
10102edc:	4f0a      	ldr	r7, [pc, #40]	; (10102f08 <RSIP_KEY_Request+0x40>)
10102ede:	e001      	b.n	10102ee4 <RSIP_KEY_Request+0x1c>
10102ee0:	2cff      	cmp	r4, #255	; 0xff
10102ee2:	d00b      	beq.n	10102efc <RSIP_KEY_Request+0x34>
10102ee4:	200a      	movs	r0, #10
10102ee6:	47b8      	blx	r7
10102ee8:	682b      	ldr	r3, [r5, #0]
10102eea:	421e      	tst	r6, r3
10102eec:	f104 0401 	add.w	r4, r4, #1
10102ef0:	d1f6      	bne.n	10102ee0 <RSIP_KEY_Request+0x18>
10102ef2:	f1b4 00ff 	subs.w	r0, r4, #255	; 0xff
10102ef6:	bf18      	it	ne
10102ef8:	2001      	movne	r0, #1
10102efa:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10102efc:	2000      	movs	r0, #0
10102efe:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10102f00:	2001      	movs	r0, #1
10102f02:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10102f04:	400002f0 	.word	0x400002f0
10102f08:	10100949 	.word	0x10100949

10102f0c <RSIP_MMU_Config>:
10102f0c:	b430      	push	{r4, r5}
10102f0e:	0100      	lsls	r0, r0, #4
10102f10:	f100 4490 	add.w	r4, r0, #1207959552	; 0x48000000
10102f14:	9d02      	ldr	r5, [sp, #8]
10102f16:	f504 64c0 	add.w	r4, r4, #1536	; 0x600
10102f1a:	6361      	str	r1, [r4, #52]	; 0x34
10102f1c:	63a2      	str	r2, [r4, #56]	; 0x38
10102f1e:	63e5      	str	r5, [r4, #60]	; 0x3c
10102f20:	6b22      	ldr	r2, [r4, #48]	; 0x30
10102f22:	f022 0202 	bic.w	r2, r2, #2
10102f26:	ea42 0343 	orr.w	r3, r2, r3, lsl #1
10102f2a:	6323      	str	r3, [r4, #48]	; 0x30
10102f2c:	bc30      	pop	{r4, r5}
10102f2e:	4770      	bx	lr

10102f30 <RSIP_MMU_Cmd>:
10102f30:	0100      	lsls	r0, r0, #4
10102f32:	f100 4090 	add.w	r0, r0, #1207959552	; 0x48000000
10102f36:	f8d0 3630 	ldr.w	r3, [r0, #1584]	; 0x630
10102f3a:	b921      	cbnz	r1, 10102f46 <RSIP_MMU_Cmd+0x16>
10102f3c:	f023 0301 	bic.w	r3, r3, #1
10102f40:	f8c0 3630 	str.w	r3, [r0, #1584]	; 0x630
10102f44:	4770      	bx	lr
10102f46:	f043 0301 	orr.w	r3, r3, #1
10102f4a:	f8c0 3630 	str.w	r3, [r0, #1584]	; 0x630
10102f4e:	4770      	bx	lr

10102f50 <PAD_DrvStrength>:
10102f50:	0080      	lsls	r0, r0, #2
10102f52:	f100 4090 	add.w	r0, r0, #1207959552	; 0x48000000
10102f56:	f8d0 3400 	ldr.w	r3, [r0, #1024]	; 0x400
10102f5a:	0289      	lsls	r1, r1, #10
10102f5c:	f401 6140 	and.w	r1, r1, #3072	; 0xc00
10102f60:	f023 0303 	bic.w	r3, r3, #3
10102f64:	430b      	orrs	r3, r1
10102f66:	f8c0 3400 	str.w	r3, [r0, #1024]	; 0x400
10102f6a:	4770      	bx	lr

10102f6c <PAD_PullCtrl>:
10102f6c:	0080      	lsls	r0, r0, #2
10102f6e:	f100 4090 	add.w	r0, r0, #1207959552	; 0x48000000
10102f72:	f8d0 3400 	ldr.w	r3, [r0, #1024]	; 0x400
10102f76:	2901      	cmp	r1, #1
10102f78:	f423 7340 	bic.w	r3, r3, #768	; 0x300
10102f7c:	d006      	beq.n	10102f8c <PAD_PullCtrl+0x20>
10102f7e:	2902      	cmp	r1, #2
10102f80:	bf08      	it	eq
10102f82:	f443 7380 	orreq.w	r3, r3, #256	; 0x100
10102f86:	f8c0 3400 	str.w	r3, [r0, #1024]	; 0x400
10102f8a:	4770      	bx	lr
10102f8c:	f443 7300 	orr.w	r3, r3, #512	; 0x200
10102f90:	f8c0 3400 	str.w	r3, [r0, #1024]	; 0x400
10102f94:	4770      	bx	lr
10102f96:	bf00      	nop

10102f98 <PAD_CMD>:
10102f98:	0080      	lsls	r0, r0, #2
10102f9a:	f100 4090 	add.w	r0, r0, #1207959552	; 0x48000000
10102f9e:	f8d0 3400 	ldr.w	r3, [r0, #1024]	; 0x400
10102fa2:	2901      	cmp	r1, #1
10102fa4:	bf16      	itet	ne
10102fa6:	f423 7340 	bicne.w	r3, r3, #768	; 0x300
10102faa:	f423 4300 	biceq.w	r3, r3, #32768	; 0x8000
10102fae:	f443 4300 	orrne.w	r3, r3, #32768	; 0x8000
10102fb2:	f8c0 3400 	str.w	r3, [r0, #1024]	; 0x400
10102fb6:	4770      	bx	lr

10102fb8 <Pinmux_Config>:
10102fb8:	0080      	lsls	r0, r0, #2
10102fba:	f100 4090 	add.w	r0, r0, #1207959552	; 0x48000000
10102fbe:	f8d0 3400 	ldr.w	r3, [r0, #1024]	; 0x400
10102fc2:	f423 4300 	bic.w	r3, r3, #32768	; 0x8000
10102fc6:	f001 011f 	and.w	r1, r1, #31
10102fca:	f023 031f 	bic.w	r3, r3, #31
10102fce:	430b      	orrs	r3, r1
10102fd0:	f8c0 3400 	str.w	r3, [r0, #1024]	; 0x400
10102fd4:	4770      	bx	lr
10102fd6:	bf00      	nop

10102fd8 <Pinmux_ConfigGet>:
10102fd8:	4b02      	ldr	r3, [pc, #8]	; (10102fe4 <Pinmux_ConfigGet+0xc>)
10102fda:	f853 0020 	ldr.w	r0, [r3, r0, lsl #2]
10102fde:	f000 001f 	and.w	r0, r0, #31
10102fe2:	4770      	bx	lr
10102fe4:	48000400 	.word	0x48000400

10102fe8 <Pinmux_UartLogCtrl>:
10102fe8:	b538      	push	{r3, r4, r5, lr}
10102fea:	460c      	mov	r4, r1
10102fec:	b9d0      	cbnz	r0, 10103024 <Pinmux_UartLogCtrl+0x3c>
10102fee:	2c00      	cmp	r4, #0
10102ff0:	bf14      	ite	ne
10102ff2:	2402      	movne	r4, #2
10102ff4:	2400      	moveq	r4, #0
10102ff6:	2102      	movs	r1, #2
10102ff8:	2007      	movs	r0, #7
10102ffa:	4d0d      	ldr	r5, [pc, #52]	; (10103030 <Pinmux_UartLogCtrl+0x48>)
10102ffc:	47a8      	blx	r5
10102ffe:	2102      	movs	r1, #2
10103000:	2008      	movs	r0, #8
10103002:	47a8      	blx	r5
10103004:	4a0b      	ldr	r2, [pc, #44]	; (10103034 <Pinmux_UartLogCtrl+0x4c>)
10103006:	69d3      	ldr	r3, [r2, #28]
10103008:	f423 4300 	bic.w	r3, r3, #32768	; 0x8000
1010300c:	f023 031f 	bic.w	r3, r3, #31
10103010:	4323      	orrs	r3, r4
10103012:	61d3      	str	r3, [r2, #28]
10103014:	6a13      	ldr	r3, [r2, #32]
10103016:	f423 4300 	bic.w	r3, r3, #32768	; 0x8000
1010301a:	f023 031f 	bic.w	r3, r3, #31
1010301e:	4323      	orrs	r3, r4
10103020:	6213      	str	r3, [r2, #32]
10103022:	bd38      	pop	{r3, r4, r5, pc}
10103024:	21aa      	movs	r1, #170	; 0xaa
10103026:	4804      	ldr	r0, [pc, #16]	; (10103038 <Pinmux_UartLogCtrl+0x50>)
10103028:	f7fd fc22 	bl	10100870 <io_assert_failed>
1010302c:	e7df      	b.n	10102fee <Pinmux_UartLogCtrl+0x6>
1010302e:	bf00      	nop
10103030:	10102f6d 	.word	0x10102f6d
10103034:	48000400 	.word	0x48000400
10103038:	101d5130 	.word	0x101d5130

1010303c <Pinmux_SpicCtrl>:
1010303c:	2900      	cmp	r1, #0
1010303e:	b538      	push	{r3, r4, r5, lr}
10103040:	bf14      	ite	ne
10103042:	2406      	movne	r4, #6
10103044:	2400      	moveq	r4, #0
10103046:	2801      	cmp	r0, #1
10103048:	f04f 0102 	mov.w	r1, #2
1010304c:	d049      	beq.n	101030e2 <Pinmux_SpicCtrl+0xa6>
1010304e:	4d4a      	ldr	r5, [pc, #296]	; (10103178 <Pinmux_SpicCtrl+0x13c>)
10103050:	2032      	movs	r0, #50	; 0x32
10103052:	47a8      	blx	r5
10103054:	2102      	movs	r1, #2
10103056:	2033      	movs	r0, #51	; 0x33
10103058:	47a8      	blx	r5
1010305a:	2102      	movs	r1, #2
1010305c:	2034      	movs	r0, #52	; 0x34
1010305e:	47a8      	blx	r5
10103060:	2102      	movs	r1, #2
10103062:	2035      	movs	r0, #53	; 0x35
10103064:	47a8      	blx	r5
10103066:	2102      	movs	r1, #2
10103068:	2036      	movs	r0, #54	; 0x36
1010306a:	47a8      	blx	r5
1010306c:	2102      	movs	r1, #2
1010306e:	2037      	movs	r0, #55	; 0x37
10103070:	47a8      	blx	r5
10103072:	4b42      	ldr	r3, [pc, #264]	; (1010317c <Pinmux_SpicCtrl+0x140>)
10103074:	f8d3 20c8 	ldr.w	r2, [r3, #200]	; 0xc8
10103078:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
1010307c:	f022 021f 	bic.w	r2, r2, #31
10103080:	4322      	orrs	r2, r4
10103082:	f8c3 20c8 	str.w	r2, [r3, #200]	; 0xc8
10103086:	f8d3 20cc 	ldr.w	r2, [r3, #204]	; 0xcc
1010308a:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
1010308e:	f022 021f 	bic.w	r2, r2, #31
10103092:	4322      	orrs	r2, r4
10103094:	f8c3 20cc 	str.w	r2, [r3, #204]	; 0xcc
10103098:	f8d3 20d0 	ldr.w	r2, [r3, #208]	; 0xd0
1010309c:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
101030a0:	f022 021f 	bic.w	r2, r2, #31
101030a4:	4322      	orrs	r2, r4
101030a6:	f8c3 20d0 	str.w	r2, [r3, #208]	; 0xd0
101030aa:	f8d3 20d4 	ldr.w	r2, [r3, #212]	; 0xd4
101030ae:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
101030b2:	f022 021f 	bic.w	r2, r2, #31
101030b6:	4322      	orrs	r2, r4
101030b8:	f8c3 20d4 	str.w	r2, [r3, #212]	; 0xd4
101030bc:	f8d3 20d8 	ldr.w	r2, [r3, #216]	; 0xd8
101030c0:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
101030c4:	f022 021f 	bic.w	r2, r2, #31
101030c8:	4322      	orrs	r2, r4
101030ca:	f8c3 20d8 	str.w	r2, [r3, #216]	; 0xd8
101030ce:	f8d3 20dc 	ldr.w	r2, [r3, #220]	; 0xdc
101030d2:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
101030d6:	f022 021f 	bic.w	r2, r2, #31
101030da:	4314      	orrs	r4, r2
101030dc:	f8c3 40dc 	str.w	r4, [r3, #220]	; 0xdc
101030e0:	bd38      	pop	{r3, r4, r5, pc}
101030e2:	4d25      	ldr	r5, [pc, #148]	; (10103178 <Pinmux_SpicCtrl+0x13c>)
101030e4:	202c      	movs	r0, #44	; 0x2c
101030e6:	47a8      	blx	r5
101030e8:	2102      	movs	r1, #2
101030ea:	202d      	movs	r0, #45	; 0x2d
101030ec:	47a8      	blx	r5
101030ee:	2102      	movs	r1, #2
101030f0:	202e      	movs	r0, #46	; 0x2e
101030f2:	47a8      	blx	r5
101030f4:	2102      	movs	r1, #2
101030f6:	202f      	movs	r0, #47	; 0x2f
101030f8:	47a8      	blx	r5
101030fa:	2102      	movs	r1, #2
101030fc:	2030      	movs	r0, #48	; 0x30
101030fe:	47a8      	blx	r5
10103100:	2102      	movs	r1, #2
10103102:	2031      	movs	r0, #49	; 0x31
10103104:	47a8      	blx	r5
10103106:	4b1d      	ldr	r3, [pc, #116]	; (1010317c <Pinmux_SpicCtrl+0x140>)
10103108:	f8d3 20b0 	ldr.w	r2, [r3, #176]	; 0xb0
1010310c:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
10103110:	f022 021f 	bic.w	r2, r2, #31
10103114:	4322      	orrs	r2, r4
10103116:	f8c3 20b0 	str.w	r2, [r3, #176]	; 0xb0
1010311a:	f8d3 20b4 	ldr.w	r2, [r3, #180]	; 0xb4
1010311e:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
10103122:	f022 021f 	bic.w	r2, r2, #31
10103126:	4322      	orrs	r2, r4
10103128:	f8c3 20b4 	str.w	r2, [r3, #180]	; 0xb4
1010312c:	f8d3 20b8 	ldr.w	r2, [r3, #184]	; 0xb8
10103130:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
10103134:	f022 021f 	bic.w	r2, r2, #31
10103138:	4322      	orrs	r2, r4
1010313a:	f8c3 20b8 	str.w	r2, [r3, #184]	; 0xb8
1010313e:	f8d3 20bc 	ldr.w	r2, [r3, #188]	; 0xbc
10103142:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
10103146:	f022 021f 	bic.w	r2, r2, #31
1010314a:	4322      	orrs	r2, r4
1010314c:	f8c3 20bc 	str.w	r2, [r3, #188]	; 0xbc
10103150:	f8d3 20c0 	ldr.w	r2, [r3, #192]	; 0xc0
10103154:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
10103158:	f022 021f 	bic.w	r2, r2, #31
1010315c:	4322      	orrs	r2, r4
1010315e:	f8c3 20c0 	str.w	r2, [r3, #192]	; 0xc0
10103162:	f8d3 20c4 	ldr.w	r2, [r3, #196]	; 0xc4
10103166:	f422 4200 	bic.w	r2, r2, #32768	; 0x8000
1010316a:	f022 021f 	bic.w	r2, r2, #31
1010316e:	4314      	orrs	r4, r2
10103170:	f8c3 40c4 	str.w	r4, [r3, #196]	; 0xc4
10103174:	bd38      	pop	{r3, r4, r5, pc}
10103176:	bf00      	nop
10103178:	10102f6d 	.word	0x10102f6d
1010317c:	48000400 	.word	0x48000400

10103180 <simulation_bit_index>:
10103180:	4603      	mov	r3, r0
10103182:	2000      	movs	r0, #0
10103184:	e002      	b.n	1010318c <simulation_bit_index+0xc>
10103186:	3001      	adds	r0, #1
10103188:	2820      	cmp	r0, #32
1010318a:	d004      	beq.n	10103196 <simulation_bit_index+0x16>
1010318c:	f013 0f01 	tst.w	r3, #1
10103190:	ea4f 0353 	mov.w	r3, r3, lsr #1
10103194:	d0f7      	beq.n	10103186 <simulation_bit_index+0x6>
10103196:	4770      	bx	lr

10103198 <simulation_stage_set>:
10103198:	b930      	cbnz	r0, 101031a8 <simulation_stage_set+0x10>
1010319a:	2901      	cmp	r1, #1
1010319c:	d009      	beq.n	101031b2 <simulation_stage_set+0x1a>
1010319e:	4b07      	ldr	r3, [pc, #28]	; (101031bc <simulation_stage_set+0x24>)
101031a0:	6818      	ldr	r0, [r3, #0]
101031a2:	4308      	orrs	r0, r1
101031a4:	6018      	str	r0, [r3, #0]
101031a6:	4770      	bx	lr
101031a8:	4b05      	ldr	r3, [pc, #20]	; (101031c0 <simulation_stage_set+0x28>)
101031aa:	6818      	ldr	r0, [r3, #0]
101031ac:	4308      	orrs	r0, r1
101031ae:	6018      	str	r0, [r3, #0]
101031b0:	4770      	bx	lr
101031b2:	4a02      	ldr	r2, [pc, #8]	; (101031bc <simulation_stage_set+0x24>)
101031b4:	4b02      	ldr	r3, [pc, #8]	; (101031c0 <simulation_stage_set+0x28>)
101031b6:	6010      	str	r0, [r2, #0]
101031b8:	6018      	str	r0, [r3, #0]
101031ba:	e7f0      	b.n	1010319e <simulation_stage_set+0x6>
101031bc:	48000144 	.word	0x48000144
101031c0:	48000148 	.word	0x48000148

101031c4 <SYSTIMER_Init>:
101031c4:	b5f0      	push	{r4, r5, r6, r7, lr}
101031c6:	b089      	sub	sp, #36	; 0x24
101031c8:	a802      	add	r0, sp, #8
101031ca:	4b0e      	ldr	r3, [pc, #56]	; (10103204 <SYSTIMER_Init+0x40>)
101031cc:	4798      	blx	r3
101031ce:	f04f 36ff 	mov.w	r6, #4294967295
101031d2:	2000      	movs	r0, #0
101031d4:	2401      	movs	r4, #1
101031d6:	2704      	movs	r7, #4
101031d8:	4d0b      	ldr	r5, [pc, #44]	; (10103208 <SYSTIMER_Init+0x44>)
101031da:	4602      	mov	r2, r0
101031dc:	a902      	add	r1, sp, #8
101031de:	9000      	str	r0, [sp, #0]
101031e0:	4603      	mov	r3, r0
101031e2:	f88d 001c 	strb.w	r0, [sp, #28]
101031e6:	9002      	str	r0, [sp, #8]
101031e8:	9603      	str	r6, [sp, #12]
101031ea:	4628      	mov	r0, r5
101031ec:	4e07      	ldr	r6, [pc, #28]	; (1010320c <SYSTIMER_Init+0x48>)
101031ee:	9404      	str	r4, [sp, #16]
101031f0:	9406      	str	r4, [sp, #24]
101031f2:	9705      	str	r7, [sp, #20]
101031f4:	47b0      	blx	r6
101031f6:	4621      	mov	r1, r4
101031f8:	4628      	mov	r0, r5
101031fa:	4b05      	ldr	r3, [pc, #20]	; (10103210 <SYSTIMER_Init+0x4c>)
101031fc:	4798      	blx	r3
101031fe:	b009      	add	sp, #36	; 0x24
10103200:	bdf0      	pop	{r4, r5, r6, r7, pc}
10103202:	bf00      	nop
10103204:	10103255 	.word	0x10103255
10103208:	48002000 	.word	0x48002000
1010320c:	1010345d 	.word	0x1010345d
10103210:	1010326d 	.word	0x1010326d

10103214 <SYSTIMER_TickGet>:
10103214:	4801      	ldr	r0, [pc, #4]	; (1010321c <SYSTIMER_TickGet+0x8>)
10103216:	4b02      	ldr	r3, [pc, #8]	; (10103220 <SYSTIMER_TickGet+0xc>)
10103218:	4718      	bx	r3
1010321a:	bf00      	nop
1010321c:	48002000 	.word	0x48002000
10103220:	101032f5 	.word	0x101032f5

10103224 <SYSTIMER_GetPassTime>:
10103224:	b510      	push	{r4, lr}
10103226:	4b08      	ldr	r3, [pc, #32]	; (10103248 <SYSTIMER_GetPassTime+0x24>)
10103228:	4604      	mov	r4, r0
1010322a:	4808      	ldr	r0, [pc, #32]	; (1010324c <SYSTIMER_GetPassTime+0x28>)
1010322c:	4798      	blx	r3
1010322e:	42a0      	cmp	r0, r4
10103230:	bf3a      	itte	cc
10103232:	1a24      	subcc	r4, r4, r0
10103234:	43e4      	mvncc	r4, r4
10103236:	1b04      	subcs	r4, r0, r4
10103238:	4805      	ldr	r0, [pc, #20]	; (10103250 <SYSTIMER_GetPassTime+0x2c>)
1010323a:	ebc4 1444 	rsb	r4, r4, r4, lsl #5
1010323e:	fba0 3004 	umull	r3, r0, r0, r4
10103242:	0980      	lsrs	r0, r0, #6
10103244:	bd10      	pop	{r4, pc}
10103246:	bf00      	nop
10103248:	101032f5 	.word	0x101032f5
1010324c:	48002000 	.word	0x48002000
10103250:	10624dd3 	.word	0x10624dd3

10103254 <RTIM_TimeBaseStructInit>:
10103254:	b410      	push	{r4}
10103256:	2301      	movs	r3, #1
10103258:	2404      	movs	r4, #4
1010325a:	2100      	movs	r1, #0
1010325c:	f64f 72ff 	movw	r2, #65535	; 0xffff
10103260:	6103      	str	r3, [r0, #16]
10103262:	e880 001e 	stmia.w	r0, {r1, r2, r3, r4}
10103266:	f85d 4b04 	ldr.w	r4, [sp], #4
1010326a:	4770      	bx	lr

1010326c <RTIM_Cmd>:
1010326c:	b538      	push	{r3, r4, r5, lr}
1010326e:	4b1e      	ldr	r3, [pc, #120]	; (101032e8 <RTIM_Cmd+0x7c>)
10103270:	4298      	cmp	r0, r3
10103272:	4604      	mov	r4, r0
10103274:	460d      	mov	r5, r1
10103276:	d024      	beq.n	101032c2 <RTIM_Cmd+0x56>
10103278:	3380      	adds	r3, #128	; 0x80
1010327a:	4298      	cmp	r0, r3
1010327c:	d021      	beq.n	101032c2 <RTIM_Cmd+0x56>
1010327e:	3380      	adds	r3, #128	; 0x80
10103280:	4298      	cmp	r0, r3
10103282:	d01e      	beq.n	101032c2 <RTIM_Cmd+0x56>
10103284:	3380      	adds	r3, #128	; 0x80
10103286:	4298      	cmp	r0, r3
10103288:	d01b      	beq.n	101032c2 <RTIM_Cmd+0x56>
1010328a:	3380      	adds	r3, #128	; 0x80
1010328c:	4298      	cmp	r0, r3
1010328e:	d018      	beq.n	101032c2 <RTIM_Cmd+0x56>
10103290:	3380      	adds	r3, #128	; 0x80
10103292:	4298      	cmp	r0, r3
10103294:	d015      	beq.n	101032c2 <RTIM_Cmd+0x56>
10103296:	4b15      	ldr	r3, [pc, #84]	; (101032ec <RTIM_Cmd+0x80>)
10103298:	4298      	cmp	r0, r3
1010329a:	d012      	beq.n	101032c2 <RTIM_Cmd+0x56>
1010329c:	3380      	adds	r3, #128	; 0x80
1010329e:	4298      	cmp	r0, r3
101032a0:	d00f      	beq.n	101032c2 <RTIM_Cmd+0x56>
101032a2:	3380      	adds	r3, #128	; 0x80
101032a4:	4298      	cmp	r0, r3
101032a6:	d00c      	beq.n	101032c2 <RTIM_Cmd+0x56>
101032a8:	3380      	adds	r3, #128	; 0x80
101032aa:	4298      	cmp	r0, r3
101032ac:	d009      	beq.n	101032c2 <RTIM_Cmd+0x56>
101032ae:	3380      	adds	r3, #128	; 0x80
101032b0:	4298      	cmp	r0, r3
101032b2:	d006      	beq.n	101032c2 <RTIM_Cmd+0x56>
101032b4:	3380      	adds	r3, #128	; 0x80
101032b6:	4298      	cmp	r0, r3
101032b8:	d003      	beq.n	101032c2 <RTIM_Cmd+0x56>
101032ba:	2190      	movs	r1, #144	; 0x90
101032bc:	480c      	ldr	r0, [pc, #48]	; (101032f0 <RTIM_Cmd+0x84>)
101032be:	f7fd fad7 	bl	10100870 <io_assert_failed>
101032c2:	6823      	ldr	r3, [r4, #0]
101032c4:	b13d      	cbz	r5, 101032d6 <RTIM_Cmd+0x6a>
101032c6:	05d8      	lsls	r0, r3, #23
101032c8:	bf5c      	itt	pl
101032ca:	2301      	movpl	r3, #1
101032cc:	6023      	strpl	r3, [r4, #0]
101032ce:	6823      	ldr	r3, [r4, #0]
101032d0:	05d9      	lsls	r1, r3, #23
101032d2:	d5fc      	bpl.n	101032ce <RTIM_Cmd+0x62>
101032d4:	bd38      	pop	{r3, r4, r5, pc}
101032d6:	05da      	lsls	r2, r3, #23
101032d8:	bf44      	itt	mi
101032da:	2302      	movmi	r3, #2
101032dc:	6023      	strmi	r3, [r4, #0]
101032de:	6823      	ldr	r3, [r4, #0]
101032e0:	05db      	lsls	r3, r3, #23
101032e2:	d4fc      	bmi.n	101032de <RTIM_Cmd+0x72>
101032e4:	bd38      	pop	{r3, r4, r5, pc}
101032e6:	bf00      	nop
101032e8:	40002000 	.word	0x40002000
101032ec:	48002000 	.word	0x48002000
101032f0:	101d5170 	.word	0x101d5170

101032f4 <RTIM_GetCount>:
101032f4:	4b17      	ldr	r3, [pc, #92]	; (10103354 <RTIM_GetCount+0x60>)
101032f6:	4298      	cmp	r0, r3
101032f8:	b510      	push	{r4, lr}
101032fa:	4604      	mov	r4, r0
101032fc:	d024      	beq.n	10103348 <RTIM_GetCount+0x54>
101032fe:	3380      	adds	r3, #128	; 0x80
10103300:	4298      	cmp	r0, r3
10103302:	d021      	beq.n	10103348 <RTIM_GetCount+0x54>
10103304:	3380      	adds	r3, #128	; 0x80
10103306:	4298      	cmp	r0, r3
10103308:	d01e      	beq.n	10103348 <RTIM_GetCount+0x54>
1010330a:	3380      	adds	r3, #128	; 0x80
1010330c:	4298      	cmp	r0, r3
1010330e:	d01b      	beq.n	10103348 <RTIM_GetCount+0x54>
10103310:	3380      	adds	r3, #128	; 0x80
10103312:	4298      	cmp	r0, r3
10103314:	d018      	beq.n	10103348 <RTIM_GetCount+0x54>
10103316:	3380      	adds	r3, #128	; 0x80
10103318:	4298      	cmp	r0, r3
1010331a:	d015      	beq.n	10103348 <RTIM_GetCount+0x54>
1010331c:	4b0e      	ldr	r3, [pc, #56]	; (10103358 <RTIM_GetCount+0x64>)
1010331e:	4298      	cmp	r0, r3
10103320:	d012      	beq.n	10103348 <RTIM_GetCount+0x54>
10103322:	3380      	adds	r3, #128	; 0x80
10103324:	4298      	cmp	r0, r3
10103326:	d00f      	beq.n	10103348 <RTIM_GetCount+0x54>
10103328:	3380      	adds	r3, #128	; 0x80
1010332a:	4298      	cmp	r0, r3
1010332c:	d00c      	beq.n	10103348 <RTIM_GetCount+0x54>
1010332e:	3380      	adds	r3, #128	; 0x80
10103330:	4298      	cmp	r0, r3
10103332:	d009      	beq.n	10103348 <RTIM_GetCount+0x54>
10103334:	3380      	adds	r3, #128	; 0x80
10103336:	4298      	cmp	r0, r3
10103338:	d006      	beq.n	10103348 <RTIM_GetCount+0x54>
1010333a:	3380      	adds	r3, #128	; 0x80
1010333c:	4298      	cmp	r0, r3
1010333e:	d003      	beq.n	10103348 <RTIM_GetCount+0x54>
10103340:	21cd      	movs	r1, #205	; 0xcd
10103342:	4806      	ldr	r0, [pc, #24]	; (1010335c <RTIM_GetCount+0x68>)
10103344:	f7fd fa94 	bl	10100870 <io_assert_failed>
10103348:	6963      	ldr	r3, [r4, #20]
1010334a:	6960      	ldr	r0, [r4, #20]
1010334c:	4283      	cmp	r3, r0
1010334e:	bf18      	it	ne
10103350:	6960      	ldrne	r0, [r4, #20]
10103352:	bd10      	pop	{r4, pc}
10103354:	40002000 	.word	0x40002000
10103358:	48002000 	.word	0x48002000
1010335c:	101d5188 	.word	0x101d5188

10103360 <RTIM_INTConfig>:
10103360:	4b20      	ldr	r3, [pc, #128]	; (101033e4 <RTIM_INTConfig+0x84>)
10103362:	4298      	cmp	r0, r3
10103364:	b570      	push	{r4, r5, r6, lr}
10103366:	4604      	mov	r4, r0
10103368:	460d      	mov	r5, r1
1010336a:	4616      	mov	r6, r2
1010336c:	d025      	beq.n	101033ba <RTIM_INTConfig+0x5a>
1010336e:	3380      	adds	r3, #128	; 0x80
10103370:	4298      	cmp	r0, r3
10103372:	d022      	beq.n	101033ba <RTIM_INTConfig+0x5a>
10103374:	3380      	adds	r3, #128	; 0x80
10103376:	4298      	cmp	r0, r3
10103378:	d01f      	beq.n	101033ba <RTIM_INTConfig+0x5a>
1010337a:	3380      	adds	r3, #128	; 0x80
1010337c:	4298      	cmp	r0, r3
1010337e:	d01c      	beq.n	101033ba <RTIM_INTConfig+0x5a>
10103380:	3380      	adds	r3, #128	; 0x80
10103382:	4298      	cmp	r0, r3
10103384:	d019      	beq.n	101033ba <RTIM_INTConfig+0x5a>
10103386:	3380      	adds	r3, #128	; 0x80
10103388:	4298      	cmp	r0, r3
1010338a:	d016      	beq.n	101033ba <RTIM_INTConfig+0x5a>
1010338c:	4b16      	ldr	r3, [pc, #88]	; (101033e8 <RTIM_INTConfig+0x88>)
1010338e:	4298      	cmp	r0, r3
10103390:	d013      	beq.n	101033ba <RTIM_INTConfig+0x5a>
10103392:	3380      	adds	r3, #128	; 0x80
10103394:	4298      	cmp	r0, r3
10103396:	d010      	beq.n	101033ba <RTIM_INTConfig+0x5a>
10103398:	3380      	adds	r3, #128	; 0x80
1010339a:	4298      	cmp	r0, r3
1010339c:	d00d      	beq.n	101033ba <RTIM_INTConfig+0x5a>
1010339e:	3380      	adds	r3, #128	; 0x80
101033a0:	4298      	cmp	r0, r3
101033a2:	d00a      	beq.n	101033ba <RTIM_INTConfig+0x5a>
101033a4:	3380      	adds	r3, #128	; 0x80
101033a6:	4298      	cmp	r0, r3
101033a8:	d007      	beq.n	101033ba <RTIM_INTConfig+0x5a>
101033aa:	3380      	adds	r3, #128	; 0x80
101033ac:	4298      	cmp	r0, r3
101033ae:	d004      	beq.n	101033ba <RTIM_INTConfig+0x5a>
101033b0:	f240 1105 	movw	r1, #261	; 0x105
101033b4:	480d      	ldr	r0, [pc, #52]	; (101033ec <RTIM_INTConfig+0x8c>)
101033b6:	f7fd fa5b 	bl	10100870 <io_assert_failed>
101033ba:	0ceb      	lsrs	r3, r5, #19
101033bc:	04db      	lsls	r3, r3, #19
101033be:	b933      	cbnz	r3, 101033ce <RTIM_INTConfig+0x6e>
101033c0:	b12d      	cbz	r5, 101033ce <RTIM_INTConfig+0x6e>
101033c2:	68a3      	ldr	r3, [r4, #8]
101033c4:	b95e      	cbnz	r6, 101033de <RTIM_INTConfig+0x7e>
101033c6:	ea23 0505 	bic.w	r5, r3, r5
101033ca:	60a5      	str	r5, [r4, #8]
101033cc:	bd70      	pop	{r4, r5, r6, pc}
101033ce:	f44f 7183 	mov.w	r1, #262	; 0x106
101033d2:	4806      	ldr	r0, [pc, #24]	; (101033ec <RTIM_INTConfig+0x8c>)
101033d4:	f7fd fa4c 	bl	10100870 <io_assert_failed>
101033d8:	68a3      	ldr	r3, [r4, #8]
101033da:	2e00      	cmp	r6, #0
101033dc:	d0f3      	beq.n	101033c6 <RTIM_INTConfig+0x66>
101033de:	431d      	orrs	r5, r3
101033e0:	60a5      	str	r5, [r4, #8]
101033e2:	bd70      	pop	{r4, r5, r6, pc}
101033e4:	40002000 	.word	0x40002000
101033e8:	48002000 	.word	0x48002000
101033ec:	101d51ac 	.word	0x101d51ac

101033f0 <RTIM_INTClear>:
101033f0:	b538      	push	{r3, r4, r5, lr}
101033f2:	4b17      	ldr	r3, [pc, #92]	; (10103450 <RTIM_INTClear+0x60>)
101033f4:	4298      	cmp	r0, r3
101033f6:	4604      	mov	r4, r0
101033f8:	68c5      	ldr	r5, [r0, #12]
101033fa:	d025      	beq.n	10103448 <RTIM_INTClear+0x58>
101033fc:	3380      	adds	r3, #128	; 0x80
101033fe:	4298      	cmp	r0, r3
10103400:	d022      	beq.n	10103448 <RTIM_INTClear+0x58>
10103402:	3380      	adds	r3, #128	; 0x80
10103404:	4298      	cmp	r0, r3
10103406:	d01f      	beq.n	10103448 <RTIM_INTClear+0x58>
10103408:	3380      	adds	r3, #128	; 0x80
1010340a:	4298      	cmp	r0, r3
1010340c:	d01c      	beq.n	10103448 <RTIM_INTClear+0x58>
1010340e:	3380      	adds	r3, #128	; 0x80
10103410:	4298      	cmp	r0, r3
10103412:	d019      	beq.n	10103448 <RTIM_INTClear+0x58>
10103414:	3380      	adds	r3, #128	; 0x80
10103416:	4298      	cmp	r0, r3
10103418:	d016      	beq.n	10103448 <RTIM_INTClear+0x58>
1010341a:	4b0e      	ldr	r3, [pc, #56]	; (10103454 <RTIM_INTClear+0x64>)
1010341c:	4298      	cmp	r0, r3
1010341e:	d013      	beq.n	10103448 <RTIM_INTClear+0x58>
10103420:	3380      	adds	r3, #128	; 0x80
10103422:	4298      	cmp	r0, r3
10103424:	d010      	beq.n	10103448 <RTIM_INTClear+0x58>
10103426:	3380      	adds	r3, #128	; 0x80
10103428:	4298      	cmp	r0, r3
1010342a:	d00d      	beq.n	10103448 <RTIM_INTClear+0x58>
1010342c:	3380      	adds	r3, #128	; 0x80
1010342e:	4298      	cmp	r0, r3
10103430:	d00a      	beq.n	10103448 <RTIM_INTClear+0x58>
10103432:	3380      	adds	r3, #128	; 0x80
10103434:	4298      	cmp	r0, r3
10103436:	d007      	beq.n	10103448 <RTIM_INTClear+0x58>
10103438:	3380      	adds	r3, #128	; 0x80
1010343a:	4298      	cmp	r0, r3
1010343c:	d004      	beq.n	10103448 <RTIM_INTClear+0x58>
1010343e:	f240 111d 	movw	r1, #285	; 0x11d
10103442:	4805      	ldr	r0, [pc, #20]	; (10103458 <RTIM_INTClear+0x68>)
10103444:	f7fd fa14 	bl	10100870 <io_assert_failed>
10103448:	60e5      	str	r5, [r4, #12]
1010344a:	68e3      	ldr	r3, [r4, #12]
1010344c:	bd38      	pop	{r3, r4, r5, pc}
1010344e:	bf00      	nop
10103450:	40002000 	.word	0x40002000
10103454:	48002000 	.word	0x48002000
10103458:	101d51d0 	.word	0x101d51d0

1010345c <RTIM_TimeBaseInit>:
1010345c:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
10103460:	4604      	mov	r4, r0
10103462:	4841      	ldr	r0, [pc, #260]	; (10103568 <RTIM_TimeBaseInit+0x10c>)
10103464:	4284      	cmp	r4, r0
10103466:	460d      	mov	r5, r1
10103468:	4617      	mov	r7, r2
1010346a:	461e      	mov	r6, r3
1010346c:	d024      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
1010346e:	4b3f      	ldr	r3, [pc, #252]	; (1010356c <RTIM_TimeBaseInit+0x110>)
10103470:	429c      	cmp	r4, r3
10103472:	d021      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
10103474:	3380      	adds	r3, #128	; 0x80
10103476:	429c      	cmp	r4, r3
10103478:	d01e      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
1010347a:	3380      	adds	r3, #128	; 0x80
1010347c:	429c      	cmp	r4, r3
1010347e:	d01b      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
10103480:	3380      	adds	r3, #128	; 0x80
10103482:	429c      	cmp	r4, r3
10103484:	d018      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
10103486:	3380      	adds	r3, #128	; 0x80
10103488:	429c      	cmp	r4, r3
1010348a:	d015      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
1010348c:	4b38      	ldr	r3, [pc, #224]	; (10103570 <RTIM_TimeBaseInit+0x114>)
1010348e:	429c      	cmp	r4, r3
10103490:	d012      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
10103492:	3380      	adds	r3, #128	; 0x80
10103494:	429c      	cmp	r4, r3
10103496:	d00f      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
10103498:	3380      	adds	r3, #128	; 0x80
1010349a:	429c      	cmp	r4, r3
1010349c:	d00c      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
1010349e:	3380      	adds	r3, #128	; 0x80
101034a0:	429c      	cmp	r4, r3
101034a2:	d009      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
101034a4:	3380      	adds	r3, #128	; 0x80
101034a6:	429c      	cmp	r4, r3
101034a8:	d006      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
101034aa:	3380      	adds	r3, #128	; 0x80
101034ac:	429c      	cmp	r4, r3
101034ae:	d003      	beq.n	101034b8 <RTIM_TimeBaseInit+0x5c>
101034b0:	213d      	movs	r1, #61	; 0x3d
101034b2:	4830      	ldr	r0, [pc, #192]	; (10103574 <RTIM_TimeBaseInit+0x118>)
101034b4:	f7fd f9dc 	bl	10100870 <io_assert_failed>
101034b8:	68eb      	ldr	r3, [r5, #12]
101034ba:	f033 0304 	bics.w	r3, r3, #4
101034be:	d003      	beq.n	101034c8 <RTIM_TimeBaseInit+0x6c>
101034c0:	213e      	movs	r1, #62	; 0x3e
101034c2:	482c      	ldr	r0, [pc, #176]	; (10103574 <RTIM_TimeBaseInit+0x118>)
101034c4:	f7fd f9d4 	bl	10100870 <io_assert_failed>
101034c8:	682b      	ldr	r3, [r5, #0]
101034ca:	2bff      	cmp	r3, #255	; 0xff
101034cc:	d847      	bhi.n	1010355e <RTIM_TimeBaseInit+0x102>
101034ce:	f04f 0800 	mov.w	r8, #0
101034d2:	4620      	mov	r0, r4
101034d4:	4641      	mov	r1, r8
101034d6:	4b28      	ldr	r3, [pc, #160]	; (10103578 <RTIM_TimeBaseInit+0x11c>)
101034d8:	4798      	blx	r3
101034da:	4b28      	ldr	r3, [pc, #160]	; (1010357c <RTIM_TimeBaseInit+0x120>)
101034dc:	f8c4 8008 	str.w	r8, [r4, #8]
101034e0:	4620      	mov	r0, r4
101034e2:	4798      	blx	r3
101034e4:	4b26      	ldr	r3, [pc, #152]	; (10103580 <RTIM_TimeBaseInit+0x124>)
101034e6:	686a      	ldr	r2, [r5, #4]
101034e8:	429c      	cmp	r4, r3
101034ea:	61e2      	str	r2, [r4, #28]
101034ec:	d034      	beq.n	10103558 <RTIM_TimeBaseInit+0xfc>
101034ee:	3380      	adds	r3, #128	; 0x80
101034f0:	429c      	cmp	r4, r3
101034f2:	d031      	beq.n	10103558 <RTIM_TimeBaseInit+0xfc>
101034f4:	4b23      	ldr	r3, [pc, #140]	; (10103584 <RTIM_TimeBaseInit+0x128>)
101034f6:	429c      	cmp	r4, r3
101034f8:	d02e      	beq.n	10103558 <RTIM_TimeBaseInit+0xfc>
101034fa:	3380      	adds	r3, #128	; 0x80
101034fc:	429c      	cmp	r4, r3
101034fe:	d02b      	beq.n	10103558 <RTIM_TimeBaseInit+0xfc>
10103500:	f8c4 8018 	str.w	r8, [r4, #24]
10103504:	692a      	ldr	r2, [r5, #16]
10103506:	6863      	ldr	r3, [r4, #4]
10103508:	b31a      	cbz	r2, 10103552 <RTIM_TimeBaseInit+0xf6>
1010350a:	f043 0310 	orr.w	r3, r3, #16
1010350e:	68ea      	ldr	r2, [r5, #12]
10103510:	2a04      	cmp	r2, #4
10103512:	68aa      	ldr	r2, [r5, #8]
10103514:	bf0c      	ite	eq
10103516:	f043 0304 	orreq.w	r3, r3, #4
1010351a:	f023 0304 	bicne.w	r3, r3, #4
1010351e:	b9aa      	cbnz	r2, 1010354c <RTIM_TimeBaseInit+0xf0>
10103520:	f043 0302 	orr.w	r3, r3, #2
10103524:	6063      	str	r3, [r4, #4]
10103526:	b146      	cbz	r6, 1010353a <RTIM_TimeBaseInit+0xde>
10103528:	230e      	movs	r3, #14
1010352a:	4630      	mov	r0, r6
1010352c:	9a06      	ldr	r2, [sp, #24]
1010352e:	4639      	mov	r1, r7
10103530:	4d15      	ldr	r5, [pc, #84]	; (10103588 <RTIM_TimeBaseInit+0x12c>)
10103532:	47a8      	blx	r5
10103534:	4638      	mov	r0, r7
10103536:	4b15      	ldr	r3, [pc, #84]	; (1010358c <RTIM_TimeBaseInit+0x130>)
10103538:	4798      	blx	r3
1010353a:	2301      	movs	r3, #1
1010353c:	6123      	str	r3, [r4, #16]
1010353e:	68e3      	ldr	r3, [r4, #12]
10103540:	2b00      	cmp	r3, #0
10103542:	dafc      	bge.n	1010353e <RTIM_TimeBaseInit+0xe2>
10103544:	4b12      	ldr	r3, [pc, #72]	; (10103590 <RTIM_TimeBaseInit+0x134>)
10103546:	60e3      	str	r3, [r4, #12]
10103548:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
1010354c:	f023 0302 	bic.w	r3, r3, #2
10103550:	e7e8      	b.n	10103524 <RTIM_TimeBaseInit+0xc8>
10103552:	f023 0310 	bic.w	r3, r3, #16
10103556:	e7da      	b.n	1010350e <RTIM_TimeBaseInit+0xb2>
10103558:	682b      	ldr	r3, [r5, #0]
1010355a:	61a3      	str	r3, [r4, #24]
1010355c:	e7d2      	b.n	10103504 <RTIM_TimeBaseInit+0xa8>
1010355e:	213f      	movs	r1, #63	; 0x3f
10103560:	4804      	ldr	r0, [pc, #16]	; (10103574 <RTIM_TimeBaseInit+0x118>)
10103562:	f7fd f985 	bl	10100870 <io_assert_failed>
10103566:	e7b2      	b.n	101034ce <RTIM_TimeBaseInit+0x72>
10103568:	40002000 	.word	0x40002000
1010356c:	40002080 	.word	0x40002080
10103570:	48002000 	.word	0x48002000
10103574:	101d5144 	.word	0x101d5144
10103578:	1010326d 	.word	0x1010326d
1010357c:	101033f1 	.word	0x101033f1
10103580:	40002200 	.word	0x40002200
10103584:	48002200 	.word	0x48002200
10103588:	10106aa9 	.word	0x10106aa9
1010358c:	101069b9 	.word	0x101069b9
10103590:	0007ffff 	.word	0x0007ffff

10103594 <RTIM_DeInit>:
10103594:	4b19      	ldr	r3, [pc, #100]	; (101035fc <RTIM_DeInit+0x68>)
10103596:	4298      	cmp	r0, r3
10103598:	b510      	push	{r4, lr}
1010359a:	4604      	mov	r4, r0
1010359c:	d024      	beq.n	101035e8 <RTIM_DeInit+0x54>
1010359e:	3380      	adds	r3, #128	; 0x80
101035a0:	4298      	cmp	r0, r3
101035a2:	d021      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035a4:	3380      	adds	r3, #128	; 0x80
101035a6:	4298      	cmp	r0, r3
101035a8:	d01e      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035aa:	3380      	adds	r3, #128	; 0x80
101035ac:	4298      	cmp	r0, r3
101035ae:	d01b      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035b0:	3380      	adds	r3, #128	; 0x80
101035b2:	4298      	cmp	r0, r3
101035b4:	d018      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035b6:	3380      	adds	r3, #128	; 0x80
101035b8:	4298      	cmp	r0, r3
101035ba:	d015      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035bc:	4b10      	ldr	r3, [pc, #64]	; (10103600 <RTIM_DeInit+0x6c>)
101035be:	4298      	cmp	r0, r3
101035c0:	d012      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035c2:	3380      	adds	r3, #128	; 0x80
101035c4:	4298      	cmp	r0, r3
101035c6:	d00f      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035c8:	3380      	adds	r3, #128	; 0x80
101035ca:	4298      	cmp	r0, r3
101035cc:	d00c      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035ce:	3380      	adds	r3, #128	; 0x80
101035d0:	4298      	cmp	r0, r3
101035d2:	d009      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035d4:	3380      	adds	r3, #128	; 0x80
101035d6:	4298      	cmp	r0, r3
101035d8:	d006      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035da:	3380      	adds	r3, #128	; 0x80
101035dc:	4298      	cmp	r0, r3
101035de:	d003      	beq.n	101035e8 <RTIM_DeInit+0x54>
101035e0:	21b6      	movs	r1, #182	; 0xb6
101035e2:	4808      	ldr	r0, [pc, #32]	; (10103604 <RTIM_DeInit+0x70>)
101035e4:	f7fd f944 	bl	10100870 <io_assert_failed>
101035e8:	2100      	movs	r1, #0
101035ea:	4620      	mov	r0, r4
101035ec:	4b06      	ldr	r3, [pc, #24]	; (10103608 <RTIM_DeInit+0x74>)
101035ee:	4798      	blx	r3
101035f0:	4b06      	ldr	r3, [pc, #24]	; (1010360c <RTIM_DeInit+0x78>)
101035f2:	4620      	mov	r0, r4
101035f4:	4798      	blx	r3
101035f6:	2300      	movs	r3, #0
101035f8:	60a3      	str	r3, [r4, #8]
101035fa:	bd10      	pop	{r4, pc}
101035fc:	40002000 	.word	0x40002000
10103600:	48002000 	.word	0x48002000
10103604:	101d517c 	.word	0x101d517c
10103608:	1010326d 	.word	0x1010326d
1010360c:	101033f1 	.word	0x101033f1

10103610 <RTIM_INTClearPendingBit>:
10103610:	b538      	push	{r3, r4, r5, lr}
10103612:	4b19      	ldr	r3, [pc, #100]	; (10103678 <RTIM_INTClearPendingBit+0x68>)
10103614:	4298      	cmp	r0, r3
10103616:	4604      	mov	r4, r0
10103618:	460d      	mov	r5, r1
1010361a:	d025      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
1010361c:	3380      	adds	r3, #128	; 0x80
1010361e:	4298      	cmp	r0, r3
10103620:	d022      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
10103622:	3380      	adds	r3, #128	; 0x80
10103624:	4298      	cmp	r0, r3
10103626:	d01f      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
10103628:	3380      	adds	r3, #128	; 0x80
1010362a:	4298      	cmp	r0, r3
1010362c:	d01c      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
1010362e:	3380      	adds	r3, #128	; 0x80
10103630:	4298      	cmp	r0, r3
10103632:	d019      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
10103634:	3380      	adds	r3, #128	; 0x80
10103636:	4298      	cmp	r0, r3
10103638:	d016      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
1010363a:	4b10      	ldr	r3, [pc, #64]	; (1010367c <RTIM_INTClearPendingBit+0x6c>)
1010363c:	4298      	cmp	r0, r3
1010363e:	d013      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
10103640:	3380      	adds	r3, #128	; 0x80
10103642:	4298      	cmp	r0, r3
10103644:	d010      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
10103646:	3380      	adds	r3, #128	; 0x80
10103648:	4298      	cmp	r0, r3
1010364a:	d00d      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
1010364c:	3380      	adds	r3, #128	; 0x80
1010364e:	4298      	cmp	r0, r3
10103650:	d00a      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
10103652:	3380      	adds	r3, #128	; 0x80
10103654:	4298      	cmp	r0, r3
10103656:	d007      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
10103658:	3380      	adds	r3, #128	; 0x80
1010365a:	4298      	cmp	r0, r3
1010365c:	d004      	beq.n	10103668 <RTIM_INTClearPendingBit+0x58>
1010365e:	f44f 71a5 	mov.w	r1, #330	; 0x14a
10103662:	4807      	ldr	r0, [pc, #28]	; (10103680 <RTIM_INTClearPendingBit+0x70>)
10103664:	f7fd f904 	bl	10100870 <io_assert_failed>
10103668:	b925      	cbnz	r5, 10103674 <RTIM_INTClearPendingBit+0x64>
1010366a:	f240 114b 	movw	r1, #331	; 0x14b
1010366e:	4804      	ldr	r0, [pc, #16]	; (10103680 <RTIM_INTClearPendingBit+0x70>)
10103670:	f7fd f8fe 	bl	10100870 <io_assert_failed>
10103674:	60e5      	str	r5, [r4, #12]
10103676:	bd38      	pop	{r3, r4, r5, pc}
10103678:	40002000 	.word	0x40002000
1010367c:	48002000 	.word	0x48002000
10103680:	101d5158 	.word	0x101d5158

10103684 <RTIM_GetFlagStatus>:
10103684:	b538      	push	{r3, r4, r5, lr}
10103686:	4b31      	ldr	r3, [pc, #196]	; (1010374c <RTIM_GetFlagStatus+0xc8>)
10103688:	4298      	cmp	r0, r3
1010368a:	4604      	mov	r4, r0
1010368c:	460d      	mov	r5, r1
1010368e:	d025      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
10103690:	3380      	adds	r3, #128	; 0x80
10103692:	4298      	cmp	r0, r3
10103694:	d022      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
10103696:	3380      	adds	r3, #128	; 0x80
10103698:	4298      	cmp	r0, r3
1010369a:	d01f      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
1010369c:	3380      	adds	r3, #128	; 0x80
1010369e:	4298      	cmp	r0, r3
101036a0:	d01c      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
101036a2:	3380      	adds	r3, #128	; 0x80
101036a4:	4298      	cmp	r0, r3
101036a6:	d019      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
101036a8:	3380      	adds	r3, #128	; 0x80
101036aa:	4298      	cmp	r0, r3
101036ac:	d016      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
101036ae:	4b28      	ldr	r3, [pc, #160]	; (10103750 <RTIM_GetFlagStatus+0xcc>)
101036b0:	4298      	cmp	r0, r3
101036b2:	d013      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
101036b4:	3380      	adds	r3, #128	; 0x80
101036b6:	4298      	cmp	r0, r3
101036b8:	d010      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
101036ba:	3380      	adds	r3, #128	; 0x80
101036bc:	4298      	cmp	r0, r3
101036be:	d00d      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
101036c0:	3380      	adds	r3, #128	; 0x80
101036c2:	4298      	cmp	r0, r3
101036c4:	d00a      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
101036c6:	3380      	adds	r3, #128	; 0x80
101036c8:	4298      	cmp	r0, r3
101036ca:	d007      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
101036cc:	3380      	adds	r3, #128	; 0x80
101036ce:	4298      	cmp	r0, r3
101036d0:	d004      	beq.n	101036dc <RTIM_GetFlagStatus+0x58>
101036d2:	f44f 71bc 	mov.w	r1, #376	; 0x178
101036d6:	481f      	ldr	r0, [pc, #124]	; (10103754 <RTIM_GetFlagStatus+0xd0>)
101036d8:	f7fd f8ca 	bl	10100870 <io_assert_failed>
101036dc:	1e6a      	subs	r2, r5, #1
101036de:	2a1f      	cmp	r2, #31
101036e0:	d907      	bls.n	101036f2 <RTIM_GetFlagStatus+0x6e>
101036e2:	2d40      	cmp	r5, #64	; 0x40
101036e4:	d109      	bne.n	101036fa <RTIM_GetFlagStatus+0x76>
101036e6:	68e3      	ldr	r3, [r4, #12]
101036e8:	421d      	tst	r5, r3
101036ea:	bf14      	ite	ne
101036ec:	2001      	movne	r0, #1
101036ee:	2000      	moveq	r0, #0
101036f0:	bd38      	pop	{r3, r4, r5, pc}
101036f2:	4b19      	ldr	r3, [pc, #100]	; (10103758 <RTIM_GetFlagStatus+0xd4>)
101036f4:	40d3      	lsrs	r3, r2
101036f6:	07db      	lsls	r3, r3, #31
101036f8:	d4f5      	bmi.n	101036e6 <RTIM_GetFlagStatus+0x62>
101036fa:	2d80      	cmp	r5, #128	; 0x80
101036fc:	d0f3      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
101036fe:	f5b5 7f80 	cmp.w	r5, #256	; 0x100
10103702:	d0f0      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
10103704:	f5b5 7f00 	cmp.w	r5, #512	; 0x200
10103708:	d0ed      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
1010370a:	f5b5 6f80 	cmp.w	r5, #1024	; 0x400
1010370e:	d0ea      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
10103710:	f5b5 6f00 	cmp.w	r5, #2048	; 0x800
10103714:	d0e7      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
10103716:	f5b5 5f80 	cmp.w	r5, #4096	; 0x1000
1010371a:	d0e4      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
1010371c:	f5b5 5f00 	cmp.w	r5, #8192	; 0x2000
10103720:	d0e1      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
10103722:	f5b5 4f80 	cmp.w	r5, #16384	; 0x4000
10103726:	d0de      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
10103728:	f5b5 4f00 	cmp.w	r5, #32768	; 0x8000
1010372c:	d0db      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
1010372e:	f5b5 3f80 	cmp.w	r5, #65536	; 0x10000
10103732:	d0d8      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
10103734:	f5b5 3f00 	cmp.w	r5, #131072	; 0x20000
10103738:	d0d5      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
1010373a:	f5b5 2f80 	cmp.w	r5, #262144	; 0x40000
1010373e:	d0d2      	beq.n	101036e6 <RTIM_GetFlagStatus+0x62>
10103740:	f240 1179 	movw	r1, #377	; 0x179
10103744:	4803      	ldr	r0, [pc, #12]	; (10103754 <RTIM_GetFlagStatus+0xd0>)
10103746:	f7fd f893 	bl	10100870 <io_assert_failed>
1010374a:	e7cc      	b.n	101036e6 <RTIM_GetFlagStatus+0x62>
1010374c:	40002000 	.word	0x40002000
10103750:	48002000 	.word	0x48002000
10103754:	101d5198 	.word	0x101d5198
10103758:	8000808b 	.word	0x8000808b

1010375c <RTIM_GetINTStatus>:
1010375c:	b538      	push	{r3, r4, r5, lr}
1010375e:	4b33      	ldr	r3, [pc, #204]	; (1010382c <RTIM_GetINTStatus+0xd0>)
10103760:	4298      	cmp	r0, r3
10103762:	4604      	mov	r4, r0
10103764:	460d      	mov	r5, r1
10103766:	d025      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
10103768:	3380      	adds	r3, #128	; 0x80
1010376a:	4298      	cmp	r0, r3
1010376c:	d022      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
1010376e:	3380      	adds	r3, #128	; 0x80
10103770:	4298      	cmp	r0, r3
10103772:	d01f      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
10103774:	3380      	adds	r3, #128	; 0x80
10103776:	4298      	cmp	r0, r3
10103778:	d01c      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
1010377a:	3380      	adds	r3, #128	; 0x80
1010377c:	4298      	cmp	r0, r3
1010377e:	d019      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
10103780:	3380      	adds	r3, #128	; 0x80
10103782:	4298      	cmp	r0, r3
10103784:	d016      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
10103786:	4b2a      	ldr	r3, [pc, #168]	; (10103830 <RTIM_GetINTStatus+0xd4>)
10103788:	4298      	cmp	r0, r3
1010378a:	d013      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
1010378c:	3380      	adds	r3, #128	; 0x80
1010378e:	4298      	cmp	r0, r3
10103790:	d010      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
10103792:	3380      	adds	r3, #128	; 0x80
10103794:	4298      	cmp	r0, r3
10103796:	d00d      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
10103798:	3380      	adds	r3, #128	; 0x80
1010379a:	4298      	cmp	r0, r3
1010379c:	d00a      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
1010379e:	3380      	adds	r3, #128	; 0x80
101037a0:	4298      	cmp	r0, r3
101037a2:	d007      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
101037a4:	3380      	adds	r3, #128	; 0x80
101037a6:	4298      	cmp	r0, r3
101037a8:	d004      	beq.n	101037b4 <RTIM_GetINTStatus+0x58>
101037aa:	f240 11af 	movw	r1, #431	; 0x1af
101037ae:	4821      	ldr	r0, [pc, #132]	; (10103834 <RTIM_GetINTStatus+0xd8>)
101037b0:	f7fd f85e 	bl	10100870 <io_assert_failed>
101037b4:	1e6a      	subs	r2, r5, #1
101037b6:	2a1f      	cmp	r2, #31
101037b8:	d90a      	bls.n	101037d0 <RTIM_GetINTStatus+0x74>
101037ba:	2d40      	cmp	r5, #64	; 0x40
101037bc:	d10c      	bne.n	101037d8 <RTIM_GetINTStatus+0x7c>
101037be:	68e0      	ldr	r0, [r4, #12]
101037c0:	4028      	ands	r0, r5
101037c2:	68a3      	ldr	r3, [r4, #8]
101037c4:	d031      	beq.n	1010382a <RTIM_GetINTStatus+0xce>
101037c6:	421d      	tst	r5, r3
101037c8:	bf14      	ite	ne
101037ca:	2001      	movne	r0, #1
101037cc:	2000      	moveq	r0, #0
101037ce:	bd38      	pop	{r3, r4, r5, pc}
101037d0:	4b19      	ldr	r3, [pc, #100]	; (10103838 <RTIM_GetINTStatus+0xdc>)
101037d2:	40d3      	lsrs	r3, r2
101037d4:	07db      	lsls	r3, r3, #31
101037d6:	d4f2      	bmi.n	101037be <RTIM_GetINTStatus+0x62>
101037d8:	2d80      	cmp	r5, #128	; 0x80
101037da:	d0f0      	beq.n	101037be <RTIM_GetINTStatus+0x62>
101037dc:	f5b5 7f80 	cmp.w	r5, #256	; 0x100
101037e0:	d0ed      	beq.n	101037be <RTIM_GetINTStatus+0x62>
101037e2:	f5b5 7f00 	cmp.w	r5, #512	; 0x200
101037e6:	d0ea      	beq.n	101037be <RTIM_GetINTStatus+0x62>
101037e8:	f5b5 6f80 	cmp.w	r5, #1024	; 0x400
101037ec:	d0e7      	beq.n	101037be <RTIM_GetINTStatus+0x62>
101037ee:	f5b5 6f00 	cmp.w	r5, #2048	; 0x800
101037f2:	d0e4      	beq.n	101037be <RTIM_GetINTStatus+0x62>
101037f4:	f5b5 5f80 	cmp.w	r5, #4096	; 0x1000
101037f8:	d0e1      	beq.n	101037be <RTIM_GetINTStatus+0x62>
101037fa:	f5b5 5f00 	cmp.w	r5, #8192	; 0x2000
101037fe:	d0de      	beq.n	101037be <RTIM_GetINTStatus+0x62>
10103800:	f5b5 4f80 	cmp.w	r5, #16384	; 0x4000
10103804:	d0db      	beq.n	101037be <RTIM_GetINTStatus+0x62>
10103806:	f5b5 4f00 	cmp.w	r5, #32768	; 0x8000
1010380a:	d0d8      	beq.n	101037be <RTIM_GetINTStatus+0x62>
1010380c:	f5b5 3f80 	cmp.w	r5, #65536	; 0x10000
10103810:	d0d5      	beq.n	101037be <RTIM_GetINTStatus+0x62>
10103812:	f5b5 3f00 	cmp.w	r5, #131072	; 0x20000
10103816:	d0d2      	beq.n	101037be <RTIM_GetINTStatus+0x62>
10103818:	f5b5 2f80 	cmp.w	r5, #262144	; 0x40000
1010381c:	d0cf      	beq.n	101037be <RTIM_GetINTStatus+0x62>
1010381e:	f44f 71d8 	mov.w	r1, #432	; 0x1b0
10103822:	4804      	ldr	r0, [pc, #16]	; (10103834 <RTIM_GetINTStatus+0xd8>)
10103824:	f7fd f824 	bl	10100870 <io_assert_failed>
10103828:	e7c9      	b.n	101037be <RTIM_GetINTStatus+0x62>
1010382a:	bd38      	pop	{r3, r4, r5, pc}
1010382c:	40002000 	.word	0x40002000
10103830:	48002000 	.word	0x48002000
10103834:	101d51bc 	.word	0x101d51bc
10103838:	8000808b 	.word	0x8000808b

1010383c <UART_DeInit>:
1010383c:	2300      	movs	r3, #0
1010383e:	6043      	str	r3, [r0, #4]
10103840:	4770      	bx	lr
10103842:	bf00      	nop

10103844 <UART_StructInit>:
10103844:	2300      	movs	r3, #0
10103846:	2201      	movs	r2, #1
10103848:	2140      	movs	r1, #64	; 0x40
1010384a:	60c2      	str	r2, [r0, #12]
1010384c:	6241      	str	r1, [r0, #36]	; 0x24
1010384e:	6042      	str	r2, [r0, #4]
10103850:	6202      	str	r2, [r0, #32]
10103852:	6002      	str	r2, [r0, #0]
10103854:	6103      	str	r3, [r0, #16]
10103856:	6143      	str	r3, [r0, #20]
10103858:	6083      	str	r3, [r0, #8]
1010385a:	61c3      	str	r3, [r0, #28]
1010385c:	6183      	str	r3, [r0, #24]
1010385e:	4770      	bx	lr

10103860 <UART_BaudParaGetFull>:
10103860:	b5f0      	push	{r4, r5, r6, r7, lr}
10103862:	fbb0 fef1 	udiv	lr, r0, r1
10103866:	fb01 001e 	mls	r0, r1, lr, r0
1010386a:	eb00 0440 	add.w	r4, r0, r0, lsl #1
1010386e:	00a4      	lsls	r4, r4, #2
10103870:	fbb4 f6f1 	udiv	r6, r4, r1
10103874:	250b      	movs	r5, #11
10103876:	2700      	movs	r7, #0
10103878:	f8c2 e000 	str.w	lr, [r2]
1010387c:	1a24      	subs	r4, r4, r0
1010387e:	4632      	mov	r2, r6
10103880:	fbb4 f6f1 	udiv	r6, r4, r1
10103884:	1ab2      	subs	r2, r6, r2
10103886:	bf18      	it	ne
10103888:	2201      	movne	r2, #1
1010388a:	3d01      	subs	r5, #1
1010388c:	ea42 0747 	orr.w	r7, r2, r7, lsl #1
10103890:	d1f4      	bne.n	1010387c <UART_BaudParaGetFull+0x1c>
10103892:	601f      	str	r7, [r3, #0]
10103894:	bdf0      	pop	{r4, r5, r6, r7, pc}
10103896:	bf00      	nop

10103898 <UART_BaudParaGet>:
10103898:	b570      	push	{r4, r5, r6, lr}
1010389a:	460d      	mov	r5, r1
1010389c:	4616      	mov	r6, r2
1010389e:	4604      	mov	r4, r0
101038a0:	4b04      	ldr	r3, [pc, #16]	; (101038b4 <UART_BaudParaGet+0x1c>)
101038a2:	4798      	blx	r3
101038a4:	4621      	mov	r1, r4
101038a6:	4633      	mov	r3, r6
101038a8:	462a      	mov	r2, r5
101038aa:	4c03      	ldr	r4, [pc, #12]	; (101038b8 <UART_BaudParaGet+0x20>)
101038ac:	47a0      	blx	r4
101038ae:	2001      	movs	r0, #1
101038b0:	bd70      	pop	{r4, r5, r6, pc}
101038b2:	bf00      	nop
101038b4:	101044e9 	.word	0x101044e9
101038b8:	10103861 	.word	0x10103861

101038bc <UART_SetBaud>:
101038bc:	b530      	push	{r4, r5, lr}
101038be:	460d      	mov	r5, r1
101038c0:	4604      	mov	r4, r0
101038c2:	b083      	sub	sp, #12
101038c4:	4b1d      	ldr	r3, [pc, #116]	; (1010393c <UART_SetBaud+0x80>)
101038c6:	4798      	blx	r3
101038c8:	4629      	mov	r1, r5
101038ca:	ab01      	add	r3, sp, #4
101038cc:	466a      	mov	r2, sp
101038ce:	4d1c      	ldr	r5, [pc, #112]	; (10103940 <UART_SetBaud+0x84>)
101038d0:	47a8      	blx	r5
101038d2:	68e3      	ldr	r3, [r4, #12]
101038d4:	f043 0380 	orr.w	r3, r3, #128	; 0x80
101038d8:	60e3      	str	r3, [r4, #12]
101038da:	69e3      	ldr	r3, [r4, #28]
101038dc:	f043 0380 	orr.w	r3, r3, #128	; 0x80
101038e0:	61e3      	str	r3, [r4, #28]
101038e2:	9900      	ldr	r1, [sp, #0]
101038e4:	6a20      	ldr	r0, [r4, #32]
101038e6:	4b17      	ldr	r3, [pc, #92]	; (10103944 <UART_SetBaud+0x88>)
101038e8:	4a17      	ldr	r2, [pc, #92]	; (10103948 <UART_SetBaud+0x8c>)
101038ea:	4003      	ands	r3, r0
101038ec:	ea02 1201 	and.w	r2, r2, r1, lsl #4
101038f0:	4313      	orrs	r3, r2
101038f2:	6223      	str	r3, [r4, #32]
101038f4:	69e2      	ldr	r2, [r4, #28]
101038f6:	9801      	ldr	r0, [sp, #4]
101038f8:	4b14      	ldr	r3, [pc, #80]	; (1010394c <UART_SetBaud+0x90>)
101038fa:	f022 62ff 	bic.w	r2, r2, #133693440	; 0x7f80000
101038fe:	ea03 4300 	and.w	r3, r3, r0, lsl #16
10103902:	f422 22e0 	bic.w	r2, r2, #458752	; 0x70000
10103906:	431a      	orrs	r2, r3
10103908:	61e2      	str	r2, [r4, #28]
1010390a:	68e2      	ldr	r2, [r4, #12]
1010390c:	f022 0280 	bic.w	r2, r2, #128	; 0x80
10103910:	60e2      	str	r2, [r4, #12]
10103912:	6ca2      	ldr	r2, [r4, #72]	; 0x48
10103914:	0d12      	lsrs	r2, r2, #20
10103916:	0512      	lsls	r2, r2, #20
10103918:	430a      	orrs	r2, r1
1010391a:	64a2      	str	r2, [r4, #72]	; 0x48
1010391c:	4a0c      	ldr	r2, [pc, #48]	; (10103950 <UART_SetBaud+0x94>)
1010391e:	6c63      	ldr	r3, [r4, #68]	; 0x44
10103920:	401a      	ands	r2, r3
10103922:	ea42 2241 	orr.w	r2, r2, r1, lsl #9
10103926:	6462      	str	r2, [r4, #68]	; 0x44
10103928:	6c23      	ldr	r3, [r4, #64]	; 0x40
1010392a:	f423 537f 	bic.w	r3, r3, #16320	; 0x3fc0
1010392e:	f023 0338 	bic.w	r3, r3, #56	; 0x38
10103932:	ea43 03c0 	orr.w	r3, r3, r0, lsl #3
10103936:	6423      	str	r3, [r4, #64]	; 0x40
10103938:	b003      	add	sp, #12
1010393a:	bd30      	pop	{r4, r5, pc}
1010393c:	101044e9 	.word	0x101044e9
10103940:	10103861 	.word	0x10103861
10103944:	ff00000f 	.word	0xff00000f
10103948:	00fffff0 	.word	0x00fffff0
1010394c:	07ff0000 	.word	0x07ff0000
10103950:	e00001ff 	.word	0xe00001ff

10103954 <UART_SetBaudExt>:
10103954:	68c3      	ldr	r3, [r0, #12]
10103956:	f043 0380 	orr.w	r3, r3, #128	; 0x80
1010395a:	60c3      	str	r3, [r0, #12]
1010395c:	69c3      	ldr	r3, [r0, #28]
1010395e:	f043 0380 	orr.w	r3, r3, #128	; 0x80
10103962:	61c3      	str	r3, [r0, #28]
10103964:	b430      	push	{r4, r5}
10103966:	4b15      	ldr	r3, [pc, #84]	; (101039bc <UART_SetBaudExt+0x68>)
10103968:	6a04      	ldr	r4, [r0, #32]
1010396a:	4d15      	ldr	r5, [pc, #84]	; (101039c0 <UART_SetBaudExt+0x6c>)
1010396c:	ea03 1301 	and.w	r3, r3, r1, lsl #4
10103970:	4025      	ands	r5, r4
10103972:	431d      	orrs	r5, r3
10103974:	6205      	str	r5, [r0, #32]
10103976:	69c4      	ldr	r4, [r0, #28]
10103978:	4b12      	ldr	r3, [pc, #72]	; (101039c4 <UART_SetBaudExt+0x70>)
1010397a:	f024 64ff 	bic.w	r4, r4, #133693440	; 0x7f80000
1010397e:	ea03 4302 	and.w	r3, r3, r2, lsl #16
10103982:	f424 24e0 	bic.w	r4, r4, #458752	; 0x70000
10103986:	431c      	orrs	r4, r3
10103988:	61c4      	str	r4, [r0, #28]
1010398a:	68c3      	ldr	r3, [r0, #12]
1010398c:	f023 0380 	bic.w	r3, r3, #128	; 0x80
10103990:	60c3      	str	r3, [r0, #12]
10103992:	6c84      	ldr	r4, [r0, #72]	; 0x48
10103994:	0d24      	lsrs	r4, r4, #20
10103996:	0524      	lsls	r4, r4, #20
10103998:	430c      	orrs	r4, r1
1010399a:	6484      	str	r4, [r0, #72]	; 0x48
1010399c:	4c0a      	ldr	r4, [pc, #40]	; (101039c8 <UART_SetBaudExt+0x74>)
1010399e:	6c43      	ldr	r3, [r0, #68]	; 0x44
101039a0:	401c      	ands	r4, r3
101039a2:	ea44 2441 	orr.w	r4, r4, r1, lsl #9
101039a6:	6444      	str	r4, [r0, #68]	; 0x44
101039a8:	6c03      	ldr	r3, [r0, #64]	; 0x40
101039aa:	f423 537f 	bic.w	r3, r3, #16320	; 0x3fc0
101039ae:	f023 0338 	bic.w	r3, r3, #56	; 0x38
101039b2:	ea43 03c2 	orr.w	r3, r3, r2, lsl #3
101039b6:	6403      	str	r3, [r0, #64]	; 0x40
101039b8:	bc30      	pop	{r4, r5}
101039ba:	4770      	bx	lr
101039bc:	00fffff0 	.word	0x00fffff0
101039c0:	ff00000f 	.word	0xff00000f
101039c4:	07ff0000 	.word	0x07ff0000
101039c8:	e00001ff 	.word	0xe00001ff

101039cc <UART_SetRxLevel>:
101039cc:	b538      	push	{r3, r4, r5, lr}
101039ce:	f031 03c0 	bics.w	r3, r1, #192	; 0xc0
101039d2:	460d      	mov	r5, r1
101039d4:	4604      	mov	r4, r0
101039d6:	d004      	beq.n	101039e2 <UART_SetRxLevel+0x16>
101039d8:	f44f 71b5 	mov.w	r1, #362	; 0x16a
101039dc:	4804      	ldr	r0, [pc, #16]	; (101039f0 <UART_SetRxLevel+0x24>)
101039de:	f7fc ff47 	bl	10100870 <io_assert_failed>
101039e2:	6d61      	ldr	r1, [r4, #84]	; 0x54
101039e4:	f021 01c0 	bic.w	r1, r1, #192	; 0xc0
101039e8:	4329      	orrs	r1, r5
101039ea:	6561      	str	r1, [r4, #84]	; 0x54
101039ec:	bd38      	pop	{r3, r4, r5, pc}
101039ee:	bf00      	nop
101039f0:	101d51ec 	.word	0x101d51ec

101039f4 <UART_RxCmd>:
101039f4:	6c03      	ldr	r3, [r0, #64]	; 0x40
101039f6:	b919      	cbnz	r1, 10103a00 <UART_RxCmd+0xc>
101039f8:	f023 0304 	bic.w	r3, r3, #4
101039fc:	6403      	str	r3, [r0, #64]	; 0x40
101039fe:	4770      	bx	lr
10103a00:	f043 0304 	orr.w	r3, r3, #4
10103a04:	6403      	str	r3, [r0, #64]	; 0x40
10103a06:	4770      	bx	lr

10103a08 <UART_Writable>:
10103a08:	6940      	ldr	r0, [r0, #20]
10103a0a:	f3c0 1040 	ubfx	r0, r0, #5, #1
10103a0e:	4770      	bx	lr

10103a10 <UART_Readable>:
10103a10:	6940      	ldr	r0, [r0, #20]
10103a12:	f000 0001 	and.w	r0, r0, #1
10103a16:	4770      	bx	lr

10103a18 <UART_CharPut>:
10103a18:	6241      	str	r1, [r0, #36]	; 0x24
10103a1a:	4770      	bx	lr

10103a1c <UART_CharGet>:
10103a1c:	6a43      	ldr	r3, [r0, #36]	; 0x24
10103a1e:	700b      	strb	r3, [r1, #0]
10103a20:	4770      	bx	lr
10103a22:	bf00      	nop

10103a24 <UART_ReceiveData>:
10103a24:	b172      	cbz	r2, 10103a44 <UART_ReceiveData+0x20>
10103a26:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
10103a28:	4604      	mov	r4, r0
10103a2a:	460e      	mov	r6, r1
10103a2c:	4d06      	ldr	r5, [pc, #24]	; (10103a48 <UART_ReceiveData+0x24>)
10103a2e:	188f      	adds	r7, r1, r2
10103a30:	4620      	mov	r0, r4
10103a32:	47a8      	blx	r5
10103a34:	2800      	cmp	r0, #0
10103a36:	d0fb      	beq.n	10103a30 <UART_ReceiveData+0xc>
10103a38:	6a63      	ldr	r3, [r4, #36]	; 0x24
10103a3a:	f806 3b01 	strb.w	r3, [r6], #1
10103a3e:	42b7      	cmp	r7, r6
10103a40:	d1f6      	bne.n	10103a30 <UART_ReceiveData+0xc>
10103a42:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10103a44:	4770      	bx	lr
10103a46:	bf00      	nop
10103a48:	10103a11 	.word	0x10103a11

10103a4c <UART_SendData>:
10103a4c:	b172      	cbz	r2, 10103a6c <UART_SendData+0x20>
10103a4e:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
10103a50:	4604      	mov	r4, r0
10103a52:	460e      	mov	r6, r1
10103a54:	4d06      	ldr	r5, [pc, #24]	; (10103a70 <UART_SendData+0x24>)
10103a56:	188f      	adds	r7, r1, r2
10103a58:	4620      	mov	r0, r4
10103a5a:	47a8      	blx	r5
10103a5c:	2800      	cmp	r0, #0
10103a5e:	d0fb      	beq.n	10103a58 <UART_SendData+0xc>
10103a60:	f816 3b01 	ldrb.w	r3, [r6], #1
10103a64:	42b7      	cmp	r7, r6
10103a66:	6263      	str	r3, [r4, #36]	; 0x24
10103a68:	d1f6      	bne.n	10103a58 <UART_SendData+0xc>
10103a6a:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10103a6c:	4770      	bx	lr
10103a6e:	bf00      	nop
10103a70:	10103a09 	.word	0x10103a09

10103a74 <UART_ReceiveDataTO>:
10103a74:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
10103a78:	2400      	movs	r4, #0
10103a7a:	4606      	mov	r6, r0
10103a7c:	468a      	mov	sl, r1
10103a7e:	4691      	mov	r9, r2
10103a80:	4698      	mov	r8, r3
10103a82:	4625      	mov	r5, r4
10103a84:	4f0a      	ldr	r7, [pc, #40]	; (10103ab0 <UART_ReceiveDataTO+0x3c>)
10103a86:	4630      	mov	r0, r6
10103a88:	47b8      	blx	r7
10103a8a:	3401      	adds	r4, #1
10103a8c:	b158      	cbz	r0, 10103aa6 <UART_ReceiveDataTO+0x32>
10103a8e:	6a73      	ldr	r3, [r6, #36]	; 0x24
10103a90:	f80a 3005 	strb.w	r3, [sl, r5]
10103a94:	3501      	adds	r5, #1
10103a96:	454d      	cmp	r5, r9
10103a98:	d207      	bcs.n	10103aaa <UART_ReceiveDataTO+0x36>
10103a9a:	4630      	mov	r0, r6
10103a9c:	2400      	movs	r4, #0
10103a9e:	47b8      	blx	r7
10103aa0:	3401      	adds	r4, #1
10103aa2:	2800      	cmp	r0, #0
10103aa4:	d1f3      	bne.n	10103a8e <UART_ReceiveDataTO+0x1a>
10103aa6:	4544      	cmp	r4, r8
10103aa8:	d9ed      	bls.n	10103a86 <UART_ReceiveDataTO+0x12>
10103aaa:	4628      	mov	r0, r5
10103aac:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
10103ab0:	10103a11 	.word	0x10103a11

10103ab4 <UART_SendDataTO>:
10103ab4:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
10103ab8:	2400      	movs	r4, #0
10103aba:	4606      	mov	r6, r0
10103abc:	468a      	mov	sl, r1
10103abe:	4691      	mov	r9, r2
10103ac0:	4698      	mov	r8, r3
10103ac2:	4625      	mov	r5, r4
10103ac4:	4f0a      	ldr	r7, [pc, #40]	; (10103af0 <UART_SendDataTO+0x3c>)
10103ac6:	4630      	mov	r0, r6
10103ac8:	47b8      	blx	r7
10103aca:	3401      	adds	r4, #1
10103acc:	b158      	cbz	r0, 10103ae6 <UART_SendDataTO+0x32>
10103ace:	f81a 3005 	ldrb.w	r3, [sl, r5]
10103ad2:	3501      	adds	r5, #1
10103ad4:	454d      	cmp	r5, r9
10103ad6:	6273      	str	r3, [r6, #36]	; 0x24
10103ad8:	d207      	bcs.n	10103aea <UART_SendDataTO+0x36>
10103ada:	4630      	mov	r0, r6
10103adc:	2400      	movs	r4, #0
10103ade:	47b8      	blx	r7
10103ae0:	3401      	adds	r4, #1
10103ae2:	2800      	cmp	r0, #0
10103ae4:	d1f3      	bne.n	10103ace <UART_SendDataTO+0x1a>
10103ae6:	4544      	cmp	r4, r8
10103ae8:	d9ed      	bls.n	10103ac6 <UART_SendDataTO+0x12>
10103aea:	4628      	mov	r0, r5
10103aec:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
10103af0:	10103a09 	.word	0x10103a09

10103af4 <UART_RxByteCntClear>:
10103af4:	6d03      	ldr	r3, [r0, #80]	; 0x50
10103af6:	f443 3380 	orr.w	r3, r3, #65536	; 0x10000
10103afa:	6503      	str	r3, [r0, #80]	; 0x50
10103afc:	4770      	bx	lr
10103afe:	bf00      	nop

10103b00 <UART_RxByteCntGet>:
10103b00:	6d00      	ldr	r0, [r0, #80]	; 0x50
10103b02:	b280      	uxth	r0, r0
10103b04:	4770      	bx	lr
10103b06:	bf00      	nop

10103b08 <UART_BreakCtl>:
10103b08:	68c3      	ldr	r3, [r0, #12]
10103b0a:	b919      	cbnz	r1, 10103b14 <UART_BreakCtl+0xc>
10103b0c:	f023 0340 	bic.w	r3, r3, #64	; 0x40
10103b10:	60c3      	str	r3, [r0, #12]
10103b12:	4770      	bx	lr
10103b14:	f043 0340 	orr.w	r3, r3, #64	; 0x40
10103b18:	60c3      	str	r3, [r0, #12]
10103b1a:	4770      	bx	lr

10103b1c <UART_ClearRxFifo>:
10103b1c:	2305      	movs	r3, #5
10103b1e:	6d42      	ldr	r2, [r0, #84]	; 0x54
10103b20:	f042 0202 	orr.w	r2, r2, #2
10103b24:	6542      	str	r2, [r0, #84]	; 0x54
10103b26:	6942      	ldr	r2, [r0, #20]
10103b28:	07d2      	lsls	r2, r2, #31
10103b2a:	d503      	bpl.n	10103b34 <UART_ClearRxFifo+0x18>
10103b2c:	3b01      	subs	r3, #1
10103b2e:	d1fa      	bne.n	10103b26 <UART_ClearRxFifo+0xa>
10103b30:	4618      	mov	r0, r3
10103b32:	4770      	bx	lr
10103b34:	2301      	movs	r3, #1
10103b36:	4618      	mov	r0, r3
10103b38:	4770      	bx	lr
10103b3a:	bf00      	nop

10103b3c <UART_Init>:
10103b3c:	b538      	push	{r3, r4, r5, lr}
10103b3e:	69cb      	ldr	r3, [r1, #28]
10103b40:	f033 03c0 	bics.w	r3, r3, #192	; 0xc0
10103b44:	460d      	mov	r5, r1
10103b46:	4604      	mov	r4, r0
10103b48:	d003      	beq.n	10103b52 <UART_Init+0x16>
10103b4a:	2183      	movs	r1, #131	; 0x83
10103b4c:	4823      	ldr	r0, [pc, #140]	; (10103bdc <UART_Init+0xa0>)
10103b4e:	f7fc fe8f 	bl	10100870 <io_assert_failed>
10103b52:	6a2b      	ldr	r3, [r5, #32]
10103b54:	2b01      	cmp	r3, #1
10103b56:	d903      	bls.n	10103b60 <UART_Init+0x24>
10103b58:	2184      	movs	r1, #132	; 0x84
10103b5a:	4820      	ldr	r0, [pc, #128]	; (10103bdc <UART_Init+0xa0>)
10103b5c:	f7fc fe88 	bl	10100870 <io_assert_failed>
10103b60:	6c23      	ldr	r3, [r4, #64]	; 0x40
10103b62:	f023 0304 	bic.w	r3, r3, #4
10103b66:	6423      	str	r3, [r4, #64]	; 0x40
10103b68:	4620      	mov	r0, r4
10103b6a:	4b1d      	ldr	r3, [pc, #116]	; (10103be0 <UART_Init+0xa4>)
10103b6c:	4798      	blx	r3
10103b6e:	2300      	movs	r3, #0
10103b70:	6063      	str	r3, [r4, #4]
10103b72:	69e3      	ldr	r3, [r4, #28]
10103b74:	f043 0380 	orr.w	r3, r3, #128	; 0x80
10103b78:	61e3      	str	r3, [r4, #28]
10103b7a:	69e9      	ldr	r1, [r5, #28]
10103b7c:	6d63      	ldr	r3, [r4, #84]	; 0x54
10103b7e:	6a2a      	ldr	r2, [r5, #32]
10103b80:	f023 03c1 	bic.w	r3, r3, #193	; 0xc1
10103b84:	430a      	orrs	r2, r1
10103b86:	4313      	orrs	r3, r2
10103b88:	69a9      	ldr	r1, [r5, #24]
10103b8a:	6563      	str	r3, [r4, #84]	; 0x54
10103b8c:	6923      	ldr	r3, [r4, #16]
10103b8e:	2901      	cmp	r1, #1
10103b90:	bf0c      	ite	eq
10103b92:	f043 0322 	orreq.w	r3, r3, #34	; 0x22
10103b96:	f023 0322 	bicne.w	r3, r3, #34	; 0x22
10103b9a:	6123      	str	r3, [r4, #16]
10103b9c:	f105 0108 	add.w	r1, r5, #8
10103ba0:	c906      	ldmia	r1, {r1, r2}
10103ba2:	686b      	ldr	r3, [r5, #4]
10103ba4:	00d2      	lsls	r2, r2, #3
10103ba6:	ea42 0281 	orr.w	r2, r2, r1, lsl #2
10103baa:	6928      	ldr	r0, [r5, #16]
10103bac:	4313      	orrs	r3, r2
10103bae:	6969      	ldr	r1, [r5, #20]
10103bb0:	ea43 1300 	orr.w	r3, r3, r0, lsl #4
10103bb4:	ea43 1341 	orr.w	r3, r3, r1, lsl #5
10103bb8:	682a      	ldr	r2, [r5, #0]
10103bba:	60e3      	str	r3, [r4, #12]
10103bbc:	6d63      	ldr	r3, [r4, #84]	; 0x54
10103bbe:	b94a      	cbnz	r2, 10103bd4 <UART_Init+0x98>
10103bc0:	f023 0308 	bic.w	r3, r3, #8
10103bc4:	6563      	str	r3, [r4, #84]	; 0x54
10103bc6:	6c23      	ldr	r3, [r4, #64]	; 0x40
10103bc8:	6a6a      	ldr	r2, [r5, #36]	; 0x24
10103bca:	b29b      	uxth	r3, r3
10103bcc:	ea43 4302 	orr.w	r3, r3, r2, lsl #16
10103bd0:	6423      	str	r3, [r4, #64]	; 0x40
10103bd2:	bd38      	pop	{r3, r4, r5, pc}
10103bd4:	f043 0308 	orr.w	r3, r3, #8
10103bd8:	6563      	str	r3, [r4, #84]	; 0x54
10103bda:	e7f4      	b.n	10103bc6 <UART_Init+0x8a>
10103bdc:	101d51e0 	.word	0x101d51e0
10103be0:	10103b1d 	.word	0x10103b1d

10103be4 <UART_ClearTxFifo>:
10103be4:	6d43      	ldr	r3, [r0, #84]	; 0x54
10103be6:	f043 0304 	orr.w	r3, r3, #4
10103bea:	6543      	str	r3, [r0, #84]	; 0x54
10103bec:	4770      	bx	lr
10103bee:	bf00      	nop

10103bf0 <UART_INTConfig>:
10103bf0:	6843      	ldr	r3, [r0, #4]
10103bf2:	2a01      	cmp	r2, #1
10103bf4:	bf0c      	ite	eq
10103bf6:	4319      	orreq	r1, r3
10103bf8:	ea23 0101 	bicne.w	r1, r3, r1
10103bfc:	6041      	str	r1, [r0, #4]
10103bfe:	4770      	bx	lr

10103c00 <UART_IntStatus>:
10103c00:	6880      	ldr	r0, [r0, #8]
10103c02:	4770      	bx	lr

10103c04 <UART_ModemStatusGet>:
10103c04:	6980      	ldr	r0, [r0, #24]
10103c06:	4770      	bx	lr

10103c08 <UART_LineStatusGet>:
10103c08:	6940      	ldr	r0, [r0, #20]
10103c0a:	4770      	bx	lr

10103c0c <UART_WaitBusy>:
10103c0c:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
10103c0e:	4605      	mov	r5, r0
10103c10:	460f      	mov	r7, r1
10103c12:	2400      	movs	r4, #0
10103c14:	4e05      	ldr	r6, [pc, #20]	; (10103c2c <UART_WaitBusy+0x20>)
10103c16:	e003      	b.n	10103c20 <UART_WaitBusy+0x14>
10103c18:	2064      	movs	r0, #100	; 0x64
10103c1a:	47b0      	blx	r6
10103c1c:	42bc      	cmp	r4, r7
10103c1e:	d804      	bhi.n	10103c2a <UART_WaitBusy+0x1e>
10103c20:	696b      	ldr	r3, [r5, #20]
10103c22:	065b      	lsls	r3, r3, #25
10103c24:	f104 0401 	add.w	r4, r4, #1
10103c28:	d5f6      	bpl.n	10103c18 <UART_WaitBusy+0xc>
10103c2a:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
10103c2c:	10100949 	.word	0x10100949

10103c30 <rtl_crypto_aes_cbc_init>:
10103c30:	b570      	push	{r4, r5, r6, lr}
10103c32:	4b10      	ldr	r3, [pc, #64]	; (10103c74 <rtl_crypto_aes_cbc_init+0x44>)
10103c34:	781b      	ldrb	r3, [r3, #0]
10103c36:	2b01      	cmp	r3, #1
10103c38:	4604      	mov	r4, r0
10103c3a:	460d      	mov	r5, r1
10103c3c:	d003      	beq.n	10103c46 <rtl_crypto_aes_cbc_init+0x16>
10103c3e:	2126      	movs	r1, #38	; 0x26
10103c40:	480d      	ldr	r0, [pc, #52]	; (10103c78 <rtl_crypto_aes_cbc_init+0x48>)
10103c42:	f7fc fe15 	bl	10100870 <io_assert_failed>
10103c46:	b194      	cbz	r4, 10103c6e <rtl_crypto_aes_cbc_init+0x3e>
10103c48:	07a3      	lsls	r3, r4, #30
10103c4a:	d10d      	bne.n	10103c68 <rtl_crypto_aes_cbc_init+0x38>
10103c4c:	2d20      	cmp	r5, #32
10103c4e:	d808      	bhi.n	10103c62 <rtl_crypto_aes_cbc_init+0x32>
10103c50:	4622      	mov	r2, r4
10103c52:	4c0a      	ldr	r4, [pc, #40]	; (10103c7c <rtl_crypto_aes_cbc_init+0x4c>)
10103c54:	462b      	mov	r3, r5
10103c56:	46a4      	mov	ip, r4
10103c58:	2121      	movs	r1, #33	; 0x21
10103c5a:	4806      	ldr	r0, [pc, #24]	; (10103c74 <rtl_crypto_aes_cbc_init+0x44>)
10103c5c:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10103c60:	4760      	bx	ip
10103c62:	f06f 0006 	mvn.w	r0, #6
10103c66:	bd70      	pop	{r4, r5, r6, pc}
10103c68:	f06f 0005 	mvn.w	r0, #5
10103c6c:	bd70      	pop	{r4, r5, r6, pc}
10103c6e:	f06f 0003 	mvn.w	r0, #3
10103c72:	bd70      	pop	{r4, r5, r6, pc}
10103c74:	100003a0 	.word	0x100003a0
10103c78:	101d51fc 	.word	0x101d51fc
10103c7c:	10105799 	.word	0x10105799

10103c80 <rtl_crypto_aes_cbc_encrypt>:
10103c80:	b570      	push	{r4, r5, r6, lr}
10103c82:	b086      	sub	sp, #24
10103c84:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10103c86:	b1d2      	cbz	r2, 10103cbe <rtl_crypto_aes_cbc_encrypt+0x3e>
10103c88:	f012 0503 	ands.w	r5, r2, #3
10103c8c:	d114      	bne.n	10103cb8 <rtl_crypto_aes_cbc_encrypt+0x38>
10103c8e:	2b10      	cmp	r3, #16
10103c90:	d10f      	bne.n	10103cb2 <rtl_crypto_aes_cbc_encrypt+0x32>
10103c92:	b1a0      	cbz	r0, 10103cbe <rtl_crypto_aes_cbc_encrypt+0x3e>
10103c94:	b19e      	cbz	r6, 10103cbe <rtl_crypto_aes_cbc_encrypt+0x3e>
10103c96:	4614      	mov	r4, r2
10103c98:	e88d 0028 	stmia.w	sp, {r3, r5}
10103c9c:	460a      	mov	r2, r1
10103c9e:	4623      	mov	r3, r4
10103ca0:	4601      	mov	r1, r0
10103ca2:	9504      	str	r5, [sp, #16]
10103ca4:	9603      	str	r6, [sp, #12]
10103ca6:	9502      	str	r5, [sp, #8]
10103ca8:	4806      	ldr	r0, [pc, #24]	; (10103cc4 <rtl_crypto_aes_cbc_encrypt+0x44>)
10103caa:	4c07      	ldr	r4, [pc, #28]	; (10103cc8 <rtl_crypto_aes_cbc_encrypt+0x48>)
10103cac:	47a0      	blx	r4
10103cae:	b006      	add	sp, #24
10103cb0:	bd70      	pop	{r4, r5, r6, pc}
10103cb2:	f06f 0008 	mvn.w	r0, #8
10103cb6:	e7fa      	b.n	10103cae <rtl_crypto_aes_cbc_encrypt+0x2e>
10103cb8:	f06f 0005 	mvn.w	r0, #5
10103cbc:	e7f7      	b.n	10103cae <rtl_crypto_aes_cbc_encrypt+0x2e>
10103cbe:	f06f 0003 	mvn.w	r0, #3
10103cc2:	e7f4      	b.n	10103cae <rtl_crypto_aes_cbc_encrypt+0x2e>
10103cc4:	100003a0 	.word	0x100003a0
10103cc8:	101057b9 	.word	0x101057b9

10103ccc <rtl_crypto_aes_cbc_decrypt>:
10103ccc:	b570      	push	{r4, r5, r6, lr}
10103cce:	b086      	sub	sp, #24
10103cd0:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10103cd2:	b1d2      	cbz	r2, 10103d0a <rtl_crypto_aes_cbc_decrypt+0x3e>
10103cd4:	f012 0503 	ands.w	r5, r2, #3
10103cd8:	d114      	bne.n	10103d04 <rtl_crypto_aes_cbc_decrypt+0x38>
10103cda:	2b10      	cmp	r3, #16
10103cdc:	d10f      	bne.n	10103cfe <rtl_crypto_aes_cbc_decrypt+0x32>
10103cde:	b1a0      	cbz	r0, 10103d0a <rtl_crypto_aes_cbc_decrypt+0x3e>
10103ce0:	b19e      	cbz	r6, 10103d0a <rtl_crypto_aes_cbc_decrypt+0x3e>
10103ce2:	4614      	mov	r4, r2
10103ce4:	e88d 0028 	stmia.w	sp, {r3, r5}
10103ce8:	460a      	mov	r2, r1
10103cea:	4623      	mov	r3, r4
10103cec:	4601      	mov	r1, r0
10103cee:	9504      	str	r5, [sp, #16]
10103cf0:	9603      	str	r6, [sp, #12]
10103cf2:	9502      	str	r5, [sp, #8]
10103cf4:	4806      	ldr	r0, [pc, #24]	; (10103d10 <rtl_crypto_aes_cbc_decrypt+0x44>)
10103cf6:	4c07      	ldr	r4, [pc, #28]	; (10103d14 <rtl_crypto_aes_cbc_decrypt+0x48>)
10103cf8:	47a0      	blx	r4
10103cfa:	b006      	add	sp, #24
10103cfc:	bd70      	pop	{r4, r5, r6, pc}
10103cfe:	f06f 0008 	mvn.w	r0, #8
10103d02:	e7fa      	b.n	10103cfa <rtl_crypto_aes_cbc_decrypt+0x2e>
10103d04:	f06f 0005 	mvn.w	r0, #5
10103d08:	e7f7      	b.n	10103cfa <rtl_crypto_aes_cbc_decrypt+0x2e>
10103d0a:	f06f 0003 	mvn.w	r0, #3
10103d0e:	e7f4      	b.n	10103cfa <rtl_crypto_aes_cbc_decrypt+0x2e>
10103d10:	100003a0 	.word	0x100003a0
10103d14:	101057e9 	.word	0x101057e9

10103d18 <rtl_crypto_aes_ecb_init>:
10103d18:	b570      	push	{r4, r5, r6, lr}
10103d1a:	4b10      	ldr	r3, [pc, #64]	; (10103d5c <rtl_crypto_aes_ecb_init+0x44>)
10103d1c:	781b      	ldrb	r3, [r3, #0]
10103d1e:	2b01      	cmp	r3, #1
10103d20:	4604      	mov	r4, r0
10103d22:	460d      	mov	r5, r1
10103d24:	d003      	beq.n	10103d2e <rtl_crypto_aes_ecb_init+0x16>
10103d26:	2171      	movs	r1, #113	; 0x71
10103d28:	480d      	ldr	r0, [pc, #52]	; (10103d60 <rtl_crypto_aes_ecb_init+0x48>)
10103d2a:	f7fc fda1 	bl	10100870 <io_assert_failed>
10103d2e:	b194      	cbz	r4, 10103d56 <rtl_crypto_aes_ecb_init+0x3e>
10103d30:	07a3      	lsls	r3, r4, #30
10103d32:	d10d      	bne.n	10103d50 <rtl_crypto_aes_ecb_init+0x38>
10103d34:	2d20      	cmp	r5, #32
10103d36:	d808      	bhi.n	10103d4a <rtl_crypto_aes_ecb_init+0x32>
10103d38:	4622      	mov	r2, r4
10103d3a:	4c0a      	ldr	r4, [pc, #40]	; (10103d64 <rtl_crypto_aes_ecb_init+0x4c>)
10103d3c:	462b      	mov	r3, r5
10103d3e:	46a4      	mov	ip, r4
10103d40:	2120      	movs	r1, #32
10103d42:	4806      	ldr	r0, [pc, #24]	; (10103d5c <rtl_crypto_aes_ecb_init+0x44>)
10103d44:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10103d48:	4760      	bx	ip
10103d4a:	f06f 0006 	mvn.w	r0, #6
10103d4e:	bd70      	pop	{r4, r5, r6, pc}
10103d50:	f06f 0005 	mvn.w	r0, #5
10103d54:	bd70      	pop	{r4, r5, r6, pc}
10103d56:	f06f 0003 	mvn.w	r0, #3
10103d5a:	bd70      	pop	{r4, r5, r6, pc}
10103d5c:	100003a0 	.word	0x100003a0
10103d60:	101d525c 	.word	0x101d525c
10103d64:	10105799 	.word	0x10105799

10103d68 <rtl_crypto_aes_ecb_encrypt>:
10103d68:	b570      	push	{r4, r5, r6, lr}
10103d6a:	b086      	sub	sp, #24
10103d6c:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10103d6e:	b178      	cbz	r0, 10103d90 <rtl_crypto_aes_ecb_encrypt+0x28>
10103d70:	b176      	cbz	r6, 10103d90 <rtl_crypto_aes_ecb_encrypt+0x28>
10103d72:	461c      	mov	r4, r3
10103d74:	2500      	movs	r5, #0
10103d76:	4613      	mov	r3, r2
10103d78:	9400      	str	r4, [sp, #0]
10103d7a:	460a      	mov	r2, r1
10103d7c:	9603      	str	r6, [sp, #12]
10103d7e:	4601      	mov	r1, r0
10103d80:	9504      	str	r5, [sp, #16]
10103d82:	9502      	str	r5, [sp, #8]
10103d84:	9501      	str	r5, [sp, #4]
10103d86:	4804      	ldr	r0, [pc, #16]	; (10103d98 <rtl_crypto_aes_ecb_encrypt+0x30>)
10103d88:	4c04      	ldr	r4, [pc, #16]	; (10103d9c <rtl_crypto_aes_ecb_encrypt+0x34>)
10103d8a:	47a0      	blx	r4
10103d8c:	b006      	add	sp, #24
10103d8e:	bd70      	pop	{r4, r5, r6, pc}
10103d90:	f06f 0003 	mvn.w	r0, #3
10103d94:	e7fa      	b.n	10103d8c <rtl_crypto_aes_ecb_encrypt+0x24>
10103d96:	bf00      	nop
10103d98:	100003a0 	.word	0x100003a0
10103d9c:	101057b9 	.word	0x101057b9

10103da0 <rtl_crypto_aes_ecb_decrypt>:
10103da0:	b570      	push	{r4, r5, r6, lr}
10103da2:	b086      	sub	sp, #24
10103da4:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10103da6:	b178      	cbz	r0, 10103dc8 <rtl_crypto_aes_ecb_decrypt+0x28>
10103da8:	b176      	cbz	r6, 10103dc8 <rtl_crypto_aes_ecb_decrypt+0x28>
10103daa:	461c      	mov	r4, r3
10103dac:	2500      	movs	r5, #0
10103dae:	4613      	mov	r3, r2
10103db0:	9400      	str	r4, [sp, #0]
10103db2:	460a      	mov	r2, r1
10103db4:	9603      	str	r6, [sp, #12]
10103db6:	4601      	mov	r1, r0
10103db8:	9504      	str	r5, [sp, #16]
10103dba:	9502      	str	r5, [sp, #8]
10103dbc:	9501      	str	r5, [sp, #4]
10103dbe:	4804      	ldr	r0, [pc, #16]	; (10103dd0 <rtl_crypto_aes_ecb_decrypt+0x30>)
10103dc0:	4c04      	ldr	r4, [pc, #16]	; (10103dd4 <rtl_crypto_aes_ecb_decrypt+0x34>)
10103dc2:	47a0      	blx	r4
10103dc4:	b006      	add	sp, #24
10103dc6:	bd70      	pop	{r4, r5, r6, pc}
10103dc8:	f06f 0003 	mvn.w	r0, #3
10103dcc:	e7fa      	b.n	10103dc4 <rtl_crypto_aes_ecb_decrypt+0x24>
10103dce:	bf00      	nop
10103dd0:	100003a0 	.word	0x100003a0
10103dd4:	101057e9 	.word	0x101057e9

10103dd8 <rtl_crypto_aes_ctr_init>:
10103dd8:	b570      	push	{r4, r5, r6, lr}
10103dda:	4b10      	ldr	r3, [pc, #64]	; (10103e1c <rtl_crypto_aes_ctr_init+0x44>)
10103ddc:	781b      	ldrb	r3, [r3, #0]
10103dde:	2b01      	cmp	r3, #1
10103de0:	4604      	mov	r4, r0
10103de2:	460d      	mov	r5, r1
10103de4:	d003      	beq.n	10103dee <rtl_crypto_aes_ctr_init+0x16>
10103de6:	21b6      	movs	r1, #182	; 0xb6
10103de8:	480d      	ldr	r0, [pc, #52]	; (10103e20 <rtl_crypto_aes_ctr_init+0x48>)
10103dea:	f7fc fd41 	bl	10100870 <io_assert_failed>
10103dee:	b194      	cbz	r4, 10103e16 <rtl_crypto_aes_ctr_init+0x3e>
10103df0:	07a3      	lsls	r3, r4, #30
10103df2:	d10d      	bne.n	10103e10 <rtl_crypto_aes_ctr_init+0x38>
10103df4:	2d20      	cmp	r5, #32
10103df6:	d808      	bhi.n	10103e0a <rtl_crypto_aes_ctr_init+0x32>
10103df8:	4622      	mov	r2, r4
10103dfa:	4c0a      	ldr	r4, [pc, #40]	; (10103e24 <rtl_crypto_aes_ctr_init+0x4c>)
10103dfc:	462b      	mov	r3, r5
10103dfe:	46a4      	mov	ip, r4
10103e00:	2124      	movs	r1, #36	; 0x24
10103e02:	4806      	ldr	r0, [pc, #24]	; (10103e1c <rtl_crypto_aes_ctr_init+0x44>)
10103e04:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10103e08:	4760      	bx	ip
10103e0a:	f06f 0006 	mvn.w	r0, #6
10103e0e:	bd70      	pop	{r4, r5, r6, pc}
10103e10:	f06f 0005 	mvn.w	r0, #5
10103e14:	bd70      	pop	{r4, r5, r6, pc}
10103e16:	f06f 0003 	mvn.w	r0, #3
10103e1a:	bd70      	pop	{r4, r5, r6, pc}
10103e1c:	100003a0 	.word	0x100003a0
10103e20:	101d5214 	.word	0x101d5214
10103e24:	10105799 	.word	0x10105799

10103e28 <rtl_crypto_aes_ctr_encrypt>:
10103e28:	b570      	push	{r4, r5, r6, lr}
10103e2a:	b086      	sub	sp, #24
10103e2c:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10103e2e:	b1aa      	cbz	r2, 10103e5c <rtl_crypto_aes_ctr_encrypt+0x34>
10103e30:	f012 0503 	ands.w	r5, r2, #3
10103e34:	d10f      	bne.n	10103e56 <rtl_crypto_aes_ctr_encrypt+0x2e>
10103e36:	b188      	cbz	r0, 10103e5c <rtl_crypto_aes_ctr_encrypt+0x34>
10103e38:	b186      	cbz	r6, 10103e5c <rtl_crypto_aes_ctr_encrypt+0x34>
10103e3a:	4614      	mov	r4, r2
10103e3c:	e88d 0028 	stmia.w	sp, {r3, r5}
10103e40:	460a      	mov	r2, r1
10103e42:	4623      	mov	r3, r4
10103e44:	4601      	mov	r1, r0
10103e46:	9504      	str	r5, [sp, #16]
10103e48:	9603      	str	r6, [sp, #12]
10103e4a:	9502      	str	r5, [sp, #8]
10103e4c:	4805      	ldr	r0, [pc, #20]	; (10103e64 <rtl_crypto_aes_ctr_encrypt+0x3c>)
10103e4e:	4c06      	ldr	r4, [pc, #24]	; (10103e68 <rtl_crypto_aes_ctr_encrypt+0x40>)
10103e50:	47a0      	blx	r4
10103e52:	b006      	add	sp, #24
10103e54:	bd70      	pop	{r4, r5, r6, pc}
10103e56:	f06f 0005 	mvn.w	r0, #5
10103e5a:	e7fa      	b.n	10103e52 <rtl_crypto_aes_ctr_encrypt+0x2a>
10103e5c:	f06f 0003 	mvn.w	r0, #3
10103e60:	e7f7      	b.n	10103e52 <rtl_crypto_aes_ctr_encrypt+0x2a>
10103e62:	bf00      	nop
10103e64:	100003a0 	.word	0x100003a0
10103e68:	101057b9 	.word	0x101057b9

10103e6c <rtl_crypto_aes_ctr_decrypt>:
10103e6c:	b570      	push	{r4, r5, r6, lr}
10103e6e:	b086      	sub	sp, #24
10103e70:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10103e72:	b1aa      	cbz	r2, 10103ea0 <rtl_crypto_aes_ctr_decrypt+0x34>
10103e74:	f012 0503 	ands.w	r5, r2, #3
10103e78:	d10f      	bne.n	10103e9a <rtl_crypto_aes_ctr_decrypt+0x2e>
10103e7a:	b188      	cbz	r0, 10103ea0 <rtl_crypto_aes_ctr_decrypt+0x34>
10103e7c:	b186      	cbz	r6, 10103ea0 <rtl_crypto_aes_ctr_decrypt+0x34>
10103e7e:	4614      	mov	r4, r2
10103e80:	e88d 0028 	stmia.w	sp, {r3, r5}
10103e84:	460a      	mov	r2, r1
10103e86:	4623      	mov	r3, r4
10103e88:	4601      	mov	r1, r0
10103e8a:	9504      	str	r5, [sp, #16]
10103e8c:	9603      	str	r6, [sp, #12]
10103e8e:	9502      	str	r5, [sp, #8]
10103e90:	4805      	ldr	r0, [pc, #20]	; (10103ea8 <rtl_crypto_aes_ctr_decrypt+0x3c>)
10103e92:	4c06      	ldr	r4, [pc, #24]	; (10103eac <rtl_crypto_aes_ctr_decrypt+0x40>)
10103e94:	47a0      	blx	r4
10103e96:	b006      	add	sp, #24
10103e98:	bd70      	pop	{r4, r5, r6, pc}
10103e9a:	f06f 0005 	mvn.w	r0, #5
10103e9e:	e7fa      	b.n	10103e96 <rtl_crypto_aes_ctr_decrypt+0x2a>
10103ea0:	f06f 0003 	mvn.w	r0, #3
10103ea4:	e7f7      	b.n	10103e96 <rtl_crypto_aes_ctr_decrypt+0x2a>
10103ea6:	bf00      	nop
10103ea8:	100003a0 	.word	0x100003a0
10103eac:	101057e9 	.word	0x101057e9

10103eb0 <rtl_crypto_aes_cfb_init>:
10103eb0:	b570      	push	{r4, r5, r6, lr}
10103eb2:	4b10      	ldr	r3, [pc, #64]	; (10103ef4 <rtl_crypto_aes_cfb_init+0x44>)
10103eb4:	781b      	ldrb	r3, [r3, #0]
10103eb6:	2b01      	cmp	r3, #1
10103eb8:	4604      	mov	r4, r0
10103eba:	460d      	mov	r5, r1
10103ebc:	d003      	beq.n	10103ec6 <rtl_crypto_aes_cfb_init+0x16>
10103ebe:	21fe      	movs	r1, #254	; 0xfe
10103ec0:	480d      	ldr	r0, [pc, #52]	; (10103ef8 <rtl_crypto_aes_cfb_init+0x48>)
10103ec2:	f7fc fcd5 	bl	10100870 <io_assert_failed>
10103ec6:	b194      	cbz	r4, 10103eee <rtl_crypto_aes_cfb_init+0x3e>
10103ec8:	07a3      	lsls	r3, r4, #30
10103eca:	d10d      	bne.n	10103ee8 <rtl_crypto_aes_cfb_init+0x38>
10103ecc:	2d20      	cmp	r5, #32
10103ece:	d808      	bhi.n	10103ee2 <rtl_crypto_aes_cfb_init+0x32>
10103ed0:	4622      	mov	r2, r4
10103ed2:	4c0a      	ldr	r4, [pc, #40]	; (10103efc <rtl_crypto_aes_cfb_init+0x4c>)
10103ed4:	462b      	mov	r3, r5
10103ed6:	46a4      	mov	ip, r4
10103ed8:	2122      	movs	r1, #34	; 0x22
10103eda:	4806      	ldr	r0, [pc, #24]	; (10103ef4 <rtl_crypto_aes_cfb_init+0x44>)
10103edc:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10103ee0:	4760      	bx	ip
10103ee2:	f06f 0006 	mvn.w	r0, #6
10103ee6:	bd70      	pop	{r4, r5, r6, pc}
10103ee8:	f06f 0005 	mvn.w	r0, #5
10103eec:	bd70      	pop	{r4, r5, r6, pc}
10103eee:	f06f 0003 	mvn.w	r0, #3
10103ef2:	bd70      	pop	{r4, r5, r6, pc}
10103ef4:	100003a0 	.word	0x100003a0
10103ef8:	101d5274 	.word	0x101d5274
10103efc:	10105799 	.word	0x10105799

10103f00 <rtl_crypto_aes_cfb_encrypt>:
10103f00:	b570      	push	{r4, r5, r6, lr}
10103f02:	b086      	sub	sp, #24
10103f04:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10103f06:	b1aa      	cbz	r2, 10103f34 <rtl_crypto_aes_cfb_encrypt+0x34>
10103f08:	f012 0503 	ands.w	r5, r2, #3
10103f0c:	d10f      	bne.n	10103f2e <rtl_crypto_aes_cfb_encrypt+0x2e>
10103f0e:	b188      	cbz	r0, 10103f34 <rtl_crypto_aes_cfb_encrypt+0x34>
10103f10:	b186      	cbz	r6, 10103f34 <rtl_crypto_aes_cfb_encrypt+0x34>
10103f12:	4614      	mov	r4, r2
10103f14:	e88d 0028 	stmia.w	sp, {r3, r5}
10103f18:	460a      	mov	r2, r1
10103f1a:	4623      	mov	r3, r4
10103f1c:	4601      	mov	r1, r0
10103f1e:	9504      	str	r5, [sp, #16]
10103f20:	9603      	str	r6, [sp, #12]
10103f22:	9502      	str	r5, [sp, #8]
10103f24:	4805      	ldr	r0, [pc, #20]	; (10103f3c <rtl_crypto_aes_cfb_encrypt+0x3c>)
10103f26:	4c06      	ldr	r4, [pc, #24]	; (10103f40 <rtl_crypto_aes_cfb_encrypt+0x40>)
10103f28:	47a0      	blx	r4
10103f2a:	b006      	add	sp, #24
10103f2c:	bd70      	pop	{r4, r5, r6, pc}
10103f2e:	f06f 0005 	mvn.w	r0, #5
10103f32:	e7fa      	b.n	10103f2a <rtl_crypto_aes_cfb_encrypt+0x2a>
10103f34:	f06f 0003 	mvn.w	r0, #3
10103f38:	e7f7      	b.n	10103f2a <rtl_crypto_aes_cfb_encrypt+0x2a>
10103f3a:	bf00      	nop
10103f3c:	100003a0 	.word	0x100003a0
10103f40:	101057b9 	.word	0x101057b9

10103f44 <rtl_crypto_aes_cfb_decrypt>:
10103f44:	b570      	push	{r4, r5, r6, lr}
10103f46:	b086      	sub	sp, #24
10103f48:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10103f4a:	b1aa      	cbz	r2, 10103f78 <rtl_crypto_aes_cfb_decrypt+0x34>
10103f4c:	f012 0503 	ands.w	r5, r2, #3
10103f50:	d10f      	bne.n	10103f72 <rtl_crypto_aes_cfb_decrypt+0x2e>
10103f52:	b188      	cbz	r0, 10103f78 <rtl_crypto_aes_cfb_decrypt+0x34>
10103f54:	b186      	cbz	r6, 10103f78 <rtl_crypto_aes_cfb_decrypt+0x34>
10103f56:	4614      	mov	r4, r2
10103f58:	e88d 0028 	stmia.w	sp, {r3, r5}
10103f5c:	460a      	mov	r2, r1
10103f5e:	4623      	mov	r3, r4
10103f60:	4601      	mov	r1, r0
10103f62:	9504      	str	r5, [sp, #16]
10103f64:	9603      	str	r6, [sp, #12]
10103f66:	9502      	str	r5, [sp, #8]
10103f68:	4805      	ldr	r0, [pc, #20]	; (10103f80 <rtl_crypto_aes_cfb_decrypt+0x3c>)
10103f6a:	4c06      	ldr	r4, [pc, #24]	; (10103f84 <rtl_crypto_aes_cfb_decrypt+0x40>)
10103f6c:	47a0      	blx	r4
10103f6e:	b006      	add	sp, #24
10103f70:	bd70      	pop	{r4, r5, r6, pc}
10103f72:	f06f 0005 	mvn.w	r0, #5
10103f76:	e7fa      	b.n	10103f6e <rtl_crypto_aes_cfb_decrypt+0x2a>
10103f78:	f06f 0003 	mvn.w	r0, #3
10103f7c:	e7f7      	b.n	10103f6e <rtl_crypto_aes_cfb_decrypt+0x2a>
10103f7e:	bf00      	nop
10103f80:	100003a0 	.word	0x100003a0
10103f84:	101057e9 	.word	0x101057e9

10103f88 <rtl_crypto_aes_ofb_init>:
10103f88:	b570      	push	{r4, r5, r6, lr}
10103f8a:	4b11      	ldr	r3, [pc, #68]	; (10103fd0 <rtl_crypto_aes_ofb_init+0x48>)
10103f8c:	781b      	ldrb	r3, [r3, #0]
10103f8e:	2b01      	cmp	r3, #1
10103f90:	4604      	mov	r4, r0
10103f92:	460d      	mov	r5, r1
10103f94:	d004      	beq.n	10103fa0 <rtl_crypto_aes_ofb_init+0x18>
10103f96:	f44f 71a3 	mov.w	r1, #326	; 0x146
10103f9a:	480e      	ldr	r0, [pc, #56]	; (10103fd4 <rtl_crypto_aes_ofb_init+0x4c>)
10103f9c:	f7fc fc68 	bl	10100870 <io_assert_failed>
10103fa0:	b194      	cbz	r4, 10103fc8 <rtl_crypto_aes_ofb_init+0x40>
10103fa2:	07a3      	lsls	r3, r4, #30
10103fa4:	d10d      	bne.n	10103fc2 <rtl_crypto_aes_ofb_init+0x3a>
10103fa6:	2d20      	cmp	r5, #32
10103fa8:	d808      	bhi.n	10103fbc <rtl_crypto_aes_ofb_init+0x34>
10103faa:	4622      	mov	r2, r4
10103fac:	4c0a      	ldr	r4, [pc, #40]	; (10103fd8 <rtl_crypto_aes_ofb_init+0x50>)
10103fae:	462b      	mov	r3, r5
10103fb0:	46a4      	mov	ip, r4
10103fb2:	2123      	movs	r1, #35	; 0x23
10103fb4:	4806      	ldr	r0, [pc, #24]	; (10103fd0 <rtl_crypto_aes_ofb_init+0x48>)
10103fb6:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10103fba:	4760      	bx	ip
10103fbc:	f06f 0006 	mvn.w	r0, #6
10103fc0:	bd70      	pop	{r4, r5, r6, pc}
10103fc2:	f06f 0005 	mvn.w	r0, #5
10103fc6:	bd70      	pop	{r4, r5, r6, pc}
10103fc8:	f06f 0003 	mvn.w	r0, #3
10103fcc:	bd70      	pop	{r4, r5, r6, pc}
10103fce:	bf00      	nop
10103fd0:	100003a0 	.word	0x100003a0
10103fd4:	101d522c 	.word	0x101d522c
10103fd8:	10105799 	.word	0x10105799

10103fdc <rtl_crypto_aes_ofb_encrypt>:
10103fdc:	b570      	push	{r4, r5, r6, lr}
10103fde:	b086      	sub	sp, #24
10103fe0:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10103fe2:	b1aa      	cbz	r2, 10104010 <rtl_crypto_aes_ofb_encrypt+0x34>
10103fe4:	f012 0503 	ands.w	r5, r2, #3
10103fe8:	d10f      	bne.n	1010400a <rtl_crypto_aes_ofb_encrypt+0x2e>
10103fea:	b188      	cbz	r0, 10104010 <rtl_crypto_aes_ofb_encrypt+0x34>
10103fec:	b186      	cbz	r6, 10104010 <rtl_crypto_aes_ofb_encrypt+0x34>
10103fee:	4614      	mov	r4, r2
10103ff0:	e88d 0028 	stmia.w	sp, {r3, r5}
10103ff4:	460a      	mov	r2, r1
10103ff6:	4623      	mov	r3, r4
10103ff8:	4601      	mov	r1, r0
10103ffa:	9504      	str	r5, [sp, #16]
10103ffc:	9603      	str	r6, [sp, #12]
10103ffe:	9502      	str	r5, [sp, #8]
10104000:	4805      	ldr	r0, [pc, #20]	; (10104018 <rtl_crypto_aes_ofb_encrypt+0x3c>)
10104002:	4c06      	ldr	r4, [pc, #24]	; (1010401c <rtl_crypto_aes_ofb_encrypt+0x40>)
10104004:	47a0      	blx	r4
10104006:	b006      	add	sp, #24
10104008:	bd70      	pop	{r4, r5, r6, pc}
1010400a:	f06f 0005 	mvn.w	r0, #5
1010400e:	e7fa      	b.n	10104006 <rtl_crypto_aes_ofb_encrypt+0x2a>
10104010:	f06f 0003 	mvn.w	r0, #3
10104014:	e7f7      	b.n	10104006 <rtl_crypto_aes_ofb_encrypt+0x2a>
10104016:	bf00      	nop
10104018:	100003a0 	.word	0x100003a0
1010401c:	101057b9 	.word	0x101057b9

10104020 <rtl_crypto_aes_ofb_decrypt>:
10104020:	b570      	push	{r4, r5, r6, lr}
10104022:	b086      	sub	sp, #24
10104024:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10104026:	b1aa      	cbz	r2, 10104054 <rtl_crypto_aes_ofb_decrypt+0x34>
10104028:	f012 0503 	ands.w	r5, r2, #3
1010402c:	d10f      	bne.n	1010404e <rtl_crypto_aes_ofb_decrypt+0x2e>
1010402e:	b188      	cbz	r0, 10104054 <rtl_crypto_aes_ofb_decrypt+0x34>
10104030:	b186      	cbz	r6, 10104054 <rtl_crypto_aes_ofb_decrypt+0x34>
10104032:	4614      	mov	r4, r2
10104034:	e88d 0028 	stmia.w	sp, {r3, r5}
10104038:	460a      	mov	r2, r1
1010403a:	4623      	mov	r3, r4
1010403c:	4601      	mov	r1, r0
1010403e:	9504      	str	r5, [sp, #16]
10104040:	9603      	str	r6, [sp, #12]
10104042:	9502      	str	r5, [sp, #8]
10104044:	4805      	ldr	r0, [pc, #20]	; (1010405c <rtl_crypto_aes_ofb_decrypt+0x3c>)
10104046:	4c06      	ldr	r4, [pc, #24]	; (10104060 <rtl_crypto_aes_ofb_decrypt+0x40>)
10104048:	47a0      	blx	r4
1010404a:	b006      	add	sp, #24
1010404c:	bd70      	pop	{r4, r5, r6, pc}
1010404e:	f06f 0005 	mvn.w	r0, #5
10104052:	e7fa      	b.n	1010404a <rtl_crypto_aes_ofb_decrypt+0x2a>
10104054:	f06f 0003 	mvn.w	r0, #3
10104058:	e7f7      	b.n	1010404a <rtl_crypto_aes_ofb_decrypt+0x2a>
1010405a:	bf00      	nop
1010405c:	100003a0 	.word	0x100003a0
10104060:	101057e9 	.word	0x101057e9

10104064 <rtl_crypto_aes_gcm_init>:
10104064:	b570      	push	{r4, r5, r6, lr}
10104066:	4b11      	ldr	r3, [pc, #68]	; (101040ac <rtl_crypto_aes_gcm_init+0x48>)
10104068:	781b      	ldrb	r3, [r3, #0]
1010406a:	2b01      	cmp	r3, #1
1010406c:	4604      	mov	r4, r0
1010406e:	460d      	mov	r5, r1
10104070:	d004      	beq.n	1010407c <rtl_crypto_aes_gcm_init+0x18>
10104072:	f44f 71c7 	mov.w	r1, #398	; 0x18e
10104076:	480e      	ldr	r0, [pc, #56]	; (101040b0 <rtl_crypto_aes_gcm_init+0x4c>)
10104078:	f7fc fbfa 	bl	10100870 <io_assert_failed>
1010407c:	b194      	cbz	r4, 101040a4 <rtl_crypto_aes_gcm_init+0x40>
1010407e:	07a3      	lsls	r3, r4, #30
10104080:	d10d      	bne.n	1010409e <rtl_crypto_aes_gcm_init+0x3a>
10104082:	2d20      	cmp	r5, #32
10104084:	d808      	bhi.n	10104098 <rtl_crypto_aes_gcm_init+0x34>
10104086:	4622      	mov	r2, r4
10104088:	4c0a      	ldr	r4, [pc, #40]	; (101040b4 <rtl_crypto_aes_gcm_init+0x50>)
1010408a:	462b      	mov	r3, r5
1010408c:	46a4      	mov	ip, r4
1010408e:	2128      	movs	r1, #40	; 0x28
10104090:	4806      	ldr	r0, [pc, #24]	; (101040ac <rtl_crypto_aes_gcm_init+0x48>)
10104092:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10104096:	4760      	bx	ip
10104098:	f06f 0006 	mvn.w	r0, #6
1010409c:	bd70      	pop	{r4, r5, r6, pc}
1010409e:	f06f 0005 	mvn.w	r0, #5
101040a2:	bd70      	pop	{r4, r5, r6, pc}
101040a4:	f06f 0003 	mvn.w	r0, #3
101040a8:	bd70      	pop	{r4, r5, r6, pc}
101040aa:	bf00      	nop
101040ac:	100003a0 	.word	0x100003a0
101040b0:	101d5244 	.word	0x101d5244
101040b4:	10105799 	.word	0x10105799

101040b8 <rtl_crypto_aes_gcm_encrypt>:
101040b8:	e92d 43f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
101040bc:	b087      	sub	sp, #28
101040be:	ae0f      	add	r6, sp, #60	; 0x3c
101040c0:	cec0      	ldmia	r6, {r6, r7}
101040c2:	b33a      	cbz	r2, 10104114 <rtl_crypto_aes_gcm_encrypt+0x5c>
101040c4:	0795      	lsls	r5, r2, #30
101040c6:	d122      	bne.n	1010410e <rtl_crypto_aes_gcm_encrypt+0x56>
101040c8:	b320      	cbz	r0, 10104114 <rtl_crypto_aes_gcm_encrypt+0x5c>
101040ca:	079c      	lsls	r4, r3, #30
101040cc:	d11f      	bne.n	1010410e <rtl_crypto_aes_gcm_encrypt+0x56>
101040ce:	b30e      	cbz	r6, 10104114 <rtl_crypto_aes_gcm_encrypt+0x5c>
101040d0:	b307      	cbz	r7, 10104114 <rtl_crypto_aes_gcm_encrypt+0x5c>
101040d2:	4604      	mov	r4, r0
101040d4:	4689      	mov	r9, r1
101040d6:	f8df 8054 	ldr.w	r8, [pc, #84]	; 1010412c <rtl_crypto_aes_gcm_encrypt+0x74>
101040da:	4611      	mov	r1, r2
101040dc:	480f      	ldr	r0, [pc, #60]	; (1010411c <rtl_crypto_aes_gcm_encrypt+0x64>)
101040de:	220c      	movs	r2, #12
101040e0:	461d      	mov	r5, r3
101040e2:	47c0      	blx	r8
101040e4:	2204      	movs	r2, #4
101040e6:	490e      	ldr	r1, [pc, #56]	; (10104120 <rtl_crypto_aes_gcm_encrypt+0x68>)
101040e8:	480e      	ldr	r0, [pc, #56]	; (10104124 <rtl_crypto_aes_gcm_encrypt+0x6c>)
101040ea:	47c0      	blx	r8
101040ec:	2010      	movs	r0, #16
101040ee:	9a0e      	ldr	r2, [sp, #56]	; 0x38
101040f0:	4b0a      	ldr	r3, [pc, #40]	; (1010411c <rtl_crypto_aes_gcm_encrypt+0x64>)
101040f2:	9202      	str	r2, [sp, #8]
101040f4:	4621      	mov	r1, r4
101040f6:	9000      	str	r0, [sp, #0]
101040f8:	9704      	str	r7, [sp, #16]
101040fa:	9603      	str	r6, [sp, #12]
101040fc:	9501      	str	r5, [sp, #4]
101040fe:	464a      	mov	r2, r9
10104100:	f1a3 00ec 	sub.w	r0, r3, #236	; 0xec
10104104:	4c08      	ldr	r4, [pc, #32]	; (10104128 <rtl_crypto_aes_gcm_encrypt+0x70>)
10104106:	47a0      	blx	r4
10104108:	b007      	add	sp, #28
1010410a:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
1010410e:	f06f 0005 	mvn.w	r0, #5
10104112:	e7f9      	b.n	10104108 <rtl_crypto_aes_gcm_encrypt+0x50>
10104114:	f06f 0003 	mvn.w	r0, #3
10104118:	e7f6      	b.n	10104108 <rtl_crypto_aes_gcm_encrypt+0x50>
1010411a:	bf00      	nop
1010411c:	1000048c 	.word	0x1000048c
10104120:	101d4040 	.word	0x101d4040
10104124:	10000498 	.word	0x10000498
10104128:	101057b9 	.word	0x101057b9
1010412c:	10106d15 	.word	0x10106d15

10104130 <rtl_crypto_aes_gcm_decrypt>:
10104130:	e92d 43f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
10104134:	b087      	sub	sp, #28
10104136:	ae0f      	add	r6, sp, #60	; 0x3c
10104138:	cec0      	ldmia	r6, {r6, r7}
1010413a:	b33a      	cbz	r2, 1010418c <rtl_crypto_aes_gcm_decrypt+0x5c>
1010413c:	0795      	lsls	r5, r2, #30
1010413e:	d122      	bne.n	10104186 <rtl_crypto_aes_gcm_decrypt+0x56>
10104140:	b320      	cbz	r0, 1010418c <rtl_crypto_aes_gcm_decrypt+0x5c>
10104142:	079c      	lsls	r4, r3, #30
10104144:	d11f      	bne.n	10104186 <rtl_crypto_aes_gcm_decrypt+0x56>
10104146:	b30e      	cbz	r6, 1010418c <rtl_crypto_aes_gcm_decrypt+0x5c>
10104148:	b307      	cbz	r7, 1010418c <rtl_crypto_aes_gcm_decrypt+0x5c>
1010414a:	4604      	mov	r4, r0
1010414c:	4689      	mov	r9, r1
1010414e:	f8df 8054 	ldr.w	r8, [pc, #84]	; 101041a4 <rtl_crypto_aes_gcm_decrypt+0x74>
10104152:	4611      	mov	r1, r2
10104154:	480f      	ldr	r0, [pc, #60]	; (10104194 <rtl_crypto_aes_gcm_decrypt+0x64>)
10104156:	220c      	movs	r2, #12
10104158:	461d      	mov	r5, r3
1010415a:	47c0      	blx	r8
1010415c:	2204      	movs	r2, #4
1010415e:	490e      	ldr	r1, [pc, #56]	; (10104198 <rtl_crypto_aes_gcm_decrypt+0x68>)
10104160:	480e      	ldr	r0, [pc, #56]	; (1010419c <rtl_crypto_aes_gcm_decrypt+0x6c>)
10104162:	47c0      	blx	r8
10104164:	2010      	movs	r0, #16
10104166:	9a0e      	ldr	r2, [sp, #56]	; 0x38
10104168:	4b0a      	ldr	r3, [pc, #40]	; (10104194 <rtl_crypto_aes_gcm_decrypt+0x64>)
1010416a:	9202      	str	r2, [sp, #8]
1010416c:	4621      	mov	r1, r4
1010416e:	9000      	str	r0, [sp, #0]
10104170:	9704      	str	r7, [sp, #16]
10104172:	9603      	str	r6, [sp, #12]
10104174:	9501      	str	r5, [sp, #4]
10104176:	464a      	mov	r2, r9
10104178:	f1a3 00ec 	sub.w	r0, r3, #236	; 0xec
1010417c:	4c08      	ldr	r4, [pc, #32]	; (101041a0 <rtl_crypto_aes_gcm_decrypt+0x70>)
1010417e:	47a0      	blx	r4
10104180:	b007      	add	sp, #28
10104182:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
10104186:	f06f 0005 	mvn.w	r0, #5
1010418a:	e7f9      	b.n	10104180 <rtl_crypto_aes_gcm_decrypt+0x50>
1010418c:	f06f 0003 	mvn.w	r0, #3
10104190:	e7f6      	b.n	10104180 <rtl_crypto_aes_gcm_decrypt+0x50>
10104192:	bf00      	nop
10104194:	1000048c 	.word	0x1000048c
10104198:	101d4040 	.word	0x101d4040
1010419c:	10000498 	.word	0x10000498
101041a0:	101057e9 	.word	0x101057e9
101041a4:	10106d15 	.word	0x10106d15

101041a8 <BOOT_ROM_SignatureCheck>:
101041a8:	4a2a      	ldr	r2, [pc, #168]	; (10104254 <BOOT_ROM_SignatureCheck+0xac>)
101041aa:	4b2b      	ldr	r3, [pc, #172]	; (10104258 <BOOT_ROM_SignatureCheck+0xb0>)
101041ac:	6891      	ldr	r1, [r2, #8]
101041ae:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
101041b2:	482a      	ldr	r0, [pc, #168]	; (1010425c <BOOT_ROM_SignatureCheck+0xb4>)
101041b4:	440b      	add	r3, r1
101041b6:	689c      	ldr	r4, [r3, #8]
101041b8:	6803      	ldr	r3, [r0, #0]
101041ba:	049d      	lsls	r5, r3, #18
101041bc:	b08a      	sub	sp, #40	; 0x28
101041be:	440c      	add	r4, r1
101041c0:	6916      	ldr	r6, [r2, #16]
101041c2:	d50a      	bpl.n	101041da <BOOT_ROM_SignatureCheck+0x32>
101041c4:	4b26      	ldr	r3, [pc, #152]	; (10104260 <BOOT_ROM_SignatureCheck+0xb8>)
101041c6:	681b      	ldr	r3, [r3, #0]
101041c8:	0398      	lsls	r0, r3, #14
101041ca:	d502      	bpl.n	101041d2 <BOOT_ROM_SignatureCheck+0x2a>
101041cc:	4825      	ldr	r0, [pc, #148]	; (10104264 <BOOT_ROM_SignatureCheck+0xbc>)
101041ce:	f7fc f911 	bl	101003f4 <DiagPrintf>
101041d2:	2001      	movs	r0, #1
101041d4:	b00a      	add	sp, #40	; 0x28
101041d6:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
101041da:	1c71      	adds	r1, r6, #1
101041dc:	d02c      	beq.n	10104238 <BOOT_ROM_SignatureCheck+0x90>
101041de:	f44f 75d0 	mov.w	r5, #416	; 0x1a0
101041e2:	f8df 8098 	ldr.w	r8, [pc, #152]	; 1010427c <BOOT_ROM_SignatureCheck+0xd4>
101041e6:	3420      	adds	r4, #32
101041e8:	af02      	add	r7, sp, #8
101041ea:	f5a5 72d0 	sub.w	r2, r5, #416	; 0x1a0
101041ee:	4629      	mov	r1, r5
101041f0:	443a      	add	r2, r7
101041f2:	2307      	movs	r3, #7
101041f4:	2000      	movs	r0, #0
101041f6:	3501      	adds	r5, #1
101041f8:	47c0      	blx	r8
101041fa:	f5b5 7fe0 	cmp.w	r5, #448	; 0x1c0
101041fe:	d1f4      	bne.n	101041ea <BOOT_ROM_SignatureCheck+0x42>
10104200:	4b19      	ldr	r3, [pc, #100]	; (10104268 <BOOT_ROM_SignatureCheck+0xc0>)
10104202:	9700      	str	r7, [sp, #0]
10104204:	4622      	mov	r2, r4
10104206:	f106 0030 	add.w	r0, r6, #48	; 0x30
1010420a:	681c      	ldr	r4, [r3, #0]
1010420c:	4912      	ldr	r1, [pc, #72]	; (10104258 <BOOT_ROM_SignatureCheck+0xb0>)
1010420e:	2300      	movs	r3, #0
10104210:	47a0      	blx	r4
10104212:	b960      	cbnz	r0, 1010422e <BOOT_ROM_SignatureCheck+0x86>
10104214:	4b12      	ldr	r3, [pc, #72]	; (10104260 <BOOT_ROM_SignatureCheck+0xb8>)
10104216:	681b      	ldr	r3, [r3, #0]
10104218:	039a      	lsls	r2, r3, #14
1010421a:	d502      	bpl.n	10104222 <BOOT_ROM_SignatureCheck+0x7a>
1010421c:	4813      	ldr	r0, [pc, #76]	; (1010426c <BOOT_ROM_SignatureCheck+0xc4>)
1010421e:	f7fc f8e9 	bl	101003f4 <DiagPrintf>
10104222:	4a13      	ldr	r2, [pc, #76]	; (10104270 <BOOT_ROM_SignatureCheck+0xc8>)
10104224:	6813      	ldr	r3, [r2, #0]
10104226:	f043 0301 	orr.w	r3, r3, #1
1010422a:	6013      	str	r3, [r2, #0]
1010422c:	e7d1      	b.n	101041d2 <BOOT_ROM_SignatureCheck+0x2a>
1010422e:	4a10      	ldr	r2, [pc, #64]	; (10104270 <BOOT_ROM_SignatureCheck+0xc8>)
10104230:	6813      	ldr	r3, [r2, #0]
10104232:	f023 0301 	bic.w	r3, r3, #1
10104236:	6013      	str	r3, [r2, #0]
10104238:	4d09      	ldr	r5, [pc, #36]	; (10104260 <BOOT_ROM_SignatureCheck+0xb8>)
1010423a:	4c0e      	ldr	r4, [pc, #56]	; (10104274 <BOOT_ROM_SignatureCheck+0xcc>)
1010423c:	4e0e      	ldr	r6, [pc, #56]	; (10104278 <BOOT_ROM_SignatureCheck+0xd0>)
1010423e:	f44f 707a 	mov.w	r0, #1000	; 0x3e8
10104242:	47a0      	blx	r4
10104244:	682b      	ldr	r3, [r5, #0]
10104246:	039b      	lsls	r3, r3, #14
10104248:	d5f9      	bpl.n	1010423e <BOOT_ROM_SignatureCheck+0x96>
1010424a:	4630      	mov	r0, r6
1010424c:	f7fc f8d2 	bl	101003f4 <DiagPrintf>
10104250:	e7f5      	b.n	1010423e <BOOT_ROM_SignatureCheck+0x96>
10104252:	bf00      	nop
10104254:	08004000 	.word	0x08004000
10104258:	08004020 	.word	0x08004020
1010425c:	480003e0 	.word	0x480003e0
10104260:	1000000c 	.word	0x1000000c
10104264:	101d45c0 	.word	0x101d45c0
10104268:	101c0000 	.word	0x101c0000
1010426c:	101d45d4 	.word	0x101d45d4
10104270:	50000800 	.word	0x50000800
10104274:	10100995 	.word	0x10100995
10104278:	101d45e4 	.word	0x101d45e4
1010427c:	10100a31 	.word	0x10100a31

10104280 <BOOT_ROM_FromFlash>:
10104280:	4a34      	ldr	r2, [pc, #208]	; (10104354 <BOOT_ROM_FromFlash+0xd4>)
10104282:	6893      	ldr	r3, [r2, #8]
10104284:	1c58      	adds	r0, r3, #1
10104286:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
1010428a:	d03d      	beq.n	10104308 <BOOT_ROM_FromFlash+0x88>
1010428c:	68d2      	ldr	r2, [r2, #12]
1010428e:	3201      	adds	r2, #1
10104290:	4c31      	ldr	r4, [pc, #196]	; (10104358 <BOOT_ROM_FromFlash+0xd8>)
10104292:	d047      	beq.n	10104324 <BOOT_ROM_FromFlash+0xa4>
10104294:	4e31      	ldr	r6, [pc, #196]	; (1010435c <BOOT_ROM_FromFlash+0xdc>)
10104296:	6822      	ldr	r2, [r4, #0]
10104298:	441e      	add	r6, r3
1010429a:	0392      	lsls	r2, r2, #14
1010429c:	f8d6 8008 	ldr.w	r8, [r6, #8]
101042a0:	68f7      	ldr	r7, [r6, #12]
101042a2:	d450      	bmi.n	10104346 <BOOT_ROM_FromFlash+0xc6>
101042a4:	4d2e      	ldr	r5, [pc, #184]	; (10104360 <BOOT_ROM_FromFlash+0xe0>)
101042a6:	4b2f      	ldr	r3, [pc, #188]	; (10104364 <BOOT_ROM_FromFlash+0xe4>)
101042a8:	4642      	mov	r2, r8
101042aa:	f106 0120 	add.w	r1, r6, #32
101042ae:	4638      	mov	r0, r7
101042b0:	4798      	blx	r3
101042b2:	f895 3020 	ldrb.w	r3, [r5, #32]
101042b6:	2b23      	cmp	r3, #35	; 0x23
101042b8:	d113      	bne.n	101042e2 <BOOT_ROM_FromFlash+0x62>
101042ba:	2379      	movs	r3, #121	; 0x79
101042bc:	492a      	ldr	r1, [pc, #168]	; (10104368 <BOOT_ROM_FromFlash+0xe8>)
101042be:	f105 0220 	add.w	r2, r5, #32
101042c2:	f812 0f01 	ldrb.w	r0, [r2, #1]!
101042c6:	4298      	cmp	r0, r3
101042c8:	d10b      	bne.n	101042e2 <BOOT_ROM_FromFlash+0x62>
101042ca:	f811 3f01 	ldrb.w	r3, [r1, #1]!
101042ce:	2bff      	cmp	r3, #255	; 0xff
101042d0:	d1f7      	bne.n	101042c2 <BOOT_ROM_FromFlash+0x42>
101042d2:	6823      	ldr	r3, [r4, #0]
101042d4:	039b      	lsls	r3, r3, #14
101042d6:	d430      	bmi.n	1010433a <BOOT_ROM_FromFlash+0xba>
101042d8:	696b      	ldr	r3, [r5, #20]
101042da:	b363      	cbz	r3, 10104336 <BOOT_ROM_FromFlash+0xb6>
101042dc:	e8bd 41f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, lr}
101042e0:	4718      	bx	r3
101042e2:	6823      	ldr	r3, [r4, #0]
101042e4:	f413 3300 	ands.w	r3, r3, #131072	; 0x20000
101042e8:	d11e      	bne.n	10104328 <BOOT_ROM_FromFlash+0xa8>
101042ea:	4d20      	ldr	r5, [pc, #128]	; (1010436c <BOOT_ROM_FromFlash+0xec>)
101042ec:	4f20      	ldr	r7, [pc, #128]	; (10104370 <BOOT_ROM_FromFlash+0xf0>)
101042ee:	4e21      	ldr	r6, [pc, #132]	; (10104374 <BOOT_ROM_FromFlash+0xf4>)
101042f0:	b933      	cbnz	r3, 10104300 <BOOT_ROM_FromFlash+0x80>
101042f2:	4630      	mov	r0, r6
101042f4:	47a8      	blx	r5
101042f6:	6823      	ldr	r3, [r4, #0]
101042f8:	f403 3300 	and.w	r3, r3, #131072	; 0x20000
101042fc:	2b00      	cmp	r3, #0
101042fe:	d0f8      	beq.n	101042f2 <BOOT_ROM_FromFlash+0x72>
10104300:	4638      	mov	r0, r7
10104302:	f7fc f877 	bl	101003f4 <DiagPrintf>
10104306:	e7f4      	b.n	101042f2 <BOOT_ROM_FromFlash+0x72>
10104308:	4c13      	ldr	r4, [pc, #76]	; (10104358 <BOOT_ROM_FromFlash+0xd8>)
1010430a:	4d18      	ldr	r5, [pc, #96]	; (1010436c <BOOT_ROM_FromFlash+0xec>)
1010430c:	4f1a      	ldr	r7, [pc, #104]	; (10104378 <BOOT_ROM_FromFlash+0xf8>)
1010430e:	4e19      	ldr	r6, [pc, #100]	; (10104374 <BOOT_ROM_FromFlash+0xf4>)
10104310:	e001      	b.n	10104316 <BOOT_ROM_FromFlash+0x96>
10104312:	4630      	mov	r0, r6
10104314:	47a8      	blx	r5
10104316:	6823      	ldr	r3, [r4, #0]
10104318:	0399      	lsls	r1, r3, #14
1010431a:	d5fa      	bpl.n	10104312 <BOOT_ROM_FromFlash+0x92>
1010431c:	4638      	mov	r0, r7
1010431e:	f7fc f869 	bl	101003f4 <DiagPrintf>
10104322:	e7f6      	b.n	10104312 <BOOT_ROM_FromFlash+0x92>
10104324:	4d11      	ldr	r5, [pc, #68]	; (1010436c <BOOT_ROM_FromFlash+0xec>)
10104326:	e7f1      	b.n	1010430c <BOOT_ROM_FromFlash+0x8c>
10104328:	4814      	ldr	r0, [pc, #80]	; (1010437c <BOOT_ROM_FromFlash+0xfc>)
1010432a:	f7fc f863 	bl	101003f4 <DiagPrintf>
1010432e:	6823      	ldr	r3, [r4, #0]
10104330:	f403 3300 	and.w	r3, r3, #131072	; 0x20000
10104334:	e7d9      	b.n	101042ea <BOOT_ROM_FromFlash+0x6a>
10104336:	682b      	ldr	r3, [r5, #0]
10104338:	e7d0      	b.n	101042dc <BOOT_ROM_FromFlash+0x5c>
1010433a:	682a      	ldr	r2, [r5, #0]
1010433c:	6969      	ldr	r1, [r5, #20]
1010433e:	4810      	ldr	r0, [pc, #64]	; (10104380 <BOOT_ROM_FromFlash+0x100>)
10104340:	f7fc f858 	bl	101003f4 <DiagPrintf>
10104344:	e7c8      	b.n	101042d8 <BOOT_ROM_FromFlash+0x58>
10104346:	4b0f      	ldr	r3, [pc, #60]	; (10104384 <BOOT_ROM_FromFlash+0x104>)
10104348:	463a      	mov	r2, r7
1010434a:	4641      	mov	r1, r8
1010434c:	480e      	ldr	r0, [pc, #56]	; (10104388 <BOOT_ROM_FromFlash+0x108>)
1010434e:	f7fc f851 	bl	101003f4 <DiagPrintf>
10104352:	e7a7      	b.n	101042a4 <BOOT_ROM_FromFlash+0x24>
10104354:	08004000 	.word	0x08004000
10104358:	1000000c 	.word	0x1000000c
1010435c:	08004020 	.word	0x08004020
10104360:	1007d000 	.word	0x1007d000
10104364:	10106d15 	.word	0x10106d15
10104368:	101d4045 	.word	0x101d4045
1010436c:	10100995 	.word	0x10100995
10104370:	101d464c 	.word	0x101d464c
10104374:	000186a0 	.word	0x000186a0
10104378:	101d45f8 	.word	0x101d45f8
1010437c:	101d4628 	.word	0x101d4628
10104380:	101d4688 	.word	0x101d4688
10104384:	1007d020 	.word	0x1007d020
10104388:	101d4610 	.word	0x101d4610

1010438c <BOOT_ROM_InitDebugFlg>:
1010438c:	4b04      	ldr	r3, [pc, #16]	; (101043a0 <BOOT_ROM_InitDebugFlg+0x14>)
1010438e:	681b      	ldr	r3, [r3, #0]
10104390:	02db      	lsls	r3, r3, #11
10104392:	d403      	bmi.n	1010439c <BOOT_ROM_InitDebugFlg+0x10>
10104394:	f04f 32ff 	mov.w	r2, #4294967295
10104398:	4b02      	ldr	r3, [pc, #8]	; (101043a4 <BOOT_ROM_InitDebugFlg+0x18>)
1010439a:	601a      	str	r2, [r3, #0]
1010439c:	4770      	bx	lr
1010439e:	bf00      	nop
101043a0:	4800022c 	.word	0x4800022c
101043a4:	1000000c 	.word	0x1000000c

101043a8 <BOOT_ROM_ResetVsr>:
101043a8:	4b39      	ldr	r3, [pc, #228]	; (10104490 <BOOT_ROM_ResetVsr+0xe8>)
101043aa:	681b      	ldr	r3, [r3, #0]
101043ac:	b570      	push	{r4, r5, r6, lr}
101043ae:	4a39      	ldr	r2, [pc, #228]	; (10104494 <BOOT_ROM_ResetVsr+0xec>)
101043b0:	4c39      	ldr	r4, [pc, #228]	; (10104498 <BOOT_ROM_ResetVsr+0xf0>)
101043b2:	01dd      	lsls	r5, r3, #7
101043b4:	eba4 0402 	sub.w	r4, r4, r2
101043b8:	d465      	bmi.n	10104486 <BOOT_ROM_ResetVsr+0xde>
101043ba:	4622      	mov	r2, r4
101043bc:	2100      	movs	r1, #0
101043be:	4c37      	ldr	r4, [pc, #220]	; (1010449c <BOOT_ROM_ResetVsr+0xf4>)
101043c0:	4834      	ldr	r0, [pc, #208]	; (10104494 <BOOT_ROM_ResetVsr+0xec>)
101043c2:	47a0      	blx	r4
101043c4:	4836      	ldr	r0, [pc, #216]	; (101044a0 <BOOT_ROM_ResetVsr+0xf8>)
101043c6:	4a37      	ldr	r2, [pc, #220]	; (101044a4 <BOOT_ROM_ResetVsr+0xfc>)
101043c8:	2100      	movs	r1, #0
101043ca:	1a12      	subs	r2, r2, r0
101043cc:	47a0      	blx	r4
101043ce:	4b36      	ldr	r3, [pc, #216]	; (101044a8 <BOOT_ROM_ResetVsr+0x100>)
101043d0:	685b      	ldr	r3, [r3, #4]
101043d2:	4798      	blx	r3
101043d4:	4b35      	ldr	r3, [pc, #212]	; (101044ac <BOOT_ROM_ResetVsr+0x104>)
101043d6:	681b      	ldr	r3, [r3, #0]
101043d8:	02d8      	lsls	r0, r3, #11
101043da:	bf5b      	ittet	pl
101043dc:	f04f 33ff 	movpl.w	r3, #4294967295
101043e0:	4c33      	ldrpl	r4, [pc, #204]	; (101044b0 <BOOT_ROM_ResetVsr+0x108>)
101043e2:	4c33      	ldrmi	r4, [pc, #204]	; (101044b0 <BOOT_ROM_ResetVsr+0x108>)
101043e4:	6023      	strpl	r3, [r4, #0]
101043e6:	4833      	ldr	r0, [pc, #204]	; (101044b4 <BOOT_ROM_ResetVsr+0x10c>)
101043e8:	4b33      	ldr	r3, [pc, #204]	; (101044b8 <BOOT_ROM_ResetVsr+0x110>)
101043ea:	4798      	blx	r3
101043ec:	6823      	ldr	r3, [r4, #0]
101043ee:	0399      	lsls	r1, r3, #14
101043f0:	d443      	bmi.n	1010447a <BOOT_ROM_ResetVsr+0xd2>
101043f2:	f3bf 8f4f 	dsb	sy
101043f6:	f3bf 8f6f 	isb	sy
101043fa:	2100      	movs	r1, #0
101043fc:	4b2f      	ldr	r3, [pc, #188]	; (101044bc <BOOT_ROM_ResetVsr+0x114>)
101043fe:	f8c3 1250 	str.w	r1, [r3, #592]	; 0x250
10104402:	f3bf 8f4f 	dsb	sy
10104406:	f3bf 8f6f 	isb	sy
1010440a:	695a      	ldr	r2, [r3, #20]
1010440c:	f442 3200 	orr.w	r2, r2, #131072	; 0x20000
10104410:	615a      	str	r2, [r3, #20]
10104412:	f3bf 8f4f 	dsb	sy
10104416:	f3bf 8f6f 	isb	sy
1010441a:	f8c3 1084 	str.w	r1, [r3, #132]	; 0x84
1010441e:	f3bf 8f4f 	dsb	sy
10104422:	f643 76e0 	movw	r6, #16352	; 0x3fe0
10104426:	4619      	mov	r1, r3
10104428:	f8d3 3080 	ldr.w	r3, [r3, #128]	; 0x80
1010442c:	f3c3 354e 	ubfx	r5, r3, #13, #15
10104430:	f3c3 04c9 	ubfx	r4, r3, #3, #10
10104434:	4623      	mov	r3, r4
10104436:	ea06 1045 	and.w	r0, r6, r5, lsl #5
1010443a:	ea40 72c3 	orr.w	r2, r0, r3, lsl #31
1010443e:	3b01      	subs	r3, #1
10104440:	f8c1 2260 	str.w	r2, [r1, #608]	; 0x260
10104444:	1c5a      	adds	r2, r3, #1
10104446:	d1f8      	bne.n	1010443a <BOOT_ROM_ResetVsr+0x92>
10104448:	f115 35ff 	adds.w	r5, r5, #4294967295
1010444c:	d2f2      	bcs.n	10104434 <BOOT_ROM_ResetVsr+0x8c>
1010444e:	f3bf 8f4f 	dsb	sy
10104452:	694b      	ldr	r3, [r1, #20]
10104454:	f443 3380 	orr.w	r3, r3, #65536	; 0x10000
10104458:	614b      	str	r3, [r1, #20]
1010445a:	f3bf 8f4f 	dsb	sy
1010445e:	f3bf 8f6f 	isb	sy
10104462:	4a0b      	ldr	r2, [pc, #44]	; (10104490 <BOOT_ROM_ResetVsr+0xe8>)
10104464:	6813      	ldr	r3, [r2, #0]
10104466:	0199      	lsls	r1, r3, #6
10104468:	d5fc      	bpl.n	10104464 <BOOT_ROM_ResetVsr+0xbc>
1010446a:	f023 7300 	bic.w	r3, r3, #33554432	; 0x2000000
1010446e:	6013      	str	r3, [r2, #0]
10104470:	f7ff fe9a 	bl	101041a8 <BOOT_ROM_SignatureCheck>
10104474:	f7ff ff04 	bl	10104280 <BOOT_ROM_FromFlash>
10104478:	e7fe      	b.n	10104478 <BOOT_ROM_ResetVsr+0xd0>
1010447a:	2202      	movs	r2, #2
1010447c:	2101      	movs	r1, #1
1010447e:	4810      	ldr	r0, [pc, #64]	; (101044c0 <BOOT_ROM_ResetVsr+0x118>)
10104480:	f7fb ffb8 	bl	101003f4 <DiagPrintf>
10104484:	e7b5      	b.n	101043f2 <BOOT_ROM_ResetVsr+0x4a>
10104486:	4b0f      	ldr	r3, [pc, #60]	; (101044c4 <BOOT_ROM_ResetVsr+0x11c>)
10104488:	689b      	ldr	r3, [r3, #8]
1010448a:	4798      	blx	r3
1010448c:	e795      	b.n	101043ba <BOOT_ROM_ResetVsr+0x12>
1010448e:	bf00      	nop
10104490:	480003f8 	.word	0x480003f8
10104494:	10000000 	.word	0x10000000
10104498:	10000564 	.word	0x10000564
1010449c:	10106e89 	.word	0x10106e89
101044a0:	1007c000 	.word	0x1007c000
101044a4:	1007c348 	.word	0x1007c348
101044a8:	101c0000 	.word	0x101c0000
101044ac:	4800022c 	.word	0x4800022c
101044b0:	1000000c 	.word	0x1000000c
101044b4:	1007effc 	.word	0x1007effc
101044b8:	1010677d 	.word	0x1010677d
101044bc:	e000ed00 	.word	0xe000ed00
101044c0:	101d469c 	.word	0x101d469c
101044c4:	1007d000 	.word	0x1007d000

101044c8 <EXT32K_Cmd>:
101044c8:	4b06      	ldr	r3, [pc, #24]	; (101044e4 <EXT32K_Cmd+0x1c>)
101044ca:	681b      	ldr	r3, [r3, #0]
101044cc:	2801      	cmp	r0, #1
101044ce:	bf0c      	ite	eq
101044d0:	f443 5300 	orreq.w	r3, r3, #8192	; 0x2000
101044d4:	f423 5340 	bicne.w	r3, r3, #12288	; 0x3000
101044d8:	4a02      	ldr	r2, [pc, #8]	; (101044e4 <EXT32K_Cmd+0x1c>)
101044da:	f423 7380 	bic.w	r3, r3, #256	; 0x100
101044de:	6013      	str	r3, [r2, #0]
101044e0:	4770      	bx	lr
101044e2:	bf00      	nop
101044e4:	48000004 	.word	0x48000004

101044e8 <XTAL_ClkGet>:
101044e8:	4b03      	ldr	r3, [pc, #12]	; (101044f8 <XTAL_ClkGet+0x10>)
101044ea:	681b      	ldr	r3, [r3, #0]
101044ec:	4a03      	ldr	r2, [pc, #12]	; (101044fc <XTAL_ClkGet+0x14>)
101044ee:	f3c3 4303 	ubfx	r3, r3, #16, #4
101044f2:	f852 0023 	ldr.w	r0, [r2, r3, lsl #2]
101044f6:	4770      	bx	lr
101044f8:	48000228 	.word	0x48000228
101044fc:	101d528c 	.word	0x101d528c

10104500 <CPU_ClkSet>:
10104500:	4a03      	ldr	r2, [pc, #12]	; (10104510 <CPU_ClkSet+0x10>)
10104502:	6813      	ldr	r3, [r2, #0]
10104504:	f023 6360 	bic.w	r3, r3, #234881024	; 0xe000000
10104508:	ea43 6040 	orr.w	r0, r3, r0, lsl #25
1010450c:	6010      	str	r0, [r2, #0]
1010450e:	4770      	bx	lr
10104510:	4800021c 	.word	0x4800021c

10104514 <CPU_ClkGet>:
10104514:	4b05      	ldr	r3, [pc, #20]	; (1010452c <CPU_ClkGet+0x18>)
10104516:	681b      	ldr	r3, [r3, #0]
10104518:	b108      	cbz	r0, 1010451e <CPU_ClkGet+0xa>
1010451a:	4805      	ldr	r0, [pc, #20]	; (10104530 <CPU_ClkGet+0x1c>)
1010451c:	4770      	bx	lr
1010451e:	4a05      	ldr	r2, [pc, #20]	; (10104534 <CPU_ClkGet+0x20>)
10104520:	f3c3 6342 	ubfx	r3, r3, #25, #3
10104524:	f852 0023 	ldr.w	r0, [r2, r3, lsl #2]
10104528:	4770      	bx	lr
1010452a:	bf00      	nop
1010452c:	4800021c 	.word	0x4800021c
10104530:	01312d00 	.word	0x01312d00
10104534:	101d52cc 	.word	0x101d52cc

10104538 <CRYPTO_MemDump>:
10104538:	2800      	cmp	r0, #0
1010453a:	d04b      	beq.n	101045d4 <CRYPTO_MemDump+0x9c>
1010453c:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10104540:	460c      	mov	r4, r1
10104542:	b083      	sub	sp, #12
10104544:	2900      	cmp	r1, #0
10104546:	d042      	beq.n	101045ce <CRYPTO_MemDump+0x96>
10104548:	4607      	mov	r7, r0
1010454a:	b11a      	cbz	r2, 10104554 <CRYPTO_MemDump+0x1c>
1010454c:	4611      	mov	r1, r2
1010454e:	4826      	ldr	r0, [pc, #152]	; (101045e8 <CRYPTO_MemDump+0xb0>)
10104550:	f7fb ff50 	bl	101003f4 <DiagPrintf>
10104554:	f04f 0800 	mov.w	r8, #0
10104558:	f004 030f 	and.w	r3, r4, #15
1010455c:	ea4f 1914 	mov.w	r9, r4, lsr #4
10104560:	4d22      	ldr	r5, [pc, #136]	; (101045ec <CRYPTO_MemDump+0xb4>)
10104562:	9301      	str	r3, [sp, #4]
10104564:	f109 0a01 	add.w	sl, r9, #1
10104568:	45c1      	cmp	r9, r8
1010456a:	bf18      	it	ne
1010456c:	2610      	movne	r6, #16
1010456e:	d036      	beq.n	101045de <CRYPTO_MemDump+0xa6>
10104570:	4639      	mov	r1, r7
10104572:	481f      	ldr	r0, [pc, #124]	; (101045f0 <CRYPTO_MemDump+0xb8>)
10104574:	f7fb ff3e 	bl	101003f4 <DiagPrintf>
10104578:	f107 3bff 	add.w	fp, r7, #4294967295
1010457c:	2400      	movs	r4, #0
1010457e:	e001      	b.n	10104584 <CRYPTO_MemDump+0x4c>
10104580:	2c08      	cmp	r4, #8
10104582:	d028      	beq.n	101045d6 <CRYPTO_MemDump+0x9e>
10104584:	3401      	adds	r4, #1
10104586:	f81b 1f01 	ldrb.w	r1, [fp, #1]!
1010458a:	4628      	mov	r0, r5
1010458c:	f7fb ff32 	bl	101003f4 <DiagPrintf>
10104590:	42b4      	cmp	r4, r6
10104592:	dbf5      	blt.n	10104580 <CRYPTO_MemDump+0x48>
10104594:	2e10      	cmp	r6, #16
10104596:	d00a      	beq.n	101045ae <CRYPTO_MemDump+0x76>
10104598:	2e07      	cmp	r6, #7
1010459a:	dd14      	ble.n	101045c6 <CRYPTO_MemDump+0x8e>
1010459c:	f8df b05c 	ldr.w	fp, [pc, #92]	; 101045fc <CRYPTO_MemDump+0xc4>
101045a0:	f1c6 0410 	rsb	r4, r6, #16
101045a4:	4658      	mov	r0, fp
101045a6:	f7fb ff25 	bl	101003f4 <DiagPrintf>
101045aa:	3c01      	subs	r4, #1
101045ac:	d1fa      	bne.n	101045a4 <CRYPTO_MemDump+0x6c>
101045ae:	f108 0801 	add.w	r8, r8, #1
101045b2:	45c2      	cmp	sl, r8
101045b4:	f107 0710 	add.w	r7, r7, #16
101045b8:	dcd6      	bgt.n	10104568 <CRYPTO_MemDump+0x30>
101045ba:	480e      	ldr	r0, [pc, #56]	; (101045f4 <CRYPTO_MemDump+0xbc>)
101045bc:	b003      	add	sp, #12
101045be:	e8bd 4ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
101045c2:	f7fb bf17 	b.w	101003f4 <DiagPrintf>
101045c6:	480c      	ldr	r0, [pc, #48]	; (101045f8 <CRYPTO_MemDump+0xc0>)
101045c8:	f7fb ff14 	bl	101003f4 <DiagPrintf>
101045cc:	e7e6      	b.n	1010459c <CRYPTO_MemDump+0x64>
101045ce:	b003      	add	sp, #12
101045d0:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
101045d4:	4770      	bx	lr
101045d6:	4808      	ldr	r0, [pc, #32]	; (101045f8 <CRYPTO_MemDump+0xc0>)
101045d8:	f7fb ff0c 	bl	101003f4 <DiagPrintf>
101045dc:	e7d2      	b.n	10104584 <CRYPTO_MemDump+0x4c>
101045de:	9b01      	ldr	r3, [sp, #4]
101045e0:	2b00      	cmp	r3, #0
101045e2:	d0ea      	beq.n	101045ba <CRYPTO_MemDump+0x82>
101045e4:	9e01      	ldr	r6, [sp, #4]
101045e6:	e7c3      	b.n	10104570 <CRYPTO_MemDump+0x38>
101045e8:	101d46ac 	.word	0x101d46ac
101045ec:	101d46c4 	.word	0x101d46c4
101045f0:	101d46b4 	.word	0x101d46b4
101045f4:	101d46b0 	.word	0x101d46b0
101045f8:	101d46c0 	.word	0x101d46c0
101045fc:	101d46cc 	.word	0x101d46cc

10104600 <CRYPTO_RegDump>:
10104600:	4a4c      	ldr	r2, [pc, #304]	; (10104734 <CRYPTO_RegDump+0x134>)
10104602:	b510      	push	{r4, lr}
10104604:	4b4c      	ldr	r3, [pc, #304]	; (10104738 <CRYPTO_RegDump+0x138>)
10104606:	e843 f300 	tt	r3, r3
1010460a:	f413 0f80 	tst.w	r3, #4194304	; 0x400000
1010460e:	4c4b      	ldr	r4, [pc, #300]	; (1010473c <CRYPTO_RegDump+0x13c>)
10104610:	bf18      	it	ne
10104612:	4614      	movne	r4, r2
10104614:	484a      	ldr	r0, [pc, #296]	; (10104740 <CRYPTO_RegDump+0x140>)
10104616:	f7fb feed 	bl	101003f4 <DiagPrintf>
1010461a:	484a      	ldr	r0, [pc, #296]	; (10104744 <CRYPTO_RegDump+0x144>)
1010461c:	f7fb feea 	bl	101003f4 <DiagPrintf>
10104620:	4847      	ldr	r0, [pc, #284]	; (10104740 <CRYPTO_RegDump+0x140>)
10104622:	f7fb fee7 	bl	101003f4 <DiagPrintf>
10104626:	6821      	ldr	r1, [r4, #0]
10104628:	4847      	ldr	r0, [pc, #284]	; (10104748 <CRYPTO_RegDump+0x148>)
1010462a:	f7fb fee3 	bl	101003f4 <DiagPrintf>
1010462e:	6861      	ldr	r1, [r4, #4]
10104630:	4846      	ldr	r0, [pc, #280]	; (1010474c <CRYPTO_RegDump+0x14c>)
10104632:	f7fb fedf 	bl	101003f4 <DiagPrintf>
10104636:	68a1      	ldr	r1, [r4, #8]
10104638:	4845      	ldr	r0, [pc, #276]	; (10104750 <CRYPTO_RegDump+0x150>)
1010463a:	f7fb fedb 	bl	101003f4 <DiagPrintf>
1010463e:	6921      	ldr	r1, [r4, #16]
10104640:	4844      	ldr	r0, [pc, #272]	; (10104754 <CRYPTO_RegDump+0x154>)
10104642:	f7fb fed7 	bl	101003f4 <DiagPrintf>
10104646:	6961      	ldr	r1, [r4, #20]
10104648:	4843      	ldr	r0, [pc, #268]	; (10104758 <CRYPTO_RegDump+0x158>)
1010464a:	f7fb fed3 	bl	101003f4 <DiagPrintf>
1010464e:	69a1      	ldr	r1, [r4, #24]
10104650:	4842      	ldr	r0, [pc, #264]	; (1010475c <CRYPTO_RegDump+0x15c>)
10104652:	f7fb fecf 	bl	101003f4 <DiagPrintf>
10104656:	69e1      	ldr	r1, [r4, #28]
10104658:	4841      	ldr	r0, [pc, #260]	; (10104760 <CRYPTO_RegDump+0x160>)
1010465a:	f7fb fecb 	bl	101003f4 <DiagPrintf>
1010465e:	6a21      	ldr	r1, [r4, #32]
10104660:	4840      	ldr	r0, [pc, #256]	; (10104764 <CRYPTO_RegDump+0x164>)
10104662:	f7fb fec7 	bl	101003f4 <DiagPrintf>
10104666:	6a61      	ldr	r1, [r4, #36]	; 0x24
10104668:	483f      	ldr	r0, [pc, #252]	; (10104768 <CRYPTO_RegDump+0x168>)
1010466a:	f7fb fec3 	bl	101003f4 <DiagPrintf>
1010466e:	6aa1      	ldr	r1, [r4, #40]	; 0x28
10104670:	483e      	ldr	r0, [pc, #248]	; (1010476c <CRYPTO_RegDump+0x16c>)
10104672:	f7fb febf 	bl	101003f4 <DiagPrintf>
10104676:	6ae1      	ldr	r1, [r4, #44]	; 0x2c
10104678:	483d      	ldr	r0, [pc, #244]	; (10104770 <CRYPTO_RegDump+0x170>)
1010467a:	f7fb febb 	bl	101003f4 <DiagPrintf>
1010467e:	6b21      	ldr	r1, [r4, #48]	; 0x30
10104680:	483c      	ldr	r0, [pc, #240]	; (10104774 <CRYPTO_RegDump+0x174>)
10104682:	f7fb feb7 	bl	101003f4 <DiagPrintf>
10104686:	6c21      	ldr	r1, [r4, #64]	; 0x40
10104688:	483b      	ldr	r0, [pc, #236]	; (10104778 <CRYPTO_RegDump+0x178>)
1010468a:	f7fb feb3 	bl	101003f4 <DiagPrintf>
1010468e:	6c61      	ldr	r1, [r4, #68]	; 0x44
10104690:	483a      	ldr	r0, [pc, #232]	; (1010477c <CRYPTO_RegDump+0x17c>)
10104692:	f7fb feaf 	bl	101003f4 <DiagPrintf>
10104696:	6ca1      	ldr	r1, [r4, #72]	; 0x48
10104698:	4839      	ldr	r0, [pc, #228]	; (10104780 <CRYPTO_RegDump+0x180>)
1010469a:	f7fb feab 	bl	101003f4 <DiagPrintf>
1010469e:	6ce1      	ldr	r1, [r4, #76]	; 0x4c
101046a0:	4838      	ldr	r0, [pc, #224]	; (10104784 <CRYPTO_RegDump+0x184>)
101046a2:	f7fb fea7 	bl	101003f4 <DiagPrintf>
101046a6:	6d21      	ldr	r1, [r4, #80]	; 0x50
101046a8:	4837      	ldr	r0, [pc, #220]	; (10104788 <CRYPTO_RegDump+0x188>)
101046aa:	f7fb fea3 	bl	101003f4 <DiagPrintf>
101046ae:	6d61      	ldr	r1, [r4, #84]	; 0x54
101046b0:	4836      	ldr	r0, [pc, #216]	; (1010478c <CRYPTO_RegDump+0x18c>)
101046b2:	f7fb fe9f 	bl	101003f4 <DiagPrintf>
101046b6:	6da1      	ldr	r1, [r4, #88]	; 0x58
101046b8:	4835      	ldr	r0, [pc, #212]	; (10104790 <CRYPTO_RegDump+0x190>)
101046ba:	f7fb fe9b 	bl	101003f4 <DiagPrintf>
101046be:	6de1      	ldr	r1, [r4, #92]	; 0x5c
101046c0:	4834      	ldr	r0, [pc, #208]	; (10104794 <CRYPTO_RegDump+0x194>)
101046c2:	f7fb fe97 	bl	101003f4 <DiagPrintf>
101046c6:	6e21      	ldr	r1, [r4, #96]	; 0x60
101046c8:	4833      	ldr	r0, [pc, #204]	; (10104798 <CRYPTO_RegDump+0x198>)
101046ca:	f7fb fe93 	bl	101003f4 <DiagPrintf>
101046ce:	6e61      	ldr	r1, [r4, #100]	; 0x64
101046d0:	4832      	ldr	r0, [pc, #200]	; (1010479c <CRYPTO_RegDump+0x19c>)
101046d2:	f7fb fe8f 	bl	101003f4 <DiagPrintf>
101046d6:	6ea1      	ldr	r1, [r4, #104]	; 0x68
101046d8:	4831      	ldr	r0, [pc, #196]	; (101047a0 <CRYPTO_RegDump+0x1a0>)
101046da:	f7fb fe8b 	bl	101003f4 <DiagPrintf>
101046de:	f8d4 1888 	ldr.w	r1, [r4, #2184]	; 0x888
101046e2:	4830      	ldr	r0, [pc, #192]	; (101047a4 <CRYPTO_RegDump+0x1a4>)
101046e4:	f7fb fe86 	bl	101003f4 <DiagPrintf>
101046e8:	f504 5380 	add.w	r3, r4, #4096	; 0x1000
101046ec:	6819      	ldr	r1, [r3, #0]
101046ee:	482e      	ldr	r0, [pc, #184]	; (101047a8 <CRYPTO_RegDump+0x1a8>)
101046f0:	f7fb fe80 	bl	101003f4 <DiagPrintf>
101046f4:	f241 0304 	movw	r3, #4100	; 0x1004
101046f8:	482c      	ldr	r0, [pc, #176]	; (101047ac <CRYPTO_RegDump+0x1ac>)
101046fa:	58e1      	ldr	r1, [r4, r3]
101046fc:	f7fb fe7a 	bl	101003f4 <DiagPrintf>
10104700:	f241 0308 	movw	r3, #4104	; 0x1008
10104704:	482a      	ldr	r0, [pc, #168]	; (101047b0 <CRYPTO_RegDump+0x1b0>)
10104706:	58e1      	ldr	r1, [r4, r3]
10104708:	f7fb fe74 	bl	101003f4 <DiagPrintf>
1010470c:	f241 030c 	movw	r3, #4108	; 0x100c
10104710:	4828      	ldr	r0, [pc, #160]	; (101047b4 <CRYPTO_RegDump+0x1b4>)
10104712:	58e1      	ldr	r1, [r4, r3]
10104714:	f7fb fe6e 	bl	101003f4 <DiagPrintf>
10104718:	f241 0310 	movw	r3, #4112	; 0x1010
1010471c:	4826      	ldr	r0, [pc, #152]	; (101047b8 <CRYPTO_RegDump+0x1b8>)
1010471e:	58e1      	ldr	r1, [r4, r3]
10104720:	f7fb fe68 	bl	101003f4 <DiagPrintf>
10104724:	f241 0314 	movw	r3, #4116	; 0x1014
10104728:	4824      	ldr	r0, [pc, #144]	; (101047bc <CRYPTO_RegDump+0x1bc>)
1010472a:	58e1      	ldr	r1, [r4, r3]
1010472c:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
10104730:	f7fb be60 	b.w	101003f4 <DiagPrintf>
10104734:	50022000 	.word	0x50022000
10104738:	101003f5 	.word	0x101003f5
1010473c:	40022000 	.word	0x40022000
10104740:	101d46d0 	.word	0x101d46d0
10104744:	101d46fc 	.word	0x101d46fc
10104748:	101d4718 	.word	0x101d4718
1010474c:	101d4728 	.word	0x101d4728
10104750:	101d4738 	.word	0x101d4738
10104754:	101d4748 	.word	0x101d4748
10104758:	101d4760 	.word	0x101d4760
1010475c:	101d4770 	.word	0x101d4770
10104760:	101d4780 	.word	0x101d4780
10104764:	101d4794 	.word	0x101d4794
10104768:	101d47a8 	.word	0x101d47a8
1010476c:	101d47bc 	.word	0x101d47bc
10104770:	101d47d0 	.word	0x101d47d0
10104774:	101d47e4 	.word	0x101d47e4
10104778:	101d47f8 	.word	0x101d47f8
1010477c:	101d480c 	.word	0x101d480c
10104780:	101d4820 	.word	0x101d4820
10104784:	101d4834 	.word	0x101d4834
10104788:	101d4848 	.word	0x101d4848
1010478c:	101d4860 	.word	0x101d4860
10104790:	101d4878 	.word	0x101d4878
10104794:	101d4890 	.word	0x101d4890
10104798:	101d48a8 	.word	0x101d48a8
1010479c:	101d48c0 	.word	0x101d48c0
101047a0:	101d48d8 	.word	0x101d48d8
101047a4:	101d48f0 	.word	0x101d48f0
101047a8:	101d4908 	.word	0x101d4908
101047ac:	101d4918 	.word	0x101d4918
101047b0:	101d4928 	.word	0x101d4928
101047b4:	101d4938 	.word	0x101d4938
101047b8:	101d4950 	.word	0x101d4950
101047bc:	101d4960 	.word	0x101d4960

101047c0 <CRYPTO_CleanCmdOk>:
101047c0:	490a      	ldr	r1, [pc, #40]	; (101047ec <CRYPTO_CleanCmdOk+0x2c>)
101047c2:	4a0b      	ldr	r2, [pc, #44]	; (101047f0 <CRYPTO_CleanCmdOk+0x30>)
101047c4:	e842 f200 	tt	r2, r2
101047c8:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
101047cc:	4b09      	ldr	r3, [pc, #36]	; (101047f4 <CRYPTO_CleanCmdOk+0x34>)
101047ce:	bf18      	it	ne
101047d0:	460b      	movne	r3, r1
101047d2:	691a      	ldr	r2, [r3, #16]
101047d4:	6919      	ldr	r1, [r3, #16]
101047d6:	0212      	lsls	r2, r2, #8
101047d8:	f402 027f 	and.w	r2, r2, #16711680	; 0xff0000
101047dc:	430a      	orrs	r2, r1
101047de:	611a      	str	r2, [r3, #16]
101047e0:	691a      	ldr	r2, [r3, #16]
101047e2:	f042 0210 	orr.w	r2, r2, #16
101047e6:	611a      	str	r2, [r3, #16]
101047e8:	4770      	bx	lr
101047ea:	bf00      	nop
101047ec:	50022000 	.word	0x50022000
101047f0:	101003f5 	.word	0x101003f5
101047f4:	40022000 	.word	0x40022000

101047f8 <CRYPTO_ClearAllINT>:
101047f8:	4907      	ldr	r1, [pc, #28]	; (10104818 <CRYPTO_ClearAllINT+0x20>)
101047fa:	b508      	push	{r3, lr}
101047fc:	4a07      	ldr	r2, [pc, #28]	; (1010481c <CRYPTO_ClearAllINT+0x24>)
101047fe:	e842 f200 	tt	r2, r2
10104802:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104806:	4b06      	ldr	r3, [pc, #24]	; (10104820 <CRYPTO_ClearAllINT+0x28>)
10104808:	bf18      	it	ne
1010480a:	460b      	movne	r3, r1
1010480c:	f64f 71ff 	movw	r1, #65535	; 0xffff
10104810:	4a04      	ldr	r2, [pc, #16]	; (10104824 <CRYPTO_ClearAllINT+0x2c>)
10104812:	61d9      	str	r1, [r3, #28]
10104814:	4790      	blx	r2
10104816:	bd08      	pop	{r3, pc}
10104818:	50022000 	.word	0x50022000
1010481c:	101003f5 	.word	0x101003f5
10104820:	40022000 	.word	0x40022000
10104824:	101047c1 	.word	0x101047c1

10104828 <CRYPTO_Reset>:
10104828:	490c      	ldr	r1, [pc, #48]	; (1010485c <CRYPTO_Reset+0x34>)
1010482a:	4a0d      	ldr	r2, [pc, #52]	; (10104860 <CRYPTO_Reset+0x38>)
1010482c:	e842 f200 	tt	r2, r2
10104830:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104834:	4b0b      	ldr	r3, [pc, #44]	; (10104864 <CRYPTO_Reset+0x3c>)
10104836:	f44f 1280 	mov.w	r2, #1048576	; 0x100000
1010483a:	bf18      	it	ne
1010483c:	460b      	movne	r3, r1
1010483e:	2101      	movs	r1, #1
10104840:	6119      	str	r1, [r3, #16]
10104842:	631a      	str	r2, [r3, #48]	; 0x30
10104844:	6b1a      	ldr	r2, [r3, #48]	; 0x30
10104846:	f042 020e 	orr.w	r2, r2, #14
1010484a:	631a      	str	r2, [r3, #48]	; 0x30
1010484c:	6b1a      	ldr	r2, [r3, #48]	; 0x30
1010484e:	4906      	ldr	r1, [pc, #24]	; (10104868 <CRYPTO_Reset+0x40>)
10104850:	f442 62c2 	orr.w	r2, r2, #1552	; 0x610
10104854:	631a      	str	r2, [r3, #48]	; 0x30
10104856:	6199      	str	r1, [r3, #24]
10104858:	4770      	bx	lr
1010485a:	bf00      	nop
1010485c:	50022000 	.word	0x50022000
10104860:	101003f5 	.word	0x101003f5
10104864:	40022000 	.word	0x40022000
10104868:	01010000 	.word	0x01010000

1010486c <CRYPTO_SetSecurityModeAD>:
1010486c:	e92d 45f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, sl, lr}
10104870:	9f09      	ldr	r7, [sp, #36]	; 0x24
10104872:	4688      	mov	r8, r1
10104874:	4616      	mov	r6, r2
10104876:	469a      	mov	sl, r3
10104878:	9d0a      	ldr	r5, [sp, #40]	; 0x28
1010487a:	4604      	mov	r4, r0
1010487c:	2800      	cmp	r0, #0
1010487e:	f000 80ce 	beq.w	10104a1e <CRYPTO_SetSecurityModeAD+0x1b2>
10104882:	7823      	ldrb	r3, [r4, #0]
10104884:	2b01      	cmp	r3, #1
10104886:	d004      	beq.n	10104892 <CRYPTO_SetSecurityModeAD+0x26>
10104888:	f44f 710d 	mov.w	r1, #564	; 0x234
1010488c:	486a      	ldr	r0, [pc, #424]	; (10104a38 <CRYPTO_SetSecurityModeAD+0x1cc>)
1010488e:	f7fb ffef 	bl	10100870 <io_assert_failed>
10104892:	b12d      	cbz	r5, 101048a0 <CRYPTO_SetSecurityModeAD+0x34>
10104894:	2f00      	cmp	r7, #0
10104896:	f000 80c8 	beq.w	10104a2a <CRYPTO_SetSecurityModeAD+0x1be>
1010489a:	2d40      	cmp	r5, #64	; 0x40
1010489c:	f200 8099 	bhi.w	101049d2 <CRYPTO_SetSecurityModeAD+0x166>
101048a0:	2200      	movs	r2, #0
101048a2:	f1b8 3fff 	cmp.w	r8, #4294967295
101048a6:	f8c4 8004 	str.w	r8, [r4, #4]
101048aa:	7262      	strb	r2, [r4, #9]
101048ac:	72a2      	strb	r2, [r4, #10]
101048ae:	7222      	strb	r2, [r4, #8]
101048b0:	72e2      	strb	r2, [r4, #11]
101048b2:	7322      	strb	r2, [r4, #12]
101048b4:	d012      	beq.n	101048dc <CRYPTO_SetSecurityModeAD+0x70>
101048b6:	f008 0330 	and.w	r3, r8, #48	; 0x30
101048ba:	2b10      	cmp	r3, #16
101048bc:	f000 8098 	beq.w	101049f0 <CRYPTO_SetSecurityModeAD+0x184>
101048c0:	d951      	bls.n	10104966 <CRYPTO_SetSecurityModeAD+0xfa>
101048c2:	2b20      	cmp	r3, #32
101048c4:	f000 809d 	beq.w	10104a02 <CRYPTO_SetSecurityModeAD+0x196>
101048c8:	2b30      	cmp	r3, #48	; 0x30
101048ca:	d101      	bne.n	101048d0 <CRYPTO_SetSecurityModeAD+0x64>
101048cc:	2301      	movs	r3, #1
101048ce:	72e3      	strb	r3, [r4, #11]
101048d0:	f088 0880 	eor.w	r8, r8, #128	; 0x80
101048d4:	f3c8 18c0 	ubfx	r8, r8, #7, #1
101048d8:	f884 800c 	strb.w	r8, [r4, #12]
101048dc:	1c72      	adds	r2, r6, #1
101048de:	6126      	str	r6, [r4, #16]
101048e0:	d06b      	beq.n	101049ba <CRYPTO_SetSecurityModeAD+0x14e>
101048e2:	f006 0803 	and.w	r8, r6, #3
101048e6:	f1b8 0f01 	cmp.w	r8, #1
101048ea:	f1a8 0102 	sub.w	r1, r8, #2
101048ee:	bf0c      	ite	eq
101048f0:	2301      	moveq	r3, #1
101048f2:	2300      	movne	r3, #0
101048f4:	fab1 f181 	clz	r1, r1
101048f8:	fab8 f288 	clz	r2, r8
101048fc:	ea4f 1151 	mov.w	r1, r1, lsr #5
10104900:	ea4f 1252 	mov.w	r2, r2, lsr #5
10104904:	75e3      	strb	r3, [r4, #23]
10104906:	f3c6 0380 	ubfx	r3, r6, #2, #1
1010490a:	7561      	strb	r1, [r4, #21]
1010490c:	75a2      	strb	r2, [r4, #22]
1010490e:	7523      	strb	r3, [r4, #20]
10104910:	d01f      	beq.n	10104952 <CRYPTO_SetSecurityModeAD+0xe6>
10104912:	2300      	movs	r3, #0
10104914:	f1b8 0f01 	cmp.w	r8, #1
10104918:	7623      	strb	r3, [r4, #24]
1010491a:	d021      	beq.n	10104960 <CRYPTO_SetSecurityModeAD+0xf4>
1010491c:	d356      	bcc.n	101049cc <CRYPTO_SetSecurityModeAD+0x160>
1010491e:	f1b8 0f02 	cmp.w	r8, #2
10104922:	d150      	bne.n	101049c6 <CRYPTO_SetSecurityModeAD+0x15a>
10104924:	2310      	movs	r3, #16
10104926:	62e3      	str	r3, [r4, #44]	; 0x2c
10104928:	9b08      	ldr	r3, [sp, #32]
1010492a:	f8c4 a04c 	str.w	sl, [r4, #76]	; 0x4c
1010492e:	64a3      	str	r3, [r4, #72]	; 0x48
10104930:	62a7      	str	r7, [r4, #40]	; 0x28
10104932:	6265      	str	r5, [r4, #36]	; 0x24
10104934:	bb15      	cbnz	r5, 1010497c <CRYPTO_SetSecurityModeAD+0x110>
10104936:	6625      	str	r5, [r4, #96]	; 0x60
10104938:	6665      	str	r5, [r4, #100]	; 0x64
1010493a:	3601      	adds	r6, #1
1010493c:	d006      	beq.n	1010494c <CRYPTO_SetSecurityModeAD+0xe0>
1010493e:	2300      	movs	r3, #0
10104940:	2201      	movs	r2, #1
10104942:	f884 3031 	strb.w	r3, [r4, #49]	; 0x31
10104946:	f884 2030 	strb.w	r2, [r4, #48]	; 0x30
1010494a:	6363      	str	r3, [r4, #52]	; 0x34
1010494c:	2000      	movs	r0, #0
1010494e:	e8bd 85f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, sl, pc}
10104952:	f006 0330 	and.w	r3, r6, #48	; 0x30
10104956:	2b10      	cmp	r3, #16
10104958:	d05c      	beq.n	10104a14 <CRYPTO_SetSecurityModeAD+0x1a8>
1010495a:	2b20      	cmp	r3, #32
1010495c:	d13f      	bne.n	101049de <CRYPTO_SetSecurityModeAD+0x172>
1010495e:	7623      	strb	r3, [r4, #24]
10104960:	7e23      	ldrb	r3, [r4, #24]
10104962:	62e3      	str	r3, [r4, #44]	; 0x2c
10104964:	e7e0      	b.n	10104928 <CRYPTO_SetSecurityModeAD+0xbc>
10104966:	2b00      	cmp	r3, #0
10104968:	d1b2      	bne.n	101048d0 <CRYPTO_SetSecurityModeAD+0x64>
1010496a:	2301      	movs	r3, #1
1010496c:	f088 0880 	eor.w	r8, r8, #128	; 0x80
10104970:	f3c8 18c0 	ubfx	r8, r8, #7, #1
10104974:	7223      	strb	r3, [r4, #8]
10104976:	f884 800c 	strb.w	r8, [r4, #12]
1010497a:	e7af      	b.n	101048dc <CRYPTO_SetSecurityModeAD+0x70>
1010497c:	f104 03a8 	add.w	r3, r4, #168	; 0xa8
10104980:	f104 0068 	add.w	r0, r4, #104	; 0x68
10104984:	6663      	str	r3, [r4, #100]	; 0x64
10104986:	2240      	movs	r2, #64	; 0x40
10104988:	2136      	movs	r1, #54	; 0x36
1010498a:	4f2c      	ldr	r7, [pc, #176]	; (10104a3c <CRYPTO_SetSecurityModeAD+0x1d0>)
1010498c:	6620      	str	r0, [r4, #96]	; 0x60
1010498e:	47b8      	blx	r7
10104990:	2240      	movs	r2, #64	; 0x40
10104992:	215c      	movs	r1, #92	; 0x5c
10104994:	6e60      	ldr	r0, [r4, #100]	; 0x64
10104996:	47b8      	blx	r7
10104998:	2300      	movs	r3, #0
1010499a:	6e21      	ldr	r1, [r4, #96]	; 0x60
1010499c:	6aa0      	ldr	r0, [r4, #40]	; 0x28
1010499e:	5cca      	ldrb	r2, [r1, r3]
101049a0:	5cc0      	ldrb	r0, [r0, r3]
101049a2:	4042      	eors	r2, r0
101049a4:	54ca      	strb	r2, [r1, r3]
101049a6:	6e61      	ldr	r1, [r4, #100]	; 0x64
101049a8:	6aa0      	ldr	r0, [r4, #40]	; 0x28
101049aa:	5cca      	ldrb	r2, [r1, r3]
101049ac:	5cc0      	ldrb	r0, [r0, r3]
101049ae:	4042      	eors	r2, r0
101049b0:	54ca      	strb	r2, [r1, r3]
101049b2:	3301      	adds	r3, #1
101049b4:	429d      	cmp	r5, r3
101049b6:	d1f0      	bne.n	1010499a <CRYPTO_SetSecurityModeAD+0x12e>
101049b8:	e7bf      	b.n	1010493a <CRYPTO_SetSecurityModeAD+0xce>
101049ba:	2300      	movs	r3, #0
101049bc:	7563      	strb	r3, [r4, #21]
101049be:	7523      	strb	r3, [r4, #20]
101049c0:	75a3      	strb	r3, [r4, #22]
101049c2:	75e3      	strb	r3, [r4, #23]
101049c4:	7623      	strb	r3, [r4, #24]
101049c6:	2300      	movs	r3, #0
101049c8:	62e3      	str	r3, [r4, #44]	; 0x2c
101049ca:	e7ad      	b.n	10104928 <CRYPTO_SetSecurityModeAD+0xbc>
101049cc:	2314      	movs	r3, #20
101049ce:	62e3      	str	r3, [r4, #44]	; 0x2c
101049d0:	e7aa      	b.n	10104928 <CRYPTO_SetSecurityModeAD+0xbc>
101049d2:	f44f 710e 	mov.w	r1, #568	; 0x238
101049d6:	4818      	ldr	r0, [pc, #96]	; (10104a38 <CRYPTO_SetSecurityModeAD+0x1cc>)
101049d8:	f7fb ff4a 	bl	10100870 <io_assert_failed>
101049dc:	e760      	b.n	101048a0 <CRYPTO_SetSecurityModeAD+0x34>
101049de:	4b18      	ldr	r3, [pc, #96]	; (10104a40 <CRYPTO_SetSecurityModeAD+0x1d4>)
101049e0:	681b      	ldr	r3, [r3, #0]
101049e2:	049b      	lsls	r3, r3, #18
101049e4:	d595      	bpl.n	10104912 <CRYPTO_SetSecurityModeAD+0xa6>
101049e6:	4631      	mov	r1, r6
101049e8:	4816      	ldr	r0, [pc, #88]	; (10104a44 <CRYPTO_SetSecurityModeAD+0x1d8>)
101049ea:	f7fb fd03 	bl	101003f4 <DiagPrintf>
101049ee:	e790      	b.n	10104912 <CRYPTO_SetSecurityModeAD+0xa6>
101049f0:	2301      	movs	r3, #1
101049f2:	f088 0880 	eor.w	r8, r8, #128	; 0x80
101049f6:	f3c8 18c0 	ubfx	r8, r8, #7, #1
101049fa:	7263      	strb	r3, [r4, #9]
101049fc:	f884 800c 	strb.w	r8, [r4, #12]
10104a00:	e76c      	b.n	101048dc <CRYPTO_SetSecurityModeAD+0x70>
10104a02:	2301      	movs	r3, #1
10104a04:	f088 0880 	eor.w	r8, r8, #128	; 0x80
10104a08:	f3c8 18c0 	ubfx	r8, r8, #7, #1
10104a0c:	72a3      	strb	r3, [r4, #10]
10104a0e:	f884 800c 	strb.w	r8, [r4, #12]
10104a12:	e763      	b.n	101048dc <CRYPTO_SetSecurityModeAD+0x70>
10104a14:	231c      	movs	r3, #28
10104a16:	7623      	strb	r3, [r4, #24]
10104a18:	7e23      	ldrb	r3, [r4, #24]
10104a1a:	62e3      	str	r3, [r4, #44]	; 0x2c
10104a1c:	e784      	b.n	10104928 <CRYPTO_SetSecurityModeAD+0xbc>
10104a1e:	f240 2133 	movw	r1, #563	; 0x233
10104a22:	4805      	ldr	r0, [pc, #20]	; (10104a38 <CRYPTO_SetSecurityModeAD+0x1cc>)
10104a24:	f7fb ff24 	bl	10100870 <io_assert_failed>
10104a28:	e72b      	b.n	10104882 <CRYPTO_SetSecurityModeAD+0x16>
10104a2a:	f240 2137 	movw	r1, #567	; 0x237
10104a2e:	4802      	ldr	r0, [pc, #8]	; (10104a38 <CRYPTO_SetSecurityModeAD+0x1cc>)
10104a30:	f7fb ff1e 	bl	10100870 <io_assert_failed>
10104a34:	e731      	b.n	1010489a <CRYPTO_SetSecurityModeAD+0x2e>
10104a36:	bf00      	nop
10104a38:	101d52e0 	.word	0x101d52e0
10104a3c:	10106e89 	.word	0x10106e89
10104a40:	1000000c 	.word	0x1000000c
10104a44:	101d4970 	.word	0x101d4970

10104a48 <CRYPTO_Init>:
10104a48:	b510      	push	{r4, lr}
10104a4a:	4c06      	ldr	r4, [pc, #24]	; (10104a64 <CRYPTO_Init+0x1c>)
10104a4c:	2800      	cmp	r0, #0
10104a4e:	bf18      	it	ne
10104a50:	4604      	movne	r4, r0
10104a52:	4b05      	ldr	r3, [pc, #20]	; (10104a68 <CRYPTO_Init+0x20>)
10104a54:	4620      	mov	r0, r4
10104a56:	4798      	blx	r3
10104a58:	2301      	movs	r3, #1
10104a5a:	2000      	movs	r0, #0
10104a5c:	7023      	strb	r3, [r4, #0]
10104a5e:	7060      	strb	r0, [r4, #1]
10104a60:	bd10      	pop	{r4, pc}
10104a62:	bf00      	nop
10104a64:	100003a0 	.word	0x100003a0
10104a68:	10104829 	.word	0x10104829

10104a6c <CRYPTO_ProcessAD>:
10104a6c:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10104a70:	4eb4      	ldr	r6, [pc, #720]	; (10104d44 <CRYPTO_ProcessAD+0x2d8>)
10104a72:	b085      	sub	sp, #20
10104a74:	4db4      	ldr	r5, [pc, #720]	; (10104d48 <CRYPTO_ProcessAD+0x2dc>)
10104a76:	9c11      	ldr	r4, [sp, #68]	; 0x44
10104a78:	4fb4      	ldr	r7, [pc, #720]	; (10104d4c <CRYPTO_ProcessAD+0x2e0>)
10104a7a:	e847 f700 	tt	r7, r7
10104a7e:	f417 0f80 	tst.w	r7, #4194304	; 0x400000
10104a82:	9200      	str	r2, [sp, #0]
10104a84:	4607      	mov	r7, r0
10104a86:	469a      	mov	sl, r3
10104a88:	bf14      	ite	ne
10104a8a:	46b3      	movne	fp, r6
10104a8c:	46ab      	moveq	fp, r5
10104a8e:	4689      	mov	r9, r1
10104a90:	2900      	cmp	r1, #0
10104a92:	f000 848a 	beq.w	101053aa <CRYPTO_ProcessAD+0x93e>
10104a96:	2f00      	cmp	r7, #0
10104a98:	f000 857f 	beq.w	1010559a <CRYPTO_ProcessAD+0xb2e>
10104a9c:	783b      	ldrb	r3, [r7, #0]
10104a9e:	2b01      	cmp	r3, #1
10104aa0:	d004      	beq.n	10104aac <CRYPTO_ProcessAD+0x40>
10104aa2:	f240 21de 	movw	r1, #734	; 0x2de
10104aa6:	48aa      	ldr	r0, [pc, #680]	; (10104d50 <CRYPTO_ProcessAD+0x2e4>)
10104aa8:	f7fb fee2 	bl	10100870 <io_assert_failed>
10104aac:	4ba9      	ldr	r3, [pc, #676]	; (10104d54 <CRYPTO_ProcessAD+0x2e8>)
10104aae:	4798      	blx	r3
10104ab0:	9a10      	ldr	r2, [sp, #64]	; 0x40
10104ab2:	7a3b      	ldrb	r3, [r7, #8]
10104ab4:	653a      	str	r2, [r7, #80]	; 0x50
10104ab6:	9a00      	ldr	r2, [sp, #0]
10104ab8:	2b01      	cmp	r3, #1
10104aba:	65ba      	str	r2, [r7, #88]	; 0x58
10104abc:	f000 82f0 	beq.w	101050a0 <CRYPTO_ProcessAD+0x634>
10104ac0:	7a7b      	ldrb	r3, [r7, #9]
10104ac2:	2b01      	cmp	r3, #1
10104ac4:	f000 82ec 	beq.w	101050a0 <CRYPTO_ProcessAD+0x634>
10104ac8:	9b00      	ldr	r3, [sp, #0]
10104aca:	f003 010f 	and.w	r1, r3, #15
10104ace:	9b10      	ldr	r3, [sp, #64]	; 0x40
10104ad0:	f003 020f 	and.w	r2, r3, #15
10104ad4:	424b      	negs	r3, r1
10104ad6:	f003 030f 	and.w	r3, r3, #15
10104ada:	65fb      	str	r3, [r7, #92]	; 0x5c
10104adc:	4253      	negs	r3, r2
10104ade:	f003 030f 	and.w	r3, r3, #15
10104ae2:	657b      	str	r3, [r7, #84]	; 0x54
10104ae4:	693b      	ldr	r3, [r7, #16]
10104ae6:	3301      	adds	r3, #1
10104ae8:	61f9      	str	r1, [r7, #28]
10104aea:	623a      	str	r2, [r7, #32]
10104aec:	f000 82ec 	beq.w	101050c8 <CRYPTO_ProcessAD+0x65c>
10104af0:	6b7b      	ldr	r3, [r7, #52]	; 0x34
10104af2:	9a00      	ldr	r2, [sp, #0]
10104af4:	4413      	add	r3, r2
10104af6:	637b      	str	r3, [r7, #52]	; 0x34
10104af8:	6afb      	ldr	r3, [r7, #44]	; 0x2c
10104afa:	2c00      	cmp	r4, #0
10104afc:	f000 84de 	beq.w	101054bc <CRYPTO_ProcessAD+0xa50>
10104b00:	2201      	movs	r2, #1
10104b02:	f04f 46e0 	mov.w	r6, #1879048192	; 0x70000000
10104b06:	f887 2031 	strb.w	r2, [r7, #49]	; 0x31
10104b0a:	4993      	ldr	r1, [pc, #588]	; (10104d58 <CRYPTO_ProcessAD+0x2ec>)
10104b0c:	694a      	ldr	r2, [r1, #20]
10104b0e:	03d0      	lsls	r0, r2, #15
10104b10:	f363 0607 	bfi	r6, r3, #0, #8
10104b14:	d512      	bpl.n	10104b3c <CRYPTO_ProcessAD+0xd0>
10104b16:	3320      	adds	r3, #32
10104b18:	f3bf 8f4f 	dsb	sy
10104b1c:	2b00      	cmp	r3, #0
10104b1e:	bfc8      	it	gt
10104b20:	f024 021f 	bicgt.w	r2, r4, #31
10104b24:	dd06      	ble.n	10104b34 <CRYPTO_ProcessAD+0xc8>
10104b26:	3b20      	subs	r3, #32
10104b28:	2b00      	cmp	r3, #0
10104b2a:	f8c1 225c 	str.w	r2, [r1, #604]	; 0x25c
10104b2e:	f102 0220 	add.w	r2, r2, #32
10104b32:	dcf8      	bgt.n	10104b26 <CRYPTO_ProcessAD+0xba>
10104b34:	f3bf 8f4f 	dsb	sy
10104b38:	f3bf 8f6f 	isb	sy
10104b3c:	4b83      	ldr	r3, [pc, #524]	; (10104d4c <CRYPTO_ProcessAD+0x2e0>)
10104b3e:	e843 f200 	tt	r2, r3
10104b42:	4b81      	ldr	r3, [pc, #516]	; (10104d48 <CRYPTO_ProcessAD+0x2dc>)
10104b44:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104b48:	4d7e      	ldr	r5, [pc, #504]	; (10104d44 <CRYPTO_ProcessAD+0x2d8>)
10104b4a:	bf08      	it	eq
10104b4c:	461d      	moveq	r5, r3
10104b4e:	f505 5380 	add.w	r3, r5, #4096	; 0x1000
10104b52:	681a      	ldr	r2, [r3, #0]
10104b54:	f012 0fff 	tst.w	r2, #255	; 0xff
10104b58:	f8df 820c 	ldr.w	r8, [pc, #524]	; 10104d68 <CRYPTO_ProcessAD+0x2fc>
10104b5c:	f040 8258 	bne.w	10105010 <CRYPTO_ProcessAD+0x5a4>
10104b60:	f8d8 2000 	ldr.w	r2, [r8]
10104b64:	0492      	lsls	r2, r2, #18
10104b66:	d504      	bpl.n	10104b72 <CRYPTO_ProcessAD+0x106>
10104b68:	6819      	ldr	r1, [r3, #0]
10104b6a:	487c      	ldr	r0, [pc, #496]	; (10104d5c <CRYPTO_ProcessAD+0x2f0>)
10104b6c:	b2c9      	uxtb	r1, r1
10104b6e:	f7fb fc41 	bl	101003f4 <DiagPrintf>
10104b72:	f897 3031 	ldrb.w	r3, [r7, #49]	; 0x31
10104b76:	f04f 44c6 	mov.w	r4, #1660944384	; 0x63000000
10104b7a:	b113      	cbz	r3, 10104b82 <CRYPTO_ProcessAD+0x116>
10104b7c:	2301      	movs	r3, #1
10104b7e:	f363 5497 	bfi	r4, r3, #22, #2
10104b82:	6d3e      	ldr	r6, [r7, #80]	; 0x50
10104b84:	f507 7586 	add.w	r5, r7, #268	; 0x10c
10104b88:	4b75      	ldr	r3, [pc, #468]	; (10104d60 <CRYPTO_ProcessAD+0x2f4>)
10104b8a:	4628      	mov	r0, r5
10104b8c:	2220      	movs	r2, #32
10104b8e:	2100      	movs	r1, #0
10104b90:	9601      	str	r6, [sp, #4]
10104b92:	6dbe      	ldr	r6, [r7, #88]	; 0x58
10104b94:	4798      	blx	r3
10104b96:	693b      	ldr	r3, [r7, #16]
10104b98:	3301      	adds	r3, #1
10104b9a:	f000 836b 	beq.w	10105274 <CRYPTO_ProcessAD+0x808>
10104b9e:	f897 310e 	ldrb.w	r3, [r7, #270]	; 0x10e
10104ba2:	f897 2030 	ldrb.w	r2, [r7, #48]	; 0x30
10104ba6:	f003 03a3 	and.w	r3, r3, #163	; 0xa3
10104baa:	f043 0344 	orr.w	r3, r3, #68	; 0x44
10104bae:	f36f 1345 	bfc	r3, #5, #1
10104bb2:	2a01      	cmp	r2, #1
10104bb4:	f887 310e 	strb.w	r3, [r7, #270]	; 0x10e
10104bb8:	f000 839a 	beq.w	101052f0 <CRYPTO_ProcessAD+0x884>
10104bbc:	7d7b      	ldrb	r3, [r7, #21]
10104bbe:	2b00      	cmp	r3, #0
10104bc0:	f000 832f 	beq.w	10105222 <CRYPTO_ProcessAD+0x7b6>
10104bc4:	f897 3113 	ldrb.w	r3, [r7, #275]	; 0x113
10104bc8:	f043 03aa 	orr.w	r3, r3, #170	; 0xaa
10104bcc:	f887 3113 	strb.w	r3, [r7, #275]	; 0x113
10104bd0:	7d3b      	ldrb	r3, [r7, #20]
10104bd2:	2b00      	cmp	r3, #0
10104bd4:	f000 8307 	beq.w	101051e6 <CRYPTO_ProcessAD+0x77a>
10104bd8:	f897 310d 	ldrb.w	r3, [r7, #269]	; 0x10d
10104bdc:	f897 2031 	ldrb.w	r2, [r7, #49]	; 0x31
10104be0:	f043 0320 	orr.w	r3, r3, #32
10104be4:	2a01      	cmp	r2, #1
10104be6:	f887 310d 	strb.w	r3, [r7, #269]	; 0x10d
10104bea:	f000 84ae 	beq.w	1010554a <CRYPTO_ProcessAD+0xade>
10104bee:	f897 310e 	ldrb.w	r3, [r7, #270]	; 0x10e
10104bf2:	f003 03fd 	and.w	r3, r3, #253	; 0xfd
10104bf6:	09b6      	lsrs	r6, r6, #6
10104bf8:	f043 0380 	orr.w	r3, r3, #128	; 0x80
10104bfc:	f8a7 6116 	strh.w	r6, [r7, #278]	; 0x116
10104c00:	f887 310e 	strb.w	r3, [r7, #270]	; 0x10e
10104c04:	2340      	movs	r3, #64	; 0x40
10104c06:	f887 310f 	strb.w	r3, [r7, #271]	; 0x10f
10104c0a:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104c0e:	049e      	lsls	r6, r3, #18
10104c10:	f100 8324 	bmi.w	1010525c <CRYPTO_ProcessAD+0x7f0>
10104c14:	4b4d      	ldr	r3, [pc, #308]	; (10104d4c <CRYPTO_ProcessAD+0x2e0>)
10104c16:	e843 f200 	tt	r2, r3
10104c1a:	4b4b      	ldr	r3, [pc, #300]	; (10104d48 <CRYPTO_ProcessAD+0x2dc>)
10104c1c:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104c20:	4e48      	ldr	r6, [pc, #288]	; (10104d44 <CRYPTO_ProcessAD+0x2d8>)
10104c22:	bf08      	it	eq
10104c24:	461e      	moveq	r6, r3
10104c26:	f44f 1380 	mov.w	r3, #1048576	; 0x100000
10104c2a:	e002      	b.n	10104c32 <CRYPTO_ProcessAD+0x1c6>
10104c2c:	3b01      	subs	r3, #1
10104c2e:	f000 83cc 	beq.w	101053ca <CRYPTO_ProcessAD+0x95e>
10104c32:	6832      	ldr	r2, [r6, #0]
10104c34:	f012 0fff 	tst.w	r2, #255	; 0xff
10104c38:	d0f8      	beq.n	10104c2c <CRYPTO_ProcessAD+0x1c0>
10104c3a:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104c3e:	0498      	lsls	r0, r3, #18
10104c40:	d504      	bpl.n	10104c4c <CRYPTO_ProcessAD+0x1e0>
10104c42:	462a      	mov	r2, r5
10104c44:	4621      	mov	r1, r4
10104c46:	4847      	ldr	r0, [pc, #284]	; (10104d64 <CRYPTO_ProcessAD+0x2f8>)
10104c48:	f7fb fbd4 	bl	101003f4 <DiagPrintf>
10104c4c:	6074      	str	r4, [r6, #4]
10104c4e:	60b5      	str	r5, [r6, #8]
10104c50:	687b      	ldr	r3, [r7, #4]
10104c52:	3301      	adds	r3, #1
10104c54:	d029      	beq.n	10104caa <CRYPTO_ProcessAD+0x23e>
10104c56:	f04f 44c0 	mov.w	r4, #1610612736	; 0x60000000
10104c5a:	6cbe      	ldr	r6, [r7, #72]	; 0x48
10104c5c:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104c60:	08b2      	lsrs	r2, r6, #2
10104c62:	f362 0403 	bfi	r4, r2, #0, #4
10104c66:	049a      	lsls	r2, r3, #18
10104c68:	6cfd      	ldr	r5, [r7, #76]	; 0x4c
10104c6a:	f100 834a 	bmi.w	10105302 <CRYPTO_ProcessAD+0x896>
10104c6e:	4b37      	ldr	r3, [pc, #220]	; (10104d4c <CRYPTO_ProcessAD+0x2e0>)
10104c70:	e843 f200 	tt	r2, r3
10104c74:	4b34      	ldr	r3, [pc, #208]	; (10104d48 <CRYPTO_ProcessAD+0x2dc>)
10104c76:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104c7a:	4e32      	ldr	r6, [pc, #200]	; (10104d44 <CRYPTO_ProcessAD+0x2d8>)
10104c7c:	bf08      	it	eq
10104c7e:	461e      	moveq	r6, r3
10104c80:	f44f 1380 	mov.w	r3, #1048576	; 0x100000
10104c84:	e002      	b.n	10104c8c <CRYPTO_ProcessAD+0x220>
10104c86:	3b01      	subs	r3, #1
10104c88:	f000 83e0 	beq.w	1010544c <CRYPTO_ProcessAD+0x9e0>
10104c8c:	6832      	ldr	r2, [r6, #0]
10104c8e:	f012 0fff 	tst.w	r2, #255	; 0xff
10104c92:	d0f8      	beq.n	10104c86 <CRYPTO_ProcessAD+0x21a>
10104c94:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104c98:	049b      	lsls	r3, r3, #18
10104c9a:	d504      	bpl.n	10104ca6 <CRYPTO_ProcessAD+0x23a>
10104c9c:	462a      	mov	r2, r5
10104c9e:	4621      	mov	r1, r4
10104ca0:	4830      	ldr	r0, [pc, #192]	; (10104d64 <CRYPTO_ProcessAD+0x2f8>)
10104ca2:	f7fb fba7 	bl	101003f4 <DiagPrintf>
10104ca6:	6074      	str	r4, [r6, #4]
10104ca8:	60b5      	str	r5, [r6, #8]
10104caa:	f1ba 0f00 	cmp.w	sl, #0
10104cae:	d02c      	beq.n	10104d0a <CRYPTO_ProcessAD+0x29e>
10104cb0:	9b0e      	ldr	r3, [sp, #56]	; 0x38
10104cb2:	b353      	cbz	r3, 10104d0a <CRYPTO_ProcessAD+0x29e>
10104cb4:	f04f 44c0 	mov.w	r4, #1610612736	; 0x60000000
10104cb8:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104cbc:	9a0e      	ldr	r2, [sp, #56]	; 0x38
10104cbe:	049d      	lsls	r5, r3, #18
10104cc0:	ea4f 0292 	mov.w	r2, r2, lsr #2
10104cc4:	f362 1407 	bfi	r4, r2, #4, #4
10104cc8:	f100 83b4 	bmi.w	10105434 <CRYPTO_ProcessAD+0x9c8>
10104ccc:	4b1f      	ldr	r3, [pc, #124]	; (10104d4c <CRYPTO_ProcessAD+0x2e0>)
10104cce:	e843 f200 	tt	r2, r3
10104cd2:	4b1d      	ldr	r3, [pc, #116]	; (10104d48 <CRYPTO_ProcessAD+0x2dc>)
10104cd4:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104cd8:	4d1a      	ldr	r5, [pc, #104]	; (10104d44 <CRYPTO_ProcessAD+0x2d8>)
10104cda:	bf08      	it	eq
10104cdc:	461d      	moveq	r5, r3
10104cde:	f44f 1380 	mov.w	r3, #1048576	; 0x100000
10104ce2:	e002      	b.n	10104cea <CRYPTO_ProcessAD+0x27e>
10104ce4:	3b01      	subs	r3, #1
10104ce6:	f000 844e 	beq.w	10105586 <CRYPTO_ProcessAD+0xb1a>
10104cea:	682a      	ldr	r2, [r5, #0]
10104cec:	f012 0fff 	tst.w	r2, #255	; 0xff
10104cf0:	d0f8      	beq.n	10104ce4 <CRYPTO_ProcessAD+0x278>
10104cf2:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104cf6:	0498      	lsls	r0, r3, #18
10104cf8:	d504      	bpl.n	10104d04 <CRYPTO_ProcessAD+0x298>
10104cfa:	4652      	mov	r2, sl
10104cfc:	4621      	mov	r1, r4
10104cfe:	4819      	ldr	r0, [pc, #100]	; (10104d64 <CRYPTO_ProcessAD+0x2f8>)
10104d00:	f7fb fb78 	bl	101003f4 <DiagPrintf>
10104d04:	606c      	str	r4, [r5, #4]
10104d06:	f8c5 a008 	str.w	sl, [r5, #8]
10104d0a:	7d3b      	ldrb	r3, [r7, #20]
10104d0c:	2b00      	cmp	r3, #0
10104d0e:	d03f      	beq.n	10104d90 <CRYPTO_ProcessAD+0x324>
10104d10:	f06f 027f 	mvn.w	r2, #127	; 0x7f
10104d14:	f04f 44c0 	mov.w	r4, #1610612736	; 0x60000000
10104d18:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104d1c:	f362 240f 	bfi	r4, r2, #8, #8
10104d20:	049a      	lsls	r2, r3, #18
10104d22:	f107 0568 	add.w	r5, r7, #104	; 0x68
10104d26:	f100 8301 	bmi.w	1010532c <CRYPTO_ProcessAD+0x8c0>
10104d2a:	4b08      	ldr	r3, [pc, #32]	; (10104d4c <CRYPTO_ProcessAD+0x2e0>)
10104d2c:	e843 f200 	tt	r2, r3
10104d30:	4b05      	ldr	r3, [pc, #20]	; (10104d48 <CRYPTO_ProcessAD+0x2dc>)
10104d32:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104d36:	4e03      	ldr	r6, [pc, #12]	; (10104d44 <CRYPTO_ProcessAD+0x2d8>)
10104d38:	bf08      	it	eq
10104d3a:	461e      	moveq	r6, r3
10104d3c:	f44f 1380 	mov.w	r3, #1048576	; 0x100000
10104d40:	e017      	b.n	10104d72 <CRYPTO_ProcessAD+0x306>
10104d42:	bf00      	nop
10104d44:	50022000 	.word	0x50022000
10104d48:	40022000 	.word	0x40022000
10104d4c:	101003f5 	.word	0x101003f5
10104d50:	101d52fc 	.word	0x101d52fc
10104d54:	101047f9 	.word	0x101047f9
10104d58:	e000ed00 	.word	0xe000ed00
10104d5c:	101d49e0 	.word	0x101d49e0
10104d60:	10106e89 	.word	0x10106e89
10104d64:	101d4a78 	.word	0x101d4a78
10104d68:	1000000c 	.word	0x1000000c
10104d6c:	3b01      	subs	r3, #1
10104d6e:	f000 83e3 	beq.w	10105538 <CRYPTO_ProcessAD+0xacc>
10104d72:	6832      	ldr	r2, [r6, #0]
10104d74:	f012 0fff 	tst.w	r2, #255	; 0xff
10104d78:	d0f8      	beq.n	10104d6c <CRYPTO_ProcessAD+0x300>
10104d7a:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104d7e:	049b      	lsls	r3, r3, #18
10104d80:	d504      	bpl.n	10104d8c <CRYPTO_ProcessAD+0x320>
10104d82:	462a      	mov	r2, r5
10104d84:	4621      	mov	r1, r4
10104d86:	48ba      	ldr	r0, [pc, #744]	; (10105070 <CRYPTO_ProcessAD+0x604>)
10104d88:	f7fb fb34 	bl	101003f4 <DiagPrintf>
10104d8c:	6074      	str	r4, [r6, #4]
10104d8e:	60b5      	str	r5, [r6, #8]
10104d90:	9b0f      	ldr	r3, [sp, #60]	; 0x3c
10104d92:	f04f 4580 	mov.w	r5, #1073741824	; 0x40000000
10104d96:	2b00      	cmp	r3, #0
10104d98:	f000 8099 	beq.w	10104ece <CRYPTO_ProcessAD+0x462>
10104d9c:	9b10      	ldr	r3, [sp, #64]	; 0x40
10104d9e:	2b10      	cmp	r3, #16
10104da0:	f240 8402 	bls.w	101055a8 <CRYPTO_ProcessAD+0xb3c>
10104da4:	461e      	mov	r6, r3
10104da6:	9c0f      	ldr	r4, [sp, #60]	; 0x3c
10104da8:	f04f 0a10 	mov.w	sl, #16
10104dac:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104db0:	0498      	lsls	r0, r3, #18
10104db2:	f36a 250c 	bfi	r5, sl, #8, #5
10104db6:	f100 813b 	bmi.w	10105030 <CRYPTO_ProcessAD+0x5c4>
10104dba:	4bae      	ldr	r3, [pc, #696]	; (10105074 <CRYPTO_ProcessAD+0x608>)
10104dbc:	e843 f100 	tt	r1, r3
10104dc0:	4aad      	ldr	r2, [pc, #692]	; (10105078 <CRYPTO_ProcessAD+0x60c>)
10104dc2:	4bae      	ldr	r3, [pc, #696]	; (1010507c <CRYPTO_ProcessAD+0x610>)
10104dc4:	f411 0f80 	tst.w	r1, #4194304	; 0x400000
10104dc8:	bf0c      	ite	eq
10104dca:	469a      	moveq	sl, r3
10104dcc:	4692      	movne	sl, r2
10104dce:	f44f 1380 	mov.w	r3, #1048576	; 0x100000
10104dd2:	e002      	b.n	10104dda <CRYPTO_ProcessAD+0x36e>
10104dd4:	3b01      	subs	r3, #1
10104dd6:	f000 8142 	beq.w	1010505e <CRYPTO_ProcessAD+0x5f2>
10104dda:	f8da 2000 	ldr.w	r2, [sl]
10104dde:	f012 0fff 	tst.w	r2, #255	; 0xff
10104de2:	d0f7      	beq.n	10104dd4 <CRYPTO_ProcessAD+0x368>
10104de4:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104de8:	0499      	lsls	r1, r3, #18
10104dea:	d504      	bpl.n	10104df6 <CRYPTO_ProcessAD+0x38a>
10104dec:	4622      	mov	r2, r4
10104dee:	4629      	mov	r1, r5
10104df0:	489f      	ldr	r0, [pc, #636]	; (10105070 <CRYPTO_ProcessAD+0x604>)
10104df2:	f7fb faff 	bl	101003f4 <DiagPrintf>
10104df6:	f8ca 5004 	str.w	r5, [sl, #4]
10104dfa:	f8ca 4008 	str.w	r4, [sl, #8]
10104dfe:	3e10      	subs	r6, #16
10104e00:	2e10      	cmp	r6, #16
10104e02:	f104 0410 	add.w	r4, r4, #16
10104e06:	f04f 4580 	mov.w	r5, #1073741824	; 0x40000000
10104e0a:	d8cd      	bhi.n	10104da8 <CRYPTO_ProcessAD+0x33c>
10104e0c:	9b10      	ldr	r3, [sp, #64]	; 0x40
10104e0e:	9a10      	ldr	r2, [sp, #64]	; 0x40
10104e10:	3b11      	subs	r3, #17
10104e12:	091b      	lsrs	r3, r3, #4
10104e14:	f1a2 0410 	sub.w	r4, r2, #16
10104e18:	ebc3 7203 	rsb	r2, r3, r3, lsl #28
10104e1c:	eb04 1402 	add.w	r4, r4, r2, lsl #4
10104e20:	9a0f      	ldr	r2, [sp, #60]	; 0x3c
10104e22:	3301      	adds	r3, #1
10104e24:	eb02 1303 	add.w	r3, r2, r3, lsl #4
10104e28:	930f      	str	r3, [sp, #60]	; 0x3c
10104e2a:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104e2e:	049b      	lsls	r3, r3, #18
10104e30:	f364 250c 	bfi	r5, r4, #8, #5
10104e34:	f100 8313 	bmi.w	1010545e <CRYPTO_ProcessAD+0x9f2>
10104e38:	4b8e      	ldr	r3, [pc, #568]	; (10105074 <CRYPTO_ProcessAD+0x608>)
10104e3a:	e843 f200 	tt	r2, r3
10104e3e:	4b8f      	ldr	r3, [pc, #572]	; (1010507c <CRYPTO_ProcessAD+0x610>)
10104e40:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104e44:	4c8c      	ldr	r4, [pc, #560]	; (10105078 <CRYPTO_ProcessAD+0x60c>)
10104e46:	bf08      	it	eq
10104e48:	461c      	moveq	r4, r3
10104e4a:	f44f 1380 	mov.w	r3, #1048576	; 0x100000
10104e4e:	e002      	b.n	10104e56 <CRYPTO_ProcessAD+0x3ea>
10104e50:	3b01      	subs	r3, #1
10104e52:	f000 83b8 	beq.w	101055c6 <CRYPTO_ProcessAD+0xb5a>
10104e56:	6822      	ldr	r2, [r4, #0]
10104e58:	f012 0fff 	tst.w	r2, #255	; 0xff
10104e5c:	d0f8      	beq.n	10104e50 <CRYPTO_ProcessAD+0x3e4>
10104e5e:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104e62:	049e      	lsls	r6, r3, #18
10104e64:	d504      	bpl.n	10104e70 <CRYPTO_ProcessAD+0x404>
10104e66:	9a0f      	ldr	r2, [sp, #60]	; 0x3c
10104e68:	4629      	mov	r1, r5
10104e6a:	4881      	ldr	r0, [pc, #516]	; (10105070 <CRYPTO_ProcessAD+0x604>)
10104e6c:	f7fb fac2 	bl	101003f4 <DiagPrintf>
10104e70:	9b0f      	ldr	r3, [sp, #60]	; 0x3c
10104e72:	6065      	str	r5, [r4, #4]
10104e74:	60a3      	str	r3, [r4, #8]
10104e76:	f04f 4580 	mov.w	r5, #1073741824	; 0x40000000
10104e7a:	6d7b      	ldr	r3, [r7, #84]	; 0x54
10104e7c:	b33b      	cbz	r3, 10104ece <CRYPTO_ProcessAD+0x462>
10104e7e:	f8d8 2008 	ldr.w	r2, [r8, #8]
10104e82:	0494      	lsls	r4, r2, #18
10104e84:	f363 250c 	bfi	r5, r3, #8, #5
10104e88:	f100 8300 	bmi.w	1010548c <CRYPTO_ProcessAD+0xa20>
10104e8c:	4b79      	ldr	r3, [pc, #484]	; (10105074 <CRYPTO_ProcessAD+0x608>)
10104e8e:	e843 f200 	tt	r2, r3
10104e92:	4b7a      	ldr	r3, [pc, #488]	; (1010507c <CRYPTO_ProcessAD+0x610>)
10104e94:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104e98:	4c77      	ldr	r4, [pc, #476]	; (10105078 <CRYPTO_ProcessAD+0x60c>)
10104e9a:	4e79      	ldr	r6, [pc, #484]	; (10105080 <CRYPTO_ProcessAD+0x614>)
10104e9c:	bf08      	it	eq
10104e9e:	461c      	moveq	r4, r3
10104ea0:	f44f 1380 	mov.w	r3, #1048576	; 0x100000
10104ea4:	e002      	b.n	10104eac <CRYPTO_ProcessAD+0x440>
10104ea6:	3b01      	subs	r3, #1
10104ea8:	f000 8384 	beq.w	101055b4 <CRYPTO_ProcessAD+0xb48>
10104eac:	6822      	ldr	r2, [r4, #0]
10104eae:	f012 0fff 	tst.w	r2, #255	; 0xff
10104eb2:	d0f8      	beq.n	10104ea6 <CRYPTO_ProcessAD+0x43a>
10104eb4:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104eb8:	0498      	lsls	r0, r3, #18
10104eba:	d504      	bpl.n	10104ec6 <CRYPTO_ProcessAD+0x45a>
10104ebc:	4632      	mov	r2, r6
10104ebe:	4629      	mov	r1, r5
10104ec0:	486b      	ldr	r0, [pc, #428]	; (10105070 <CRYPTO_ProcessAD+0x604>)
10104ec2:	f7fb fa97 	bl	101003f4 <DiagPrintf>
10104ec6:	6065      	str	r5, [r4, #4]
10104ec8:	60a6      	str	r6, [r4, #8]
10104eca:	f04f 4580 	mov.w	r5, #1073741824	; 0x40000000
10104ece:	f643 7af0 	movw	sl, #16368	; 0x3ff0
10104ed2:	9e00      	ldr	r6, [sp, #0]
10104ed4:	4556      	cmp	r6, sl
10104ed6:	f240 8354 	bls.w	10105582 <CRYPTO_ProcessAD+0xb16>
10104eda:	464a      	mov	r2, r9
10104edc:	46b9      	mov	r9, r7
10104ede:	4617      	mov	r7, r2
10104ee0:	4b65      	ldr	r3, [pc, #404]	; (10105078 <CRYPTO_ProcessAD+0x60c>)
10104ee2:	4a64      	ldr	r2, [pc, #400]	; (10105074 <CRYPTO_ProcessAD+0x608>)
10104ee4:	e842 f200 	tt	r2, r2
10104ee8:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104eec:	4a63      	ldr	r2, [pc, #396]	; (1010507c <CRYPTO_ProcessAD+0x610>)
10104eee:	bf14      	ite	ne
10104ef0:	461c      	movne	r4, r3
10104ef2:	4614      	moveq	r4, r2
10104ef4:	f36a 359b 	bfi	r5, sl, #14, #14
10104ef8:	f44f 1280 	mov.w	r2, #1048576	; 0x100000
10104efc:	e002      	b.n	10104f04 <CRYPTO_ProcessAD+0x498>
10104efe:	3a01      	subs	r2, #1
10104f00:	f000 80a2 	beq.w	10105048 <CRYPTO_ProcessAD+0x5dc>
10104f04:	6821      	ldr	r1, [r4, #0]
10104f06:	f011 0fff 	tst.w	r1, #255	; 0xff
10104f0a:	d0f8      	beq.n	10104efe <CRYPTO_ProcessAD+0x492>
10104f0c:	f8d8 2008 	ldr.w	r2, [r8, #8]
10104f10:	0492      	lsls	r2, r2, #18
10104f12:	d506      	bpl.n	10104f22 <CRYPTO_ProcessAD+0x4b6>
10104f14:	463a      	mov	r2, r7
10104f16:	4629      	mov	r1, r5
10104f18:	4855      	ldr	r0, [pc, #340]	; (10105070 <CRYPTO_ProcessAD+0x604>)
10104f1a:	9300      	str	r3, [sp, #0]
10104f1c:	f7fb fa6a 	bl	101003f4 <DiagPrintf>
10104f20:	9b00      	ldr	r3, [sp, #0]
10104f22:	6065      	str	r5, [r4, #4]
10104f24:	60a7      	str	r7, [r4, #8]
10104f26:	f5a6 567f 	sub.w	r6, r6, #16320	; 0x3fc0
10104f2a:	3e30      	subs	r6, #48	; 0x30
10104f2c:	4556      	cmp	r6, sl
10104f2e:	4457      	add	r7, sl
10104f30:	f04f 4580 	mov.w	r5, #1073741824	; 0x40000000
10104f34:	d8d5      	bhi.n	10104ee2 <CRYPTO_ProcessAD+0x476>
10104f36:	463b      	mov	r3, r7
10104f38:	464f      	mov	r7, r9
10104f3a:	4699      	mov	r9, r3
10104f3c:	6dfb      	ldr	r3, [r7, #92]	; 0x5c
10104f3e:	2b00      	cmp	r3, #0
10104f40:	bf08      	it	eq
10104f42:	f04f 45a0 	moveq.w	r5, #1342177280	; 0x50000000
10104f46:	4b4d      	ldr	r3, [pc, #308]	; (1010507c <CRYPTO_ProcessAD+0x610>)
10104f48:	4a4a      	ldr	r2, [pc, #296]	; (10105074 <CRYPTO_ProcessAD+0x608>)
10104f4a:	e842 f200 	tt	r2, r2
10104f4e:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104f52:	4c49      	ldr	r4, [pc, #292]	; (10105078 <CRYPTO_ProcessAD+0x60c>)
10104f54:	f366 359b 	bfi	r5, r6, #14, #14
10104f58:	bf08      	it	eq
10104f5a:	461c      	moveq	r4, r3
10104f5c:	f44f 1380 	mov.w	r3, #1048576	; 0x100000
10104f60:	e002      	b.n	10104f68 <CRYPTO_ProcessAD+0x4fc>
10104f62:	3b01      	subs	r3, #1
10104f64:	f000 8228 	beq.w	101053b8 <CRYPTO_ProcessAD+0x94c>
10104f68:	6822      	ldr	r2, [r4, #0]
10104f6a:	f012 0fff 	tst.w	r2, #255	; 0xff
10104f6e:	d0f8      	beq.n	10104f62 <CRYPTO_ProcessAD+0x4f6>
10104f70:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104f74:	0498      	lsls	r0, r3, #18
10104f76:	d504      	bpl.n	10104f82 <CRYPTO_ProcessAD+0x516>
10104f78:	464a      	mov	r2, r9
10104f7a:	4629      	mov	r1, r5
10104f7c:	483c      	ldr	r0, [pc, #240]	; (10105070 <CRYPTO_ProcessAD+0x604>)
10104f7e:	f7fb fa39 	bl	101003f4 <DiagPrintf>
10104f82:	6065      	str	r5, [r4, #4]
10104f84:	f8c4 9008 	str.w	r9, [r4, #8]
10104f88:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104f8c:	049a      	lsls	r2, r3, #18
10104f8e:	f100 8159 	bmi.w	10105244 <CRYPTO_ProcessAD+0x7d8>
10104f92:	6dfb      	ldr	r3, [r7, #92]	; 0x5c
10104f94:	b343      	cbz	r3, 10104fe8 <CRYPTO_ProcessAD+0x57c>
10104f96:	f3c3 040d 	ubfx	r4, r3, #0, #14
10104f9a:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104f9e:	03a5      	lsls	r5, r4, #14
10104fa0:	049b      	lsls	r3, r3, #18
10104fa2:	f045 45a0 	orr.w	r5, r5, #1342177280	; 0x50000000
10104fa6:	f100 8239 	bmi.w	1010541c <CRYPTO_ProcessAD+0x9b0>
10104faa:	4b32      	ldr	r3, [pc, #200]	; (10105074 <CRYPTO_ProcessAD+0x608>)
10104fac:	e843 f200 	tt	r2, r3
10104fb0:	4b32      	ldr	r3, [pc, #200]	; (1010507c <CRYPTO_ProcessAD+0x610>)
10104fb2:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
10104fb6:	4c30      	ldr	r4, [pc, #192]	; (10105078 <CRYPTO_ProcessAD+0x60c>)
10104fb8:	4e31      	ldr	r6, [pc, #196]	; (10105080 <CRYPTO_ProcessAD+0x614>)
10104fba:	bf08      	it	eq
10104fbc:	461c      	moveq	r4, r3
10104fbe:	f44f 1380 	mov.w	r3, #1048576	; 0x100000
10104fc2:	e002      	b.n	10104fca <CRYPTO_ProcessAD+0x55e>
10104fc4:	3b01      	subs	r3, #1
10104fc6:	f000 82d3 	beq.w	10105570 <CRYPTO_ProcessAD+0xb04>
10104fca:	6822      	ldr	r2, [r4, #0]
10104fcc:	f012 0fff 	tst.w	r2, #255	; 0xff
10104fd0:	d0f8      	beq.n	10104fc4 <CRYPTO_ProcessAD+0x558>
10104fd2:	f8d8 3008 	ldr.w	r3, [r8, #8]
10104fd6:	049f      	lsls	r7, r3, #18
10104fd8:	d504      	bpl.n	10104fe4 <CRYPTO_ProcessAD+0x578>
10104fda:	4632      	mov	r2, r6
10104fdc:	4629      	mov	r1, r5
10104fde:	4824      	ldr	r0, [pc, #144]	; (10105070 <CRYPTO_ProcessAD+0x604>)
10104fe0:	f7fb fa08 	bl	101003f4 <DiagPrintf>
10104fe4:	6065      	str	r5, [r4, #4]
10104fe6:	60a6      	str	r6, [r4, #8]
10104fe8:	4b26      	ldr	r3, [pc, #152]	; (10105084 <CRYPTO_ProcessAD+0x618>)
10104fea:	e009      	b.n	10105000 <CRYPTO_ProcessAD+0x594>
10104fec:	f8db 201c 	ldr.w	r2, [fp, #28]
10104ff0:	9203      	str	r2, [sp, #12]
10104ff2:	9a03      	ldr	r2, [sp, #12]
10104ff4:	2a00      	cmp	r2, #0
10104ff6:	f040 80ec 	bne.w	101051d2 <CRYPTO_ProcessAD+0x766>
10104ffa:	3b01      	subs	r3, #1
10104ffc:	f000 823b 	beq.w	10105476 <CRYPTO_ProcessAD+0xa0a>
10105000:	f8db 2010 	ldr.w	r2, [fp, #16]
10105004:	06d1      	lsls	r1, r2, #27
10105006:	d5f1      	bpl.n	10104fec <CRYPTO_ProcessAD+0x580>
10105008:	2000      	movs	r0, #0
1010500a:	b005      	add	sp, #20
1010500c:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10105010:	f8d8 3008 	ldr.w	r3, [r8, #8]
10105014:	0499      	lsls	r1, r3, #18
10105016:	d504      	bpl.n	10105022 <CRYPTO_ProcessAD+0x5b6>
10105018:	4622      	mov	r2, r4
1010501a:	4631      	mov	r1, r6
1010501c:	481a      	ldr	r0, [pc, #104]	; (10105088 <CRYPTO_ProcessAD+0x61c>)
1010501e:	f7fb f9e9 	bl	101003f4 <DiagPrintf>
10105022:	f241 0204 	movw	r2, #4100	; 0x1004
10105026:	f241 0308 	movw	r3, #4104	; 0x1008
1010502a:	50ae      	str	r6, [r5, r2]
1010502c:	50ec      	str	r4, [r5, r3]
1010502e:	e5a0      	b.n	10104b72 <CRYPTO_ProcessAD+0x106>
10105030:	4653      	mov	r3, sl
10105032:	4622      	mov	r2, r4
10105034:	4915      	ldr	r1, [pc, #84]	; (1010508c <CRYPTO_ProcessAD+0x620>)
10105036:	4816      	ldr	r0, [pc, #88]	; (10105090 <CRYPTO_ProcessAD+0x624>)
10105038:	f7fb f9dc 	bl	101003f4 <DiagPrintf>
1010503c:	4a15      	ldr	r2, [pc, #84]	; (10105094 <CRYPTO_ProcessAD+0x628>)
1010503e:	4651      	mov	r1, sl
10105040:	4620      	mov	r0, r4
10105042:	4b15      	ldr	r3, [pc, #84]	; (10105098 <CRYPTO_ProcessAD+0x62c>)
10105044:	4798      	blx	r3
10105046:	e6b8      	b.n	10104dba <CRYPTO_ProcessAD+0x34e>
10105048:	f8d8 2000 	ldr.w	r2, [r8]
1010504c:	0495      	lsls	r5, r2, #18
1010504e:	f57f af6a 	bpl.w	10104f26 <CRYPTO_ProcessAD+0x4ba>
10105052:	4812      	ldr	r0, [pc, #72]	; (1010509c <CRYPTO_ProcessAD+0x630>)
10105054:	9300      	str	r3, [sp, #0]
10105056:	f7fb f9cd 	bl	101003f4 <DiagPrintf>
1010505a:	9b00      	ldr	r3, [sp, #0]
1010505c:	e763      	b.n	10104f26 <CRYPTO_ProcessAD+0x4ba>
1010505e:	f8d8 3000 	ldr.w	r3, [r8]
10105062:	049a      	lsls	r2, r3, #18
10105064:	f57f aecb 	bpl.w	10104dfe <CRYPTO_ProcessAD+0x392>
10105068:	480c      	ldr	r0, [pc, #48]	; (1010509c <CRYPTO_ProcessAD+0x630>)
1010506a:	f7fb f9c3 	bl	101003f4 <DiagPrintf>
1010506e:	e6c6      	b.n	10104dfe <CRYPTO_ProcessAD+0x392>
10105070:	101d4a78 	.word	0x101d4a78
10105074:	101003f5 	.word	0x101003f5
10105078:	50022000 	.word	0x50022000
1010507c:	40022000 	.word	0x40022000
10105080:	10000520 	.word	0x10000520
10105084:	000f4240 	.word	0x000f4240
10105088:	101d49ac 	.word	0x101d49ac
1010508c:	101d4a20 	.word	0x101d4a20
10105090:	101d4a38 	.word	0x101d4a38
10105094:	101d4afc 	.word	0x101d4afc
10105098:	10104539 	.word	0x10104539
1010509c:	101d4aac 	.word	0x101d4aac
101050a0:	9b00      	ldr	r3, [sp, #0]
101050a2:	f003 0107 	and.w	r1, r3, #7
101050a6:	9b10      	ldr	r3, [sp, #64]	; 0x40
101050a8:	f003 0207 	and.w	r2, r3, #7
101050ac:	424b      	negs	r3, r1
101050ae:	f003 0307 	and.w	r3, r3, #7
101050b2:	65fb      	str	r3, [r7, #92]	; 0x5c
101050b4:	4253      	negs	r3, r2
101050b6:	f003 0307 	and.w	r3, r3, #7
101050ba:	657b      	str	r3, [r7, #84]	; 0x54
101050bc:	693b      	ldr	r3, [r7, #16]
101050be:	3301      	adds	r3, #1
101050c0:	61f9      	str	r1, [r7, #28]
101050c2:	623a      	str	r2, [r7, #32]
101050c4:	f47f ad14 	bne.w	10104af0 <CRYPTO_ProcessAD+0x84>
101050c8:	2c00      	cmp	r4, #0
101050ca:	f000 81f3 	beq.w	101054b4 <CRYPTO_ProcessAD+0xa48>
101050ce:	f04f 46d0 	mov.w	r6, #1744830464	; 0x68000000
101050d2:	6dbb      	ldr	r3, [r7, #88]	; 0x58
101050d4:	9a12      	ldr	r2, [sp, #72]	; 0x48
101050d6:	f363 0617 	bfi	r6, r3, #0, #24
101050da:	2a00      	cmp	r2, #0
101050dc:	f000 829a 	beq.w	10105614 <CRYPTO_ProcessAD+0xba8>
101050e0:	49be      	ldr	r1, [pc, #760]	; (101053dc <CRYPTO_ProcessAD+0x970>)
101050e2:	694a      	ldr	r2, [r1, #20]
101050e4:	03d2      	lsls	r2, r2, #15
101050e6:	d512      	bpl.n	1010510e <CRYPTO_ProcessAD+0x6a2>
101050e8:	3320      	adds	r3, #32
101050ea:	f3bf 8f4f 	dsb	sy
101050ee:	2b00      	cmp	r3, #0
101050f0:	bfc8      	it	gt
101050f2:	f024 021f 	bicgt.w	r2, r4, #31
101050f6:	dd06      	ble.n	10105106 <CRYPTO_ProcessAD+0x69a>
101050f8:	3b20      	subs	r3, #32
101050fa:	2b00      	cmp	r3, #0
101050fc:	f8c1 225c 	str.w	r2, [r1, #604]	; 0x25c
10105100:	f102 0220 	add.w	r2, r2, #32
10105104:	dcf8      	bgt.n	101050f8 <CRYPTO_ProcessAD+0x68c>
10105106:	f3bf 8f4f 	dsb	sy
1010510a:	f3bf 8f6f 	isb	sy
1010510e:	4bb4      	ldr	r3, [pc, #720]	; (101053e0 <CRYPTO_ProcessAD+0x974>)
10105110:	e843 f200 	tt	r2, r3
10105114:	4bb3      	ldr	r3, [pc, #716]	; (101053e4 <CRYPTO_ProcessAD+0x978>)
10105116:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
1010511a:	4db3      	ldr	r5, [pc, #716]	; (101053e8 <CRYPTO_ProcessAD+0x97c>)
1010511c:	bf08      	it	eq
1010511e:	461d      	moveq	r5, r3
10105120:	f505 5380 	add.w	r3, r5, #4096	; 0x1000
10105124:	681a      	ldr	r2, [r3, #0]
10105126:	f012 0fff 	tst.w	r2, #255	; 0xff
1010512a:	f8df 82ec 	ldr.w	r8, [pc, #748]	; 10105418 <CRYPTO_ProcessAD+0x9ac>
1010512e:	f000 8131 	beq.w	10105394 <CRYPTO_ProcessAD+0x928>
10105132:	f8d8 3008 	ldr.w	r3, [r8, #8]
10105136:	049b      	lsls	r3, r3, #18
10105138:	d504      	bpl.n	10105144 <CRYPTO_ProcessAD+0x6d8>
1010513a:	4622      	mov	r2, r4
1010513c:	4631      	mov	r1, r6
1010513e:	48ab      	ldr	r0, [pc, #684]	; (101053ec <CRYPTO_ProcessAD+0x980>)
10105140:	f7fb f958 	bl	101003f4 <DiagPrintf>
10105144:	f241 0204 	movw	r2, #4100	; 0x1004
10105148:	f241 0308 	movw	r3, #4104	; 0x1008
1010514c:	50ae      	str	r6, [r5, r2]
1010514e:	50ec      	str	r4, [r5, r3]
10105150:	9b12      	ldr	r3, [sp, #72]	; 0x48
10105152:	2b00      	cmp	r3, #0
10105154:	f43f ad0d 	beq.w	10104b72 <CRYPTO_ProcessAD+0x106>
10105158:	f04f 4580 	mov.w	r5, #1073741824	; 0x40000000
1010515c:	2310      	movs	r3, #16
1010515e:	f36f 65db 	bfc	r5, #27, #1
10105162:	f363 0507 	bfi	r5, r3, #0, #8
10105166:	f045 5580 	orr.w	r5, r5, #268435456	; 0x10000000
1010516a:	4b9c      	ldr	r3, [pc, #624]	; (101053dc <CRYPTO_ProcessAD+0x970>)
1010516c:	695a      	ldr	r2, [r3, #20]
1010516e:	03d0      	lsls	r0, r2, #15
10105170:	d50e      	bpl.n	10105190 <CRYPTO_ProcessAD+0x724>
10105172:	9a12      	ldr	r2, [sp, #72]	; 0x48
10105174:	f022 021f 	bic.w	r2, r2, #31
10105178:	f3bf 8f4f 	dsb	sy
1010517c:	f102 0120 	add.w	r1, r2, #32
10105180:	f8c3 225c 	str.w	r2, [r3, #604]	; 0x25c
10105184:	f8c3 125c 	str.w	r1, [r3, #604]	; 0x25c
10105188:	f3bf 8f4f 	dsb	sy
1010518c:	f3bf 8f6f 	isb	sy
10105190:	4b93      	ldr	r3, [pc, #588]	; (101053e0 <CRYPTO_ProcessAD+0x974>)
10105192:	e843 f200 	tt	r2, r3
10105196:	4b93      	ldr	r3, [pc, #588]	; (101053e4 <CRYPTO_ProcessAD+0x978>)
10105198:	f412 0f80 	tst.w	r2, #4194304	; 0x400000
1010519c:	4c92      	ldr	r4, [pc, #584]	; (101053e8 <CRYPTO_ProcessAD+0x97c>)
1010519e:	bf08      	it	eq
101051a0:	461c      	moveq	r4, r3
101051a2:	f504 5380 	add.w	r3, r4, #4096	; 0x1000
101051a6:	681a      	ldr	r2, [r3, #0]
101051a8:	f012 0fff 	tst.w	r2, #255	; 0xff
101051ac:	f43f acd8 	beq.w	10104b60 <CRYPTO_ProcessAD+0xf4>
101051b0:	f8d8 3008 	ldr.w	r3, [r8, #8]
101051b4:	0499      	lsls	r1, r3, #18
101051b6:	d504      	bpl.n	101051c2 <CRYPTO_ProcessAD+0x756>
101051b8:	9a12      	ldr	r2, [sp, #72]	; 0x48
101051ba:	4629      	mov	r1, r5
101051bc:	488b      	ldr	r0, [pc, #556]	; (101053ec <CRYPTO_ProcessAD+0x980>)
101051be:	f7fb f919 	bl	101003f4 <DiagPrintf>
101051c2:	f241 0204 	movw	r2, #4100	; 0x1004
101051c6:	f241 0308 	movw	r3, #4104	; 0x1008
101051ca:	50a5      	str	r5, [r4, r2]
101051cc:	9a12      	ldr	r2, [sp, #72]	; 0x48
101051ce:	50e2      	str	r2, [r4, r3]
101051d0:	e4cf      	b.n	10104b72 <CRYPTO_ProcessAD+0x106>
101051d2:	f8d8 3000 	ldr.w	r3, [r8]
101051d6:	049a      	lsls	r2, r3, #18
101051d8:	f100 8163 	bmi.w	101054a2 <CRYPTO_ProcessAD+0xa36>
101051dc:	f04f 30ff 	mov.w	r0, #4294967295
101051e0:	b005      	add	sp, #20
101051e2:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
101051e6:	f897 3031 	ldrb.w	r3, [r7, #49]	; 0x31
101051ea:	2b01      	cmp	r3, #1
101051ec:	f47f acff 	bne.w	10104bee <CRYPTO_ProcessAD+0x182>
101051f0:	69fb      	ldr	r3, [r7, #28]
101051f2:	f897 1110 	ldrb.w	r1, [r7, #272]	; 0x110
101051f6:	f363 1107 	bfi	r1, r3, #4, #4
101051fa:	6b7b      	ldr	r3, [r7, #52]	; 0x34
101051fc:	f106 020f 	add.w	r2, r6, #15
10105200:	0912      	lsrs	r2, r2, #4
10105202:	00db      	lsls	r3, r3, #3
10105204:	f8a7 2116 	strh.w	r2, [r7, #278]	; 0x116
10105208:	f887 1110 	strb.w	r1, [r7, #272]	; 0x110
1010520c:	f8c7 3118 	str.w	r3, [r7, #280]	; 0x118
10105210:	f897 310e 	ldrb.w	r3, [r7, #270]	; 0x10e
10105214:	f043 0302 	orr.w	r3, r3, #2
10105218:	f36f 13c7 	bfc	r3, #7, #1
1010521c:	f887 310e 	strb.w	r3, [r7, #270]	; 0x10e
10105220:	e4f0      	b.n	10104c04 <CRYPTO_ProcessAD+0x198>
10105222:	7dbb      	ldrb	r3, [r7, #22]
10105224:	2b00      	cmp	r3, #0
10105226:	d078      	beq.n	1010531a <CRYPTO_ProcessAD+0x8ae>
10105228:	2101      	movs	r1, #1
1010522a:	f8d7 210c 	ldr.w	r2, [r7, #268]	; 0x10c
1010522e:	f897 3113 	ldrb.w	r3, [r7, #275]	; 0x113
10105232:	f361 3290 	bfi	r2, r1, #14, #3
10105236:	f043 0302 	orr.w	r3, r3, #2
1010523a:	f8c7 210c 	str.w	r2, [r7, #268]	; 0x10c
1010523e:	f887 3113 	strb.w	r3, [r7, #275]	; 0x113
10105242:	e4c5      	b.n	10104bd0 <CRYPTO_ProcessAD+0x164>
10105244:	4633      	mov	r3, r6
10105246:	464a      	mov	r2, r9
10105248:	4969      	ldr	r1, [pc, #420]	; (101053f0 <CRYPTO_ProcessAD+0x984>)
1010524a:	486a      	ldr	r0, [pc, #424]	; (101053f4 <CRYPTO_ProcessAD+0x988>)
1010524c:	f7fb f8d2 	bl	101003f4 <DiagPrintf>
10105250:	4631      	mov	r1, r6
10105252:	4648      	mov	r0, r9
10105254:	4a68      	ldr	r2, [pc, #416]	; (101053f8 <CRYPTO_ProcessAD+0x98c>)
10105256:	4b69      	ldr	r3, [pc, #420]	; (101053fc <CRYPTO_ProcessAD+0x990>)
10105258:	4798      	blx	r3
1010525a:	e69a      	b.n	10104f92 <CRYPTO_ProcessAD+0x526>
1010525c:	462a      	mov	r2, r5
1010525e:	2320      	movs	r3, #32
10105260:	4963      	ldr	r1, [pc, #396]	; (101053f0 <CRYPTO_ProcessAD+0x984>)
10105262:	4864      	ldr	r0, [pc, #400]	; (101053f4 <CRYPTO_ProcessAD+0x988>)
10105264:	f7fb f8c6 	bl	101003f4 <DiagPrintf>
10105268:	4a65      	ldr	r2, [pc, #404]	; (10105400 <CRYPTO_ProcessAD+0x994>)
1010526a:	2120      	movs	r1, #32
1010526c:	4628      	mov	r0, r5
1010526e:	4b63      	ldr	r3, [pc, #396]	; (101053fc <CRYPTO_ProcessAD+0x990>)
10105270:	4798      	blx	r3
10105272:	e4cf      	b.n	10104c14 <CRYPTO_ProcessAD+0x1a8>
10105274:	f897 210c 	ldrb.w	r2, [r7, #268]	; 0x10c
10105278:	687b      	ldr	r3, [r7, #4]
1010527a:	7ab9      	ldrb	r1, [r7, #10]
1010527c:	f363 0203 	bfi	r2, r3, #0, #4
10105280:	f887 210c 	strb.w	r2, [r7, #268]	; 0x10c
10105284:	2900      	cmp	r1, #0
10105286:	d05d      	beq.n	10105344 <CRYPTO_ProcessAD+0x8d8>
10105288:	b2d1      	uxtb	r1, r2
1010528a:	6cba      	ldr	r2, [r7, #72]	; 0x48
1010528c:	f36f 1105 	bfc	r1, #4, #2
10105290:	2a18      	cmp	r2, #24
10105292:	f887 110c 	strb.w	r1, [r7, #268]	; 0x10c
10105296:	f000 81cc 	beq.w	10105632 <CRYPTO_ProcessAD+0xbc6>
1010529a:	2a20      	cmp	r2, #32
1010529c:	f000 81b2 	beq.w	10105604 <CRYPTO_ProcessAD+0xb98>
101052a0:	2a10      	cmp	r2, #16
101052a2:	d105      	bne.n	101052b0 <CRYPTO_ProcessAD+0x844>
101052a4:	f897 210d 	ldrb.w	r2, [r7, #269]	; 0x10d
101052a8:	f36f 0201 	bfc	r2, #0, #2
101052ac:	f887 210d 	strb.w	r2, [r7, #269]	; 0x10d
101052b0:	f897 0110 	ldrb.w	r0, [r7, #272]	; 0x110
101052b4:	69fa      	ldr	r2, [r7, #28]
101052b6:	f106 010f 	add.w	r1, r6, #15
101052ba:	f003 030f 	and.w	r3, r3, #15
101052be:	0909      	lsrs	r1, r1, #4
101052c0:	f362 1007 	bfi	r0, r2, #4, #4
101052c4:	2b08      	cmp	r3, #8
101052c6:	f8a7 1116 	strh.w	r1, [r7, #278]	; 0x116
101052ca:	f887 0110 	strb.w	r0, [r7, #272]	; 0x110
101052ce:	d14e      	bne.n	1010536e <CRYPTO_ProcessAD+0x902>
101052d0:	9b01      	ldr	r3, [sp, #4]
101052d2:	f897 1115 	ldrb.w	r1, [r7, #277]	; 0x115
101052d6:	330f      	adds	r3, #15
101052d8:	091b      	lsrs	r3, r3, #4
101052da:	6a3a      	ldr	r2, [r7, #32]
101052dc:	f363 0105 	bfi	r1, r3, #0, #6
101052e0:	b2c3      	uxtb	r3, r0
101052e2:	f362 0303 	bfi	r3, r2, #0, #4
101052e6:	f887 1115 	strb.w	r1, [r7, #277]	; 0x115
101052ea:	f887 3110 	strb.w	r3, [r7, #272]	; 0x110
101052ee:	e03e      	b.n	1010536e <CRYPTO_ProcessAD+0x902>
101052f0:	2200      	movs	r2, #0
101052f2:	b2db      	uxtb	r3, r3
101052f4:	f043 0320 	orr.w	r3, r3, #32
101052f8:	f887 310e 	strb.w	r3, [r7, #270]	; 0x10e
101052fc:	f887 2030 	strb.w	r2, [r7, #48]	; 0x30
10105300:	e45c      	b.n	10104bbc <CRYPTO_ProcessAD+0x150>
10105302:	4633      	mov	r3, r6
10105304:	462a      	mov	r2, r5
10105306:	493a      	ldr	r1, [pc, #232]	; (101053f0 <CRYPTO_ProcessAD+0x984>)
10105308:	483a      	ldr	r0, [pc, #232]	; (101053f4 <CRYPTO_ProcessAD+0x988>)
1010530a:	f7fb f873 	bl	101003f4 <DiagPrintf>
1010530e:	4631      	mov	r1, r6
10105310:	4a3c      	ldr	r2, [pc, #240]	; (10105404 <CRYPTO_ProcessAD+0x998>)
10105312:	4628      	mov	r0, r5
10105314:	4b39      	ldr	r3, [pc, #228]	; (101053fc <CRYPTO_ProcessAD+0x990>)
10105316:	4798      	blx	r3
10105318:	e4a9      	b.n	10104c6e <CRYPTO_ProcessAD+0x202>
1010531a:	7e3b      	ldrb	r3, [r7, #24]
1010531c:	2b00      	cmp	r3, #0
1010531e:	f43f ac57 	beq.w	10104bd0 <CRYPTO_ProcessAD+0x164>
10105322:	2b1c      	cmp	r3, #28
10105324:	bf14      	ite	ne
10105326:	2103      	movne	r1, #3
10105328:	2102      	moveq	r1, #2
1010532a:	e77e      	b.n	1010522a <CRYPTO_ProcessAD+0x7be>
1010532c:	462a      	mov	r2, r5
1010532e:	2380      	movs	r3, #128	; 0x80
10105330:	492f      	ldr	r1, [pc, #188]	; (101053f0 <CRYPTO_ProcessAD+0x984>)
10105332:	4830      	ldr	r0, [pc, #192]	; (101053f4 <CRYPTO_ProcessAD+0x988>)
10105334:	f7fb f85e 	bl	101003f4 <DiagPrintf>
10105338:	4628      	mov	r0, r5
1010533a:	4a33      	ldr	r2, [pc, #204]	; (10105408 <CRYPTO_ProcessAD+0x99c>)
1010533c:	2180      	movs	r1, #128	; 0x80
1010533e:	4b2f      	ldr	r3, [pc, #188]	; (101053fc <CRYPTO_ProcessAD+0x990>)
10105340:	4798      	blx	r3
10105342:	e4f2      	b.n	10104d2a <CRYPTO_ProcessAD+0x2be>
10105344:	7a3b      	ldrb	r3, [r7, #8]
10105346:	2b00      	cmp	r3, #0
10105348:	f000 8146 	beq.w	101055d8 <CRYPTO_ProcessAD+0xb6c>
1010534c:	2201      	movs	r2, #1
1010534e:	f897 010c 	ldrb.w	r0, [r7, #268]	; 0x10c
10105352:	f362 1005 	bfi	r0, r2, #4, #2
10105356:	f897 210d 	ldrb.w	r2, [r7, #269]	; 0x10d
1010535a:	1df3      	adds	r3, r6, #7
1010535c:	08db      	lsrs	r3, r3, #3
1010535e:	f361 0282 	bfi	r2, r1, #2, #1
10105362:	f8a7 3116 	strh.w	r3, [r7, #278]	; 0x116
10105366:	f887 010c 	strb.w	r0, [r7, #268]	; 0x10c
1010536a:	f887 210d 	strb.w	r2, [r7, #269]	; 0x10d
1010536e:	7b3b      	ldrb	r3, [r7, #12]
10105370:	7afa      	ldrb	r2, [r7, #11]
10105372:	b92b      	cbnz	r3, 10105380 <CRYPTO_ProcessAD+0x914>
10105374:	f897 310c 	ldrb.w	r3, [r7, #268]	; 0x10c
10105378:	f043 0380 	orr.w	r3, r3, #128	; 0x80
1010537c:	f887 310c 	strb.w	r3, [r7, #268]	; 0x10c
10105380:	2a00      	cmp	r2, #0
10105382:	f040 80c5 	bne.w	10105510 <CRYPTO_ProcessAD+0xaa4>
10105386:	f897 3112 	ldrb.w	r3, [r7, #274]	; 0x112
1010538a:	f043 0302 	orr.w	r3, r3, #2
1010538e:	f887 3112 	strb.w	r3, [r7, #274]	; 0x112
10105392:	e437      	b.n	10104c04 <CRYPTO_ProcessAD+0x198>
10105394:	f8d8 2000 	ldr.w	r2, [r8]
10105398:	0494      	lsls	r4, r2, #18
1010539a:	f57f aed9 	bpl.w	10105150 <CRYPTO_ProcessAD+0x6e4>
1010539e:	6819      	ldr	r1, [r3, #0]
101053a0:	481a      	ldr	r0, [pc, #104]	; (1010540c <CRYPTO_ProcessAD+0x9a0>)
101053a2:	b2c9      	uxtb	r1, r1
101053a4:	f7fb f826 	bl	101003f4 <DiagPrintf>
101053a8:	e6d2      	b.n	10105150 <CRYPTO_ProcessAD+0x6e4>
101053aa:	f240 21db 	movw	r1, #731	; 0x2db
101053ae:	4818      	ldr	r0, [pc, #96]	; (10105410 <CRYPTO_ProcessAD+0x9a4>)
101053b0:	f7fb fa5e 	bl	10100870 <io_assert_failed>
101053b4:	f7ff bb6f 	b.w	10104a96 <CRYPTO_ProcessAD+0x2a>
101053b8:	f8d8 3000 	ldr.w	r3, [r8]
101053bc:	0499      	lsls	r1, r3, #18
101053be:	f57f ade3 	bpl.w	10104f88 <CRYPTO_ProcessAD+0x51c>
101053c2:	4814      	ldr	r0, [pc, #80]	; (10105414 <CRYPTO_ProcessAD+0x9a8>)
101053c4:	f7fb f816 	bl	101003f4 <DiagPrintf>
101053c8:	e5de      	b.n	10104f88 <CRYPTO_ProcessAD+0x51c>
101053ca:	f8d8 3000 	ldr.w	r3, [r8]
101053ce:	0499      	lsls	r1, r3, #18
101053d0:	f57f ac3e 	bpl.w	10104c50 <CRYPTO_ProcessAD+0x1e4>
101053d4:	480f      	ldr	r0, [pc, #60]	; (10105414 <CRYPTO_ProcessAD+0x9a8>)
101053d6:	f7fb f80d 	bl	101003f4 <DiagPrintf>
101053da:	e439      	b.n	10104c50 <CRYPTO_ProcessAD+0x1e4>
101053dc:	e000ed00 	.word	0xe000ed00
101053e0:	101003f5 	.word	0x101003f5
101053e4:	40022000 	.word	0x40022000
101053e8:	50022000 	.word	0x50022000
101053ec:	101d49ac 	.word	0x101d49ac
101053f0:	101d4a20 	.word	0x101d4a20
101053f4:	101d4a38 	.word	0x101d4a38
101053f8:	101d4b14 	.word	0x101d4b14
101053fc:	10104539 	.word	0x10104539
10105400:	101d4a64 	.word	0x101d4a64
10105404:	101d4ae4 	.word	0x101d4ae4
10105408:	101d4af4 	.word	0x101d4af4
1010540c:	101d49e0 	.word	0x101d49e0
10105410:	101d52fc 	.word	0x101d52fc
10105414:	101d4aac 	.word	0x101d4aac
10105418:	1000000c 	.word	0x1000000c
1010541c:	4623      	mov	r3, r4
1010541e:	4a8b      	ldr	r2, [pc, #556]	; (1010564c <CRYPTO_ProcessAD+0xbe0>)
10105420:	498b      	ldr	r1, [pc, #556]	; (10105650 <CRYPTO_ProcessAD+0xbe4>)
10105422:	488c      	ldr	r0, [pc, #560]	; (10105654 <CRYPTO_ProcessAD+0xbe8>)
10105424:	f7fa ffe6 	bl	101003f4 <DiagPrintf>
10105428:	4621      	mov	r1, r4
1010542a:	4a8b      	ldr	r2, [pc, #556]	; (10105658 <CRYPTO_ProcessAD+0xbec>)
1010542c:	4887      	ldr	r0, [pc, #540]	; (1010564c <CRYPTO_ProcessAD+0xbe0>)
1010542e:	4b8b      	ldr	r3, [pc, #556]	; (1010565c <CRYPTO_ProcessAD+0xbf0>)
10105430:	4798      	blx	r3
10105432:	e5ba      	b.n	10104faa <CRYPTO_ProcessAD+0x53e>
10105434:	9b0e      	ldr	r3, [sp, #56]	; 0x38
10105436:	4652      	mov	r2, sl
10105438:	4985      	ldr	r1, [pc, #532]	; (10105650 <CRYPTO_ProcessAD+0xbe4>)
1010543a:	4886      	ldr	r0, [pc, #536]	; (10105654 <CRYPTO_ProcessAD+0xbe8>)
1010543c:	f7fa ffda 	bl	101003f4 <DiagPrintf>
10105440:	990e      	ldr	r1, [sp, #56]	; 0x38
10105442:	4a87      	ldr	r2, [pc, #540]	; (10105660 <CRYPTO_ProcessAD+0xbf4>)
10105444:	4650      	mov	r0, sl
10105446:	4b85      	ldr	r3, [pc, #532]	; (1010565c <CRYPTO_ProcessAD+0xbf0>)
10105448:	4798      	blx	r3
1010544a:	e43f      	b.n	10104ccc <CRYPTO_ProcessAD+0x260>
1010544c:	f8d8 3000 	ldr.w	r3, [r8]
10105450:	049e      	lsls	r6, r3, #18
10105452:	f57f ac2a 	bpl.w	10104caa <CRYPTO_ProcessAD+0x23e>
10105456:	4883      	ldr	r0, [pc, #524]	; (10105664 <CRYPTO_ProcessAD+0xbf8>)
10105458:	f7fa ffcc 	bl	101003f4 <DiagPrintf>
1010545c:	e425      	b.n	10104caa <CRYPTO_ProcessAD+0x23e>
1010545e:	4623      	mov	r3, r4
10105460:	9a0f      	ldr	r2, [sp, #60]	; 0x3c
10105462:	497b      	ldr	r1, [pc, #492]	; (10105650 <CRYPTO_ProcessAD+0xbe4>)
10105464:	487b      	ldr	r0, [pc, #492]	; (10105654 <CRYPTO_ProcessAD+0xbe8>)
10105466:	f7fa ffc5 	bl	101003f4 <DiagPrintf>
1010546a:	4621      	mov	r1, r4
1010546c:	4a7e      	ldr	r2, [pc, #504]	; (10105668 <CRYPTO_ProcessAD+0xbfc>)
1010546e:	980f      	ldr	r0, [sp, #60]	; 0x3c
10105470:	4b7a      	ldr	r3, [pc, #488]	; (1010565c <CRYPTO_ProcessAD+0xbf0>)
10105472:	4798      	blx	r3
10105474:	e4e0      	b.n	10104e38 <CRYPTO_ProcessAD+0x3cc>
10105476:	f8d8 3000 	ldr.w	r3, [r8]
1010547a:	049b      	lsls	r3, r3, #18
1010547c:	f57f aeae 	bpl.w	101051dc <CRYPTO_ProcessAD+0x770>
10105480:	487a      	ldr	r0, [pc, #488]	; (1010566c <CRYPTO_ProcessAD+0xc00>)
10105482:	f7fa ffb7 	bl	101003f4 <DiagPrintf>
10105486:	f04f 30ff 	mov.w	r0, #4294967295
1010548a:	e5be      	b.n	1010500a <CRYPTO_ProcessAD+0x59e>
1010548c:	4a6f      	ldr	r2, [pc, #444]	; (1010564c <CRYPTO_ProcessAD+0xbe0>)
1010548e:	4970      	ldr	r1, [pc, #448]	; (10105650 <CRYPTO_ProcessAD+0xbe4>)
10105490:	4870      	ldr	r0, [pc, #448]	; (10105654 <CRYPTO_ProcessAD+0xbe8>)
10105492:	f7fa ffaf 	bl	101003f4 <DiagPrintf>
10105496:	4a76      	ldr	r2, [pc, #472]	; (10105670 <CRYPTO_ProcessAD+0xc04>)
10105498:	6d79      	ldr	r1, [r7, #84]	; 0x54
1010549a:	486c      	ldr	r0, [pc, #432]	; (1010564c <CRYPTO_ProcessAD+0xbe0>)
1010549c:	4b6f      	ldr	r3, [pc, #444]	; (1010565c <CRYPTO_ProcessAD+0xbf0>)
1010549e:	4798      	blx	r3
101054a0:	e4f4      	b.n	10104e8c <CRYPTO_ProcessAD+0x420>
101054a2:	9903      	ldr	r1, [sp, #12]
101054a4:	4873      	ldr	r0, [pc, #460]	; (10105674 <CRYPTO_ProcessAD+0xc08>)
101054a6:	f7fa ffa5 	bl	101003f4 <DiagPrintf>
101054aa:	f04f 30ff 	mov.w	r0, #4294967295
101054ae:	b005      	add	sp, #20
101054b0:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
101054b4:	9b12      	ldr	r3, [sp, #72]	; 0x48
101054b6:	2b00      	cmp	r3, #0
101054b8:	f040 80af 	bne.w	1010561a <CRYPTO_ProcessAD+0xbae>
101054bc:	f8df 81bc 	ldr.w	r8, [pc, #444]	; 1010567c <CRYPTO_ProcessAD+0xc10>
101054c0:	f7ff bb57 	b.w	10104b72 <CRYPTO_ProcessAD+0x106>
101054c4:	7afa      	ldrb	r2, [r7, #11]
101054c6:	2a00      	cmp	r2, #0
101054c8:	f000 80bb 	beq.w	10105642 <CRYPTO_ProcessAD+0xbd6>
101054cc:	2002      	movs	r0, #2
101054ce:	69fb      	ldr	r3, [r7, #28]
101054d0:	f897 1110 	ldrb.w	r1, [r7, #272]	; 0x110
101054d4:	360f      	adds	r6, #15
101054d6:	f363 1107 	bfi	r1, r3, #4, #4
101054da:	9b01      	ldr	r3, [sp, #4]
101054dc:	0936      	lsrs	r6, r6, #4
101054de:	330f      	adds	r3, #15
101054e0:	f8a7 6116 	strh.w	r6, [r7, #278]	; 0x116
101054e4:	f897 6115 	ldrb.w	r6, [r7, #277]	; 0x115
101054e8:	091b      	lsrs	r3, r3, #4
101054ea:	f363 0605 	bfi	r6, r3, #0, #6
101054ee:	6a3b      	ldr	r3, [r7, #32]
101054f0:	f363 0103 	bfi	r1, r3, #0, #4
101054f4:	f897 310c 	ldrb.w	r3, [r7, #268]	; 0x10c
101054f8:	f360 1305 	bfi	r3, r0, #4, #2
101054fc:	7b38      	ldrb	r0, [r7, #12]
101054fe:	f887 6115 	strb.w	r6, [r7, #277]	; 0x115
10105502:	f887 1110 	strb.w	r1, [r7, #272]	; 0x110
10105506:	f887 310c 	strb.w	r3, [r7, #268]	; 0x10c
1010550a:	2800      	cmp	r0, #0
1010550c:	f43f af32 	beq.w	10105374 <CRYPTO_ProcessAD+0x908>
10105510:	f897 1111 	ldrb.w	r1, [r7, #273]	; 0x111
10105514:	f897 210d 	ldrb.w	r2, [r7, #269]	; 0x10d
10105518:	f897 3112 	ldrb.w	r3, [r7, #274]	; 0x112
1010551c:	f041 0108 	orr.w	r1, r1, #8
10105520:	f042 0210 	orr.w	r2, r2, #16
10105524:	f043 03fe 	orr.w	r3, r3, #254	; 0xfe
10105528:	f887 1111 	strb.w	r1, [r7, #273]	; 0x111
1010552c:	f887 210d 	strb.w	r2, [r7, #269]	; 0x10d
10105530:	f887 3112 	strb.w	r3, [r7, #274]	; 0x112
10105534:	f7ff bb66 	b.w	10104c04 <CRYPTO_ProcessAD+0x198>
10105538:	f8d8 3000 	ldr.w	r3, [r8]
1010553c:	049d      	lsls	r5, r3, #18
1010553e:	f57f ac27 	bpl.w	10104d90 <CRYPTO_ProcessAD+0x324>
10105542:	4848      	ldr	r0, [pc, #288]	; (10105664 <CRYPTO_ProcessAD+0xbf8>)
10105544:	f7fa ff56 	bl	101003f4 <DiagPrintf>
10105548:	e422      	b.n	10104d90 <CRYPTO_ProcessAD+0x324>
1010554a:	6b79      	ldr	r1, [r7, #52]	; 0x34
1010554c:	f897 0110 	ldrb.w	r0, [r7, #272]	; 0x110
10105550:	69fa      	ldr	r2, [r7, #28]
10105552:	f106 030f 	add.w	r3, r6, #15
10105556:	00c9      	lsls	r1, r1, #3
10105558:	091b      	lsrs	r3, r3, #4
1010555a:	f501 7100 	add.w	r1, r1, #512	; 0x200
1010555e:	f362 1007 	bfi	r0, r2, #4, #4
10105562:	f8a7 3116 	strh.w	r3, [r7, #278]	; 0x116
10105566:	f8c7 1118 	str.w	r1, [r7, #280]	; 0x118
1010556a:	f887 0110 	strb.w	r0, [r7, #272]	; 0x110
1010556e:	e64f      	b.n	10105210 <CRYPTO_ProcessAD+0x7a4>
10105570:	f8d8 3000 	ldr.w	r3, [r8]
10105574:	0498      	lsls	r0, r3, #18
10105576:	f57f ad37 	bpl.w	10104fe8 <CRYPTO_ProcessAD+0x57c>
1010557a:	483a      	ldr	r0, [pc, #232]	; (10105664 <CRYPTO_ProcessAD+0xbf8>)
1010557c:	f7fa ff3a 	bl	101003f4 <DiagPrintf>
10105580:	e532      	b.n	10104fe8 <CRYPTO_ProcessAD+0x57c>
10105582:	9e00      	ldr	r6, [sp, #0]
10105584:	e4da      	b.n	10104f3c <CRYPTO_ProcessAD+0x4d0>
10105586:	f8d8 3000 	ldr.w	r3, [r8]
1010558a:	0499      	lsls	r1, r3, #18
1010558c:	f57f abbd 	bpl.w	10104d0a <CRYPTO_ProcessAD+0x29e>
10105590:	4834      	ldr	r0, [pc, #208]	; (10105664 <CRYPTO_ProcessAD+0xbf8>)
10105592:	f7fa ff2f 	bl	101003f4 <DiagPrintf>
10105596:	f7ff bbb8 	b.w	10104d0a <CRYPTO_ProcessAD+0x29e>
1010559a:	f240 21dd 	movw	r1, #733	; 0x2dd
1010559e:	4836      	ldr	r0, [pc, #216]	; (10105678 <CRYPTO_ProcessAD+0xc0c>)
101055a0:	f7fb f966 	bl	10100870 <io_assert_failed>
101055a4:	f7ff ba7a 	b.w	10104a9c <CRYPTO_ProcessAD+0x30>
101055a8:	9b10      	ldr	r3, [sp, #64]	; 0x40
101055aa:	2b00      	cmp	r3, #0
101055ac:	f43f ac65 	beq.w	10104e7a <CRYPTO_ProcessAD+0x40e>
101055b0:	461c      	mov	r4, r3
101055b2:	e43a      	b.n	10104e2a <CRYPTO_ProcessAD+0x3be>
101055b4:	f8d8 3000 	ldr.w	r3, [r8]
101055b8:	0499      	lsls	r1, r3, #18
101055ba:	f57f ac86 	bpl.w	10104eca <CRYPTO_ProcessAD+0x45e>
101055be:	4829      	ldr	r0, [pc, #164]	; (10105664 <CRYPTO_ProcessAD+0xbf8>)
101055c0:	f7fa ff18 	bl	101003f4 <DiagPrintf>
101055c4:	e481      	b.n	10104eca <CRYPTO_ProcessAD+0x45e>
101055c6:	f8d8 3000 	ldr.w	r3, [r8]
101055ca:	049d      	lsls	r5, r3, #18
101055cc:	f57f ac53 	bpl.w	10104e76 <CRYPTO_ProcessAD+0x40a>
101055d0:	4824      	ldr	r0, [pc, #144]	; (10105664 <CRYPTO_ProcessAD+0xbf8>)
101055d2:	f7fa ff0f 	bl	101003f4 <DiagPrintf>
101055d6:	e44e      	b.n	10104e76 <CRYPTO_ProcessAD+0x40a>
101055d8:	7a7b      	ldrb	r3, [r7, #9]
101055da:	2b00      	cmp	r3, #0
101055dc:	f43f af72 	beq.w	101054c4 <CRYPTO_ProcessAD+0xa58>
101055e0:	2301      	movs	r3, #1
101055e2:	f897 110c 	ldrb.w	r1, [r7, #268]	; 0x10c
101055e6:	f363 1105 	bfi	r1, r3, #4, #2
101055ea:	f897 310d 	ldrb.w	r3, [r7, #269]	; 0x10d
101055ee:	1df2      	adds	r2, r6, #7
101055f0:	08d2      	lsrs	r2, r2, #3
101055f2:	f043 0304 	orr.w	r3, r3, #4
101055f6:	f8a7 2116 	strh.w	r2, [r7, #278]	; 0x116
101055fa:	f887 110c 	strb.w	r1, [r7, #268]	; 0x10c
101055fe:	f887 310d 	strb.w	r3, [r7, #269]	; 0x10d
10105602:	e6b4      	b.n	1010536e <CRYPTO_ProcessAD+0x902>
10105604:	2102      	movs	r1, #2
10105606:	f897 210d 	ldrb.w	r2, [r7, #269]	; 0x10d
1010560a:	f361 0201 	bfi	r2, r1, #0, #2
1010560e:	f887 210d 	strb.w	r2, [r7, #269]	; 0x10d
10105612:	e64d      	b.n	101052b0 <CRYPTO_ProcessAD+0x844>
10105614:	f046 5680 	orr.w	r6, r6, #268435456	; 0x10000000
10105618:	e562      	b.n	101050e0 <CRYPTO_ProcessAD+0x674>
1010561a:	f04f 4580 	mov.w	r5, #1073741824	; 0x40000000
1010561e:	2310      	movs	r3, #16
10105620:	f364 65db 	bfi	r5, r4, #27, #1
10105624:	f363 0507 	bfi	r5, r3, #0, #8
10105628:	f045 5540 	orr.w	r5, r5, #805306368	; 0x30000000
1010562c:	f8df 804c 	ldr.w	r8, [pc, #76]	; 1010567c <CRYPTO_ProcessAD+0xc10>
10105630:	e59b      	b.n	1010516a <CRYPTO_ProcessAD+0x6fe>
10105632:	2101      	movs	r1, #1
10105634:	f897 210d 	ldrb.w	r2, [r7, #269]	; 0x10d
10105638:	f361 0201 	bfi	r2, r1, #0, #2
1010563c:	f887 210d 	strb.w	r2, [r7, #269]	; 0x10d
10105640:	e636      	b.n	101052b0 <CRYPTO_ProcessAD+0x844>
10105642:	7b3a      	ldrb	r2, [r7, #12]
10105644:	2a00      	cmp	r2, #0
10105646:	f47f ae9e 	bne.w	10105386 <CRYPTO_ProcessAD+0x91a>
1010564a:	e693      	b.n	10105374 <CRYPTO_ProcessAD+0x908>
1010564c:	10000520 	.word	0x10000520
10105650:	101d4a20 	.word	0x101d4a20
10105654:	101d4a38 	.word	0x101d4a38
10105658:	101d4b20 	.word	0x101d4b20
1010565c:	10104539 	.word	0x10104539
10105660:	101d4aec 	.word	0x101d4aec
10105664:	101d4aac 	.word	0x101d4aac
10105668:	101d4afc 	.word	0x101d4afc
1010566c:	101d4b64 	.word	0x101d4b64
10105670:	101d4b04 	.word	0x101d4b04
10105674:	101d4b30 	.word	0x101d4b30
10105678:	101d52fc 	.word	0x101d52fc
1010567c:	1000000c 	.word	0x1000000c

10105680 <CRYPTO_SendSeqBuf>:
10105680:	e92d 43f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
10105684:	4c40      	ldr	r4, [pc, #256]	; (10105788 <CRYPTO_SendSeqBuf+0x108>)
10105686:	f894 3044 	ldrb.w	r3, [r4, #68]	; 0x44
1010568a:	6c25      	ldr	r5, [r4, #64]	; 0x40
1010568c:	f1c3 0740 	rsb	r7, r3, #64	; 0x40
10105690:	4606      	mov	r6, r0
10105692:	42bd      	cmp	r5, r7
10105694:	eb04 0003 	add.w	r0, r4, r3
10105698:	b087      	sub	sp, #28
1010569a:	f500 7096 	add.w	r0, r0, #300	; 0x12c
1010569e:	da12      	bge.n	101056c6 <CRYPTO_SendSeqBuf+0x46>
101056a0:	462a      	mov	r2, r5
101056a2:	4b3a      	ldr	r3, [pc, #232]	; (1010578c <CRYPTO_SendSeqBuf+0x10c>)
101056a4:	6be1      	ldr	r1, [r4, #60]	; 0x3c
101056a6:	4798      	blx	r3
101056a8:	f894 3044 	ldrb.w	r3, [r4, #68]	; 0x44
101056ac:	441d      	add	r5, r3
101056ae:	f884 5044 	strb.w	r5, [r4, #68]	; 0x44
101056b2:	2e00      	cmp	r6, #0
101056b4:	d065      	beq.n	10105782 <CRYPTO_SendSeqBuf+0x102>
101056b6:	f894 2044 	ldrb.w	r2, [r4, #68]	; 0x44
101056ba:	2a00      	cmp	r2, #0
101056bc:	d13e      	bne.n	1010573c <CRYPTO_SendSeqBuf+0xbc>
101056be:	4610      	mov	r0, r2
101056c0:	b007      	add	sp, #28
101056c2:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
101056c6:	463a      	mov	r2, r7
101056c8:	6be1      	ldr	r1, [r4, #60]	; 0x3c
101056ca:	f8df 80c0 	ldr.w	r8, [pc, #192]	; 1010578c <CRYPTO_SendSeqBuf+0x10c>
101056ce:	47c0      	blx	r8
101056d0:	42bd      	cmp	r5, r7
101056d2:	f04f 0300 	mov.w	r3, #0
101056d6:	d03f      	beq.n	10105758 <CRYPTO_SendSeqBuf+0xd8>
101056d8:	2240      	movs	r2, #64	; 0x40
101056da:	9304      	str	r3, [sp, #16]
101056dc:	9303      	str	r3, [sp, #12]
101056de:	9302      	str	r3, [sp, #8]
101056e0:	9301      	str	r3, [sp, #4]
101056e2:	9300      	str	r3, [sp, #0]
101056e4:	f504 7196 	add.w	r1, r4, #300	; 0x12c
101056e8:	4620      	mov	r0, r4
101056ea:	f8df 90a8 	ldr.w	r9, [pc, #168]	; 10105794 <CRYPTO_SendSeqBuf+0x114>
101056ee:	47c8      	blx	r9
101056f0:	2800      	cmp	r0, #0
101056f2:	d1e5      	bne.n	101056c0 <CRYPTO_SendSeqBuf+0x40>
101056f4:	1beb      	subs	r3, r5, r7
101056f6:	6be1      	ldr	r1, [r4, #60]	; 0x3c
101056f8:	f003 053f 	and.w	r5, r3, #63	; 0x3f
101056fc:	4439      	add	r1, r7
101056fe:	1b5f      	subs	r7, r3, r5
10105700:	2f00      	cmp	r7, #0
10105702:	6423      	str	r3, [r4, #64]	; 0x40
10105704:	f884 0044 	strb.w	r0, [r4, #68]	; 0x44
10105708:	63e1      	str	r1, [r4, #60]	; 0x3c
1010570a:	dd11      	ble.n	10105730 <CRYPTO_SendSeqBuf+0xb0>
1010570c:	2d00      	cmp	r5, #0
1010570e:	bf0c      	ite	eq
10105710:	4632      	moveq	r2, r6
10105712:	2200      	movne	r2, #0
10105714:	9004      	str	r0, [sp, #16]
10105716:	9002      	str	r0, [sp, #8]
10105718:	9001      	str	r0, [sp, #4]
1010571a:	9000      	str	r0, [sp, #0]
1010571c:	4603      	mov	r3, r0
1010571e:	9203      	str	r2, [sp, #12]
10105720:	4620      	mov	r0, r4
10105722:	463a      	mov	r2, r7
10105724:	47c8      	blx	r9
10105726:	2800      	cmp	r0, #0
10105728:	d1ca      	bne.n	101056c0 <CRYPTO_SendSeqBuf+0x40>
1010572a:	6be3      	ldr	r3, [r4, #60]	; 0x3c
1010572c:	441f      	add	r7, r3
1010572e:	63e7      	str	r7, [r4, #60]	; 0x3c
10105730:	b325      	cbz	r5, 1010577c <CRYPTO_SendSeqBuf+0xfc>
10105732:	462a      	mov	r2, r5
10105734:	6be1      	ldr	r1, [r4, #60]	; 0x3c
10105736:	4816      	ldr	r0, [pc, #88]	; (10105790 <CRYPTO_SendSeqBuf+0x110>)
10105738:	47c0      	blx	r8
1010573a:	e01f      	b.n	1010577c <CRYPTO_SendSeqBuf+0xfc>
1010573c:	2300      	movs	r3, #0
1010573e:	4914      	ldr	r1, [pc, #80]	; (10105790 <CRYPTO_SendSeqBuf+0x110>)
10105740:	9603      	str	r6, [sp, #12]
10105742:	9304      	str	r3, [sp, #16]
10105744:	9302      	str	r3, [sp, #8]
10105746:	9301      	str	r3, [sp, #4]
10105748:	9300      	str	r3, [sp, #0]
1010574a:	f5a1 7096 	sub.w	r0, r1, #300	; 0x12c
1010574e:	4c11      	ldr	r4, [pc, #68]	; (10105794 <CRYPTO_SendSeqBuf+0x114>)
10105750:	47a0      	blx	r4
10105752:	b007      	add	sp, #28
10105754:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
10105758:	9603      	str	r6, [sp, #12]
1010575a:	9304      	str	r3, [sp, #16]
1010575c:	9302      	str	r3, [sp, #8]
1010575e:	9301      	str	r3, [sp, #4]
10105760:	9300      	str	r3, [sp, #0]
10105762:	2240      	movs	r2, #64	; 0x40
10105764:	f504 7196 	add.w	r1, r4, #300	; 0x12c
10105768:	4620      	mov	r0, r4
1010576a:	4f0a      	ldr	r7, [pc, #40]	; (10105794 <CRYPTO_SendSeqBuf+0x114>)
1010576c:	47b8      	blx	r7
1010576e:	2800      	cmp	r0, #0
10105770:	d1a6      	bne.n	101056c0 <CRYPTO_SendSeqBuf+0x40>
10105772:	6be3      	ldr	r3, [r4, #60]	; 0x3c
10105774:	442b      	add	r3, r5
10105776:	4605      	mov	r5, r0
10105778:	6420      	str	r0, [r4, #64]	; 0x40
1010577a:	63e3      	str	r3, [r4, #60]	; 0x3c
1010577c:	f884 5044 	strb.w	r5, [r4, #68]	; 0x44
10105780:	e797      	b.n	101056b2 <CRYPTO_SendSeqBuf+0x32>
10105782:	4630      	mov	r0, r6
10105784:	e79c      	b.n	101056c0 <CRYPTO_SendSeqBuf+0x40>
10105786:	bf00      	nop
10105788:	100003a0 	.word	0x100003a0
1010578c:	10106d15 	.word	0x10106d15
10105790:	100004cc 	.word	0x100004cc
10105794:	10104a6d 	.word	0x10104a6d

10105798 <CRYPTO_CipherInit>:
10105798:	b510      	push	{r4, lr}
1010579a:	2400      	movs	r4, #0
1010579c:	b084      	sub	sp, #16
1010579e:	9300      	str	r3, [sp, #0]
101057a0:	9402      	str	r4, [sp, #8]
101057a2:	4613      	mov	r3, r2
101057a4:	9401      	str	r4, [sp, #4]
101057a6:	f04f 32ff 	mov.w	r2, #4294967295
101057aa:	4c02      	ldr	r4, [pc, #8]	; (101057b4 <CRYPTO_CipherInit+0x1c>)
101057ac:	47a0      	blx	r4
101057ae:	b004      	add	sp, #16
101057b0:	bd10      	pop	{r4, pc}
101057b2:	bf00      	nop
101057b4:	1010486d 	.word	0x1010486d

101057b8 <CRYPTO_CipherEncryptAD>:
101057b8:	b5f0      	push	{r4, r5, r6, r7, lr}
101057ba:	2700      	movs	r7, #0
101057bc:	b087      	sub	sp, #28
101057be:	6845      	ldr	r5, [r0, #4]
101057c0:	9e0c      	ldr	r6, [sp, #48]	; 0x30
101057c2:	f045 0580 	orr.w	r5, r5, #128	; 0x80
101057c6:	6045      	str	r5, [r0, #4]
101057c8:	7307      	strb	r7, [r0, #12]
101057ca:	9c0f      	ldr	r4, [sp, #60]	; 0x3c
101057cc:	9d0d      	ldr	r5, [sp, #52]	; 0x34
101057ce:	9f0e      	ldr	r7, [sp, #56]	; 0x38
101057d0:	9600      	str	r6, [sp, #0]
101057d2:	9e10      	ldr	r6, [sp, #64]	; 0x40
101057d4:	9403      	str	r4, [sp, #12]
101057d6:	9501      	str	r5, [sp, #4]
101057d8:	9702      	str	r7, [sp, #8]
101057da:	9604      	str	r6, [sp, #16]
101057dc:	4c01      	ldr	r4, [pc, #4]	; (101057e4 <CRYPTO_CipherEncryptAD+0x2c>)
101057de:	47a0      	blx	r4
101057e0:	b007      	add	sp, #28
101057e2:	bdf0      	pop	{r4, r5, r6, r7, pc}
101057e4:	10104a6d 	.word	0x10104a6d

101057e8 <CRYPTO_CipherDecryptAD>:
101057e8:	b5f0      	push	{r4, r5, r6, r7, lr}
101057ea:	2701      	movs	r7, #1
101057ec:	b087      	sub	sp, #28
101057ee:	6845      	ldr	r5, [r0, #4]
101057f0:	9e0c      	ldr	r6, [sp, #48]	; 0x30
101057f2:	f085 0580 	eor.w	r5, r5, #128	; 0x80
101057f6:	6045      	str	r5, [r0, #4]
101057f8:	7307      	strb	r7, [r0, #12]
101057fa:	9c0f      	ldr	r4, [sp, #60]	; 0x3c
101057fc:	9d0d      	ldr	r5, [sp, #52]	; 0x34
101057fe:	9f0e      	ldr	r7, [sp, #56]	; 0x38
10105800:	9600      	str	r6, [sp, #0]
10105802:	9e10      	ldr	r6, [sp, #64]	; 0x40
10105804:	9403      	str	r4, [sp, #12]
10105806:	9501      	str	r5, [sp, #4]
10105808:	9702      	str	r7, [sp, #8]
1010580a:	9604      	str	r6, [sp, #16]
1010580c:	4c01      	ldr	r4, [pc, #4]	; (10105814 <CRYPTO_CipherDecryptAD+0x2c>)
1010580e:	47a0      	blx	r4
10105810:	b007      	add	sp, #28
10105812:	bdf0      	pop	{r4, r5, r6, r7, pc}
10105814:	10104a6d 	.word	0x10104a6d

10105818 <rtl_crypto_3des_cbc_init>:
10105818:	b570      	push	{r4, r5, r6, lr}
1010581a:	4b10      	ldr	r3, [pc, #64]	; (1010585c <rtl_crypto_3des_cbc_init+0x44>)
1010581c:	781b      	ldrb	r3, [r3, #0]
1010581e:	2b01      	cmp	r3, #1
10105820:	4604      	mov	r4, r0
10105822:	460d      	mov	r5, r1
10105824:	d003      	beq.n	1010582e <rtl_crypto_3des_cbc_init+0x16>
10105826:	2123      	movs	r1, #35	; 0x23
10105828:	480d      	ldr	r0, [pc, #52]	; (10105860 <rtl_crypto_3des_cbc_init+0x48>)
1010582a:	f7fb f821 	bl	10100870 <io_assert_failed>
1010582e:	b194      	cbz	r4, 10105856 <rtl_crypto_3des_cbc_init+0x3e>
10105830:	07a3      	lsls	r3, r4, #30
10105832:	d10d      	bne.n	10105850 <rtl_crypto_3des_cbc_init+0x38>
10105834:	2d20      	cmp	r5, #32
10105836:	d808      	bhi.n	1010584a <rtl_crypto_3des_cbc_init+0x32>
10105838:	4622      	mov	r2, r4
1010583a:	4c0a      	ldr	r4, [pc, #40]	; (10105864 <rtl_crypto_3des_cbc_init+0x4c>)
1010583c:	462b      	mov	r3, r5
1010583e:	46a4      	mov	ip, r4
10105840:	2111      	movs	r1, #17
10105842:	4806      	ldr	r0, [pc, #24]	; (1010585c <rtl_crypto_3des_cbc_init+0x44>)
10105844:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10105848:	4760      	bx	ip
1010584a:	f06f 0006 	mvn.w	r0, #6
1010584e:	bd70      	pop	{r4, r5, r6, pc}
10105850:	f06f 0005 	mvn.w	r0, #5
10105854:	bd70      	pop	{r4, r5, r6, pc}
10105856:	f06f 0003 	mvn.w	r0, #3
1010585a:	bd70      	pop	{r4, r5, r6, pc}
1010585c:	100003a0 	.word	0x100003a0
10105860:	101d5328 	.word	0x101d5328
10105864:	10105799 	.word	0x10105799

10105868 <rtl_crypto_3des_cbc_encrypt>:
10105868:	b570      	push	{r4, r5, r6, lr}
1010586a:	b086      	sub	sp, #24
1010586c:	9e0a      	ldr	r6, [sp, #40]	; 0x28
1010586e:	b1d2      	cbz	r2, 101058a6 <rtl_crypto_3des_cbc_encrypt+0x3e>
10105870:	f012 0503 	ands.w	r5, r2, #3
10105874:	d111      	bne.n	1010589a <rtl_crypto_3des_cbc_encrypt+0x32>
10105876:	2b20      	cmp	r3, #32
10105878:	d812      	bhi.n	101058a0 <rtl_crypto_3des_cbc_encrypt+0x38>
1010587a:	b1a0      	cbz	r0, 101058a6 <rtl_crypto_3des_cbc_encrypt+0x3e>
1010587c:	b19e      	cbz	r6, 101058a6 <rtl_crypto_3des_cbc_encrypt+0x3e>
1010587e:	4614      	mov	r4, r2
10105880:	e88d 0028 	stmia.w	sp, {r3, r5}
10105884:	460a      	mov	r2, r1
10105886:	4623      	mov	r3, r4
10105888:	4601      	mov	r1, r0
1010588a:	9504      	str	r5, [sp, #16]
1010588c:	9603      	str	r6, [sp, #12]
1010588e:	9502      	str	r5, [sp, #8]
10105890:	4806      	ldr	r0, [pc, #24]	; (101058ac <rtl_crypto_3des_cbc_encrypt+0x44>)
10105892:	4c07      	ldr	r4, [pc, #28]	; (101058b0 <rtl_crypto_3des_cbc_encrypt+0x48>)
10105894:	47a0      	blx	r4
10105896:	b006      	add	sp, #24
10105898:	bd70      	pop	{r4, r5, r6, pc}
1010589a:	f06f 0005 	mvn.w	r0, #5
1010589e:	e7fa      	b.n	10105896 <rtl_crypto_3des_cbc_encrypt+0x2e>
101058a0:	f06f 0008 	mvn.w	r0, #8
101058a4:	e7f7      	b.n	10105896 <rtl_crypto_3des_cbc_encrypt+0x2e>
101058a6:	f06f 0003 	mvn.w	r0, #3
101058aa:	e7f4      	b.n	10105896 <rtl_crypto_3des_cbc_encrypt+0x2e>
101058ac:	100003a0 	.word	0x100003a0
101058b0:	101057b9 	.word	0x101057b9

101058b4 <rtl_crypto_3des_cbc_decrypt>:
101058b4:	b570      	push	{r4, r5, r6, lr}
101058b6:	b086      	sub	sp, #24
101058b8:	9e0a      	ldr	r6, [sp, #40]	; 0x28
101058ba:	b1d2      	cbz	r2, 101058f2 <rtl_crypto_3des_cbc_decrypt+0x3e>
101058bc:	f012 0503 	ands.w	r5, r2, #3
101058c0:	d111      	bne.n	101058e6 <rtl_crypto_3des_cbc_decrypt+0x32>
101058c2:	2b20      	cmp	r3, #32
101058c4:	d812      	bhi.n	101058ec <rtl_crypto_3des_cbc_decrypt+0x38>
101058c6:	b1a0      	cbz	r0, 101058f2 <rtl_crypto_3des_cbc_decrypt+0x3e>
101058c8:	b19e      	cbz	r6, 101058f2 <rtl_crypto_3des_cbc_decrypt+0x3e>
101058ca:	4614      	mov	r4, r2
101058cc:	e88d 0028 	stmia.w	sp, {r3, r5}
101058d0:	460a      	mov	r2, r1
101058d2:	4623      	mov	r3, r4
101058d4:	4601      	mov	r1, r0
101058d6:	9504      	str	r5, [sp, #16]
101058d8:	9603      	str	r6, [sp, #12]
101058da:	9502      	str	r5, [sp, #8]
101058dc:	4806      	ldr	r0, [pc, #24]	; (101058f8 <rtl_crypto_3des_cbc_decrypt+0x44>)
101058de:	4c07      	ldr	r4, [pc, #28]	; (101058fc <rtl_crypto_3des_cbc_decrypt+0x48>)
101058e0:	47a0      	blx	r4
101058e2:	b006      	add	sp, #24
101058e4:	bd70      	pop	{r4, r5, r6, pc}
101058e6:	f06f 0005 	mvn.w	r0, #5
101058ea:	e7fa      	b.n	101058e2 <rtl_crypto_3des_cbc_decrypt+0x2e>
101058ec:	f06f 0008 	mvn.w	r0, #8
101058f0:	e7f7      	b.n	101058e2 <rtl_crypto_3des_cbc_decrypt+0x2e>
101058f2:	f06f 0003 	mvn.w	r0, #3
101058f6:	e7f4      	b.n	101058e2 <rtl_crypto_3des_cbc_decrypt+0x2e>
101058f8:	100003a0 	.word	0x100003a0
101058fc:	101057e9 	.word	0x101057e9

10105900 <rtl_crypto_3des_ecb_init>:
10105900:	b570      	push	{r4, r5, r6, lr}
10105902:	4b10      	ldr	r3, [pc, #64]	; (10105944 <rtl_crypto_3des_ecb_init+0x44>)
10105904:	781b      	ldrb	r3, [r3, #0]
10105906:	2b01      	cmp	r3, #1
10105908:	4604      	mov	r4, r0
1010590a:	460d      	mov	r5, r1
1010590c:	d003      	beq.n	10105916 <rtl_crypto_3des_ecb_init+0x16>
1010590e:	216d      	movs	r1, #109	; 0x6d
10105910:	480d      	ldr	r0, [pc, #52]	; (10105948 <rtl_crypto_3des_ecb_init+0x48>)
10105912:	f7fa ffad 	bl	10100870 <io_assert_failed>
10105916:	b194      	cbz	r4, 1010593e <rtl_crypto_3des_ecb_init+0x3e>
10105918:	07a3      	lsls	r3, r4, #30
1010591a:	d10d      	bne.n	10105938 <rtl_crypto_3des_ecb_init+0x38>
1010591c:	2d20      	cmp	r5, #32
1010591e:	d808      	bhi.n	10105932 <rtl_crypto_3des_ecb_init+0x32>
10105920:	4622      	mov	r2, r4
10105922:	4c0a      	ldr	r4, [pc, #40]	; (1010594c <rtl_crypto_3des_ecb_init+0x4c>)
10105924:	462b      	mov	r3, r5
10105926:	46a4      	mov	ip, r4
10105928:	2110      	movs	r1, #16
1010592a:	4806      	ldr	r0, [pc, #24]	; (10105944 <rtl_crypto_3des_ecb_init+0x44>)
1010592c:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10105930:	4760      	bx	ip
10105932:	f06f 0006 	mvn.w	r0, #6
10105936:	bd70      	pop	{r4, r5, r6, pc}
10105938:	f06f 0005 	mvn.w	r0, #5
1010593c:	bd70      	pop	{r4, r5, r6, pc}
1010593e:	f06f 0003 	mvn.w	r0, #3
10105942:	bd70      	pop	{r4, r5, r6, pc}
10105944:	100003a0 	.word	0x100003a0
10105948:	101d53a8 	.word	0x101d53a8
1010594c:	10105799 	.word	0x10105799

10105950 <rtl_crypto_3des_ecb_encrypt>:
10105950:	b570      	push	{r4, r5, r6, lr}
10105952:	b086      	sub	sp, #24
10105954:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105956:	b178      	cbz	r0, 10105978 <rtl_crypto_3des_ecb_encrypt+0x28>
10105958:	b176      	cbz	r6, 10105978 <rtl_crypto_3des_ecb_encrypt+0x28>
1010595a:	461c      	mov	r4, r3
1010595c:	2500      	movs	r5, #0
1010595e:	4613      	mov	r3, r2
10105960:	9400      	str	r4, [sp, #0]
10105962:	460a      	mov	r2, r1
10105964:	9603      	str	r6, [sp, #12]
10105966:	4601      	mov	r1, r0
10105968:	9504      	str	r5, [sp, #16]
1010596a:	9502      	str	r5, [sp, #8]
1010596c:	9501      	str	r5, [sp, #4]
1010596e:	4804      	ldr	r0, [pc, #16]	; (10105980 <rtl_crypto_3des_ecb_encrypt+0x30>)
10105970:	4c04      	ldr	r4, [pc, #16]	; (10105984 <rtl_crypto_3des_ecb_encrypt+0x34>)
10105972:	47a0      	blx	r4
10105974:	b006      	add	sp, #24
10105976:	bd70      	pop	{r4, r5, r6, pc}
10105978:	f06f 0003 	mvn.w	r0, #3
1010597c:	e7fa      	b.n	10105974 <rtl_crypto_3des_ecb_encrypt+0x24>
1010597e:	bf00      	nop
10105980:	100003a0 	.word	0x100003a0
10105984:	101057b9 	.word	0x101057b9

10105988 <rtl_crypto_3des_ecb_decrypt>:
10105988:	b570      	push	{r4, r5, r6, lr}
1010598a:	b086      	sub	sp, #24
1010598c:	9e0a      	ldr	r6, [sp, #40]	; 0x28
1010598e:	b178      	cbz	r0, 101059b0 <rtl_crypto_3des_ecb_decrypt+0x28>
10105990:	b176      	cbz	r6, 101059b0 <rtl_crypto_3des_ecb_decrypt+0x28>
10105992:	461c      	mov	r4, r3
10105994:	2500      	movs	r5, #0
10105996:	4613      	mov	r3, r2
10105998:	9400      	str	r4, [sp, #0]
1010599a:	460a      	mov	r2, r1
1010599c:	9603      	str	r6, [sp, #12]
1010599e:	4601      	mov	r1, r0
101059a0:	9504      	str	r5, [sp, #16]
101059a2:	9502      	str	r5, [sp, #8]
101059a4:	9501      	str	r5, [sp, #4]
101059a6:	4804      	ldr	r0, [pc, #16]	; (101059b8 <rtl_crypto_3des_ecb_decrypt+0x30>)
101059a8:	4c04      	ldr	r4, [pc, #16]	; (101059bc <rtl_crypto_3des_ecb_decrypt+0x34>)
101059aa:	47a0      	blx	r4
101059ac:	b006      	add	sp, #24
101059ae:	bd70      	pop	{r4, r5, r6, pc}
101059b0:	f06f 0003 	mvn.w	r0, #3
101059b4:	e7fa      	b.n	101059ac <rtl_crypto_3des_ecb_decrypt+0x24>
101059b6:	bf00      	nop
101059b8:	100003a0 	.word	0x100003a0
101059bc:	101057e9 	.word	0x101057e9

101059c0 <rtl_crypto_3des_cfb_init>:
101059c0:	b570      	push	{r4, r5, r6, lr}
101059c2:	4b10      	ldr	r3, [pc, #64]	; (10105a04 <rtl_crypto_3des_cfb_init+0x44>)
101059c4:	781b      	ldrb	r3, [r3, #0]
101059c6:	2b01      	cmp	r3, #1
101059c8:	4604      	mov	r4, r0
101059ca:	460d      	mov	r5, r1
101059cc:	d003      	beq.n	101059d6 <rtl_crypto_3des_cfb_init+0x16>
101059ce:	21b1      	movs	r1, #177	; 0xb1
101059d0:	480d      	ldr	r0, [pc, #52]	; (10105a08 <rtl_crypto_3des_cfb_init+0x48>)
101059d2:	f7fa ff4d 	bl	10100870 <io_assert_failed>
101059d6:	b194      	cbz	r4, 101059fe <rtl_crypto_3des_cfb_init+0x3e>
101059d8:	07a3      	lsls	r3, r4, #30
101059da:	d10d      	bne.n	101059f8 <rtl_crypto_3des_cfb_init+0x38>
101059dc:	2d20      	cmp	r5, #32
101059de:	d808      	bhi.n	101059f2 <rtl_crypto_3des_cfb_init+0x32>
101059e0:	4622      	mov	r2, r4
101059e2:	4c0a      	ldr	r4, [pc, #40]	; (10105a0c <rtl_crypto_3des_cfb_init+0x4c>)
101059e4:	462b      	mov	r3, r5
101059e6:	46a4      	mov	ip, r4
101059e8:	2112      	movs	r1, #18
101059ea:	4806      	ldr	r0, [pc, #24]	; (10105a04 <rtl_crypto_3des_cfb_init+0x44>)
101059ec:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
101059f0:	4760      	bx	ip
101059f2:	f06f 0006 	mvn.w	r0, #6
101059f6:	bd70      	pop	{r4, r5, r6, pc}
101059f8:	f06f 0005 	mvn.w	r0, #5
101059fc:	bd70      	pop	{r4, r5, r6, pc}
101059fe:	f06f 0003 	mvn.w	r0, #3
10105a02:	bd70      	pop	{r4, r5, r6, pc}
10105a04:	100003a0 	.word	0x100003a0
10105a08:	101d53f8 	.word	0x101d53f8
10105a0c:	10105799 	.word	0x10105799

10105a10 <rtl_crypto_3des_cfb_encrypt>:
10105a10:	b570      	push	{r4, r5, r6, lr}
10105a12:	b086      	sub	sp, #24
10105a14:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105a16:	b178      	cbz	r0, 10105a38 <rtl_crypto_3des_cfb_encrypt+0x28>
10105a18:	b176      	cbz	r6, 10105a38 <rtl_crypto_3des_cfb_encrypt+0x28>
10105a1a:	461c      	mov	r4, r3
10105a1c:	2500      	movs	r5, #0
10105a1e:	4613      	mov	r3, r2
10105a20:	9400      	str	r4, [sp, #0]
10105a22:	460a      	mov	r2, r1
10105a24:	9603      	str	r6, [sp, #12]
10105a26:	4601      	mov	r1, r0
10105a28:	9504      	str	r5, [sp, #16]
10105a2a:	9502      	str	r5, [sp, #8]
10105a2c:	9501      	str	r5, [sp, #4]
10105a2e:	4804      	ldr	r0, [pc, #16]	; (10105a40 <rtl_crypto_3des_cfb_encrypt+0x30>)
10105a30:	4c04      	ldr	r4, [pc, #16]	; (10105a44 <rtl_crypto_3des_cfb_encrypt+0x34>)
10105a32:	47a0      	blx	r4
10105a34:	b006      	add	sp, #24
10105a36:	bd70      	pop	{r4, r5, r6, pc}
10105a38:	f06f 0003 	mvn.w	r0, #3
10105a3c:	e7fa      	b.n	10105a34 <rtl_crypto_3des_cfb_encrypt+0x24>
10105a3e:	bf00      	nop
10105a40:	100003a0 	.word	0x100003a0
10105a44:	101057b9 	.word	0x101057b9

10105a48 <rtl_crypto_3des_cfb_decrypt>:
10105a48:	b570      	push	{r4, r5, r6, lr}
10105a4a:	b086      	sub	sp, #24
10105a4c:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105a4e:	b178      	cbz	r0, 10105a70 <rtl_crypto_3des_cfb_decrypt+0x28>
10105a50:	b176      	cbz	r6, 10105a70 <rtl_crypto_3des_cfb_decrypt+0x28>
10105a52:	461c      	mov	r4, r3
10105a54:	2500      	movs	r5, #0
10105a56:	4613      	mov	r3, r2
10105a58:	9400      	str	r4, [sp, #0]
10105a5a:	460a      	mov	r2, r1
10105a5c:	9603      	str	r6, [sp, #12]
10105a5e:	4601      	mov	r1, r0
10105a60:	9504      	str	r5, [sp, #16]
10105a62:	9502      	str	r5, [sp, #8]
10105a64:	9501      	str	r5, [sp, #4]
10105a66:	4804      	ldr	r0, [pc, #16]	; (10105a78 <rtl_crypto_3des_cfb_decrypt+0x30>)
10105a68:	4c04      	ldr	r4, [pc, #16]	; (10105a7c <rtl_crypto_3des_cfb_decrypt+0x34>)
10105a6a:	47a0      	blx	r4
10105a6c:	b006      	add	sp, #24
10105a6e:	bd70      	pop	{r4, r5, r6, pc}
10105a70:	f06f 0003 	mvn.w	r0, #3
10105a74:	e7fa      	b.n	10105a6c <rtl_crypto_3des_cfb_decrypt+0x24>
10105a76:	bf00      	nop
10105a78:	100003a0 	.word	0x100003a0
10105a7c:	101057e9 	.word	0x101057e9

10105a80 <rtl_crypto_3des_ofb_init>:
10105a80:	b570      	push	{r4, r5, r6, lr}
10105a82:	4b10      	ldr	r3, [pc, #64]	; (10105ac4 <rtl_crypto_3des_ofb_init+0x44>)
10105a84:	781b      	ldrb	r3, [r3, #0]
10105a86:	2b01      	cmp	r3, #1
10105a88:	4604      	mov	r4, r0
10105a8a:	460d      	mov	r5, r1
10105a8c:	d003      	beq.n	10105a96 <rtl_crypto_3des_ofb_init+0x16>
10105a8e:	21f5      	movs	r1, #245	; 0xf5
10105a90:	480d      	ldr	r0, [pc, #52]	; (10105ac8 <rtl_crypto_3des_ofb_init+0x48>)
10105a92:	f7fa feed 	bl	10100870 <io_assert_failed>
10105a96:	b194      	cbz	r4, 10105abe <rtl_crypto_3des_ofb_init+0x3e>
10105a98:	07a3      	lsls	r3, r4, #30
10105a9a:	d10d      	bne.n	10105ab8 <rtl_crypto_3des_ofb_init+0x38>
10105a9c:	2d20      	cmp	r5, #32
10105a9e:	d808      	bhi.n	10105ab2 <rtl_crypto_3des_ofb_init+0x32>
10105aa0:	4622      	mov	r2, r4
10105aa2:	4c0a      	ldr	r4, [pc, #40]	; (10105acc <rtl_crypto_3des_ofb_init+0x4c>)
10105aa4:	462b      	mov	r3, r5
10105aa6:	46a4      	mov	ip, r4
10105aa8:	2113      	movs	r1, #19
10105aaa:	4806      	ldr	r0, [pc, #24]	; (10105ac4 <rtl_crypto_3des_ofb_init+0x44>)
10105aac:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10105ab0:	4760      	bx	ip
10105ab2:	f06f 0006 	mvn.w	r0, #6
10105ab6:	bd70      	pop	{r4, r5, r6, pc}
10105ab8:	f06f 0005 	mvn.w	r0, #5
10105abc:	bd70      	pop	{r4, r5, r6, pc}
10105abe:	f06f 0003 	mvn.w	r0, #3
10105ac2:	bd70      	pop	{r4, r5, r6, pc}
10105ac4:	100003a0 	.word	0x100003a0
10105ac8:	101d53dc 	.word	0x101d53dc
10105acc:	10105799 	.word	0x10105799

10105ad0 <rtl_crypto_3des_ofb_encrypt>:
10105ad0:	b570      	push	{r4, r5, r6, lr}
10105ad2:	b086      	sub	sp, #24
10105ad4:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105ad6:	b178      	cbz	r0, 10105af8 <rtl_crypto_3des_ofb_encrypt+0x28>
10105ad8:	b176      	cbz	r6, 10105af8 <rtl_crypto_3des_ofb_encrypt+0x28>
10105ada:	461c      	mov	r4, r3
10105adc:	2500      	movs	r5, #0
10105ade:	4613      	mov	r3, r2
10105ae0:	9400      	str	r4, [sp, #0]
10105ae2:	460a      	mov	r2, r1
10105ae4:	9603      	str	r6, [sp, #12]
10105ae6:	4601      	mov	r1, r0
10105ae8:	9504      	str	r5, [sp, #16]
10105aea:	9502      	str	r5, [sp, #8]
10105aec:	9501      	str	r5, [sp, #4]
10105aee:	4804      	ldr	r0, [pc, #16]	; (10105b00 <rtl_crypto_3des_ofb_encrypt+0x30>)
10105af0:	4c04      	ldr	r4, [pc, #16]	; (10105b04 <rtl_crypto_3des_ofb_encrypt+0x34>)
10105af2:	47a0      	blx	r4
10105af4:	b006      	add	sp, #24
10105af6:	bd70      	pop	{r4, r5, r6, pc}
10105af8:	f06f 0003 	mvn.w	r0, #3
10105afc:	e7fa      	b.n	10105af4 <rtl_crypto_3des_ofb_encrypt+0x24>
10105afe:	bf00      	nop
10105b00:	100003a0 	.word	0x100003a0
10105b04:	101057b9 	.word	0x101057b9

10105b08 <rtl_crypto_3des_ofb_decrypt>:
10105b08:	b570      	push	{r4, r5, r6, lr}
10105b0a:	b086      	sub	sp, #24
10105b0c:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105b0e:	b178      	cbz	r0, 10105b30 <rtl_crypto_3des_ofb_decrypt+0x28>
10105b10:	b176      	cbz	r6, 10105b30 <rtl_crypto_3des_ofb_decrypt+0x28>
10105b12:	461c      	mov	r4, r3
10105b14:	2500      	movs	r5, #0
10105b16:	4613      	mov	r3, r2
10105b18:	9400      	str	r4, [sp, #0]
10105b1a:	460a      	mov	r2, r1
10105b1c:	9603      	str	r6, [sp, #12]
10105b1e:	4601      	mov	r1, r0
10105b20:	9504      	str	r5, [sp, #16]
10105b22:	9502      	str	r5, [sp, #8]
10105b24:	9501      	str	r5, [sp, #4]
10105b26:	4804      	ldr	r0, [pc, #16]	; (10105b38 <rtl_crypto_3des_ofb_decrypt+0x30>)
10105b28:	4c04      	ldr	r4, [pc, #16]	; (10105b3c <rtl_crypto_3des_ofb_decrypt+0x34>)
10105b2a:	47a0      	blx	r4
10105b2c:	b006      	add	sp, #24
10105b2e:	bd70      	pop	{r4, r5, r6, pc}
10105b30:	f06f 0003 	mvn.w	r0, #3
10105b34:	e7fa      	b.n	10105b2c <rtl_crypto_3des_ofb_decrypt+0x24>
10105b36:	bf00      	nop
10105b38:	100003a0 	.word	0x100003a0
10105b3c:	101057e9 	.word	0x101057e9

10105b40 <rtl_crypto_3des_ctr_init>:
10105b40:	b570      	push	{r4, r5, r6, lr}
10105b42:	4b11      	ldr	r3, [pc, #68]	; (10105b88 <rtl_crypto_3des_ctr_init+0x48>)
10105b44:	781b      	ldrb	r3, [r3, #0]
10105b46:	2b01      	cmp	r3, #1
10105b48:	4604      	mov	r4, r0
10105b4a:	460d      	mov	r5, r1
10105b4c:	d004      	beq.n	10105b58 <rtl_crypto_3des_ctr_init+0x18>
10105b4e:	f240 1139 	movw	r1, #313	; 0x139
10105b52:	480e      	ldr	r0, [pc, #56]	; (10105b8c <rtl_crypto_3des_ctr_init+0x4c>)
10105b54:	f7fa fe8c 	bl	10100870 <io_assert_failed>
10105b58:	b194      	cbz	r4, 10105b80 <rtl_crypto_3des_ctr_init+0x40>
10105b5a:	07a3      	lsls	r3, r4, #30
10105b5c:	d10d      	bne.n	10105b7a <rtl_crypto_3des_ctr_init+0x3a>
10105b5e:	2d20      	cmp	r5, #32
10105b60:	d808      	bhi.n	10105b74 <rtl_crypto_3des_ctr_init+0x34>
10105b62:	4622      	mov	r2, r4
10105b64:	4c0a      	ldr	r4, [pc, #40]	; (10105b90 <rtl_crypto_3des_ctr_init+0x50>)
10105b66:	462b      	mov	r3, r5
10105b68:	46a4      	mov	ip, r4
10105b6a:	2114      	movs	r1, #20
10105b6c:	4806      	ldr	r0, [pc, #24]	; (10105b88 <rtl_crypto_3des_ctr_init+0x48>)
10105b6e:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10105b72:	4760      	bx	ip
10105b74:	f06f 0006 	mvn.w	r0, #6
10105b78:	bd70      	pop	{r4, r5, r6, pc}
10105b7a:	f06f 0005 	mvn.w	r0, #5
10105b7e:	bd70      	pop	{r4, r5, r6, pc}
10105b80:	f06f 0003 	mvn.w	r0, #3
10105b84:	bd70      	pop	{r4, r5, r6, pc}
10105b86:	bf00      	nop
10105b88:	100003a0 	.word	0x100003a0
10105b8c:	101d535c 	.word	0x101d535c
10105b90:	10105799 	.word	0x10105799

10105b94 <rtl_crypto_3des_ctr_encrypt>:
10105b94:	b570      	push	{r4, r5, r6, lr}
10105b96:	b086      	sub	sp, #24
10105b98:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105b9a:	b178      	cbz	r0, 10105bbc <rtl_crypto_3des_ctr_encrypt+0x28>
10105b9c:	b176      	cbz	r6, 10105bbc <rtl_crypto_3des_ctr_encrypt+0x28>
10105b9e:	461c      	mov	r4, r3
10105ba0:	2500      	movs	r5, #0
10105ba2:	4613      	mov	r3, r2
10105ba4:	9400      	str	r4, [sp, #0]
10105ba6:	460a      	mov	r2, r1
10105ba8:	9603      	str	r6, [sp, #12]
10105baa:	4601      	mov	r1, r0
10105bac:	9504      	str	r5, [sp, #16]
10105bae:	9502      	str	r5, [sp, #8]
10105bb0:	9501      	str	r5, [sp, #4]
10105bb2:	4804      	ldr	r0, [pc, #16]	; (10105bc4 <rtl_crypto_3des_ctr_encrypt+0x30>)
10105bb4:	4c04      	ldr	r4, [pc, #16]	; (10105bc8 <rtl_crypto_3des_ctr_encrypt+0x34>)
10105bb6:	47a0      	blx	r4
10105bb8:	b006      	add	sp, #24
10105bba:	bd70      	pop	{r4, r5, r6, pc}
10105bbc:	f06f 0003 	mvn.w	r0, #3
10105bc0:	e7fa      	b.n	10105bb8 <rtl_crypto_3des_ctr_encrypt+0x24>
10105bc2:	bf00      	nop
10105bc4:	100003a0 	.word	0x100003a0
10105bc8:	101057b9 	.word	0x101057b9

10105bcc <rtl_crypto_3des_ctr_decrypt>:
10105bcc:	b570      	push	{r4, r5, r6, lr}
10105bce:	b086      	sub	sp, #24
10105bd0:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105bd2:	b178      	cbz	r0, 10105bf4 <rtl_crypto_3des_ctr_decrypt+0x28>
10105bd4:	b176      	cbz	r6, 10105bf4 <rtl_crypto_3des_ctr_decrypt+0x28>
10105bd6:	461c      	mov	r4, r3
10105bd8:	2500      	movs	r5, #0
10105bda:	4613      	mov	r3, r2
10105bdc:	9400      	str	r4, [sp, #0]
10105bde:	460a      	mov	r2, r1
10105be0:	9603      	str	r6, [sp, #12]
10105be2:	4601      	mov	r1, r0
10105be4:	9504      	str	r5, [sp, #16]
10105be6:	9502      	str	r5, [sp, #8]
10105be8:	9501      	str	r5, [sp, #4]
10105bea:	4804      	ldr	r0, [pc, #16]	; (10105bfc <rtl_crypto_3des_ctr_decrypt+0x30>)
10105bec:	4c04      	ldr	r4, [pc, #16]	; (10105c00 <rtl_crypto_3des_ctr_decrypt+0x34>)
10105bee:	47a0      	blx	r4
10105bf0:	b006      	add	sp, #24
10105bf2:	bd70      	pop	{r4, r5, r6, pc}
10105bf4:	f06f 0003 	mvn.w	r0, #3
10105bf8:	e7fa      	b.n	10105bf0 <rtl_crypto_3des_ctr_decrypt+0x24>
10105bfa:	bf00      	nop
10105bfc:	100003a0 	.word	0x100003a0
10105c00:	101057e9 	.word	0x101057e9

10105c04 <rtl_crypto_des_cbc_init>:
10105c04:	b570      	push	{r4, r5, r6, lr}
10105c06:	4b11      	ldr	r3, [pc, #68]	; (10105c4c <rtl_crypto_des_cbc_init+0x48>)
10105c08:	781b      	ldrb	r3, [r3, #0]
10105c0a:	2b01      	cmp	r3, #1
10105c0c:	4604      	mov	r4, r0
10105c0e:	460d      	mov	r5, r1
10105c10:	d004      	beq.n	10105c1c <rtl_crypto_des_cbc_init+0x18>
10105c12:	f240 117d 	movw	r1, #381	; 0x17d
10105c16:	480e      	ldr	r0, [pc, #56]	; (10105c50 <rtl_crypto_des_cbc_init+0x4c>)
10105c18:	f7fa fe2a 	bl	10100870 <io_assert_failed>
10105c1c:	b194      	cbz	r4, 10105c44 <rtl_crypto_des_cbc_init+0x40>
10105c1e:	07a3      	lsls	r3, r4, #30
10105c20:	d10d      	bne.n	10105c3e <rtl_crypto_des_cbc_init+0x3a>
10105c22:	2d20      	cmp	r5, #32
10105c24:	d808      	bhi.n	10105c38 <rtl_crypto_des_cbc_init+0x34>
10105c26:	4622      	mov	r2, r4
10105c28:	4c0a      	ldr	r4, [pc, #40]	; (10105c54 <rtl_crypto_des_cbc_init+0x50>)
10105c2a:	462b      	mov	r3, r5
10105c2c:	46a4      	mov	ip, r4
10105c2e:	2101      	movs	r1, #1
10105c30:	4806      	ldr	r0, [pc, #24]	; (10105c4c <rtl_crypto_des_cbc_init+0x48>)
10105c32:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10105c36:	4760      	bx	ip
10105c38:	f06f 0006 	mvn.w	r0, #6
10105c3c:	bd70      	pop	{r4, r5, r6, pc}
10105c3e:	f06f 0005 	mvn.w	r0, #5
10105c42:	bd70      	pop	{r4, r5, r6, pc}
10105c44:	f06f 0003 	mvn.w	r0, #3
10105c48:	bd70      	pop	{r4, r5, r6, pc}
10105c4a:	bf00      	nop
10105c4c:	100003a0 	.word	0x100003a0
10105c50:	101d5378 	.word	0x101d5378
10105c54:	10105799 	.word	0x10105799

10105c58 <rtl_crypto_des_cbc_encrypt>:
10105c58:	b5f0      	push	{r4, r5, r6, r7, lr}
10105c5a:	b087      	sub	sp, #28
10105c5c:	9f0c      	ldr	r7, [sp, #48]	; 0x30
10105c5e:	b30a      	cbz	r2, 10105ca4 <rtl_crypto_des_cbc_encrypt+0x4c>
10105c60:	f012 0503 	ands.w	r5, r2, #3
10105c64:	d118      	bne.n	10105c98 <rtl_crypto_des_cbc_encrypt+0x40>
10105c66:	2b20      	cmp	r3, #32
10105c68:	d819      	bhi.n	10105c9e <rtl_crypto_des_cbc_encrypt+0x46>
10105c6a:	4e10      	ldr	r6, [pc, #64]	; (10105cac <rtl_crypto_des_cbc_encrypt+0x54>)
10105c6c:	6cb4      	ldr	r4, [r6, #72]	; 0x48
10105c6e:	42a3      	cmp	r3, r4
10105c70:	d10f      	bne.n	10105c92 <rtl_crypto_des_cbc_encrypt+0x3a>
10105c72:	b1b8      	cbz	r0, 10105ca4 <rtl_crypto_des_cbc_encrypt+0x4c>
10105c74:	b1b7      	cbz	r7, 10105ca4 <rtl_crypto_des_cbc_encrypt+0x4c>
10105c76:	4614      	mov	r4, r2
10105c78:	e88d 0028 	stmia.w	sp, {r3, r5}
10105c7c:	460a      	mov	r2, r1
10105c7e:	4623      	mov	r3, r4
10105c80:	4601      	mov	r1, r0
10105c82:	9504      	str	r5, [sp, #16]
10105c84:	9703      	str	r7, [sp, #12]
10105c86:	9502      	str	r5, [sp, #8]
10105c88:	4630      	mov	r0, r6
10105c8a:	4c09      	ldr	r4, [pc, #36]	; (10105cb0 <rtl_crypto_des_cbc_encrypt+0x58>)
10105c8c:	47a0      	blx	r4
10105c8e:	b007      	add	sp, #28
10105c90:	bdf0      	pop	{r4, r5, r6, r7, pc}
10105c92:	f06f 000b 	mvn.w	r0, #11
10105c96:	e7fa      	b.n	10105c8e <rtl_crypto_des_cbc_encrypt+0x36>
10105c98:	f06f 0005 	mvn.w	r0, #5
10105c9c:	e7f7      	b.n	10105c8e <rtl_crypto_des_cbc_encrypt+0x36>
10105c9e:	f06f 0008 	mvn.w	r0, #8
10105ca2:	e7f4      	b.n	10105c8e <rtl_crypto_des_cbc_encrypt+0x36>
10105ca4:	f06f 0003 	mvn.w	r0, #3
10105ca8:	e7f1      	b.n	10105c8e <rtl_crypto_des_cbc_encrypt+0x36>
10105caa:	bf00      	nop
10105cac:	100003a0 	.word	0x100003a0
10105cb0:	101057b9 	.word	0x101057b9

10105cb4 <rtl_crypto_des_cbc_decrypt>:
10105cb4:	b5f0      	push	{r4, r5, r6, r7, lr}
10105cb6:	b087      	sub	sp, #28
10105cb8:	9f0c      	ldr	r7, [sp, #48]	; 0x30
10105cba:	b30a      	cbz	r2, 10105d00 <rtl_crypto_des_cbc_decrypt+0x4c>
10105cbc:	f012 0503 	ands.w	r5, r2, #3
10105cc0:	d118      	bne.n	10105cf4 <rtl_crypto_des_cbc_decrypt+0x40>
10105cc2:	2b20      	cmp	r3, #32
10105cc4:	d819      	bhi.n	10105cfa <rtl_crypto_des_cbc_decrypt+0x46>
10105cc6:	4e10      	ldr	r6, [pc, #64]	; (10105d08 <rtl_crypto_des_cbc_decrypt+0x54>)
10105cc8:	6cb4      	ldr	r4, [r6, #72]	; 0x48
10105cca:	42a3      	cmp	r3, r4
10105ccc:	d10f      	bne.n	10105cee <rtl_crypto_des_cbc_decrypt+0x3a>
10105cce:	b1b8      	cbz	r0, 10105d00 <rtl_crypto_des_cbc_decrypt+0x4c>
10105cd0:	b1b7      	cbz	r7, 10105d00 <rtl_crypto_des_cbc_decrypt+0x4c>
10105cd2:	4614      	mov	r4, r2
10105cd4:	e88d 0028 	stmia.w	sp, {r3, r5}
10105cd8:	460a      	mov	r2, r1
10105cda:	4623      	mov	r3, r4
10105cdc:	4601      	mov	r1, r0
10105cde:	9504      	str	r5, [sp, #16]
10105ce0:	9703      	str	r7, [sp, #12]
10105ce2:	9502      	str	r5, [sp, #8]
10105ce4:	4630      	mov	r0, r6
10105ce6:	4c09      	ldr	r4, [pc, #36]	; (10105d0c <rtl_crypto_des_cbc_decrypt+0x58>)
10105ce8:	47a0      	blx	r4
10105cea:	b007      	add	sp, #28
10105cec:	bdf0      	pop	{r4, r5, r6, r7, pc}
10105cee:	f06f 000b 	mvn.w	r0, #11
10105cf2:	e7fa      	b.n	10105cea <rtl_crypto_des_cbc_decrypt+0x36>
10105cf4:	f06f 0005 	mvn.w	r0, #5
10105cf8:	e7f7      	b.n	10105cea <rtl_crypto_des_cbc_decrypt+0x36>
10105cfa:	f06f 0008 	mvn.w	r0, #8
10105cfe:	e7f4      	b.n	10105cea <rtl_crypto_des_cbc_decrypt+0x36>
10105d00:	f06f 0003 	mvn.w	r0, #3
10105d04:	e7f1      	b.n	10105cea <rtl_crypto_des_cbc_decrypt+0x36>
10105d06:	bf00      	nop
10105d08:	100003a0 	.word	0x100003a0
10105d0c:	101057e9 	.word	0x101057e9

10105d10 <rtl_crypto_des_ecb_init>:
10105d10:	b570      	push	{r4, r5, r6, lr}
10105d12:	4b11      	ldr	r3, [pc, #68]	; (10105d58 <rtl_crypto_des_ecb_init+0x48>)
10105d14:	781b      	ldrb	r3, [r3, #0]
10105d16:	2b01      	cmp	r3, #1
10105d18:	4604      	mov	r4, r0
10105d1a:	460d      	mov	r5, r1
10105d1c:	d004      	beq.n	10105d28 <rtl_crypto_des_ecb_init+0x18>
10105d1e:	f240 11c9 	movw	r1, #457	; 0x1c9
10105d22:	480e      	ldr	r0, [pc, #56]	; (10105d5c <rtl_crypto_des_ecb_init+0x4c>)
10105d24:	f7fa fda4 	bl	10100870 <io_assert_failed>
10105d28:	b194      	cbz	r4, 10105d50 <rtl_crypto_des_ecb_init+0x40>
10105d2a:	f014 0103 	ands.w	r1, r4, #3
10105d2e:	d10c      	bne.n	10105d4a <rtl_crypto_des_ecb_init+0x3a>
10105d30:	2d20      	cmp	r5, #32
10105d32:	d807      	bhi.n	10105d44 <rtl_crypto_des_ecb_init+0x34>
10105d34:	4622      	mov	r2, r4
10105d36:	4c0a      	ldr	r4, [pc, #40]	; (10105d60 <rtl_crypto_des_ecb_init+0x50>)
10105d38:	462b      	mov	r3, r5
10105d3a:	46a4      	mov	ip, r4
10105d3c:	4806      	ldr	r0, [pc, #24]	; (10105d58 <rtl_crypto_des_ecb_init+0x48>)
10105d3e:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10105d42:	4760      	bx	ip
10105d44:	f06f 0006 	mvn.w	r0, #6
10105d48:	bd70      	pop	{r4, r5, r6, pc}
10105d4a:	f06f 0005 	mvn.w	r0, #5
10105d4e:	bd70      	pop	{r4, r5, r6, pc}
10105d50:	f06f 0003 	mvn.w	r0, #3
10105d54:	bd70      	pop	{r4, r5, r6, pc}
10105d56:	bf00      	nop
10105d58:	100003a0 	.word	0x100003a0
10105d5c:	101d5344 	.word	0x101d5344
10105d60:	10105799 	.word	0x10105799

10105d64 <rtl_crypto_des_ecb_encrypt>:
10105d64:	b570      	push	{r4, r5, r6, lr}
10105d66:	b086      	sub	sp, #24
10105d68:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105d6a:	b178      	cbz	r0, 10105d8c <rtl_crypto_des_ecb_encrypt+0x28>
10105d6c:	b176      	cbz	r6, 10105d8c <rtl_crypto_des_ecb_encrypt+0x28>
10105d6e:	461c      	mov	r4, r3
10105d70:	2500      	movs	r5, #0
10105d72:	4613      	mov	r3, r2
10105d74:	9400      	str	r4, [sp, #0]
10105d76:	460a      	mov	r2, r1
10105d78:	9603      	str	r6, [sp, #12]
10105d7a:	4601      	mov	r1, r0
10105d7c:	9504      	str	r5, [sp, #16]
10105d7e:	9502      	str	r5, [sp, #8]
10105d80:	9501      	str	r5, [sp, #4]
10105d82:	4804      	ldr	r0, [pc, #16]	; (10105d94 <rtl_crypto_des_ecb_encrypt+0x30>)
10105d84:	4c04      	ldr	r4, [pc, #16]	; (10105d98 <rtl_crypto_des_ecb_encrypt+0x34>)
10105d86:	47a0      	blx	r4
10105d88:	b006      	add	sp, #24
10105d8a:	bd70      	pop	{r4, r5, r6, pc}
10105d8c:	f06f 0003 	mvn.w	r0, #3
10105d90:	e7fa      	b.n	10105d88 <rtl_crypto_des_ecb_encrypt+0x24>
10105d92:	bf00      	nop
10105d94:	100003a0 	.word	0x100003a0
10105d98:	101057b9 	.word	0x101057b9

10105d9c <rtl_crypto_des_ecb_decrypt>:
10105d9c:	b570      	push	{r4, r5, r6, lr}
10105d9e:	b086      	sub	sp, #24
10105da0:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105da2:	b178      	cbz	r0, 10105dc4 <rtl_crypto_des_ecb_decrypt+0x28>
10105da4:	b176      	cbz	r6, 10105dc4 <rtl_crypto_des_ecb_decrypt+0x28>
10105da6:	461c      	mov	r4, r3
10105da8:	2500      	movs	r5, #0
10105daa:	4613      	mov	r3, r2
10105dac:	9400      	str	r4, [sp, #0]
10105dae:	460a      	mov	r2, r1
10105db0:	9603      	str	r6, [sp, #12]
10105db2:	4601      	mov	r1, r0
10105db4:	9504      	str	r5, [sp, #16]
10105db6:	9502      	str	r5, [sp, #8]
10105db8:	9501      	str	r5, [sp, #4]
10105dba:	4804      	ldr	r0, [pc, #16]	; (10105dcc <rtl_crypto_des_ecb_decrypt+0x30>)
10105dbc:	4c04      	ldr	r4, [pc, #16]	; (10105dd0 <rtl_crypto_des_ecb_decrypt+0x34>)
10105dbe:	47a0      	blx	r4
10105dc0:	b006      	add	sp, #24
10105dc2:	bd70      	pop	{r4, r5, r6, pc}
10105dc4:	f06f 0003 	mvn.w	r0, #3
10105dc8:	e7fa      	b.n	10105dc0 <rtl_crypto_des_ecb_decrypt+0x24>
10105dca:	bf00      	nop
10105dcc:	100003a0 	.word	0x100003a0
10105dd0:	101057e9 	.word	0x101057e9

10105dd4 <rtl_crypto_des_cfb_init>:
10105dd4:	b570      	push	{r4, r5, r6, lr}
10105dd6:	4b11      	ldr	r3, [pc, #68]	; (10105e1c <rtl_crypto_des_cfb_init+0x48>)
10105dd8:	781b      	ldrb	r3, [r3, #0]
10105dda:	2b01      	cmp	r3, #1
10105ddc:	4604      	mov	r4, r0
10105dde:	460d      	mov	r5, r1
10105de0:	d004      	beq.n	10105dec <rtl_crypto_des_cfb_init+0x18>
10105de2:	f240 210d 	movw	r1, #525	; 0x20d
10105de6:	480e      	ldr	r0, [pc, #56]	; (10105e20 <rtl_crypto_des_cfb_init+0x4c>)
10105de8:	f7fa fd42 	bl	10100870 <io_assert_failed>
10105dec:	b194      	cbz	r4, 10105e14 <rtl_crypto_des_cfb_init+0x40>
10105dee:	07a3      	lsls	r3, r4, #30
10105df0:	d10d      	bne.n	10105e0e <rtl_crypto_des_cfb_init+0x3a>
10105df2:	2d20      	cmp	r5, #32
10105df4:	d808      	bhi.n	10105e08 <rtl_crypto_des_cfb_init+0x34>
10105df6:	4622      	mov	r2, r4
10105df8:	4c0a      	ldr	r4, [pc, #40]	; (10105e24 <rtl_crypto_des_cfb_init+0x50>)
10105dfa:	462b      	mov	r3, r5
10105dfc:	46a4      	mov	ip, r4
10105dfe:	2102      	movs	r1, #2
10105e00:	4806      	ldr	r0, [pc, #24]	; (10105e1c <rtl_crypto_des_cfb_init+0x48>)
10105e02:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10105e06:	4760      	bx	ip
10105e08:	f06f 0006 	mvn.w	r0, #6
10105e0c:	bd70      	pop	{r4, r5, r6, pc}
10105e0e:	f06f 0005 	mvn.w	r0, #5
10105e12:	bd70      	pop	{r4, r5, r6, pc}
10105e14:	f06f 0003 	mvn.w	r0, #3
10105e18:	bd70      	pop	{r4, r5, r6, pc}
10105e1a:	bf00      	nop
10105e1c:	100003a0 	.word	0x100003a0
10105e20:	101d5390 	.word	0x101d5390
10105e24:	10105799 	.word	0x10105799

10105e28 <rtl_crypto_des_cfb_encrypt>:
10105e28:	b570      	push	{r4, r5, r6, lr}
10105e2a:	b086      	sub	sp, #24
10105e2c:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105e2e:	b178      	cbz	r0, 10105e50 <rtl_crypto_des_cfb_encrypt+0x28>
10105e30:	b176      	cbz	r6, 10105e50 <rtl_crypto_des_cfb_encrypt+0x28>
10105e32:	461c      	mov	r4, r3
10105e34:	2500      	movs	r5, #0
10105e36:	4613      	mov	r3, r2
10105e38:	9400      	str	r4, [sp, #0]
10105e3a:	460a      	mov	r2, r1
10105e3c:	9603      	str	r6, [sp, #12]
10105e3e:	4601      	mov	r1, r0
10105e40:	9504      	str	r5, [sp, #16]
10105e42:	9502      	str	r5, [sp, #8]
10105e44:	9501      	str	r5, [sp, #4]
10105e46:	4804      	ldr	r0, [pc, #16]	; (10105e58 <rtl_crypto_des_cfb_encrypt+0x30>)
10105e48:	4c04      	ldr	r4, [pc, #16]	; (10105e5c <rtl_crypto_des_cfb_encrypt+0x34>)
10105e4a:	47a0      	blx	r4
10105e4c:	b006      	add	sp, #24
10105e4e:	bd70      	pop	{r4, r5, r6, pc}
10105e50:	f06f 0003 	mvn.w	r0, #3
10105e54:	e7fa      	b.n	10105e4c <rtl_crypto_des_cfb_encrypt+0x24>
10105e56:	bf00      	nop
10105e58:	100003a0 	.word	0x100003a0
10105e5c:	101057b9 	.word	0x101057b9

10105e60 <rtl_crypto_des_cfb_decrypt>:
10105e60:	b570      	push	{r4, r5, r6, lr}
10105e62:	b086      	sub	sp, #24
10105e64:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105e66:	b178      	cbz	r0, 10105e88 <rtl_crypto_des_cfb_decrypt+0x28>
10105e68:	b176      	cbz	r6, 10105e88 <rtl_crypto_des_cfb_decrypt+0x28>
10105e6a:	461c      	mov	r4, r3
10105e6c:	2500      	movs	r5, #0
10105e6e:	4613      	mov	r3, r2
10105e70:	9400      	str	r4, [sp, #0]
10105e72:	460a      	mov	r2, r1
10105e74:	9603      	str	r6, [sp, #12]
10105e76:	4601      	mov	r1, r0
10105e78:	9504      	str	r5, [sp, #16]
10105e7a:	9502      	str	r5, [sp, #8]
10105e7c:	9501      	str	r5, [sp, #4]
10105e7e:	4804      	ldr	r0, [pc, #16]	; (10105e90 <rtl_crypto_des_cfb_decrypt+0x30>)
10105e80:	4c04      	ldr	r4, [pc, #16]	; (10105e94 <rtl_crypto_des_cfb_decrypt+0x34>)
10105e82:	47a0      	blx	r4
10105e84:	b006      	add	sp, #24
10105e86:	bd70      	pop	{r4, r5, r6, pc}
10105e88:	f06f 0003 	mvn.w	r0, #3
10105e8c:	e7fa      	b.n	10105e84 <rtl_crypto_des_cfb_decrypt+0x24>
10105e8e:	bf00      	nop
10105e90:	100003a0 	.word	0x100003a0
10105e94:	101057e9 	.word	0x101057e9

10105e98 <rtl_crypto_des_ofb_init>:
10105e98:	b570      	push	{r4, r5, r6, lr}
10105e9a:	4b11      	ldr	r3, [pc, #68]	; (10105ee0 <rtl_crypto_des_ofb_init+0x48>)
10105e9c:	781b      	ldrb	r3, [r3, #0]
10105e9e:	2b01      	cmp	r3, #1
10105ea0:	4604      	mov	r4, r0
10105ea2:	460d      	mov	r5, r1
10105ea4:	d004      	beq.n	10105eb0 <rtl_crypto_des_ofb_init+0x18>
10105ea6:	f240 2151 	movw	r1, #593	; 0x251
10105eaa:	480e      	ldr	r0, [pc, #56]	; (10105ee4 <rtl_crypto_des_ofb_init+0x4c>)
10105eac:	f7fa fce0 	bl	10100870 <io_assert_failed>
10105eb0:	b194      	cbz	r4, 10105ed8 <rtl_crypto_des_ofb_init+0x40>
10105eb2:	07a3      	lsls	r3, r4, #30
10105eb4:	d10d      	bne.n	10105ed2 <rtl_crypto_des_ofb_init+0x3a>
10105eb6:	2d20      	cmp	r5, #32
10105eb8:	d808      	bhi.n	10105ecc <rtl_crypto_des_ofb_init+0x34>
10105eba:	4622      	mov	r2, r4
10105ebc:	4c0a      	ldr	r4, [pc, #40]	; (10105ee8 <rtl_crypto_des_ofb_init+0x50>)
10105ebe:	462b      	mov	r3, r5
10105ec0:	46a4      	mov	ip, r4
10105ec2:	2103      	movs	r1, #3
10105ec4:	4806      	ldr	r0, [pc, #24]	; (10105ee0 <rtl_crypto_des_ofb_init+0x48>)
10105ec6:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10105eca:	4760      	bx	ip
10105ecc:	f06f 0006 	mvn.w	r0, #6
10105ed0:	bd70      	pop	{r4, r5, r6, pc}
10105ed2:	f06f 0005 	mvn.w	r0, #5
10105ed6:	bd70      	pop	{r4, r5, r6, pc}
10105ed8:	f06f 0003 	mvn.w	r0, #3
10105edc:	bd70      	pop	{r4, r5, r6, pc}
10105ede:	bf00      	nop
10105ee0:	100003a0 	.word	0x100003a0
10105ee4:	101d53c4 	.word	0x101d53c4
10105ee8:	10105799 	.word	0x10105799

10105eec <rtl_crypto_des_ofb_encrypt>:
10105eec:	b570      	push	{r4, r5, r6, lr}
10105eee:	b086      	sub	sp, #24
10105ef0:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105ef2:	b178      	cbz	r0, 10105f14 <rtl_crypto_des_ofb_encrypt+0x28>
10105ef4:	b176      	cbz	r6, 10105f14 <rtl_crypto_des_ofb_encrypt+0x28>
10105ef6:	461c      	mov	r4, r3
10105ef8:	2500      	movs	r5, #0
10105efa:	4613      	mov	r3, r2
10105efc:	9400      	str	r4, [sp, #0]
10105efe:	460a      	mov	r2, r1
10105f00:	9603      	str	r6, [sp, #12]
10105f02:	4601      	mov	r1, r0
10105f04:	9504      	str	r5, [sp, #16]
10105f06:	9502      	str	r5, [sp, #8]
10105f08:	9501      	str	r5, [sp, #4]
10105f0a:	4804      	ldr	r0, [pc, #16]	; (10105f1c <rtl_crypto_des_ofb_encrypt+0x30>)
10105f0c:	4c04      	ldr	r4, [pc, #16]	; (10105f20 <rtl_crypto_des_ofb_encrypt+0x34>)
10105f0e:	47a0      	blx	r4
10105f10:	b006      	add	sp, #24
10105f12:	bd70      	pop	{r4, r5, r6, pc}
10105f14:	f06f 0003 	mvn.w	r0, #3
10105f18:	e7fa      	b.n	10105f10 <rtl_crypto_des_ofb_encrypt+0x24>
10105f1a:	bf00      	nop
10105f1c:	100003a0 	.word	0x100003a0
10105f20:	101057b9 	.word	0x101057b9

10105f24 <rtl_crypto_des_ofb_decrypt>:
10105f24:	b570      	push	{r4, r5, r6, lr}
10105f26:	b086      	sub	sp, #24
10105f28:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105f2a:	b178      	cbz	r0, 10105f4c <rtl_crypto_des_ofb_decrypt+0x28>
10105f2c:	b176      	cbz	r6, 10105f4c <rtl_crypto_des_ofb_decrypt+0x28>
10105f2e:	461c      	mov	r4, r3
10105f30:	2500      	movs	r5, #0
10105f32:	4613      	mov	r3, r2
10105f34:	9400      	str	r4, [sp, #0]
10105f36:	460a      	mov	r2, r1
10105f38:	9603      	str	r6, [sp, #12]
10105f3a:	4601      	mov	r1, r0
10105f3c:	9504      	str	r5, [sp, #16]
10105f3e:	9502      	str	r5, [sp, #8]
10105f40:	9501      	str	r5, [sp, #4]
10105f42:	4804      	ldr	r0, [pc, #16]	; (10105f54 <rtl_crypto_des_ofb_decrypt+0x30>)
10105f44:	4c04      	ldr	r4, [pc, #16]	; (10105f58 <rtl_crypto_des_ofb_decrypt+0x34>)
10105f46:	47a0      	blx	r4
10105f48:	b006      	add	sp, #24
10105f4a:	bd70      	pop	{r4, r5, r6, pc}
10105f4c:	f06f 0003 	mvn.w	r0, #3
10105f50:	e7fa      	b.n	10105f48 <rtl_crypto_des_ofb_decrypt+0x24>
10105f52:	bf00      	nop
10105f54:	100003a0 	.word	0x100003a0
10105f58:	101057e9 	.word	0x101057e9

10105f5c <rtl_crypto_des_ctr_init>:
10105f5c:	b570      	push	{r4, r5, r6, lr}
10105f5e:	4b11      	ldr	r3, [pc, #68]	; (10105fa4 <rtl_crypto_des_ctr_init+0x48>)
10105f60:	781b      	ldrb	r3, [r3, #0]
10105f62:	2b01      	cmp	r3, #1
10105f64:	4604      	mov	r4, r0
10105f66:	460d      	mov	r5, r1
10105f68:	d004      	beq.n	10105f74 <rtl_crypto_des_ctr_init+0x18>
10105f6a:	f240 2195 	movw	r1, #661	; 0x295
10105f6e:	480e      	ldr	r0, [pc, #56]	; (10105fa8 <rtl_crypto_des_ctr_init+0x4c>)
10105f70:	f7fa fc7e 	bl	10100870 <io_assert_failed>
10105f74:	b194      	cbz	r4, 10105f9c <rtl_crypto_des_ctr_init+0x40>
10105f76:	07a3      	lsls	r3, r4, #30
10105f78:	d10d      	bne.n	10105f96 <rtl_crypto_des_ctr_init+0x3a>
10105f7a:	2d20      	cmp	r5, #32
10105f7c:	d808      	bhi.n	10105f90 <rtl_crypto_des_ctr_init+0x34>
10105f7e:	4622      	mov	r2, r4
10105f80:	4c0a      	ldr	r4, [pc, #40]	; (10105fac <rtl_crypto_des_ctr_init+0x50>)
10105f82:	462b      	mov	r3, r5
10105f84:	46a4      	mov	ip, r4
10105f86:	2104      	movs	r1, #4
10105f88:	4806      	ldr	r0, [pc, #24]	; (10105fa4 <rtl_crypto_des_ctr_init+0x48>)
10105f8a:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
10105f8e:	4760      	bx	ip
10105f90:	f06f 0006 	mvn.w	r0, #6
10105f94:	bd70      	pop	{r4, r5, r6, pc}
10105f96:	f06f 0005 	mvn.w	r0, #5
10105f9a:	bd70      	pop	{r4, r5, r6, pc}
10105f9c:	f06f 0003 	mvn.w	r0, #3
10105fa0:	bd70      	pop	{r4, r5, r6, pc}
10105fa2:	bf00      	nop
10105fa4:	100003a0 	.word	0x100003a0
10105fa8:	101d5310 	.word	0x101d5310
10105fac:	10105799 	.word	0x10105799

10105fb0 <rtl_crypto_des_ctr_encrypt>:
10105fb0:	b570      	push	{r4, r5, r6, lr}
10105fb2:	b086      	sub	sp, #24
10105fb4:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105fb6:	b178      	cbz	r0, 10105fd8 <rtl_crypto_des_ctr_encrypt+0x28>
10105fb8:	b176      	cbz	r6, 10105fd8 <rtl_crypto_des_ctr_encrypt+0x28>
10105fba:	461c      	mov	r4, r3
10105fbc:	2500      	movs	r5, #0
10105fbe:	4613      	mov	r3, r2
10105fc0:	9400      	str	r4, [sp, #0]
10105fc2:	460a      	mov	r2, r1
10105fc4:	9603      	str	r6, [sp, #12]
10105fc6:	4601      	mov	r1, r0
10105fc8:	9504      	str	r5, [sp, #16]
10105fca:	9502      	str	r5, [sp, #8]
10105fcc:	9501      	str	r5, [sp, #4]
10105fce:	4804      	ldr	r0, [pc, #16]	; (10105fe0 <rtl_crypto_des_ctr_encrypt+0x30>)
10105fd0:	4c04      	ldr	r4, [pc, #16]	; (10105fe4 <rtl_crypto_des_ctr_encrypt+0x34>)
10105fd2:	47a0      	blx	r4
10105fd4:	b006      	add	sp, #24
10105fd6:	bd70      	pop	{r4, r5, r6, pc}
10105fd8:	f06f 0003 	mvn.w	r0, #3
10105fdc:	e7fa      	b.n	10105fd4 <rtl_crypto_des_ctr_encrypt+0x24>
10105fde:	bf00      	nop
10105fe0:	100003a0 	.word	0x100003a0
10105fe4:	101057b9 	.word	0x101057b9

10105fe8 <rtl_crypto_des_ctr_decrypt>:
10105fe8:	b570      	push	{r4, r5, r6, lr}
10105fea:	b086      	sub	sp, #24
10105fec:	9e0a      	ldr	r6, [sp, #40]	; 0x28
10105fee:	b178      	cbz	r0, 10106010 <rtl_crypto_des_ctr_decrypt+0x28>
10105ff0:	b176      	cbz	r6, 10106010 <rtl_crypto_des_ctr_decrypt+0x28>
10105ff2:	461c      	mov	r4, r3
10105ff4:	2500      	movs	r5, #0
10105ff6:	4613      	mov	r3, r2
10105ff8:	9400      	str	r4, [sp, #0]
10105ffa:	460a      	mov	r2, r1
10105ffc:	9603      	str	r6, [sp, #12]
10105ffe:	4601      	mov	r1, r0
10106000:	9504      	str	r5, [sp, #16]
10106002:	9502      	str	r5, [sp, #8]
10106004:	9501      	str	r5, [sp, #4]
10106006:	4804      	ldr	r0, [pc, #16]	; (10106018 <rtl_crypto_des_ctr_decrypt+0x30>)
10106008:	4c04      	ldr	r4, [pc, #16]	; (1010601c <rtl_crypto_des_ctr_decrypt+0x34>)
1010600a:	47a0      	blx	r4
1010600c:	b006      	add	sp, #24
1010600e:	bd70      	pop	{r4, r5, r6, pc}
10106010:	f06f 0003 	mvn.w	r0, #3
10106014:	e7fa      	b.n	1010600c <rtl_crypto_des_ctr_decrypt+0x24>
10106016:	bf00      	nop
10106018:	100003a0 	.word	0x100003a0
1010601c:	101057e9 	.word	0x101057e9

10106020 <RCC_PeriphClockCmd>:
10106020:	0f8b      	lsrs	r3, r1, #30
10106022:	2b03      	cmp	r3, #3
10106024:	b430      	push	{r4, r5}
10106026:	d005      	beq.n	10106034 <RCC_PeriphClockCmd+0x14>
10106028:	2b02      	cmp	r3, #2
1010602a:	d031      	beq.n	10106090 <RCC_PeriphClockCmd+0x70>
1010602c:	2b01      	cmp	r3, #1
1010602e:	d037      	beq.n	101060a0 <RCC_PeriphClockCmd+0x80>
10106030:	bc30      	pop	{r4, r5}
10106032:	4770      	bx	lr
10106034:	f44f 7404 	mov.w	r4, #528	; 0x210
10106038:	0f83      	lsrs	r3, r0, #30
1010603a:	2b03      	cmp	r3, #3
1010603c:	d02d      	beq.n	1010609a <RCC_PeriphClockCmd+0x7a>
1010603e:	2b02      	cmp	r3, #2
10106040:	d031      	beq.n	101060a6 <RCC_PeriphClockCmd+0x86>
10106042:	2b01      	cmp	r3, #1
10106044:	bf14      	ite	ne
10106046:	f44f 7303 	movne.w	r3, #524	; 0x20c
1010604a:	f44f 7302 	moveq.w	r3, #520	; 0x208
1010604e:	f020 4540 	bic.w	r5, r0, #3221225472	; 0xc0000000
10106052:	b199      	cbz	r1, 1010607c <RCC_PeriphClockCmd+0x5c>
10106054:	f104 4480 	add.w	r4, r4, #1073741824	; 0x40000000
10106058:	2a01      	cmp	r2, #1
1010605a:	f021 4140 	bic.w	r1, r1, #3221225472	; 0xc0000000
1010605e:	6822      	ldr	r2, [r4, #0]
10106060:	d024      	beq.n	101060ac <RCC_PeriphClockCmd+0x8c>
10106062:	ea22 0101 	bic.w	r1, r2, r1
10106066:	6021      	str	r1, [r4, #0]
10106068:	2800      	cmp	r0, #0
1010606a:	d0e1      	beq.n	10106030 <RCC_PeriphClockCmd+0x10>
1010606c:	f103 4380 	add.w	r3, r3, #1073741824	; 0x40000000
10106070:	681a      	ldr	r2, [r3, #0]
10106072:	ea22 0205 	bic.w	r2, r2, r5
10106076:	601a      	str	r2, [r3, #0]
10106078:	bc30      	pop	{r4, r5}
1010607a:	4770      	bx	lr
1010607c:	2800      	cmp	r0, #0
1010607e:	d0d7      	beq.n	10106030 <RCC_PeriphClockCmd+0x10>
10106080:	2a01      	cmp	r2, #1
10106082:	d1f3      	bne.n	1010606c <RCC_PeriphClockCmd+0x4c>
10106084:	f103 4380 	add.w	r3, r3, #1073741824	; 0x40000000
10106088:	681a      	ldr	r2, [r3, #0]
1010608a:	432a      	orrs	r2, r5
1010608c:	601a      	str	r2, [r3, #0]
1010608e:	e7cf      	b.n	10106030 <RCC_PeriphClockCmd+0x10>
10106090:	0f83      	lsrs	r3, r0, #30
10106092:	2b03      	cmp	r3, #3
10106094:	f44f 7405 	mov.w	r4, #532	; 0x214
10106098:	d1d1      	bne.n	1010603e <RCC_PeriphClockCmd+0x1e>
1010609a:	f44f 7300 	mov.w	r3, #512	; 0x200
1010609e:	e7d6      	b.n	1010604e <RCC_PeriphClockCmd+0x2e>
101060a0:	f44f 7406 	mov.w	r4, #536	; 0x218
101060a4:	e7c8      	b.n	10106038 <RCC_PeriphClockCmd+0x18>
101060a6:	f44f 7301 	mov.w	r3, #516	; 0x204
101060aa:	e7d0      	b.n	1010604e <RCC_PeriphClockCmd+0x2e>
101060ac:	4311      	orrs	r1, r2
101060ae:	6021      	str	r1, [r4, #0]
101060b0:	2800      	cmp	r0, #0
101060b2:	d1e7      	bne.n	10106084 <RCC_PeriphClockCmd+0x64>
101060b4:	e7bc      	b.n	10106030 <RCC_PeriphClockCmd+0x10>
101060b6:	bf00      	nop

101060b8 <RCC_PeriphClockSource_RTC>:
101060b8:	b538      	push	{r3, r4, r5, lr}
101060ba:	b930      	cbnz	r0, 101060ca <RCC_PeriphClockSource_RTC+0x12>
101060bc:	4b0e      	ldr	r3, [pc, #56]	; (101060f8 <RCC_PeriphClockSource_RTC+0x40>)
101060be:	681b      	ldr	r3, [r3, #0]
101060c0:	4a0d      	ldr	r2, [pc, #52]	; (101060f8 <RCC_PeriphClockSource_RTC+0x40>)
101060c2:	f423 7380 	bic.w	r3, r3, #256	; 0x100
101060c6:	6013      	str	r3, [r2, #0]
101060c8:	bd38      	pop	{r3, r4, r5, pc}
101060ca:	4d0c      	ldr	r5, [pc, #48]	; (101060fc <RCC_PeriphClockSource_RTC+0x44>)
101060cc:	682b      	ldr	r3, [r5, #0]
101060ce:	f423 23ff 	bic.w	r3, r3, #522240	; 0x7f800
101060d2:	f423 63e0 	bic.w	r3, r3, #1792	; 0x700
101060d6:	4a0a      	ldr	r2, [pc, #40]	; (10106100 <RCC_PeriphClockSource_RTC+0x48>)
101060d8:	f043 0401 	orr.w	r4, r3, #1
101060dc:	4790      	blx	r2
101060de:	f500 4080 	add.w	r0, r0, #16384	; 0x4000
101060e2:	0bc3      	lsrs	r3, r0, #15
101060e4:	ea44 2303 	orr.w	r3, r4, r3, lsl #8
101060e8:	602b      	str	r3, [r5, #0]
101060ea:	4b03      	ldr	r3, [pc, #12]	; (101060f8 <RCC_PeriphClockSource_RTC+0x40>)
101060ec:	681b      	ldr	r3, [r3, #0]
101060ee:	4a02      	ldr	r2, [pc, #8]	; (101060f8 <RCC_PeriphClockSource_RTC+0x40>)
101060f0:	f443 7380 	orr.w	r3, r3, #256	; 0x100
101060f4:	6013      	str	r3, [r2, #0]
101060f6:	bd38      	pop	{r3, r4, r5, pc}
101060f8:	48000004 	.word	0x48000004
101060fc:	48000330 	.word	0x48000330
10106100:	101044e9 	.word	0x101044e9

10106104 <RCC_PeriphClockSource_I2C>:
10106104:	4b06      	ldr	r3, [pc, #24]	; (10106120 <RCC_PeriphClockSource_I2C+0x1c>)
10106106:	681b      	ldr	r3, [r3, #0]
10106108:	b921      	cbnz	r1, 10106114 <RCC_PeriphClockSource_I2C+0x10>
1010610a:	4a05      	ldr	r2, [pc, #20]	; (10106120 <RCC_PeriphClockSource_I2C+0x1c>)
1010610c:	f423 6300 	bic.w	r3, r3, #2048	; 0x800
10106110:	6013      	str	r3, [r2, #0]
10106112:	4770      	bx	lr
10106114:	4a02      	ldr	r2, [pc, #8]	; (10106120 <RCC_PeriphClockSource_I2C+0x1c>)
10106116:	f443 6300 	orr.w	r3, r3, #2048	; 0x800
1010611a:	6013      	str	r3, [r2, #0]
1010611c:	4770      	bx	lr
1010611e:	bf00      	nop
10106120:	48000214 	.word	0x48000214

10106124 <RCC_PeriphClockSource_QDEC>:
10106124:	4b06      	ldr	r3, [pc, #24]	; (10106140 <RCC_PeriphClockSource_QDEC+0x1c>)
10106126:	681b      	ldr	r3, [r3, #0]
10106128:	b921      	cbnz	r1, 10106134 <RCC_PeriphClockSource_QDEC+0x10>
1010612a:	4a05      	ldr	r2, [pc, #20]	; (10106140 <RCC_PeriphClockSource_QDEC+0x1c>)
1010612c:	f423 3300 	bic.w	r3, r3, #131072	; 0x20000
10106130:	6013      	str	r3, [r2, #0]
10106132:	4770      	bx	lr
10106134:	4a02      	ldr	r2, [pc, #8]	; (10106140 <RCC_PeriphClockSource_QDEC+0x1c>)
10106136:	f443 3300 	orr.w	r3, r3, #131072	; 0x20000
1010613a:	6013      	str	r3, [r2, #0]
1010613c:	4770      	bx	lr
1010613e:	bf00      	nop
10106140:	48000214 	.word	0x48000214

10106144 <RCC_PeriphClockSource_UART>:
10106144:	2902      	cmp	r1, #2
10106146:	b538      	push	{r3, r4, r5, lr}
10106148:	460d      	mov	r5, r1
1010614a:	4604      	mov	r4, r0
1010614c:	d903      	bls.n	10106156 <RCC_PeriphClockSource_UART+0x12>
1010614e:	21c2      	movs	r1, #194	; 0xc2
10106150:	4815      	ldr	r0, [pc, #84]	; (101061a8 <RCC_PeriphClockSource_UART+0x64>)
10106152:	f7fa fb8d 	bl	10100870 <io_assert_failed>
10106156:	f1b4 2f40 	cmp.w	r4, #1073758208	; 0x40004000
1010615a:	d014      	beq.n	10106186 <RCC_PeriphClockSource_UART+0x42>
1010615c:	4b13      	ldr	r3, [pc, #76]	; (101061ac <RCC_PeriphClockSource_UART+0x68>)
1010615e:	429c      	cmp	r4, r3
10106160:	d019      	beq.n	10106196 <RCC_PeriphClockSource_UART+0x52>
10106162:	f5a3 4380 	sub.w	r3, r3, #16384	; 0x4000
10106166:	429c      	cmp	r4, r3
10106168:	d005      	beq.n	10106176 <RCC_PeriphClockSource_UART+0x32>
1010616a:	21c3      	movs	r1, #195	; 0xc3
1010616c:	480e      	ldr	r0, [pc, #56]	; (101061a8 <RCC_PeriphClockSource_UART+0x64>)
1010616e:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
10106172:	f7fa bb7d 	b.w	10100870 <io_assert_failed>
10106176:	4a0e      	ldr	r2, [pc, #56]	; (101061b0 <RCC_PeriphClockSource_UART+0x6c>)
10106178:	6813      	ldr	r3, [r2, #0]
1010617a:	f023 6340 	bic.w	r3, r3, #201326592	; 0xc000000
1010617e:	ea43 6585 	orr.w	r5, r3, r5, lsl #26
10106182:	6015      	str	r5, [r2, #0]
10106184:	bd38      	pop	{r3, r4, r5, pc}
10106186:	4a0b      	ldr	r2, [pc, #44]	; (101061b4 <RCC_PeriphClockSource_UART+0x70>)
10106188:	6813      	ldr	r3, [r2, #0]
1010618a:	f023 0330 	bic.w	r3, r3, #48	; 0x30
1010618e:	ea43 1505 	orr.w	r5, r3, r5, lsl #4
10106192:	6015      	str	r5, [r2, #0]
10106194:	bd38      	pop	{r3, r4, r5, pc}
10106196:	4a06      	ldr	r2, [pc, #24]	; (101061b0 <RCC_PeriphClockSource_UART+0x6c>)
10106198:	6813      	ldr	r3, [r2, #0]
1010619a:	f023 7340 	bic.w	r3, r3, #50331648	; 0x3000000
1010619e:	ea43 6505 	orr.w	r5, r3, r5, lsl #24
101061a2:	6015      	str	r5, [r2, #0]
101061a4:	bd38      	pop	{r3, r4, r5, pc}
101061a6:	bf00      	nop
101061a8:	101d5414 	.word	0x101d5414
101061ac:	48012000 	.word	0x48012000
101061b0:	48000214 	.word	0x48000214
101061b4:	40000210 	.word	0x40000210

101061b8 <SYSCFG_GetChipInfo>:
101061b8:	4b01      	ldr	r3, [pc, #4]	; (101061c0 <SYSCFG_GetChipInfo+0x8>)
101061ba:	6818      	ldr	r0, [r3, #0]
101061bc:	4770      	bx	lr
101061be:	bf00      	nop
101061c0:	480003f0 	.word	0x480003f0

101061c4 <INT_HardFault>:
101061c4:	f3ef 8008 	mrs	r0, MSP
101061c8:	f3ef 8109 	mrs	r1, PSP
101061cc:	4672      	mov	r2, lr
101061ce:	f04f 0300 	mov.w	r3, #0
101061d2:	f1a0 0480 	sub.w	r4, r0, #128	; 0x80
101061d6:	f384 8808 	msr	MSP, r4
101061da:	f8df 4934 	ldr.w	r4, [pc, #2356]	; 10106b10 <irq_unregister+0x1c>
101061de:	4720      	bx	r4
101061e0:	4770      	bx	lr
101061e2:	bf00      	nop

101061e4 <INT_MemManage>:
101061e4:	f3ef 8008 	mrs	r0, MSP
101061e8:	f3ef 8109 	mrs	r1, PSP
101061ec:	4672      	mov	r2, lr
101061ee:	f04f 0303 	mov.w	r3, #3
101061f2:	f1a0 0480 	sub.w	r4, r0, #128	; 0x80
101061f6:	f384 8808 	msr	MSP, r4
101061fa:	f8df 4914 	ldr.w	r4, [pc, #2324]	; 10106b10 <irq_unregister+0x1c>
101061fe:	4720      	bx	r4
10106200:	4770      	bx	lr
10106202:	bf00      	nop

10106204 <INT_BusFault>:
10106204:	f3ef 8008 	mrs	r0, MSP
10106208:	f3ef 8109 	mrs	r1, PSP
1010620c:	4672      	mov	r2, lr
1010620e:	f04f 0302 	mov.w	r3, #2
10106212:	f1a0 0480 	sub.w	r4, r0, #128	; 0x80
10106216:	f384 8808 	msr	MSP, r4
1010621a:	f8df 48f4 	ldr.w	r4, [pc, #2292]	; 10106b10 <irq_unregister+0x1c>
1010621e:	4720      	bx	r4
10106220:	4770      	bx	lr
10106222:	bf00      	nop

10106224 <INT_UsageFault>:
10106224:	f3ef 8008 	mrs	r0, MSP
10106228:	f3ef 8109 	mrs	r1, PSP
1010622c:	4672      	mov	r2, lr
1010622e:	f04f 0301 	mov.w	r3, #1
10106232:	f1a0 0480 	sub.w	r4, r0, #128	; 0x80
10106236:	f384 8808 	msr	MSP, r4
1010623a:	f8df 48d4 	ldr.w	r4, [pc, #2260]	; 10106b10 <irq_unregister+0x1c>
1010623e:	4720      	bx	r4
10106240:	4770      	bx	lr
10106242:	bf00      	nop

10106244 <INT_SecureFault>:
10106244:	f3ef 8008 	mrs	r0, MSP
10106248:	f3ef 8109 	mrs	r1, PSP
1010624c:	4672      	mov	r2, lr
1010624e:	f04f 0304 	mov.w	r3, #4
10106252:	f1a0 0480 	sub.w	r4, r0, #128	; 0x80
10106256:	f384 8808 	msr	MSP, r4
1010625a:	f8df 48b4 	ldr.w	r4, [pc, #2228]	; 10106b10 <irq_unregister+0x1c>
1010625e:	4720      	bx	r4
10106260:	4770      	bx	lr
10106262:	bf00      	nop

10106264 <INT_HardFault_C>:
10106264:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
10106268:	4e9c      	ldr	r6, [pc, #624]	; (101064dc <INT_HardFault_C+0x278>)
1010626a:	e846 f600 	tt	r6, r6
1010626e:	4605      	mov	r5, r0
10106270:	460f      	mov	r7, r1
10106272:	4690      	mov	r8, r2
10106274:	f3c6 5680 	ubfx	r6, r6, #22, #1
10106278:	4c99      	ldr	r4, [pc, #612]	; (101064e0 <INT_HardFault_C+0x27c>)
1010627a:	2b00      	cmp	r3, #0
1010627c:	f040 81a0 	bne.w	101065c0 <INT_HardFault_C+0x35c>
10106280:	6823      	ldr	r3, [r4, #0]
10106282:	0399      	lsls	r1, r3, #14
10106284:	d45a      	bmi.n	1010633c <INT_HardFault_C+0xd8>
10106286:	b116      	cbz	r6, 1010628e <INT_HardFault_C+0x2a>
10106288:	6823      	ldr	r3, [r4, #0]
1010628a:	0398      	lsls	r0, r3, #14
1010628c:	d400      	bmi.n	10106290 <INT_HardFault_C+0x2c>
1010628e:	e7fe      	b.n	1010628e <INT_HardFault_C+0x2a>
10106290:	f3ef 8188 	mrs	r1, MSP_NS
10106294:	4893      	ldr	r0, [pc, #588]	; (101064e4 <INT_HardFault_C+0x280>)
10106296:	f7fa f8ad 	bl	101003f4 <DiagPrintf>
1010629a:	6823      	ldr	r3, [r4, #0]
1010629c:	0399      	lsls	r1, r3, #14
1010629e:	d5f6      	bpl.n	1010628e <INT_HardFault_C+0x2a>
101062a0:	f3ef 8189 	mrs	r1, PSP_NS
101062a4:	4890      	ldr	r0, [pc, #576]	; (101064e8 <INT_HardFault_C+0x284>)
101062a6:	f7fa f8a5 	bl	101003f4 <DiagPrintf>
101062aa:	6823      	ldr	r3, [r4, #0]
101062ac:	039a      	lsls	r2, r3, #14
101062ae:	d5ee      	bpl.n	1010628e <INT_HardFault_C+0x2a>
101062b0:	4b8e      	ldr	r3, [pc, #568]	; (101064ec <INT_HardFault_C+0x288>)
101062b2:	488f      	ldr	r0, [pc, #572]	; (101064f0 <INT_HardFault_C+0x28c>)
101062b4:	6819      	ldr	r1, [r3, #0]
101062b6:	f7fa f89d 	bl	101003f4 <DiagPrintf>
101062ba:	6823      	ldr	r3, [r4, #0]
101062bc:	039b      	lsls	r3, r3, #14
101062be:	d5e6      	bpl.n	1010628e <INT_HardFault_C+0x2a>
101062c0:	4b8c      	ldr	r3, [pc, #560]	; (101064f4 <INT_HardFault_C+0x290>)
101062c2:	488d      	ldr	r0, [pc, #564]	; (101064f8 <INT_HardFault_C+0x294>)
101062c4:	6819      	ldr	r1, [r3, #0]
101062c6:	f7fa f895 	bl	101003f4 <DiagPrintf>
101062ca:	6823      	ldr	r3, [r4, #0]
101062cc:	039f      	lsls	r7, r3, #14
101062ce:	d5de      	bpl.n	1010628e <INT_HardFault_C+0x2a>
101062d0:	4b8a      	ldr	r3, [pc, #552]	; (101064fc <INT_HardFault_C+0x298>)
101062d2:	488b      	ldr	r0, [pc, #556]	; (10106500 <INT_HardFault_C+0x29c>)
101062d4:	6819      	ldr	r1, [r3, #0]
101062d6:	f7fa f88d 	bl	101003f4 <DiagPrintf>
101062da:	6823      	ldr	r3, [r4, #0]
101062dc:	039e      	lsls	r6, r3, #14
101062de:	d5d6      	bpl.n	1010628e <INT_HardFault_C+0x2a>
101062e0:	4b88      	ldr	r3, [pc, #544]	; (10106504 <INT_HardFault_C+0x2a0>)
101062e2:	4889      	ldr	r0, [pc, #548]	; (10106508 <INT_HardFault_C+0x2a4>)
101062e4:	6819      	ldr	r1, [r3, #0]
101062e6:	f7fa f885 	bl	101003f4 <DiagPrintf>
101062ea:	6823      	ldr	r3, [r4, #0]
101062ec:	039d      	lsls	r5, r3, #14
101062ee:	d5ce      	bpl.n	1010628e <INT_HardFault_C+0x2a>
101062f0:	4b86      	ldr	r3, [pc, #536]	; (1010650c <INT_HardFault_C+0x2a8>)
101062f2:	4887      	ldr	r0, [pc, #540]	; (10106510 <INT_HardFault_C+0x2ac>)
101062f4:	6819      	ldr	r1, [r3, #0]
101062f6:	f7fa f87d 	bl	101003f4 <DiagPrintf>
101062fa:	6823      	ldr	r3, [r4, #0]
101062fc:	0398      	lsls	r0, r3, #14
101062fe:	d5c6      	bpl.n	1010628e <INT_HardFault_C+0x2a>
10106300:	4b84      	ldr	r3, [pc, #528]	; (10106514 <INT_HardFault_C+0x2b0>)
10106302:	4885      	ldr	r0, [pc, #532]	; (10106518 <INT_HardFault_C+0x2b4>)
10106304:	6819      	ldr	r1, [r3, #0]
10106306:	f7fa f875 	bl	101003f4 <DiagPrintf>
1010630a:	6823      	ldr	r3, [r4, #0]
1010630c:	0399      	lsls	r1, r3, #14
1010630e:	d5be      	bpl.n	1010628e <INT_HardFault_C+0x2a>
10106310:	4b82      	ldr	r3, [pc, #520]	; (1010651c <INT_HardFault_C+0x2b8>)
10106312:	4883      	ldr	r0, [pc, #524]	; (10106520 <INT_HardFault_C+0x2bc>)
10106314:	7819      	ldrb	r1, [r3, #0]
10106316:	f7fa f86d 	bl	101003f4 <DiagPrintf>
1010631a:	6823      	ldr	r3, [r4, #0]
1010631c:	039a      	lsls	r2, r3, #14
1010631e:	d5b6      	bpl.n	1010628e <INT_HardFault_C+0x2a>
10106320:	4b80      	ldr	r3, [pc, #512]	; (10106524 <INT_HardFault_C+0x2c0>)
10106322:	4881      	ldr	r0, [pc, #516]	; (10106528 <INT_HardFault_C+0x2c4>)
10106324:	7819      	ldrb	r1, [r3, #0]
10106326:	f7fa f865 	bl	101003f4 <DiagPrintf>
1010632a:	6823      	ldr	r3, [r4, #0]
1010632c:	039b      	lsls	r3, r3, #14
1010632e:	d5ae      	bpl.n	1010628e <INT_HardFault_C+0x2a>
10106330:	4b7e      	ldr	r3, [pc, #504]	; (1010652c <INT_HardFault_C+0x2c8>)
10106332:	487f      	ldr	r0, [pc, #508]	; (10106530 <INT_HardFault_C+0x2cc>)
10106334:	7819      	ldrb	r1, [r3, #0]
10106336:	f7fa f85d 	bl	101003f4 <DiagPrintf>
1010633a:	e7a8      	b.n	1010628e <INT_HardFault_C+0x2a>
1010633c:	487d      	ldr	r0, [pc, #500]	; (10106534 <INT_HardFault_C+0x2d0>)
1010633e:	f7fa f859 	bl	101003f4 <DiagPrintf>
10106342:	6823      	ldr	r3, [r4, #0]
10106344:	039b      	lsls	r3, r3, #14
10106346:	d59e      	bpl.n	10106286 <INT_HardFault_C+0x22>
10106348:	4631      	mov	r1, r6
1010634a:	487b      	ldr	r0, [pc, #492]	; (10106538 <INT_HardFault_C+0x2d4>)
1010634c:	f7fa f852 	bl	101003f4 <DiagPrintf>
10106350:	6823      	ldr	r3, [r4, #0]
10106352:	0398      	lsls	r0, r3, #14
10106354:	d597      	bpl.n	10106286 <INT_HardFault_C+0x22>
10106356:	4879      	ldr	r0, [pc, #484]	; (1010653c <INT_HardFault_C+0x2d8>)
10106358:	f7fa f84c 	bl	101003f4 <DiagPrintf>
1010635c:	6823      	ldr	r3, [r4, #0]
1010635e:	0399      	lsls	r1, r3, #14
10106360:	d591      	bpl.n	10106286 <INT_HardFault_C+0x22>
10106362:	6829      	ldr	r1, [r5, #0]
10106364:	4876      	ldr	r0, [pc, #472]	; (10106540 <INT_HardFault_C+0x2dc>)
10106366:	f7fa f845 	bl	101003f4 <DiagPrintf>
1010636a:	6823      	ldr	r3, [r4, #0]
1010636c:	039a      	lsls	r2, r3, #14
1010636e:	d58a      	bpl.n	10106286 <INT_HardFault_C+0x22>
10106370:	6869      	ldr	r1, [r5, #4]
10106372:	4874      	ldr	r0, [pc, #464]	; (10106544 <INT_HardFault_C+0x2e0>)
10106374:	f7fa f83e 	bl	101003f4 <DiagPrintf>
10106378:	6823      	ldr	r3, [r4, #0]
1010637a:	039b      	lsls	r3, r3, #14
1010637c:	d583      	bpl.n	10106286 <INT_HardFault_C+0x22>
1010637e:	68a9      	ldr	r1, [r5, #8]
10106380:	4871      	ldr	r0, [pc, #452]	; (10106548 <INT_HardFault_C+0x2e4>)
10106382:	f7fa f837 	bl	101003f4 <DiagPrintf>
10106386:	6823      	ldr	r3, [r4, #0]
10106388:	0398      	lsls	r0, r3, #14
1010638a:	f57f af7c 	bpl.w	10106286 <INT_HardFault_C+0x22>
1010638e:	68e9      	ldr	r1, [r5, #12]
10106390:	486e      	ldr	r0, [pc, #440]	; (1010654c <INT_HardFault_C+0x2e8>)
10106392:	f7fa f82f 	bl	101003f4 <DiagPrintf>
10106396:	6823      	ldr	r3, [r4, #0]
10106398:	0399      	lsls	r1, r3, #14
1010639a:	f57f af74 	bpl.w	10106286 <INT_HardFault_C+0x22>
1010639e:	6929      	ldr	r1, [r5, #16]
101063a0:	486b      	ldr	r0, [pc, #428]	; (10106550 <INT_HardFault_C+0x2ec>)
101063a2:	f7fa f827 	bl	101003f4 <DiagPrintf>
101063a6:	6823      	ldr	r3, [r4, #0]
101063a8:	039a      	lsls	r2, r3, #14
101063aa:	f57f af6c 	bpl.w	10106286 <INT_HardFault_C+0x22>
101063ae:	6969      	ldr	r1, [r5, #20]
101063b0:	4868      	ldr	r0, [pc, #416]	; (10106554 <INT_HardFault_C+0x2f0>)
101063b2:	f7fa f81f 	bl	101003f4 <DiagPrintf>
101063b6:	6823      	ldr	r3, [r4, #0]
101063b8:	039b      	lsls	r3, r3, #14
101063ba:	f57f af64 	bpl.w	10106286 <INT_HardFault_C+0x22>
101063be:	69a9      	ldr	r1, [r5, #24]
101063c0:	4865      	ldr	r0, [pc, #404]	; (10106558 <INT_HardFault_C+0x2f4>)
101063c2:	f7fa f817 	bl	101003f4 <DiagPrintf>
101063c6:	6823      	ldr	r3, [r4, #0]
101063c8:	0398      	lsls	r0, r3, #14
101063ca:	f57f af5c 	bpl.w	10106286 <INT_HardFault_C+0x22>
101063ce:	69e9      	ldr	r1, [r5, #28]
101063d0:	4862      	ldr	r0, [pc, #392]	; (1010655c <INT_HardFault_C+0x2f8>)
101063d2:	f7fa f80f 	bl	101003f4 <DiagPrintf>
101063d6:	6823      	ldr	r3, [r4, #0]
101063d8:	0399      	lsls	r1, r3, #14
101063da:	f57f af54 	bpl.w	10106286 <INT_HardFault_C+0x22>
101063de:	4860      	ldr	r0, [pc, #384]	; (10106560 <INT_HardFault_C+0x2fc>)
101063e0:	f7fa f808 	bl	101003f4 <DiagPrintf>
101063e4:	6823      	ldr	r3, [r4, #0]
101063e6:	039a      	lsls	r2, r3, #14
101063e8:	f57f af4d 	bpl.w	10106286 <INT_HardFault_C+0x22>
101063ec:	4641      	mov	r1, r8
101063ee:	485d      	ldr	r0, [pc, #372]	; (10106564 <INT_HardFault_C+0x300>)
101063f0:	f7fa f800 	bl	101003f4 <DiagPrintf>
101063f4:	6823      	ldr	r3, [r4, #0]
101063f6:	039b      	lsls	r3, r3, #14
101063f8:	f57f af45 	bpl.w	10106286 <INT_HardFault_C+0x22>
101063fc:	4629      	mov	r1, r5
101063fe:	485a      	ldr	r0, [pc, #360]	; (10106568 <INT_HardFault_C+0x304>)
10106400:	f7f9 fff8 	bl	101003f4 <DiagPrintf>
10106404:	6823      	ldr	r3, [r4, #0]
10106406:	0398      	lsls	r0, r3, #14
10106408:	f57f af3d 	bpl.w	10106286 <INT_HardFault_C+0x22>
1010640c:	4639      	mov	r1, r7
1010640e:	4857      	ldr	r0, [pc, #348]	; (1010656c <INT_HardFault_C+0x308>)
10106410:	f7f9 fff0 	bl	101003f4 <DiagPrintf>
10106414:	6823      	ldr	r3, [r4, #0]
10106416:	0399      	lsls	r1, r3, #14
10106418:	f57f af35 	bpl.w	10106286 <INT_HardFault_C+0x22>
1010641c:	f3ef 8103 	mrs	r1, PSR
10106420:	4853      	ldr	r0, [pc, #332]	; (10106570 <INT_HardFault_C+0x30c>)
10106422:	f7f9 ffe7 	bl	101003f4 <DiagPrintf>
10106426:	6823      	ldr	r3, [r4, #0]
10106428:	039a      	lsls	r2, r3, #14
1010642a:	f57f af2c 	bpl.w	10106286 <INT_HardFault_C+0x22>
1010642e:	4b51      	ldr	r3, [pc, #324]	; (10106574 <INT_HardFault_C+0x310>)
10106430:	4851      	ldr	r0, [pc, #324]	; (10106578 <INT_HardFault_C+0x314>)
10106432:	6819      	ldr	r1, [r3, #0]
10106434:	f7f9 ffde 	bl	101003f4 <DiagPrintf>
10106438:	6823      	ldr	r3, [r4, #0]
1010643a:	039b      	lsls	r3, r3, #14
1010643c:	f57f af23 	bpl.w	10106286 <INT_HardFault_C+0x22>
10106440:	4b4e      	ldr	r3, [pc, #312]	; (1010657c <INT_HardFault_C+0x318>)
10106442:	484f      	ldr	r0, [pc, #316]	; (10106580 <INT_HardFault_C+0x31c>)
10106444:	6819      	ldr	r1, [r3, #0]
10106446:	f7f9 ffd5 	bl	101003f4 <DiagPrintf>
1010644a:	6823      	ldr	r3, [r4, #0]
1010644c:	039f      	lsls	r7, r3, #14
1010644e:	f57f af1a 	bpl.w	10106286 <INT_HardFault_C+0x22>
10106452:	4b4c      	ldr	r3, [pc, #304]	; (10106584 <INT_HardFault_C+0x320>)
10106454:	484c      	ldr	r0, [pc, #304]	; (10106588 <INT_HardFault_C+0x324>)
10106456:	6819      	ldr	r1, [r3, #0]
10106458:	f7f9 ffcc 	bl	101003f4 <DiagPrintf>
1010645c:	6823      	ldr	r3, [r4, #0]
1010645e:	039d      	lsls	r5, r3, #14
10106460:	f57f af11 	bpl.w	10106286 <INT_HardFault_C+0x22>
10106464:	4b49      	ldr	r3, [pc, #292]	; (1010658c <INT_HardFault_C+0x328>)
10106466:	484a      	ldr	r0, [pc, #296]	; (10106590 <INT_HardFault_C+0x32c>)
10106468:	6819      	ldr	r1, [r3, #0]
1010646a:	f7f9 ffc3 	bl	101003f4 <DiagPrintf>
1010646e:	6823      	ldr	r3, [r4, #0]
10106470:	0398      	lsls	r0, r3, #14
10106472:	f57f af08 	bpl.w	10106286 <INT_HardFault_C+0x22>
10106476:	4b47      	ldr	r3, [pc, #284]	; (10106594 <INT_HardFault_C+0x330>)
10106478:	4847      	ldr	r0, [pc, #284]	; (10106598 <INT_HardFault_C+0x334>)
1010647a:	6819      	ldr	r1, [r3, #0]
1010647c:	f7f9 ffba 	bl	101003f4 <DiagPrintf>
10106480:	6823      	ldr	r3, [r4, #0]
10106482:	0399      	lsls	r1, r3, #14
10106484:	f57f aeff 	bpl.w	10106286 <INT_HardFault_C+0x22>
10106488:	4b44      	ldr	r3, [pc, #272]	; (1010659c <INT_HardFault_C+0x338>)
1010648a:	4845      	ldr	r0, [pc, #276]	; (101065a0 <INT_HardFault_C+0x33c>)
1010648c:	6819      	ldr	r1, [r3, #0]
1010648e:	f7f9 ffb1 	bl	101003f4 <DiagPrintf>
10106492:	6823      	ldr	r3, [r4, #0]
10106494:	039a      	lsls	r2, r3, #14
10106496:	f57f aef6 	bpl.w	10106286 <INT_HardFault_C+0x22>
1010649a:	f3ef 8110 	mrs	r1, PRIMASK
1010649e:	4841      	ldr	r0, [pc, #260]	; (101065a4 <INT_HardFault_C+0x340>)
101064a0:	f7f9 ffa8 	bl	101003f4 <DiagPrintf>
101064a4:	6823      	ldr	r3, [r4, #0]
101064a6:	039b      	lsls	r3, r3, #14
101064a8:	f57f aeed 	bpl.w	10106286 <INT_HardFault_C+0x22>
101064ac:	4b3e      	ldr	r3, [pc, #248]	; (101065a8 <INT_HardFault_C+0x344>)
101064ae:	483f      	ldr	r0, [pc, #252]	; (101065ac <INT_HardFault_C+0x348>)
101064b0:	7819      	ldrb	r1, [r3, #0]
101064b2:	f7f9 ff9f 	bl	101003f4 <DiagPrintf>
101064b6:	6823      	ldr	r3, [r4, #0]
101064b8:	039f      	lsls	r7, r3, #14
101064ba:	f57f aee4 	bpl.w	10106286 <INT_HardFault_C+0x22>
101064be:	4b3c      	ldr	r3, [pc, #240]	; (101065b0 <INT_HardFault_C+0x34c>)
101064c0:	483c      	ldr	r0, [pc, #240]	; (101065b4 <INT_HardFault_C+0x350>)
101064c2:	7819      	ldrb	r1, [r3, #0]
101064c4:	f7f9 ff96 	bl	101003f4 <DiagPrintf>
101064c8:	6823      	ldr	r3, [r4, #0]
101064ca:	039d      	lsls	r5, r3, #14
101064cc:	f57f aedb 	bpl.w	10106286 <INT_HardFault_C+0x22>
101064d0:	4b39      	ldr	r3, [pc, #228]	; (101065b8 <INT_HardFault_C+0x354>)
101064d2:	483a      	ldr	r0, [pc, #232]	; (101065bc <INT_HardFault_C+0x358>)
101064d4:	7819      	ldrb	r1, [r3, #0]
101064d6:	f7f9 ff8d 	bl	101003f4 <DiagPrintf>
101064da:	e6d4      	b.n	10106286 <INT_HardFault_C+0x22>
101064dc:	10106265 	.word	0x10106265
101064e0:	1000000c 	.word	0x1000000c
101064e4:	101d4df4 	.word	0x101d4df4
101064e8:	101d4e08 	.word	0x101d4e08
101064ec:	e002ed28 	.word	0xe002ed28
101064f0:	101d4e1c 	.word	0x101d4e1c
101064f4:	e002ed2c 	.word	0xe002ed2c
101064f8:	101d4e34 	.word	0x101d4e34
101064fc:	e002ed30 	.word	0xe002ed30
10106500:	101d4e4c 	.word	0x101d4e4c
10106504:	e002ed34 	.word	0xe002ed34
10106508:	101d4e64 	.word	0x101d4e64
1010650c:	e002ed38 	.word	0xe002ed38
10106510:	101d4e7c 	.word	0x101d4e7c
10106514:	e002ed3c 	.word	0xe002ed3c
10106518:	101d4e94 	.word	0x101d4e94
1010651c:	e002ed1f 	.word	0xe002ed1f
10106520:	101d4eac 	.word	0x101d4eac
10106524:	e002ed22 	.word	0xe002ed22
10106528:	101d4ec8 	.word	0x101d4ec8
1010652c:	e002ed23 	.word	0xe002ed23
10106530:	101d4ee8 	.word	0x101d4ee8
10106534:	101d4b90 	.word	0x101d4b90
10106538:	101d4c18 	.word	0x101d4c18
1010653c:	101d4c2c 	.word	0x101d4c2c
10106540:	101d4c3c 	.word	0x101d4c3c
10106544:	101d4c4c 	.word	0x101d4c4c
10106548:	101d4c5c 	.word	0x101d4c5c
1010654c:	101d4c6c 	.word	0x101d4c6c
10106550:	101d4c7c 	.word	0x101d4c7c
10106554:	101d4c8c 	.word	0x101d4c8c
10106558:	101d4c9c 	.word	0x101d4c9c
1010655c:	101d4cac 	.word	0x101d4cac
10106560:	101d4cbc 	.word	0x101d4cbc
10106564:	101d4ccc 	.word	0x101d4ccc
10106568:	101d4ce4 	.word	0x101d4ce4
1010656c:	101d4cf4 	.word	0x101d4cf4
10106570:	101d4d04 	.word	0x101d4d04
10106574:	e000ed28 	.word	0xe000ed28
10106578:	101d4d18 	.word	0x101d4d18
1010657c:	e000ed2c 	.word	0xe000ed2c
10106580:	101d4d2c 	.word	0x101d4d2c
10106584:	e000ed30 	.word	0xe000ed30
10106588:	101d4d40 	.word	0x101d4d40
1010658c:	e000ed34 	.word	0xe000ed34
10106590:	101d4d54 	.word	0x101d4d54
10106594:	e000ed38 	.word	0xe000ed38
10106598:	101d4d68 	.word	0x101d4d68
1010659c:	e000ed3c 	.word	0xe000ed3c
101065a0:	101d4d7c 	.word	0x101d4d7c
101065a4:	101d4d90 	.word	0x101d4d90
101065a8:	e000ed1f 	.word	0xe000ed1f
101065ac:	101d4da4 	.word	0x101d4da4
101065b0:	e000ed22 	.word	0xe000ed22
101065b4:	101d4dbc 	.word	0x101d4dbc
101065b8:	e000ed23 	.word	0xe000ed23
101065bc:	101d4dd8 	.word	0x101d4dd8
101065c0:	2b01      	cmp	r3, #1
101065c2:	d024      	beq.n	1010660e <INT_HardFault_C+0x3aa>
101065c4:	2b02      	cmp	r3, #2
101065c6:	d012      	beq.n	101065ee <INT_HardFault_C+0x38a>
101065c8:	2b03      	cmp	r3, #3
101065ca:	d018      	beq.n	101065fe <INT_HardFault_C+0x39a>
101065cc:	2b04      	cmp	r3, #4
101065ce:	6823      	ldr	r3, [r4, #0]
101065d0:	d006      	beq.n	101065e0 <INT_HardFault_C+0x37c>
101065d2:	039a      	lsls	r2, r3, #14
101065d4:	f57f ae57 	bpl.w	10106286 <INT_HardFault_C+0x22>
101065d8:	4811      	ldr	r0, [pc, #68]	; (10106620 <INT_HardFault_C+0x3bc>)
101065da:	f7f9 ff0b 	bl	101003f4 <DiagPrintf>
101065de:	e6b0      	b.n	10106342 <INT_HardFault_C+0xde>
101065e0:	0399      	lsls	r1, r3, #14
101065e2:	f57f ae50 	bpl.w	10106286 <INT_HardFault_C+0x22>
101065e6:	480f      	ldr	r0, [pc, #60]	; (10106624 <INT_HardFault_C+0x3c0>)
101065e8:	f7f9 ff04 	bl	101003f4 <DiagPrintf>
101065ec:	e6a9      	b.n	10106342 <INT_HardFault_C+0xde>
101065ee:	6823      	ldr	r3, [r4, #0]
101065f0:	039b      	lsls	r3, r3, #14
101065f2:	f57f ae48 	bpl.w	10106286 <INT_HardFault_C+0x22>
101065f6:	480c      	ldr	r0, [pc, #48]	; (10106628 <INT_HardFault_C+0x3c4>)
101065f8:	f7f9 fefc 	bl	101003f4 <DiagPrintf>
101065fc:	e6a1      	b.n	10106342 <INT_HardFault_C+0xde>
101065fe:	6823      	ldr	r3, [r4, #0]
10106600:	0398      	lsls	r0, r3, #14
10106602:	f57f ae40 	bpl.w	10106286 <INT_HardFault_C+0x22>
10106606:	4809      	ldr	r0, [pc, #36]	; (1010662c <INT_HardFault_C+0x3c8>)
10106608:	f7f9 fef4 	bl	101003f4 <DiagPrintf>
1010660c:	e699      	b.n	10106342 <INT_HardFault_C+0xde>
1010660e:	6823      	ldr	r3, [r4, #0]
10106610:	039a      	lsls	r2, r3, #14
10106612:	f57f ae38 	bpl.w	10106286 <INT_HardFault_C+0x22>
10106616:	4806      	ldr	r0, [pc, #24]	; (10106630 <INT_HardFault_C+0x3cc>)
10106618:	f7f9 feec 	bl	101003f4 <DiagPrintf>
1010661c:	e691      	b.n	10106342 <INT_HardFault_C+0xde>
1010661e:	bf00      	nop
10106620:	101d4bfc 	.word	0x101d4bfc
10106624:	101d4be4 	.word	0x101d4be4
10106628:	101d4bb8 	.word	0x101d4bb8
1010662c:	101d4bcc 	.word	0x101d4bcc
10106630:	101d4ba4 	.word	0x101d4ba4

10106634 <INT_NMI>:
10106634:	4b03      	ldr	r3, [pc, #12]	; (10106644 <INT_NMI+0x10>)
10106636:	681b      	ldr	r3, [r3, #0]
10106638:	039b      	lsls	r3, r3, #14
1010663a:	d400      	bmi.n	1010663e <INT_NMI+0xa>
1010663c:	4770      	bx	lr
1010663e:	4802      	ldr	r0, [pc, #8]	; (10106648 <INT_NMI+0x14>)
10106640:	f7f9 bed8 	b.w	101003f4 <DiagPrintf>
10106644:	1000000c 	.word	0x1000000c
10106648:	101d4f08 	.word	0x101d4f08

1010664c <INT_Entry>:
1010664c:	2800      	cmp	r0, #0
1010664e:	b410      	push	{r4}
10106650:	db08      	blt.n	10106664 <INT_Entry+0x18>
10106652:	2201      	movs	r2, #1
10106654:	f000 041f 	and.w	r4, r0, #31
10106658:	0943      	lsrs	r3, r0, #5
1010665a:	490e      	ldr	r1, [pc, #56]	; (10106694 <INT_Entry+0x48>)
1010665c:	40a2      	lsls	r2, r4
1010665e:	3360      	adds	r3, #96	; 0x60
10106660:	f841 2023 	str.w	r2, [r1, r3, lsl #2]
10106664:	4b0c      	ldr	r3, [pc, #48]	; (10106698 <INT_Entry+0x4c>)
10106666:	f853 3020 	ldr.w	r3, [r3, r0, lsl #2]
1010666a:	b12b      	cbz	r3, 10106678 <INT_Entry+0x2c>
1010666c:	4a0b      	ldr	r2, [pc, #44]	; (1010669c <INT_Entry+0x50>)
1010666e:	f85d 4b04 	ldr.w	r4, [sp], #4
10106672:	f852 0020 	ldr.w	r0, [r2, r0, lsl #2]
10106676:	4718      	bx	r3
10106678:	4b09      	ldr	r3, [pc, #36]	; (101066a0 <INT_Entry+0x54>)
1010667a:	681b      	ldr	r3, [r3, #0]
1010667c:	039b      	lsls	r3, r3, #14
1010667e:	d402      	bmi.n	10106686 <INT_Entry+0x3a>
10106680:	f85d 4b04 	ldr.w	r4, [sp], #4
10106684:	4770      	bx	lr
10106686:	4601      	mov	r1, r0
10106688:	f85d 4b04 	ldr.w	r4, [sp], #4
1010668c:	4805      	ldr	r0, [pc, #20]	; (101066a4 <INT_Entry+0x58>)
1010668e:	f7f9 beb1 	b.w	101003f4 <DiagPrintf>
10106692:	bf00      	nop
10106694:	e000e100 	.word	0xe000e100
10106698:	1007c140 	.word	0x1007c140
1010669c:	1007c240 	.word	0x1007c240
101066a0:	1000000c 	.word	0x1000000c
101066a4:	101d4f20 	.word	0x101d4f20

101066a8 <INT_Gdma0Ch5_S>:
101066a8:	2039      	movs	r0, #57	; 0x39
101066aa:	e7cf      	b.n	1010664c <INT_Entry>

101066ac <INT_Gdma0Ch4_S>:
101066ac:	2038      	movs	r0, #56	; 0x38
101066ae:	e7cd      	b.n	1010664c <INT_Entry>

101066b0 <INT_Gdma0Ch3_S>:
101066b0:	2037      	movs	r0, #55	; 0x37
101066b2:	e7cb      	b.n	1010664c <INT_Entry>

101066b4 <INT_Gdma0Ch2_S>:
101066b4:	2036      	movs	r0, #54	; 0x36
101066b6:	e7c9      	b.n	1010664c <INT_Entry>

101066b8 <INT_Gdma0Ch1_S>:
101066b8:	2035      	movs	r0, #53	; 0x35
101066ba:	e7c7      	b.n	1010664c <INT_Entry>

101066bc <INT_Gdma0Ch0_S>:
101066bc:	2034      	movs	r0, #52	; 0x34
101066be:	e7c5      	b.n	1010664c <INT_Entry>

101066c0 <INT_Gdma0Ch5>:
101066c0:	202e      	movs	r0, #46	; 0x2e
101066c2:	e7c3      	b.n	1010664c <INT_Entry>

101066c4 <INT_Gdma0Ch4>:
101066c4:	202d      	movs	r0, #45	; 0x2d
101066c6:	e7c1      	b.n	1010664c <INT_Entry>

101066c8 <INT_Gdma0Ch3>:
101066c8:	202c      	movs	r0, #44	; 0x2c
101066ca:	e7bf      	b.n	1010664c <INT_Entry>

101066cc <INT_Gdma0Ch2>:
101066cc:	202b      	movs	r0, #43	; 0x2b
101066ce:	e7bd      	b.n	1010664c <INT_Entry>

101066d0 <INT_Gdma0Ch1>:
101066d0:	202a      	movs	r0, #42	; 0x2a
101066d2:	e7bb      	b.n	1010664c <INT_Entry>

101066d4 <INT_Gdma0Ch0>:
101066d4:	2029      	movs	r0, #41	; 0x29
101066d6:	e7b9      	b.n	1010664c <INT_Entry>

101066d8 <INT_BT2WL>:
101066d8:	2028      	movs	r0, #40	; 0x28
101066da:	e7b7      	b.n	1010664c <INT_Entry>

101066dc <INT_IR>:
101066dc:	2027      	movs	r0, #39	; 0x27
101066de:	e7b5      	b.n	1010664c <INT_Entry>

101066e0 <INT_USI>:
101066e0:	2026      	movs	r0, #38	; 0x26
101066e2:	e7b3      	b.n	1010664c <INT_Entry>

101066e4 <INT_SPI1>:
101066e4:	2025      	movs	r0, #37	; 0x25
101066e6:	e7b1      	b.n	1010664c <INT_Entry>

101066e8 <INT_SPI0>:
101066e8:	2024      	movs	r0, #36	; 0x24
101066ea:	e7af      	b.n	1010664c <INT_Entry>

101066ec <INT_Uart1>:
101066ec:	2023      	movs	r0, #35	; 0x23
101066ee:	e7ad      	b.n	1010664c <INT_Entry>

101066f0 <INT_Uart0>:
101066f0:	2022      	movs	r0, #34	; 0x22
101066f2:	e7ab      	b.n	1010664c <INT_Entry>

101066f4 <INT_PSRAMC>:
101066f4:	2021      	movs	r0, #33	; 0x21
101066f6:	e7a9      	b.n	1010664c <INT_Entry>

101066f8 <INT_WlProtocol>:
101066f8:	2020      	movs	r0, #32
101066fa:	e7a7      	b.n	1010664c <INT_Entry>

101066fc <INT_WlDma>:
101066fc:	201f      	movs	r0, #31
101066fe:	e7a5      	b.n	1010664c <INT_Entry>

10106700 <INT_ADCComp>:
10106700:	201e      	movs	r0, #30
10106702:	e7a3      	b.n	1010664c <INT_Entry>

10106704 <INT_PowerDown>:
10106704:	201d      	movs	r0, #29
10106706:	e7a1      	b.n	1010664c <INT_Entry>

10106708 <INT_I2S0>:
10106708:	201c      	movs	r0, #28
1010670a:	e79f      	b.n	1010664c <INT_Entry>

1010670c <INT_IPSEC>:
1010670c:	201b      	movs	r0, #27
1010670e:	e79d      	b.n	1010664c <INT_Entry>

10106710 <INT_SdioH>:
10106710:	201a      	movs	r0, #26
10106712:	e79b      	b.n	1010664c <INT_Entry>

10106714 <INT_SdioD>:
10106714:	2019      	movs	r0, #25
10106716:	e799      	b.n	1010664c <INT_Entry>

10106718 <INT_OTG>:
10106718:	2018      	movs	r0, #24
1010671a:	e797      	b.n	1010664c <INT_Entry>

1010671c <INT_LCDC>:
1010671c:	2017      	movs	r0, #23
1010671e:	e795      	b.n	1010664c <INT_Entry>

10106720 <INT_Timer5>:
10106720:	2016      	movs	r0, #22
10106722:	e793      	b.n	1010664c <INT_Entry>

10106724 <INT_Timer4>:
10106724:	2015      	movs	r0, #21
10106726:	e791      	b.n	1010664c <INT_Entry>

10106728 <INT_Timer3>:
10106728:	2014      	movs	r0, #20
1010672a:	e78f      	b.n	1010664c <INT_Entry>

1010672c <INT_Timer2>:
1010672c:	2013      	movs	r0, #19
1010672e:	e78d      	b.n	1010664c <INT_Entry>

10106730 <INT_Timer1>:
10106730:	2012      	movs	r0, #18
10106732:	e78b      	b.n	1010664c <INT_Entry>

10106734 <INT_Timer0>:
10106734:	2011      	movs	r0, #17
10106736:	e789      	b.n	1010664c <INT_Entry>

10106738 <INT_QDECODER>:
10106738:	2010      	movs	r0, #16
1010673a:	e787      	b.n	1010664c <INT_Entry>

1010673c <INT_ADC>:
1010673c:	200f      	movs	r0, #15
1010673e:	e785      	b.n	1010664c <INT_Entry>

10106740 <INT_IPC>:
10106740:	200e      	movs	r0, #14
10106742:	e783      	b.n	1010664c <INT_Entry>

10106744 <INT_SGPIO>:
10106744:	200d      	movs	r0, #13
10106746:	e781      	b.n	1010664c <INT_Entry>

10106748 <INT_BOR2>:
10106748:	200c      	movs	r0, #12
1010674a:	e77f      	b.n	1010664c <INT_Entry>

1010674c <INT_CTOUCH>:
1010674c:	200b      	movs	r0, #11
1010674e:	e77d      	b.n	1010664c <INT_Entry>

10106750 <INT_KEYSCAN>:
10106750:	200a      	movs	r0, #10
10106752:	e77b      	b.n	1010664c <INT_Entry>

10106754 <INT_UARTLP>:
10106754:	2009      	movs	r0, #9
10106756:	e779      	b.n	1010664c <INT_Entry>

10106758 <INT_GPIOB>:
10106758:	2008      	movs	r0, #8
1010675a:	e777      	b.n	1010664c <INT_Entry>

1010675c <INT_SPIFlash>:
1010675c:	2007      	movs	r0, #7
1010675e:	e775      	b.n	1010664c <INT_Entry>

10106760 <INT_I2C0>:
10106760:	2006      	movs	r0, #6
10106762:	e773      	b.n	1010664c <INT_Entry>

10106764 <INT_RTC>:
10106764:	2005      	movs	r0, #5
10106766:	e771      	b.n	1010664c <INT_Entry>

10106768 <INT_GPIOA>:
10106768:	2004      	movs	r0, #4
1010676a:	e76f      	b.n	1010664c <INT_Entry>

1010676c <INT_Uartlog>:
1010676c:	2003      	movs	r0, #3
1010676e:	e76d      	b.n	1010664c <INT_Entry>

10106770 <INT_RXI300>:
10106770:	2002      	movs	r0, #2
10106772:	e76b      	b.n	1010664c <INT_Entry>

10106774 <INT_Wdg>:
10106774:	2001      	movs	r0, #1
10106776:	e769      	b.n	1010664c <INT_Entry>

10106778 <INT_SysOn>:
10106778:	2000      	movs	r0, #0
1010677a:	e767      	b.n	1010664c <INT_Entry>

1010677c <irq_table_init>:
1010677c:	4b51      	ldr	r3, [pc, #324]	; (101068c4 <irq_table_init+0x148>)
1010677e:	b5f0      	push	{r4, r5, r6, r7, lr}
10106780:	4951      	ldr	r1, [pc, #324]	; (101068c8 <irq_table_init+0x14c>)
10106782:	4c52      	ldr	r4, [pc, #328]	; (101068cc <irq_table_init+0x150>)
10106784:	4a52      	ldr	r2, [pc, #328]	; (101068d0 <irq_table_init+0x154>)
10106786:	4f53      	ldr	r7, [pc, #332]	; (101068d4 <irq_table_init+0x158>)
10106788:	4e53      	ldr	r6, [pc, #332]	; (101068d8 <irq_table_init+0x15c>)
1010678a:	6018      	str	r0, [r3, #0]
1010678c:	4d53      	ldr	r5, [pc, #332]	; (101068dc <irq_table_init+0x160>)
1010678e:	609c      	str	r4, [r3, #8]
10106790:	4853      	ldr	r0, [pc, #332]	; (101068e0 <irq_table_init+0x164>)
10106792:	4c54      	ldr	r4, [pc, #336]	; (101068e4 <irq_table_init+0x168>)
10106794:	6119      	str	r1, [r3, #16]
10106796:	615a      	str	r2, [r3, #20]
10106798:	4953      	ldr	r1, [pc, #332]	; (101068e8 <irq_table_init+0x16c>)
1010679a:	4a54      	ldr	r2, [pc, #336]	; (101068ec <irq_table_init+0x170>)
1010679c:	619f      	str	r7, [r3, #24]
1010679e:	61de      	str	r6, [r3, #28]
101067a0:	4f53      	ldr	r7, [pc, #332]	; (101068f0 <irq_table_init+0x174>)
101067a2:	4e54      	ldr	r6, [pc, #336]	; (101068f4 <irq_table_init+0x178>)
101067a4:	641d      	str	r5, [r3, #64]	; 0x40
101067a6:	645c      	str	r4, [r3, #68]	; 0x44
101067a8:	4d53      	ldr	r5, [pc, #332]	; (101068f8 <irq_table_init+0x17c>)
101067aa:	4c54      	ldr	r4, [pc, #336]	; (101068fc <irq_table_init+0x180>)
101067ac:	6498      	str	r0, [r3, #72]	; 0x48
101067ae:	64d9      	str	r1, [r3, #76]	; 0x4c
101067b0:	4853      	ldr	r0, [pc, #332]	; (10106900 <irq_table_init+0x184>)
101067b2:	4954      	ldr	r1, [pc, #336]	; (10106904 <irq_table_init+0x188>)
101067b4:	651a      	str	r2, [r3, #80]	; 0x50
101067b6:	4a54      	ldr	r2, [pc, #336]	; (10106908 <irq_table_init+0x18c>)
101067b8:	655f      	str	r7, [r3, #84]	; 0x54
101067ba:	659e      	str	r6, [r3, #88]	; 0x58
101067bc:	4f53      	ldr	r7, [pc, #332]	; (1010690c <irq_table_init+0x190>)
101067be:	4e54      	ldr	r6, [pc, #336]	; (10106910 <irq_table_init+0x194>)
101067c0:	65dd      	str	r5, [r3, #92]	; 0x5c
101067c2:	661c      	str	r4, [r3, #96]	; 0x60
101067c4:	4d53      	ldr	r5, [pc, #332]	; (10106914 <irq_table_init+0x198>)
101067c6:	4c54      	ldr	r4, [pc, #336]	; (10106918 <irq_table_init+0x19c>)
101067c8:	6658      	str	r0, [r3, #100]	; 0x64
101067ca:	6699      	str	r1, [r3, #104]	; 0x68
101067cc:	4853      	ldr	r0, [pc, #332]	; (1010691c <irq_table_init+0x1a0>)
101067ce:	4954      	ldr	r1, [pc, #336]	; (10106920 <irq_table_init+0x1a4>)
101067d0:	66da      	str	r2, [r3, #108]	; 0x6c
101067d2:	4a54      	ldr	r2, [pc, #336]	; (10106924 <irq_table_init+0x1a8>)
101067d4:	671f      	str	r7, [r3, #112]	; 0x70
101067d6:	675e      	str	r6, [r3, #116]	; 0x74
101067d8:	4f53      	ldr	r7, [pc, #332]	; (10106928 <irq_table_init+0x1ac>)
101067da:	4e54      	ldr	r6, [pc, #336]	; (1010692c <irq_table_init+0x1b0>)
101067dc:	679d      	str	r5, [r3, #120]	; 0x78
101067de:	67dc      	str	r4, [r3, #124]	; 0x7c
101067e0:	4d53      	ldr	r5, [pc, #332]	; (10106930 <irq_table_init+0x1b4>)
101067e2:	4c54      	ldr	r4, [pc, #336]	; (10106934 <irq_table_init+0x1b8>)
101067e4:	f8c3 0080 	str.w	r0, [r3, #128]	; 0x80
101067e8:	f8c3 1084 	str.w	r1, [r3, #132]	; 0x84
101067ec:	4852      	ldr	r0, [pc, #328]	; (10106938 <irq_table_init+0x1bc>)
101067ee:	4953      	ldr	r1, [pc, #332]	; (1010693c <irq_table_init+0x1c0>)
101067f0:	f8c3 2088 	str.w	r2, [r3, #136]	; 0x88
101067f4:	f8df e1bc 	ldr.w	lr, [pc, #444]	; 101069b4 <irq_table_init+0x238>
101067f8:	4a51      	ldr	r2, [pc, #324]	; (10106940 <irq_table_init+0x1c4>)
101067fa:	f8c3 708c 	str.w	r7, [r3, #140]	; 0x8c
101067fe:	f8c3 6090 	str.w	r6, [r3, #144]	; 0x90
10106802:	4f50      	ldr	r7, [pc, #320]	; (10106944 <irq_table_init+0x1c8>)
10106804:	4e50      	ldr	r6, [pc, #320]	; (10106948 <irq_table_init+0x1cc>)
10106806:	f8c3 5094 	str.w	r5, [r3, #148]	; 0x94
1010680a:	f8c3 4098 	str.w	r4, [r3, #152]	; 0x98
1010680e:	4d4f      	ldr	r5, [pc, #316]	; (1010694c <irq_table_init+0x1d0>)
10106810:	4c4f      	ldr	r4, [pc, #316]	; (10106950 <irq_table_init+0x1d4>)
10106812:	f8c3 009c 	str.w	r0, [r3, #156]	; 0x9c
10106816:	f8c3 e00c 	str.w	lr, [r3, #12]
1010681a:	484e      	ldr	r0, [pc, #312]	; (10106954 <irq_table_init+0x1d8>)
1010681c:	f8c3 10a0 	str.w	r1, [r3, #160]	; 0xa0
10106820:	494d      	ldr	r1, [pc, #308]	; (10106958 <irq_table_init+0x1dc>)
10106822:	f8c3 20a4 	str.w	r2, [r3, #164]	; 0xa4
10106826:	4a4d      	ldr	r2, [pc, #308]	; (1010695c <irq_table_init+0x1e0>)
10106828:	f8c3 70a8 	str.w	r7, [r3, #168]	; 0xa8
1010682c:	f8c3 60ac 	str.w	r6, [r3, #172]	; 0xac
10106830:	4f4b      	ldr	r7, [pc, #300]	; (10106960 <irq_table_init+0x1e4>)
10106832:	4e4c      	ldr	r6, [pc, #304]	; (10106964 <irq_table_init+0x1e8>)
10106834:	f8c3 50b0 	str.w	r5, [r3, #176]	; 0xb0
10106838:	f8c3 40b4 	str.w	r4, [r3, #180]	; 0xb4
1010683c:	4d4a      	ldr	r5, [pc, #296]	; (10106968 <irq_table_init+0x1ec>)
1010683e:	4c4b      	ldr	r4, [pc, #300]	; (1010696c <irq_table_init+0x1f0>)
10106840:	f8c3 00b8 	str.w	r0, [r3, #184]	; 0xb8
10106844:	f8c3 10bc 	str.w	r1, [r3, #188]	; 0xbc
10106848:	4849      	ldr	r0, [pc, #292]	; (10106970 <irq_table_init+0x1f4>)
1010684a:	494a      	ldr	r1, [pc, #296]	; (10106974 <irq_table_init+0x1f8>)
1010684c:	f8c3 20c0 	str.w	r2, [r3, #192]	; 0xc0
10106850:	4a49      	ldr	r2, [pc, #292]	; (10106978 <irq_table_init+0x1fc>)
10106852:	f8c3 70c4 	str.w	r7, [r3, #196]	; 0xc4
10106856:	f8c3 60c8 	str.w	r6, [r3, #200]	; 0xc8
1010685a:	4f48      	ldr	r7, [pc, #288]	; (1010697c <irq_table_init+0x200>)
1010685c:	4e48      	ldr	r6, [pc, #288]	; (10106980 <irq_table_init+0x204>)
1010685e:	f8c3 50cc 	str.w	r5, [r3, #204]	; 0xcc
10106862:	f8c3 40d0 	str.w	r4, [r3, #208]	; 0xd0
10106866:	4d47      	ldr	r5, [pc, #284]	; (10106984 <irq_table_init+0x208>)
10106868:	4c47      	ldr	r4, [pc, #284]	; (10106988 <irq_table_init+0x20c>)
1010686a:	f8c3 00d4 	str.w	r0, [r3, #212]	; 0xd4
1010686e:	f8c3 10d8 	str.w	r1, [r3, #216]	; 0xd8
10106872:	4846      	ldr	r0, [pc, #280]	; (1010698c <irq_table_init+0x210>)
10106874:	4946      	ldr	r1, [pc, #280]	; (10106990 <irq_table_init+0x214>)
10106876:	f8c3 20dc 	str.w	r2, [r3, #220]	; 0xdc
1010687a:	4a46      	ldr	r2, [pc, #280]	; (10106994 <irq_table_init+0x218>)
1010687c:	f8c3 70e0 	str.w	r7, [r3, #224]	; 0xe0
10106880:	f8c3 60e4 	str.w	r6, [r3, #228]	; 0xe4
10106884:	f8c3 50e8 	str.w	r5, [r3, #232]	; 0xe8
10106888:	f8c3 40ec 	str.w	r4, [r3, #236]	; 0xec
1010688c:	f8c3 00f0 	str.w	r0, [r3, #240]	; 0xf0
10106890:	f8c3 10f4 	str.w	r1, [r3, #244]	; 0xf4
10106894:	f8c3 20f8 	str.w	r2, [r3, #248]	; 0xf8
10106898:	4f3f      	ldr	r7, [pc, #252]	; (10106998 <irq_table_init+0x21c>)
1010689a:	4e40      	ldr	r6, [pc, #256]	; (1010699c <irq_table_init+0x220>)
1010689c:	4d40      	ldr	r5, [pc, #256]	; (101069a0 <irq_table_init+0x224>)
1010689e:	4c41      	ldr	r4, [pc, #260]	; (101069a4 <irq_table_init+0x228>)
101068a0:	4841      	ldr	r0, [pc, #260]	; (101069a8 <irq_table_init+0x22c>)
101068a2:	4942      	ldr	r1, [pc, #264]	; (101069ac <irq_table_init+0x230>)
101068a4:	4a42      	ldr	r2, [pc, #264]	; (101069b0 <irq_table_init+0x234>)
101068a6:	f8c3 7110 	str.w	r7, [r3, #272]	; 0x110
101068aa:	f8c3 6114 	str.w	r6, [r3, #276]	; 0x114
101068ae:	f8c3 5118 	str.w	r5, [r3, #280]	; 0x118
101068b2:	f8c3 411c 	str.w	r4, [r3, #284]	; 0x11c
101068b6:	f8c3 0120 	str.w	r0, [r3, #288]	; 0x120
101068ba:	f8c3 1124 	str.w	r1, [r3, #292]	; 0x124
101068be:	6093      	str	r3, [r2, #8]
101068c0:	bdf0      	pop	{r4, r5, r6, r7, pc}
101068c2:	bf00      	nop
101068c4:	1007c000 	.word	0x1007c000
101068c8:	101061e5 	.word	0x101061e5
101068cc:	10106635 	.word	0x10106635
101068d0:	10106205 	.word	0x10106205
101068d4:	10106225 	.word	0x10106225
101068d8:	10106245 	.word	0x10106245
101068dc:	10106779 	.word	0x10106779
101068e0:	10106771 	.word	0x10106771
101068e4:	10106775 	.word	0x10106775
101068e8:	1010676d 	.word	0x1010676d
101068ec:	10106769 	.word	0x10106769
101068f0:	10106765 	.word	0x10106765
101068f4:	10106761 	.word	0x10106761
101068f8:	1010675d 	.word	0x1010675d
101068fc:	10106759 	.word	0x10106759
10106900:	10106755 	.word	0x10106755
10106904:	10106751 	.word	0x10106751
10106908:	1010674d 	.word	0x1010674d
1010690c:	10106749 	.word	0x10106749
10106910:	10106745 	.word	0x10106745
10106914:	10106741 	.word	0x10106741
10106918:	1010673d 	.word	0x1010673d
1010691c:	10106739 	.word	0x10106739
10106920:	10106735 	.word	0x10106735
10106924:	10106731 	.word	0x10106731
10106928:	1010672d 	.word	0x1010672d
1010692c:	10106729 	.word	0x10106729
10106930:	10106725 	.word	0x10106725
10106934:	10106721 	.word	0x10106721
10106938:	1010671d 	.word	0x1010671d
1010693c:	10106719 	.word	0x10106719
10106940:	10106715 	.word	0x10106715
10106944:	10106711 	.word	0x10106711
10106948:	1010670d 	.word	0x1010670d
1010694c:	10106709 	.word	0x10106709
10106950:	10106705 	.word	0x10106705
10106954:	10106701 	.word	0x10106701
10106958:	101066fd 	.word	0x101066fd
1010695c:	101066f9 	.word	0x101066f9
10106960:	101066f5 	.word	0x101066f5
10106964:	101066f1 	.word	0x101066f1
10106968:	101066ed 	.word	0x101066ed
1010696c:	101066e9 	.word	0x101066e9
10106970:	101066e5 	.word	0x101066e5
10106974:	101066e1 	.word	0x101066e1
10106978:	101066dd 	.word	0x101066dd
1010697c:	101066d9 	.word	0x101066d9
10106980:	101066d5 	.word	0x101066d5
10106984:	101066d1 	.word	0x101066d1
10106988:	101066cd 	.word	0x101066cd
1010698c:	101066c9 	.word	0x101066c9
10106990:	101066c5 	.word	0x101066c5
10106994:	101066c1 	.word	0x101066c1
10106998:	101066bd 	.word	0x101066bd
1010699c:	101066b9 	.word	0x101066b9
101069a0:	101066b5 	.word	0x101066b5
101069a4:	101066b1 	.word	0x101066b1
101069a8:	101066ad 	.word	0x101066ad
101069ac:	101066a9 	.word	0x101066a9
101069b0:	e000ed00 	.word	0xe000ed00
101069b4:	101061c5 	.word	0x101061c5

101069b8 <irq_enable>:
101069b8:	2800      	cmp	r0, #0
101069ba:	db07      	blt.n	101069cc <irq_enable+0x14>
101069bc:	2301      	movs	r3, #1
101069be:	f000 011f 	and.w	r1, r0, #31
101069c2:	4a03      	ldr	r2, [pc, #12]	; (101069d0 <irq_enable+0x18>)
101069c4:	408b      	lsls	r3, r1
101069c6:	0940      	lsrs	r0, r0, #5
101069c8:	f842 3020 	str.w	r3, [r2, r0, lsl #2]
101069cc:	4770      	bx	lr
101069ce:	bf00      	nop
101069d0:	e000e100 	.word	0xe000e100

101069d4 <irq_disable>:
101069d4:	2800      	cmp	r0, #0
101069d6:	db0c      	blt.n	101069f2 <irq_disable+0x1e>
101069d8:	2301      	movs	r3, #1
101069da:	f000 011f 	and.w	r1, r0, #31
101069de:	4a05      	ldr	r2, [pc, #20]	; (101069f4 <irq_disable+0x20>)
101069e0:	0940      	lsrs	r0, r0, #5
101069e2:	408b      	lsls	r3, r1
101069e4:	3020      	adds	r0, #32
101069e6:	f842 3020 	str.w	r3, [r2, r0, lsl #2]
101069ea:	f3bf 8f4f 	dsb	sy
101069ee:	f3bf 8f6f 	isb	sy
101069f2:	4770      	bx	lr
101069f4:	e000e100 	.word	0xe000e100

101069f8 <irq_set_priority>:
101069f8:	2800      	cmp	r0, #0
101069fa:	db08      	blt.n	10106a0e <irq_set_priority+0x16>
101069fc:	0109      	lsls	r1, r1, #4
101069fe:	f100 4060 	add.w	r0, r0, #3758096384	; 0xe0000000
10106a02:	b2c9      	uxtb	r1, r1
10106a04:	f500 4061 	add.w	r0, r0, #57600	; 0xe100
10106a08:	f880 1300 	strb.w	r1, [r0, #768]	; 0x300
10106a0c:	4770      	bx	lr
10106a0e:	4b04      	ldr	r3, [pc, #16]	; (10106a20 <irq_set_priority+0x28>)
10106a10:	f000 000f 	and.w	r0, r0, #15
10106a14:	0109      	lsls	r1, r1, #4
10106a16:	b2c9      	uxtb	r1, r1
10106a18:	4403      	add	r3, r0
10106a1a:	7619      	strb	r1, [r3, #24]
10106a1c:	4770      	bx	lr
10106a1e:	bf00      	nop
10106a20:	e000ecfc 	.word	0xe000ecfc

10106a24 <irq_get_priority>:
10106a24:	2800      	cmp	r0, #0
10106a26:	db07      	blt.n	10106a38 <irq_get_priority+0x14>
10106a28:	f100 4060 	add.w	r0, r0, #3758096384	; 0xe0000000
10106a2c:	f500 4061 	add.w	r0, r0, #57600	; 0xe100
10106a30:	f890 0300 	ldrb.w	r0, [r0, #768]	; 0x300
10106a34:	0900      	lsrs	r0, r0, #4
10106a36:	4770      	bx	lr
10106a38:	4b03      	ldr	r3, [pc, #12]	; (10106a48 <irq_get_priority+0x24>)
10106a3a:	f000 000f 	and.w	r0, r0, #15
10106a3e:	4403      	add	r3, r0
10106a40:	7e18      	ldrb	r0, [r3, #24]
10106a42:	0900      	lsrs	r0, r0, #4
10106a44:	4770      	bx	lr
10106a46:	bf00      	nop
10106a48:	e000ecfc 	.word	0xe000ecfc

10106a4c <irq_set_pending>:
10106a4c:	2800      	cmp	r0, #0
10106a4e:	db08      	blt.n	10106a62 <irq_set_pending+0x16>
10106a50:	2301      	movs	r3, #1
10106a52:	f000 011f 	and.w	r1, r0, #31
10106a56:	4a03      	ldr	r2, [pc, #12]	; (10106a64 <irq_set_pending+0x18>)
10106a58:	0940      	lsrs	r0, r0, #5
10106a5a:	408b      	lsls	r3, r1
10106a5c:	3040      	adds	r0, #64	; 0x40
10106a5e:	f842 3020 	str.w	r3, [r2, r0, lsl #2]
10106a62:	4770      	bx	lr
10106a64:	e000e100 	.word	0xe000e100

10106a68 <irq_get_pending>:
10106a68:	1e03      	subs	r3, r0, #0
10106a6a:	db0a      	blt.n	10106a82 <irq_get_pending+0x1a>
10106a6c:	095a      	lsrs	r2, r3, #5
10106a6e:	4906      	ldr	r1, [pc, #24]	; (10106a88 <irq_get_pending+0x20>)
10106a70:	3240      	adds	r2, #64	; 0x40
10106a72:	f851 0022 	ldr.w	r0, [r1, r2, lsl #2]
10106a76:	f003 031f 	and.w	r3, r3, #31
10106a7a:	40d8      	lsrs	r0, r3
10106a7c:	f000 0001 	and.w	r0, r0, #1
10106a80:	4770      	bx	lr
10106a82:	2000      	movs	r0, #0
10106a84:	4770      	bx	lr
10106a86:	bf00      	nop
10106a88:	e000e100 	.word	0xe000e100

10106a8c <irq_clear_pending>:
10106a8c:	2800      	cmp	r0, #0
10106a8e:	db08      	blt.n	10106aa2 <irq_clear_pending+0x16>
10106a90:	2301      	movs	r3, #1
10106a92:	f000 011f 	and.w	r1, r0, #31
10106a96:	4a03      	ldr	r2, [pc, #12]	; (10106aa4 <irq_clear_pending+0x18>)
10106a98:	0940      	lsrs	r0, r0, #5
10106a9a:	408b      	lsls	r3, r1
10106a9c:	3060      	adds	r0, #96	; 0x60
10106a9e:	f842 3020 	str.w	r3, [r2, r0, lsl #2]
10106aa2:	4770      	bx	lr
10106aa4:	e000e100 	.word	0xe000e100

10106aa8 <irq_register>:
10106aa8:	b430      	push	{r4, r5}
10106aaa:	4d0f      	ldr	r5, [pc, #60]	; (10106ae8 <irq_register+0x40>)
10106aac:	4c0f      	ldr	r4, [pc, #60]	; (10106aec <irq_register+0x44>)
10106aae:	f040 0001 	orr.w	r0, r0, #1
10106ab2:	2900      	cmp	r1, #0
10106ab4:	f845 0021 	str.w	r0, [r5, r1, lsl #2]
10106ab8:	f844 2021 	str.w	r2, [r4, r1, lsl #2]
10106abc:	db0a      	blt.n	10106ad4 <irq_register+0x2c>
10106abe:	011b      	lsls	r3, r3, #4
10106ac0:	f101 4160 	add.w	r1, r1, #3758096384	; 0xe0000000
10106ac4:	b2db      	uxtb	r3, r3
10106ac6:	f501 4161 	add.w	r1, r1, #57600	; 0xe100
10106aca:	f881 3300 	strb.w	r3, [r1, #768]	; 0x300
10106ace:	2001      	movs	r0, #1
10106ad0:	bc30      	pop	{r4, r5}
10106ad2:	4770      	bx	lr
10106ad4:	4a06      	ldr	r2, [pc, #24]	; (10106af0 <irq_register+0x48>)
10106ad6:	f001 010f 	and.w	r1, r1, #15
10106ada:	011b      	lsls	r3, r3, #4
10106adc:	b2db      	uxtb	r3, r3
10106ade:	440a      	add	r2, r1
10106ae0:	7613      	strb	r3, [r2, #24]
10106ae2:	2001      	movs	r0, #1
10106ae4:	bc30      	pop	{r4, r5}
10106ae6:	4770      	bx	lr
10106ae8:	1007c140 	.word	0x1007c140
10106aec:	1007c240 	.word	0x1007c240
10106af0:	e000ecfc 	.word	0xe000ecfc

10106af4 <irq_unregister>:
10106af4:	2300      	movs	r3, #0
10106af6:	4904      	ldr	r1, [pc, #16]	; (10106b08 <irq_unregister+0x14>)
10106af8:	4a04      	ldr	r2, [pc, #16]	; (10106b0c <irq_unregister+0x18>)
10106afa:	f841 3020 	str.w	r3, [r1, r0, lsl #2]
10106afe:	f842 3020 	str.w	r3, [r2, r0, lsl #2]
10106b02:	2001      	movs	r0, #1
10106b04:	4770      	bx	lr
10106b06:	bf00      	nop
10106b08:	1007c140 	.word	0x1007c140
10106b0c:	1007c240 	.word	0x1007c240
10106b10:	10106265 	.word	0x10106265

10106b14 <_char2num>:
10106b14:	f1a0 0330 	sub.w	r3, r0, #48	; 0x30
10106b18:	4602      	mov	r2, r0
10106b1a:	b2d8      	uxtb	r0, r3
10106b1c:	2809      	cmp	r0, #9
10106b1e:	d908      	bls.n	10106b32 <_char2num+0x1e>
10106b20:	f1a2 0361 	sub.w	r3, r2, #97	; 0x61
10106b24:	2b05      	cmp	r3, #5
10106b26:	d905      	bls.n	10106b34 <_char2num+0x20>
10106b28:	f1a2 0341 	sub.w	r3, r2, #65	; 0x41
10106b2c:	2b05      	cmp	r3, #5
10106b2e:	d905      	bls.n	10106b3c <_char2num+0x28>
10106b30:	20ff      	movs	r0, #255	; 0xff
10106b32:	4770      	bx	lr
10106b34:	f1a2 0057 	sub.w	r0, r2, #87	; 0x57
10106b38:	b2c0      	uxtb	r0, r0
10106b3a:	4770      	bx	lr
10106b3c:	f1a2 0037 	sub.w	r0, r2, #55	; 0x37
10106b40:	b2c0      	uxtb	r0, r0
10106b42:	4770      	bx	lr

10106b44 <_2char2dec>:
10106b44:	f1a0 0330 	sub.w	r3, r0, #48	; 0x30
10106b48:	b2db      	uxtb	r3, r3
10106b4a:	2b09      	cmp	r3, #9
10106b4c:	d817      	bhi.n	10106b7e <_2char2dec+0x3a>
10106b4e:	eb03 0083 	add.w	r0, r3, r3, lsl #2
10106b52:	0040      	lsls	r0, r0, #1
10106b54:	b2c0      	uxtb	r0, r0
10106b56:	f1a1 0330 	sub.w	r3, r1, #48	; 0x30
10106b5a:	b2db      	uxtb	r3, r3
10106b5c:	2b09      	cmp	r3, #9
10106b5e:	d90b      	bls.n	10106b78 <_2char2dec+0x34>
10106b60:	f1a1 0361 	sub.w	r3, r1, #97	; 0x61
10106b64:	2b05      	cmp	r3, #5
10106b66:	d91a      	bls.n	10106b9e <_2char2dec+0x5a>
10106b68:	f1a1 0341 	sub.w	r3, r1, #65	; 0x41
10106b6c:	2b05      	cmp	r3, #5
10106b6e:	bf8e      	itee	hi
10106b70:	23ff      	movhi	r3, #255	; 0xff
10106b72:	f1a1 0337 	subls.w	r3, r1, #55	; 0x37
10106b76:	b2db      	uxtbls	r3, r3
10106b78:	4418      	add	r0, r3
10106b7a:	b2c0      	uxtb	r0, r0
10106b7c:	4770      	bx	lr
10106b7e:	f1a0 0361 	sub.w	r3, r0, #97	; 0x61
10106b82:	2b05      	cmp	r3, #5
10106b84:	d805      	bhi.n	10106b92 <_2char2dec+0x4e>
10106b86:	3857      	subs	r0, #87	; 0x57
10106b88:	eb00 0080 	add.w	r0, r0, r0, lsl #2
10106b8c:	0040      	lsls	r0, r0, #1
10106b8e:	b2c0      	uxtb	r0, r0
10106b90:	e7e1      	b.n	10106b56 <_2char2dec+0x12>
10106b92:	f1a0 0341 	sub.w	r3, r0, #65	; 0x41
10106b96:	2b05      	cmp	r3, #5
10106b98:	d907      	bls.n	10106baa <_2char2dec+0x66>
10106b9a:	20f6      	movs	r0, #246	; 0xf6
10106b9c:	e7db      	b.n	10106b56 <_2char2dec+0x12>
10106b9e:	f1a1 0357 	sub.w	r3, r1, #87	; 0x57
10106ba2:	b2db      	uxtb	r3, r3
10106ba4:	4418      	add	r0, r3
10106ba6:	b2c0      	uxtb	r0, r0
10106ba8:	4770      	bx	lr
10106baa:	3837      	subs	r0, #55	; 0x37
10106bac:	eb00 0080 	add.w	r0, r0, r0, lsl #2
10106bb0:	0040      	lsls	r0, r0, #1
10106bb2:	b2c0      	uxtb	r0, r0
10106bb4:	e7cf      	b.n	10106b56 <_2char2dec+0x12>
10106bb6:	bf00      	nop

10106bb8 <_2char2hex>:
10106bb8:	f1a0 0330 	sub.w	r3, r0, #48	; 0x30
10106bbc:	b2db      	uxtb	r3, r3
10106bbe:	2b09      	cmp	r3, #9
10106bc0:	d819      	bhi.n	10106bf6 <_2char2hex+0x3e>
10106bc2:	0118      	lsls	r0, r3, #4
10106bc4:	b243      	sxtb	r3, r0
10106bc6:	f1a1 0030 	sub.w	r0, r1, #48	; 0x30
10106bca:	b2c0      	uxtb	r0, r0
10106bcc:	2809      	cmp	r0, #9
10106bce:	d90f      	bls.n	10106bf0 <_2char2hex+0x38>
10106bd0:	f1a1 0261 	sub.w	r2, r1, #97	; 0x61
10106bd4:	2a05      	cmp	r2, #5
10106bd6:	d909      	bls.n	10106bec <_2char2hex+0x34>
10106bd8:	f1a1 0241 	sub.w	r2, r1, #65	; 0x41
10106bdc:	2a05      	cmp	r2, #5
10106bde:	bf9d      	ittte	ls
10106be0:	f1a1 0037 	subls.w	r0, r1, #55	; 0x37
10106be4:	4318      	orrls	r0, r3
10106be6:	b2c0      	uxtbls	r0, r0
10106be8:	20ff      	movhi	r0, #255	; 0xff
10106bea:	4770      	bx	lr
10106bec:	f1a1 0057 	sub.w	r0, r1, #87	; 0x57
10106bf0:	4318      	orrs	r0, r3
10106bf2:	b2c0      	uxtb	r0, r0
10106bf4:	4770      	bx	lr
10106bf6:	f1a0 0361 	sub.w	r3, r0, #97	; 0x61
10106bfa:	2b05      	cmp	r3, #5
10106bfc:	d804      	bhi.n	10106c08 <_2char2hex+0x50>
10106bfe:	3857      	subs	r0, #87	; 0x57
10106c00:	f340 0003 	sbfx	r0, r0, #0, #4
10106c04:	0103      	lsls	r3, r0, #4
10106c06:	e7de      	b.n	10106bc6 <_2char2hex+0xe>
10106c08:	f1a0 0341 	sub.w	r3, r0, #65	; 0x41
10106c0c:	2b05      	cmp	r3, #5
10106c0e:	bf9d      	ittte	ls
10106c10:	3837      	subls	r0, #55	; 0x37
10106c12:	f340 0003 	sbfxls	r0, r0, #0, #4
10106c16:	0103      	lslls	r3, r0, #4
10106c18:	f06f 030f 	mvnhi.w	r3, #15
10106c1c:	e7d3      	b.n	10106bc6 <_2char2hex+0xe>
10106c1e:	bf00      	nop

10106c20 <_memchr>:
10106c20:	0783      	lsls	r3, r0, #30
10106c22:	b470      	push	{r4, r5, r6}
10106c24:	b2cd      	uxtb	r5, r1
10106c26:	d03e      	beq.n	10106ca6 <_memchr+0x86>
10106c28:	1e54      	subs	r4, r2, #1
10106c2a:	b30a      	cbz	r2, 10106c70 <_memchr+0x50>
10106c2c:	7803      	ldrb	r3, [r0, #0]
10106c2e:	42ab      	cmp	r3, r5
10106c30:	d01f      	beq.n	10106c72 <_memchr+0x52>
10106c32:	1c43      	adds	r3, r0, #1
10106c34:	e005      	b.n	10106c42 <_memchr+0x22>
10106c36:	f114 34ff 	adds.w	r4, r4, #4294967295
10106c3a:	d319      	bcc.n	10106c70 <_memchr+0x50>
10106c3c:	7802      	ldrb	r2, [r0, #0]
10106c3e:	42aa      	cmp	r2, r5
10106c40:	d017      	beq.n	10106c72 <_memchr+0x52>
10106c42:	f013 0f03 	tst.w	r3, #3
10106c46:	4618      	mov	r0, r3
10106c48:	f103 0301 	add.w	r3, r3, #1
10106c4c:	d1f3      	bne.n	10106c36 <_memchr+0x16>
10106c4e:	2c03      	cmp	r4, #3
10106c50:	d811      	bhi.n	10106c76 <_memchr+0x56>
10106c52:	b354      	cbz	r4, 10106caa <_memchr+0x8a>
10106c54:	7803      	ldrb	r3, [r0, #0]
10106c56:	42ab      	cmp	r3, r5
10106c58:	d00b      	beq.n	10106c72 <_memchr+0x52>
10106c5a:	4404      	add	r4, r0
10106c5c:	1c43      	adds	r3, r0, #1
10106c5e:	e002      	b.n	10106c66 <_memchr+0x46>
10106c60:	7802      	ldrb	r2, [r0, #0]
10106c62:	42aa      	cmp	r2, r5
10106c64:	d005      	beq.n	10106c72 <_memchr+0x52>
10106c66:	429c      	cmp	r4, r3
10106c68:	4618      	mov	r0, r3
10106c6a:	f103 0301 	add.w	r3, r3, #1
10106c6e:	d1f7      	bne.n	10106c60 <_memchr+0x40>
10106c70:	2000      	movs	r0, #0
10106c72:	bc70      	pop	{r4, r5, r6}
10106c74:	4770      	bx	lr
10106c76:	4602      	mov	r2, r0
10106c78:	020e      	lsls	r6, r1, #8
10106c7a:	f406 467f 	and.w	r6, r6, #65280	; 0xff00
10106c7e:	432e      	orrs	r6, r5
10106c80:	ea46 4606 	orr.w	r6, r6, r6, lsl #16
10106c84:	6813      	ldr	r3, [r2, #0]
10106c86:	4073      	eors	r3, r6
10106c88:	f1a3 3101 	sub.w	r1, r3, #16843009	; 0x1010101
10106c8c:	ea21 0303 	bic.w	r3, r1, r3
10106c90:	f013 3f80 	tst.w	r3, #2155905152	; 0x80808080
10106c94:	4610      	mov	r0, r2
10106c96:	f102 0204 	add.w	r2, r2, #4
10106c9a:	d1db      	bne.n	10106c54 <_memchr+0x34>
10106c9c:	3c04      	subs	r4, #4
10106c9e:	2c03      	cmp	r4, #3
10106ca0:	4610      	mov	r0, r2
10106ca2:	d8ef      	bhi.n	10106c84 <_memchr+0x64>
10106ca4:	e7d5      	b.n	10106c52 <_memchr+0x32>
10106ca6:	4614      	mov	r4, r2
10106ca8:	e7d1      	b.n	10106c4e <_memchr+0x2e>
10106caa:	4620      	mov	r0, r4
10106cac:	e7e1      	b.n	10106c72 <_memchr+0x52>
10106cae:	bf00      	nop

10106cb0 <_memcmp>:
10106cb0:	2a03      	cmp	r2, #3
10106cb2:	b470      	push	{r4, r5, r6}
10106cb4:	d926      	bls.n	10106d04 <_memcmp+0x54>
10106cb6:	ea40 0301 	orr.w	r3, r0, r1
10106cba:	079b      	lsls	r3, r3, #30
10106cbc:	d011      	beq.n	10106ce2 <_memcmp+0x32>
10106cbe:	7803      	ldrb	r3, [r0, #0]
10106cc0:	780c      	ldrb	r4, [r1, #0]
10106cc2:	42a3      	cmp	r3, r4
10106cc4:	d122      	bne.n	10106d0c <_memcmp+0x5c>
10106cc6:	440a      	add	r2, r1
10106cc8:	3101      	adds	r1, #1
10106cca:	e005      	b.n	10106cd8 <_memcmp+0x28>
10106ccc:	f810 3f01 	ldrb.w	r3, [r0, #1]!
10106cd0:	f811 4b01 	ldrb.w	r4, [r1], #1
10106cd4:	42a3      	cmp	r3, r4
10106cd6:	d119      	bne.n	10106d0c <_memcmp+0x5c>
10106cd8:	4291      	cmp	r1, r2
10106cda:	d1f7      	bne.n	10106ccc <_memcmp+0x1c>
10106cdc:	2000      	movs	r0, #0
10106cde:	bc70      	pop	{r4, r5, r6}
10106ce0:	4770      	bx	lr
10106ce2:	460c      	mov	r4, r1
10106ce4:	4603      	mov	r3, r0
10106ce6:	681e      	ldr	r6, [r3, #0]
10106ce8:	6825      	ldr	r5, [r4, #0]
10106cea:	42ae      	cmp	r6, r5
10106cec:	4618      	mov	r0, r3
10106cee:	4621      	mov	r1, r4
10106cf0:	f103 0304 	add.w	r3, r3, #4
10106cf4:	f104 0404 	add.w	r4, r4, #4
10106cf8:	d1e1      	bne.n	10106cbe <_memcmp+0xe>
10106cfa:	3a04      	subs	r2, #4
10106cfc:	2a03      	cmp	r2, #3
10106cfe:	4618      	mov	r0, r3
10106d00:	4621      	mov	r1, r4
10106d02:	d8f0      	bhi.n	10106ce6 <_memcmp+0x36>
10106d04:	2a00      	cmp	r2, #0
10106d06:	d1da      	bne.n	10106cbe <_memcmp+0xe>
10106d08:	4610      	mov	r0, r2
10106d0a:	e7e8      	b.n	10106cde <_memcmp+0x2e>
10106d0c:	1b18      	subs	r0, r3, r4
10106d0e:	bc70      	pop	{r4, r5, r6}
10106d10:	4770      	bx	lr
10106d12:	bf00      	nop

10106d14 <_memcpy>:
10106d14:	2a0f      	cmp	r2, #15
10106d16:	b5f0      	push	{r4, r5, r6, r7, lr}
10106d18:	d94a      	bls.n	10106db0 <_memcpy+0x9c>
10106d1a:	ea41 0300 	orr.w	r3, r1, r0
10106d1e:	079b      	lsls	r3, r3, #30
10106d20:	d148      	bne.n	10106db4 <_memcpy+0xa0>
10106d22:	4694      	mov	ip, r2
10106d24:	f100 0e10 	add.w	lr, r0, #16
10106d28:	f101 0310 	add.w	r3, r1, #16
10106d2c:	f853 7c10 	ldr.w	r7, [r3, #-16]
10106d30:	f853 6c0c 	ldr.w	r6, [r3, #-12]
10106d34:	f853 5c08 	ldr.w	r5, [r3, #-8]
10106d38:	f853 4c04 	ldr.w	r4, [r3, #-4]
10106d3c:	f1ac 0c10 	sub.w	ip, ip, #16
10106d40:	f1bc 0f0f 	cmp.w	ip, #15
10106d44:	f84e 7c10 	str.w	r7, [lr, #-16]
10106d48:	f84e 6c0c 	str.w	r6, [lr, #-12]
10106d4c:	f84e 5c08 	str.w	r5, [lr, #-8]
10106d50:	f84e 4c04 	str.w	r4, [lr, #-4]
10106d54:	f103 0310 	add.w	r3, r3, #16
10106d58:	f10e 0e10 	add.w	lr, lr, #16
10106d5c:	d8e6      	bhi.n	10106d2c <_memcpy+0x18>
10106d5e:	f1a2 0310 	sub.w	r3, r2, #16
10106d62:	f023 030f 	bic.w	r3, r3, #15
10106d66:	f002 0e0f 	and.w	lr, r2, #15
10106d6a:	3310      	adds	r3, #16
10106d6c:	f1be 0f03 	cmp.w	lr, #3
10106d70:	4419      	add	r1, r3
10106d72:	4403      	add	r3, r0
10106d74:	d921      	bls.n	10106dba <_memcpy+0xa6>
10106d76:	460e      	mov	r6, r1
10106d78:	4674      	mov	r4, lr
10106d7a:	1f1d      	subs	r5, r3, #4
10106d7c:	f856 7b04 	ldr.w	r7, [r6], #4
10106d80:	3c04      	subs	r4, #4
10106d82:	2c03      	cmp	r4, #3
10106d84:	f845 7f04 	str.w	r7, [r5, #4]!
10106d88:	d8f8      	bhi.n	10106d7c <_memcpy+0x68>
10106d8a:	f1ae 0404 	sub.w	r4, lr, #4
10106d8e:	f024 0403 	bic.w	r4, r4, #3
10106d92:	3404      	adds	r4, #4
10106d94:	4423      	add	r3, r4
10106d96:	4421      	add	r1, r4
10106d98:	f002 0203 	and.w	r2, r2, #3
10106d9c:	b162      	cbz	r2, 10106db8 <_memcpy+0xa4>
10106d9e:	3b01      	subs	r3, #1
10106da0:	440a      	add	r2, r1
10106da2:	f811 4b01 	ldrb.w	r4, [r1], #1
10106da6:	4291      	cmp	r1, r2
10106da8:	f803 4f01 	strb.w	r4, [r3, #1]!
10106dac:	d1f9      	bne.n	10106da2 <_memcpy+0x8e>
10106dae:	bdf0      	pop	{r4, r5, r6, r7, pc}
10106db0:	4603      	mov	r3, r0
10106db2:	e7f3      	b.n	10106d9c <_memcpy+0x88>
10106db4:	4603      	mov	r3, r0
10106db6:	e7f2      	b.n	10106d9e <_memcpy+0x8a>
10106db8:	bdf0      	pop	{r4, r5, r6, r7, pc}
10106dba:	4672      	mov	r2, lr
10106dbc:	e7ee      	b.n	10106d9c <_memcpy+0x88>
10106dbe:	bf00      	nop

10106dc0 <_memmove>:
10106dc0:	4288      	cmp	r0, r1
10106dc2:	b5f0      	push	{r4, r5, r6, r7, lr}
10106dc4:	d90d      	bls.n	10106de2 <_memmove+0x22>
10106dc6:	188b      	adds	r3, r1, r2
10106dc8:	4298      	cmp	r0, r3
10106dca:	d20a      	bcs.n	10106de2 <_memmove+0x22>
10106dcc:	1881      	adds	r1, r0, r2
10106dce:	2a00      	cmp	r2, #0
10106dd0:	d051      	beq.n	10106e76 <_memmove+0xb6>
10106dd2:	1a9a      	subs	r2, r3, r2
10106dd4:	f813 4d01 	ldrb.w	r4, [r3, #-1]!
10106dd8:	4293      	cmp	r3, r2
10106dda:	f801 4d01 	strb.w	r4, [r1, #-1]!
10106dde:	d1f9      	bne.n	10106dd4 <_memmove+0x14>
10106de0:	bdf0      	pop	{r4, r5, r6, r7, pc}
10106de2:	2a0f      	cmp	r2, #15
10106de4:	d948      	bls.n	10106e78 <_memmove+0xb8>
10106de6:	ea41 0300 	orr.w	r3, r1, r0
10106dea:	079b      	lsls	r3, r3, #30
10106dec:	d146      	bne.n	10106e7c <_memmove+0xbc>
10106dee:	4615      	mov	r5, r2
10106df0:	f100 0410 	add.w	r4, r0, #16
10106df4:	f101 0310 	add.w	r3, r1, #16
10106df8:	f853 6c10 	ldr.w	r6, [r3, #-16]
10106dfc:	f844 6c10 	str.w	r6, [r4, #-16]
10106e00:	f853 6c0c 	ldr.w	r6, [r3, #-12]
10106e04:	f844 6c0c 	str.w	r6, [r4, #-12]
10106e08:	f853 6c08 	ldr.w	r6, [r3, #-8]
10106e0c:	f844 6c08 	str.w	r6, [r4, #-8]
10106e10:	3d10      	subs	r5, #16
10106e12:	f853 6c04 	ldr.w	r6, [r3, #-4]
10106e16:	2d0f      	cmp	r5, #15
10106e18:	f844 6c04 	str.w	r6, [r4, #-4]
10106e1c:	f103 0310 	add.w	r3, r3, #16
10106e20:	f104 0410 	add.w	r4, r4, #16
10106e24:	d8e8      	bhi.n	10106df8 <_memmove+0x38>
10106e26:	f1a2 0310 	sub.w	r3, r2, #16
10106e2a:	f023 030f 	bic.w	r3, r3, #15
10106e2e:	f002 0e0f 	and.w	lr, r2, #15
10106e32:	3310      	adds	r3, #16
10106e34:	f1be 0f03 	cmp.w	lr, #3
10106e38:	4419      	add	r1, r3
10106e3a:	4403      	add	r3, r0
10106e3c:	d921      	bls.n	10106e82 <_memmove+0xc2>
10106e3e:	460e      	mov	r6, r1
10106e40:	4674      	mov	r4, lr
10106e42:	1f1d      	subs	r5, r3, #4
10106e44:	f856 7b04 	ldr.w	r7, [r6], #4
10106e48:	3c04      	subs	r4, #4
10106e4a:	2c03      	cmp	r4, #3
10106e4c:	f845 7f04 	str.w	r7, [r5, #4]!
10106e50:	d8f8      	bhi.n	10106e44 <_memmove+0x84>
10106e52:	f1ae 0404 	sub.w	r4, lr, #4
10106e56:	f024 0403 	bic.w	r4, r4, #3
10106e5a:	3404      	adds	r4, #4
10106e5c:	4423      	add	r3, r4
10106e5e:	4421      	add	r1, r4
10106e60:	f002 0203 	and.w	r2, r2, #3
10106e64:	b162      	cbz	r2, 10106e80 <_memmove+0xc0>
10106e66:	3b01      	subs	r3, #1
10106e68:	440a      	add	r2, r1
10106e6a:	f811 4b01 	ldrb.w	r4, [r1], #1
10106e6e:	428a      	cmp	r2, r1
10106e70:	f803 4f01 	strb.w	r4, [r3, #1]!
10106e74:	d1f9      	bne.n	10106e6a <_memmove+0xaa>
10106e76:	bdf0      	pop	{r4, r5, r6, r7, pc}
10106e78:	4603      	mov	r3, r0
10106e7a:	e7f3      	b.n	10106e64 <_memmove+0xa4>
10106e7c:	4603      	mov	r3, r0
10106e7e:	e7f2      	b.n	10106e66 <_memmove+0xa6>
10106e80:	bdf0      	pop	{r4, r5, r6, r7, pc}
10106e82:	4672      	mov	r2, lr
10106e84:	e7ee      	b.n	10106e64 <_memmove+0xa4>
10106e86:	bf00      	nop

10106e88 <_memset>:
10106e88:	b470      	push	{r4, r5, r6}
10106e8a:	0786      	lsls	r6, r0, #30
10106e8c:	d046      	beq.n	10106f1c <_memset+0x94>
10106e8e:	1e54      	subs	r4, r2, #1
10106e90:	2a00      	cmp	r2, #0
10106e92:	d041      	beq.n	10106f18 <_memset+0x90>
10106e94:	b2ca      	uxtb	r2, r1
10106e96:	4603      	mov	r3, r0
10106e98:	e002      	b.n	10106ea0 <_memset+0x18>
10106e9a:	f114 34ff 	adds.w	r4, r4, #4294967295
10106e9e:	d33b      	bcc.n	10106f18 <_memset+0x90>
10106ea0:	f803 2b01 	strb.w	r2, [r3], #1
10106ea4:	079d      	lsls	r5, r3, #30
10106ea6:	d1f8      	bne.n	10106e9a <_memset+0x12>
10106ea8:	2c03      	cmp	r4, #3
10106eaa:	d92e      	bls.n	10106f0a <_memset+0x82>
10106eac:	b2cd      	uxtb	r5, r1
10106eae:	ea45 2505 	orr.w	r5, r5, r5, lsl #8
10106eb2:	2c0f      	cmp	r4, #15
10106eb4:	ea45 4505 	orr.w	r5, r5, r5, lsl #16
10106eb8:	d919      	bls.n	10106eee <_memset+0x66>
10106eba:	4626      	mov	r6, r4
10106ebc:	f103 0210 	add.w	r2, r3, #16
10106ec0:	3e10      	subs	r6, #16
10106ec2:	2e0f      	cmp	r6, #15
10106ec4:	f842 5c10 	str.w	r5, [r2, #-16]
10106ec8:	f842 5c0c 	str.w	r5, [r2, #-12]
10106ecc:	f842 5c08 	str.w	r5, [r2, #-8]
10106ed0:	f842 5c04 	str.w	r5, [r2, #-4]
10106ed4:	f102 0210 	add.w	r2, r2, #16
10106ed8:	d8f2      	bhi.n	10106ec0 <_memset+0x38>
10106eda:	f1a4 0210 	sub.w	r2, r4, #16
10106ede:	f022 020f 	bic.w	r2, r2, #15
10106ee2:	f004 040f 	and.w	r4, r4, #15
10106ee6:	3210      	adds	r2, #16
10106ee8:	2c03      	cmp	r4, #3
10106eea:	4413      	add	r3, r2
10106eec:	d90d      	bls.n	10106f0a <_memset+0x82>
10106eee:	461e      	mov	r6, r3
10106ef0:	4622      	mov	r2, r4
10106ef2:	3a04      	subs	r2, #4
10106ef4:	2a03      	cmp	r2, #3
10106ef6:	f846 5b04 	str.w	r5, [r6], #4
10106efa:	d8fa      	bhi.n	10106ef2 <_memset+0x6a>
10106efc:	1f22      	subs	r2, r4, #4
10106efe:	f022 0203 	bic.w	r2, r2, #3
10106f02:	3204      	adds	r2, #4
10106f04:	4413      	add	r3, r2
10106f06:	f004 0403 	and.w	r4, r4, #3
10106f0a:	b12c      	cbz	r4, 10106f18 <_memset+0x90>
10106f0c:	b2c9      	uxtb	r1, r1
10106f0e:	441c      	add	r4, r3
10106f10:	f803 1b01 	strb.w	r1, [r3], #1
10106f14:	42a3      	cmp	r3, r4
10106f16:	d1fb      	bne.n	10106f10 <_memset+0x88>
10106f18:	bc70      	pop	{r4, r5, r6}
10106f1a:	4770      	bx	lr
10106f1c:	4614      	mov	r4, r2
10106f1e:	4603      	mov	r3, r0
10106f20:	e7c2      	b.n	10106ea8 <_memset+0x20>
10106f22:	bf00      	nop

10106f24 <judge_digit_width>:
10106f24:	2910      	cmp	r1, #16
10106f26:	b410      	push	{r4}
10106f28:	d02b      	beq.n	10106f82 <judge_digit_width+0x5e>
10106f2a:	b191      	cbz	r1, 10106f52 <judge_digit_width+0x2e>
10106f2c:	2908      	cmp	r1, #8
10106f2e:	d03e      	beq.n	10106fae <judge_digit_width+0x8a>
10106f30:	7803      	ldrb	r3, [r0, #0]
10106f32:	3b30      	subs	r3, #48	; 0x30
10106f34:	2b09      	cmp	r3, #9
10106f36:	f04f 0100 	mov.w	r1, #0
10106f3a:	d806      	bhi.n	10106f4a <judge_digit_width+0x26>
10106f3c:	f810 3f01 	ldrb.w	r3, [r0, #1]!
10106f40:	3b30      	subs	r3, #48	; 0x30
10106f42:	2b09      	cmp	r3, #9
10106f44:	f101 0101 	add.w	r1, r1, #1
10106f48:	d9f8      	bls.n	10106f3c <judge_digit_width+0x18>
10106f4a:	4608      	mov	r0, r1
10106f4c:	f85d 4b04 	ldr.w	r4, [sp], #4
10106f50:	4770      	bx	lr
10106f52:	7803      	ldrb	r3, [r0, #0]
10106f54:	2b30      	cmp	r3, #48	; 0x30
10106f56:	d1ec      	bne.n	10106f32 <judge_digit_width+0xe>
10106f58:	7843      	ldrb	r3, [r0, #1]
10106f5a:	f043 0320 	orr.w	r3, r3, #32
10106f5e:	2b78      	cmp	r3, #120	; 0x78
10106f60:	d12b      	bne.n	10106fba <judge_digit_width+0x96>
10106f62:	3001      	adds	r0, #1
10106f64:	2102      	movs	r1, #2
10106f66:	e000      	b.n	10106f6a <judge_digit_width+0x46>
10106f68:	3101      	adds	r1, #1
10106f6a:	f810 3f01 	ldrb.w	r3, [r0, #1]!
10106f6e:	f023 0220 	bic.w	r2, r3, #32
10106f72:	3b30      	subs	r3, #48	; 0x30
10106f74:	2b09      	cmp	r3, #9
10106f76:	f1a2 0241 	sub.w	r2, r2, #65	; 0x41
10106f7a:	d9f5      	bls.n	10106f68 <judge_digit_width+0x44>
10106f7c:	2a05      	cmp	r2, #5
10106f7e:	d9f3      	bls.n	10106f68 <judge_digit_width+0x44>
10106f80:	e7e3      	b.n	10106f4a <judge_digit_width+0x26>
10106f82:	7803      	ldrb	r3, [r0, #0]
10106f84:	2b30      	cmp	r3, #48	; 0x30
10106f86:	d027      	beq.n	10106fd8 <judge_digit_width+0xb4>
10106f88:	4604      	mov	r4, r0
10106f8a:	e001      	b.n	10106f90 <judge_digit_width+0x6c>
10106f8c:	f814 3f01 	ldrb.w	r3, [r4, #1]!
10106f90:	f023 0220 	bic.w	r2, r3, #32
10106f94:	3b30      	subs	r3, #48	; 0x30
10106f96:	2b09      	cmp	r3, #9
10106f98:	f1a2 0241 	sub.w	r2, r2, #65	; 0x41
10106f9c:	eba4 0100 	sub.w	r1, r4, r0
10106fa0:	d9f4      	bls.n	10106f8c <judge_digit_width+0x68>
10106fa2:	2a05      	cmp	r2, #5
10106fa4:	d9f2      	bls.n	10106f8c <judge_digit_width+0x68>
10106fa6:	4608      	mov	r0, r1
10106fa8:	f85d 4b04 	ldr.w	r4, [sp], #4
10106fac:	4770      	bx	lr
10106fae:	7803      	ldrb	r3, [r0, #0]
10106fb0:	3b30      	subs	r3, #48	; 0x30
10106fb2:	2b07      	cmp	r3, #7
10106fb4:	f04f 0100 	mov.w	r1, #0
10106fb8:	d8c7      	bhi.n	10106f4a <judge_digit_width+0x26>
10106fba:	f810 3f01 	ldrb.w	r3, [r0, #1]!
10106fbe:	3b30      	subs	r3, #48	; 0x30
10106fc0:	2b07      	cmp	r3, #7
10106fc2:	f101 0101 	add.w	r1, r1, #1
10106fc6:	d8c0      	bhi.n	10106f4a <judge_digit_width+0x26>
10106fc8:	f810 3f01 	ldrb.w	r3, [r0, #1]!
10106fcc:	3b30      	subs	r3, #48	; 0x30
10106fce:	2b07      	cmp	r3, #7
10106fd0:	f101 0101 	add.w	r1, r1, #1
10106fd4:	d9f1      	bls.n	10106fba <judge_digit_width+0x96>
10106fd6:	e7b8      	b.n	10106f4a <judge_digit_width+0x26>
10106fd8:	7842      	ldrb	r2, [r0, #1]
10106fda:	f042 0220 	orr.w	r2, r2, #32
10106fde:	2a78      	cmp	r2, #120	; 0x78
10106fe0:	d0bf      	beq.n	10106f62 <judge_digit_width+0x3e>
10106fe2:	e7d1      	b.n	10106f88 <judge_digit_width+0x64>

10106fe4 <_vsscanf>:
10106fe4:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10106fe8:	460f      	mov	r7, r1
10106fea:	2100      	movs	r1, #0
10106fec:	b08d      	sub	sp, #52	; 0x34
10106fee:	9002      	str	r0, [sp, #8]
10106ff0:	4692      	mov	sl, r2
10106ff2:	f10d 092f 	add.w	r9, sp, #47	; 0x2f
10106ff6:	f10d 0217 	add.w	r2, sp, #23
10106ffa:	f802 1f01 	strb.w	r1, [r2, #1]!
10106ffe:	454a      	cmp	r2, r9
10107000:	d1fb      	bne.n	10106ffa <_vsscanf+0x16>
10107002:	f04f 0b00 	mov.w	fp, #0
10107006:	783a      	ldrb	r2, [r7, #0]
10107008:	9c02      	ldr	r4, [sp, #8]
1010700a:	b37a      	cbz	r2, 1010706c <_vsscanf+0x88>
1010700c:	2a20      	cmp	r2, #32
1010700e:	d00f      	beq.n	10107030 <_vsscanf+0x4c>
10107010:	f1a2 0109 	sub.w	r1, r2, #9
10107014:	2904      	cmp	r1, #4
10107016:	d90b      	bls.n	10107030 <_vsscanf+0x4c>
10107018:	2a2c      	cmp	r2, #44	; 0x2c
1010701a:	d009      	beq.n	10107030 <_vsscanf+0x4c>
1010701c:	2a25      	cmp	r2, #37	; 0x25
1010701e:	463d      	mov	r5, r7
10107020:	d028      	beq.n	10107074 <_vsscanf+0x90>
10107022:	7821      	ldrb	r1, [r4, #0]
10107024:	4291      	cmp	r1, r2
10107026:	d121      	bne.n	1010706c <_vsscanf+0x88>
10107028:	3401      	adds	r4, #1
1010702a:	1c6f      	adds	r7, r5, #1
1010702c:	786a      	ldrb	r2, [r5, #1]
1010702e:	e7ec      	b.n	1010700a <_vsscanf+0x26>
10107030:	3701      	adds	r7, #1
10107032:	783a      	ldrb	r2, [r7, #0]
10107034:	2a20      	cmp	r2, #32
10107036:	463d      	mov	r5, r7
10107038:	f1a2 0309 	sub.w	r3, r2, #9
1010703c:	f107 0701 	add.w	r7, r7, #1
10107040:	d0f7      	beq.n	10107032 <_vsscanf+0x4e>
10107042:	2b04      	cmp	r3, #4
10107044:	d9f5      	bls.n	10107032 <_vsscanf+0x4e>
10107046:	2a2c      	cmp	r2, #44	; 0x2c
10107048:	d0f3      	beq.n	10107032 <_vsscanf+0x4e>
1010704a:	4620      	mov	r0, r4
1010704c:	7801      	ldrb	r1, [r0, #0]
1010704e:	2920      	cmp	r1, #32
10107050:	4604      	mov	r4, r0
10107052:	f1a1 0309 	sub.w	r3, r1, #9
10107056:	f100 0001 	add.w	r0, r0, #1
1010705a:	d0f7      	beq.n	1010704c <_vsscanf+0x68>
1010705c:	2b04      	cmp	r3, #4
1010705e:	d9f5      	bls.n	1010704c <_vsscanf+0x68>
10107060:	292c      	cmp	r1, #44	; 0x2c
10107062:	d0f3      	beq.n	1010704c <_vsscanf+0x68>
10107064:	2a25      	cmp	r2, #37	; 0x25
10107066:	d005      	beq.n	10107074 <_vsscanf+0x90>
10107068:	2a00      	cmp	r2, #0
1010706a:	d1db      	bne.n	10107024 <_vsscanf+0x40>
1010706c:	4658      	mov	r0, fp
1010706e:	b00d      	add	sp, #52	; 0x34
10107070:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10107074:	786a      	ldrb	r2, [r5, #1]
10107076:	2a2a      	cmp	r2, #42	; 0x2a
10107078:	f105 0501 	add.w	r5, r5, #1
1010707c:	f000 80f5 	beq.w	1010726a <_vsscanf+0x286>
10107080:	f1a2 0130 	sub.w	r1, r2, #48	; 0x30
10107084:	2909      	cmp	r1, #9
10107086:	f200 80d9 	bhi.w	1010723c <_vsscanf+0x258>
1010708a:	f04f 0800 	mov.w	r8, #0
1010708e:	eb08 0888 	add.w	r8, r8, r8, lsl #2
10107092:	eb02 0848 	add.w	r8, r2, r8, lsl #1
10107096:	f815 2f01 	ldrb.w	r2, [r5, #1]!
1010709a:	f1a2 0330 	sub.w	r3, r2, #48	; 0x30
1010709e:	2b09      	cmp	r3, #9
101070a0:	f1a8 0830 	sub.w	r8, r8, #48	; 0x30
101070a4:	d9f3      	bls.n	1010708e <_vsscanf+0xaa>
101070a6:	fa0f f888 	sxth.w	r8, r8
101070aa:	f1b8 0f00 	cmp.w	r8, #0
101070ae:	dddd      	ble.n	1010706c <_vsscanf+0x88>
101070b0:	2a68      	cmp	r2, #104	; 0x68
101070b2:	9201      	str	r2, [sp, #4]
101070b4:	f000 80c8 	beq.w	10107248 <_vsscanf+0x264>
101070b8:	f042 0120 	orr.w	r1, r2, #32
101070bc:	296c      	cmp	r1, #108	; 0x6c
101070be:	f000 80cb 	beq.w	10107258 <_vsscanf+0x274>
101070c2:	297a      	cmp	r1, #122	; 0x7a
101070c4:	f000 80c8 	beq.w	10107258 <_vsscanf+0x274>
101070c8:	23ff      	movs	r3, #255	; 0xff
101070ca:	9301      	str	r3, [sp, #4]
101070cc:	2a00      	cmp	r2, #0
101070ce:	d0cd      	beq.n	1010706c <_vsscanf+0x88>
101070d0:	2a6e      	cmp	r2, #110	; 0x6e
101070d2:	f000 80f0 	beq.w	101072b6 <_vsscanf+0x2d2>
101070d6:	7826      	ldrb	r6, [r4, #0]
101070d8:	2e00      	cmp	r6, #0
101070da:	d0c7      	beq.n	1010706c <_vsscanf+0x88>
101070dc:	3a25      	subs	r2, #37	; 0x25
101070de:	1c6f      	adds	r7, r5, #1
101070e0:	2a53      	cmp	r2, #83	; 0x53
101070e2:	d8c3      	bhi.n	1010706c <_vsscanf+0x88>
101070e4:	a301      	add	r3, pc, #4	; (adr r3, 101070ec <_vsscanf+0x108>)
101070e6:	f853 f022 	ldr.w	pc, [r3, r2, lsl #2]
101070ea:	bf00      	nop
101070ec:	101074a1 	.word	0x101074a1
101070f0:	1010706d 	.word	0x1010706d
101070f4:	1010706d 	.word	0x1010706d
101070f8:	1010706d 	.word	0x1010706d
101070fc:	1010706d 	.word	0x1010706d
10107100:	1010706d 	.word	0x1010706d
10107104:	1010706d 	.word	0x1010706d
10107108:	1010706d 	.word	0x1010706d
1010710c:	1010706d 	.word	0x1010706d
10107110:	1010706d 	.word	0x1010706d
10107114:	1010706d 	.word	0x1010706d
10107118:	1010706d 	.word	0x1010706d
1010711c:	1010706d 	.word	0x1010706d
10107120:	1010706d 	.word	0x1010706d
10107124:	1010706d 	.word	0x1010706d
10107128:	1010706d 	.word	0x1010706d
1010712c:	1010706d 	.word	0x1010706d
10107130:	1010706d 	.word	0x1010706d
10107134:	1010706d 	.word	0x1010706d
10107138:	1010706d 	.word	0x1010706d
1010713c:	1010706d 	.word	0x1010706d
10107140:	1010706d 	.word	0x1010706d
10107144:	1010706d 	.word	0x1010706d
10107148:	1010706d 	.word	0x1010706d
1010714c:	1010706d 	.word	0x1010706d
10107150:	1010706d 	.word	0x1010706d
10107154:	1010706d 	.word	0x1010706d
10107158:	1010706d 	.word	0x1010706d
1010715c:	1010706d 	.word	0x1010706d
10107160:	1010706d 	.word	0x1010706d
10107164:	1010706d 	.word	0x1010706d
10107168:	1010706d 	.word	0x1010706d
1010716c:	1010706d 	.word	0x1010706d
10107170:	1010706d 	.word	0x1010706d
10107174:	1010706d 	.word	0x1010706d
10107178:	1010706d 	.word	0x1010706d
1010717c:	1010706d 	.word	0x1010706d
10107180:	1010706d 	.word	0x1010706d
10107184:	1010706d 	.word	0x1010706d
10107188:	1010706d 	.word	0x1010706d
1010718c:	1010706d 	.word	0x1010706d
10107190:	1010706d 	.word	0x1010706d
10107194:	1010706d 	.word	0x1010706d
10107198:	1010706d 	.word	0x1010706d
1010719c:	1010706d 	.word	0x1010706d
101071a0:	1010706d 	.word	0x1010706d
101071a4:	1010706d 	.word	0x1010706d
101071a8:	1010706d 	.word	0x1010706d
101071ac:	1010706d 	.word	0x1010706d
101071b0:	1010706d 	.word	0x1010706d
101071b4:	1010706d 	.word	0x1010706d
101071b8:	10107499 	.word	0x10107499
101071bc:	1010706d 	.word	0x1010706d
101071c0:	1010706d 	.word	0x1010706d
101071c4:	1010706d 	.word	0x1010706d
101071c8:	1010706d 	.word	0x1010706d
101071cc:	1010706d 	.word	0x1010706d
101071d0:	1010706d 	.word	0x1010706d
101071d4:	1010706d 	.word	0x1010706d
101071d8:	1010706d 	.word	0x1010706d
101071dc:	1010706d 	.word	0x1010706d
101071e0:	1010706d 	.word	0x1010706d
101071e4:	1010745d 	.word	0x1010745d
101071e8:	10107455 	.word	0x10107455
101071ec:	1010706d 	.word	0x1010706d
101071f0:	1010706d 	.word	0x1010706d
101071f4:	1010706d 	.word	0x1010706d
101071f8:	1010706d 	.word	0x1010706d
101071fc:	101074ad 	.word	0x101074ad
10107200:	1010706d 	.word	0x1010706d
10107204:	1010706d 	.word	0x1010706d
10107208:	1010706d 	.word	0x1010706d
1010720c:	1010706d 	.word	0x1010706d
10107210:	1010706d 	.word	0x1010706d
10107214:	1010744d 	.word	0x1010744d
10107218:	1010706d 	.word	0x1010706d
1010721c:	1010706d 	.word	0x1010706d
10107220:	1010706d 	.word	0x1010706d
10107224:	101073db 	.word	0x101073db
10107228:	1010706d 	.word	0x1010706d
1010722c:	101072cb 	.word	0x101072cb
10107230:	1010706d 	.word	0x1010706d
10107234:	1010706d 	.word	0x1010706d
10107238:	10107499 	.word	0x10107499
1010723c:	2a68      	cmp	r2, #104	; 0x68
1010723e:	9201      	str	r2, [sp, #4]
10107240:	f04f 38ff 	mov.w	r8, #4294967295
10107244:	f47f af38 	bne.w	101070b8 <_vsscanf+0xd4>
10107248:	786a      	ldrb	r2, [r5, #1]
1010724a:	2a68      	cmp	r2, #104	; 0x68
1010724c:	f105 0101 	add.w	r1, r5, #1
10107250:	f000 8184 	beq.w	1010755c <_vsscanf+0x578>
10107254:	460d      	mov	r5, r1
10107256:	e739      	b.n	101070cc <_vsscanf+0xe8>
10107258:	7869      	ldrb	r1, [r5, #1]
1010725a:	428a      	cmp	r2, r1
1010725c:	f105 0001 	add.w	r0, r5, #1
10107260:	f000 8157 	beq.w	10107512 <_vsscanf+0x52e>
10107264:	460a      	mov	r2, r1
10107266:	4605      	mov	r5, r0
10107268:	e730      	b.n	101070cc <_vsscanf+0xe8>
1010726a:	7820      	ldrb	r0, [r4, #0]
1010726c:	b938      	cbnz	r0, 1010727e <_vsscanf+0x29a>
1010726e:	e6fd      	b.n	1010706c <_vsscanf+0x88>
10107270:	2a2c      	cmp	r2, #44	; 0x2c
10107272:	d00a      	beq.n	1010728a <_vsscanf+0x2a6>
10107274:	2a25      	cmp	r2, #37	; 0x25
10107276:	d008      	beq.n	1010728a <_vsscanf+0x2a6>
10107278:	f012 0fdf 	tst.w	r2, #223	; 0xdf
1010727c:	d005      	beq.n	1010728a <_vsscanf+0x2a6>
1010727e:	f815 2f01 	ldrb.w	r2, [r5, #1]!
10107282:	f1a2 0309 	sub.w	r3, r2, #9
10107286:	2b04      	cmp	r3, #4
10107288:	d8f2      	bhi.n	10107270 <_vsscanf+0x28c>
1010728a:	2820      	cmp	r0, #32
1010728c:	d011      	beq.n	101072b2 <_vsscanf+0x2ce>
1010728e:	f1a0 0109 	sub.w	r1, r0, #9
10107292:	2904      	cmp	r1, #4
10107294:	d90d      	bls.n	101072b2 <_vsscanf+0x2ce>
10107296:	282c      	cmp	r0, #44	; 0x2c
10107298:	d105      	bne.n	101072a6 <_vsscanf+0x2c2>
1010729a:	e00a      	b.n	101072b2 <_vsscanf+0x2ce>
1010729c:	2b2c      	cmp	r3, #44	; 0x2c
1010729e:	d008      	beq.n	101072b2 <_vsscanf+0x2ce>
101072a0:	f013 0fdf 	tst.w	r3, #223	; 0xdf
101072a4:	d005      	beq.n	101072b2 <_vsscanf+0x2ce>
101072a6:	f814 3f01 	ldrb.w	r3, [r4, #1]!
101072aa:	f1a3 0109 	sub.w	r1, r3, #9
101072ae:	2904      	cmp	r1, #4
101072b0:	d8f4      	bhi.n	1010729c <_vsscanf+0x2b8>
101072b2:	462f      	mov	r7, r5
101072b4:	e6a9      	b.n	1010700a <_vsscanf+0x26>
101072b6:	9b02      	ldr	r3, [sp, #8]
101072b8:	f8da 2000 	ldr.w	r2, [sl]
101072bc:	1ae1      	subs	r1, r4, r3
101072be:	6011      	str	r1, [r2, #0]
101072c0:	f10a 0a04 	add.w	sl, sl, #4
101072c4:	786a      	ldrb	r2, [r5, #1]
101072c6:	1c6f      	adds	r7, r5, #1
101072c8:	e69f      	b.n	1010700a <_vsscanf+0x26>
101072ca:	2300      	movs	r3, #0
101072cc:	220a      	movs	r2, #10
101072ce:	9300      	str	r3, [sp, #0]
101072d0:	e001      	b.n	101072d6 <_vsscanf+0x2f2>
101072d2:	f814 6f01 	ldrb.w	r6, [r4, #1]!
101072d6:	2e20      	cmp	r6, #32
101072d8:	f1a6 0309 	sub.w	r3, r6, #9
101072dc:	d0f9      	beq.n	101072d2 <_vsscanf+0x2ee>
101072de:	2b04      	cmp	r3, #4
101072e0:	d9f7      	bls.n	101072d2 <_vsscanf+0x2ee>
101072e2:	2e2c      	cmp	r6, #44	; 0x2c
101072e4:	d0f5      	beq.n	101072d2 <_vsscanf+0x2ee>
101072e6:	9b00      	ldr	r3, [sp, #0]
101072e8:	4611      	mov	r1, r2
101072ea:	9203      	str	r2, [sp, #12]
101072ec:	b113      	cbz	r3, 101072f4 <_vsscanf+0x310>
101072ee:	2e2d      	cmp	r6, #45	; 0x2d
101072f0:	f000 8125 	beq.w	1010753e <_vsscanf+0x55a>
101072f4:	f1b8 3fff 	cmp.w	r8, #4294967295
101072f8:	4620      	mov	r0, r4
101072fa:	f000 811a 	beq.w	10107532 <_vsscanf+0x54e>
101072fe:	f7ff fe11 	bl	10106f24 <judge_digit_width>
10107302:	9a03      	ldr	r2, [sp, #12]
10107304:	4540      	cmp	r0, r8
10107306:	bfb8      	it	lt
10107308:	fa0f f880 	sxthlt.w	r8, r0
1010730c:	2e00      	cmp	r6, #0
1010730e:	f43f aead 	beq.w	1010706c <_vsscanf+0x88>
10107312:	2a10      	cmp	r2, #16
10107314:	f000 8101 	beq.w	1010751a <_vsscanf+0x536>
10107318:	2a0a      	cmp	r2, #10
1010731a:	f000 80e2 	beq.w	101074e2 <_vsscanf+0x4fe>
1010731e:	2a08      	cmp	r2, #8
10107320:	f040 80dc 	bne.w	101074dc <_vsscanf+0x4f8>
10107324:	3e30      	subs	r6, #48	; 0x30
10107326:	2e07      	cmp	r6, #7
10107328:	f63f aea0 	bhi.w	1010706c <_vsscanf+0x88>
1010732c:	f1b8 0f18 	cmp.w	r8, #24
10107330:	f300 80df 	bgt.w	101074f2 <_vsscanf+0x50e>
10107334:	f1b8 0f00 	cmp.w	r8, #0
10107338:	f340 8120 	ble.w	1010757c <_vsscanf+0x598>
1010733c:	a806      	add	r0, sp, #24
1010733e:	f108 3cff 	add.w	ip, r8, #4294967295
10107342:	f10d 0117 	add.w	r1, sp, #23
10107346:	4484      	add	ip, r0
10107348:	1e66      	subs	r6, r4, #1
1010734a:	f816 3f01 	ldrb.w	r3, [r6, #1]!
1010734e:	f801 3f01 	strb.w	r3, [r1, #1]!
10107352:	4561      	cmp	r1, ip
10107354:	d1f9      	bne.n	1010734a <_vsscanf+0x366>
10107356:	9b00      	ldr	r3, [sp, #0]
10107358:	2b00      	cmp	r3, #0
1010735a:	f000 80d2 	beq.w	10107502 <_vsscanf+0x51e>
1010735e:	9b01      	ldr	r3, [sp, #4]
10107360:	2b4c      	cmp	r3, #76	; 0x4c
10107362:	a905      	add	r1, sp, #20
10107364:	f000 80ff 	beq.w	10107566 <_vsscanf+0x582>
10107368:	4e8a      	ldr	r6, [pc, #552]	; (10107594 <_vsscanf+0x5b0>)
1010736a:	47b0      	blx	r6
1010736c:	17c1      	asrs	r1, r0, #31
1010736e:	2600      	movs	r6, #0
10107370:	4444      	add	r4, r8
10107372:	9405      	str	r4, [sp, #20]
10107374:	f10d 0217 	add.w	r2, sp, #23
10107378:	f802 6f01 	strb.w	r6, [r2, #1]!
1010737c:	454a      	cmp	r2, r9
1010737e:	d1fb      	bne.n	10107378 <_vsscanf+0x394>
10107380:	9b01      	ldr	r3, [sp, #4]
10107382:	f1a3 0248 	sub.w	r2, r3, #72	; 0x48
10107386:	2a32      	cmp	r2, #50	; 0x32
10107388:	d81b      	bhi.n	101073c2 <_vsscanf+0x3de>
1010738a:	e8df f002 	tbb	[pc, r2]
1010738e:	1a9a      	.short	0x1a9a
10107390:	1a931a1a 	.word	0x1a931a1a
10107394:	1a1a1a1a 	.word	0x1a1a1a1a
10107398:	1a1a1a1a 	.word	0x1a1a1a1a
1010739c:	1a1a1a1a 	.word	0x1a1a1a1a
101073a0:	1a1a1a1a 	.word	0x1a1a1a1a
101073a4:	1a1a1a1a 	.word	0x1a1a1a1a
101073a8:	1a1a1a1a 	.word	0x1a1a1a1a
101073ac:	1aa11a1a 	.word	0x1aa11a1a
101073b0:	1a1a1a1a 	.word	0x1a1a1a1a
101073b4:	1a1a1a1a 	.word	0x1a1a1a1a
101073b8:	1a1a1a1a 	.word	0x1a1a1a1a
101073bc:	1a1a1a1a 	.word	0x1a1a1a1a
101073c0:	1a          	.byte	0x1a
101073c1:	00          	.byte	0x00
101073c2:	f8da 2000 	ldr.w	r2, [sl]
101073c6:	6010      	str	r0, [r2, #0]
101073c8:	f10a 0a04 	add.w	sl, sl, #4
101073cc:	f10b 0b01 	add.w	fp, fp, #1
101073d0:	2c00      	cmp	r4, #0
101073d2:	f43f ae4b 	beq.w	1010706c <_vsscanf+0x88>
101073d6:	786a      	ldrb	r2, [r5, #1]
101073d8:	e617      	b.n	1010700a <_vsscanf+0x26>
101073da:	f647 71ff 	movw	r1, #32767	; 0x7fff
101073de:	4632      	mov	r2, r6
101073e0:	f1b8 3fff 	cmp.w	r8, #4294967295
101073e4:	bf08      	it	eq
101073e6:	4688      	moveq	r8, r1
101073e8:	f10a 0604 	add.w	r6, sl, #4
101073ec:	f8da 3000 	ldr.w	r3, [sl]
101073f0:	e001      	b.n	101073f6 <_vsscanf+0x412>
101073f2:	f814 2f01 	ldrb.w	r2, [r4, #1]!
101073f6:	2a20      	cmp	r2, #32
101073f8:	f1a2 0109 	sub.w	r1, r2, #9
101073fc:	d0f9      	beq.n	101073f2 <_vsscanf+0x40e>
101073fe:	2904      	cmp	r1, #4
10107400:	d9f7      	bls.n	101073f2 <_vsscanf+0x40e>
10107402:	2a2c      	cmp	r2, #44	; 0x2c
10107404:	d0f5      	beq.n	101073f2 <_vsscanf+0x40e>
10107406:	b1d2      	cbz	r2, 1010743e <_vsscanf+0x45a>
10107408:	f108 30ff 	add.w	r0, r8, #4294967295
1010740c:	b280      	uxth	r0, r0
1010740e:	f1b8 0f00 	cmp.w	r8, #0
10107412:	d014      	beq.n	1010743e <_vsscanf+0x45a>
10107414:	3002      	adds	r0, #2
10107416:	4420      	add	r0, r4
10107418:	1c61      	adds	r1, r4, #1
1010741a:	e006      	b.n	1010742a <_vsscanf+0x446>
1010741c:	f1be 0f04 	cmp.w	lr, #4
10107420:	d90d      	bls.n	1010743e <_vsscanf+0x45a>
10107422:	2a2c      	cmp	r2, #44	; 0x2c
10107424:	d00b      	beq.n	1010743e <_vsscanf+0x45a>
10107426:	4281      	cmp	r1, r0
10107428:	d009      	beq.n	1010743e <_vsscanf+0x45a>
1010742a:	f803 2b01 	strb.w	r2, [r3], #1
1010742e:	460c      	mov	r4, r1
10107430:	f811 2b01 	ldrb.w	r2, [r1], #1
10107434:	f012 0fdf 	tst.w	r2, #223	; 0xdf
10107438:	f1a2 0e09 	sub.w	lr, r2, #9
1010743c:	d1ee      	bne.n	1010741c <_vsscanf+0x438>
1010743e:	2200      	movs	r2, #0
10107440:	701a      	strb	r2, [r3, #0]
10107442:	f10b 0b01 	add.w	fp, fp, #1
10107446:	46b2      	mov	sl, r6
10107448:	786a      	ldrb	r2, [r5, #1]
1010744a:	e5de      	b.n	1010700a <_vsscanf+0x26>
1010744c:	2300      	movs	r3, #0
1010744e:	2208      	movs	r2, #8
10107450:	9300      	str	r3, [sp, #0]
10107452:	e740      	b.n	101072d6 <_vsscanf+0x2f2>
10107454:	2301      	movs	r3, #1
10107456:	220a      	movs	r2, #10
10107458:	9300      	str	r3, [sp, #0]
1010745a:	e73c      	b.n	101072d6 <_vsscanf+0x2f2>
1010745c:	f1b8 3fff 	cmp.w	r8, #4294967295
10107460:	f10a 0e04 	add.w	lr, sl, #4
10107464:	f8da 0000 	ldr.w	r0, [sl]
10107468:	f000 8091 	beq.w	1010758e <_vsscanf+0x5aa>
1010746c:	4633      	mov	r3, r6
1010746e:	3801      	subs	r0, #1
10107470:	1c61      	adds	r1, r4, #1
10107472:	f108 38ff 	add.w	r8, r8, #4294967295
10107476:	fa0f f888 	sxth.w	r8, r8
1010747a:	f1b8 0f00 	cmp.w	r8, #0
1010747e:	f800 3f01 	strb.w	r3, [r0, #1]!
10107482:	460c      	mov	r4, r1
10107484:	dd03      	ble.n	1010748e <_vsscanf+0x4aa>
10107486:	f811 3b01 	ldrb.w	r3, [r1], #1
1010748a:	2b00      	cmp	r3, #0
1010748c:	d1f1      	bne.n	10107472 <_vsscanf+0x48e>
1010748e:	f10b 0b01 	add.w	fp, fp, #1
10107492:	786a      	ldrb	r2, [r5, #1]
10107494:	46f2      	mov	sl, lr
10107496:	e5b8      	b.n	1010700a <_vsscanf+0x26>
10107498:	2300      	movs	r3, #0
1010749a:	2210      	movs	r2, #16
1010749c:	9300      	str	r3, [sp, #0]
1010749e:	e71a      	b.n	101072d6 <_vsscanf+0x2f2>
101074a0:	2e25      	cmp	r6, #37	; 0x25
101074a2:	f47f ade3 	bne.w	1010706c <_vsscanf+0x88>
101074a6:	3401      	adds	r4, #1
101074a8:	786a      	ldrb	r2, [r5, #1]
101074aa:	e5ae      	b.n	1010700a <_vsscanf+0x26>
101074ac:	2301      	movs	r3, #1
101074ae:	2200      	movs	r2, #0
101074b0:	9300      	str	r3, [sp, #0]
101074b2:	e710      	b.n	101072d6 <_vsscanf+0x2f2>
101074b4:	f8da 2000 	ldr.w	r2, [sl]
101074b8:	f10a 0a04 	add.w	sl, sl, #4
101074bc:	e882 0003 	stmia.w	r2, {r0, r1}
101074c0:	e784      	b.n	101073cc <_vsscanf+0x3e8>
101074c2:	f8da 2000 	ldr.w	r2, [sl]
101074c6:	7010      	strb	r0, [r2, #0]
101074c8:	f10a 0a04 	add.w	sl, sl, #4
101074cc:	9c05      	ldr	r4, [sp, #20]
101074ce:	e77d      	b.n	101073cc <_vsscanf+0x3e8>
101074d0:	f8da 2000 	ldr.w	r2, [sl]
101074d4:	f10a 0a04 	add.w	sl, sl, #4
101074d8:	8010      	strh	r0, [r2, #0]
101074da:	e777      	b.n	101073cc <_vsscanf+0x3e8>
101074dc:	2a00      	cmp	r2, #0
101074de:	f47f af25 	bne.w	1010732c <_vsscanf+0x348>
101074e2:	3e30      	subs	r6, #48	; 0x30
101074e4:	2e09      	cmp	r6, #9
101074e6:	f63f adc1 	bhi.w	1010706c <_vsscanf+0x88>
101074ea:	f1b8 0f18 	cmp.w	r8, #24
101074ee:	f77f af21 	ble.w	10107334 <_vsscanf+0x350>
101074f2:	f240 1181 	movw	r1, #385	; 0x181
101074f6:	4828      	ldr	r0, [pc, #160]	; (10107598 <_vsscanf+0x5b4>)
101074f8:	9203      	str	r2, [sp, #12]
101074fa:	f7f9 f9b9 	bl	10100870 <io_assert_failed>
101074fe:	9a03      	ldr	r2, [sp, #12]
10107500:	e718      	b.n	10107334 <_vsscanf+0x350>
10107502:	9b01      	ldr	r3, [sp, #4]
10107504:	2b4c      	cmp	r3, #76	; 0x4c
10107506:	a905      	add	r1, sp, #20
10107508:	d030      	beq.n	1010756c <_vsscanf+0x588>
1010750a:	4b24      	ldr	r3, [pc, #144]	; (1010759c <_vsscanf+0x5b8>)
1010750c:	4798      	blx	r3
1010750e:	9900      	ldr	r1, [sp, #0]
10107510:	e72d      	b.n	1010736e <_vsscanf+0x38a>
10107512:	2a6c      	cmp	r2, #108	; 0x6c
10107514:	d02d      	beq.n	10107572 <_vsscanf+0x58e>
10107516:	4605      	mov	r5, r0
10107518:	e5d8      	b.n	101070cc <_vsscanf+0xe8>
1010751a:	f1a6 0130 	sub.w	r1, r6, #48	; 0x30
1010751e:	2909      	cmp	r1, #9
10107520:	f67f af04 	bls.w	1010732c <_vsscanf+0x348>
10107524:	f026 0120 	bic.w	r1, r6, #32
10107528:	3941      	subs	r1, #65	; 0x41
1010752a:	2905      	cmp	r1, #5
1010752c:	f67f aefe 	bls.w	1010732c <_vsscanf+0x348>
10107530:	e59c      	b.n	1010706c <_vsscanf+0x88>
10107532:	f7ff fcf7 	bl	10106f24 <judge_digit_width>
10107536:	9a03      	ldr	r2, [sp, #12]
10107538:	fa0f f880 	sxth.w	r8, r0
1010753c:	e6e6      	b.n	1010730c <_vsscanf+0x328>
1010753e:	f1b8 3fff 	cmp.w	r8, #4294967295
10107542:	f104 0001 	add.w	r0, r4, #1
10107546:	d01b      	beq.n	10107580 <_vsscanf+0x59c>
10107548:	f7ff fcec 	bl	10106f24 <judge_digit_width>
1010754c:	3001      	adds	r0, #1
1010754e:	4540      	cmp	r0, r8
10107550:	9a03      	ldr	r2, [sp, #12]
10107552:	bfb8      	it	lt
10107554:	fa0f f880 	sxthlt.w	r8, r0
10107558:	7866      	ldrb	r6, [r4, #1]
1010755a:	e6d7      	b.n	1010730c <_vsscanf+0x328>
1010755c:	2348      	movs	r3, #72	; 0x48
1010755e:	78aa      	ldrb	r2, [r5, #2]
10107560:	9301      	str	r3, [sp, #4]
10107562:	3502      	adds	r5, #2
10107564:	e5b2      	b.n	101070cc <_vsscanf+0xe8>
10107566:	4b0e      	ldr	r3, [pc, #56]	; (101075a0 <_vsscanf+0x5bc>)
10107568:	4798      	blx	r3
1010756a:	e700      	b.n	1010736e <_vsscanf+0x38a>
1010756c:	4b0d      	ldr	r3, [pc, #52]	; (101075a4 <_vsscanf+0x5c0>)
1010756e:	4798      	blx	r3
10107570:	e6fd      	b.n	1010736e <_vsscanf+0x38a>
10107572:	234c      	movs	r3, #76	; 0x4c
10107574:	78aa      	ldrb	r2, [r5, #2]
10107576:	9301      	str	r3, [sp, #4]
10107578:	3502      	adds	r5, #2
1010757a:	e5a7      	b.n	101070cc <_vsscanf+0xe8>
1010757c:	a806      	add	r0, sp, #24
1010757e:	e6ea      	b.n	10107356 <_vsscanf+0x372>
10107580:	f7ff fcd0 	bl	10106f24 <judge_digit_width>
10107584:	3001      	adds	r0, #1
10107586:	fa0f f880 	sxth.w	r8, r0
1010758a:	9a03      	ldr	r2, [sp, #12]
1010758c:	e7e4      	b.n	10107558 <_vsscanf+0x574>
1010758e:	3401      	adds	r4, #1
10107590:	7006      	strb	r6, [r0, #0]
10107592:	e77c      	b.n	1010748e <_vsscanf+0x4aa>
10107594:	10108199 	.word	0x10108199
10107598:	101d5430 	.word	0x101d5430
1010759c:	101082d1 	.word	0x101082d1
101075a0:	10107fe5 	.word	0x10107fe5
101075a4:	10107f25 	.word	0x10107f25

101075a8 <_sscanf>:
101075a8:	b40e      	push	{r1, r2, r3}
101075aa:	b500      	push	{lr}
101075ac:	b082      	sub	sp, #8
101075ae:	ab03      	add	r3, sp, #12
101075b0:	f853 1b04 	ldr.w	r1, [r3], #4
101075b4:	461a      	mov	r2, r3
101075b6:	9301      	str	r3, [sp, #4]
101075b8:	f7ff fd14 	bl	10106fe4 <_vsscanf>
101075bc:	b002      	add	sp, #8
101075be:	f85d eb04 	ldr.w	lr, [sp], #4
101075c2:	b003      	add	sp, #12
101075c4:	4770      	bx	lr
101075c6:	bf00      	nop

101075c8 <_stratoi>:
101075c8:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
101075cc:	2400      	movs	r4, #0
101075ce:	4605      	mov	r5, r0
101075d0:	4e11      	ldr	r6, [pc, #68]	; (10107618 <_stratoi+0x50>)
101075d2:	4627      	mov	r7, r4
101075d4:	46a0      	mov	r8, r4
101075d6:	47b0      	blx	r6
101075d8:	f105 39ff 	add.w	r9, r5, #4294967295
101075dc:	f819 3f01 	ldrb.w	r3, [r9, #1]!
101075e0:	f1a3 0130 	sub.w	r1, r3, #48	; 0x30
101075e4:	eb08 0288 	add.w	r2, r8, r8, lsl #2
101075e8:	2909      	cmp	r1, #9
101075ea:	eb03 0342 	add.w	r3, r3, r2, lsl #1
101075ee:	d80c      	bhi.n	1010760a <_stratoi+0x42>
101075f0:	f1a3 0830 	sub.w	r8, r3, #48	; 0x30
101075f4:	4628      	mov	r0, r5
101075f6:	47b0      	blx	r6
101075f8:	3401      	adds	r4, #1
101075fa:	42a0      	cmp	r0, r4
101075fc:	d2ee      	bcs.n	101075dc <_stratoi+0x14>
101075fe:	b10f      	cbz	r7, 10107604 <_stratoi+0x3c>
10107600:	f1c8 0800 	rsb	r8, r8, #0
10107604:	4640      	mov	r0, r8
10107606:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
1010760a:	782b      	ldrb	r3, [r5, #0]
1010760c:	2b2d      	cmp	r3, #45	; 0x2d
1010760e:	d1f6      	bne.n	101075fe <_stratoi+0x36>
10107610:	2c00      	cmp	r4, #0
10107612:	d1f4      	bne.n	101075fe <_stratoi+0x36>
10107614:	2701      	movs	r7, #1
10107616:	e7ed      	b.n	101075f4 <_stratoi+0x2c>
10107618:	10107821 	.word	0x10107821

1010761c <_strcat>:
1010761c:	0783      	lsls	r3, r0, #30
1010761e:	b510      	push	{r4, lr}
10107620:	4604      	mov	r4, r0
10107622:	d110      	bne.n	10107646 <_strcat+0x2a>
10107624:	6802      	ldr	r2, [r0, #0]
10107626:	f1a2 3301 	sub.w	r3, r2, #16843009	; 0x1010101
1010762a:	ea23 0302 	bic.w	r3, r3, r2
1010762e:	f013 3f80 	tst.w	r3, #2155905152	; 0x80808080
10107632:	d108      	bne.n	10107646 <_strcat+0x2a>
10107634:	f850 2f04 	ldr.w	r2, [r0, #4]!
10107638:	f1a2 3301 	sub.w	r3, r2, #16843009	; 0x1010101
1010763c:	ea23 0302 	bic.w	r3, r3, r2
10107640:	f013 3f80 	tst.w	r3, #2155905152	; 0x80808080
10107644:	d0f6      	beq.n	10107634 <_strcat+0x18>
10107646:	7803      	ldrb	r3, [r0, #0]
10107648:	b11b      	cbz	r3, 10107652 <_strcat+0x36>
1010764a:	f810 3f01 	ldrb.w	r3, [r0, #1]!
1010764e:	2b00      	cmp	r3, #0
10107650:	d1fb      	bne.n	1010764a <_strcat+0x2e>
10107652:	f000 f8a5 	bl	101077a0 <_strcpy>
10107656:	4620      	mov	r0, r4
10107658:	bd10      	pop	{r4, pc}
1010765a:	bf00      	nop

1010765c <_strchr>:
1010765c:	b470      	push	{r4, r5, r6}
1010765e:	f011 04ff 	ands.w	r4, r1, #255	; 0xff
10107662:	d034      	beq.n	101076ce <_strchr+0x72>
10107664:	0785      	lsls	r5, r0, #30
10107666:	d00f      	beq.n	10107688 <_strchr+0x2c>
10107668:	7803      	ldrb	r3, [r0, #0]
1010766a:	2b00      	cmp	r3, #0
1010766c:	d05a      	beq.n	10107724 <_strchr+0xc8>
1010766e:	429c      	cmp	r4, r3
10107670:	d02b      	beq.n	101076ca <_strchr+0x6e>
10107672:	1c43      	adds	r3, r0, #1
10107674:	e005      	b.n	10107682 <_strchr+0x26>
10107676:	f813 2b01 	ldrb.w	r2, [r3], #1
1010767a:	2a00      	cmp	r2, #0
1010767c:	d04f      	beq.n	1010771e <_strchr+0xc2>
1010767e:	4294      	cmp	r4, r2
10107680:	d023      	beq.n	101076ca <_strchr+0x6e>
10107682:	079a      	lsls	r2, r3, #30
10107684:	4618      	mov	r0, r3
10107686:	d1f6      	bne.n	10107676 <_strchr+0x1a>
10107688:	020e      	lsls	r6, r1, #8
1010768a:	f406 467f 	and.w	r6, r6, #65280	; 0xff00
1010768e:	4326      	orrs	r6, r4
10107690:	6801      	ldr	r1, [r0, #0]
10107692:	ea46 4606 	orr.w	r6, r6, r6, lsl #16
10107696:	e001      	b.n	1010769c <_strchr+0x40>
10107698:	f850 1f04 	ldr.w	r1, [r0, #4]!
1010769c:	ea86 0501 	eor.w	r5, r6, r1
101076a0:	f1a5 3301 	sub.w	r3, r5, #16843009	; 0x1010101
101076a4:	f1a1 3201 	sub.w	r2, r1, #16843009	; 0x1010101
101076a8:	ea23 0305 	bic.w	r3, r3, r5
101076ac:	ea22 0201 	bic.w	r2, r2, r1
101076b0:	4313      	orrs	r3, r2
101076b2:	f013 3f80 	tst.w	r3, #2155905152	; 0x80808080
101076b6:	d0ef      	beq.n	10107698 <_strchr+0x3c>
101076b8:	7803      	ldrb	r3, [r0, #0]
101076ba:	b923      	cbnz	r3, 101076c6 <_strchr+0x6a>
101076bc:	e032      	b.n	10107724 <_strchr+0xc8>
101076be:	f810 3f01 	ldrb.w	r3, [r0, #1]!
101076c2:	2b00      	cmp	r3, #0
101076c4:	d02e      	beq.n	10107724 <_strchr+0xc8>
101076c6:	429c      	cmp	r4, r3
101076c8:	d1f9      	bne.n	101076be <_strchr+0x62>
101076ca:	bc70      	pop	{r4, r5, r6}
101076cc:	4770      	bx	lr
101076ce:	0784      	lsls	r4, r0, #30
101076d0:	d00b      	beq.n	101076ea <_strchr+0x8e>
101076d2:	7803      	ldrb	r3, [r0, #0]
101076d4:	2b00      	cmp	r3, #0
101076d6:	d0f8      	beq.n	101076ca <_strchr+0x6e>
101076d8:	1c43      	adds	r3, r0, #1
101076da:	e003      	b.n	101076e4 <_strchr+0x88>
101076dc:	7802      	ldrb	r2, [r0, #0]
101076de:	3301      	adds	r3, #1
101076e0:	2a00      	cmp	r2, #0
101076e2:	d0f2      	beq.n	101076ca <_strchr+0x6e>
101076e4:	0799      	lsls	r1, r3, #30
101076e6:	4618      	mov	r0, r3
101076e8:	d1f8      	bne.n	101076dc <_strchr+0x80>
101076ea:	6802      	ldr	r2, [r0, #0]
101076ec:	f1a2 3301 	sub.w	r3, r2, #16843009	; 0x1010101
101076f0:	ea23 0302 	bic.w	r3, r3, r2
101076f4:	f013 3f80 	tst.w	r3, #2155905152	; 0x80808080
101076f8:	d108      	bne.n	1010770c <_strchr+0xb0>
101076fa:	f850 2f04 	ldr.w	r2, [r0, #4]!
101076fe:	f1a2 3301 	sub.w	r3, r2, #16843009	; 0x1010101
10107702:	ea23 0302 	bic.w	r3, r3, r2
10107706:	f013 3f80 	tst.w	r3, #2155905152	; 0x80808080
1010770a:	d0f6      	beq.n	101076fa <_strchr+0x9e>
1010770c:	7803      	ldrb	r3, [r0, #0]
1010770e:	2b00      	cmp	r3, #0
10107710:	d0db      	beq.n	101076ca <_strchr+0x6e>
10107712:	f810 3f01 	ldrb.w	r3, [r0, #1]!
10107716:	2b00      	cmp	r3, #0
10107718:	d1fb      	bne.n	10107712 <_strchr+0xb6>
1010771a:	bc70      	pop	{r4, r5, r6}
1010771c:	4770      	bx	lr
1010771e:	4610      	mov	r0, r2
10107720:	bc70      	pop	{r4, r5, r6}
10107722:	4770      	bx	lr
10107724:	4618      	mov	r0, r3
10107726:	bc70      	pop	{r4, r5, r6}
10107728:	4770      	bx	lr
1010772a:	bf00      	nop

1010772c <_strcmp>:
1010772c:	ea40 0301 	orr.w	r3, r0, r1
10107730:	f013 0303 	ands.w	r3, r3, #3
10107734:	b470      	push	{r4, r5, r6}
10107736:	d11d      	bne.n	10107774 <_strcmp+0x48>
10107738:	680a      	ldr	r2, [r1, #0]
1010773a:	6804      	ldr	r4, [r0, #0]
1010773c:	42a2      	cmp	r2, r4
1010773e:	d119      	bne.n	10107774 <_strcmp+0x48>
10107740:	f1a2 3401 	sub.w	r4, r2, #16843009	; 0x1010101
10107744:	ea24 0202 	bic.w	r2, r4, r2
10107748:	f012 3f80 	tst.w	r2, #2155905152	; 0x80808080
1010774c:	d125      	bne.n	1010779a <_strcmp+0x6e>
1010774e:	1d05      	adds	r5, r0, #4
10107750:	1d0c      	adds	r4, r1, #4
10107752:	e002      	b.n	1010775a <_strcmp+0x2e>
10107754:	f012 3f80 	tst.w	r2, #2155905152	; 0x80808080
10107758:	d11c      	bne.n	10107794 <_strcmp+0x68>
1010775a:	6826      	ldr	r6, [r4, #0]
1010775c:	4628      	mov	r0, r5
1010775e:	f855 3b04 	ldr.w	r3, [r5], #4
10107762:	f1a3 3201 	sub.w	r2, r3, #16843009	; 0x1010101
10107766:	42b3      	cmp	r3, r6
10107768:	4621      	mov	r1, r4
1010776a:	ea22 0203 	bic.w	r2, r2, r3
1010776e:	f104 0404 	add.w	r4, r4, #4
10107772:	d0ef      	beq.n	10107754 <_strcmp+0x28>
10107774:	7803      	ldrb	r3, [r0, #0]
10107776:	780a      	ldrb	r2, [r1, #0]
10107778:	b92b      	cbnz	r3, 10107786 <_strcmp+0x5a>
1010777a:	e006      	b.n	1010778a <_strcmp+0x5e>
1010777c:	f810 3f01 	ldrb.w	r3, [r0, #1]!
10107780:	b133      	cbz	r3, 10107790 <_strcmp+0x64>
10107782:	f811 2f01 	ldrb.w	r2, [r1, #1]!
10107786:	4293      	cmp	r3, r2
10107788:	d0f8      	beq.n	1010777c <_strcmp+0x50>
1010778a:	1a98      	subs	r0, r3, r2
1010778c:	bc70      	pop	{r4, r5, r6}
1010778e:	4770      	bx	lr
10107790:	784a      	ldrb	r2, [r1, #1]
10107792:	e7fa      	b.n	1010778a <_strcmp+0x5e>
10107794:	2000      	movs	r0, #0
10107796:	bc70      	pop	{r4, r5, r6}
10107798:	4770      	bx	lr
1010779a:	4618      	mov	r0, r3
1010779c:	e7f6      	b.n	1010778c <_strcmp+0x60>
1010779e:	bf00      	nop

101077a0 <_strcpy>:
101077a0:	ea41 0300 	orr.w	r3, r1, r0
101077a4:	079b      	lsls	r3, r3, #30
101077a6:	b430      	push	{r4, r5}
101077a8:	d11e      	bne.n	101077e8 <_strcpy+0x48>
101077aa:	680a      	ldr	r2, [r1, #0]
101077ac:	f1a2 3301 	sub.w	r3, r2, #16843009	; 0x1010101
101077b0:	ea23 0302 	bic.w	r3, r3, r2
101077b4:	f013 3f80 	tst.w	r3, #2155905152	; 0x80808080
101077b8:	4603      	mov	r3, r0
101077ba:	d10c      	bne.n	101077d6 <_strcpy+0x36>
101077bc:	1d0d      	adds	r5, r1, #4
101077be:	f843 2b04 	str.w	r2, [r3], #4
101077c2:	4629      	mov	r1, r5
101077c4:	f855 2b04 	ldr.w	r2, [r5], #4
101077c8:	f1a2 3401 	sub.w	r4, r2, #16843009	; 0x1010101
101077cc:	ea24 0402 	bic.w	r4, r4, r2
101077d0:	f014 3f80 	tst.w	r4, #2155905152	; 0x80808080
101077d4:	d0f3      	beq.n	101077be <_strcpy+0x1e>
101077d6:	3b01      	subs	r3, #1
101077d8:	f811 2b01 	ldrb.w	r2, [r1], #1
101077dc:	f803 2f01 	strb.w	r2, [r3, #1]!
101077e0:	2a00      	cmp	r2, #0
101077e2:	d1f9      	bne.n	101077d8 <_strcpy+0x38>
101077e4:	bc30      	pop	{r4, r5}
101077e6:	4770      	bx	lr
101077e8:	4603      	mov	r3, r0
101077ea:	e7f4      	b.n	101077d6 <_strcpy+0x36>

101077ec <_stricmp>:
101077ec:	b470      	push	{r4, r5, r6}
101077ee:	f810 3b01 	ldrb.w	r3, [r0], #1
101077f2:	f811 2b01 	ldrb.w	r2, [r1], #1
101077f6:	4293      	cmp	r3, r2
101077f8:	d009      	beq.n	1010780e <_stricmp+0x22>
101077fa:	f043 0420 	orr.w	r4, r3, #32
101077fe:	f1a4 0561 	sub.w	r5, r4, #97	; 0x61
10107802:	2d19      	cmp	r5, #25
10107804:	d808      	bhi.n	10107818 <_stricmp+0x2c>
10107806:	f042 0620 	orr.w	r6, r2, #32
1010780a:	42b4      	cmp	r4, r6
1010780c:	d104      	bne.n	10107818 <_stricmp+0x2c>
1010780e:	2b00      	cmp	r3, #0
10107810:	d1ed      	bne.n	101077ee <_stricmp+0x2>
10107812:	4618      	mov	r0, r3
10107814:	bc70      	pop	{r4, r5, r6}
10107816:	4770      	bx	lr
10107818:	2001      	movs	r0, #1
1010781a:	bc70      	pop	{r4, r5, r6}
1010781c:	4770      	bx	lr
1010781e:	bf00      	nop

10107820 <_strlen>:
10107820:	b410      	push	{r4}
10107822:	0784      	lsls	r4, r0, #30
10107824:	d029      	beq.n	1010787a <_strlen+0x5a>
10107826:	7803      	ldrb	r3, [r0, #0]
10107828:	b34b      	cbz	r3, 1010787e <_strlen+0x5e>
1010782a:	1c43      	adds	r3, r0, #1
1010782c:	e003      	b.n	10107836 <_strlen+0x16>
1010782e:	7819      	ldrb	r1, [r3, #0]
10107830:	1c5c      	adds	r4, r3, #1
10107832:	b1f1      	cbz	r1, 10107872 <_strlen+0x52>
10107834:	4623      	mov	r3, r4
10107836:	0799      	lsls	r1, r3, #30
10107838:	461a      	mov	r2, r3
1010783a:	d1f8      	bne.n	1010782e <_strlen+0xe>
1010783c:	6811      	ldr	r1, [r2, #0]
1010783e:	f1a1 3301 	sub.w	r3, r1, #16843009	; 0x1010101
10107842:	ea23 0301 	bic.w	r3, r3, r1
10107846:	f013 3f80 	tst.w	r3, #2155905152	; 0x80808080
1010784a:	d108      	bne.n	1010785e <_strlen+0x3e>
1010784c:	f852 4f04 	ldr.w	r4, [r2, #4]!
10107850:	f1a4 3101 	sub.w	r1, r4, #16843009	; 0x1010101
10107854:	ea21 0104 	bic.w	r1, r1, r4
10107858:	f011 3f80 	tst.w	r1, #2155905152	; 0x80808080
1010785c:	d0f6      	beq.n	1010784c <_strlen+0x2c>
1010785e:	7813      	ldrb	r3, [r2, #0]
10107860:	b11b      	cbz	r3, 1010786a <_strlen+0x4a>
10107862:	f812 1f01 	ldrb.w	r1, [r2, #1]!
10107866:	2900      	cmp	r1, #0
10107868:	d1fb      	bne.n	10107862 <_strlen+0x42>
1010786a:	1a10      	subs	r0, r2, r0
1010786c:	f85d 4b04 	ldr.w	r4, [sp], #4
10107870:	4770      	bx	lr
10107872:	1a18      	subs	r0, r3, r0
10107874:	f85d 4b04 	ldr.w	r4, [sp], #4
10107878:	4770      	bx	lr
1010787a:	4602      	mov	r2, r0
1010787c:	e7de      	b.n	1010783c <_strlen+0x1c>
1010787e:	4618      	mov	r0, r3
10107880:	e7f4      	b.n	1010786c <_strlen+0x4c>
10107882:	bf00      	nop

10107884 <_strncat>:
10107884:	0783      	lsls	r3, r0, #30
10107886:	b430      	push	{r4, r5}
10107888:	d125      	bne.n	101078d6 <_strncat+0x52>
1010788a:	6804      	ldr	r4, [r0, #0]
1010788c:	f1a4 3301 	sub.w	r3, r4, #16843009	; 0x1010101
10107890:	ea23 0304 	bic.w	r3, r3, r4
10107894:	f013 3f80 	tst.w	r3, #2155905152	; 0x80808080
10107898:	4603      	mov	r3, r0
1010789a:	d108      	bne.n	101078ae <_strncat+0x2a>
1010789c:	f853 5f04 	ldr.w	r5, [r3, #4]!
101078a0:	f1a5 3401 	sub.w	r4, r5, #16843009	; 0x1010101
101078a4:	ea24 0405 	bic.w	r4, r4, r5
101078a8:	f014 3f80 	tst.w	r4, #2155905152	; 0x80808080
101078ac:	d0f6      	beq.n	1010789c <_strncat+0x18>
101078ae:	781c      	ldrb	r4, [r3, #0]
101078b0:	b11c      	cbz	r4, 101078ba <_strncat+0x36>
101078b2:	f813 4f01 	ldrb.w	r4, [r3, #1]!
101078b6:	2c00      	cmp	r4, #0
101078b8:	d1fb      	bne.n	101078b2 <_strncat+0x2e>
101078ba:	188d      	adds	r5, r1, r2
101078bc:	e005      	b.n	101078ca <_strncat+0x46>
101078be:	f811 4b01 	ldrb.w	r4, [r1], #1
101078c2:	f803 4b01 	strb.w	r4, [r3], #1
101078c6:	b124      	cbz	r4, 101078d2 <_strncat+0x4e>
101078c8:	b13a      	cbz	r2, 101078da <_strncat+0x56>
101078ca:	42a9      	cmp	r1, r5
101078cc:	f102 32ff 	add.w	r2, r2, #4294967295
101078d0:	d1f5      	bne.n	101078be <_strncat+0x3a>
101078d2:	bc30      	pop	{r4, r5}
101078d4:	4770      	bx	lr
101078d6:	4603      	mov	r3, r0
101078d8:	e7e9      	b.n	101078ae <_strncat+0x2a>
101078da:	701a      	strb	r2, [r3, #0]
101078dc:	e7f5      	b.n	101078ca <_strncat+0x46>
101078de:	bf00      	nop

101078e0 <_strncmp>:
101078e0:	2a00      	cmp	r2, #0
101078e2:	d041      	beq.n	10107968 <_strncmp+0x88>
101078e4:	ea40 0301 	orr.w	r3, r0, r1
101078e8:	f013 0303 	ands.w	r3, r3, #3
101078ec:	b4f0      	push	{r4, r5, r6, r7}
101078ee:	d125      	bne.n	1010793c <_strncmp+0x5c>
101078f0:	2a03      	cmp	r2, #3
101078f2:	d923      	bls.n	1010793c <_strncmp+0x5c>
101078f4:	6804      	ldr	r4, [r0, #0]
101078f6:	680d      	ldr	r5, [r1, #0]
101078f8:	42ac      	cmp	r4, r5
101078fa:	d11f      	bne.n	1010793c <_strncmp+0x5c>
101078fc:	3a04      	subs	r2, #4
101078fe:	d035      	beq.n	1010796c <_strncmp+0x8c>
10107900:	f1a4 3501 	sub.w	r5, r4, #16843009	; 0x1010101
10107904:	ea25 0404 	bic.w	r4, r5, r4
10107908:	f014 3f80 	tst.w	r4, #2155905152	; 0x80808080
1010790c:	d131      	bne.n	10107972 <_strncmp+0x92>
1010790e:	1d07      	adds	r7, r0, #4
10107910:	1d0d      	adds	r5, r1, #4
10107912:	e00d      	b.n	10107930 <_strncmp+0x50>
10107914:	f857 3b04 	ldr.w	r3, [r7], #4
10107918:	680e      	ldr	r6, [r1, #0]
1010791a:	f1a3 3401 	sub.w	r4, r3, #16843009	; 0x1010101
1010791e:	42b3      	cmp	r3, r6
10107920:	ea24 0403 	bic.w	r4, r4, r3
10107924:	d10a      	bne.n	1010793c <_strncmp+0x5c>
10107926:	3a04      	subs	r2, #4
10107928:	d020      	beq.n	1010796c <_strncmp+0x8c>
1010792a:	f014 3f80 	tst.w	r4, #2155905152	; 0x80808080
1010792e:	d123      	bne.n	10107978 <_strncmp+0x98>
10107930:	2a03      	cmp	r2, #3
10107932:	4629      	mov	r1, r5
10107934:	4638      	mov	r0, r7
10107936:	f105 0504 	add.w	r5, r5, #4
1010793a:	d8eb      	bhi.n	10107914 <_strncmp+0x34>
1010793c:	7805      	ldrb	r5, [r0, #0]
1010793e:	780c      	ldrb	r4, [r1, #0]
10107940:	42ac      	cmp	r4, r5
10107942:	f102 33ff 	add.w	r3, r2, #4294967295
10107946:	d119      	bne.n	1010797c <_strncmp+0x9c>
10107948:	b19b      	cbz	r3, 10107972 <_strncmp+0x92>
1010794a:	b914      	cbnz	r4, 10107952 <_strncmp+0x72>
1010794c:	e018      	b.n	10107980 <_strncmp+0xa0>
1010794e:	b183      	cbz	r3, 10107972 <_strncmp+0x92>
10107950:	b162      	cbz	r2, 1010796c <_strncmp+0x8c>
10107952:	f810 2f01 	ldrb.w	r2, [r0, #1]!
10107956:	f811 4f01 	ldrb.w	r4, [r1, #1]!
1010795a:	42a2      	cmp	r2, r4
1010795c:	f103 33ff 	add.w	r3, r3, #4294967295
10107960:	d0f5      	beq.n	1010794e <_strncmp+0x6e>
10107962:	1b10      	subs	r0, r2, r4
10107964:	bcf0      	pop	{r4, r5, r6, r7}
10107966:	4770      	bx	lr
10107968:	4610      	mov	r0, r2
1010796a:	4770      	bx	lr
1010796c:	4610      	mov	r0, r2
1010796e:	bcf0      	pop	{r4, r5, r6, r7}
10107970:	4770      	bx	lr
10107972:	4618      	mov	r0, r3
10107974:	bcf0      	pop	{r4, r5, r6, r7}
10107976:	4770      	bx	lr
10107978:	2000      	movs	r0, #0
1010797a:	e7f3      	b.n	10107964 <_strncmp+0x84>
1010797c:	462a      	mov	r2, r5
1010797e:	e7f0      	b.n	10107962 <_strncmp+0x82>
10107980:	4620      	mov	r0, r4
10107982:	e7ef      	b.n	10107964 <_strncmp+0x84>

10107984 <_strncpy>:
10107984:	ea40 0301 	orr.w	r3, r0, r1
10107988:	079b      	lsls	r3, r3, #30
1010798a:	b470      	push	{r4, r5, r6}
1010798c:	d12b      	bne.n	101079e6 <_strncpy+0x62>
1010798e:	2a03      	cmp	r2, #3
10107990:	d929      	bls.n	101079e6 <_strncpy+0x62>
10107992:	460c      	mov	r4, r1
10107994:	4603      	mov	r3, r0
10107996:	4621      	mov	r1, r4
10107998:	f854 6b04 	ldr.w	r6, [r4], #4
1010799c:	f1a6 3501 	sub.w	r5, r6, #16843009	; 0x1010101
101079a0:	ea25 0506 	bic.w	r5, r5, r6
101079a4:	f015 3f80 	tst.w	r5, #2155905152	; 0x80808080
101079a8:	d106      	bne.n	101079b8 <_strncpy+0x34>
101079aa:	3a04      	subs	r2, #4
101079ac:	2a03      	cmp	r2, #3
101079ae:	f843 6b04 	str.w	r6, [r3], #4
101079b2:	4621      	mov	r1, r4
101079b4:	d8ef      	bhi.n	10107996 <_strncpy+0x12>
101079b6:	b1a2      	cbz	r2, 101079e2 <_strncpy+0x5e>
101079b8:	780c      	ldrb	r4, [r1, #0]
101079ba:	3a01      	subs	r2, #1
101079bc:	701c      	strb	r4, [r3, #0]
101079be:	3101      	adds	r1, #1
101079c0:	3301      	adds	r3, #1
101079c2:	b13c      	cbz	r4, 101079d4 <_strncpy+0x50>
101079c4:	b16a      	cbz	r2, 101079e2 <_strncpy+0x5e>
101079c6:	f811 4b01 	ldrb.w	r4, [r1], #1
101079ca:	3a01      	subs	r2, #1
101079cc:	f803 4b01 	strb.w	r4, [r3], #1
101079d0:	2c00      	cmp	r4, #0
101079d2:	d1f7      	bne.n	101079c4 <_strncpy+0x40>
101079d4:	b12a      	cbz	r2, 101079e2 <_strncpy+0x5e>
101079d6:	2100      	movs	r1, #0
101079d8:	441a      	add	r2, r3
101079da:	f803 1b01 	strb.w	r1, [r3], #1
101079de:	429a      	cmp	r2, r3
101079e0:	d1fb      	bne.n	101079da <_strncpy+0x56>
101079e2:	bc70      	pop	{r4, r5, r6}
101079e4:	4770      	bx	lr
101079e6:	4603      	mov	r3, r0
101079e8:	e7e5      	b.n	101079b6 <_strncpy+0x32>
101079ea:	bf00      	nop

101079ec <_strnlen>:
101079ec:	b199      	cbz	r1, 10107a16 <_strnlen+0x2a>
101079ee:	7803      	ldrb	r3, [r0, #0]
101079f0:	b19b      	cbz	r3, 10107a1a <_strnlen+0x2e>
101079f2:	b410      	push	{r4}
101079f4:	4401      	add	r1, r0
101079f6:	1c43      	adds	r3, r0, #1
101079f8:	e003      	b.n	10107a02 <_strnlen+0x16>
101079fa:	781a      	ldrb	r2, [r3, #0]
101079fc:	1c5c      	adds	r4, r3, #1
101079fe:	b132      	cbz	r2, 10107a0e <_strnlen+0x22>
10107a00:	4623      	mov	r3, r4
10107a02:	4299      	cmp	r1, r3
10107a04:	d1f9      	bne.n	101079fa <_strnlen+0xe>
10107a06:	1a08      	subs	r0, r1, r0
10107a08:	f85d 4b04 	ldr.w	r4, [sp], #4
10107a0c:	4770      	bx	lr
10107a0e:	1a18      	subs	r0, r3, r0
10107a10:	f85d 4b04 	ldr.w	r4, [sp], #4
10107a14:	4770      	bx	lr
10107a16:	4608      	mov	r0, r1
10107a18:	4770      	bx	lr
10107a1a:	4618      	mov	r0, r3
10107a1c:	4770      	bx	lr
10107a1e:	bf00      	nop

10107a20 <_strpbrk>:
10107a20:	b430      	push	{r4, r5}
10107a22:	7804      	ldrb	r4, [r0, #0]
10107a24:	b17c      	cbz	r4, 10107a46 <_strpbrk+0x26>
10107a26:	780d      	ldrb	r5, [r1, #0]
10107a28:	b14d      	cbz	r5, 10107a3e <_strpbrk+0x1e>
10107a2a:	42a5      	cmp	r5, r4
10107a2c:	d00c      	beq.n	10107a48 <_strpbrk+0x28>
10107a2e:	460a      	mov	r2, r1
10107a30:	e001      	b.n	10107a36 <_strpbrk+0x16>
10107a32:	42a3      	cmp	r3, r4
10107a34:	d008      	beq.n	10107a48 <_strpbrk+0x28>
10107a36:	f812 3f01 	ldrb.w	r3, [r2, #1]!
10107a3a:	2b00      	cmp	r3, #0
10107a3c:	d1f9      	bne.n	10107a32 <_strpbrk+0x12>
10107a3e:	f810 4f01 	ldrb.w	r4, [r0, #1]!
10107a42:	2c00      	cmp	r4, #0
10107a44:	d1f0      	bne.n	10107a28 <_strpbrk+0x8>
10107a46:	4620      	mov	r0, r4
10107a48:	bc30      	pop	{r4, r5}
10107a4a:	4770      	bx	lr

10107a4c <_strsep>:
10107a4c:	4602      	mov	r2, r0
10107a4e:	2300      	movs	r3, #0
10107a50:	6800      	ldr	r0, [r0, #0]
10107a52:	f000 badd 	b.w	10108010 <__strtok_r>
10107a56:	bf00      	nop

10107a58 <__rtl_critical_factorization>:
10107a58:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
10107a5c:	f04f 0e01 	mov.w	lr, #1
10107a60:	2500      	movs	r5, #0
10107a62:	4674      	mov	r4, lr
10107a64:	f04f 36ff 	mov.w	r6, #4294967295
10107a68:	192b      	adds	r3, r5, r4
10107a6a:	428b      	cmp	r3, r1
10107a6c:	eb00 0706 	add.w	r7, r0, r6
10107a70:	d20d      	bcs.n	10107a8e <__rtl_critical_factorization+0x36>
10107a72:	5d3f      	ldrb	r7, [r7, r4]
10107a74:	f810 c003 	ldrb.w	ip, [r0, r3]
10107a78:	45bc      	cmp	ip, r7
10107a7a:	d22d      	bcs.n	10107ad8 <__rtl_critical_factorization+0x80>
10107a7c:	461d      	mov	r5, r3
10107a7e:	2401      	movs	r4, #1
10107a80:	eba3 0e06 	sub.w	lr, r3, r6
10107a84:	192b      	adds	r3, r5, r4
10107a86:	428b      	cmp	r3, r1
10107a88:	eb00 0706 	add.w	r7, r0, r6
10107a8c:	d3f1      	bcc.n	10107a72 <__rtl_critical_factorization+0x1a>
10107a8e:	f04f 0801 	mov.w	r8, #1
10107a92:	2500      	movs	r5, #0
10107a94:	4644      	mov	r4, r8
10107a96:	f04f 37ff 	mov.w	r7, #4294967295
10107a9a:	f8c2 e000 	str.w	lr, [r2]
10107a9e:	192b      	adds	r3, r5, r4
10107aa0:	4299      	cmp	r1, r3
10107aa2:	eb00 0e07 	add.w	lr, r0, r7
10107aa6:	d90e      	bls.n	10107ac6 <__rtl_critical_factorization+0x6e>
10107aa8:	f81e e004 	ldrb.w	lr, [lr, r4]
10107aac:	f810 c003 	ldrb.w	ip, [r0, r3]
10107ab0:	45f4      	cmp	ip, lr
10107ab2:	d918      	bls.n	10107ae6 <__rtl_critical_factorization+0x8e>
10107ab4:	461d      	mov	r5, r3
10107ab6:	2401      	movs	r4, #1
10107ab8:	eba3 0807 	sub.w	r8, r3, r7
10107abc:	192b      	adds	r3, r5, r4
10107abe:	4299      	cmp	r1, r3
10107ac0:	eb00 0e07 	add.w	lr, r0, r7
10107ac4:	d8f0      	bhi.n	10107aa8 <__rtl_critical_factorization+0x50>
10107ac6:	3701      	adds	r7, #1
10107ac8:	1c70      	adds	r0, r6, #1
10107aca:	4287      	cmp	r7, r0
10107acc:	bf24      	itt	cs
10107ace:	4638      	movcs	r0, r7
10107ad0:	f8c2 8000 	strcs.w	r8, [r2]
10107ad4:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
10107ad8:	d00c      	beq.n	10107af4 <__rtl_critical_factorization+0x9c>
10107ada:	f04f 0e01 	mov.w	lr, #1
10107ade:	462e      	mov	r6, r5
10107ae0:	4674      	mov	r4, lr
10107ae2:	4475      	add	r5, lr
10107ae4:	e7c0      	b.n	10107a68 <__rtl_critical_factorization+0x10>
10107ae6:	d00c      	beq.n	10107b02 <__rtl_critical_factorization+0xaa>
10107ae8:	f04f 0801 	mov.w	r8, #1
10107aec:	462f      	mov	r7, r5
10107aee:	4644      	mov	r4, r8
10107af0:	4445      	add	r5, r8
10107af2:	e7d4      	b.n	10107a9e <__rtl_critical_factorization+0x46>
10107af4:	4574      	cmp	r4, lr
10107af6:	bf09      	itett	eq
10107af8:	46a6      	moveq	lr, r4
10107afa:	3401      	addne	r4, #1
10107afc:	461d      	moveq	r5, r3
10107afe:	2401      	moveq	r4, #1
10107b00:	e7b2      	b.n	10107a68 <__rtl_critical_factorization+0x10>
10107b02:	4544      	cmp	r4, r8
10107b04:	bf09      	itett	eq
10107b06:	46a0      	moveq	r8, r4
10107b08:	3401      	addne	r4, #1
10107b0a:	461d      	moveq	r5, r3
10107b0c:	2401      	moveq	r4, #1
10107b0e:	e7c6      	b.n	10107a9e <__rtl_critical_factorization+0x46>

10107b10 <__rtl_two_way_long_needle>:
10107b10:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10107b14:	f2ad 4d14 	subw	sp, sp, #1044	; 0x414
10107b18:	4616      	mov	r6, r2
10107b1a:	4605      	mov	r5, r0
10107b1c:	468b      	mov	fp, r1
10107b1e:	4610      	mov	r0, r2
10107b20:	4619      	mov	r1, r3
10107b22:	aa03      	add	r2, sp, #12
10107b24:	461c      	mov	r4, r3
10107b26:	f7ff ff97 	bl	10107a58 <__rtl_critical_factorization>
10107b2a:	4681      	mov	r9, r0
10107b2c:	ab03      	add	r3, sp, #12
10107b2e:	f20d 420c 	addw	r2, sp, #1036	; 0x40c
10107b32:	f843 4f04 	str.w	r4, [r3, #4]!
10107b36:	4293      	cmp	r3, r2
10107b38:	d1fb      	bne.n	10107b32 <__rtl_two_way_long_needle+0x22>
10107b3a:	b14c      	cbz	r4, 10107b50 <__rtl_two_way_long_needle+0x40>
10107b3c:	1e63      	subs	r3, r4, #1
10107b3e:	1e72      	subs	r2, r6, #1
10107b40:	a804      	add	r0, sp, #16
10107b42:	f812 1f01 	ldrb.w	r1, [r2, #1]!
10107b46:	f840 3021 	str.w	r3, [r0, r1, lsl #2]
10107b4a:	f113 33ff 	adds.w	r3, r3, #4294967295
10107b4e:	d2f8      	bcs.n	10107b42 <__rtl_two_way_long_needle+0x32>
10107b50:	9903      	ldr	r1, [sp, #12]
10107b52:	464a      	mov	r2, r9
10107b54:	4431      	add	r1, r6
10107b56:	4630      	mov	r0, r6
10107b58:	f7ff f8aa 	bl	10106cb0 <_memcmp>
10107b5c:	2800      	cmp	r0, #0
10107b5e:	d16f      	bne.n	10107c40 <__rtl_two_way_long_needle+0x130>
10107b60:	f109 33ff 	add.w	r3, r9, #4294967295
10107b64:	9300      	str	r3, [sp, #0]
10107b66:	18f3      	adds	r3, r6, r3
10107b68:	4682      	mov	sl, r0
10107b6a:	9301      	str	r3, [sp, #4]
10107b6c:	4623      	mov	r3, r4
10107b6e:	4680      	mov	r8, r0
10107b70:	4654      	mov	r4, sl
10107b72:	4658      	mov	r0, fp
10107b74:	469a      	mov	sl, r3
10107b76:	eb08 070a 	add.w	r7, r8, sl
10107b7a:	1a3a      	subs	r2, r7, r0
10107b7c:	2100      	movs	r1, #0
10107b7e:	4428      	add	r0, r5
10107b80:	f7ff f84e 	bl	10106c20 <_memchr>
10107b84:	2800      	cmp	r0, #0
10107b86:	d156      	bne.n	10107c36 <__rtl_two_way_long_needle+0x126>
10107b88:	2f00      	cmp	r7, #0
10107b8a:	d054      	beq.n	10107c36 <__rtl_two_way_long_needle+0x126>
10107b8c:	19eb      	adds	r3, r5, r7
10107b8e:	f813 2c01 	ldrb.w	r2, [r3, #-1]
10107b92:	ab04      	add	r3, sp, #16
10107b94:	f853 3022 	ldr.w	r3, [r3, r2, lsl #2]
10107b98:	b14b      	cbz	r3, 10107bae <__rtl_two_way_long_needle+0x9e>
10107b9a:	b124      	cbz	r4, 10107ba6 <__rtl_two_way_long_needle+0x96>
10107b9c:	9a03      	ldr	r2, [sp, #12]
10107b9e:	4293      	cmp	r3, r2
10107ba0:	d201      	bcs.n	10107ba6 <__rtl_two_way_long_needle+0x96>
10107ba2:	ebaa 0302 	sub.w	r3, sl, r2
10107ba6:	4498      	add	r8, r3
10107ba8:	2400      	movs	r4, #0
10107baa:	4638      	mov	r0, r7
10107bac:	e7e3      	b.n	10107b76 <__rtl_two_way_long_needle+0x66>
10107bae:	454c      	cmp	r4, r9
10107bb0:	4623      	mov	r3, r4
10107bb2:	bf38      	it	cc
10107bb4:	464b      	movcc	r3, r9
10107bb6:	f10a 3eff 	add.w	lr, sl, #4294967295
10107bba:	4573      	cmp	r3, lr
10107bbc:	d213      	bcs.n	10107be6 <__rtl_two_way_long_needle+0xd6>
10107bbe:	eb08 0203 	add.w	r2, r8, r3
10107bc2:	5ca8      	ldrb	r0, [r5, r2]
10107bc4:	f816 c003 	ldrb.w	ip, [r6, r3]
10107bc8:	4584      	cmp	ip, r0
10107bca:	442a      	add	r2, r5
10107bcc:	eb06 0103 	add.w	r1, r6, r3
10107bd0:	d006      	beq.n	10107be0 <__rtl_two_way_long_needle+0xd0>
10107bd2:	e02c      	b.n	10107c2e <__rtl_two_way_long_needle+0x11e>
10107bd4:	f811 cf01 	ldrb.w	ip, [r1, #1]!
10107bd8:	f812 0f01 	ldrb.w	r0, [r2, #1]!
10107bdc:	4584      	cmp	ip, r0
10107bde:	d126      	bne.n	10107c2e <__rtl_two_way_long_needle+0x11e>
10107be0:	3301      	adds	r3, #1
10107be2:	4573      	cmp	r3, lr
10107be4:	d3f6      	bcc.n	10107bd4 <__rtl_two_way_long_needle+0xc4>
10107be6:	454c      	cmp	r4, r9
10107be8:	9900      	ldr	r1, [sp, #0]
10107bea:	f080 8089 	bcs.w	10107d00 <__rtl_two_way_long_needle+0x1f0>
10107bee:	9b00      	ldr	r3, [sp, #0]
10107bf0:	9801      	ldr	r0, [sp, #4]
10107bf2:	eb08 0203 	add.w	r2, r8, r3
10107bf6:	5cab      	ldrb	r3, [r5, r2]
10107bf8:	7800      	ldrb	r0, [r0, #0]
10107bfa:	4298      	cmp	r0, r3
10107bfc:	442a      	add	r2, r5
10107bfe:	d17f      	bne.n	10107d00 <__rtl_two_way_long_needle+0x1f0>
10107c00:	9801      	ldr	r0, [sp, #4]
10107c02:	f104 3bff 	add.w	fp, r4, #4294967295
10107c06:	e006      	b.n	10107c16 <__rtl_two_way_long_needle+0x106>
10107c08:	f810 cd01 	ldrb.w	ip, [r0, #-1]!
10107c0c:	f812 ed01 	ldrb.w	lr, [r2, #-1]!
10107c10:	45f4      	cmp	ip, lr
10107c12:	d103      	bne.n	10107c1c <__rtl_two_way_long_needle+0x10c>
10107c14:	4619      	mov	r1, r3
10107c16:	1e4b      	subs	r3, r1, #1
10107c18:	459b      	cmp	fp, r3
10107c1a:	d1f5      	bne.n	10107c08 <__rtl_two_way_long_needle+0xf8>
10107c1c:	3401      	adds	r4, #1
10107c1e:	428c      	cmp	r4, r1
10107c20:	d870      	bhi.n	10107d04 <__rtl_two_way_long_needle+0x1f4>
10107c22:	9c03      	ldr	r4, [sp, #12]
10107c24:	4638      	mov	r0, r7
10107c26:	44a0      	add	r8, r4
10107c28:	ebaa 0404 	sub.w	r4, sl, r4
10107c2c:	e7a3      	b.n	10107b76 <__rtl_two_way_long_needle+0x66>
10107c2e:	f1c9 0201 	rsb	r2, r9, #1
10107c32:	4490      	add	r8, r2
10107c34:	e7b7      	b.n	10107ba6 <__rtl_two_way_long_needle+0x96>
10107c36:	2000      	movs	r0, #0
10107c38:	f20d 4d14 	addw	sp, sp, #1044	; 0x414
10107c3c:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10107c40:	eba4 0309 	sub.w	r3, r4, r9
10107c44:	454b      	cmp	r3, r9
10107c46:	bf38      	it	cc
10107c48:	464b      	movcc	r3, r9
10107c4a:	f109 38ff 	add.w	r8, r9, #4294967295
10107c4e:	3301      	adds	r3, #1
10107c50:	9303      	str	r3, [sp, #12]
10107c52:	eb06 0308 	add.w	r3, r6, r8
10107c56:	4658      	mov	r0, fp
10107c58:	f04f 0a00 	mov.w	sl, #0
10107c5c:	46cb      	mov	fp, r9
10107c5e:	4699      	mov	r9, r3
10107c60:	eb0a 0704 	add.w	r7, sl, r4
10107c64:	1a3a      	subs	r2, r7, r0
10107c66:	2100      	movs	r1, #0
10107c68:	4428      	add	r0, r5
10107c6a:	f7fe ffd9 	bl	10106c20 <_memchr>
10107c6e:	2800      	cmp	r0, #0
10107c70:	d1e1      	bne.n	10107c36 <__rtl_two_way_long_needle+0x126>
10107c72:	2f00      	cmp	r7, #0
10107c74:	d0df      	beq.n	10107c36 <__rtl_two_way_long_needle+0x126>
10107c76:	19eb      	adds	r3, r5, r7
10107c78:	f813 2c01 	ldrb.w	r2, [r3, #-1]
10107c7c:	ab04      	add	r3, sp, #16
10107c7e:	f853 3022 	ldr.w	r3, [r3, r2, lsl #2]
10107c82:	bba3      	cbnz	r3, 10107cee <__rtl_two_way_long_needle+0x1de>
10107c84:	1e60      	subs	r0, r4, #1
10107c86:	4583      	cmp	fp, r0
10107c88:	d215      	bcs.n	10107cb6 <__rtl_two_way_long_needle+0x1a6>
10107c8a:	eb0a 020b 	add.w	r2, sl, fp
10107c8e:	f815 e002 	ldrb.w	lr, [r5, r2]
10107c92:	f816 300b 	ldrb.w	r3, [r6, fp]
10107c96:	459e      	cmp	lr, r3
10107c98:	442a      	add	r2, r5
10107c9a:	eb06 010b 	add.w	r1, r6, fp
10107c9e:	465b      	mov	r3, fp
10107ca0:	d006      	beq.n	10107cb0 <__rtl_two_way_long_needle+0x1a0>
10107ca2:	e027      	b.n	10107cf4 <__rtl_two_way_long_needle+0x1e4>
10107ca4:	f811 cf01 	ldrb.w	ip, [r1, #1]!
10107ca8:	f812 ef01 	ldrb.w	lr, [r2, #1]!
10107cac:	45f4      	cmp	ip, lr
10107cae:	d121      	bne.n	10107cf4 <__rtl_two_way_long_needle+0x1e4>
10107cb0:	3301      	adds	r3, #1
10107cb2:	4283      	cmp	r3, r0
10107cb4:	d3f6      	bcc.n	10107ca4 <__rtl_two_way_long_needle+0x194>
10107cb6:	f1b8 3fff 	cmp.w	r8, #4294967295
10107cba:	d011      	beq.n	10107ce0 <__rtl_two_way_long_needle+0x1d0>
10107cbc:	eb0a 0208 	add.w	r2, sl, r8
10107cc0:	5cab      	ldrb	r3, [r5, r2]
10107cc2:	f899 1000 	ldrb.w	r1, [r9]
10107cc6:	4299      	cmp	r1, r3
10107cc8:	442a      	add	r2, r5
10107cca:	d10f      	bne.n	10107cec <__rtl_two_way_long_needle+0x1dc>
10107ccc:	464b      	mov	r3, r9
10107cce:	e005      	b.n	10107cdc <__rtl_two_way_long_needle+0x1cc>
10107cd0:	f813 0d01 	ldrb.w	r0, [r3, #-1]!
10107cd4:	f812 1d01 	ldrb.w	r1, [r2, #-1]!
10107cd8:	4288      	cmp	r0, r1
10107cda:	d107      	bne.n	10107cec <__rtl_two_way_long_needle+0x1dc>
10107cdc:	42b3      	cmp	r3, r6
10107cde:	d1f7      	bne.n	10107cd0 <__rtl_two_way_long_needle+0x1c0>
10107ce0:	eb05 000a 	add.w	r0, r5, sl
10107ce4:	f20d 4d14 	addw	sp, sp, #1044	; 0x414
10107ce8:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10107cec:	9b03      	ldr	r3, [sp, #12]
10107cee:	449a      	add	sl, r3
10107cf0:	4638      	mov	r0, r7
10107cf2:	e7b5      	b.n	10107c60 <__rtl_two_way_long_needle+0x150>
10107cf4:	f1cb 0201 	rsb	r2, fp, #1
10107cf8:	4492      	add	sl, r2
10107cfa:	449a      	add	sl, r3
10107cfc:	4638      	mov	r0, r7
10107cfe:	e7af      	b.n	10107c60 <__rtl_two_way_long_needle+0x150>
10107d00:	4649      	mov	r1, r9
10107d02:	e78b      	b.n	10107c1c <__rtl_two_way_long_needle+0x10c>
10107d04:	eb05 0008 	add.w	r0, r5, r8
10107d08:	e796      	b.n	10107c38 <__rtl_two_way_long_needle+0x128>
10107d0a:	bf00      	nop

10107d0c <_strstr>:
10107d0c:	7802      	ldrb	r2, [r0, #0]
10107d0e:	2a00      	cmp	r2, #0
10107d10:	f000 8101 	beq.w	10107f16 <_strstr+0x20a>
10107d14:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
10107d18:	f891 8000 	ldrb.w	r8, [r1]
10107d1c:	b085      	sub	sp, #20
10107d1e:	4644      	mov	r4, r8
10107d20:	f1b8 0f00 	cmp.w	r8, #0
10107d24:	d016      	beq.n	10107d54 <_strstr+0x48>
10107d26:	4686      	mov	lr, r0
10107d28:	f101 0c01 	add.w	ip, r1, #1
10107d2c:	2701      	movs	r7, #1
10107d2e:	e004      	b.n	10107d3a <_strstr+0x2e>
10107d30:	4663      	mov	r3, ip
10107d32:	f813 4b01 	ldrb.w	r4, [r3], #1
10107d36:	b164      	cbz	r4, 10107d52 <_strstr+0x46>
10107d38:	469c      	mov	ip, r3
10107d3a:	42a2      	cmp	r2, r4
10107d3c:	bf14      	ite	ne
10107d3e:	2700      	movne	r7, #0
10107d40:	f007 0701 	andeq.w	r7, r7, #1
10107d44:	f81e 2f01 	ldrb.w	r2, [lr, #1]!
10107d48:	2a00      	cmp	r2, #0
10107d4a:	d1f1      	bne.n	10107d30 <_strstr+0x24>
10107d4c:	f89c 3000 	ldrb.w	r3, [ip]
10107d50:	b9fb      	cbnz	r3, 10107d92 <_strstr+0x86>
10107d52:	b117      	cbz	r7, 10107d5a <_strstr+0x4e>
10107d54:	b005      	add	sp, #20
10107d56:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10107d5a:	460e      	mov	r6, r1
10107d5c:	4605      	mov	r5, r0
10107d5e:	4641      	mov	r1, r8
10107d60:	3001      	adds	r0, #1
10107d62:	ebac 0406 	sub.w	r4, ip, r6
10107d66:	f7ff fc79 	bl	1010765c <_strchr>
10107d6a:	4607      	mov	r7, r0
10107d6c:	b188      	cbz	r0, 10107d92 <_strstr+0x86>
10107d6e:	2c01      	cmp	r4, #1
10107d70:	d0f0      	beq.n	10107d54 <_strstr+0x48>
10107d72:	1928      	adds	r0, r5, r4
10107d74:	4287      	cmp	r7, r0
10107d76:	bf8c      	ite	hi
10107d78:	2101      	movhi	r1, #1
10107d7a:	1bc1      	subls	r1, r0, r7
10107d7c:	2c1f      	cmp	r4, #31
10107d7e:	468b      	mov	fp, r1
10107d80:	d90b      	bls.n	10107d9a <_strstr+0x8e>
10107d82:	4623      	mov	r3, r4
10107d84:	4632      	mov	r2, r6
10107d86:	4638      	mov	r0, r7
10107d88:	f7ff fec2 	bl	10107b10 <__rtl_two_way_long_needle>
10107d8c:	b005      	add	sp, #20
10107d8e:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10107d92:	2000      	movs	r0, #0
10107d94:	b005      	add	sp, #20
10107d96:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10107d9a:	aa03      	add	r2, sp, #12
10107d9c:	4621      	mov	r1, r4
10107d9e:	4630      	mov	r0, r6
10107da0:	f7ff fe5a 	bl	10107a58 <__rtl_critical_factorization>
10107da4:	9903      	ldr	r1, [sp, #12]
10107da6:	4680      	mov	r8, r0
10107da8:	4602      	mov	r2, r0
10107daa:	4431      	add	r1, r6
10107dac:	4630      	mov	r0, r6
10107dae:	f7fe ff7f 	bl	10106cb0 <_memcmp>
10107db2:	2800      	cmp	r0, #0
10107db4:	d157      	bne.n	10107e66 <_strstr+0x15a>
10107db6:	4681      	mov	r9, r0
10107db8:	4605      	mov	r5, r0
10107dba:	46b2      	mov	sl, r6
10107dbc:	4658      	mov	r0, fp
10107dbe:	f108 33ff 	add.w	r3, r8, #4294967295
10107dc2:	9301      	str	r3, [sp, #4]
10107dc4:	18f3      	adds	r3, r6, r3
10107dc6:	9300      	str	r3, [sp, #0]
10107dc8:	1966      	adds	r6, r4, r5
10107dca:	1a32      	subs	r2, r6, r0
10107dcc:	2100      	movs	r1, #0
10107dce:	4438      	add	r0, r7
10107dd0:	f7fe ff26 	bl	10106c20 <_memchr>
10107dd4:	2800      	cmp	r0, #0
10107dd6:	d1dc      	bne.n	10107d92 <_strstr+0x86>
10107dd8:	2e00      	cmp	r6, #0
10107dda:	d0da      	beq.n	10107d92 <_strstr+0x86>
10107ddc:	45c8      	cmp	r8, r9
10107dde:	4643      	mov	r3, r8
10107de0:	bf38      	it	cc
10107de2:	464b      	movcc	r3, r9
10107de4:	429c      	cmp	r4, r3
10107de6:	d912      	bls.n	10107e0e <_strstr+0x102>
10107de8:	195a      	adds	r2, r3, r5
10107dea:	5cb8      	ldrb	r0, [r7, r2]
10107dec:	f81a 1003 	ldrb.w	r1, [sl, r3]
10107df0:	4288      	cmp	r0, r1
10107df2:	443a      	add	r2, r7
10107df4:	eb0a 0e03 	add.w	lr, sl, r3
10107df8:	d006      	beq.n	10107e08 <_strstr+0xfc>
10107dfa:	e02c      	b.n	10107e56 <_strstr+0x14a>
10107dfc:	f81e 0f01 	ldrb.w	r0, [lr, #1]!
10107e00:	f812 1f01 	ldrb.w	r1, [r2, #1]!
10107e04:	4288      	cmp	r0, r1
10107e06:	d126      	bne.n	10107e56 <_strstr+0x14a>
10107e08:	3301      	adds	r3, #1
10107e0a:	429c      	cmp	r4, r3
10107e0c:	d1f6      	bne.n	10107dfc <_strstr+0xf0>
10107e0e:	9b01      	ldr	r3, [sp, #4]
10107e10:	45c8      	cmp	r8, r9
10107e12:	4619      	mov	r1, r3
10107e14:	f240 8082 	bls.w	10107f1c <_strstr+0x210>
10107e18:	9800      	ldr	r0, [sp, #0]
10107e1a:	18ea      	adds	r2, r5, r3
10107e1c:	5cbb      	ldrb	r3, [r7, r2]
10107e1e:	7800      	ldrb	r0, [r0, #0]
10107e20:	4298      	cmp	r0, r3
10107e22:	443a      	add	r2, r7
10107e24:	d17a      	bne.n	10107f1c <_strstr+0x210>
10107e26:	9800      	ldr	r0, [sp, #0]
10107e28:	f109 3bff 	add.w	fp, r9, #4294967295
10107e2c:	e006      	b.n	10107e3c <_strstr+0x130>
10107e2e:	f810 cd01 	ldrb.w	ip, [r0, #-1]!
10107e32:	f812 ed01 	ldrb.w	lr, [r2, #-1]!
10107e36:	45f4      	cmp	ip, lr
10107e38:	d103      	bne.n	10107e42 <_strstr+0x136>
10107e3a:	4619      	mov	r1, r3
10107e3c:	1e4b      	subs	r3, r1, #1
10107e3e:	455b      	cmp	r3, fp
10107e40:	d1f5      	bne.n	10107e2e <_strstr+0x122>
10107e42:	f109 0901 	add.w	r9, r9, #1
10107e46:	4589      	cmp	r9, r1
10107e48:	d857      	bhi.n	10107efa <_strstr+0x1ee>
10107e4a:	9b03      	ldr	r3, [sp, #12]
10107e4c:	4630      	mov	r0, r6
10107e4e:	441d      	add	r5, r3
10107e50:	eba4 0903 	sub.w	r9, r4, r3
10107e54:	e7b8      	b.n	10107dc8 <_strstr+0xbc>
10107e56:	f1c8 0201 	rsb	r2, r8, #1
10107e5a:	4415      	add	r5, r2
10107e5c:	441d      	add	r5, r3
10107e5e:	f04f 0900 	mov.w	r9, #0
10107e62:	4630      	mov	r0, r6
10107e64:	e7b0      	b.n	10107dc8 <_strstr+0xbc>
10107e66:	eba4 0308 	sub.w	r3, r4, r8
10107e6a:	4543      	cmp	r3, r8
10107e6c:	bf38      	it	cc
10107e6e:	4643      	movcc	r3, r8
10107e70:	f108 39ff 	add.w	r9, r8, #4294967295
10107e74:	3301      	adds	r3, #1
10107e76:	9303      	str	r3, [sp, #12]
10107e78:	eb06 0309 	add.w	r3, r6, r9
10107e7c:	4658      	mov	r0, fp
10107e7e:	2500      	movs	r5, #0
10107e80:	46bb      	mov	fp, r7
10107e82:	469a      	mov	sl, r3
10107e84:	1967      	adds	r7, r4, r5
10107e86:	1a3a      	subs	r2, r7, r0
10107e88:	2100      	movs	r1, #0
10107e8a:	4458      	add	r0, fp
10107e8c:	f7fe fec8 	bl	10106c20 <_memchr>
10107e90:	2800      	cmp	r0, #0
10107e92:	f47f af7e 	bne.w	10107d92 <_strstr+0x86>
10107e96:	2f00      	cmp	r7, #0
10107e98:	f43f af7b 	beq.w	10107d92 <_strstr+0x86>
10107e9c:	4544      	cmp	r4, r8
10107e9e:	d915      	bls.n	10107ecc <_strstr+0x1c0>
10107ea0:	eb08 0205 	add.w	r2, r8, r5
10107ea4:	f81b 0002 	ldrb.w	r0, [fp, r2]
10107ea8:	f816 3008 	ldrb.w	r3, [r6, r8]
10107eac:	4298      	cmp	r0, r3
10107eae:	445a      	add	r2, fp
10107eb0:	eb06 0108 	add.w	r1, r6, r8
10107eb4:	4643      	mov	r3, r8
10107eb6:	d006      	beq.n	10107ec6 <_strstr+0x1ba>
10107eb8:	e023      	b.n	10107f02 <_strstr+0x1f6>
10107eba:	f811 ef01 	ldrb.w	lr, [r1, #1]!
10107ebe:	f812 0f01 	ldrb.w	r0, [r2, #1]!
10107ec2:	4586      	cmp	lr, r0
10107ec4:	d11d      	bne.n	10107f02 <_strstr+0x1f6>
10107ec6:	3301      	adds	r3, #1
10107ec8:	429c      	cmp	r4, r3
10107eca:	d1f6      	bne.n	10107eba <_strstr+0x1ae>
10107ecc:	f1b9 3fff 	cmp.w	r9, #4294967295
10107ed0:	d012      	beq.n	10107ef8 <_strstr+0x1ec>
10107ed2:	eb05 0209 	add.w	r2, r5, r9
10107ed6:	f81b 1002 	ldrb.w	r1, [fp, r2]
10107eda:	f89a 3000 	ldrb.w	r3, [sl]
10107ede:	4299      	cmp	r1, r3
10107ee0:	445a      	add	r2, fp
10107ee2:	d114      	bne.n	10107f0e <_strstr+0x202>
10107ee4:	4653      	mov	r3, sl
10107ee6:	e005      	b.n	10107ef4 <_strstr+0x1e8>
10107ee8:	f813 0d01 	ldrb.w	r0, [r3, #-1]!
10107eec:	f812 1d01 	ldrb.w	r1, [r2, #-1]!
10107ef0:	4288      	cmp	r0, r1
10107ef2:	d10c      	bne.n	10107f0e <_strstr+0x202>
10107ef4:	42b3      	cmp	r3, r6
10107ef6:	d1f7      	bne.n	10107ee8 <_strstr+0x1dc>
10107ef8:	465f      	mov	r7, fp
10107efa:	1978      	adds	r0, r7, r5
10107efc:	b005      	add	sp, #20
10107efe:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
10107f02:	f1c8 0201 	rsb	r2, r8, #1
10107f06:	4415      	add	r5, r2
10107f08:	441d      	add	r5, r3
10107f0a:	4638      	mov	r0, r7
10107f0c:	e7ba      	b.n	10107e84 <_strstr+0x178>
10107f0e:	9b03      	ldr	r3, [sp, #12]
10107f10:	4638      	mov	r0, r7
10107f12:	441d      	add	r5, r3
10107f14:	e7b6      	b.n	10107e84 <_strstr+0x178>
10107f16:	780b      	ldrb	r3, [r1, #0]
10107f18:	b913      	cbnz	r3, 10107f20 <_strstr+0x214>
10107f1a:	4770      	bx	lr
10107f1c:	4641      	mov	r1, r8
10107f1e:	e790      	b.n	10107e42 <_strstr+0x136>
10107f20:	2000      	movs	r0, #0
10107f22:	4770      	bx	lr

10107f24 <_strtoull>:
10107f24:	e92d 43f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, lr}
10107f28:	7801      	ldrb	r1, [r0, #0]
10107f2a:	bbba      	cbnz	r2, 10107f9c <_strtoull+0x78>
10107f2c:	2930      	cmp	r1, #48	; 0x30
10107f2e:	d043      	beq.n	10107fb8 <_strtoull+0x94>
10107f30:	220a      	movs	r2, #10
10107f32:	2900      	cmp	r1, #0
10107f34:	d052      	beq.n	10107fdc <_strtoull+0xb8>
10107f36:	2600      	movs	r6, #0
10107f38:	2700      	movs	r7, #0
10107f3a:	b2d5      	uxtb	r5, r2
10107f3c:	e015      	b.n	10107f6a <_strtoull+0x46>
10107f3e:	fb05 fe01 	mul.w	lr, r5, r1
10107f42:	fb05 f104 	mul.w	r1, r5, r4
10107f46:	fb05 f406 	mul.w	r4, r5, r6
10107f4a:	eb01 611e 	add.w	r1, r1, lr, lsr #24
10107f4e:	0a0e      	lsrs	r6, r1, #8
10107f50:	fb05 6907 	mla	r9, r5, r7, r6
10107f54:	f024 447f 	bic.w	r4, r4, #4278190080	; 0xff000000
10107f58:	ea44 6801 	orr.w	r8, r4, r1, lsl #24
10107f5c:	f810 1f01 	ldrb.w	r1, [r0, #1]!
10107f60:	eb18 0603 	adds.w	r6, r8, r3
10107f64:	f149 0700 	adc.w	r7, r9, #0
10107f68:	b1a1      	cbz	r1, 10107f94 <_strtoull+0x70>
10107f6a:	f1a1 0330 	sub.w	r3, r1, #48	; 0x30
10107f6e:	f041 0420 	orr.w	r4, r1, #32
10107f72:	b2d9      	uxtb	r1, r3
10107f74:	b2e4      	uxtb	r4, r4
10107f76:	2909      	cmp	r1, #9
10107f78:	f1a4 0e61 	sub.w	lr, r4, #97	; 0x61
10107f7c:	d904      	bls.n	10107f88 <_strtoull+0x64>
10107f7e:	f1be 0f05 	cmp.w	lr, #5
10107f82:	d807      	bhi.n	10107f94 <_strtoull+0x70>
10107f84:	f1a4 0357 	sub.w	r3, r4, #87	; 0x57
10107f88:	4293      	cmp	r3, r2
10107f8a:	f026 417f 	bic.w	r1, r6, #4278190080	; 0xff000000
10107f8e:	ea4f 6416 	mov.w	r4, r6, lsr #24
10107f92:	d3d4      	bcc.n	10107f3e <_strtoull+0x1a>
10107f94:	4630      	mov	r0, r6
10107f96:	4639      	mov	r1, r7
10107f98:	e8bd 83f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, pc}
10107f9c:	2a10      	cmp	r2, #16
10107f9e:	d1c8      	bne.n	10107f32 <_strtoull+0xe>
10107fa0:	2930      	cmp	r1, #48	; 0x30
10107fa2:	d1c6      	bne.n	10107f32 <_strtoull+0xe>
10107fa4:	7843      	ldrb	r3, [r0, #1]
10107fa6:	f043 0320 	orr.w	r3, r3, #32
10107faa:	2b78      	cmp	r3, #120	; 0x78
10107fac:	d1c3      	bne.n	10107f36 <_strtoull+0x12>
10107fae:	7883      	ldrb	r3, [r0, #2]
10107fb0:	4619      	mov	r1, r3
10107fb2:	3002      	adds	r0, #2
10107fb4:	2210      	movs	r2, #16
10107fb6:	e7bc      	b.n	10107f32 <_strtoull+0xe>
10107fb8:	7843      	ldrb	r3, [r0, #1]
10107fba:	f043 0320 	orr.w	r3, r3, #32
10107fbe:	2b78      	cmp	r3, #120	; 0x78
10107fc0:	d001      	beq.n	10107fc6 <_strtoull+0xa2>
10107fc2:	2208      	movs	r2, #8
10107fc4:	e7b7      	b.n	10107f36 <_strtoull+0x12>
10107fc6:	7883      	ldrb	r3, [r0, #2]
10107fc8:	f1a3 0230 	sub.w	r2, r3, #48	; 0x30
10107fcc:	2a09      	cmp	r2, #9
10107fce:	d9ef      	bls.n	10107fb0 <_strtoull+0x8c>
10107fd0:	f023 0220 	bic.w	r2, r3, #32
10107fd4:	3a41      	subs	r2, #65	; 0x41
10107fd6:	2a05      	cmp	r2, #5
10107fd8:	d9ea      	bls.n	10107fb0 <_strtoull+0x8c>
10107fda:	e7f2      	b.n	10107fc2 <_strtoull+0x9e>
10107fdc:	2600      	movs	r6, #0
10107fde:	2700      	movs	r7, #0
10107fe0:	e7d8      	b.n	10107f94 <_strtoull+0x70>
10107fe2:	bf00      	nop

10107fe4 <_strtoll>:
10107fe4:	b510      	push	{r4, lr}
10107fe6:	7804      	ldrb	r4, [r0, #0]
10107fe8:	2c2d      	cmp	r4, #45	; 0x2d
10107fea:	d003      	beq.n	10107ff4 <_strtoll+0x10>
10107fec:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
10107ff0:	f7ff bf98 	b.w	10107f24 <_strtoull>
10107ff4:	3001      	adds	r0, #1
10107ff6:	f7ff ff95 	bl	10107f24 <_strtoull>
10107ffa:	4240      	negs	r0, r0
10107ffc:	eb61 0141 	sbc.w	r1, r1, r1, lsl #1
10108000:	bd10      	pop	{r4, pc}
10108002:	bf00      	nop

10108004 <_strtok>:
10108004:	2301      	movs	r3, #1
10108006:	4a01      	ldr	r2, [pc, #4]	; (1010800c <_strtok+0x8>)
10108008:	f000 b802 	b.w	10108010 <__strtok_r>
1010800c:	10000560 	.word	0x10000560

10108010 <__strtok_r>:
10108010:	b4f0      	push	{r4, r5, r6, r7}
10108012:	b320      	cbz	r0, 1010805e <__strtok_r+0x4e>
10108014:	4607      	mov	r7, r0
10108016:	460d      	mov	r5, r1
10108018:	f817 6b01 	ldrb.w	r6, [r7], #1
1010801c:	e001      	b.n	10108022 <__strtok_r+0x12>
1010801e:	42a6      	cmp	r6, r4
10108020:	d016      	beq.n	10108050 <__strtok_r+0x40>
10108022:	f815 4b01 	ldrb.w	r4, [r5], #1
10108026:	2c00      	cmp	r4, #0
10108028:	d1f9      	bne.n	1010801e <__strtok_r+0xe>
1010802a:	b1ee      	cbz	r6, 10108068 <__strtok_r+0x58>
1010802c:	463e      	mov	r6, r7
1010802e:	460c      	mov	r4, r1
10108030:	f816 5b01 	ldrb.w	r5, [r6], #1
10108034:	e000      	b.n	10108038 <__strtok_r+0x28>
10108036:	b173      	cbz	r3, 10108056 <__strtok_r+0x46>
10108038:	f814 3b01 	ldrb.w	r3, [r4], #1
1010803c:	429d      	cmp	r5, r3
1010803e:	d1fa      	bne.n	10108036 <__strtok_r+0x26>
10108040:	b15d      	cbz	r5, 1010805a <__strtok_r+0x4a>
10108042:	2300      	movs	r3, #0
10108044:	703b      	strb	r3, [r7, #0]
10108046:	6016      	str	r6, [r2, #0]
10108048:	4606      	mov	r6, r0
1010804a:	4630      	mov	r0, r6
1010804c:	bcf0      	pop	{r4, r5, r6, r7}
1010804e:	4770      	bx	lr
10108050:	b163      	cbz	r3, 1010806c <__strtok_r+0x5c>
10108052:	4638      	mov	r0, r7
10108054:	e7de      	b.n	10108014 <__strtok_r+0x4>
10108056:	4637      	mov	r7, r6
10108058:	e7e8      	b.n	1010802c <__strtok_r+0x1c>
1010805a:	462e      	mov	r6, r5
1010805c:	e7f3      	b.n	10108046 <__strtok_r+0x36>
1010805e:	6810      	ldr	r0, [r2, #0]
10108060:	2800      	cmp	r0, #0
10108062:	d1d7      	bne.n	10108014 <__strtok_r+0x4>
10108064:	4606      	mov	r6, r0
10108066:	e7f0      	b.n	1010804a <__strtok_r+0x3a>
10108068:	6016      	str	r6, [r2, #0]
1010806a:	e7ee      	b.n	1010804a <__strtok_r+0x3a>
1010806c:	6017      	str	r7, [r2, #0]
1010806e:	4606      	mov	r6, r0
10108070:	7003      	strb	r3, [r0, #0]
10108072:	e7ea      	b.n	1010804a <__strtok_r+0x3a>

10108074 <_strtok_r>:
10108074:	2301      	movs	r3, #1
10108076:	f7ff bfcb 	b.w	10108010 <__strtok_r>
1010807a:	bf00      	nop

1010807c <_strtol_r>:
1010807c:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
10108080:	4684      	mov	ip, r0
10108082:	4605      	mov	r5, r0
10108084:	462b      	mov	r3, r5
10108086:	f813 4b01 	ldrb.w	r4, [r3], #1
1010808a:	2c20      	cmp	r4, #32
1010808c:	f1a4 0609 	sub.w	r6, r4, #9
10108090:	d003      	beq.n	1010809a <_strtol_r+0x1e>
10108092:	2e04      	cmp	r6, #4
10108094:	d901      	bls.n	1010809a <_strtol_r+0x1e>
10108096:	2c2c      	cmp	r4, #44	; 0x2c
10108098:	d101      	bne.n	1010809e <_strtol_r+0x22>
1010809a:	461d      	mov	r5, r3
1010809c:	e7f2      	b.n	10108084 <_strtol_r+0x8>
1010809e:	2c2d      	cmp	r4, #45	; 0x2d
101080a0:	d05e      	beq.n	10108160 <_strtol_r+0xe4>
101080a2:	f04f 0900 	mov.w	r9, #0
101080a6:	2c2b      	cmp	r4, #43	; 0x2b
101080a8:	bf04      	itt	eq
101080aa:	786c      	ldrbeq	r4, [r5, #1]
101080ac:	1cab      	addeq	r3, r5, #2
101080ae:	2a00      	cmp	r2, #0
101080b0:	d043      	beq.n	1010813a <_strtol_r+0xbe>
101080b2:	2a10      	cmp	r2, #16
101080b4:	d059      	beq.n	1010816a <_strtol_r+0xee>
101080b6:	4610      	mov	r0, r2
101080b8:	f1b9 0f00 	cmp.w	r9, #0
101080bc:	bf0c      	ite	eq
101080be:	f06f 4800 	mvneq.w	r8, #2147483648	; 0x80000000
101080c2:	f04f 4800 	movne.w	r8, #2147483648	; 0x80000000
101080c6:	2600      	movs	r6, #0
101080c8:	fbb8 fef0 	udiv	lr, r8, r0
101080cc:	4637      	mov	r7, r6
101080ce:	fb00 881e 	mls	r8, r0, lr, r8
101080d2:	e005      	b.n	101080e0 <_strtol_r+0x64>
101080d4:	d020      	beq.n	10108118 <_strtol_r+0x9c>
101080d6:	2601      	movs	r6, #1
101080d8:	fb00 5707 	mla	r7, r0, r7, r5
101080dc:	f813 4b01 	ldrb.w	r4, [r3], #1
101080e0:	f1a4 0530 	sub.w	r5, r4, #48	; 0x30
101080e4:	fa5f fa85 	uxtb.w	sl, r5
101080e8:	f1ba 0f09 	cmp.w	sl, #9
101080ec:	d909      	bls.n	10108102 <_strtol_r+0x86>
101080ee:	f1a4 0541 	sub.w	r5, r4, #65	; 0x41
101080f2:	2d19      	cmp	r5, #25
101080f4:	d90e      	bls.n	10108114 <_strtol_r+0x98>
101080f6:	f1a4 0561 	sub.w	r5, r4, #97	; 0x61
101080fa:	2d19      	cmp	r5, #25
101080fc:	d811      	bhi.n	10108122 <_strtol_r+0xa6>
101080fe:	2557      	movs	r5, #87	; 0x57
10108100:	1b65      	subs	r5, r4, r5
10108102:	42aa      	cmp	r2, r5
10108104:	dd0d      	ble.n	10108122 <_strtol_r+0xa6>
10108106:	1c74      	adds	r4, r6, #1
10108108:	d0e8      	beq.n	101080dc <_strtol_r+0x60>
1010810a:	4577      	cmp	r7, lr
1010810c:	d9e2      	bls.n	101080d4 <_strtol_r+0x58>
1010810e:	f04f 36ff 	mov.w	r6, #4294967295
10108112:	e7e3      	b.n	101080dc <_strtol_r+0x60>
10108114:	2537      	movs	r5, #55	; 0x37
10108116:	e7f3      	b.n	10108100 <_strtol_r+0x84>
10108118:	4545      	cmp	r5, r8
1010811a:	dddc      	ble.n	101080d6 <_strtol_r+0x5a>
1010811c:	f04f 36ff 	mov.w	r6, #4294967295
10108120:	e7dc      	b.n	101080dc <_strtol_r+0x60>
10108122:	1c72      	adds	r2, r6, #1
10108124:	d010      	beq.n	10108148 <_strtol_r+0xcc>
10108126:	f1b9 0f00 	cmp.w	r9, #0
1010812a:	d10b      	bne.n	10108144 <_strtol_r+0xc8>
1010812c:	4638      	mov	r0, r7
1010812e:	b379      	cbz	r1, 10108190 <_strtol_r+0x114>
10108130:	b996      	cbnz	r6, 10108158 <_strtol_r+0xdc>
10108132:	4663      	mov	r3, ip
10108134:	600b      	str	r3, [r1, #0]
10108136:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
1010813a:	2c30      	cmp	r4, #48	; 0x30
1010813c:	d021      	beq.n	10108182 <_strtol_r+0x106>
1010813e:	220a      	movs	r2, #10
10108140:	4610      	mov	r0, r2
10108142:	e7b9      	b.n	101080b8 <_strtol_r+0x3c>
10108144:	427f      	negs	r7, r7
10108146:	e7f1      	b.n	1010812c <_strtol_r+0xb0>
10108148:	f1b9 0f00 	cmp.w	r9, #0
1010814c:	bf14      	ite	ne
1010814e:	f04f 4000 	movne.w	r0, #2147483648	; 0x80000000
10108152:	f06f 4000 	mvneq.w	r0, #2147483648	; 0x80000000
10108156:	b1e9      	cbz	r1, 10108194 <_strtol_r+0x118>
10108158:	3b01      	subs	r3, #1
1010815a:	600b      	str	r3, [r1, #0]
1010815c:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
10108160:	1cab      	adds	r3, r5, #2
10108162:	786c      	ldrb	r4, [r5, #1]
10108164:	f04f 0901 	mov.w	r9, #1
10108168:	e7a1      	b.n	101080ae <_strtol_r+0x32>
1010816a:	2c30      	cmp	r4, #48	; 0x30
1010816c:	d1a3      	bne.n	101080b6 <_strtol_r+0x3a>
1010816e:	7818      	ldrb	r0, [r3, #0]
10108170:	f000 00df 	and.w	r0, r0, #223	; 0xdf
10108174:	2858      	cmp	r0, #88	; 0x58
10108176:	d19e      	bne.n	101080b6 <_strtol_r+0x3a>
10108178:	2010      	movs	r0, #16
1010817a:	785c      	ldrb	r4, [r3, #1]
1010817c:	4602      	mov	r2, r0
1010817e:	3302      	adds	r3, #2
10108180:	e79a      	b.n	101080b8 <_strtol_r+0x3c>
10108182:	781a      	ldrb	r2, [r3, #0]
10108184:	f002 02df 	and.w	r2, r2, #223	; 0xdf
10108188:	2a58      	cmp	r2, #88	; 0x58
1010818a:	d0f5      	beq.n	10108178 <_strtol_r+0xfc>
1010818c:	2208      	movs	r2, #8
1010818e:	e792      	b.n	101080b6 <_strtol_r+0x3a>
10108190:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
10108194:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}

10108198 <_strtol>:
10108198:	f7ff bf70 	b.w	1010807c <_strtol_r>

1010819c <_strtoul_r>:
1010819c:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
101081a0:	4605      	mov	r5, r0
101081a2:	462b      	mov	r3, r5
101081a4:	f813 4b01 	ldrb.w	r4, [r3], #1
101081a8:	2c20      	cmp	r4, #32
101081aa:	f1a4 0609 	sub.w	r6, r4, #9
101081ae:	d003      	beq.n	101081b8 <_strtoul_r+0x1c>
101081b0:	2e04      	cmp	r6, #4
101081b2:	d901      	bls.n	101081b8 <_strtoul_r+0x1c>
101081b4:	2c2c      	cmp	r4, #44	; 0x2c
101081b6:	d101      	bne.n	101081bc <_strtoul_r+0x20>
101081b8:	461d      	mov	r5, r3
101081ba:	e7f2      	b.n	101081a2 <_strtoul_r+0x6>
101081bc:	2c2d      	cmp	r4, #45	; 0x2d
101081be:	d056      	beq.n	1010826e <_strtoul_r+0xd2>
101081c0:	f04f 0900 	mov.w	r9, #0
101081c4:	2c2b      	cmp	r4, #43	; 0x2b
101081c6:	bf04      	itt	eq
101081c8:	786c      	ldrbeq	r4, [r5, #1]
101081ca:	1cab      	addeq	r3, r5, #2
101081cc:	b15a      	cbz	r2, 101081e6 <_strtoul_r+0x4a>
101081ce:	2a10      	cmp	r2, #16
101081d0:	d052      	beq.n	10108278 <_strtoul_r+0xdc>
101081d2:	f04f 3eff 	mov.w	lr, #4294967295
101081d6:	fbbe fef2 	udiv	lr, lr, r2
101081da:	fb02 f80e 	mul.w	r8, r2, lr
101081de:	4694      	mov	ip, r2
101081e0:	ea6f 0808 	mvn.w	r8, r8
101081e4:	e007      	b.n	101081f6 <_strtoul_r+0x5a>
101081e6:	2c30      	cmp	r4, #48	; 0x30
101081e8:	d057      	beq.n	1010829a <_strtoul_r+0xfe>
101081ea:	220a      	movs	r2, #10
101081ec:	f04f 0805 	mov.w	r8, #5
101081f0:	4694      	mov	ip, r2
101081f2:	f8df e0d8 	ldr.w	lr, [pc, #216]	; 101082cc <_strtoul_r+0x130>
101081f6:	2600      	movs	r6, #0
101081f8:	4637      	mov	r7, r6
101081fa:	e005      	b.n	10108208 <_strtoul_r+0x6c>
101081fc:	d020      	beq.n	10108240 <_strtoul_r+0xa4>
101081fe:	2601      	movs	r6, #1
10108200:	fb0c 5707 	mla	r7, ip, r7, r5
10108204:	f813 4b01 	ldrb.w	r4, [r3], #1
10108208:	f1a4 0530 	sub.w	r5, r4, #48	; 0x30
1010820c:	fa5f fa85 	uxtb.w	sl, r5
10108210:	f1ba 0f09 	cmp.w	sl, #9
10108214:	d909      	bls.n	1010822a <_strtoul_r+0x8e>
10108216:	f1a4 0541 	sub.w	r5, r4, #65	; 0x41
1010821a:	2d19      	cmp	r5, #25
1010821c:	d90e      	bls.n	1010823c <_strtoul_r+0xa0>
1010821e:	f1a4 0561 	sub.w	r5, r4, #97	; 0x61
10108222:	2d19      	cmp	r5, #25
10108224:	d811      	bhi.n	1010824a <_strtoul_r+0xae>
10108226:	2557      	movs	r5, #87	; 0x57
10108228:	1b65      	subs	r5, r4, r5
1010822a:	42aa      	cmp	r2, r5
1010822c:	dd0d      	ble.n	1010824a <_strtoul_r+0xae>
1010822e:	2e00      	cmp	r6, #0
10108230:	db01      	blt.n	10108236 <_strtoul_r+0x9a>
10108232:	4577      	cmp	r7, lr
10108234:	d9e2      	bls.n	101081fc <_strtoul_r+0x60>
10108236:	f04f 36ff 	mov.w	r6, #4294967295
1010823a:	e7e3      	b.n	10108204 <_strtoul_r+0x68>
1010823c:	2537      	movs	r5, #55	; 0x37
1010823e:	e7f3      	b.n	10108228 <_strtoul_r+0x8c>
10108240:	4545      	cmp	r5, r8
10108242:	dddc      	ble.n	101081fe <_strtoul_r+0x62>
10108244:	f04f 36ff 	mov.w	r6, #4294967295
10108248:	e7dc      	b.n	10108204 <_strtoul_r+0x68>
1010824a:	2e00      	cmp	r6, #0
1010824c:	db09      	blt.n	10108262 <_strtoul_r+0xc6>
1010824e:	f1b9 0f00 	cmp.w	r9, #0
10108252:	d000      	beq.n	10108256 <_strtoul_r+0xba>
10108254:	427f      	negs	r7, r7
10108256:	b109      	cbz	r1, 1010825c <_strtoul_r+0xc0>
10108258:	b93e      	cbnz	r6, 1010826a <_strtoul_r+0xce>
1010825a:	6008      	str	r0, [r1, #0]
1010825c:	4638      	mov	r0, r7
1010825e:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
10108262:	f04f 37ff 	mov.w	r7, #4294967295
10108266:	2900      	cmp	r1, #0
10108268:	d0f8      	beq.n	1010825c <_strtoul_r+0xc0>
1010826a:	1e58      	subs	r0, r3, #1
1010826c:	e7f5      	b.n	1010825a <_strtoul_r+0xbe>
1010826e:	1cab      	adds	r3, r5, #2
10108270:	786c      	ldrb	r4, [r5, #1]
10108272:	f04f 0901 	mov.w	r9, #1
10108276:	e7a9      	b.n	101081cc <_strtoul_r+0x30>
10108278:	2c30      	cmp	r4, #48	; 0x30
1010827a:	d11a      	bne.n	101082b2 <_strtoul_r+0x116>
1010827c:	781d      	ldrb	r5, [r3, #0]
1010827e:	f005 05df 	and.w	r5, r5, #223	; 0xdf
10108282:	2d58      	cmp	r5, #88	; 0x58
10108284:	d11b      	bne.n	101082be <_strtoul_r+0x122>
10108286:	f04f 0c10 	mov.w	ip, #16
1010828a:	785c      	ldrb	r4, [r3, #1]
1010828c:	4662      	mov	r2, ip
1010828e:	3302      	adds	r3, #2
10108290:	f04f 080f 	mov.w	r8, #15
10108294:	f06f 4e70 	mvn.w	lr, #4026531840	; 0xf0000000
10108298:	e7ad      	b.n	101081f6 <_strtoul_r+0x5a>
1010829a:	781a      	ldrb	r2, [r3, #0]
1010829c:	f002 02df 	and.w	r2, r2, #223	; 0xdf
101082a0:	2a58      	cmp	r2, #88	; 0x58
101082a2:	d0f0      	beq.n	10108286 <_strtoul_r+0xea>
101082a4:	2208      	movs	r2, #8
101082a6:	f04f 0807 	mov.w	r8, #7
101082aa:	4694      	mov	ip, r2
101082ac:	f06f 4e60 	mvn.w	lr, #3758096384	; 0xe0000000
101082b0:	e7a1      	b.n	101081f6 <_strtoul_r+0x5a>
101082b2:	f04f 080f 	mov.w	r8, #15
101082b6:	f06f 4e70 	mvn.w	lr, #4026531840	; 0xf0000000
101082ba:	4694      	mov	ip, r2
101082bc:	e79b      	b.n	101081f6 <_strtoul_r+0x5a>
101082be:	4694      	mov	ip, r2
101082c0:	f04f 080f 	mov.w	r8, #15
101082c4:	f06f 4e70 	mvn.w	lr, #4026531840	; 0xf0000000
101082c8:	e795      	b.n	101081f6 <_strtoul_r+0x5a>
101082ca:	bf00      	nop
101082cc:	19999999 	.word	0x19999999

101082d0 <_strtoul>:
101082d0:	f7ff bf64 	b.w	1010819c <_strtoul_r>

101082d4 <_strupr>:
101082d4:	7803      	ldrb	r3, [r0, #0]
101082d6:	b153      	cbz	r3, 101082ee <_strupr+0x1a>
101082d8:	4602      	mov	r2, r0
101082da:	f1a3 0161 	sub.w	r1, r3, #97	; 0x61
101082de:	2919      	cmp	r1, #25
101082e0:	bf9c      	itt	ls
101082e2:	3b20      	subls	r3, #32
101082e4:	7013      	strbls	r3, [r2, #0]
101082e6:	f812 3f01 	ldrb.w	r3, [r2, #1]!
101082ea:	2b00      	cmp	r3, #0
101082ec:	d1f5      	bne.n	101082da <_strupr+0x6>
101082ee:	4770      	bx	lr
