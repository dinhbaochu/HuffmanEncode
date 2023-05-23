#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char input;  // input characters
    int freq;  // input frequency
    struct Node *left, *right;  //left & right child nodes of this node
};

int k = 0; //Travel each character in the message

char encode_output [500] = ""; //create the output array 

// Create memory for new node with specific character and given frequency
struct Node* newNode (char input, int freq) {
    struct Node* new = (struct Node*) malloc(sizeof(struct Node));
    new->left = new->right = NULL;
    new->input = input;
    new->freq = freq;
    return new;
};

// Swap two nodes
void swap(struct Node** node1, struct Node** node2) {
    struct Node* temp = *node1;
    *node1 = *node2;
    *node2 = temp;
};

// Connect the nodes
struct Tree {
    int size; //size of node
    int capa; //capacity of node
    struct Node **arr; //the array of node pointers
};

// Create a node by given capacity
struct Tree* createNode (int capa) {
    struct Tree* tree = (struct Tree*) malloc(sizeof(struct Tree));
    tree->size = 0; 
    tree->capa = capa;
    tree->arr = (struct Node**)malloc(tree->capa * sizeof(struct Node*));
    return tree;
};

// give the left and right node the index (theory of binary tree)
void Index(struct Tree* tree, int idx) {
    int least = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    //compared the frequency of the nodes and assigne the index least
    if ((left < tree->size) && (tree->arr[left]->freq < tree->arr[least]->freq)) {
        least = left;
    }

	if ((right < tree->size) && (tree->arr[right]->freq < tree->arr[least]->freq)) {
	    least = right;
	}

    // swap the nodes if the smallest value is in the left/right of the nodes
    if (least != idx) {
        swap(&tree->arr[least], &tree->arr[idx]);
        // recursive for the next stage
        Index(tree,least);
    }
}

//Extract the min value node from the tree
struct Node* min(struct Tree* tree) {
    struct Node* intial = tree->arr[0];
    //first element in array
    tree->arr[0] = tree->arr[tree->size - 1];
    --tree->size;
    //find the index of nodes in the three, starting from 0
    Index (tree, 0);
    return intial;
};

// Merge new node to the Tree
void Merge (struct Tree* tree, struct Node* node) {
    ++tree->size;
    int i = tree->size - 1;
    // nodes in binary tree theory
    while (i && node->freq < tree->arr[(i-1)/2]->freq) {
        tree->arr[i] = tree->arr[(i-1)/2];
        i = (i-1)/2;
    }
    tree->arr[i] = node;
}

//From the above functions, we build a tree
void Build (struct Tree* tree) {
    int n = tree->size - 1;
    int i;
    // loop 
    for (i = (n - 1) / 2; i >= 0; i--) {
        Index(tree,i);
    }
}

// Insert the data (input & frequency) to the tree, the tree has the capacity same as the size of input
struct Tree* data(char input[], int freq[], int size) {
    struct Tree* tree = createNode(size);
    int i = 0;
    // add new nodes to the array in the tree
    for (i; i < size; i++) {
        tree->arr[i] = newNode(input[i], freq[i]);
    }
    tree->size = size;
    Build(tree);   
    return tree;
};
// check if the size of the tree is 1 or not
    int size1 (struct Tree* tree) {
        return (tree->size == 1);
    }
// The main algo in Huffman Coding
struct Node* Huffman (char input[], int freq[], int size) {
    struct Node *left, *right, *internal;
    struct Tree* tree = data (input, freq, size);


    // loop untill the size of the tree is not 1
    while (!size1(tree)) {
        // find the two nodes that have two min frequency values
        left = min(tree);
		right = min(tree);

        // create an internal node with frequency equal to sum of two minimum frequencies
        internal = newNode('$',left->freq + right->freq);
        // current left and right become the child nodes of the internal node
        internal->left = left;
		internal->right = right;

        Merge(tree, internal);
    }
    return min(tree);
};
// check if the node is left (right or left)
    int checkLeaf(struct Node* root) {
        return (!(root->left) && !(root->right));
        };

// the function to print the decoded message 
void Encode1(struct Node* root, int arr[], int n, char *input_encode) {
    // left nodes are assigned to 0
 
    if (root->left) {
		arr[n] = 0;
		Encode1(root->left, arr, n + 1, input_encode);
	}

    // left nodes are assigned to 1
	if (root->right) {
		arr[n] = 1;
		Encode1(root->right, arr, n + 1, input_encode);
	}
    
    // if the node is leaf, return the encoded binary message for each character
	if (checkLeaf(root)) {
        int i;
		//printf("%c: ", root->input);
        for (i = 0; i < n; i++) {
           
            //printf("%d", arr[i]);
            if (input_encode[k]==root->input){ // If current character in message is the same as the character in the current leaf
		    char value_to_add = arr[i] + '0'; // Add encode sequence to encode_output
            strncat(encode_output,&value_to_add,1);
		}
        }
	}
}
// function to get the input characters and frequency, run the Encode1 function
void HuffmanCodes1(char input[], int freq[], int size, char *input_encode) {
    FILE *fp;
    fp=fopen("encoded.txt","a");
	struct Node* root = Huffman(input, freq, size);
	int arr[100], n = 0;
	for(int i = 0;input_encode[i]!='\0';i++){
	    k = i; //Travel each character in the message and encode it
	    Encode1(root, arr, n, input_encode);
	}
	fprintf(fp, "%s\n",encode_output); // Print encode version to the file 
}

// the function to print the dictionary
void Encode(struct Node* root, int arr[], int n) {
    FILE *fp;
    fp=fopen("encoded.txt","a");
    // left nodes are assigned to 0
    if (root->left) {
		arr[n] = 0;
		Encode(root->left, arr, n + 1);
	}

    // left nodes are assigned to 1
	if (root->right) {
		arr[n] = 1;
		Encode(root->right, arr, n + 1);
	}
    // check if the node is left (right or left)
    int checkLeaf(struct Node* root)  {
        return (!(root->left) && !(root->right));
        };
    // if the node is leaf, return the encoded binary message for each character
	if (checkLeaf(root)) {
        int i;
        fprintf (fp,"%c\n", root->input );
        for (i = 0; i < n; i++) {
          fprintf (fp, "%d", arr[i]);
        }
        fprintf(fp,"\n");
	}   
}
// function to get the input characters and frequency, run the Encode function 
void HuffmanCodes(char input[], int freq[], int size) { 
	struct Node* root = Huffman(input, freq, size);
	int arr[100], n = 0;
	Encode(root, arr, n);
}