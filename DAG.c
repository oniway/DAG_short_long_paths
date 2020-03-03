#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node{
	int sp_len;			//sp - shortest path
	int sp_count;
	int lp_len;			//lp - longest path
	int lp_count;
};

void node_init(struct node * new_node, int is_s);
int ** adj_matrix_init(int N);
void adj_matrix_free(int N, int ** adj_matrix);
//void node_compare(int i, int j);


int main(int argc, char const *argv[])
{	
	int N;
	int M;
	
	scanf("%d", &N);

	//printf("%d\n", N);
	scanf("%d", &M);
	//printf("%d\n", M);

//make and fill adjacency matrix
	int ** adj_matrix = adj_matrix_init(N);
	int a;
	int b;
	while(1){
		scanf("%d %d", &a, &b);
		adj_matrix[a-1][b-1] = 1;
		if(feof(stdin)){
			break;
		}
	}

//make an array of the nodes
	struct node * node_array = malloc(sizeof(struct node)*N);
	node_init(&node_array[0], 1);
	//("%d\n", node_array[0].sp_len);
	for(int i=1; i<N; i++){
		node_init(&node_array[i], 0);
	}

//loop through matrix and update node characteristics
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(adj_matrix[i][j] == 1){
				if(node_array[j].sp_len > (node_array[i].sp_len +1)){
					node_array[j].sp_len = node_array[i].sp_len +1;
					node_array[j].sp_count = node_array[i].sp_count;

				}else if(node_array[j].sp_len == (node_array[i].sp_len +1)){
					node_array[j].sp_count += node_array[i].sp_count;
				}

				if(node_array[j].lp_len < node_array[i].lp_len +1){
					node_array[j].lp_len = node_array[i].lp_len +1;
					node_array[j].lp_count = node_array[i].lp_count;

				}else if(node_array[j].lp_len == node_array[i].lp_len +1){
					node_array[j].lp_count += node_array[i].lp_count;
				}
				/*
					printf("jslen:%d\n", node_array[j].sp_len);
					printf("islen:%d\n", node_array[i].sp_len);
					printf("jllen%d\n", node_array[j].lp_len);
					printf("illen:%d\n", node_array[i].lp_len);
				*/
			}
		}
	}

	printf("Shortest path: %d\n", node_array[N-1].sp_len);
	printf("Number of short paths: %d\n", node_array[N-1].sp_count);
	printf("Longest path: %d\n", node_array[N-1].lp_len);
	printf("Number of long paths: %d\n", node_array[N-1].lp_count);

	free(node_array);
	adj_matrix_free(N, adj_matrix);
	
	return 0;
}

void node_init(struct node * new_node, int is_s){ //creates new node, returns NULL if something goes wrong
	if (new_node != NULL){
		if(is_s){
			new_node->sp_len = 0;
			new_node->sp_count = 1;
			new_node->lp_len = 0;
			new_node->lp_count = 1;
		}else{
			new_node->sp_len = INT_MAX;		//update
			new_node->sp_count = 0;
			new_node->lp_len = INT_MIN;     //update
			new_node->lp_count = 0;
		}
	};
}


int ** adj_matrix_init(int N){
	int **adj_matrix = malloc(sizeof(int*) * N);
	if(adj_matrix == NULL){
		return NULL;
	}
	for(int i=0; i<N; i++){
		adj_matrix[i] = malloc(sizeof(int) * N);
		if(adj_matrix[i] == NULL){
			free(adj_matrix);
			for(int j=0; j<i; j++){
				free(adj_matrix[j]);
			}
			return NULL;
		}
		for(int j=0; j<N; j++){
			adj_matrix[i][j] = 0;
		}
	}
	return adj_matrix;
}

void adj_matrix_free(int N, int ** adj_matrix){
	for(int i=0; i<N; i++){
		free(adj_matrix[i]);
	}
	free(adj_matrix);
}
