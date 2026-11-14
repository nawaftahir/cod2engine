/*
**	(c) COPYRIGHT MIT 1995.
**	Please first read the full copyright statement in the file COPYRIGH.
*/
#ifndef HTAABROW_H
#define HTAABROW_H
#include "HTUTree.h"
#include "HTNet.h"

typedef struct _HTBasic {		  /* Basic challenge and credentials */
    char *	uid;
    char *	pw;
    BOOL	retry;			    /* Should we ask the user again? */
    BOOL	proxy;				     /* Proxy authentication */
} HTBasic;

extern HTBasic * HTBasic_new (void);
extern BOOL basic_credentials (HTRequest * request, HTBasic * basic);

extern HTNetBefore	HTBasic_generate;
extern HTNetAfter 	HTBasic_parse;
extern HTUTree_gc	HTBasic_delete;
extern HTNetBefore	HTDigest_generate;
extern HTNetAfter 	HTDigest_parse;
extern HTNetAfter       HTDigest_updateInfo;
extern HTUTree_gc	HTDigest_delete;
#endif	/* NOT HTAABROW_H */
