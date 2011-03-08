#ifndef _ENDIANESS_HEADER_
#define _ENDIANESS_HEADER_

#define SYSTEM_IS_LITTLE_ENDIAN

#ifdef SYSTEM_IS_LITTLE_ENDIAN
inline Uint16 READ_UINT16(const void *ptr) {
	const Uint8 *b = (const Uint8 *)ptr;
	return (b[1] << 8) | b[0];
}
		
inline Uint32 READ_UINT32(const void *ptr) {
	const Uint8 *b = (const Uint8 *)ptr;
	return (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | (b[0]);
}

inline void WRITE_UINT16(void *ptr, Uint16 value) {
	Uint8 *b = (Uint8 *)ptr;
	b[0] = (Uint8)(value >> 0);
	b[1] = (Uint8)(value >> 8);
}

inline void WRITE_UINT32(void *ptr, Uint32 value) {
	Uint8 *b = (Uint8 *)ptr;
	b[0] = (Uint8)(value >>  0);
	b[1] = (Uint8)(value >>  8);
	b[2] = (Uint8)(value >> 16);
	b[3] = (Uint8)(value >> 24);
}
#else 

inline Uint16 READ_UINT16(const void *ptr) {
	const Uint8 *b = (const Uint8 *)ptr;
	return (b[0] << 8) | b[1];
}

inline Uint32 READ_UINT32(const void *ptr) {
	const Uint8 *b = (const Uint8 *)ptr;
	return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | (b[3]);
}

inline void WRITE_UINT16(void *ptr, Uint16 value) {
	Uint8 *b = (Uint8 *)ptr;
	b[0] = (Uint8)(value >> 8);
	b[1] = (Uint8)(value >> 0);
}

inline void WRITE_UINT32(void *ptr, Uint32 value) {
	Uint8 *b = (Uint8 *)ptr;
	b[0] = (Uint8)(value >> 24);
	b[1] = (Uint8)(value >> 16);
	b[2] = (Uint8)(value >>  8);
	b[3] = (Uint8)(value >>  0);
}
#endif /* SYSTEM_IS_LITTLE_ENDIAN */


#endif /* _ENDIANESS_HEADER_ */
