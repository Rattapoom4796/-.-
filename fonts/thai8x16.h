/*
 *
 * thai8x16
 *
 *
 * File Name           : thai8x16.h
 * Date Created        : 23 Juni 2020
 * Date Updated        : 29 Juni 2020
 * Font width          : 8
 * Font height         : 16
 * Font first char     : 32
 * Font last char      : 127
 * Font used chars     : 94
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#ifdef __AVR__
#include <avr/pgmspace.h>
#elif defined (ESP8266)
#include <pgmspace.h>
#else
#define PROGMEM
#endif

#ifndef thai8x16_H
#define thai8x16_H

#define thai8x16_H_WIDTH 8
#define thai8x16_H_HEIGHT 16

/*
 * added to allow fontname to match header file name. 
 * as well as keep the old name for backward compability
 */

#define thai8x16 thai8x16

const static uint8_t thai8x16[] PROGMEM = {
    0x10, //16, // size 
	0x80, //128, // size of zero indicates fixed width font, actual length is width * height
    0x08, //8, // width
    0x10, //16, // height
    0x20, //32, // first char
    0xc3, //195, // char count

	0x01, 0x02, 0x05, 0x08, 0x08, 0x08, 0x08, 0x02, 0x05, 0x05, // spasi  !	"	#	$	%	&	'	(	)
	0x05, 0x08, 0x04, 0x08, 0x04, 0x08, // *	+   ,	-	.	/	

   	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, // 0	1	2	3 	4	5	6	7	8	9

	0x04, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, // :	;	<	=	>	?	@

	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // A	B	C	D	E	F	G	H	I	J
	0x08, 0x08, 0x08, 0x07, 0x06, 0x08, 0x08, 0x08, 0x07, 0x08, // K	L	M	N	O	P	Q	R	S	T
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08,	// U	V	W	X	Y	Z

	0x04, 0x08, 0x04, 0x08, 0x08, 0x04, //	[	\	]	^	_	`

	0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x08, 0x08, 0x02, 0x05,  // a	b	c	d	e	f	g	h	i	j
	0x08, 0x02, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x05,  //	k	l	m	n	o	p	q	r	s	t
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, //	u	v	w	x	y	z

	0x06, 0x02, 0x06, 0x08, 0x08, //	{	|	}	->	<-
    	0x07, 0x07, 0x08, 0x09, 0x09, 0x09, 0x05, 0x08, // ก	ข	ฃ	ค	ฅ	ฆ	ง	จ
    	0x0a, 0x08, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x0a,// ฉ	ช	ซ	ฌ	ญ	ฎ	ฏ	ฐ	ฑ
	0x0b, 0x0a, 0x09, 0x09, 0x07, 0x09, 0x08, 0x08,// ฒ	ณ	ด	ต	ถ	ท	ร	น	
	0x07, 0x07, 0x08, 0x08, 0x0a, 0x0a, 0x09, 0x08, 0x08, //บ		ป	ผ	ฝ	พ	ฟ	ภ	ม	ย	
	0x09, 0x09, 0x06, 0x09, 0x0c, 0x08, 0x0c, 0x0b, 0x09, 0x08,//ร	ล	ว	ศ	ษ	ส	ห	ฬ	อ	ฮ
	0x06, 0x06, 0x06, 0x06, 0x03, 0x05, 0x04, 0x04, 0x03, 0x06, 0x06,  // อิ	อี	อึ	อื	อุ	อู	อะ	อา	เอ	แอ 	ออ
	0x06, 0x05, 0x05, 0x06, 0x05, 0x09, 0x06, 0x0a, 0x02, 0x07, //โอ		ไอ	ใอ	อั	ฤ	ฤๅ	ฦ	ฦๅ	อ่	อ้
	0x0a, 0x04, 0x08, 0x07,	// อ๊	อ๋	อำ	อ็	
	0x16, 0x18, 0x17, 0x18, 0x1c,//eng1 eng2 eng3 eng4 eng5
	0x16, 0x18, 0x1a, 0x15, 0x25, // thai1 thai2 thai3 thai4 thai5
	0x0f, 0x0c, 0x0b, 0x13, 0x0e, // จีน1 จีน2 จีน3 จีน4 จีน5
	0x18, 0x4a, 0x20, 0x19, 0x1c, // สวีเดน1 สวีเดน2 สวีเดน3 สวีเดน4 สวีเดน5
	0x25, 0x22, 0x26, 0x24, 0x50, // russia1 russia2 russia3 russia4 russia4
	0x13, 0x11, 0x10, 0x10, 0x14, // emo1 emo2 emo3 emo4 emo5

	// font data			   |

	0x00, 0x00, // (space)
	0xff, 0xff, 0xcf, 0xcf, // !
	0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,// "
	0x30, 0xff, 0xff, 0x30, 0x30, 0xff, 0xff, 0x30, 0x0c, 0xff, 0xff, 0x0c, 0x0c, 0xff, 0xff, 0x0c,// #
	0xf8, 0xfc, 0x8c, 0x8f, 0x8f, 0x8c, 0x8c, 0x0c, 0x30, 0x31, 0x31, 0xf1, 0xf1, 0x31, 0x3f, 0x1f,// $
	0x06, 0x0f, 0x0f, 0x86, 0xe0, 0x78, 0x1f, 0x0f, 0xf0, 0xf8, 0x1e, 0x07, 0x63, 0xf0, 0xf0, 0x60,// %
	0xfe, 0xff, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x7f, 0xff, 0xc0, 0xc0, 0xc0, 0xfe, 0x7e, 0x06, // &
	0x0f, 0x0f, 0x00, 0x00, // '
	0xc0, 0xf0, 0x3c, 0x0e, 0x03, 0x03, 0x0f, 0x3c, 0x70, 0xc0, // (
	0x03, 0x0e, 0x3c, 0xf0, 0xc0, 0xc0, 0x70, 0x3c, 0x0f, 0x03, // )
	0x15, 0x0e, 0x1f, 0x0e, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00,// *
	0x80, 0x80, 0x80, 0xf8, 0xf8, 0x80, 0x80, 0x80, 0x01, 0x01, 0x01, 0x1f, 0x1f, 0x01, 0x01, 0x01,// +
	0x00, 0x00, 0x00, 0x00, 0xdc, 0xde, 0xfe, 0x7c, // ,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,// -
	0x00, 0x00, 0x00, 0x00, 0x60, 0xf0, 0xf0, 0x60, // .
	0x00, 0x00, 0x00, 0x80, 0xe0, 0x78, 0x1f, 0x0f, 0xf0, 0xf8, 0x1e, 0x07, 0x03, 0x00, 0x00, 0x00,// /

	0xfc, 0x07, 0x03, 0x03, 0x07, 0xfc, 0x00, 0x7f, 0xe0, 0xc0, 0xc0, 0xe0, 0x7f, 0x00, // new 0	
	0x70, 0x1c, 0xff, 0xff, 0x00, 0x00, 0x00, 0x80, 0x80, 0xff, 0xff, 0x80, 0x80, 0x00, // new 1
	0x0e, 0x03, 0x01, 0x81, 0x41, 0x3e, 0x00, 0xfc, 0x82, 0x81, 0x80, 0x80, 0x80, 0x00, // new 2
	0x83, 0x83, 0x83, 0x83, 0x83, 0xff, 0x00, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0x00, // new 3
	0xf0, 0x98, 0x8c, 0x86, 0xff, 0x80, 0x00, 0x01, 0x01, 0x01, 0x01, 0xff, 0x01, 0x00, // new 4
	0xff, 0xff, 0x83, 0x83, 0x83, 0x83, 0x00, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0xff, 0x00, // new 5
	0xff, 0x83, 0x83, 0x83, 0x83, 0x83, 0x00, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0x00, // new 6 
	0x03, 0x03, 0x03, 0x03, 0xc3, 0x3f, 0x00, 0xc0, 0x30, 0x0c, 0x03, 0x00, 0x00, 0x00, // new 7
	0xff, 0x83, 0x83, 0x83, 0x83, 0xff, 0x00, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0x00, // new 8
	0xff, 0x83, 0x83, 0x83, 0x83, 0xff, 0x00, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0x00, // new 9

        0x18, 0x3c, 0x3c, 0x18, 0x18, 0x3c, 0x3c, 0x18,	//:
	0x18, 0x3c, 0x3c, 0x18, 0x98, 0xbc, 0xfc, 0x78, //; 	
	0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, // <
	0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, // =
	0x03, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, // >
	0x0e, 0x0f, 0x03, 0x03, 0xc3, 0xe3, 0x7f, 0x3e, 0x00, 0x00, 0x00, 0xdf, 0xdf, 0x01, 0x00, 0x00, // ?
	0xfe, 0xff, 0x03, 0xf3, 0xf3, 0x03, 0xff, 0xfe, 0x7f, 0xff, 0xc0, 0xc0, 0xcf, 0xcc, 0xcf, 0x4f, // @

	0xfe, 0x02, 0x03, 0x01, 0x03, 0x02, 0xfe, 0x00, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0x00,// new A
	0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7e, 0x00, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7f, 0x00,// new B
	0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x07, 0x00, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0xf8, 0x00,// new C
	0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0xfe, 0x00, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7f, 0x00,// new D
	0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x00, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,// new E
	0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// new F
	0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0xff, 0x80, 0x80, 0x81, 0x81, 0x81, 0xff, 0x00,// new G
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0x00,// new H
	0x01, 0x01, 0x01, 0xff, 0x01, 0x01, 0x01, 0x00, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x00,// new I
	0x01, 0x01, 0x01, 0x01, 0xff, 0x01, 0x01, 0x00, 0xf0, 0x80, 0x80, 0x80, 0xff, 0x00, 0x00, 0x00,// new J
	0xff, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0f, 0x00, 0xff, 0x01, 0x03, 0x06, 0x0c, 0x18, 0xf0, 0x00,// new K
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,// new L
	0xff, 0x02, 0xfc, 0x00, 0xfc, 0x02, 0xff, 0x00, 0xff, 0x00, 0x07, 0x08, 0x07, 0x00, 0xff, 0x00,// new M
	0xff, 0x02, 0x7c, 0x80, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x0f, 0x70, 0xff, 0x00,// new N
	0xfc, 0x06, 0x03, 0x06, 0xfc, 0x00, 0x3f, 0x60, 0xc0, 0x60, 0x3f, 0x00,// new O
	0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// new P
	0xfe, 0x03, 0x03, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xf0, 0x7f, 0xc0, 0x80, 0x00,// new Q
	0xff, 0x33, 0x73, 0xb3, 0x33, 0x33, 0x3f, 0x00, 0xff, 0x00, 0x00, 0x01, 0x06, 0x18, 0xe0, 0x00,// new R
	0x1c, 0x23, 0x43, 0x83, 0x03, 0x0c, 0x00, 0x60, 0x80, 0x80, 0x80, 0xe3, 0x7c, 0x00,// new S
	0x03, 0x03, 0x03, 0xff, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,// new T
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x3f, 0x60, 0xc0, 0xc0, 0xc0, 0x60, 0x3f, 0x00,// new U
	0x3f, 0xf0, 0x80, 0x00, 0x80, 0xf0, 0x3f, 0x00, 0x00, 0x03, 0x3f, 0xf8, 0x3f, 0x03, 0x00, 0x00,// new V
	0xff, 0xe0, 0x00, 0xf8, 0x00, 0xe0, 0xff, 0x00, 0x00, 0x0f, 0xfe, 0x1f, 0xfe, 0x0f, 0x00, 0x00,// new W
	0x01, 0x0e, 0x70, 0x80, 0x70, 0x0e, 0x01, 0x00, 0x80, 0x60, 0x1c, 0x03, 0x1c, 0x60, 0x80, 0x00,// new X
	0x07, 0x0c, 0x38, 0xe0, 0x38, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,// new Y
	0x03, 0x03, 0x03, 0x83, 0x63, 0x1b, 0x0f, 0x00, 0xe0, 0xd8, 0xc6, 0xc1, 0xc0, 0xc0, 0xc0, 0x00,// new Z

	0xff, 0xff, 0x03, 0x03, 0xff, 0xff, 0xc0, 0xc0, // [
	0x0f, 0x1f, 0x78, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x1e, 0xf8, 0xf0,// "\"
	0x03, 0x03, 0xff, 0xff, 0xc0, 0xc0, 0xff, 0xff, // ]
	0x18, 0x1c, 0x0e, 0x03, 0x03, 0x0e, 0x1c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// ^
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,// _
	0x18, 0x3c, 0x3c, 0x18, 0x18, 0x3c, 0x3c, 0x18,// `

	0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xe0, 0x7e, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0x7f,// a
	0xff, 0xff, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xe0, 0x7f, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x7f,// b
	0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x70, 0x60, 0x7f, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0x60,// c
	0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0xff, 0xff, 0x7f, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x7f,// d
	0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xe0, 0x7f, 0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf, 0xcf,// e
	0xfe, 0xff, 0xc3, 0xc3, 0xc3, 0x03, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, // f
	0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xf0, 0xc7, 0xcf, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0x7f,// g
	0xff, 0xff, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xe0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,// h
	0xf3, 0xf3, 0xff, 0xff, // i
	0x00, 0x00, 0x00, 0xf3, 0xf3, 0xc0, 0xc0, 0xc0, 0xff, 0x7f, // j
	0xff, 0xff, 0x00, 0x00, 0x80, 0x80, 0xf0, 0x70, 0xff, 0xff, 0x03, 0x03, 0x07, 0x07, 0xfc, 0xf8,// k
	0xff, 0xff, 0xff, 0xff, // l
	0xe0, 0xf0, 0xf0, 0xc0, 0xc0, 0xf0, 0xf0, 0xe0, 0xff, 0xff, 0x00, 0x03, 0x03, 0x00, 0xff, 0xff,// m
	0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xe0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,// n
	0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xe0, 0x7f, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x7f,// o
	0xf0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xe0, 0xff, 0xff, 0x0c, 0x0c, 0x0c, 0x0c, 0x0f, 0x07,// p
	0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xf0, 0x07, 0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xff,// q
	0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// r
	0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xc3, 0xc7, 0xc6, 0xc6, 0xc6, 0xc6, 0xfe, 0x7c,// s
	0xff, 0xff, 0x30, 0x30, 0x30, 0x7f, 0xff, 0xc0, 0xc0, 0xc0,// t
	0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x7f, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x7f,// u
	0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x0f, 0x3f, 0x7c, 0xe0, 0xe0, 0x7c, 0x3f, 0x0f,// v
	0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x7f, 0xff, 0xf0, 0x3c, 0x3c, 0xf0, 0xff, 0x7f,// w
	0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf9, 0x0f, 0x06, 0x06, 0x0f, 0xf9, 0xf0,// x
	0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xc7, 0xcf, 0xcc, 0xcc, 0xcc, 0xcc, 0xff, 0x7f,// y
	0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3, 0xc1, 0xc0,// z

	0x80, 0xc0, 0xfe, 0x7f, 0x03, 0x03, 0x01, 0x03, 0x7f, 0xfe, 0xc0, 0xc0, // {
	0xff, 0xff, 0xff, 0xff,// |
	0x03, 0x03, 0x7f, 0xfe, 0xc0, 0x80, 0xc0, 0xc0, 0xfe, 0x7f, 0x03, 0x01,// }
	0x80, 0x80, 0x9c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x01, 0x01, 0x39, 0x1c, 0x0e, 0x07, 0x03, 0x01,// ->
	0x80, 0xc0, 0xe0, 0x70, 0x38, 0x9c, 0x80, 0x80, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x39, 0x01, 0x01, // <-
	
	0xa0, 0x50, 0x10, 0x10, 0x10, 0xe0, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00,	0x0f, 0x00, // "ก"
	0x20, 0x50, 0xe0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x07, 0x00, // "ข"
	0x20, 0x50, 0x20, 0xd0, 0x20, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x07, 0x00, // "ฃ"
	0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x20, 0xc0, 0x00, 0x07, 0x08, 0x04, 0x03, 0x01, 0x00, 0x00, 0x0f, 0x00, // "ค"
	0xc0, 0x20, 0x10, 0x20, 0x20, 0x10, 0x20, 0xc0, 0x00, 0x07, 0x08, 0x04, 0x03, 0x01, 0x00, 0x00, 0x0f, 0x00, // "ฅ"
	0x20, 0x50, 0x20, 0xd0, 0x20, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0e, 0x0a, 0x0f, 0x02, 0x04, 0x08, 0x0f, 0x00, // "ฆ"
	0x00, 0x20, 0x50, 0xe0, 0x00, 0x01, 0x02, 0x04, 0x0f, 0x00, // "ง"
	0x40, 0x20, 0x10, 0x90, 0x10, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x01, 0x02, 0x07, 0x0e, 0x03, 0x00, // "จ"
	0x20, 0x10, 0x90, 0x10, 0x10, 0x20, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0f, 0x08, 0x04, 0x07, 0x0a, 0x04, 0x00, // "ฉ"
	0x20, 0x50, 0xe0, 0x00, 0x10, 0xe8, 0x04, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x07, 0x00, 0x00, // "ช"
	0x20, 0x50, 0x20, 0xd0, 0x20, 0x10, 0xe8, 0x04, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x07, 0x00, 0x00, // "ซ"
	0xa0, 0x50, 0x10, 0x10, 0x10, 0xe0, 0x00, 0xf0, 0x00, 0x07, 0x0a, 0x04, 0x00, 0x04, 0x0b, 0x04, 0x0f, 0x00, // "ฌ"
	0xa0, 0x50, 0x10, 0x10, 0x10, 0xe0, 0x00, 0xf0, 0x00, 0x07, 0x0a, 0x04, 0x00, 0x00, 0x2f, 0x28, 0x2f, 0x00, // "ญ"
	0x00, 0x00, 0xa0, 0x50, 0x10, 0x10, 0x10, 0xf0, 0x00, 0x04, 0x0a, 0x07, 0x00, 0x20, 0x50, 0x28, 0x1f, 0x00, // "ฎ"
	0x00, 0x00, 0xa0, 0x50, 0x10, 0x10, 0x10, 0xf0, 0x00, 0x04, 0x0a, 0x07, 0x10, 0x28, 0x14, 0x20, 0x1f, 0x00, // "ฏ"
	0x00, 0x60, 0x50, 0x50, 0x50, 0xa0, 0x10, 0x00, 0x40, 0xa1, 0x63, 0x54, 0x88, 0xe7, 0x00, 0x00, // "ฐ"
	0x20, 0x50, 0x20, 0xd0, 0x20, 0x80, 0xf0, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x04, 0x03, 0x00, 0x00, 0x0f, 0x00, // "ฑ"
	0xc0, 0x20, 0x10, 0x20, 0x10, 0x10, 0xe0, 0x00, 0x00, 0xf0, 0x00, 0x01, 0x06, 0x08, 0x05, 0x03, 0x0c, 0x0f, 0x02, 0x02, 0x0f, 0x00, // "ฒ"
	0xc0, 0x20, 0x10, 0x10, 0x10, 0xe0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x00, 0x00, 0x0f, 0x04, 0x0b, 0x0c, 0x00, // "ณ"
	0xc0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x30, 0xc0, 0x00, 0x03, 0x04, 0x08, 0x0d, 0x03, 0x00, 0x00, 0x0f, 0x00, // "ด"
	0xc0, 0x20, 0x10, 0x20, 0x10, 0x10, 0x30, 0xc0, 0x00, 0x03, 0x04, 0x08, 0x0d, 0x03, 0x00, 0x00, 0x0f, 0x00, // "ต"
	0xc0, 0xa0, 0x10, 0x10, 0x10, 0xe0, 0x00, 0x00, 0x0f, 0x08, 0x00, 0x00, 0x0f, 0x00, // "ถ"
	0x10, 0xf0, 0x00, 0x80, 0x60, 0x10, 0x30, 0xc0, 0x00, 0x00, 0x0f, 0x06, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, // "ท"
	0x20, 0x50, 0x50, 0x50, 0x90, 0x20, 0x10, 0x00, 0x0f, 0x09, 0x09, 0x08, 0x0f, 0x00, 0x00, 0x00, // "ธ"
	0x10, 0xf0, 0x00, 0x80, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x06, 0x01, 0x07, 0x0d, 0x06, 0x00, // "น"
	0x10, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x00, // "บ"
	0x10, 0xf0, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x00, // "ป"
	0xf0, 0x10, 0x00, 0x80, 0x00, 0x00, 0xf0, 0x00, 0x0f, 0x04, 0x03, 0x00, 0x03, 0x04, 0x0f, 0x00, // "ผ"
	0xf0, 0x10, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x0f, 0x08, 0x04, 0x02, 0x04, 0x08, 0x0f, 0x00, // "ฝ"
	0x70, 0x50, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0x04, 0x02, 0x01, 0x02, 0x04, 0x0f, 0x00, // "พ"
	0x70, 0x50, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x0f, 0x04, 0x02, 0x01, 0x02, 0x04, 0x0f, 0x00, // "ฟ"
	0x40, 0x60, 0x90, 0x10, 0x10, 0x10, 0x10, 0xf0, 0x00, 0x0e, 0x0a, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, // "ภ"
	0x70, 0x50, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x0e, 0x0a, 0x0f, 0x02, 0x02, 0x02, 0x0f, 0x00, // "ม"
	0xf0, 0x50, 0x70, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x0e, 0x09, 0x09, 0x08, 0x08, 0x08, 0x0f, 0x00, // "ย"
	0x60, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x0a, 0x0f, 0x00, // "ร"
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0xf0, 0x00, 0x0f, 0x0a, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, // "ล"
	0x10, 0x10, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x0e, 0x0a, 0x0f, 0x00, // "ว"
	0xf0, 0x10, 0x90, 0x90, 0x90, 0x10, 0x18, 0xf4, 0x00, 0x0f, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x0f, 0x00, // "ศ"
	0x70, 0x50, 0xf0, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x80, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x00, 0x00, // "ษ"
	0x10, 0x10, 0x10, 0x10, 0x10, 0x18, 0xf4, 0x00, 0x0f, 0x0d, 0x01, 0x01, 0x01, 0x01, 0x0f, 0x00, // "ส"
	0x70, 0x50, 0xf0, 0x00, 0x00, 0x00, 0x80, 0x40, 0xf0, 0x50, 0x70, 0x00, 0x00, 0x00, 0x0f, 0x04, 0x02, 0x01, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, // "ห"
	0x70, 0x50, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x02, 0x00, 0x00, 0x00, 0x0f, 0x04, 0x02, 0x01, 0x02, 0x04, 0x0f, 0x00, 0x00, // "ฬ"
	0x90, 0x90, 0x90, 0x10, 0x10, 0x10, 0x10, 0xf0, 0x00, 0x0f, 0x0a, 0x0b, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x00, // "อ"
	0x10, 0x10, 0x10, 0x10, 0x10, 0x18, 0xf4, 0x00, 0x0f, 0x0b, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x00, // "ฮ"
	0x08, 0x0c, 0x0c, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "อิ"
	0x08, 0x0c, 0x0c, 0x0c, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "อี"
	0x08, 0x0c, 0x0c, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "อึ"
	0x08, 0x0c, 0x0e, 0x0c, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "อื"
	0x00, 0x00, 0x00, 0x30, 0xf0, 0x00, // "อุ"
	0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xf0, 0x80, 0xf0, 0x00, // "อู"
	0x60, 0x40, 0x40, 0x00, 0x06, 0x04, 0x04, 0x00, // "อะ"
	0x30, 0x30, 0xf0, 0x00, 0x00, 0x00, 0xf, 0x00, // "อา"
	0xf0, 0x00, 0x00, 0xf, 0xc, 0x00, // "เอ"
	0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf, 0xc, 0x00, 0xf, 0xc, 0x00, // "แอ"
	0xb0, 0x90, 0x90, 0x10, 0xf0, 0x00, 0x0f, 0x09, 0x09, 0x08, 0x0f, 0x00, // "ออ"
	0x07, 0x05, 0xfd, 0x01, 0x01, 0x00, 0x00, 0x00, 0xF, 0xC, 0x00, 0x00, // "โอ"
	0x01, 0x02, 0xff, 0x00, 0x00, 0x00, 0x00, 0xF, 0xC, 0x00, // "ไอ"
	0x07, 0x05, 0xff, 0x00, 0x00, 0x00, 0x00, 0xF, 0xC, 0x00, // "ใอ"
	0x0f, 0x0f, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "อั"
	0xb0, 0x50, 0x10, 0xf0, 0x00, 0x0f, 0x08, 0x00, 0xff, 0x00, // "ฤ"
	0xb0, 0x50, 0x10, 0xf0, 0x00, 0x10, 0x10, 0xf0, 0x00, 0x0f, 0x08, 0x00, 0x7f, 0x00, 0x00, 0x00, 0xff, 0x00, // "ฤๅ"
	0x00, 0xb0, 0x50, 0x10, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xff, 0x00, // "ฦ"
	0x00, 0xb0, 0x50, 0x10, 0xf0, 0x00, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, // "ฦๅ"
	0x0f, 0x00, 0x00, 0x00, // "อ่"
	0x0d, 0x0b, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "อ้"
	0x00, 0x05, 0x09, 0x02, 0x09, 0x05, 0x06, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "อ๊"
	0x02, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, // "อ๋"
	0x03, 0x03, 0x00, 0x00, 0x30, 0x30, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, // "อำ"
	0x06, 0x09, 0x05, 0x09, 0x0a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // "อ็"
	0xfc, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0xfc, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x01, 0x01, 0x01, 0x3f, 0x00, 0x1e, 0x25, 
	0x25, 0x25, 0x09, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x00, // "eng1"
	0xfc, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x01, 0x01, 0x01, 
	0x1c, 0x22, 0x22, 0x22, 0x1c, 0x20, 0x00, 0x3e, 0x08, 0x04, 0x02, 0x00, 0x3e, 0x04, 
	0x04, 0x38, 0x04, 0x04, 0x38, 0x00, // "eng2"
	0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x20, 0x20, 0x20, 
	0x20, 0x00, 0x3e, 0x00, 0x06, 0x08, 0x10, 0x20, 0x10, 0x08, 0x06, 0x00, 0x1c, 0x2a, 
	0x2a, 0x2a, 0x0c, 0x00, // "eng3"
	0xf0, 0x08, 0x08, 0x08, 0x70, 0x00, 0xf8, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x1f, 0x20, 0x20, 0x20, 
	0x1c, 0x00, 0x3f, 0x00, 0x19, 0x24, 0x24, 0x1b, 0x20, 0x00, 0x13, 0x24, 0x24, 0x19, 
	0x00, 0x13, 0x24, 0x24, 0x19, 0x00, // "eng4"
	0xff, 0x81, 0x81, 0x81, 0xc3, 0x66, 0x3c, 0x00, 0x00, 0xf8, 
	0x08, 0x06, 0x01, 0x01, 0x06, 0x08, 0xf8, 0x00, 0x00, 0xff, 
	0x01, 0x01, 0x01, 0x03, 0x06, 0x0c, 0xf8, 0x00, 0xff, 0x80, 
	0x80, 0x80, 0xc1, 0x63, 0x3e, 0x00, 0x00, 0xff, 0x01, 0x01, 
	0x01, 0x01, 0x01, 0x01, 0xff, 0x00, 0x00, 0xff, 0x80, 0x80, 
	0x80, 0xc0, 0x60, 0x38, 0x0f, 0x00
	, // "eng5"
	0x30, 0xf0, 0x40, 0x20, 0x10, 0xf0, 0x00, 0x60, 0x60, 0x80, 0x80, 0x40, 0x00, 0xf0, 
	0x00, 0x00, 0x20, 0x10, 0x90, 0x90, 0x60, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 
	0x00, 0x06, 0x06, 0x08, 0x08, 0x04, 0x00, 0x0f, 0x0c, 0x00, 0x0e, 0x0d, 0x00, 0x00, 
	0x0f, 0x00, // "thai1"

	0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x30, 0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x20, 
	0x10, 0x90, 0x90, 0x60, 0x00, 0x00, 0x00, 0x30, 0xf0, 0x00, 0x0f, 0x0c, 0x00, 0x0f, 
	0x0c, 0x00, 0x06, 0x0f, 0x01, 0x02, 0x04, 0x0f, 0x00, 0x0e, 0x0d, 0x00, 0x00, 0x0f, 
	0x00, 0x01, 0x02, 0x04, 0x0f, 0x00, // "thai2"

	0x10, 0x10, 0x90, 0x90, 0x60, 0x00, 0xa0, 0x50, 0x10, 0xe0, 0x00, 0xf0, 0x00, 0x00, 
	0xa0, 0x50, 0x10, 0xe0, 0x00, 0xe0, 0x10, 0x90, 0x90, 0x10, 0xe0, 0x00, 0x0e, 0x2d, 
	0xe0, 0x80, 0xef, 0x00, 0x07, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0x0c, 0x00, 0x0f, 0x00, 
	0x00, 0x0f, 0x00, 0x0f, 0x08, 0x05, 0x03, 0x00, 0x0f, 0x00, // "thai3"

	0x20, 0x10, 0x96, 0x96, 0x60, 0x00, 0x20, 0x10, 0x10, 0x16, 0xe5, 0x01, 0xfe, 0x00, 
	0x00, 0x70, 0x90, 0x30, 0x00, 0xf0, 0x00, 0x0e, 0x0d, 0x00, 0x00, 0x0f, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0x0c, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x00, // "thai4"

	0xe0, 0x10, 0x96, 0x96, 0x10, 0xe0, 0x00, 0x20, 0x10, 0x10, 0x10, 0xe0, 0x00, 0x30, 
	0xf0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x20, 0x10, 0x10, 0x10, 0xe0, 0x00, 0xa0, 0x50, 
	0x10, 0x10, 0xe0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x0f, 0x08, 0x07, 0x01, 0x00, 
	0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x04, 0x02, 0x01, 0x0f, 
	0x06, 0x00, 0x00, 0x0c, 0x0c, 0x07, 0x00, 0x0f, 0x0c, 0x00, 0x00, 0x0f, 0x04, 0x02, 
	0x01, 0x0f, 0x06, 0x00, // "thai5"

	0x90, 0x98, 0x88, 0xf8, 0x8c, 0x84, 0x80, 0x80, 0xf8, 0x8c, 0x80, 0x98, 0xb0, 0xa0, 
	0x00, 0x08, 0x2c, 0x44, 0x7f, 0x02, 0x12, 0x10, 0x18, 0x0f, 0x18, 0x6c, 0x26, 0x30, 
	0x18, 0x00, // "จีน1"

	0x84, 0x44, 0x4e, 0x24, 0x14, 0x94, 0x24, 0x44, 0x4e, 0x84, 0x04, 0x00, 0x00, 0x18, 
	0x0d, 0x25, 0x21, 0x1f, 0x01, 0x05, 0x0c, 0x18, 0x00, 0x00, // "จีน2"

	0xf8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xf8, 0x00, 0x04, 0x04, 0x04, 
	0x04, 0x3f, 0x3f, 0x04, 0x04, 0x04, 0x04, 0x00, // "จีน3"

	0x20, 0x10, 0xf8, 0x0c, 0x04, 0x80, 0xc0, 0xfc, 0x40, 0x60, 0x20, 0x20, 0xfe, 0x30, 
	0x10, 0x10, 0x18, 0xf8, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x18, 
	0x30, 0x20, 0x20, 0x23, 0x20, 0x22, 0x26, 0x36, 0x13, 0x00, // "จีน4"

	0xc0, 0x60, 0xf0, 0xbc, 0x88, 0x88, 0xe8, 0xb8, 0x98, 0x80, 0x80, 0x00, 0x00, 0x00, 
	0x20, 0x20, 0x2f, 0x2a, 0x2a, 0x2a, 0x2f, 0x2a, 0x2a, 0x2a, 0x2f, 0x20, 0x20, 0x00, // "จีน5"

	0x20, 0x16, 0x16, 0x10, 0x16, 0xe6, 0x00, 0x00, 0x06, 0x06, 0xff, 0xff, 0x06, 0x06, 
	0x20, 0x10, 0x8c, 0x8c, 0x8c, 0x8c, 0xf0, 0x00, 0x00, 0x00, 0x1e, 0x21, 0x41, 0x41, 
	0x41, 0x21, 0xde, 0x80, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x1e, 0x0f, 0x10, 0x20, 
	0x20, 0x20, 0x90, 0xef, 0x40, 0x00, // "สวีเดน1"

	0x3c, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x3c, 0x00, 0x20, 0x16, 0x16, 0x10, 
	0x16, 0xe6, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0xfe, 0xc0, 0xe0, 0x38, 0x0c, 0x04, 
	0x00, 0xf8, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xf8, 0x00, 0x04, 0x08, 0xf0, 
	0x08, 0x04, 0x04, 0x08, 0x10, 0x08, 0x04, 0x04, 0x08, 0xf0, 0x00, 0x04, 0x08, 0xf0, 
	0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 0xf0, 0x00, 0x10, 0x88, 0x88, 0x88, 0x88, 
	0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x78, 0x60, 0x78, 0x0f, 0x01, 0x00, 0x00, 
	0x1e, 0x21, 0x41, 0x41, 0x41, 0x21, 0xde, 0x80, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 
	0x03, 0x0e, 0x38, 0xe0, 0x00, 0x7f, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7f, 
	0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x0f, 
	0x10, 0x20, 0x20, 0x20, 0x10, 0xe0, 0xc0, 0x00, // "สวีเดน2"

	0x06, 0x06, 0xff, 0xff, 0x06, 0x06, 0x20, 0x10, 0x8c, 0x8c, 0x8c, 0x8c, 0xf0, 0x00, 
	0x00, 0x00, 0xe0, 0x10, 0x18, 0x08, 0x08, 0x08, 0x08, 0x10, 0x00, 0xfe, 0xc0, 0xe0, 
	0x38, 0x0c, 0x04, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x1e, 0x0f, 0x10, 0x20, 
	0x20, 0x20, 0x90, 0xe0, 0x40, 0x00, 0x1f, 0x20, 0x60, 0x40, 0x40, 0x40, 0x40, 0x20, 
	0x00, 0xff, 0x00, 0x03, 0x0e, 0x38, 0xe0, 0x00, // "สวีเดน3"

	0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0x00, 0xe0, 0x58, 0x44, 0x44, 
	0x44, 0x44, 0x44, 0x48, 0x30, 0x00, 0x00, 0x00, 0xfb, 0xfb, 0x00, 0xff, 0xff, 0x01,
	0x01, 0x01, 0x01, 0x01, 0xff, 0xff, 0x00, 0x0f, 0x30, 0x40, 0x40, 0x40, 0x40, 0x40, 
	0x40, 0x30, 0x00, 0xc0, 0xe0, 0x7f, 0x3f, 0x00, // "สวีเดน4"

	0xff, 0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0xc0, 0x00, 0x10, 0x8c, 0x8c, 0x8c, 0x8c, 
	0xf0, 0x00, 0x00, 0x00, 0x38, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x38, 0x00, 
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x0f, 0x10, 0x20, 0x20, 0x20, 
	0x90, 0xe0, 0x40, 0x00, 0x00, 0x01, 0xf,  0x78,  0xe0, 0x78, 0xf, 0x01, 0x00, 0x00, // "สวีเดน5"

	0xfc, 0x04, 0x04, 0x04, 0x04, 0xfc, 0x00, 0x00, 0xfc, 0x08, 0x08, 0x08, 0xf0, 0x00, 
	0x00, 0xfc, 0x00, 0x00, 0xc0, 0x60, 0x18, 0xfc, 0x00, 0x00, 0xfc, 0x44, 0x44, 0x44, 
	0xb8, 0x00, 0x00, 0x04, 0x04, 0xfc, 0x04, 0x04, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 
	0x0f, 0x00, 0x00, 0x7f, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x06, 0x03, 0x01, 
	0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 
	0x0f, 0x00, 0x00, 0x00, // "russia1"

	0xfc, 0x08, 0x70, 0xc0, 0x70, 0x08, 0xfc, 0x00, 0x00, 0xf0, 0x18, 0x0c, 0x04, 0x04, 
	0x04, 0x0c, 0x18, 0xf0, 0x00, 0x00, 0xfc, 0x08, 0x08, 0x08, 0xf0, 0x00, 0x00, 0xf0, 
	0x98, 0x88, 0x88, 0x98, 0xf0, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 
	0x00, 0x03, 0x06, 0x0c, 0x08, 0x08, 0x08, 0x0c, 0x06, 0x03, 0x00, 0x00, 0x7f, 0x02, 
	0x02, 0x01, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x08, 0x04, 0x00, // "russia2"

	0xf0, 0x18, 0x0c, 0x04, 0x04, 0x04, 0x08, 0x00, 0x00, 0xfc, 0x04, 0x04, 0x04, 0x04, 
	0xfc, 0x00, 0x00, 0x08, 0x84, 0x44, 0x44, 0x44, 0xf8, 0x00, 0x00, 0x04, 0x04, 0xfc, 
	0x04, 0x04, 0x00, 0x00, 0xfc, 0x80, 0x80, 0x80, 0x00, 0x00, 0x03, 0x06, 0x0c, 0x08, 
	0x08, 0x08, 0x04, 0x00, 0x00, 0xf, 0x00, 0x00, 0x00, 0x00, 0xf, 0x00, 0x00, 0x03, 
	0xc, 0x08, 0x08, 0x04, 0xf, 0x00, 0x00, 0x00, 0x00, 0xf, 0x00, 0x00, 0x00, 0x00, 
	0xf, 0x08, 0x08, 0x08, 0x07, 0x00, // "russia3"

	0x00, 0x18, 0x64, 0xc4, 0x44, 0x44, 0xfc, 0x00, 0x00, 0x88, 0x84, 0x84, 0x84, 0x84, 
	0x84, 0x84, 0x78, 0x00, 0x00, 0xfc, 0x80, 0x80, 0x80, 0x00, 0x00, 0xfc, 0x00, 0x00, 
	0xfc, 0x40, 0xa0, 0x10, 0x08, 0x04, 0x00, 0x00, 0x08, 0x04, 0x03, 0x01, 0x00, 0x00, 
	0xf, 0x00, 0x00, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0xf, 
	0x08, 0x08, 0x08, 0x07, 0x00, 0xf, 0x00, 0x00, 0xf, 0x00, 0x00, 0x01, 0x02, 0x04, 
	0x08, 0x00, // "russia4"

	0xfc, 0x40, 0x40, 0x40, 0x40, 0xfc, 0x00, 0x00, 0x08, 0x84, 0x44, 0x44, 0x44, 0xf8, 
	0x00, 0x00, 0xf0, 0x18, 0xc, 0x04, 0x04, 0x04, 0x08, 0x00, 0x00, 0xf0, 0x98, 0x88, 
	0x88, 0x98, 0xf0, 0x00, 0x00, 0xfc, 0x40, 0xa0, 0x10, 0x08, 0x04, 0x00, 0x00, 0x00, 
	0xf0, 0x18, 0xc, 0x04, 0x04, 0x04, 0xc, 0x18, 0xf0, 0x00, 0x00, 0xfc, 0x08, 0x70, 
	0xc0, 0x70, 0x08, 0xfc, 0x00, 0x00, 0xf0, 0x18, 0xc, 0x04, 0x04, 0x04, 0xc, 0x18, 
	0xf0, 0x00, 0x00, 0xf0, 0x98, 0x88, 0x88, 0x98, 0xf0, 0x00, 0xf, 0x00, 0x00, 0x00, 
	0x00, 0xf, 0x00, 0x00, 0x03, 0xc, 0x08, 0x08, 0x04, 0xf, 0x00, 0x00, 0x03, 0x06, 
	0xc, 0x08, 0x08, 0x08, 0x04, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x08, 0x04, 0x00, 
	0x00, 0xf, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x03, 0x06, 0xc, 0x08, 
	0x08, 0x08, 0xc, 0x06, 0x03, 0x00, 0x00, 0xf, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf, 
	0x00, 0x00, 0x03, 0x06, 0xc, 0x08, 0x08, 0x08, 0xc, 0x06, 0x03, 0x00, 0x00, 0x07, 
	0x08, 0x08, 0x08, 0x08, 0x04, 0x00, // "russia5"

	0x00, 0xfc, 0xc, 0x14, 0x14, 0x24, 0x24, 0x44, 0xf4, 0x14, 0xf4, 0x44, 0x24, 0x24, 
	0x14, 0x14, 0xc, 0xfc, 0x00, 0x00, 0x7f, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x41, 
	0x41, 0x41, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7f, 0x00, // "emo1"

	0x00, 0x00, 0x40, 0xcc, 0xce, 0xc6, 0x06, 0x2e, 0x3c, 0x38, 0x3c, 0x00, 0x00, 0xc0,
	0xc0, 0x80, 0x00, 0x00, 0x1e, 0x3f, 0x33, 0x31, 0x03, 0x00, 0x00, 0x3c, 0x1c, 0x3c, 
	0x74, 0x60, 0x60, 0x7f, 0x3f, 0x00, // "emo2"

	0x00, 0xf0, 0x28, 0x74, 0x7a, 0xf9, 0x61, 0x81, 0x81, 0x61, 0xf9, 0xfa, 0x74, 0x28, 
	0xf0, 0x00, 0x00, 0xf, 0x10, 0x20, 0x40, 0xb0, 0xb8, 0xbd, 0xbd, 0xb8, 0xb0, 0x40, 
	0x20, 0x10, 0xf, 0x00, // "emo3"

	0x00, 0xf0, 0x08, 0x04, 0xf2, 0xf1, 0xf1, 0x01, 0x01, 0xf1, 0xf1, 0xf2, 0x04, 0x08, 
	0xf0, 0x00, 0x00, 0xf, 0x10, 0x20, 0x41, 0x91, 0x91, 0x90, 0x90, 0x91, 0x91, 0x41, 
	0x20, 0x10, 0xf, 0x00, // "emo4"
	0x00, 0xf8, 0x8c, 0x06, 0x03, 0x01, 0x01, 0x01, 0x02, 0x04, 0x04, 0x02, 0x01, 0x01, 
	0x01, 0x03, 0x06, 0x8c, 0xf8, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x30, 
	0x60, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x00, 0x00, // "emo5"
};

#endif
