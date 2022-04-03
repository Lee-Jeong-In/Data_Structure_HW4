#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;           // 사용자가 사용하고 싶은 기능을 담아둠
    int row, col;           // 사용자에가 만들고 싶은 배열의 행과 열의 크기를 받음

    srand(time(NULL));      // rand()함수를 사용하기 위한 seed값 + time()를 사용해서 seed값이 계속 변화하도록 한다.

    printf("[----- [이정인]  [2019038015] -----]\n");

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);

    int** matrix_a = create_matrix(row, col);       // 배열을 만든다.
    int** matrix_b = create_matrix(row, col);       // 배열을 만든다.
    int** matrix_a_t = create_matrix(col, row);     // 배열을 만든다. 이때, transpose되었으므로 행과 열의 값도 바뀐다.
    if (matrix_a == NULL || matrix_b == NULL || matrix_a_t == NULL) {return -1;}      // matrix_a_t가 생성이 안되면..?? ==> 오류

    printf("Matrix Created.\n");

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);                 // 사용자에게 원하는 기능을 받는다.

        switch(command) {                       //  switch문을 사용해 7가지의 경우의 수로 흐름을 나눈다.
        case 'z': case 'Z':                     //  사용자가 알파벳의 소문자, 대문자 모두 사용할 수 있기 때문에 대비한다.
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);      // command에 맞는 기능을 하는 함수를 호출한다.
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            print_matrix(matrix_a,row,col);
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);      // 프로그램을 종료하기전에 이중포인터로 만든 동적할당을 Heap에서 제거해준다.
            free_matrix(matrix_a, row, col);    
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if(row<=0 &&col<=0)                                     // pre
    {
        printf("Check the sizes of row and col! \n");
        return NULL;
    }

    int **arr_entry=(int**)malloc(sizeof(int*)*row);        // 배열에 들어가는 요소를 넣은 포인터 선언
                                                            // 이때 row를 곱하는 이유는 행에 따라 열이 생성 될것이다.
    for(int i=0;i<row;i++)
        arr_entry[i]=(int*)malloc(sizeof(int)*col);         // arr_entry[i]는 i번째 행을 의미하므로, 그에 따른 col를 생성

    return arr_entry;                                       // 이차원 배열을 만들수 있는 이중포인터를 반환해 준다.

    if (arr_entry == NULL)                                  // post
    {
        printf("Fail to create! \n");
        return NULL;
    }
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if(matrix==NULL || row<=0 || col<=0)                    // pre
    {
        printf("Can't print!\n");
        return ;
    }

    printf("\n <matrix>\n");

    for(int i=0;i<row;i++)                                  // 매개변수로 들어온 이중포인터를 이용해
    {                                                       //  matrix에 들어있는 값을 하나씩 출력한다.
        for(int j=0;j<col;j++)                              // 이때, 이중포인터이므로 값에 직접 접근하려면 이중for문을 사용해야하고
            printf("%d\t",matrix[i][j]);                    //  행부터 접근한다.
        printf("\n");
    }

    if (matrix == NULL)                                     // post
    {
	    printf("Fail to print.\n");
		return;
	}

    return ;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{

	if (matrix == NULL || row <= 0 || col <= 0)             // pre
    {
		printf("Can't free!\n");
		return -1;
	}

    for (int i = 0; i < row; i++) 
	    free(matrix[i]);                // 행에 대한 포인터변수를 해제
	
	free(matrix);                       // 이중포인터에 대한 포인터변수를 해제
     return 0;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{    
    if(matrix==NULL || row<=0 || col<=0)        // pre  
    {
        printf("Can't print!\n");
        return NULL;
    }

    for(int i=0;i<row;i++)                      // 배열에 들어가야 할 요소를 이중for문을 사용해 넣는다.
        for(int j=0;j<col;j++)
            matrix[i][j]=rand()%20;             // 이때 들어가야 할 값은 0~19 까지 이므로  %20를 사용해 20을 넘지 않도록 해준다.

    print_matrix(matrix,row,col);               // 만들었으면 출력해서 확인한다.

    if (matrix == NULL)                         // post
    {
	    printf("Fail to print.\n");
		return -1;
	}
    
    return 0;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if(matrix_a==NULL ||matrix_b==NULL || row<=0 || col<=0)     // pre
    {
        printf("Can't create!\n");
        return NULL;
    }

    int** matrix_add=create_matrix(row,col);                    // 계산을 위한 임의의 이중포인터를 선언한다.

    for(int i=0;i<row;i++)                                      // 행렬의 덧셈을 계산하는 방법이다.
        for(int j=0;j<col;j++)                                  // 이중포인터이기 때문에 이중for문으로 접근한다.
            matrix_add[i][j]=matrix_a[i][j]+matrix_b[i][j];

    printf("====After addition====");

    print_matrix(matrix_add,row,col);                           // 기능을 제대로 했는지 출력해서 확인한다.

    if (matrix_add == NULL)                                     // post
    {
	    printf("Fail to sum.\n");
		return -1;
	}

    free_matrix(matrix_add,row,col);                            // 계산을 위해 사용했던 임의의 이중포인터를 Heap에서 해제한다.
    return 0;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if(matrix_a==NULL ||matrix_b==NULL || row<=0 || col<=0)     // pre
    {
        printf("Can't create!\n");
        return NULL;
    }

    int** matrix_sub=create_matrix(row,col);                    // 계산을 위한 임의의 이중포인터를 선언한다.

    for(int i=0;i<row;i++)                                      // 행렬의 뺄셈을 계산하는 방법이다.
        for(int j=0;j<col;j++)                                  // 이중포인터이기 때문에 이중for문으로 접근한다.
            matrix_sub[i][j]=matrix_a[i][j]-matrix_b[i][j];

    printf("====After subtraction====");
    print_matrix(matrix_sub,row,col);                           // 기능을 제대로 했는지 출력해서 확인한다.

    if (matrix_sub == NULL)                                     // post
    {
	    printf("Fail to subtract.\n");
		return -1;
	}

    free_matrix(matrix_sub,row,col);                            // 계산을 위해 사용했던 임의의 이중포인터를 Heap에서 해제한다.
    return 0;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if(matrix==NULL ||matrix_t==NULL || row<=0 || col<=0)       // pre
    {   
        printf("Can't create!\n");
        return NULL;
    }

    for(int i=0;i<row;i++)                                      // 전치행열을 만드는 방법이다.
        for(int j=0;j<col;j++)                                  // 전치행열을 원래행열의 행과 열의 위치를 바꾼 행렬이다.
            matrix_t[i][j]=matrix[j][i];

    printf("====After transpose====");
    print_matrix(matrix_t,row,col);                             // 기능을 제대로 했는지 출력해서 확인한다.

    if (matrix_t == NULL)                                       // post
    {
	    printf("Fail to transpose.\n");
		return -1;
	}
    return 0;

}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{


	if (row <= 0 || col <= 0)                                   // pre
    {
		printf("Check the size of row and col!\n");
		return -1;
	}

    int** matrix_mul = create_matrix(row, row);                 // row*col 과 col*row 행렬을 곱하면 row*row 형태의 행렬이 나온다.
                                                                // 계산을 위한 임의의 이중포인터를 선언한다.

	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++)      // 우선 계산하려는 행렬의 행을 접근한다.
    {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++)  // 우선 계산하려는 행렬의 행을 접근한다.
        {
			int temp = 0;                                               // 행렬의 곱은 첫번째 행열의 행과 두번째 행열의 열의 요소의 곱들의 합이므로,
                                                                        // 합을 저장해줄 변수를 선언한다.
			for (int matrix_col = 0; matrix_col < col; matrix_col++)    // 열을 바꿔가면서 각각의 요소들에게 접근한다.
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];    // 접근한 요소로 계산법에 맞도록 연산해준다.
			matrix_mul[matrix_a_row][matrix_t_row] = temp;              // 연산된 값을 곱의 행열의 요소에 대입한다.
		}
	}
	print_matrix(matrix_mul, row, row);                         // 기능을 제대로 했는지 출력해서 확인한다.
	free_matrix(matrix_mul, row, col);                          // 계산을 위해 사용했던 임의의 이중포인터를 Heap에서 해제한다.

    if (matrix_t == NULL || matrix_mul ==NULL)                  // post
    {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
}
