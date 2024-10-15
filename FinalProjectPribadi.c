#include <stdio.h>
#include <string.h>

struct game {
    char code[10];
    int rank;
    int kill;
    int assist;
    int death;
    char survival_time[10];
};

void display_data() {
    char temp_code[10];
    struct game data;
    FILE *file = fopen("history.txt", "r");

    printf("\n==============================================================\n");
    printf("\t\t      HISTORY MATCH\n");
    printf("==============================================================\n");
    printf("\n Game Code\tRank\tKill\tAssist\tDeath\tSurvival Time\n");

    while (fscanf(file, "%s %d %d %d %d %s\n", temp_code, &data.rank, &data.kill, &data.assist, &data.death, data.survival_time) != EOF) {
        printf(" %s\t\t%d\t%d\t%d\t%d\t%s\n\n", temp_code, data.rank, data.kill, data.assist, data.death, data.survival_time);
    }
    fclose(file);
}

void add_data(struct game data) {
    FILE *file = fopen("history.txt", "a");
    fprintf(file, "%s %d %d %d %d %s\n", data.code, data.rank, data.kill, data.assist, data.death, data.survival_time);
    fclose(file);
}

void delete_data(char code[10]) {
    char temp_code[10];
    char temp[1000];
    struct game data;
    FILE *file = fopen("history.txt", "r");
    FILE *temp_file = fopen("temp.txt", "w");
    while (fscanf(file, "%s %d %d %d %d %s\n", temp_code, &data.rank, &data.kill, &data.assist, &data.death, data.survival_time) != EOF) {
        if (strcmp(temp_code, code) != 0) {
            sprintf(temp, "%s %d %d %d %d %s\n", temp_code, data.rank, data.kill, data.assist, data.death, data.survival_time);
            fputs(temp, temp_file);
        }
    }
    fclose(file);
    fclose(temp_file);
    remove("history.txt");
    rename("temp.txt", "history.txt");
}

void search_data(char code[10]) {
    char temp_code[10];
    struct game data;
    int found = 0;
    FILE *file = fopen("history.txt", "r");
    while (fscanf(file, "%s %d %d %d %d %s\n", temp_code, &data.rank, &data.kill, &data.assist, &data.death, data.survival_time) != EOF) {
        if (strcmp(temp_code, code) == 0) {

            printf("\n==============================================================\n");
            printf("\t\t      HISTORY MATCH\n");
            printf("==============================================================\n");
            printf("\n Game Code\tRank\tKill\tAssist\tDeath\tSurvival Time\n");

            printf(" %s\t\t%d\t%d\t%d\t%d\t%s\n\n", temp_code, data.rank, data.kill, data.assist, data.death, data.survival_time);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Data tidak ditemukan.\n");
    }
    fclose(file);
}

int main() {
    int choice;
    struct game data;
    char code[10];
    while (1) {
        printf("Menu:\n");
        printf("1. Tampilkan data\n");
        printf("2. Tambah data\n");
        printf("3. Hapus data\n");
        printf("4. Cari data\n");
        printf("5. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                display_data();
                break;
            case 2:
                printf("\nMasukkan kode permainan: ");
                scanf("%s", data.code);
                printf("Masukkan peringkat: ");
                scanf("%d", &data.rank);
                printf("Masukkan kill: ");
                scanf("%d", &data.kill);
                printf("Masukkan assist: ");
                scanf("%d", &data.assist);
                printf("Masukkan death: ");
                scanf("%d", &data.death);
                printf("Masukkan survival time (hh:mm:ss): ");
                scanf("%s", data.survival_time);
                add_data(data);
                printf("Data berhasil ditambahkan.\n");
                break;
            case 3:
                printf("Masukkan kode permainan: ");
                scanf("%s", code);
                delete_data(code);
                printf("Data berhasil dihapus.\n");
                break;
            case 4:
                printf("Masukkan kode permainan: ");
                scanf("%s", code);
                search_data(code);
                break;
            case 5:
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    }
    return 0;
}
