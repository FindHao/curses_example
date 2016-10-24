//
// Created by find on 16-10-24.
//

#ifndef EMBEDDED_SYSTEM_RSA_ENCTYPT_H_H
#define EMBEDDED_SYSTEM_RSA_ENCTYPT_H_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/err.h>
#define OPENSSLKEY "/home/find/mega/master/2016/embedded_system/test.key"
#define PUBLICKEY "/home/find/mega/master/2016/embedded_system/test_pub.key"
#define BUFFSIZE 1024
char* my_encrypt(char *str,char *path_key);//加密
char* my_decrypt(char *str,char *path_key);//解密
#endif //EMBEDDED_SYSTEM_RSA_ENCTYPT_H_H
