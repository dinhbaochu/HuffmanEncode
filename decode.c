#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a node
struct Node {
    char character;
    char *encoded_value;
    struct Node *next;
};

// Create node consists of character and its corresponding encoded values
struct Node* createNode(char c, char* encoded) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->character = c;
    node->encoded_value = (char*)malloc(strlen(encoded) + 1);
    strcpy(node->encoded_value, encoded);
    node->next = NULL;
    return node;
}

// Append each node to current linked list
void appendNode(struct Node** head_ref, char c, char* encoded) {
    struct Node* node = createNode(c, encoded);
    // Check if linked list is initialized or not   
    if (*head_ref == NULL) {
        *head_ref = node;
        return;
    }
    struct Node* curr = *head_ref;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = node;
}

void decodeMessage(char* message, struct Node* head) {
    struct Node* curr = head;
    int i = 0;
    while (message[i] != '\0') {
        // Compare set of encoded values with values in each node
        if (strncmp(message+i, curr->encoded_value, strlen(curr->encoded_value)) == 0) {
            printf("%c", curr->character);
            // Output decoded characters to I/O File
            FILE *fptr;
            fptr=fopen("output.txt","a");
            fprintf(fptr, "%c", curr->character);
            i += strlen(curr->encoded_value);
            curr = head;
        } else {
            curr = curr->next;
        }
    }
    printf("\n");
}


int main() {
    FILE *fp;
    char filename[] = "encoded.txt";
    char c, encoded[1000], message[1000] = "";
    struct Node* head = NULL;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Cannot open file %s", filename);
        return 1;
    }

    // read message to be decoded
    fgets(message, sizeof(message), fp);
    strtok(message, "\n");  // remove newline character

    // read characters and their encoded values
    while (fscanf(fp, " %c", &c) == 1) {
        //printf("%c",c);
        fscanf(fp, " %s", encoded);
        appendNode(&head, c, encoded);
    }
    
    fclose(fp);

    // decode message using linked list
    decodeMessage(message, head);

    return 0;
}
