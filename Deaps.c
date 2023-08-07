#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int size;

int parent(int i){
    return (i - 1) / 2;
}

int left_child(int i){
    return (2*i + 1);
}

int right_child(int i){
    return (2*i + 2);
}

void swap(int heap[],int a,int b){
	int t=heap[a];
	heap[a]=heap[b];
	heap[b]=t;
}

int left_or_right(int index){ //index should be greater than 0
	int lvl,num,mid;
	lvl=log2(index+1);
	num=pow(2,lvl);
	mid=num-1+(num/2);
	if(index<mid)
		return 1; //left tree
	else
		return 0;	//right tree
}

int corr_right(int index){
	int lvl=log2(index+1);
	int r=index+pow(2,lvl-1);
	if(r<size)
		return r;
	corr_right((index-1)/2);
}

int corr_left(int index){
	int lvl=log2(index+1);
	int l=index-pow(2,lvl-1);
	return l;
}

void insert(int heap[],int ind){
	if(size==2)
		return;
	if(left_or_right(ind)){ //left subtree
		if(heap[ind]<heap[parent(ind)]){
			swap(heap,ind,parent(ind));
			insert(heap,parent(ind));
		}
		if(heap[ind]>heap[corr_right(ind)]){
			swap(heap,ind,corr_right(ind));
			insert(heap,corr_right(ind));
		}
	}
	else{ //right subtree
		if(heap[ind]>heap[parent(ind)]){
			swap(heap,ind,parent(ind));
			insert(heap,parent(ind));
		}
		if(heap[ind]<heap[corr_left(ind)]){
			swap(heap,ind,corr_left(ind));
			insert(heap,corr_left(ind));
		}
	}
}

int get_min(int heap[]){
	return(heap[1]);
}

int get_max(int heap[]){
	return(heap[2]);
}

void heapify(int heap[],int index){
	if(left_or_right(index)){
		if(left_child(index)<size && heap[index]>heap[left_child(index)]){
			swap(heap,index,left_child(index));
			heapify(heap,left_child(index));
		}
		if(right_child(index)<size && heap[index]>heap[right_child(index)]){
			swap(heap,index,right_child(index));
			heapify(heap,right_child(index));
		}
		if(parent(index)>0 && heap[index]<heap[parent(index)]){
			swap(heap,index,parent(index));
			heapify(heap,parent(index));
		}
		if(heap[index]>heap[corr_right(index)]){
			swap(heap,index,corr_right(index));
			heapify(heap,corr_right(index));
		}
	}
	else{
		if(left_child(index)<size && heap[index]<heap[left_child(index)])
		{
			swap(heap,index,left_child(index));
			heapify(heap,left_child(index));
		}
		if(right_child(index)<size && heap[index]<heap[right_child(index)]){
			swap(heap,index,right_child(index));
			heapify(heap,right_child(index));
		}
		if(parent(index)>0 && heap[index]>heap[parent(index)])
		{
			swap(heap,index,parent(index));
			heapify(heap,parent(index));
		}
		if(heap[index]<heap[corr_left(index)])
		{
			swap(heap,index,corr_left(index));
			heapify(heap,corr_left(index));
		}
	}
}

int extract_max(int heap[]){
	int max=heap[2];
	swap(heap,2,size-1);
	size--;
	heapify(heap,2);
	return max;
}

int extract_min(int heap[])
{
	int min=heap[1];
	swap(heap,1,size-1);
	size--;
	heapify(heap,1);
	return min;
}

int main(){
	int arr[]={-1,4,5,7,9,11,13,8,50,70,99,2,4};
	size=1;
	int heap[31];
	for(int i=0;i<13;i++){
		heap[size]=arr[i];
		size++;
		insert(heap,i+1);
	}
	
	for(int i=1;i<size;i++){
		printf("%d ",heap[i]);
	}
	printf("\n%d \n",extract_min(heap));
	for(int i=1;i<size;i++){
		printf("%d ",heap[i]);
	}
	
	return 0;
}
