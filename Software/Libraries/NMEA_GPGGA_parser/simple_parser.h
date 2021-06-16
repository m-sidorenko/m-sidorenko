#ifndef __SIMPLE_PARSER_H__
#define __SIMPLE_PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//-------------------------------------------
// 			parser's statuses

#define		STATUS_END_OF_MSG		3
#define		STATUS_FIND_START		2
#define		STATUS_OK				1
#define		STATUS_ERROR			0


//-------------------------------------------
// 		typedef for GPGGA NMEA message

typedef struct
{
	uint8_t utc[10];	// 2
	uint8_t lat[11];		// 3
	uint8_t lat_s;		// 4
	uint8_t lon[12];	// 5
	uint8_t lon_s;		// 6
	uint8_t fix_q;		// 7
	uint8_t num_s[3];	// 8
	uint8_t hdop[3];	// 9
	uint8_t alt[5];		// 10
	uint8_t alt_u;		// 11
	uint8_t	height[5];	// 12
	uint8_t	height_u;	// 13
	uint8_t	tslu[3];	// 14
/*	uint8_t	st_id[5]; */	// 15
	uint8_t	ch_sum[4];	// 15
} T_GPGGA;


//-------------------------------------------
// 		enum for GPGGA NMEA message

enum gpgga_fields
{
	utc = 1,
	lat,
	lat_s,
	lon,
	lon_s,
	fix_q,
	num_s,
	hdop,
	alt,
	alt_u,
	height,
	height_u,
	tslu,
//	st_id,
	ch_sum
};


//-------------------------------------------
// 		parser function for GPGGA message

uint8_t parser(uint8_t* raw_data, T_GPGGA* msg);


#endif
// *********************************** E N D **********************************
