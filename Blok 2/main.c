#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

static int iBase, iAdd, iRes;
static char iChRes;
static char iArRes[12];

void ass_add() {
    printf("Úloha 2.1.1\n");
    scanf("%d %d", &iBase, &iAdd);
    iRes = 0;

    asm(".intel_syntax noprefix \n"

        "mov eax, iBase  \n"
        "mov ecx, iAdd  \n"
        "add eax, ecx   \n"
        "mov iRes, eax  \n"

        ".att_syntax    \n");

    printf("%d\n", iRes);
}

void ass_double() {
    printf("Úloha 2.1.2\n");
    scanf("%d", &iBase);
    iRes = 0;

    asm(".intel_syntax noprefix \n"

        "mov eax, iBase  \n"
        "shl eax, 1     \n"
        "mov iRes, eax  \n"

        ".att_syntax    \n");

    printf("%d\n", iRes);
}

void ass_dec2hex() {
    printf("Úloha 2.1.3\n");
    scanf("%d", &iBase);

    asm(".intel_syntax noprefix \n"

        "mov eax, iBase  \n"
        "cmp eax, 9   \n"
        "jg tennup      \n"
        "add eax, -7   \n"
        "mov iChRes, eax     \n"
        "tennup:    \n"
        "add eax, 55   \n"
        "mov iChRes, eax     \n"

        ".att_syntax    \n");

    printf("%c\n", iChRes);

}

void ass_cpuid() {
    printf("Úloha 2.1.4\n");
    asm(".intel_syntax noprefix \n"

        "mov eax, 0  \n"
        "cpuid     \n"
        "mov iArRes[0], ebx     \n"
        "mov iArRes[4], edx     \n"
        "mov iArRes[8], ecx     \n"
        "mov iRes, eax      \n"

        ".att_syntax    \n");

    printf("%s\n", iArRes);
    printf("%d\n", iRes);
}

void ram_string() {
    printf("Úloha 2.2\n");
    char veta[] = "architektura_pocitacov_je_super_predmet";
    printf("%s\n", veta);

    char* pointer = (char *) &veta;
    printf("%p\n", pointer);

    pointer++;
    *pointer = '9';
    printf("%s\n", veta);

    /*pointer += 1000000000;
    *pointer = 3;
    printf(":3\n");*/

    int arr[3] = {1,2,3};
    printf("%d %d %d\n", arr[0], arr[1], arr[2]);

    int* ptr = (int *) &arr;
    printf("%p\n", ptr);

    ptr++;
    *ptr = 1024;
    printf("%d %d %d\n", arr[0], arr[1], arr[2]);
}

void disk_poviedka() {
    printf("Úloha 2.3.1\n");
    FILE * file = fopen("poviedka.html", "r");
    FILE * dest = fopen("prelozena_poviedka.html", "w");

    if (file == NULL) {
        printf("ERROR\n");
        return;
    }

    while (feof(file) == 0) {
        int c = getc(file);
        switch (c) {
            case 165:
                fprintf(dest, "%c", 188);
                break;
            case 169:
                fprintf(dest, "%c", 138);
                break;
            case 171:
                fprintf(dest, "%c", 141);
                break;
            case 174:
                fprintf(dest, "%c", 142);
                break;
            case 181:
                fprintf(dest, "%c", 190);
                break;
            case 185:
                fprintf(dest, "%c", 154);
                break;
            case 187:
                fprintf(dest, "%c", 157);
                break;
            case 190:
                fprintf(dest, "%c", 158);
                break;
            default:
                fprintf(dest, "%c", c);
        }
    }

    fclose(file);
    fclose(dest);
    printf("DONE\n");
}

void disk_koniec() {
    printf("Úloha 2.3.2\n");
    FILE * file = fopen("koniec_poviedky.html", "rb");
    FILE * dest = fopen("prelozeny_koniec.html", "w");

    if (file == NULL) {
        printf("ERROR\n");
        return;
    }

    while (feof(file) == 0) {
        int c = getc(file);
        if (c != EOF) {
            fprintf(dest, "%c", c ^ 27);
        }
    }

    fclose(file);
    fclose(dest);
    printf("DONE\n");
}

void main_menu() {
    printf("|--------------------------------|\n");
    printf("|  0:play  ▶\uFE0F                    |\n");
    printf("|  1:pause ⏸\uFE0F                    |\n");
    printf("|  2:stop  ⏹\uFE0F                    |\n");
    printf("|--------------------------------|\n");
}

void song_list(const char *arr[], const int n) {
    printf("|--------------------------------|\n");
    for (int i = 0; i < n; i++) {
        printf("|         - %.10s           |\n", arr[i]);
    }
    printf("|--------------------------------|\n");
}

void playing(char arg[]) {
    printf("|--------------------------------|\n");
    printf("|          NOW PLAYING           |\n");
    printf("|         - %.10s           |\n", arg);
    printf("|       ▶\uFE0F(0) ⏸\uFE0F(1) ⏹\uFE0F(2)        |\n");
    printf("|--------------------------------|\n");
}


void mm_audio() {
    printf("Úloha 2.4\n");
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    int oper;
    char arg[64];
    const char *playlist[3] = {"audio1.mp3", "audio2.mp3", "audio3.mp3"};
    const int n = 3;


    Mix_Music *music = NULL;
    main_menu();
    scanf("%d", &oper);
    while (oper != 2) {

        if (oper == 0) {
            song_list(playlist, n);
            scanf("%s", arg);
            music = Mix_LoadMUS(arg);
            Mix_PlayMusic(music, 1);
            playing(arg);
        } else if (oper == 1) {
            Mix_PauseMusic();
            main_menu();
        }
        scanf("%d", &oper);
    }
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}

int main(){
    // Úloha 2.1.1          (1b)
    ass_add();

    // Úloha 2.1.2          (1b)
    ass_double();

    // Úloha 2.1.3          (3b)
    ass_dec2hex();

    // Úloha 2.1.4          (2b)
    ass_cpuid();

    // Úloha 2.2            (3b) Niekedy má compiler problém pri kompilácii ak sú tam assembler úlohy
    ram_string();

    // Úloha 2.3.1          (2b)
    disk_poviedka();

    // Úloha 2.3.2          (1b)
    disk_koniec();

    // Úloha 2.4            (4b)
    mm_audio();

    return(0);
}
