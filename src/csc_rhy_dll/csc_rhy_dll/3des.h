#ifndef __3DES_H__
#define __3DES_H__
 
 
 
	#define EXPORT  
 
 
#define EN0 0
#define DE1 1
#define maxsize 1024
#define		CRC8		0x80
typedef struct
{
	unsigned long ek[32];
	unsigned long dk[32];
} des_ctx;
typedef unsigned int uint;
  void showbininfo( char* infos, unsigned char* x,int l);
  void des_dec(des_ctx *dc,unsigned char *data,int blocks);
  void des_enc(des_ctx *dc,unsigned char *data,int blocks);
  void des_key(des_ctx *dc,unsigned char *key);

  unsigned int getcrc8(unsigned char *cdata, uint nlength);
  char *  enc3des16(char * hexkey,  char * hexdat );
  char* dec3des16(char * hexkey,  char * hexdat);
  void  dec( unsigned char*  key,unsigned   char* cp);
  void  enc(unsigned char*  key,unsigned   char* cp);
#endif 
