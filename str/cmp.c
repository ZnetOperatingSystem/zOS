#include <kernel/types.h>
#include <string.h>
int strcmp(const char *str1,const char *str2){
	int i = 0;
	while(i < strlen(str1)){
		if(str1[i] != str2[i])
			return ++i;
		//else
		//	continue;
		i++;
	}
	return 0;
}
int strncmp(const char *str1,const char *str2,ksize_t n){
	int i = 0;
	while(i < n){
		if(str1[i] != str2[i])
			return ++i;
		//else
		//	continue;
		i++;
	}
	return 0;
}
int memcmp(const void *v1,const void *v2,ksize_t n){
	const unsigned char *s1 = (const char *)v1;
	const unsigned char *s2 = (const char *)v2;
	int i = 0;
	while(i < n){
		if(s1[i] != s2[i])
			return ++i;
		else
			continue;
		i++;
	}
	return 0;
}

