#include <stdlib.h>
#include <stdio.h>

#define MAX_LEN 256

void put(const char *s){
	if(s && s[0] != '\0')
		printf("%s\n", s);
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
	char buf[MAX_LEN] = {0};
	int idx = 0;
	int comment = 0;

	if(!s || strlen(s) == 0)
		return;

	for(; *s; s++){
		if(comment == 1){//line comment
			if(1 == endComment(*s, 1)){
				comment = 0;
			}
			continue;
		} else if(comment == 2){//comment all.
			if(1 == endComment(*s, 2)){
				comment = 0;
			}
			continue;
		}
		comment = startComment(*s);
		if(1 == comment || 2 == comment){
			put(buf);
			memset(buf, 0, sizeof(buf));
			idx = 0;
			continue;
		}

		if((*s>='a' && *s<='z') || *s == '_' || (*s>='0' && *s <= '9')){
			buf[idx++] = *s;
			continue;
		}
		put(buf);
		idx = 0;
		memset(buf, 0, sizeof(buf));
	}
	put(buf);
	idx = 0;
	memset(buf, 0, sizeof(buf));
}

int main(int argc, char *argv[]) {
	const char *s = "hello /*workd*/ mytest\ntest//mytest\ntest2";
	process(s);
}
