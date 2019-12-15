#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef __int64 int64;
typedef unsigned __int64 uint64;
typedef wchar_t wchar;
typedef const char* pchar;
typedef uchar* puchar;
typedef const wchar_t* pwchar;
typedef void* pvoid;

#ifdef __BORLANDC__
  inline char max(char x, char y) {return (x>=y)? x: y;}
  inline char min(char x, char y) {return (x<y)? x: y;}

  inline uchar max(uchar x, uchar y) {return (x>=y)? x: y;}
  inline uchar min(uchar x, uchar y) {return (x<y)? x: y;}

  inline short max(short x, short y) {return (x>=y)? x: y;}
  inline short min(short x, short y) {return (x<y)? x: y;}

  inline ushort max(ushort x, ushort y) {return (x>=y)? x: y;}
  inline ushort min(ushort x, ushort y) {return (x<y)? x: y;}

  inline int max(int x, int y) {return (x>=y)? x: y;}
  inline int min(int x, int y) {return (x<y)? x: y;}

  inline uint max(uint x, uint y) {return (x>=y)? x: y;}
  inline uint min(uint x, uint y) {return (x<y)? x: y;}

  inline int64 max(int64 x, int64 y) {return (x>=y)? x: y;}
  inline int64 min(int64 x, int64 y) {return (x<y)? x: y;}

  inline uint64 max(uint64 x, uint64 y) {return (x>=y)? x: y;}
  inline uint64 min(uint64 x, uint64 y) {return (x<y)? x: y;}

  inline float max(float x, float y) {return (x>=y)? x: y;}
  inline float min(float x, float y) {return (x<y)? x: y;}

  inline double max(double x, double y) {return (x>=y)? x: y;}
  inline double min(double x, double y) {return (x<y)? x: y;}

  #define _strdup strdup
  #define _itoa itoa

  typedef int intptr_t;
#endif

#endif
