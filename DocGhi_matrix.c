#include <stdio.h>
#include <stdlib.h>


void docmatran(char *filename, float matrix[100][100], int *n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        exit(1);
    }
    fscanf(file, "%d", n);
    for (int i = 1; i <= *n; i++) {
        for (int j = 1; j <= *n; j++) {
            fscanf(file, "%f", &matrix[i][j]);
        }
    }
    fclose(file);
}

void ghimatran(char *filename, float matrix[100][100], int n) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file %s\n", filename);
        exit(1);
    }
    fprintf(file, "%d\n", n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fprintf(file, "%5.2f ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void nhanmatran(float A[100][100], float B[100][100], float C[100][100], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            C[i][j] = 0;
            for (int k = 1; k <= n; k++) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

void congmatran(float A[100][100], float B[100][100], float C[100][100], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void doicot(float matrix[100][100], int p, int q, int n) {
    for (int i = 1; i <= n; i++) {
        int temp = matrix[i][p];
        matrix[i][p] = matrix[i][q];
        matrix[i][q] = temp;
    }
}

void inmatran(float matrix[100][100], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%10.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}
void chuyenvi(float C[100][100], float D[100][100], int n) {
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            D[j][i] = C[i][j];
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++)
        printf("%10.2f ", D[i][j]);
        printf("\n");
    }
}
void nhapmatran(float A[100][100], int n){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            printf("Nhap A[%d][%d] = ", i, j);
            scanf("%f", &A[i][j]);
        }
}
int check_matrix(float A[100][100], int n){
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
    if(A[i][j] != 0) return 0;
    return 1;
}
int main() {
    system("cls");
    // KHAI BAO
    char file1[100], file2[100], file3[100];
    float A[100][100], B[100][100], C[100][100], D[100][100];
    int n, m;
    int x;
    char c;

    tryagain:
    // CHON MENU
    printf("MOI BAN CHON MENU: \n");
    printf("1. Doc du lieu tu ban phim. \n");
    printf("2. Doc du lieu tu file. \n");
    printf("3. Tinh ma tran tong va tich. \n");
    printf("4. Doi cot ma tran tich. \n");
    printf("5. Chuyen vi cua ma tran tich. \n");
    printf("6. Ghi ma tran tich vao file. \n");
    printf("7. Ket thuc chuong trinh. \n");
    scanf("%d", &x);
    system("cls");
    // THUC THI
    switch(x) {
        // CASE 1
        case 1:
        printf("BAN DA CHON DOC DU LIEU TU BAN PHIM: \n");
        printf("Nhap cap cua ma tran A: ");
        scanf("%d", &n);
        printf("Nhap cap cua ma tran B: ");
        scanf("%d", &m);
        if(m!=n) {
        printf("Hai ma tran khong cung cap!!!\n");
        printf("\n");
        goto tryagain;
        }
        nhapmatran(A, n);
        printf("\n");
        nhapmatran(B, n);
        printf("\n");
        printf("Ma tran A ban da nhap la: \n");
        inmatran(A, n);
        printf("Matran B ban da nhap la: \n");
        inmatran(B, n);
        goto tryagain;
        // CASE 2
        case 2:
        printf("BAN DA CHON DOC DU LIEU TU FILE: \n");
        printf("Nhap dia chi file chua ma tran A: ");
        scanf("%s", file1);
        printf("Nhap dia chi file chua ma tran B: ");
        scanf("%s", file2);
        docmatran(file1, A, &n);
        int g = n;
        docmatran(file2, B, &n);
        if(g!=n) printf("Hai ma tran khong cung cap!!!");
        printf("\n\n");
        goto tryagain;
        // CASE 3
        case 3:
        printf("BAN DA CHON TINH MA TRAN TONG VA TICH: \n\n");
        if(check_matrix(A, n)) {
            printf("Ma tran tich chua co du lieu!!!\n");
            printf("Nhan ENTER de tiep tuc. \n");
            getchar();
            getchar();
            goto tryagain;
        }
        printf("Tong 2 ma tran A va B: \n");
        congmatran(A, B, C, n);
        inmatran(C, n);
        printf("Tich 2 ma tran A va B: \n");
        nhanmatran(A, B, C, n);
        inmatran(C, n);
        printf("\n");
        printf("Nhan ENTER de tiep tuc. \n");
        getchar();
        getchar();
        goto tryagain;
        // CASE 4
        case 4:
        printf("BAN DA CHON DOI COI MA TRAN TICH: \n\n");
        if(check_matrix(A, n)){
            printf("Ma tran tich chua co du lieu!!!");
            printf("\n");
            printf("Nhan ENTER de tiep tuc. \n");
            getchar();
            getchar();
            goto tryagain;
        }
        int p, q;
        printf("Nhap so cot can doi : ");
        scanf("%d %d", &p, &q);
        if (p <= 0 || q <= 0 || p > n || q > n) {
            printf("Cot khong ton tai!!!");
            goto tryagain;
        }
        doicot(C, p, q, n);
        printf("Ma tran tich sau khi doi cot:\n");
        inmatran(C, n);
        printf("\n");
        printf("Nhan ENTER de tiep tuc. \n");
        getchar();
        getchar();
        goto tryagain;
        // CASE 5
        case 5:
        printf("BAN DA CHON CHUYEN VI CUA MA TRAN TICH: \n");
        if(check_matrix(A, n)){
            printf("Ma tran tich chua co du lieu!!!\n");
            printf("Nhan ENTER de tiep tuc: \n");
            getchar();
            getchar();
            goto tryagain;
        }
        chuyenvi(C, D, n);
        printf("\n");
        printf("Nhan ENTER de tiep tuc. \n");
        getchar();
        getchar();
        goto tryagain;
        // CASE 6
        case 6:
        printf("BAN DA CHON GHI MA TRAN TICH VAO FILE: \n");
        printf("Nhap dia chi file chua ket qua: ");
        scanf("%s", file3);
        ghimatran(file3, C, n);
        printf("\n");
        printf("Nhan ENTER de tiep tuc. \n");
        getchar();
        getchar();
        goto tryagain;
        // CASE 7
        case 7:
        exit(1);
    }
}

