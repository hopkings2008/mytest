#include <stdlib.h>
#include <stdio.h>

int getCharValue(char c){
	if(c<'a' || c > 'z')
		return 0;
	return c - 'a' +1;
}

char getChar(int i){
	return 'a' + i - 1;
}

int sumChar(const char *s){
	int sum = 0;
	for(; *s; s++){
		sum = sum*26 + getCharValue(*s);
	}
	return sum;
}

char *sumInt(int v){
	char s[6] = {0};
	char *buf = (char *)malloc(6);
	int i = 0;
	int j = 0;
	char c = 0;
	memset(buf, 0, 6);

	while(v){
		c = v - 26 *(v/26);
		s[i++] = getChar(c);
		v = v/26;
	}

	for(i=i-1; i >= 0; --i){
		buf[j++] = s[i];
	}

	return buf;
}

void convert(const char *s, char *out){
	int flag = 0; //-1 for char, 1 for int.
	char *p=s;
	int v;
	for(; *s; s++){
		if(*s>='a' && *s<='z') {
			if(flag == 1){
				sprintf(out, "ERROR");
				return;
			}
			flag = -1;
		}
		else {
			if(flag == -1){
				sprintf(out, "ERROR");
				return;
			}
			flag = 1;
		}
	}
	s = p;

	if(1 == flag){
		v = atoi(s);
		p = sumInt(v);
		strncpy(out, p, strlen(p));
		return;
	}

	v = sumChar(s);
	sprintf(out, "%d", v);
	return;
}

int main(int argc, char *argv[]){
	char buf[10] = {0};
	convert("test", buf);
	printf("out: %s\n", buf);
	memset(buf, 0, sizeof(buf));
	convert("104143", buf);
	printf("out: %s\n", buf);
	memset(buf, 0, sizeof(buf));
	convert("zzzzzz", buf);
	printf("out: %s\n", buf);
	memset(buf, 0, sizeof(buf));
	convert("abc123", buf);
	printf("out: %s\n", buf);
	memset(buf, 0, sizeof(buf));
}
