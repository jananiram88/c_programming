#include<stdio.h>
#include<stdlib.h>

int main() {
	int i=0, j=0;
	int count=0;
	char temp;
	char inputString[50];

	//Input the string
	scanf("%s", inputString);

	//Sort the string
	while(inputString[j] != '\0') {
		while(inputString[i] != '\0') {
			int a = (int)inputString[i];
			int b = (int)inputString[i + 1];

			if(inputString[i+1] != '\0') {
				if(a > b) {
					temp = a;
					inputString[i]  = inputString[i+1];
					inputString[i+1] = temp;
				}
			}
			i++;
		}
		i = 0;
		j++;
	}
	
	i=0;

	//Find the number of letters repeated more than once in a word
	while(inputString[i] != '\0') {
		if(inputString[i] == inputString[i+1]) {
			count++;
		}
		j=i;
		while(inputString[j]==inputString[j+1]) {
			i++;
			j++;
		}
		j=0;
		i++;
	}

	printf("%d\n", count);
}
