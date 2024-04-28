#include <stdio.h>
#include <limits.h>
#include "ft_printf_bonus.h"

int main()
{
	const char *num = "abc";
	unsigned int	x = 123;
	char	c = 0;
	int y = 0;

	y = printf("%c", '\0');
	printf("%d", y);
	//y = printf("%-1c%-2c%-3c", '0', 0, '1');
	//printf("%d", y);
}


//플래그 = # +- width.정밀도
//하나가 오면 다른 플래그는 올 수 없음
//%% #: 영향없음, 공백: 영향없음, +: 영향없음, -: 0과 같이 쓰면 0 없는 효과, 정밀도: 영향 없음
//di #: warning (영향없음), 공백: O, +: O (정밀도나 0이 올 경우 0 앞에 써줌/정밀도 뒤에 있어도 warning이지만 적용됨), -: O(0과 같이 쓰면 warning & 0없는 효과), 정밀도: 숫자길이보다 낮게 줘도 숫자는 전부 나옴, 숫자길이보다 긴 경우 긴만큼 0이 앞에 붙음 , -랑 정밀도나 0 같이쓰면 -나 0이 안먹음
//u  #: warning (영향없음), 공백: warning (영향없음), +: warning (영향없음), -: O(0과 같이 쓰면 warning & 0없는 효과), 정밀도: 숫자길이보다 낮게 줘도 전부 나옴, 숫자길이보다 긴 경우 긴만큼 0이 앞에 붙음
//xX #: O, 나머지 u와 같음
//p  #: 영향없음, 나머지 u와 같음
//c  #: warning (영향없음), 공백: warning (영향없음), +: warning (영향없음), -: O(0쓰면 위와 동일), 정밀도: 영향없음 (width 같이쓰면 warning), 0옵션: 출력되지만 warning뜸
//s 정밀도가 최대 문자 갯수, 0옵션 warning하지만 출력은 됨


//" " > - > 0        공백과 0은 같이 사용가능 (음수일 때는 안됨)