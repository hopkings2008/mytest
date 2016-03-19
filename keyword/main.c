#include <stdlib.h>
#include <stdio.h>

#define MAX_LEN 256

static char buf[MAX_LEN] = {0};
static int idx = 0;
void put(const char *s){
	if(s && s[0] != '\0'){
		printf("%s\n", s);
		memset(buf, 0, sizeof(buf));
		idx = 0;
	}
}

int startComment(const char c){
	static char pattern = 0;
	switch(c){
		case '/':
			if(pattern == '/'){
				return 1; //line comment.
			}
			pattern = c;
			break;
		case '*':
			if(pattern == '/'){
				return 2;
			}
			pattern = 0;
			break;
		default:
			pattern = 0;
			break;
	}

	return 0;
}

int endComment(const char c, int type){
	static char pattern = 0;
	
	switch(c){
		case '\n':
			pattern = 0;
			if(1 == type){
				return 1; //line comment end
			}
			break;
		case '*':
			pattern = '*';
			break;
		case '/':
			if(pattern == '*' && 2 == type){
				return 1; //comment all end.
			}
			break;
		default:
			pattern = 0;
			break;
	}
	return 0;
}

void process(const char *s){
	int comment = 0;
	char c = 0;

	if(!s || strlen(s) == 0)
		return;

	while(c=*s++){
		if(comment == 0)
			comment = startComment(c);
		if(comment == 1 || comment == 2){
			put(buf);
			do{
				c=*s++;
				if(!c){
					put(buf);
					return;
				}
			}while(0 == endComment(c, comment));
			comment = 0;
			continue;
		}
		
		if((c>='a' && c<='z') || c == '_' || (c>='0' && c <= '9')){
			buf[idx++] = c;
			continue;
		}
		put(buf);
	}
	put(buf);
}

int main(int argc, char *argv[]) {
	const char *s = "hello /*workd*/ mytest\ntest//mytest1\ntest2";
	process(s);
}
