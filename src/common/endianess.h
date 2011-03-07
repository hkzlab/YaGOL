#ifndef _ENDIANESS_HEADER_
#define _ENDIANESS_HEADER_

#define SYSTEM_IS_LITTLE_ENDIAN

#ifdef SYSTEM_IS_LITTLE_ENDIAN
inline uint16 READ_UINT16(const void *ptr) {
	const uint8 *b = (const uint8 *)ptr;
	return (b[1] << 8) | b[0];
}
		
inline uint32 READ_UINT32(const void *ptr) {
	const uint8 *b = (const uint8 *)ptr;
	return (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | (b[0]);
}

inline void WRITE_UINT16(void *ptr, uint16 value) {
	uint8 *b = (uint8 *)ptr;
	b[0] = (uint8)(value >> 0);
	b[1] = (uint8)(value >> 8);
}

inline void WRITE_UINT32(void *ptr, uint32 value) {
	uint8 *b = (uint8 *)ptr;
	b[0] = (uint8)(value >>  0);
	b[1] = (uint8)(value >>  8);
	b[2] = (uint8)(value >> 16);
	b[3] = (uint8)(value >> 24);
}
#else 

inline uint16 READ_UINT16(const void *ptr) {
	const uint8 *b = (const uint8 *)ptr;
	return (b[0] << 8) | b[1];
}

inline uint32 READ_UINT32(const void *ptr) {
	const uint8 *b = (const uint8 *)ptr;
	return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | (b[3]);
}

inline void WRITE_UINT16(void *ptr, uint16 value) {
	uint8 *b = (uint8 *)ptr;
	b[0] = (uint8)(value >> 8);
	b[1] = (uint8)(value >> 0);
}

inline void WRITE_UINT32(void *ptr, uint32 value) {
	uint8 *b = (uint8 *)ptr;
	b[0] = (uint8)(value >> 24);
	b[1] = (uint8)(value >> 16);
	b[2] = (uint8)(value >>  8);
	b[3] = (uint8)(value >>  0);
}
#endif /* SYSTEM_IS_LITTLE_ENDIAN */


#endif /* _ENDIANESS_HEADER_ */
