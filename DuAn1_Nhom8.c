#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<errno.h>

                                                //KHỞI TẠO CÁC STRUCT
struct NgaySinh{
    unsigned int Ngay;
    unsigned int Thang;
    unsigned int Nam;
};

struct element {
    unsigned long MNV;
    char Ten[50];
    struct NgaySinh NgaySinh;
    char GioiTinh[4];
    int DonVi;
    char ChucVu[3];
    double HeSoLuong;
    double Luong;
    double PhuCap;
    double ThucLinh;
};
struct Node {
    struct element val;
    struct Node *next;
    struct Node *prev;
};
typedef struct Node *List;
typedef struct Node *Position;

                                                //HÀM TẠO HEADERNODE CHO LIST
Position createList(){
    Position headerNode = malloc(sizeof(struct Node));
    headerNode->next = NULL;
    headerNode->prev = NULL;
    return headerNode;
}
// Hàm kiểm tra giá trị trong mảng (Dơn vị) đã tồn tại hay chưa
int mang[20];
int so_luong_phan_tu = 0;
bool kiem_tra_trung_lap(int gia_tri) {
    for (int i = 0; i < so_luong_phan_tu; i++) {
        if (mang[i] == gia_tri) {
            return true;
        }
    }
    return false;
}
// Hàm lưu giá trị của Đơn vị vào mảng
void luu_gia_tri(int gia_tri) {
    // kiem tra trung lap
    if (!kiem_tra_trung_lap(gia_tri)) {
        mang[so_luong_phan_tu] = gia_tri;
        so_luong_phan_tu++;
    }
}
                                                //HÀM CHÈN VÀO DANH SÁCH LIÊN KẾT
void InsertIntoList(List pL, struct element e){
    Position newItem = malloc(sizeof(struct Node));
    Position p = pL;
    newItem->val = e;
    while (p->next != NULL) p = p->next;
    newItem->next = p->next;
    p->next = newItem;
    newItem->prev = p;
    luu_gia_tri(newItem->val.DonVi);
}
                                                //HÀM HIỂN THỊ DANH SÁCH LIÊN KẾT
void Display(List pL) {
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|STT|Ma Nhan Vien| Ten                          | Ngay Sinh  | Gioi Tinh | Don Vi | Chuc Vu | He So Luong | Luong         | Phu Cap      | Thuc Linh      |\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    pL = pL->next;
    int count = 1;
    while (pL != NULL) {
        printf("|%-3d|%-12llu| %-29s| %-2u/%02u/%-5u| %-10s| %-6d | %-7s | %-11.2lf | %-13.2lf | %-12.2lf | %-14.2lf |\n", 
               count, 
               pL->val.MNV, 
               pL->val.Ten, 
               pL->val.NgaySinh.Ngay, 
               pL->val.NgaySinh.Thang, 
               pL->val.NgaySinh.Nam, 
               pL->val.GioiTinh, 
               pL->val.DonVi, 
               pL->val.ChucVu, 
               pL->val.HeSoLuong, 
               pL->val.Luong, 
               pL->val.PhuCap, 
               pL->val.ThucLinh);
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        count++;
        pL = pL->next;
    }

    
}

                                                //HÀM XOÁ NHÂN VIÊN CÓ ĐỘ TUỔI TRÊN 60
void Delete_NV_60(List pL){
    Position p = pL->next;
    while(p != NULL){
        if(p->val.NgaySinh.Nam < 1964) {
            Position temp = p;
            p->prev->next = p->next;
            if(p->next != NULL)
                p->next->prev = p->prev;
            p = p->next;
            free(temp);
        } else {
            p = p->next;
        }
    }
}

                                                //HÀM TÍNH LUONG
void Tinh_luong(List pL) {
    Position p = pL->next;
    while (p != NULL) {
        p->val.Luong = 0;
        p->val.Luong = (p->val.HeSoLuong) * 1800000.0;
        p = p->next;
    }
}

                                                //HÀM TÍNH PHỤ CẤP
void Phu_cap(List pL) {
    Position p = pL->next;
    Tinh_luong(pL);
    while (p != NULL) {
        if (strcmp(p->val.ChucVu, "GD") == 0 || strcmp(p->val.ChucVu, "PGD") == 0) {
            p->val.PhuCap = 0.5 * p->val.Luong;
        } else if (strcmp(p->val.ChucVu, "TP") == 0 || strcmp(p->val.ChucVu, "PP") == 0) {
            p->val.PhuCap = 0.25 * p->val.Luong;
        }
        p = p->next;
    }
}

                                                //HÀM TÍNH THỰC LĨNH
void Thuc_Linh(List pL) {
    Position p = pL->next;
        Phu_cap(pL);
    while (p != NULL) {
        p->val.ThucLinh = p->val.Luong + p->val.PhuCap;
        p = p->next;
    }
}

                                                //HÀM HIỂN THỊ BẢNG SỐ LIỆU THEO ĐƠN VỊ
void Display_BTK_DonVi(List pL, int mang[20]) {
    printf("--------------------------------------------------------------------------\n");
    printf("| Don Vi | So Nhan Vien | Ti le NV Nam | Ti le NV Nu | Tong thuc linh    |\n");
    printf("--------------------------------------------------------------------------\n");

    for(int i = 0; i < so_luong_phan_tu; i++) {
        int male_count = 0;
        int female_count = 0;
        double total_salary = 0;
        Position p = pL->next;
        while (p != NULL) {
            if (p->val.DonVi == mang[i]) {
                total_salary += p->val.ThucLinh;
                if (strcmp(p->val.GioiTinh, "Nam") == 0) male_count++;
                else female_count++;
            }
            p = p->next;
        }
        if (male_count + female_count == 0) continue;

        double Percent_male = (double)(male_count) * 100 / (male_count + female_count);
        double Percent_female = (double)(female_count) * 100 / (male_count + female_count);

        printf("| %-6d | %-12d | %-11.2lf%% | %-10.2lf%% | %-17.2lf |\n", mang[i], male_count + female_count, Percent_male, Percent_female, total_salary);
        printf("--------------------------------------------------------------------------\n");
    }

    
}

                                                //HÀM NHẬP DỮ LIỆU NHÂN VIÊN TỪ BÀN PHÍM
struct element Nhap(struct element e, List pL) {
    char s[4];
    printf("Nhap ma nhan vien: ");
    scanf("%llu", &e.MNV);
    getchar();
    pL = pL->next;
    while(pL != NULL){
        if(pL->val.MNV == e.MNV){
            printf("Ma nhan vien da ton tai !!!\n");
            e.MNV = 0;
            return e;
        }
        pL = pL->next;
    }
    printf("Nhap ten nhan vien: ");
    fgets(e.Ten, sizeof(e.Ten), stdin);
    // Loai bo ky tu \n neu co
    size_t len = strlen(e.Ten);
    if (len > 0 && e.Ten[len-1] == '\n') {
        e.Ten[len-1] = '\0';
    }

    printf("Nhap gioi tinh (Nam/Nu): ");
    fgets(s, sizeof(s), stdin);
    // Loai bo ky tu \n neu co
    len = strlen(s);
    if (len > 0 && s[len-1] == '\n') {
        s[len-1] = '\0';
    }
    strcpy(e.GioiTinh, s);

    printf("Nhap ngay sinh (Ngay Thang Nam): ");
    scanf("%u %u %u", &e.NgaySinh.Ngay, &e.NgaySinh.Thang, &e.NgaySinh.Nam);
    getchar();

    printf("Nhap don vi cong tac: ");
    scanf("%d", &e.DonVi);
    getchar();

    printf("Nhap chuc vu: ");
    fgets(e.ChucVu, sizeof(e.ChucVu), stdin);
    // Loai bo ky tu \n neu co
    len = strlen(e.ChucVu);
    if (len > 0 && e.ChucVu[len-1] == '\n') {
        e.ChucVu[len-1] = '\0';
    }

    printf("Nhap he so luong: ");
    scanf("%lf", &e.HeSoLuong);
    return e;
}

                                                //HÀM NHẬP DỮ LIỆU NHÂN VIÊN TỪ FILE
void Nhap_Tu_File(char *ten_file, List pL) {
    FILE *file = fopen(ten_file, "r");
    if (file == NULL) {
        printf("Khong the mo file! %s\n", strerror(errno));
        exit(1);
    }

    struct element e;
    while (fscanf(file, "%lu", &e.MNV) == 1) {
        fgetc(file); // Doc ky tu '\n' sau MNV
        fgets(e.Ten, sizeof(e.Ten), file);
        // Loai bo ky tu \n neu co
        size_t len = strlen(e.Ten);
        if (len > 0 && e.Ten[len-1] == '\n') {
            e.Ten[len-1] = '\0';
        }

        fscanf(file, "%u", &e.NgaySinh.Ngay);
        fscanf(file, "%u", &e.NgaySinh.Thang);
        fscanf(file, "%u", &e.NgaySinh.Nam);
        fscanf(file, "%s", e.GioiTinh);
        fscanf(file, "%d", &e.DonVi);
        fscanf(file, "%s", e.ChucVu);
        fscanf(file, "%lf", &e.HeSoLuong);
        InsertIntoList(pL, e);
    }
    fclose(file);
}
// Hàm xóa ký tự xuống dòng ở cuối chuỗi
void remove_newline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

                                                //HÀM GHI DỮ LIỆU NHÂN VIÊN VÀO FILE
void Ghi_Vao_File(char *ten_file, struct element e) {
    FILE *file = fopen(ten_file, "a");
    if (file == NULL) {
        printf("Không thể mở file! %s\n", strerror(errno));
        exit(1);
    }

    // Xóa ký tự xuống dòng ở cuối chuỗi tên nếu có
    remove_newline(e.Ten);
    remove_newline(e.GioiTinh);

    // Ghi dữ liệu vào file
    fprintf(file, "%lu\n", e.MNV);       // Ghi MNV trên một dòng
    fprintf(file, "%s\n", e.Ten);        // Ghi Tên trên một dòng
    // Ghi các thông tin còn lại trên một dòng
    fprintf(file, "%u %u %u %s %d %s %.2lf\n", e.NgaySinh.Ngay, e.NgaySinh.Thang, e.NgaySinh.Nam, e.GioiTinh, e.DonVi, e.ChucVu, e.HeSoLuong);

    fclose(file);
}

                                                //HÀM GIẢI PHÓNG LIST
Position freeList(List *pL) {
    Position p = (*pL)->next;
    while (p != NULL) {
        Position temp = p;
        p = p->next;
        free(temp);
    }
    free(*pL);
    return (NULL);
}

// Hàm hoán đổi 2 element
void swap(Position a, Position b){
    struct element temp;
    temp = a->val;
    a->val = b->val;
    b->val = temp;
}

                                                //HÀM SẮP SẾP MÃ NHÂN VIÊN
void Bubble_sort_MNV(List pL){
    pL = pL->next;
    if(pL == NULL){
        printf("DANH SACH TRONG !!!");
        return;
    }

    bool swapped;
    Position p, lp = NULL;

    do{
        swapped = false;
        p = pL;

        while (p->next != lp) {
            if(p->val.MNV > p->next->val.MNV){
                swap(p, p->next);
                swapped = true;
            }
            p = p->next;
        }
        lp = p;
    } while (swapped);
}

                                                //HÀM SẮP SẾP THEO ĐƠN VỊ
void Bubble_sort_DonVi(List pL){
    pL = pL->next;
    if(pL == NULL){
        printf("DANH SACH TRONG !!!");
        return;
    }

    bool swapped;
    Position p, lp = NULL;

    do{
        swapped = false;
        p = pL;

        while (p->next != lp) {
            if(p->val.DonVi > p->next->val.DonVi){
                swap(p, p->next);
                swapped = true;
            }
            p = p->next;
        }
        lp = p;
    } while (swapped);
}

                                                //HÀM SẮP SẾP THEO THỰC LĨNH
void Bubble_sort_ThucLinh(List pL){
    pL = pL->next;
    if(pL == NULL){
        printf("DANH SACH TRONG !!!");
        return;
    }

    bool swapped;
    Position p, lp = NULL;

    do{
        swapped = false;
        p = pL;

        while (p->next != lp) {
            if(p->val.ThucLinh > p->next->val.ThucLinh){
                swap(p, p->next);
                swapped = true;
            }
            p = p->next;
        }
        lp = p;
    } while (swapped);
}

                                                //HÀM TÌM KIẾM MÃ NHÂN VIÊN
void Tim_Kiem(List pL, unsigned long MNV){
    Position p = pL->next;
    if(p == NULL){
        printf("DANH SACH TRONG !!!\n");
        return;
    }
    while(p != NULL){
        if(p->val.MNV == MNV) {
            printf("\nTHONG TIN NHAN VIEN (MNV: %llu)\n", MNV);
            printf("Ten nhan vien: %s\nNgay sinh: %u/%u/%u\nGioi tinh: %s\nDon vi: %d\nChuc vu: %s", p->val.Ten,
            p->val.NgaySinh.Ngay, p->val.NgaySinh.Thang, p->val.NgaySinh.Nam, p->val.GioiTinh, p->val.DonVi, p->val.ChucVu);
            return;
        }
        p = p->next;
    }
    printf("Khong tim thay nhan vien co MNV: %llu", MNV);
}
                                                //HÀM SỬA THÔNG TIN NHÂN VIÊN
void Chinh_Sua(List pL, unsigned long MNV){
    Position p = pL->next;
    if(p == NULL){
        printf("DANH SACH TRONG !!!\n");
        return;
    }
    while(p != NULL){
        if(p->val.MNV == MNV) {
            printf("\nTHONG TIN NHAN VIEN (MNV: %llu)\n", MNV);
            printf("Ten nhan vien: %s\nNgay sinh: %u/%u/%u\nGioi tinh: %s\nDon vi: %d\nChuc vu: %s", p->val.Ten,
            p->val.NgaySinh.Ngay, p->val.NgaySinh.Thang, p->val.NgaySinh.Nam, p->val.GioiTinh, p->val.DonVi, p->val.ChucVu);
            break;
        }
        p = p->next;
    }
    if(p == NULL){
        printf("Khong tim thay nhan vien co MNV: %llu\n", MNV);
        return;
    }
    printf("\n\nNhap thong tin can sua doi:\n");
    printf("1.Ma nhan vien\n2.Ho&Ten\n3.Ngay Sinh(Ngay Thang Nam)\n4.Gioi Tinh\n5.Don Vi\n6.Chuc Vu\n");
    int c;
    scanf("%d", &c);
    getchar();
    switch(c) {
        case 1:
        printf("Nhap ma sua doi: ");
        unsigned long mnv;
        scanf("%llu", &mnv);
        p->val.MNV = mnv;
        break;
        case 2:
        printf("Nhap Ho&Ten sua doi: ");
        char s[50];
        fgets(s, sizeof(s), stdin);
        // Loai bo ky tu \n neu co
        size_t len = strlen(s);
        if (len > 0 && s[len-1] == '\n') {
        s[len-1] = '\0';
        }
        strcpy(p->val.Ten, s);
        break;
        case 3:
        printf("Nhap Ngay sinh (Ngay Thang Nam) sua doi: ");
        unsigned int Ngay, Thang, Nam;
        scanf("%u%u%u", &Ngay, &Thang, &Nam);
        p->val.NgaySinh.Ngay = Ngay;
        p->val.NgaySinh.Thang = Thang;
        p->val.NgaySinh.Nam = Nam;
        break;
        case 4:
        printf("Nhap Gioi Tinh sua doi: ");
        char m[4];
        scanf("%s", &m);
        strcpy(p->val.GioiTinh, m);
        break;
        case 5:
        printf("Nhap Don Vi sua doi: ");
        int x;
        scanf("%d", &x);
        p->val.DonVi = x;
        break;
        case 6:
        printf("Nhap Chuc Vu sua doi: ");
        char n[3];
        scanf("%s", &n);
        strcpy(p->val.ChucVu, n);
    }
}              
                                                //HÀM MAIN                                  
int main(){
    system("cls");
    // Khai bao
    struct element e;
    char file[100] = "D:\\PBL1\\file1.txt";
    List pL = createList();
    Nhap_Tu_File(file, pL);
    int x;
    // MENU
    tryagain:
    printf("\n\t\tQUAN LY NHAN VIEN\n");
    printf("    (Tac gia: VO THANH NHAN - DANG QUANG SON)\n");
        printf("+");
        for(int i = 0; i <= 50; i++)
        printf("-");
        printf("+\n");
            printf("| %-50s|\n","1. Doc du lieu tu file");
            printf("| %-50s|\n","2. Doc du lieu tu ban phim");
            printf("| %-50s|\n","3. Xoa Nhan vien co do tuoi > 60");
            printf("| %-50s|\n","4. Hien thi danh sach");
            printf("| %-50s|\n","5. Thong ke");
            printf("| %-50s|\n","6. Sap xep Ma Nhan Vien tang dan");
            printf("| %-50s|\n","7. Sap xep Don Vi tang dan");
            printf("| %-50s|\n","8. Sap xep Thuc Linh tang dan");
            printf("| %-50s|\n","9. Tim kiem nhan vien");
            printf("| %-50s|\n","10. Chinh sua thong tin nhan vien");
            printf("| %-50s|\n","11. Ket thuc chuong trinh");
        printf("+");
        for(int i=0; i <= 50; i++) printf("-");printf("+\n\n");
    printf("Nhap lua chon: ");
    scanf("%d", &x);
    switch(x) {
        case 1:
            system("cls");
            printf("DOC DU LIEU TU FILE\nNhap dia chi chua file: \n");
            scanf("%s", &file);
            Nhap_Tu_File(file, pL);
            printf("Nhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
        case 2:
            system("cls");
            printf("DOC DU LIEU TU BAN PHIM\n");
            e = Nhap(e, pL);
            if(e.MNV == 0){
                printf("Nhan ENTER de tiep tuc!!!");
                getchar();
                goto tryagain;
            }
            InsertIntoList(pL, e);
            FILE *f = fopen(file, "a");
            if (f == NULL) {
            printf("\nNhap dia chi file can luu du lieu: ");
            scanf("%s", file);
            }
            Ghi_Vao_File(file, e);
            printf("Nhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
        case 3:
            system("cls");
            Delete_NV_60(pL);
            printf("DA XOA NHAN VIEN CO DO TUOI TREN 60\n");
            printf("Nhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
        case 4:
            Thuc_Linh(pL);
            system("cls");
            printf("HIEN THI DANH SACH: \n");
            Display(pL);
            printf("Nhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
        case 5:
            Thuc_Linh(pL);
            system("cls");
            printf("HIEN THI BANG SO LIEU THEO DON VI: \n");
            Display_BTK_DonVi(pL,mang);
            printf("Nhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
        case 6:
            system("cls");
            Bubble_sort_MNV(pL);
            printf("DA SAP XEP THEO MA NHAN VIEN(MNV)\n");
            printf("Nhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
        case 7:
            system("cls");
            Bubble_sort_DonVi(pL);
            printf("DA SAP XEP THEO DON VI\n");
            printf("Nhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
        case 8:
            system("cls");
            Bubble_sort_ThucLinh(pL);
            printf("DA SAP XEP THEO THUC LINH\n");
            printf("Nhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
        case 9:
            system("cls");
            if(pL->next == NULL){
                printf("DANH SACH TRONG !!!\n");
                goto tryagain;
            }
            printf("Nhap Ma nhan vien can tim kiem: ");
            unsigned long MNV;
            scanf("%llu", &MNV);
            Tim_Kiem(pL, MNV);
            printf("\nNhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
        case 10:
            system("cls");
            printf("Nhap ma nhan vien can sua doi: ");
            unsigned long mnv;
            scanf("%llu", &mnv);
            Chinh_Sua(pL, mnv);
            printf("Nhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
        case 11:
            pL = freeList(&pL);
            system("cls");
            printf("KET THUC !!!\n");
            exit(1);
        default:
            system("cls");
            printf("NHAP SAI DU LIEU !!!\n");
            printf("Nhan ENTER de tiep tuc!!!");
            getchar();
            getchar();
            goto tryagain;
    }
}
