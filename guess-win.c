#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//背景知识：输入字符串的最后一位为'\n'；
//当试图清理空的输入缓冲区时，阻塞

int input(char* str) {
    //使用fgets可以处理输入内容过长的情况
    fgets(str, 5, stdin);
	while (judge(str)) {
	    memset(str, 0, 5);
		printf("您已误入歧途，施主，回头是岸\n");
		printf("请输入一个1-100之间的整数：");
		fgets(str, 5, stdin);
	}
	return atoi(str);
}
//确保输入的字符串为合法字符串
int judge(char* str) {
    //当输入的字符串长度小于3位时
    if (strlen(str) < 4) {
        //不能以'\n'或者0开头
        if (str[0] == 10 || str[0] == 48)
            return -1;
        //前两位可能的格式如下：
        //'num+'\n'、ltr+'\n'、纯num、包含非法字符的两位内容
        int i = 0;
        for (i = 0; i < 2; i++) {
            if (str[i] == 10)
                continue;
            else {
                if (str[i] < 48 || str[i] > 57)
                    return -1;
            }
        }
        return 0;
    }
    //当输入的字符串长度为3位时
    //不能写为"strlen(str) = 4"，因为该条件下
    //包含两种可能，而它们需要区别对待
    if (str[3] == '\n') {
        //判断字符串是否为100
        if (atoi(str) == 100)
            return 0;
        else
            return -1;
    }
    //执行到这里，输入的字符串长度肯定大于3位，直接清理
    //输入缓冲区中的多余数据，返回-1
    scanf("%*[^\n]");
    scanf("%*c");
    return -1;
}

int main() {
	int ran = 0, guess = 0, guess1 = 0;
	char confirm = 0;
	char str[5] = {0};
	srand((unsigned) time(NULL));
	ran = rand() % 100 + 1;

	while (1) {
    	printf("这是一个十分无聊的猜数游戏^_^\n");
    	printf("请输入一个1-100之间的整数：");

        //调用函数确保输入字符串为合法格式
        guess = input(str);
	    while (guess != ran) {
	    	if (guess > ran) {
	    		printf("您猜的数大了\n");
	    		printf("请继续输入：\n");
	    		guess1 = input(str);
	    		while (guess1 > guess) {
	    			printf("请不要在绝望的道路上越走越远\n");
	    			printf("请继续输入：\n");
	    		    guess1 = input(str);
	    		}
	    		guess = guess1;
	    	}
	    	if (guess < ran) {				
	    		printf("您猜的数小了\n");
	    		printf("请继续输入：\n");
	    		guess1 = input(str);
	    		while (guess1 < guess) {
	    			printf("请不要在绝望的道路上越走越远\n");
	    			printf("请继续输入：\n");
	    			guess1 = input(str);
	    		}
	    		guess = guess1;
	    	}
	    }
	    printf("恭喜您，猜对了！没奖!\n");

	    printf("是否继续游戏（输入y以继续）：\n");
    	scanf("%c", &confirm);
    	if (confirm != 'y')
	        break;
	    //清理输入缓冲区中的'\n'，否则
	    //下次scanf()会读出该'\n'，造成错误
	    scanf("%*c");
	}
	getchar();
	return 0;
}
