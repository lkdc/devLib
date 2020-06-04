#include<stdio.h>

char str[100] = "abcdefghijklmnopqrstuvwxyzghh";

char find_char(char str[]){
    int cnt;
    int i = 0;
 
    while(str[i] != '\0'){
        cnt = 1;
        int j = i;
        while(str[++j] != '\0'){
            if(str[i] == str[j])
                cnt++;
            if(cnt >= 3) 
                return str[i];
        }
        i++;
    }
    return '\0';

}


int main(int argv, char *argc[]){

printf("%c \n",find_char(str));

}
    
