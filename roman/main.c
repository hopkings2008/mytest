#include <stdlib.h>
#include <stdio.h>

int getValue(char c) {
	switch(c){
	  case 'I':
		  return 1;
	  case 'V':
		  return 5;
	  case 'X':
		  return 10;
	  case 'L':
		  return 50;
	  case 'C':
		  return 100;
	  case 'D':
		  return 500;
	  case 'M':
		  return 1000;
	  default:
		  return -1;
	}
}

int isVld(char c){
	static int vv = 0;
	static int ll = 0;
	static int dd = 0;
	switch(c){
	  case 'V':
		  ++vv;
		  ll = 0;
		  dd = 0;
		  break;
	  case 'L':
		  ++ll;
		  vv = 0;
		  dd = 0;
		  break;
          case 'D':
		  ++dd;
		  vv = 0;
		  ll = 0;
		  break;
	  default:
		  vv=0;
		  ll=0;
		  dd=0;
		  break;
	}
	if(vv >= 2 || ll >= 2 || dd >= 2){
		vv = 0;
		ll = 0;
		dd = 0;
		return 1;
	}
	return 0;
}

int isSame(char c){
	static int same = 0;
	static char former = 0;
	if(former == c){
		same++;
	}
	else {
		same = 0;
		former = c;
		return 0;
	}
	if(same > 3){
		same = 0;
		former = 0;
		return 1;
	}
	return 0;
}

int roman(const char *s){
	int former = 0;
	int formersame = 0;
	int cur = -1;
	int sum = 0;
	if(!s || strlen(s) == 0)
		return -1;
	
	for(; *s; s++) {
		cur = getValue(*s);
		if(isVld(*s) == 1){
			return -1;
		}
		if(isSame(*s) == 1){
			return -1;
		}
		if(0 == former){
			former = cur;
			sum += cur;
			continue;
		}
		
		formersame = (former == cur) ? 1 : 0;

		if(former >= cur){
			sum += cur;
			former = cur;
			continue;
		}

		if(1 == formersame)
			return -1;
		switch(former){
			case 1:
			case 10:
			case 100:
				break;
			default:
				return -1;
		}
		if (cur / former > 10)
			return -1;
		printf("sum: %d, cur: %d, former: %d\n", sum, cur, former);
		sum -= former;
		sum += (cur - former);
		former = cur;
	}

	return sum;
}

int main(int argc, char *argv[]){
	int ret = 0;
	char *s = "MMMMXC";
	ret = roman(s);
	printf("%s: %d\n", s, ret);
	s = "MDIII";
	ret = roman(s);
	printf("%s: %d\n", s, ret);
	s = "XCIX";
	ret = roman(s);
	printf("%s: %d\n", s, ret);
	s = "IX";
	ret = roman(s);
	printf("%s: %d\n", s, ret);
	s = "IL";
	ret = roman(s);
	printf("%s: %d\n", s, ret);
	return 0;
}

