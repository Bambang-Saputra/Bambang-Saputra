#include <stdio.h>

int binary(int data[], int left, int right, int key){
	while(left < right){
		int mid = left + (right-left)/2;
		if(data[mid] < key){
			left = mid + 1;
		}else{
			right = mid;
		} 
	}
	return (data[left]==key)?left+1:-1;
}

int main(){
	int n,m;
	scanf("%d %d", &n, &m); getchar();
	
	int x[n], y;
	for(int i=0; i<n; i++){
		scanf("%d", &x[i]); getchar();
	}
	
	for(int i=0; i<m; i++){
		scanf("%d", &y); getchar();
		int result = binary(x, 0, n-1, y);
		printf("%d\n", result);
	}
	

	return 0;
}
