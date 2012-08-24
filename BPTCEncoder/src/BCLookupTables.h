//--------------------------------------------------------------------------------------
// Copyright 2011 Intel Corporation
// All Rights Reserved
//
// Permission is granted to use, copy, distribute and prepare derivative works of this
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  THIS SOFTWARE IS PROVIDED "AS IS."
// INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, AND ALL LIABILITY,
// INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES, FOR THE USE OF THIS SOFTWARE,
// INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY RIGHTS, AND INCLUDING THE
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.
//
//--------------------------------------------------------------------------------------

// Each value from 0 to 255 can be exactly interpolated between two other values
// with 7 bit precision. BC7 Mode 5 gives us this precision, so we can use look-up
// tables to speed up this precision by allowing every value to be 1/3 of the way
// between the two colors specified.
/*
	UINT nbits = 7;
	UINT lastNum = -1;
	UINT vals[255];
	UINT valIdx = 0;
	for(UINT i = 0; i < 256; i++) {
		UINT num = (i >> (8 - nbits));
		num <<= (8-nbits);
		num |= i >> nbits;

		if(num != lastNum) {
			lastNum = num;
			vals[valIdx++] = num;
		}
	}

	for(UINT i = 0; i < 256; i++) {

		UINT mindist = 0xFFFFFFFF;
		UINT minj = 0, mink = 0;

		UINT tableEntry[2] = { 0, 0 };

		mindist = 0xFFFFFFFF;
		minj = 0, mink = 0;

		for(UINT j = 0; j < valIdx; j++) {
			for(UINT k = 0; k < valIdx ; k++) {

				UINT combo = (43 * vals[j] + 21 * vals[k] + 32) >> 6;
				UINT dist = ((i > combo) ? i - combo : combo - i);
				if( dist < mindist )
				{
					mindist = dist;
					minj = j;
					mink = k;
				}
			}
		}

		assert(mindist == 0);

		tableEntry[0] = vals[minj];
		tableEntry[1] = vals[mink];

		wchar_t tableEntryStr[256];
		swprintf(tableEntryStr, 256, L"{ 0x%02x, 0x%02x },\n", 
			tableEntry[0] >> (8 - nbits),
			tableEntry[1] >> (8 - nbits)
		);
		OutputDebugString(tableEntryStr);
	}
*/
static unsigned char Optimal7CompressBC7Mode5[256][2] = {
	{ 0x00, 0x00 },
	{ 0x00, 0x01 },
	{ 0x00, 0x03 },
	{ 0x00, 0x04 },
	{ 0x00, 0x06 },
	{ 0x00, 0x07 },
	{ 0x00, 0x09 },
	{ 0x00, 0x0a },
	{ 0x00, 0x0c },
	{ 0x00, 0x0d },
	{ 0x00, 0x0f },
	{ 0x00, 0x10 },
	{ 0x00, 0x12 },
	{ 0x00, 0x14 },
	{ 0x00, 0x15 },
	{ 0x00, 0x17 },
	{ 0x00, 0x18 },
	{ 0x00, 0x1a },
	{ 0x00, 0x1b },
	{ 0x00, 0x1d },
	{ 0x00, 0x1e },
	{ 0x00, 0x20 },
	{ 0x00, 0x21 },
	{ 0x00, 0x23 },
	{ 0x00, 0x24 },
	{ 0x00, 0x26 },
	{ 0x00, 0x27 },
	{ 0x00, 0x29 },
	{ 0x00, 0x2a },
	{ 0x00, 0x2c },
	{ 0x00, 0x2d },
	{ 0x00, 0x2f },
	{ 0x00, 0x30 },
	{ 0x00, 0x32 },
	{ 0x00, 0x34 },
	{ 0x00, 0x35 },
	{ 0x00, 0x37 },
	{ 0x00, 0x38 },
	{ 0x00, 0x3a },
	{ 0x00, 0x3b },
	{ 0x00, 0x3d },
	{ 0x00, 0x3e },
	{ 0x00, 0x40 },
	{ 0x00, 0x41 },
	{ 0x00, 0x42 },
	{ 0x00, 0x44 },
	{ 0x00, 0x45 },
	{ 0x00, 0x47 },
	{ 0x00, 0x48 },
	{ 0x00, 0x4a },
	{ 0x00, 0x4b },
	{ 0x00, 0x4d },
	{ 0x00, 0x4e },
	{ 0x00, 0x50 },
	{ 0x00, 0x52 },
	{ 0x00, 0x53 },
	{ 0x00, 0x55 },
	{ 0x00, 0x56 },
	{ 0x00, 0x58 },
	{ 0x00, 0x59 },
	{ 0x00, 0x5b },
	{ 0x00, 0x5c },
	{ 0x00, 0x5e },
	{ 0x00, 0x5f },
	{ 0x00, 0x61 },
	{ 0x00, 0x62 },
	{ 0x00, 0x64 },
	{ 0x00, 0x65 },
	{ 0x00, 0x67 },
	{ 0x00, 0x68 },
	{ 0x00, 0x6a },
	{ 0x00, 0x6b },
	{ 0x00, 0x6d },
	{ 0x00, 0x6e },
	{ 0x00, 0x70 },
	{ 0x00, 0x72 },
	{ 0x00, 0x73 },
	{ 0x00, 0x75 },
	{ 0x00, 0x76 },
	{ 0x00, 0x78 },
	{ 0x00, 0x79 },
	{ 0x00, 0x7b },
	{ 0x00, 0x7c },
	{ 0x00, 0x7e },
	{ 0x00, 0x7f },
	{ 0x01, 0x7f },
	{ 0x02, 0x7e },
	{ 0x03, 0x7e },
	{ 0x03, 0x7f },
	{ 0x04, 0x7f },
	{ 0x05, 0x7e },
	{ 0x06, 0x7e },
	{ 0x06, 0x7f },
	{ 0x07, 0x7f },
	{ 0x08, 0x7e },
	{ 0x09, 0x7e },
	{ 0x09, 0x7f },
	{ 0x0a, 0x7f },
	{ 0x0b, 0x7e },
	{ 0x0c, 0x7e },
	{ 0x0c, 0x7f },
	{ 0x0d, 0x7f },
	{ 0x0e, 0x7e },
	{ 0x0f, 0x7d },
	{ 0x0f, 0x7f },
	{ 0x10, 0x7e },
	{ 0x11, 0x7e },
	{ 0x11, 0x7f },
	{ 0x12, 0x7f },
	{ 0x13, 0x7e },
	{ 0x14, 0x7e },
	{ 0x14, 0x7f },
	{ 0x15, 0x7f },
	{ 0x16, 0x7e },
	{ 0x17, 0x7e },
	{ 0x17, 0x7f },
	{ 0x18, 0x7f },
	{ 0x19, 0x7e },
	{ 0x1a, 0x7e },
	{ 0x1a, 0x7f },
	{ 0x1b, 0x7f },
	{ 0x1c, 0x7e },
	{ 0x1d, 0x7e },
	{ 0x1d, 0x7f },
	{ 0x1e, 0x7f },
	{ 0x1f, 0x7e },
	{ 0x20, 0x7e },
	{ 0x20, 0x7f },
	{ 0x21, 0x7f },
	{ 0x22, 0x7e },
	{ 0x23, 0x7e },
	{ 0x23, 0x7f },
	{ 0x24, 0x7f },
	{ 0x25, 0x7e },
	{ 0x26, 0x7e },
	{ 0x26, 0x7f },
	{ 0x27, 0x7f },
	{ 0x28, 0x7e },
	{ 0x29, 0x7e },
	{ 0x29, 0x7f },
	{ 0x2a, 0x7f },
	{ 0x2b, 0x7e },
	{ 0x2c, 0x7e },
	{ 0x2c, 0x7f },
	{ 0x2d, 0x7f },
	{ 0x2e, 0x7e },
	{ 0x2f, 0x7d },
	{ 0x2f, 0x7f },
	{ 0x30, 0x7e },
	{ 0x31, 0x7e },
	{ 0x31, 0x7f },
	{ 0x32, 0x7f },
	{ 0x33, 0x7e },
	{ 0x34, 0x7e },
	{ 0x34, 0x7f },
	{ 0x35, 0x7f },
	{ 0x36, 0x7e },
	{ 0x37, 0x7e },
	{ 0x37, 0x7f },
	{ 0x38, 0x7f },
	{ 0x39, 0x7e },
	{ 0x3a, 0x7e },
	{ 0x3a, 0x7f },
	{ 0x3b, 0x7f },
	{ 0x3c, 0x7e },
	{ 0x3d, 0x7e },
	{ 0x3d, 0x7f },
	{ 0x3e, 0x7f },
	{ 0x3f, 0x7e },
	{ 0x40, 0x7d },
	{ 0x40, 0x7e },
	{ 0x41, 0x7e },
	{ 0x41, 0x7f },
	{ 0x42, 0x7f },
	{ 0x43, 0x7e },
	{ 0x44, 0x7e },
	{ 0x44, 0x7f },
	{ 0x45, 0x7f },
	{ 0x46, 0x7e },
	{ 0x47, 0x7e },
	{ 0x47, 0x7f },
	{ 0x48, 0x7f },
	{ 0x49, 0x7e },
	{ 0x4a, 0x7e },
	{ 0x4a, 0x7f },
	{ 0x4b, 0x7f },
	{ 0x4c, 0x7e },
	{ 0x4d, 0x7d },
	{ 0x4d, 0x7f },
	{ 0x4e, 0x7e },
	{ 0x4f, 0x7e },
	{ 0x4f, 0x7f },
	{ 0x50, 0x7f },
	{ 0x51, 0x7e },
	{ 0x52, 0x7e },
	{ 0x52, 0x7f },
	{ 0x53, 0x7f },
	{ 0x54, 0x7e },
	{ 0x55, 0x7e },
	{ 0x55, 0x7f },
	{ 0x56, 0x7f },
	{ 0x57, 0x7e },
	{ 0x58, 0x7e },
	{ 0x58, 0x7f },
	{ 0x59, 0x7f },
	{ 0x5a, 0x7e },
	{ 0x5b, 0x7e },
	{ 0x5b, 0x7f },
	{ 0x5c, 0x7f },
	{ 0x5d, 0x7e },
	{ 0x5e, 0x7e },
	{ 0x5e, 0x7f },
	{ 0x5f, 0x7f },
	{ 0x60, 0x7e },
	{ 0x61, 0x7e },
	{ 0x61, 0x7f },
	{ 0x62, 0x7f },
	{ 0x63, 0x7e },
	{ 0x64, 0x7e },
	{ 0x64, 0x7f },
	{ 0x65, 0x7f },
	{ 0x66, 0x7e },
	{ 0x67, 0x7e },
	{ 0x67, 0x7f },
	{ 0x68, 0x7f },
	{ 0x69, 0x7e },
	{ 0x6a, 0x7e },
	{ 0x6a, 0x7f },
	{ 0x6b, 0x7f },
	{ 0x6c, 0x7e },
	{ 0x6d, 0x7d },
	{ 0x6d, 0x7f },
	{ 0x6e, 0x7e },
	{ 0x6f, 0x7e },
	{ 0x6f, 0x7f },
	{ 0x70, 0x7f },
	{ 0x71, 0x7e },
	{ 0x72, 0x7e },
	{ 0x72, 0x7f },
	{ 0x73, 0x7f },
	{ 0x74, 0x7e },
	{ 0x75, 0x7e },
	{ 0x75, 0x7f },
	{ 0x76, 0x7f },
	{ 0x77, 0x7e },
	{ 0x78, 0x7e },
	{ 0x78, 0x7f },
	{ 0x79, 0x7f },
	{ 0x7a, 0x7e },
	{ 0x7b, 0x7e },
	{ 0x7b, 0x7f },
	{ 0x7c, 0x7f },
	{ 0x7d, 0x7e },
	{ 0x7e, 0x7e },
	{ 0x7e, 0x7f },
	{ 0x7f, 0x7f }
};

// For each value, we give the best possible compression range for that value with 5 bits.
// The first value says whether or not it's
// 1 - the midpoint of two other values, or 
// 0 - 1/3 of the way in between two other values.
// If the first value is 1 or 2 then the last two values are the range between which the
// value should be interpolated. If the first value is 2, then it should be interpolated
// one third of the way from the second to third value...
//
// The following tables were generated with the following program:
/*
 	UINT nbits = 5;
	UINT lastNum = -1;
	UINT vals[255];
	UINT valIdx = 0;
	for(UINT i = 0; i < 256; i++) {
		UINT num = (i >> (8 - nbits));
		num <<= (8-nbits);
		num |= i >> nbits;

		if(num != lastNum) {
			lastNum = num;
			vals[valIdx++] = num;
		}
	}

	for(UINT i = 0; i < 256; i++) {

		UINT mindist = 0xFFFFFFFF;
		UINT minj = 0, mink = 0;

		UINT tableEntry[2][4] = { {1, 0, 0, 0xFFFFFFFF}, {0, 0, 0, 0xFFFFFFFF} };

		for(UINT j = 0; j < valIdx; j++) {
			for(UINT k = j; k < valIdx ; k++) {

				UINT combo = (vals[j] + vals[k]) / 2;
				UINT dist = ((i > combo) ? i - combo : combo - i);
				if( dist < mindist )
				{
					mindist = dist;
					minj = j;
					mink = k;
				}
			}
		}

		tableEntry[0][1] = vals[minj];
		tableEntry[0][2] = vals[mink];
		tableEntry[0][3] = mindist;

		mindist = 0xFFFFFFFF;
		minj = 0, mink = 0;

		for(UINT j = 0; j < valIdx; j++) {
			for(UINT k = j; k < valIdx ; k++) {

				UINT combo = (2 * vals[j] + vals[k]) / 3;
				UINT dist = ((i > combo) ? i - combo : combo - i);
				if( dist < mindist )
				{
					mindist = dist;
					minj = j;
					mink = k;
				}
			}
		}

		tableEntry[1][1] = vals[minj];
		tableEntry[1][2] = vals[mink];
		tableEntry[1][3] = mindist;

		wchar_t tableEntryStr[256];
		if(tableEntry[1][3] > tableEntry[0][3]) {
			swprintf(tableEntryStr, 256, L"{ { %d, 0x%02x, 0x%02x }, { %d, 0x%02x, 0x%02x } },\n", 
				tableEntry[0][0],
				tableEntry[0][1] >> (8 - nbits),
				tableEntry[0][2] >> (8 - nbits),
				tableEntry[1][0],
				tableEntry[1][1] >> (8 - nbits),
				tableEntry[1][2] >> (8 - nbits)
			);
		}
		else {
			swprintf(tableEntryStr, 256, L"{ { %d, 0x%02x, 0x%02x }, { %d, 0x%02x, 0x%02x } },\n", 
				tableEntry[1][0],
				tableEntry[1][1] >> (8 - nbits),
				tableEntry[1][2] >> (8 - nbits),
				tableEntry[0][0],
				tableEntry[0][1] >> (8 - nbits),
				tableEntry[0][2] >> (8 - nbits)
			);
		}
		OutputDebugString(tableEntryStr);
	}
*/
static unsigned char Optimal5CompressDXT1[256][2][3] = {
	{ { 0, 0x00, 0x00 }, { 1, 0x00, 0x00 } },
	{ { 0, 0x00, 0x00 }, { 1, 0x00, 0x00 } },
	{ { 0, 0x00, 0x01 }, { 1, 0x00, 0x00 } },
	{ { 0, 0x00, 0x01 }, { 1, 0x00, 0x01 } },
	{ { 1, 0x00, 0x01 }, { 0, 0x00, 0x02 } },
	{ { 0, 0x00, 0x02 }, { 1, 0x00, 0x01 } },
	{ { 0, 0x00, 0x02 }, { 1, 0x00, 0x01 } },
	{ { 0, 0x00, 0x03 }, { 1, 0x00, 0x02 } },
	{ { 0, 0x00, 0x03 }, { 1, 0x00, 0x02 } },
	{ { 0, 0x00, 0x03 }, { 1, 0x00, 0x02 } },
	{ { 0, 0x01, 0x02 }, { 1, 0x00, 0x02 } },
	{ { 0, 0x00, 0x04 }, { 1, 0x00, 0x03 } },
	{ { 1, 0x00, 0x03 }, { 0, 0x00, 0x04 } },
	{ { 0, 0x00, 0x05 }, { 1, 0x00, 0x03 } },
	{ { 0, 0x00, 0x05 }, { 1, 0x00, 0x03 } },
	{ { 0, 0x00, 0x06 }, { 1, 0x00, 0x04 } },
	{ { 0, 0x00, 0x06 }, { 1, 0x00, 0x04 } },
	{ { 0, 0x00, 0x06 }, { 1, 0x00, 0x04 } },
	{ { 0, 0x02, 0x03 }, { 1, 0x00, 0x04 } },
	{ { 0, 0x00, 0x07 }, { 1, 0x00, 0x05 } },
	{ { 1, 0x00, 0x05 }, { 0, 0x00, 0x07 } },
	{ { 0, 0x01, 0x06 }, { 1, 0x00, 0x05 } },
	{ { 0, 0x00, 0x08 }, { 1, 0x00, 0x05 } },
	{ { 0, 0x00, 0x08 }, { 1, 0x00, 0x06 } },
	{ { 0, 0x00, 0x09 }, { 1, 0x00, 0x06 } },
	{ { 0, 0x00, 0x09 }, { 1, 0x00, 0x06 } },
	{ { 0, 0x00, 0x0a }, { 1, 0x00, 0x06 } },
	{ { 0, 0x00, 0x0a }, { 1, 0x00, 0x07 } },
	{ { 1, 0x00, 0x07 }, { 0, 0x00, 0x0a } },
	{ { 0, 0x02, 0x07 }, { 1, 0x00, 0x07 } },
	{ { 0, 0x00, 0x0b }, { 1, 0x00, 0x07 } },
	{ { 0, 0x00, 0x0b }, { 1, 0x01, 0x07 } },
	{ { 0, 0x01, 0x0a }, { 1, 0x01, 0x07 } },
	{ { 0, 0x00, 0x0c }, { 1, 0x00, 0x08 } },
	{ { 0, 0x00, 0x0c }, { 1, 0x00, 0x08 } },
	{ { 0, 0x00, 0x0d }, { 1, 0x02, 0x07 } },
	{ { 1, 0x02, 0x07 }, { 0, 0x00, 0x0d } },
	{ { 1, 0x00, 0x09 }, { 0, 0x00, 0x0e } },
	{ { 0, 0x00, 0x0e }, { 1, 0x00, 0x09 } },
	{ { 0, 0x00, 0x0e }, { 1, 0x03, 0x07 } },
	{ { 0, 0x02, 0x0b }, { 1, 0x03, 0x07 } },
	{ { 0, 0x00, 0x0f }, { 1, 0x00, 0x0a } },
	{ { 0, 0x00, 0x0f }, { 1, 0x00, 0x0a } },
	{ { 0, 0x01, 0x0e }, { 1, 0x00, 0x0a } },
	{ { 0, 0x00, 0x10 }, { 1, 0x00, 0x0b } },
	{ { 1, 0x00, 0x0b }, { 0, 0x00, 0x10 } },
	{ { 0, 0x00, 0x11 }, { 1, 0x00, 0x0b } },
	{ { 0, 0x00, 0x11 }, { 1, 0x00, 0x0b } },
	{ { 0, 0x00, 0x12 }, { 1, 0x00, 0x0c } },
	{ { 0, 0x00, 0x12 }, { 1, 0x00, 0x0c } },
	{ { 0, 0x00, 0x12 }, { 1, 0x00, 0x0c } },
	{ { 0, 0x02, 0x0f }, { 1, 0x00, 0x0c } },
	{ { 0, 0x00, 0x13 }, { 1, 0x00, 0x0d } },
	{ { 1, 0x00, 0x0d }, { 0, 0x00, 0x13 } },
	{ { 0, 0x01, 0x12 }, { 1, 0x00, 0x0d } },
	{ { 0, 0x00, 0x14 }, { 1, 0x00, 0x0d } },
	{ { 0, 0x00, 0x14 }, { 1, 0x00, 0x0e } },
	{ { 0, 0x00, 0x15 }, { 1, 0x00, 0x0e } },
	{ { 0, 0x00, 0x15 }, { 1, 0x00, 0x0e } },
	{ { 0, 0x00, 0x16 }, { 1, 0x00, 0x0e } },
	{ { 0, 0x00, 0x16 }, { 1, 0x00, 0x0f } },
	{ { 1, 0x00, 0x0f }, { 0, 0x00, 0x16 } },
	{ { 0, 0x02, 0x13 }, { 1, 0x00, 0x0f } },
	{ { 0, 0x00, 0x17 }, { 1, 0x00, 0x0f } },
	{ { 0, 0x00, 0x17 }, { 1, 0x01, 0x0f } },
	{ { 0, 0x01, 0x16 }, { 1, 0x01, 0x0f } },
	{ { 0, 0x00, 0x18 }, { 1, 0x00, 0x10 } },
	{ { 0, 0x00, 0x18 }, { 1, 0x00, 0x10 } },
	{ { 0, 0x00, 0x19 }, { 1, 0x02, 0x0f } },
	{ { 1, 0x02, 0x0f }, { 0, 0x00, 0x19 } },
	{ { 1, 0x00, 0x11 }, { 0, 0x00, 0x1a } },
	{ { 0, 0x00, 0x1a }, { 1, 0x00, 0x11 } },
	{ { 0, 0x00, 0x1a }, { 1, 0x03, 0x0f } },
	{ { 0, 0x02, 0x17 }, { 1, 0x03, 0x0f } },
	{ { 0, 0x00, 0x1b }, { 1, 0x00, 0x12 } },
	{ { 0, 0x00, 0x1b }, { 1, 0x00, 0x12 } },
	{ { 0, 0x01, 0x1a }, { 1, 0x00, 0x12 } },
	{ { 0, 0x00, 0x1c }, { 1, 0x00, 0x13 } },
	{ { 1, 0x00, 0x13 }, { 0, 0x00, 0x1c } },
	{ { 0, 0x00, 0x1d }, { 1, 0x00, 0x13 } },
	{ { 0, 0x00, 0x1d }, { 1, 0x00, 0x13 } },
	{ { 0, 0x00, 0x1e }, { 1, 0x00, 0x14 } },
	{ { 0, 0x00, 0x1e }, { 1, 0x00, 0x14 } },
	{ { 0, 0x00, 0x1e }, { 1, 0x00, 0x14 } },
	{ { 0, 0x02, 0x1b }, { 1, 0x00, 0x14 } },
	{ { 0, 0x00, 0x1f }, { 1, 0x00, 0x15 } },
	{ { 1, 0x00, 0x15 }, { 0, 0x00, 0x1f } },
	{ { 0, 0x01, 0x1e }, { 1, 0x00, 0x15 } },
	{ { 0, 0x04, 0x18 }, { 1, 0x00, 0x15 } },
	{ { 0, 0x01, 0x1f }, { 1, 0x00, 0x16 } },
	{ { 0, 0x01, 0x1f }, { 1, 0x00, 0x16 } },
	{ { 0, 0x01, 0x1f }, { 1, 0x00, 0x16 } },
	{ { 0, 0x02, 0x1e }, { 1, 0x00, 0x16 } },
	{ { 0, 0x02, 0x1e }, { 1, 0x00, 0x17 } },
	{ { 1, 0x00, 0x17 }, { 0, 0x02, 0x1e } },
	{ { 0, 0x02, 0x1f }, { 1, 0x00, 0x17 } },
	{ { 0, 0x04, 0x1b }, { 1, 0x00, 0x17 } },
	{ { 0, 0x03, 0x1e }, { 1, 0x01, 0x17 } },
	{ { 0, 0x03, 0x1e }, { 1, 0x01, 0x17 } },
	{ { 0, 0x04, 0x1c }, { 1, 0x00, 0x18 } },
	{ { 0, 0x03, 0x1f }, { 1, 0x00, 0x18 } },
	{ { 0, 0x03, 0x1f }, { 1, 0x02, 0x17 } },
	{ { 1, 0x02, 0x17 }, { 0, 0x03, 0x1f } },
	{ { 1, 0x00, 0x19 }, { 0, 0x04, 0x1e } },
	{ { 0, 0x04, 0x1e }, { 1, 0x00, 0x19 } },
	{ { 0, 0x04, 0x1e }, { 1, 0x03, 0x17 } },
	{ { 0, 0x06, 0x1b }, { 1, 0x03, 0x17 } },
	{ { 0, 0x04, 0x1f }, { 1, 0x00, 0x1a } },
	{ { 0, 0x04, 0x1f }, { 1, 0x00, 0x1a } },
	{ { 0, 0x05, 0x1e }, { 1, 0x00, 0x1a } },
	{ { 0, 0x08, 0x18 }, { 1, 0x00, 0x1b } },
	{ { 1, 0x00, 0x1b }, { 0, 0x05, 0x1f } },
	{ { 0, 0x05, 0x1f }, { 1, 0x00, 0x1b } },
	{ { 0, 0x05, 0x1f }, { 1, 0x00, 0x1b } },
	{ { 0, 0x06, 0x1e }, { 1, 0x00, 0x1c } },
	{ { 0, 0x06, 0x1e }, { 1, 0x00, 0x1c } },
	{ { 0, 0x06, 0x1e }, { 1, 0x00, 0x1c } },
	{ { 0, 0x06, 0x1f }, { 1, 0x00, 0x1c } },
	{ { 0, 0x08, 0x1b }, { 1, 0x00, 0x1d } },
	{ { 1, 0x00, 0x1d }, { 0, 0x07, 0x1e } },
	{ { 0, 0x07, 0x1e }, { 1, 0x00, 0x1d } },
	{ { 0, 0x08, 0x1c }, { 1, 0x00, 0x1d } },
	{ { 0, 0x07, 0x1f }, { 1, 0x00, 0x1e } },
	{ { 0, 0x07, 0x1f }, { 1, 0x00, 0x1e } },
	{ { 0, 0x07, 0x1f }, { 1, 0x00, 0x1e } },
	{ { 0, 0x08, 0x1e }, { 1, 0x00, 0x1e } },
	{ { 0, 0x08, 0x1e }, { 1, 0x00, 0x1f } },
	{ { 1, 0x00, 0x1f }, { 0, 0x08, 0x1e } },
	{ { 0, 0x0a, 0x1b }, { 1, 0x00, 0x1f } },
	{ { 0, 0x08, 0x1f }, { 1, 0x00, 0x1f } },
	{ { 0, 0x08, 0x1f }, { 1, 0x01, 0x1f } },
	{ { 0, 0x09, 0x1e }, { 1, 0x01, 0x1f } },
	{ { 0, 0x0c, 0x18 }, { 1, 0x04, 0x1c } },
	{ { 0, 0x09, 0x1f }, { 1, 0x04, 0x1c } },
	{ { 0, 0x09, 0x1f }, { 1, 0x02, 0x1f } },
	{ { 1, 0x02, 0x1f }, { 0, 0x09, 0x1f } },
	{ { 1, 0x04, 0x1d }, { 0, 0x0a, 0x1e } },
	{ { 0, 0x0a, 0x1e }, { 1, 0x04, 0x1d } },
	{ { 0, 0x0a, 0x1e }, { 1, 0x03, 0x1f } },
	{ { 0, 0x0a, 0x1f }, { 1, 0x03, 0x1f } },
	{ { 0, 0x0c, 0x1b }, { 1, 0x04, 0x1e } },
	{ { 0, 0x0b, 0x1e }, { 1, 0x04, 0x1e } },
	{ { 0, 0x0b, 0x1e }, { 1, 0x04, 0x1e } },
	{ { 0, 0x0c, 0x1c }, { 1, 0x04, 0x1f } },
	{ { 1, 0x04, 0x1f }, { 0, 0x0b, 0x1f } },
	{ { 0, 0x0b, 0x1f }, { 1, 0x04, 0x1f } },
	{ { 0, 0x0b, 0x1f }, { 1, 0x04, 0x1f } },
	{ { 0, 0x0c, 0x1e }, { 1, 0x05, 0x1f } },
	{ { 0, 0x0c, 0x1e }, { 1, 0x05, 0x1f } },
	{ { 0, 0x0c, 0x1e }, { 1, 0x05, 0x1f } },
	{ { 0, 0x0e, 0x1b }, { 1, 0x05, 0x1f } },
	{ { 0, 0x0c, 0x1f }, { 1, 0x06, 0x1f } },
	{ { 1, 0x06, 0x1f }, { 0, 0x0c, 0x1f } },
	{ { 0, 0x0d, 0x1e }, { 1, 0x06, 0x1f } },
	{ { 0, 0x10, 0x18 }, { 1, 0x06, 0x1f } },
	{ { 0, 0x0d, 0x1f }, { 1, 0x07, 0x1f } },
	{ { 0, 0x0d, 0x1f }, { 1, 0x07, 0x1f } },
	{ { 0, 0x0d, 0x1f }, { 1, 0x07, 0x1f } },
	{ { 0, 0x0e, 0x1e }, { 1, 0x07, 0x1f } },
	{ { 0, 0x0e, 0x1e }, { 1, 0x08, 0x1f } },
	{ { 1, 0x08, 0x1f }, { 0, 0x0e, 0x1e } },
	{ { 0, 0x0e, 0x1f }, { 1, 0x08, 0x1f } },
	{ { 0, 0x10, 0x1b }, { 1, 0x08, 0x1f } },
	{ { 0, 0x0f, 0x1e }, { 1, 0x09, 0x1f } },
	{ { 0, 0x0f, 0x1e }, { 1, 0x09, 0x1f } },
	{ { 0, 0x10, 0x1c }, { 1, 0x0c, 0x1c } },
	{ { 0, 0x0f, 0x1f }, { 1, 0x0c, 0x1c } },
	{ { 0, 0x0f, 0x1f }, { 1, 0x0a, 0x1f } },
	{ { 1, 0x0a, 0x1f }, { 0, 0x0f, 0x1f } },
	{ { 1, 0x0c, 0x1d }, { 0, 0x10, 0x1e } },
	{ { 0, 0x10, 0x1e }, { 1, 0x0c, 0x1d } },
	{ { 0, 0x10, 0x1e }, { 1, 0x0b, 0x1f } },
	{ { 0, 0x12, 0x1b }, { 1, 0x0b, 0x1f } },
	{ { 0, 0x10, 0x1f }, { 1, 0x0c, 0x1e } },
	{ { 0, 0x10, 0x1f }, { 1, 0x0c, 0x1e } },
	{ { 0, 0x11, 0x1e }, { 1, 0x0c, 0x1e } },
	{ { 0, 0x14, 0x18 }, { 1, 0x0c, 0x1f } },
	{ { 1, 0x0c, 0x1f }, { 0, 0x11, 0x1f } },
	{ { 0, 0x11, 0x1f }, { 1, 0x0c, 0x1f } },
	{ { 0, 0x11, 0x1f }, { 1, 0x0c, 0x1f } },
	{ { 0, 0x12, 0x1e }, { 1, 0x0d, 0x1f } },
	{ { 0, 0x12, 0x1e }, { 1, 0x0d, 0x1f } },
	{ { 0, 0x12, 0x1e }, { 1, 0x0d, 0x1f } },
	{ { 0, 0x12, 0x1f }, { 1, 0x0d, 0x1f } },
	{ { 0, 0x14, 0x1b }, { 1, 0x0e, 0x1f } },
	{ { 1, 0x0e, 0x1f }, { 0, 0x13, 0x1e } },
	{ { 0, 0x13, 0x1e }, { 1, 0x0e, 0x1f } },
	{ { 0, 0x14, 0x1c }, { 1, 0x0e, 0x1f } },
	{ { 0, 0x13, 0x1f }, { 1, 0x0f, 0x1f } },
	{ { 0, 0x13, 0x1f }, { 1, 0x0f, 0x1f } },
	{ { 0, 0x13, 0x1f }, { 1, 0x0f, 0x1f } },
	{ { 0, 0x14, 0x1e }, { 1, 0x0f, 0x1f } },
	{ { 0, 0x14, 0x1e }, { 1, 0x10, 0x1f } },
	{ { 1, 0x10, 0x1f }, { 0, 0x14, 0x1e } },
	{ { 0, 0x16, 0x1b }, { 1, 0x10, 0x1f } },
	{ { 0, 0x14, 0x1f }, { 1, 0x10, 0x1f } },
	{ { 0, 0x14, 0x1f }, { 1, 0x11, 0x1f } },
	{ { 0, 0x15, 0x1e }, { 1, 0x11, 0x1f } },
	{ { 0, 0x18, 0x18 }, { 1, 0x14, 0x1c } },
	{ { 0, 0x15, 0x1f }, { 1, 0x14, 0x1c } },
	{ { 0, 0x15, 0x1f }, { 1, 0x12, 0x1f } },
	{ { 1, 0x12, 0x1f }, { 0, 0x15, 0x1f } },
	{ { 1, 0x14, 0x1d }, { 0, 0x16, 0x1e } },
	{ { 0, 0x16, 0x1e }, { 1, 0x14, 0x1d } },
	{ { 0, 0x16, 0x1e }, { 1, 0x13, 0x1f } },
	{ { 0, 0x16, 0x1f }, { 1, 0x13, 0x1f } },
	{ { 0, 0x18, 0x1b }, { 1, 0x14, 0x1e } },
	{ { 0, 0x17, 0x1e }, { 1, 0x14, 0x1e } },
	{ { 0, 0x17, 0x1e }, { 1, 0x14, 0x1e } },
	{ { 0, 0x18, 0x1c }, { 1, 0x14, 0x1f } },
	{ { 1, 0x14, 0x1f }, { 0, 0x17, 0x1f } },
	{ { 0, 0x17, 0x1f }, { 1, 0x14, 0x1f } },
	{ { 0, 0x17, 0x1f }, { 1, 0x14, 0x1f } },
	{ { 0, 0x18, 0x1e }, { 1, 0x15, 0x1f } },
	{ { 0, 0x18, 0x1e }, { 1, 0x15, 0x1f } },
	{ { 0, 0x18, 0x1e }, { 1, 0x15, 0x1f } },
	{ { 0, 0x1a, 0x1b }, { 1, 0x15, 0x1f } },
	{ { 0, 0x18, 0x1f }, { 1, 0x16, 0x1f } },
	{ { 1, 0x16, 0x1f }, { 0, 0x18, 0x1f } },
	{ { 0, 0x19, 0x1e }, { 1, 0x16, 0x1f } },
	{ { 0, 0x19, 0x1e }, { 1, 0x16, 0x1f } },
	{ { 0, 0x19, 0x1f }, { 1, 0x17, 0x1f } },
	{ { 0, 0x19, 0x1f }, { 1, 0x17, 0x1f } },
	{ { 0, 0x19, 0x1f }, { 1, 0x17, 0x1f } },
	{ { 0, 0x1a, 0x1e }, { 1, 0x17, 0x1f } },
	{ { 0, 0x1a, 0x1e }, { 1, 0x18, 0x1f } },
	{ { 1, 0x18, 0x1f }, { 0, 0x1a, 0x1e } },
	{ { 0, 0x1a, 0x1f }, { 1, 0x18, 0x1f } },
	{ { 0, 0x1a, 0x1f }, { 1, 0x18, 0x1f } },
	{ { 0, 0x1b, 0x1e }, { 1, 0x19, 0x1f } },
	{ { 0, 0x1b, 0x1e }, { 1, 0x19, 0x1f } },
	{ { 0, 0x1c, 0x1c }, { 1, 0x1c, 0x1c } },
	{ { 0, 0x1b, 0x1f }, { 1, 0x1c, 0x1c } },
	{ { 0, 0x1b, 0x1f }, { 1, 0x1a, 0x1f } },
	{ { 1, 0x1a, 0x1f }, { 0, 0x1b, 0x1f } },
	{ { 1, 0x1c, 0x1d }, { 0, 0x1c, 0x1e } },
	{ { 0, 0x1c, 0x1e }, { 1, 0x1c, 0x1d } },
	{ { 0, 0x1c, 0x1e }, { 1, 0x1b, 0x1f } },
	{ { 1, 0x1b, 0x1f }, { 0, 0x1c, 0x1f } },
	{ { 0, 0x1c, 0x1f }, { 1, 0x1c, 0x1e } },
	{ { 0, 0x1c, 0x1f }, { 1, 0x1c, 0x1e } },
	{ { 0, 0x1d, 0x1e }, { 1, 0x1c, 0x1e } },
	{ { 0, 0x1d, 0x1e }, { 1, 0x1c, 0x1f } },
	{ { 1, 0x1c, 0x1f }, { 0, 0x1d, 0x1f } },
	{ { 0, 0x1d, 0x1f }, { 1, 0x1c, 0x1f } },
	{ { 0, 0x1d, 0x1f }, { 1, 0x1c, 0x1f } },
	{ { 0, 0x1e, 0x1e }, { 1, 0x1d, 0x1f } },
	{ { 0, 0x1e, 0x1e }, { 1, 0x1d, 0x1f } },
	{ { 0, 0x1e, 0x1e }, { 1, 0x1d, 0x1f } },
	{ { 0, 0x1e, 0x1f }, { 1, 0x1d, 0x1f } },
	{ { 0, 0x1e, 0x1f }, { 1, 0x1e, 0x1f } },
	{ { 1, 0x1e, 0x1f }, { 0, 0x1e, 0x1f } },
	{ { 1, 0x1e, 0x1f }, { 0, 0x1e, 0x1f } },
	{ { 0, 0x1f, 0x1f }, { 1, 0x1e, 0x1f } },
	{ { 0, 0x1f, 0x1f }, { 1, 0x1f, 0x1f } },
	{ { 0, 0x1f, 0x1f }, { 1, 0x1f, 0x1f } }
};

static unsigned char Optimal6CompressDXT1[256][2][3] = {
	{ { 0, 0x00, 0x00 }, { 1, 0x00, 0x00 } },
	{ { 0, 0x00, 0x01 }, { 1, 0x00, 0x00 } },
	{ { 0, 0x00, 0x02 }, { 1, 0x00, 0x01 } },
	{ { 0, 0x00, 0x02 }, { 1, 0x00, 0x01 } },
	{ { 0, 0x00, 0x03 }, { 1, 0x00, 0x02 } },
	{ { 0, 0x00, 0x04 }, { 1, 0x00, 0x02 } },
	{ { 0, 0x00, 0x05 }, { 1, 0x00, 0x03 } },
	{ { 0, 0x00, 0x05 }, { 1, 0x00, 0x03 } },
	{ { 0, 0x00, 0x06 }, { 1, 0x00, 0x04 } },
	{ { 0, 0x00, 0x07 }, { 1, 0x00, 0x04 } },
	{ { 0, 0x00, 0x08 }, { 1, 0x00, 0x05 } },
	{ { 0, 0x00, 0x08 }, { 1, 0x00, 0x05 } },
	{ { 0, 0x00, 0x09 }, { 1, 0x00, 0x06 } },
	{ { 0, 0x00, 0x0a }, { 1, 0x00, 0x06 } },
	{ { 0, 0x00, 0x0b }, { 1, 0x00, 0x07 } },
	{ { 0, 0x00, 0x0b }, { 1, 0x00, 0x07 } },
	{ { 0, 0x00, 0x0c }, { 1, 0x00, 0x08 } },
	{ { 0, 0x00, 0x0d }, { 1, 0x00, 0x08 } },
	{ { 0, 0x00, 0x0e }, { 1, 0x00, 0x09 } },
	{ { 0, 0x00, 0x0e }, { 1, 0x00, 0x09 } },
	{ { 0, 0x00, 0x0f }, { 1, 0x00, 0x0a } },
	{ { 0, 0x00, 0x10 }, { 1, 0x00, 0x0a } },
	{ { 0, 0x01, 0x0f }, { 1, 0x00, 0x0b } },
	{ { 0, 0x00, 0x11 }, { 1, 0x00, 0x0b } },
	{ { 0, 0x00, 0x12 }, { 1, 0x00, 0x0c } },
	{ { 0, 0x00, 0x13 }, { 1, 0x00, 0x0c } },
	{ { 0, 0x03, 0x0e }, { 1, 0x00, 0x0d } },
	{ { 0, 0x00, 0x14 }, { 1, 0x00, 0x0d } },
	{ { 0, 0x00, 0x15 }, { 1, 0x00, 0x0e } },
	{ { 0, 0x00, 0x16 }, { 1, 0x00, 0x0e } },
	{ { 0, 0x04, 0x0f }, { 1, 0x00, 0x0f } },
	{ { 0, 0x00, 0x17 }, { 1, 0x00, 0x0f } },
	{ { 0, 0x00, 0x18 }, { 1, 0x00, 0x10 } },
	{ { 0, 0x00, 0x19 }, { 1, 0x00, 0x10 } },
	{ { 0, 0x06, 0x0e }, { 1, 0x00, 0x11 } },
	{ { 0, 0x00, 0x1a }, { 1, 0x00, 0x11 } },
	{ { 0, 0x00, 0x1b }, { 1, 0x00, 0x12 } },
	{ { 0, 0x00, 0x1c }, { 1, 0x00, 0x12 } },
	{ { 0, 0x07, 0x0f }, { 1, 0x00, 0x13 } },
	{ { 0, 0x00, 0x1d }, { 1, 0x00, 0x13 } },
	{ { 0, 0x00, 0x1e }, { 1, 0x00, 0x14 } },
	{ { 0, 0x00, 0x1f }, { 1, 0x00, 0x14 } },
	{ { 0, 0x09, 0x0e }, { 1, 0x00, 0x15 } },
	{ { 0, 0x00, 0x20 }, { 1, 0x00, 0x15 } },
	{ { 0, 0x00, 0x21 }, { 1, 0x00, 0x16 } },
	{ { 0, 0x02, 0x1e }, { 1, 0x00, 0x16 } },
	{ { 0, 0x00, 0x22 }, { 1, 0x00, 0x17 } },
	{ { 0, 0x00, 0x23 }, { 1, 0x00, 0x17 } },
	{ { 0, 0x00, 0x24 }, { 1, 0x00, 0x18 } },
	{ { 0, 0x03, 0x1f }, { 1, 0x00, 0x18 } },
	{ { 0, 0x00, 0x25 }, { 1, 0x00, 0x19 } },
	{ { 0, 0x00, 0x26 }, { 1, 0x00, 0x19 } },
	{ { 0, 0x00, 0x27 }, { 1, 0x00, 0x1a } },
	{ { 0, 0x05, 0x1e }, { 1, 0x00, 0x1a } },
	{ { 0, 0x00, 0x28 }, { 1, 0x00, 0x1b } },
	{ { 0, 0x00, 0x29 }, { 1, 0x00, 0x1b } },
	{ { 0, 0x00, 0x2a }, { 1, 0x00, 0x1c } },
	{ { 0, 0x06, 0x1f }, { 1, 0x00, 0x1c } },
	{ { 0, 0x00, 0x2b }, { 1, 0x00, 0x1d } },
	{ { 0, 0x00, 0x2c }, { 1, 0x00, 0x1d } },
	{ { 0, 0x00, 0x2d }, { 1, 0x00, 0x1e } },
	{ { 0, 0x08, 0x1e }, { 1, 0x00, 0x1e } },
	{ { 0, 0x00, 0x2e }, { 1, 0x00, 0x1f } },
	{ { 0, 0x00, 0x2f }, { 1, 0x00, 0x1f } },
	{ { 0, 0x01, 0x2e }, { 1, 0x01, 0x1f } },
	{ { 0, 0x00, 0x30 }, { 1, 0x00, 0x20 } },
	{ { 0, 0x00, 0x31 }, { 1, 0x02, 0x1f } },
	{ { 0, 0x00, 0x32 }, { 1, 0x00, 0x21 } },
	{ { 0, 0x02, 0x2f }, { 1, 0x03, 0x1f } },
	{ { 0, 0x00, 0x33 }, { 1, 0x00, 0x22 } },
	{ { 0, 0x00, 0x34 }, { 1, 0x04, 0x1f } },
	{ { 0, 0x00, 0x35 }, { 1, 0x00, 0x23 } },
	{ { 0, 0x04, 0x2e }, { 1, 0x05, 0x1f } },
	{ { 0, 0x00, 0x36 }, { 1, 0x00, 0x24 } },
	{ { 0, 0x00, 0x37 }, { 1, 0x06, 0x1f } },
	{ { 0, 0x00, 0x38 }, { 1, 0x00, 0x25 } },
	{ { 0, 0x05, 0x2f }, { 1, 0x07, 0x1f } },
	{ { 0, 0x00, 0x39 }, { 1, 0x00, 0x26 } },
	{ { 0, 0x00, 0x3a }, { 1, 0x08, 0x1f } },
	{ { 0, 0x00, 0x3b }, { 1, 0x00, 0x27 } },
	{ { 0, 0x07, 0x2e }, { 1, 0x09, 0x1f } },
	{ { 0, 0x00, 0x3c }, { 1, 0x00, 0x28 } },
	{ { 0, 0x00, 0x3d }, { 1, 0x0a, 0x1f } },
	{ { 0, 0x00, 0x3e }, { 1, 0x00, 0x29 } },
	{ { 0, 0x08, 0x2f }, { 1, 0x0b, 0x1f } },
	{ { 0, 0x00, 0x3f }, { 1, 0x00, 0x2a } },
	{ { 0, 0x01, 0x3e }, { 1, 0x0c, 0x1f } },
	{ { 0, 0x01, 0x3f }, { 1, 0x00, 0x2b } },
	{ { 0, 0x0a, 0x2e }, { 1, 0x0d, 0x1f } },
	{ { 0, 0x02, 0x3e }, { 1, 0x00, 0x2c } },
	{ { 0, 0x02, 0x3f }, { 1, 0x0e, 0x1f } },
	{ { 0, 0x03, 0x3e }, { 1, 0x00, 0x2d } },
	{ { 0, 0x0b, 0x2f }, { 1, 0x0f, 0x1f } },
	{ { 0, 0x03, 0x3f }, { 1, 0x00, 0x2e } },
	{ { 0, 0x04, 0x3e }, { 1, 0x00, 0x2e } },
	{ { 0, 0x04, 0x3f }, { 1, 0x00, 0x2f } },
	{ { 0, 0x0d, 0x2e }, { 1, 0x00, 0x2f } },
	{ { 0, 0x05, 0x3e }, { 1, 0x00, 0x30 } },
	{ { 0, 0x05, 0x3f }, { 1, 0x00, 0x30 } },
	{ { 0, 0x06, 0x3e }, { 1, 0x00, 0x31 } },
	{ { 0, 0x0e, 0x2f }, { 1, 0x00, 0x31 } },
	{ { 0, 0x06, 0x3f }, { 1, 0x00, 0x32 } },
	{ { 0, 0x07, 0x3e }, { 1, 0x00, 0x32 } },
	{ { 0, 0x07, 0x3f }, { 1, 0x00, 0x33 } },
	{ { 0, 0x10, 0x2d }, { 1, 0x00, 0x33 } },
	{ { 0, 0x08, 0x3e }, { 1, 0x00, 0x34 } },
	{ { 0, 0x08, 0x3f }, { 1, 0x00, 0x34 } },
	{ { 0, 0x09, 0x3e }, { 1, 0x00, 0x35 } },
	{ { 0, 0x10, 0x30 }, { 1, 0x00, 0x35 } },
	{ { 0, 0x09, 0x3f }, { 1, 0x00, 0x36 } },
	{ { 0, 0x0a, 0x3e }, { 1, 0x00, 0x36 } },
	{ { 0, 0x0a, 0x3f }, { 1, 0x00, 0x37 } },
	{ { 0, 0x10, 0x33 }, { 1, 0x00, 0x37 } },
	{ { 0, 0x0b, 0x3e }, { 1, 0x00, 0x38 } },
	{ { 0, 0x0b, 0x3f }, { 1, 0x00, 0x38 } },
	{ { 0, 0x0c, 0x3e }, { 1, 0x00, 0x39 } },
	{ { 0, 0x10, 0x36 }, { 1, 0x00, 0x39 } },
	{ { 0, 0x0c, 0x3f }, { 1, 0x00, 0x3a } },
	{ { 0, 0x0d, 0x3e }, { 1, 0x00, 0x3a } },
	{ { 0, 0x0d, 0x3f }, { 1, 0x00, 0x3b } },
	{ { 0, 0x10, 0x39 }, { 1, 0x00, 0x3b } },
	{ { 0, 0x0e, 0x3e }, { 1, 0x00, 0x3c } },
	{ { 0, 0x0e, 0x3f }, { 1, 0x00, 0x3c } },
	{ { 0, 0x0f, 0x3e }, { 1, 0x00, 0x3d } },
	{ { 0, 0x10, 0x3c }, { 1, 0x00, 0x3d } },
	{ { 0, 0x0f, 0x3f }, { 1, 0x00, 0x3e } },
	{ { 0, 0x18, 0x2e }, { 1, 0x00, 0x3e } },
	{ { 0, 0x10, 0x3e }, { 1, 0x00, 0x3f } },
	{ { 0, 0x10, 0x3f }, { 1, 0x00, 0x3f } },
	{ { 0, 0x11, 0x3e }, { 1, 0x01, 0x3f } },
	{ { 0, 0x19, 0x2f }, { 1, 0x10, 0x30 } },
	{ { 0, 0x11, 0x3f }, { 1, 0x02, 0x3f } },
	{ { 0, 0x12, 0x3e }, { 1, 0x10, 0x31 } },
	{ { 0, 0x12, 0x3f }, { 1, 0x03, 0x3f } },
	{ { 0, 0x1b, 0x2e }, { 1, 0x10, 0x32 } },
	{ { 0, 0x13, 0x3e }, { 1, 0x04, 0x3f } },
	{ { 0, 0x13, 0x3f }, { 1, 0x10, 0x33 } },
	{ { 0, 0x14, 0x3e }, { 1, 0x05, 0x3f } },
	{ { 0, 0x1c, 0x2f }, { 1, 0x10, 0x34 } },
	{ { 0, 0x14, 0x3f }, { 1, 0x06, 0x3f } },
	{ { 0, 0x15, 0x3e }, { 1, 0x10, 0x35 } },
	{ { 0, 0x15, 0x3f }, { 1, 0x07, 0x3f } },
	{ { 0, 0x1e, 0x2e }, { 1, 0x10, 0x36 } },
	{ { 0, 0x16, 0x3e }, { 1, 0x08, 0x3f } },
	{ { 0, 0x16, 0x3f }, { 1, 0x10, 0x37 } },
	{ { 0, 0x17, 0x3e }, { 1, 0x09, 0x3f } },
	{ { 0, 0x1f, 0x2f }, { 1, 0x10, 0x38 } },
	{ { 0, 0x17, 0x3f }, { 1, 0x0a, 0x3f } },
	{ { 0, 0x18, 0x3e }, { 1, 0x10, 0x39 } },
	{ { 0, 0x18, 0x3f }, { 1, 0x0b, 0x3f } },
	{ { 0, 0x20, 0x2f }, { 1, 0x10, 0x3a } },
	{ { 0, 0x19, 0x3e }, { 1, 0x0c, 0x3f } },
	{ { 0, 0x19, 0x3f }, { 1, 0x10, 0x3b } },
	{ { 0, 0x1a, 0x3e }, { 1, 0x0d, 0x3f } },
	{ { 0, 0x20, 0x32 }, { 1, 0x10, 0x3c } },
	{ { 0, 0x1a, 0x3f }, { 1, 0x0e, 0x3f } },
	{ { 0, 0x1b, 0x3e }, { 1, 0x10, 0x3d } },
	{ { 0, 0x1b, 0x3f }, { 1, 0x0f, 0x3f } },
	{ { 0, 0x20, 0x35 }, { 1, 0x10, 0x3e } },
	{ { 0, 0x1c, 0x3e }, { 1, 0x10, 0x3e } },
	{ { 0, 0x1c, 0x3f }, { 1, 0x10, 0x3f } },
	{ { 0, 0x1d, 0x3e }, { 1, 0x10, 0x3f } },
	{ { 0, 0x20, 0x38 }, { 1, 0x11, 0x3f } },
	{ { 0, 0x1d, 0x3f }, { 1, 0x11, 0x3f } },
	{ { 0, 0x1e, 0x3e }, { 1, 0x12, 0x3f } },
	{ { 0, 0x1e, 0x3f }, { 1, 0x12, 0x3f } },
	{ { 0, 0x20, 0x3b }, { 1, 0x13, 0x3f } },
	{ { 0, 0x1f, 0x3e }, { 1, 0x13, 0x3f } },
	{ { 0, 0x1f, 0x3f }, { 1, 0x14, 0x3f } },
	{ { 0, 0x20, 0x3d }, { 1, 0x14, 0x3f } },
	{ { 0, 0x20, 0x3e }, { 1, 0x15, 0x3f } },
	{ { 0, 0x20, 0x3f }, { 1, 0x15, 0x3f } },
	{ { 0, 0x29, 0x2e }, { 1, 0x16, 0x3f } },
	{ { 0, 0x21, 0x3e }, { 1, 0x16, 0x3f } },
	{ { 0, 0x21, 0x3f }, { 1, 0x17, 0x3f } },
	{ { 0, 0x22, 0x3e }, { 1, 0x17, 0x3f } },
	{ { 0, 0x2a, 0x2f }, { 1, 0x18, 0x3f } },
	{ { 0, 0x22, 0x3f }, { 1, 0x18, 0x3f } },
	{ { 0, 0x23, 0x3e }, { 1, 0x19, 0x3f } },
	{ { 0, 0x23, 0x3f }, { 1, 0x19, 0x3f } },
	{ { 0, 0x2c, 0x2e }, { 1, 0x1a, 0x3f } },
	{ { 0, 0x24, 0x3e }, { 1, 0x1a, 0x3f } },
	{ { 0, 0x24, 0x3f }, { 1, 0x1b, 0x3f } },
	{ { 0, 0x25, 0x3e }, { 1, 0x1b, 0x3f } },
	{ { 0, 0x2d, 0x2f }, { 1, 0x1c, 0x3f } },
	{ { 0, 0x25, 0x3f }, { 1, 0x1c, 0x3f } },
	{ { 0, 0x26, 0x3e }, { 1, 0x1d, 0x3f } },
	{ { 0, 0x26, 0x3f }, { 1, 0x1d, 0x3f } },
	{ { 1, 0x1e, 0x3f }, { 0, 0x26, 0x3f } },
	{ { 0, 0x27, 0x3e }, { 1, 0x1e, 0x3f } },
	{ { 0, 0x27, 0x3f }, { 1, 0x1f, 0x3f } },
	{ { 0, 0x28, 0x3e }, { 1, 0x1f, 0x3f } },
	{ { 1, 0x20, 0x3f }, { 0, 0x28, 0x3e } },
	{ { 0, 0x28, 0x3f }, { 1, 0x20, 0x3f } },
	{ { 0, 0x29, 0x3e }, { 1, 0x21, 0x3f } },
	{ { 0, 0x29, 0x3f }, { 1, 0x30, 0x30 } },
	{ { 0, 0x30, 0x31 }, { 1, 0x22, 0x3f } },
	{ { 0, 0x2a, 0x3e }, { 1, 0x30, 0x31 } },
	{ { 0, 0x2a, 0x3f }, { 1, 0x23, 0x3f } },
	{ { 0, 0x2b, 0x3e }, { 1, 0x30, 0x32 } },
	{ { 0, 0x30, 0x34 }, { 1, 0x24, 0x3f } },
	{ { 0, 0x2b, 0x3f }, { 1, 0x30, 0x33 } },
	{ { 0, 0x2c, 0x3e }, { 1, 0x25, 0x3f } },
	{ { 0, 0x2c, 0x3f }, { 1, 0x30, 0x34 } },
	{ { 0, 0x30, 0x37 }, { 1, 0x26, 0x3f } },
	{ { 0, 0x2d, 0x3e }, { 1, 0x30, 0x35 } },
	{ { 0, 0x2d, 0x3f }, { 1, 0x27, 0x3f } },
	{ { 0, 0x2e, 0x3e }, { 1, 0x30, 0x36 } },
	{ { 0, 0x30, 0x3a }, { 1, 0x28, 0x3f } },
	{ { 0, 0x2e, 0x3f }, { 1, 0x30, 0x37 } },
	{ { 0, 0x2f, 0x3e }, { 1, 0x29, 0x3f } },
	{ { 0, 0x2f, 0x3f }, { 1, 0x30, 0x38 } },
	{ { 0, 0x30, 0x3d }, { 1, 0x2a, 0x3f } },
	{ { 0, 0x30, 0x3e }, { 1, 0x30, 0x39 } },
	{ { 1, 0x2b, 0x3f }, { 0, 0x30, 0x3e } },
	{ { 0, 0x30, 0x3f }, { 1, 0x30, 0x3a } },
	{ { 0, 0x31, 0x3e }, { 1, 0x2c, 0x3f } },
	{ { 0, 0x31, 0x3f }, { 1, 0x30, 0x3b } },
	{ { 1, 0x2d, 0x3f }, { 0, 0x31, 0x3f } },
	{ { 0, 0x32, 0x3e }, { 1, 0x30, 0x3c } },
	{ { 0, 0x32, 0x3f }, { 1, 0x2e, 0x3f } },
	{ { 0, 0x33, 0x3e }, { 1, 0x30, 0x3d } },
	{ { 1, 0x2f, 0x3f }, { 0, 0x33, 0x3e } },
	{ { 0, 0x33, 0x3f }, { 1, 0x30, 0x3e } },
	{ { 0, 0x34, 0x3e }, { 1, 0x30, 0x3e } },
	{ { 0, 0x34, 0x3f }, { 1, 0x30, 0x3f } },
	{ { 0, 0x34, 0x3f }, { 1, 0x30, 0x3f } },
	{ { 0, 0x35, 0x3e }, { 1, 0x31, 0x3f } },
	{ { 0, 0x35, 0x3f }, { 1, 0x31, 0x3f } },
	{ { 0, 0x36, 0x3e }, { 1, 0x32, 0x3f } },
	{ { 0, 0x36, 0x3e }, { 1, 0x32, 0x3f } },
	{ { 0, 0x36, 0x3f }, { 1, 0x33, 0x3f } },
	{ { 0, 0x37, 0x3e }, { 1, 0x33, 0x3f } },
	{ { 0, 0x37, 0x3f }, { 1, 0x34, 0x3f } },
	{ { 0, 0x37, 0x3f }, { 1, 0x34, 0x3f } },
	{ { 0, 0x38, 0x3e }, { 1, 0x35, 0x3f } },
	{ { 0, 0x38, 0x3f }, { 1, 0x35, 0x3f } },
	{ { 0, 0x39, 0x3e }, { 1, 0x36, 0x3f } },
	{ { 0, 0x39, 0x3e }, { 1, 0x36, 0x3f } },
	{ { 0, 0x39, 0x3f }, { 1, 0x37, 0x3f } },
	{ { 0, 0x3a, 0x3e }, { 1, 0x37, 0x3f } },
	{ { 0, 0x3a, 0x3f }, { 1, 0x38, 0x3f } },
	{ { 0, 0x3a, 0x3f }, { 1, 0x38, 0x3f } },
	{ { 0, 0x3b, 0x3e }, { 1, 0x39, 0x3f } },
	{ { 0, 0x3b, 0x3f }, { 1, 0x39, 0x3f } },
	{ { 0, 0x3c, 0x3e }, { 1, 0x3a, 0x3f } },
	{ { 0, 0x3c, 0x3e }, { 1, 0x3a, 0x3f } },
	{ { 0, 0x3c, 0x3f }, { 1, 0x3b, 0x3f } },
	{ { 0, 0x3d, 0x3e }, { 1, 0x3b, 0x3f } },
	{ { 0, 0x3d, 0x3f }, { 1, 0x3c, 0x3f } },
	{ { 0, 0x3d, 0x3f }, { 1, 0x3c, 0x3f } },
	{ { 0, 0x3e, 0x3e }, { 1, 0x3d, 0x3f } },
	{ { 0, 0x3e, 0x3f }, { 1, 0x3d, 0x3f } },
	{ { 1, 0x3e, 0x3f }, { 0, 0x3e, 0x3f } },
	{ { 0, 0x3f, 0x3f }, { 1, 0x3e, 0x3f } },
	{ { 0, 0x3f, 0x3f }, { 1, 0x3f, 0x3f } }
};