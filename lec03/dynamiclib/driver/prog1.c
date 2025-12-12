

#include <stdio.h>
#include "../mymath.h"

int main() {

	double first, second;
	printf("Enter the first num: \n");
	scanf("%lf", &first);
	printf("Enter the second num: \n");
	scanf("%lf", &second);

	double ans1 = myadd(first, second);
	double ans2 = mysub(first, second);
	double ans3 = mymul(first, second);
	double last = mydiv(first, second);

	printf("ANS RESULT ==== => [%7.1lf] [%7.2lf] [%7.2lf] [%7.2lf]\n", ans1, ans2, ans3, last);
	return 0;
}
