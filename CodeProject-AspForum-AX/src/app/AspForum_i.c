/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed May 17 16:20:35 2000
 */
/* Compiler settings for C:\Dokumente und Einstellungen\Uwe\Eigene Dateien\Projekte\AspForum\src\app\AspForum.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IForum2 = {0x9BEA98F0,0xBAD6,0x11D3,{0xA5,0xC1,0x00,0x10,0x5A,0xEF,0xAB,0xBE}};


const IID LIBID_ASPFORUMLib = {0x9BEA98E1,0xBAD6,0x11D3,{0xA5,0xC1,0x00,0x10,0x5A,0xEF,0xAB,0xBE}};


const IID DIID__IForum2Events = {0x9BEA98F2,0xBAD6,0x11D3,{0xA5,0xC1,0x00,0x10,0x5A,0xEF,0xAB,0xBE}};


const CLSID CLSID_Forum2 = {0x9BEA98F1,0xBAD6,0x11D3,{0xA5,0xC1,0x00,0x10,0x5A,0xEF,0xAB,0xBE}};


#ifdef __cplusplus
}
#endif

