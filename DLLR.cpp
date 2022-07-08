struct node* reverse(struct node* head){
    struct node * T1 = head, struct node * T2 = T1 -> rlink;
    T1 -> rlink = NULL, T1 -> llink = T2;
    while(T2 != NULL){
        T2 -> llink = T2 -> rlink, T2 -> rlink = T1;
        T1 = T2;
        T2 = T2 -> llink;
    }
    head = T1;
    return head;
}



void transpose(term a[], term b[]){
    //b is set to the transpose of a
    int n, i, j, currentb;
    n = a[0].value;       //total number of elements
    b[0].row = a[0].col;  //rows in b = columns in a
    b[0].col = a[0].row;  //columns in b = rows in a
    b[0].value = n;
    if(n > 0){ //non zero matrix
        currentb  =1;
        for(i = 0; i < a[0].col; i++){
            //transpose by the columns in a
            for(j = 1; j <= n; j++){
                //find elements from the current column
                if(a[j].col == i){
                    //elements is in current column, add it to b
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
        }
    }
}



while(stack is not empty){
    //move to position at top of stack
    <row, col, dir> = delete from top of stack;
    while(there are mpre moves from current position){
        <next_row, next_col> = coordinates of next move;
        dir = direction of move;
        if((next_row == EXIT_ROW) && (next_col == EXIT_COL)){
            success;
        }
        if(maze[next_row][next_col] == 0 && mark[next_row][next_col] == 0){
            //logal move and haven't been there
            mark[next_row][next_col] = 1;
            //save current position and direction
            add<row, col, dir>to the top  of the stack
            row = next_row;
            col = next_col;
            dor = north;
        }
    }
}
printf("no path found\n");


void push(element item, int*n){
    //insert item into a max heap of current size *n
    int i;
    if(HEAP_FULL(*n)){
        fprintf(stderr, "the heap is full\n");
        exit(1);
    }
    i = ++(*n);
    while((i != 1) && (item.key > heap[i/2].key)){
        heap[i] = heap[i/2];
        i = i / 2;
    }
    heap[i] = item;
}

element pop(int*n){
    //delete element with the highest key from the heap
    int parent, child;
    element item, temp;
    if(HEAP_FULL(*n)){
        fprintf(stderr, "the heap is full\n");
        exit(1);
    }
    //save value of the element with the highest key
    item = heap[1];
    //use last element in heap to adjust heap
    temp = heap[(*n)--];
    parent = 1;
    child = 2;
    while(child <= *n){
        //find the larger child of the current parent
        if((child < *n) && (heap[child].key < heap[child+1].key){
            child++;
        }
        if(temp.key >= heap[child].key){
            break;
        }
        //move to the next lower level
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}