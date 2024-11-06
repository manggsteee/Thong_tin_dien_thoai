#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char maSanPham[50];
    char thoiHan[21];
    char ngayMua[11];
    float gia;
} DienThoai;

bool namNhuan(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getNgay(int year, int month) {
    if (month == 1 || month == 3 || month == 5 || month == 7
        || month == 8 || month == 10 || month == 12)
        return 31;
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    if (namNhuan(year))
        return 29;
    return 28;
}

void ngayHetHan(DienThoai dienThoai) {
    int day, month, year, cnt = 0, exDate;
    char *type;
    char *buyDate = strtok(dienThoai.ngayMua, "/");
    while (buyDate != NULL) {
        if (cnt == 0)
            day = atoi(buyDate);
        else if (cnt == 1)
            month = atoi(buyDate);
        else if (cnt == 2)
            year = atoi(buyDate);
        cnt++;
        buyDate = strtok(NULL, "/");
    }
    cnt = 0;
    char *expiredDate = strtok(dienThoai.thoiHan, " ");
    while (expiredDate != NULL) {
        if (cnt == 0)
            exDate = atoi(expiredDate);
        else if (cnt == 1)
            type = expiredDate;
        cnt++;
        expiredDate = strtok(NULL, " ");
    }
    for (int i = 0; i < strlen(type); i++)
        printf("type[%d] = %c\n", i, type[i]);
    cnt = 0;
    if (strcmp(type, "ngay") == 0) {
        printf("true");
        while (cnt < exDate) {
            int limitDate = getNgay(year, month);
            if (day < limitDate)
                day++;
            else if (month == 12) {
                day = 1;
                month = 1;
                year++;
            } else {
                day = 1;
                month++;
            }
            cnt++;
        }
    } else if (strcmp(type, "thang") == 0)
        while (cnt < exDate) {
            if (month == 12) {
                month = 1;
                year++;
            } else
                month++;
            cnt++;
        }
    else
        while (cnt < exDate) {
            year++;
            cnt++;
        }
    printf("Ngay het han: %d/%d/%d\n", day, month, year);
}

void nhap(DienThoai *dienThoai) {
    printf("Nhap thong tin dien thoai:\n");
    printf("Ma san pham: ");
    fgets(dienThoai->maSanPham, 50, stdin);
    dienThoai->maSanPham[strcspn(dienThoai->maSanPham, "\n")] = '\0';
    printf("Thoi han bao hanh: ");
    fgets(dienThoai->thoiHan, 21, stdin);
    dienThoai->thoiHan[strcspn(dienThoai->thoiHan, "\n")] = '\0';
    printf("Ngay mua hang: ");
    fgets(dienThoai->ngayMua, 11, stdin);
    dienThoai->ngayMua[strcspn(dienThoai->ngayMua, "\n")] = '\0';
    printf("Gia tien: ");
    scanf("%f", &dienThoai->gia);
}

void swap(DienThoai *a, DienThoai *b) {
    DienThoai temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sapxep(DienThoai *dienThoai, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((dienThoai + i)->gia > (dienThoai + j)->gia) {
                swap(dienThoai + i, dienThoai + j);
            }
        }
    }
}

int main(void) {
    printf("Cau a:\n");
    DienThoai* dienThoai = malloc(sizeof(DienThoai));
    nhap(dienThoai);
    ngayHetHan(*dienThoai);
    free(dienThoai);

    printf("Cau b:\n");
    int n;
    do {
        printf("Nhap so thong tin dien thoai ban muon nhap: ");
        scanf("%d", &n);
    } while (n > 100);
    getchar();
    DienThoai *dien_thoai = malloc(sizeof(DienThoai) * n);
    for (int i = 0; i < n; i++) {
        nhap(dien_thoai + i);
        if (i != n - 1)
            getchar();
    }
    sapxep(dien_thoai,n);
    for (int i = 0; i < n; i++) {
        printf("%f \t",(dien_thoai + i)->gia);
    }
    free(dien_thoai);
    return 0;
}
