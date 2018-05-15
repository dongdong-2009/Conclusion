#ifndef GPSGPRS_ENCODE_TY_H
#define GPSGPRS_ENCODE_TY_H

int encode_Base64(char *buf, int size, const char *user, const char *pwd);
unsigned char CharHToI(unsigned char h);
unsigned int inet_addr_ty(char *ipaddr);
int ParaseString(char *str,char *out);

#endif

