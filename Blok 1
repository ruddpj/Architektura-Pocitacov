#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

void fibbonaci() {
    int k; // Input od užívateľa
    printf("Zadajte vrchnú hodnotu: ");
    scanf("%d", &k);

    int a = 1; // Začiatočné premenné
    int b = 1;
    printf("1\n");

    while (b <= k) { // While loop kým b je menšie rovné ako k
        printf("%i\n", b);
        int c = a;
        a = b;
        b = c + a;
    }
}

long int factorial(int x) { // Faktoriál (x!) som zobral len pre cases ktoré môžu nastať
    long int fac_num = 1;
    while (x > 0) {
        fac_num = fac_num * x;
        x--;
    }
    return fac_num;
}

double power(double x, int y) {   // aj keď v math library je funkcia pow() aka mocnina, nechcel som používať špeciálne
    int i;                      // build parametre, lebo som nevedel v akom stave vám odovzdám projekt
    double value = x;            // keby som dal 'gcc main.c -o main -lm' tak by to buildlo aj s pow()
    for (i = 1; i < y; i++) {
        x = value*x;
    }
    return x;
}

double pi_float_mod(double x) {   // Rovnaký problém ako pow() ale táto funkcia berie len jeden parameter lebo
    while ((x < (-1)*M_PI || x > M_PI)) { // je to potrebné len raz s rovnakým deliteľom
        if (x >= M_PI) {           // Dostaneme hodnotu medzi -pi a pi, čo je perióda sin(x) aka 2pi
            x = x - 2*M_PI;
        } else if (x <= (-1)*M_PI) {
            x = x + 2*M_PI;
        }
    }
    return x;
}

double sinus(double radians, double epsilon) {
    double prev_num = 0; // Predošlé číslo môže byť ľubovoľné
    radians = pi_float_mod(radians*M_PI); // Hodnota v radiánoch pre interval -pi až pi
    double curr_num = radians;
    int x = 3;
    int bit = -1; // Hodnota sa strieda pre záporný a kladný člen

    while (fabs(prev_num-curr_num) > epsilon) { // Kontrola o koľko sa zmenila hodnota
        prev_num = curr_num; // Výmena
        curr_num = curr_num + bit*((power(radians, x)) / (factorial(x)));
        bit = bit * (-1);
        x = x + 2;
    }

    return curr_num;
}

void intel_hex(char* hex) {
    int len_hex = strlen(hex);  // Získame takto dĺžku inputnutého stringu
    int i;
    int value = 0;  // Toto bude súčet hexadecimálnych dvojčísel v dekadickom zápise
    for (i = 1; i < len_hex-2; i = i + 2) { // Začíname od index 1 lebo index 0 je ':' a končíme o dve miesta skôr
        char word[2] = {hex[i], hex[i+1]};  // Vytvoríme string s dvoma charaktermi
        value = value + strtol(word, NULL, 16); // 'strtol' z stdlib library premení string na long int
    }
    printf("%x\n", (256 - value%256)); // Pri printovaní vieme zadať dekadické číslo s format specifierom "%x"
}                                            // pre hexadecimálne čísla

void dec_to_bin_to_hex(int a) {
    printf("%d\n", a);
    printf("%x\n", a);

    int bin_value[32];
    int i;
    for (i = 0; a > 0; i++) {
        if (a % 2) {
            bin_value[i] = 1;
        } else {
            bin_value[i] = 0;
        }
        a = a / 2;
    }

    int j;
    for (j = i-1; j >= 0; j--) {
        printf("%d", bin_value[j]);
    }

    printf("\n");
}

void dek_to_rimske(int a) {
    int dek_num[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *roman_num[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int i;
    for (i = 0; i < 13; i++) {
        while (a >= dek_num[i]) {
            printf("%s", roman_num[i]);
            a = a - dek_num[i];
        }
    }
    printf("\n");
}

void strojove_epsilon() {
    printf("float.h lib:\nFLT_EPSILON: %.32lf\nDBL_EPSILON: %.32lf\nMoje výsledky:\n", FLT_EPSILON, DBL_EPSILON);

    float flt_x = 1, flt_one = 1;
    double dbl_x = 1, dbl_one = 1;

    while (flt_one + flt_x != flt_one) {
        flt_x = flt_x / 2;
    }
    printf("Float: %.32f\n", flt_x*2);

    while (dbl_one + dbl_x != dbl_one) {
        dbl_x = dbl_x / 2;
    }
    printf("Double: %.32lf\n", dbl_x*2);
}


int main() {
    printf("/// Úloha 1.3\n");
    fibbonaci();

    printf("/// Úloha 1.5\n");
    double mult;
    printf("Zadajte násobok pi: ");
    scanf("%lf", &mult);
    printf("%f\n", sinus(((mult)), 0.0000001));

    printf("/// Úloha 1.6\n");
    char hex_num[64];
    printf("Zadajte reťazec: ");
    scanf("%s", *&hex_num);
    intel_hex(hex_num);

    printf("// Úloha 1.1\n");
    dec_to_bin_to_hex(33777);
    dec_to_bin_to_hex('X');

    printf("// Úloha 1.2\n");
    dek_to_rimske(2024);

    printf("// Úloha 1.4\n");
    strojove_epsilon();

    return 0;
}
