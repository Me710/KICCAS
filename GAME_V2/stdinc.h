/////////////////////////////////////////////////
//stdinc.h
/////////////////////////////////////////////////
//Entête d'inclusion standard
/////////////////////////////////////////////////

#ifndef __STDINC_H__
#define __STDINC_H__

typedef unsigned char u8 ; 
typedef char s8 ;
typedef unsigned short u16 ; 
typedef short s16 ; 
typedef unsigned int u32 ; 
typedef int s32 ; 

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4018) 
#endif 


#endif //__STDINC_H__
