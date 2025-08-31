#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int A, F, B, C, M1, T, M, M2, M9;
int D9, E, X, X1;
int D1, D3, F1, F2, F9;
int K8, S4, L1, C1;
int S5, S6, T1;
int B3, B1;
char input_buffer[100];
char shooting_words[5][10] = {"", "BANG", "BLAM", "POW", "WHAM"};

void print_instructions();
void initial_purchases();
void set_date();
void beginning_turn();
void stop_at_fort();
int get_input_with_validation(const char* prompt, int min, int max);
float get_float_input(const char* prompt);
void hunting();
void eating();
void riders_attack();
void select_events();
void mountains();
void dying(int cause);
void final_turn();
void shooting_subroutine();
void illness_subroutine();
float random_float();
int random_int(int max);
void print_supplies();

int main() {
    char response[10];

    srand((unsigned int)time(NULL));

    printf("DO YOU NEED INSTRUCTIONS (YES/NO)? ");
    fgets(response, sizeof(response), stdin);
    for(int i = 0; response[i] && response[i] != '\n'; i++) {
        response[i] = toupper(response[i]);
    }
    response[strcspn(response, "\n")] = 0;

    if (strncmp(response, "NO", 2) != 0) {
        print_instructions();
    }

    X1 = 1;
    K8 = S4 = F1 = F2 = M = M9 = D3 = 0;
    T = 700;

    printf("\nHOW GOOD A SHOT ARE YOU WITH YOUR RIFLE?\n");
    printf("  (1) ACE MARKSMAN,  (2) GOOD SHOT,  (3) FAIR TO MIDDLIN'\n");
    printf("  (4) NEED MORE PRACTICE,  (5) SHAKY KNEES\n");
    printf("ENTER ONE OF THE ABOVE -- THE BETTER YOU CLAIM YOU ARE, THE\n");
    printf("FASTER YOU'LL HAVE TO BE WITH YOUR GUN TO BE SUCCESSFUL.\n");

    D9 = get_input_with_validation("", 1, 5);
    if (D9 > 5) D9 = 5;

    initial_purchases();

    printf("AFTER ALL YOUR PURCHASES, YOU NOW HAVE $%d DOLLARS LEFT\n", T);
    printf("MONDAY MARCH 29 1847\n");

    while (M < 2040) {
        set_date();
        if (M >= 2040) break;

        beginning_turn();
        
        if (F < 0) {
            dying(1);
            return 0;
        }

        eating();

        M += 200 + (A - 220) / 3 + random_int(10);
        L1 = C1 = 0;

        riders_attack();
        select_events();
        mountains();

        if (K8 == 1 || S4 == 1) {
            T -= 20;
            if (T < 0) {
                printf("YOU CAN'T AFFORD A DOCTOR\n");
                dying(4);
                return 0;
            }
            printf("DOCTOR'S BILL IS $20\n");
            K8 = S4 = 0;
        }

        if (F < 0) {
            dying(1);
            return 0;
        }
        if (M1 < 0) {
            dying(2);
            return 0;
        }
        if (B < 0) {
            dying(3);
            return 0;
        }
    }

    final_turn();
    return 0;
}

void print_instructions() {
    printf("THIS PROGRAM SIMULATES A TRIP OVER THE OREGON TRAIL FROM\n");
    printf("INDEPENDENCE, MISSOURI TO OREGON CITY, OREGON IN 1847.\n");
    printf("YOUR FAMILY OF FIVE WILL COVER THE 2040 MILE OREGON TRAIL\n");
    printf("IN 5-6 MONTHS --- IF YOU MAKE IT ALIVE.\n");

    printf("YOU HAD SAVED $900 TO SPEND FOR THE TRIP, AND YOU'VE JUST\n");
    printf("  PAID $200 FOR A WAGON.\n");
    printf("YOU WILL NEED TO SPEND THE REST OF YOUR MONEY ON THE\n");
    printf("  FOLLOWING ITEMS:\n");

    printf("  OXEN - YOU CAN SPEND $200-$300 ON YOUR TEAM\n");
    printf("  THE MORE YOU SPEND, THE FASTER YOU'LL GO\n");
    printf("  BECAUSE YOU'LL HAVE BETTER ANIMALS\n");

    printf("  FOOD - THE MORE YOU HAVE, THE LESS CHANCE THERE\n");
    printf("  IS OF GETTING SICK\n");

    printf("  AMMUNITION - $1 BUYS A BELT OF 50 BULLETS\n");
    printf("  YOU WILL NEED BULLETS FOR ATTACKS BY ANIMALS\n");
    printf("  AND BANDITS, AND FOR HUNTING FOOD\n");

    printf("  CLOTHING - THIS IS ESPECIALLY IMPORTANT FOR THE COLD\n");
    printf("  WEATHER YOU WILL ENCOUNTER WHEN CROSSING\n");
    printf("  THE MOUNTAINS\n");

    printf("  MISCELLANEOUS SUPPLIES - THIS INCLUDES MEDICINE AND\n");
    printf("  OTHER THINGS YOU WILL NEED FOR SICKNESS\n");
    printf("  AND EMERGENCY REPAIRS\n");

    printf("YOU CAN SPEND ALL YOUR MONEY BEFORE YOU START YOUR TRIP -\n");
    printf("OR YOU CAN SAVE SOME OF YOUR CASH TO SPEND AT FORTS ALONG\n");
    printf("THE WAY WHEN YOU RUN LOW. HOWEVER, ITEMS COST MORE AT\n");
    printf("THE FORTS. YOU CAN ALSO GO HUNTING ALONG THE WAY TO GET\n");
    printf("MORE FOOD.\n");

    printf("WHENEVER YOU HAVE TO USE YOUR TRUSTY RIFLE ALONG THE WAY,\n");
    printf("YOU WILL BE TOLD TO TYPE IN THAT WORD (ONE THAT SOUNDS LIKE A\n");
    printf("GUN SHOT). THE FASTER YOU TYPE IN THAT WORD AND HIT THE\n");
    printf("\"RETURN\" KEY, THE BETTER LUCK YOU'LL HAVE WITH YOUR GUN.\n");

    printf("AT EACH TURN, ALL ITEMS ARE SHOWN IN DOLLAR AMOUNTS\n");
    printf("EXCEPT BULLETS\n");
    printf("WHEN ASKED TO ENTER MONEY AMOUNTS, DON'T USE A \"$\".\n");

    printf("GOOD LUCK!!!\n");
}

void initial_purchases() {
    float f_val;
    
    do {
        printf("HOW MUCH DO YOU WANT TO SPEND ON YOUR OXEN TEAM? ");
        f_val = get_float_input("");
        A = (int)f_val;
        if (A < 200 || A > 300) {
            printf(A < 200 ? "NOT ENOUGH\n" : "TOO MUCH\n");
        }
    } while (A < 200 || A > 300);

    do {
        f_val = get_float_input("HOW MUCH DO YOU WANT TO SPEND ON FOOD? ");
        F = (int)f_val;
        if (F < 0) printf("IMPOSSIBLE\n");
    } while (F < 0);

    do {
        f_val = get_float_input("HOW MUCH DO YOU WANT TO SPEND ON AMMUNITION? ");
        B = (int)f_val;
        if (B < 0) printf("IMPOSSIBLE\n");
    } while (B < 0);

    do {
        f_val = get_float_input("HOW MUCH DO YOU WANT TO SPEND ON CLOTHING? ");
        C = (int)f_val;
        if (C < 0) printf("IMPOSSIBLE\n");
    } while (C < 0);

    do {
        f_val = get_float_input("HOW MUCH DO YOU WANT TO SPEND ON MISCELLANEOUS SUPPLIES? ");
        M1 = (int)f_val;
        if (M1 < 0) printf("IMPOSSIBLE\n");
    } while (M1 < 0);

    T = 700 - A - F - B - C - M1;

    if (T < 0) {
        printf("YOU OVERSPENT--YOU ONLY HAD $700 TO SPEND. BUY AGAIN\n");
        initial_purchases();
        return;
    }

    B = 50 * B;
}

void set_date() {
    D3++;
    printf("MONDAY ");

    const char* dates[] = {
        "MARCH 29", "APRIL 12", "APRIL 26", "MAY 10", "MAY 24", "JUNE 7",
        "JUNE 21", "JULY 5", "JULY 19", "AUGUST 2", "AUGUST 16",
        "AUGUST 31", "SEPTEMBER 13", "SEPTEMBER 27", "OCTOBER 11",
        "OCTOBER 25", "NOVEMBER 8", "NOVEMBER 22", "DECEMBER 6", "DECEMBER 20"
    };

    if (D3 >= 20) {
        printf("YOU HAVE BEEN ON THE TRAIL TOO LONG ------\n");
        printf("YOUR FAMILY DIES IN THE FIRST BLIZZARD OF WINTER\n");
        dying(5);
        return;
    }

    printf("%s 1847\n", dates[D3]);
}

void beginning_turn() {
    if (F < 0) F = 0;
    if (B < 0) B = 0;
    if (C < 0) C = 0;
    if (M1 < 0) M1 = 0;

    if (F < 13) {
        printf("YOU'D BETTER DO SOME HUNTING OR BUY FOOD SOON!!!!\n");
    }

    M2 = M;

    if (M9 == 1) {
        printf("TOTAL MILEAGE IS 950\n");
        M9 = 0;
    } else {
        printf("TOTAL MILEAGE IS %d\n", M);
    }

    print_supplies();

    if (X1 == 1) {
        printf("DO YOU WANT TO (1) HUNT, OR (2) CONTINUE? ");
        X = get_input_with_validation("", 1, 2);
    } else {
        printf("DO YOU WANT TO (1) STOP AT THE NEXT FORT, (2) HUNT, OR (3) CONTINUE? ");
        X = get_input_with_validation("", 1, 3);
    }

    if ((X == 1 && X1 == 1) || (X == 2 && X1 == -1)) { // Hunting
        if (B <= 39) {
            printf("TOUGH---YOU NEED MORE BULLETS TO GO HUNTING\n");
            // Reroute to continue if hunting is not possible
            if (X1 == 1) X = 2;
            else X = 3;
        }
    }

    if (X1 == 1) {
        if (X == 1) hunting();
        else {
            if (B <= 39) {
                printf("TOUGH---YOU NEED MORE BULLETS TO GO HUNTING\n");
            }
        }
    } else {
        if (X == 1) stop_at_fort();
        else if (X == 2) hunting();
    }
}

void stop_at_fort() {
    float P;

    printf("ENTER WHAT YOU WISH TO SPEND ON THE FOLLOWING\n");

    P = get_float_input("FOOD? ");
    if (P >= 0 && T >= P) {
        T -= (int)P;
        F += (int)(2.0/3.0 * P);
    } else if (P > 0) {
        printf("YOU DON'T HAVE THAT MUCH--KEEP YOUR SPENDING DOWN\n");
        printf("YOU MISS YOUR CHANCE TO SPEND ON THAT ITEM\n");
    }

    P = get_float_input("AMMUNITION? ");
    if (P >= 0 && T >= P) {
        T -= (int)P;
        B += (int)(2.0/3.0 * P * 50);
    } else if (P > 0) {
        printf("YOU DON'T HAVE THAT MUCH--KEEP YOUR SPENDING DOWN\n");
        printf("YOU MISS YOUR CHANCE TO SPEND ON THAT ITEM\n");
    }

    P = get_float_input("CLOTHING? ");
    if (P >= 0 && T >= P) {
        T -= (int)P;
        C += (int)(2.0/3.0 * P);
    } else if (P > 0) {
        printf("YOU DON'T HAVE THAT MUCH--KEEP YOUR SPENDING DOWN\n");
        printf("YOU MISS YOUR CHANCE TO SPEND ON THAT ITEM\n");
    }

    P = get_float_input("MISCELLANEOUS SUPPLIES? ");
    if (P >= 0 && T >= P) {
        T -= (int)P;
        M1 += (int)(2.0/3.0 * P);
    } else if (P > 0) {
        printf("YOU DON'T HAVE THAT MUCH--KEEP YOUR SPENDING DOWN\n");
        printf("YOU MISS YOUR CHANCE TO SPEND ON THAT ITEM\n");
    }

    M -= 45;
}

void hunting() {
    if (B <= 39) {
        printf("TOUGH---YOU NEED MORE BULLETS TO GO HUNTING\n");
        return;
    }

    M -= 45;
    shooting_subroutine();

    if (B1 <= 1) {
        printf("RIGHT BETWEEN THE EYES---YOU GOT A BIG ONE!!!!\n");
        printf("FULL BELLIES TONIGHT!\n");
        F += 52 + random_int(6);
        B -= 10 + random_int(4);
    } else if ((random_float() * 100) < (13 * B1)) {
        printf("YOU MISSED---AND YOUR DINNER GOT AWAY.....\n");
    } else {
        printf("NICE SHOT--RIGHT ON TARGET--GOOD EATIN' TONIGHT!!\n");
        F += 48 - 2 * B1;
        B -= 10 + 3 * B1;
    }
}

void eating() {
    printf("DO YOU WANT TO EAT (1) POORLY (2) MODERATELY\n");
    printf("OR (3) WELL? ");
    E = get_input_with_validation("", 1, 3);

    int food_needed = 8 + 5 * E;

    if (F < food_needed) {
        printf("YOU CAN'T EAT THAT WELL\n");
        eating();
        return;
    }

    F -= food_needed;
}

void riders_attack() {
    float attack_chance = ((M / 100.0 - 4) * (M / 100.0 - 4) + 72) / ((M / 100.0 - 4) * (M / 100.0 - 4) + 12) - 1;

    if (random_float() * 10 > attack_chance) return;

    printf("RIDERS AHEAD. THEY ");
    S5 = 0;

    if (random_float() < 0.8) {
        printf("DON'T ");
        S5 = 1;
    }
    printf("LOOK HOSTILE\n");

    printf("TACTICS\n");
    printf("(1) RUN (2) ATTACK (3) CONTINUE (4) CIRCLE WAGONS\n");
    
    T1 = get_input_with_validation("", 1, 4);

    if (S5 == 1) {
        switch (T1) {
            case 1:
                M += 15;
                A -= 10;
                break;
            case 2:
                M -= 5;
                B -= 100;
                break;
            case 3:
                break;
            case 4:
                M -= 20;
                break;
        }
        if (random_float() <= 0.8) {
            printf("RIDERS WERE FRIENDLY, BUT CHECK FOR POSSIBLE LOSSES\n");
        } else {
            printf("THEY DID NOT ATTACK\n");
        }
    } else {
        switch (T1) {
            case 1:
                M += 20;
                M1 -= 15;
                B -= 150;
                A -= 40;
                break;
            case 2:
                shooting_subroutine();
                B -= B1 * 40 + 80;
                if (B1 <= 1) {
                    printf("NICE SHOOTING---YOU DROVE THEM OFF\n");
                } else if (B1 <= 4) {
                    printf("KINDA SLOW WITH YOUR COLT .45\n");
                } else {
                    printf("LOUSY SHOT---YOU GOT KNIFED\n");
                    K8 = 1;
                    printf("YOU HAVE TO SEE OL' DOC BLANCHARD\n");
                }
                break;
            case 3:
                if (random_float() <= 0.8) {
                    B -= 150;
                    M1 -= 15;
                } else {
                    printf("THEY DID NOT ATTACK\n");
                    return;
                }
                break;
            case 4:
                shooting_subroutine();
                B -= B1 * 30 + 80;
                M -= 25;
                if (B1 <= 1) {
                    printf("NICE SHOOTING---YOU DROVE THEM OFF\n");
                } else if (B1 <= 4) {
                    printf("KINDA SLOW WITH YOUR COLT .45\n");
                } else {
                    printf("LOUSY SHOT---YOU GOT KNIFED\n");
                    K8 = 1;
                    printf("YOU HAVE TO SEE OL' DOC BLANCHARD\n");
                }
                break;
        }
        printf("RIDERS WERE HOSTILE--CHECK FOR LOSSES\n");
    }
}

void select_events() {
    int event_chances[] = {6, 11, 13, 15, 17, 22, 32, 35, 37, 42, 44, 54, 64, 69, 95};
    float R1 = random_float() * 100;
    int event_num = 0;

    for (int i = 0; i < 15; i++) {
        if (R1 <= event_chances[i]) {
            event_num = i + 1;
            break;
        }
    }
    
    if (event_num == 0) {
        printf("HELPFUL INDIANS SHOW YOU WHERE TO FIND MORE FOOD\n");
        F += 14;
        return;
    }

    switch (event_num) {
        case 1:
            printf("WAGON BREAKS DOWN--LOSE TIME AND SUPPLIES FIXING IT\n");
            M -= 15 + random_int(5);
            M1 -= 8;
            break;
        case 2:
            printf("OX INJURES LEG---SLOWS YOU DOWN REST OF TRIP\n");
            M -= 25;
            A -= 20;
            break;
        case 3:
            printf("BAD LUCK---YOUR DAUGHTER BROKE HER ARM\n");
            printf("YOU HAD TO STOP AND USE SUPPLIES TO MAKE A SLING\n");
            M -= 5 + random_int(4);
            M1 -= 2 + random_int(3);
            break;
        case 4:
            printf("OX WANDERS OFF---SPEND TIME LOOKING FOR IT\n");
            M -= 17;
            break;
        case 5:
            printf("YOUR SON GETS LOST---SPEND HALF THE DAY LOOKING FOR HIM\n");
            M -= 10;
            break;
        case 6:
            printf("UNSAFE WATER--LOSE TIME LOOKING FOR CLEAN SPRING\n");
            M -= random_int(10) + 2;
            break;
        case 7:
            if (M > 950) {
                printf("COLD WEATHER---BRRRRRRR!--YOU ");
                if (C > 22 + random_int(4)) {
                    printf("HAVE ENOUGH CLOTHING TO KEEP YOU WARM\n");
                } else {
                    printf("DON'T HAVE ENOUGH CLOTHING TO KEEP YOU WARM\n");
                    C1 = 1;
                    illness_subroutine();
                }
            } else {
                printf("HEAVY RAINS---TIME AND SUPPLIES LOST\n");
                F -= 10;
                B -= 500;
                M1 -= 15;
                M -= random_int(10) + 5;
            }
            break;
        case 8:
            printf("BANDITS ATTACK\n");
            shooting_subroutine();
            B -= 20 * B1;
            if (B < 0) {
                printf("YOU RAN OUT OF BULLETS---THEY GET LOTS OF CASH\n");
                T /= 3;
            } else if (B1 <= 1) {
                printf("QUICKEST DRAW OUTSIDE OF DODGE CITY!!!\n");
                printf("YOU GOT 'EM!\n");
            } else {
                printf("YOU GOT SHOT IN THE LEG AND THEY TOOK ONE OF YOUR OXEN\n");
                K8 = 1;
                printf("BETTER HAVE A DOC LOOK AT YOUR WOUND\n");
                M1 -= 5;
                A -= 20;
            }
            break;
        case 9:
            printf("THERE WAS A FIRE IN YOUR WAGON--FOOD AND SUPPLIES DAMAGE!\n");
            F -= 40;
            B -= 400;
            M1 -= random_int(8) + 3;
            M -= 15;
            break;
        case 10:
            printf("LOSE YOUR WAY IN HEAVY FOG---TIME IS LOST\n");
            M -= 10 + random_int(5);
            break;
        case 11:
            printf("YOU KILLED A POISONOUS SNAKE AFTER IT BIT YOU\n");
            B -= 10;
            M1 -= 5;
            if (M1 < 0) {
                printf("YOU DIE OF SNAKEBITE SINCE YOU HAVE NO MEDICINE\n");
                dying(2);
                return;
            }
            break;
        case 12:
            printf("WAGON GETS SWAMPED FORDING RIVER--LOSE FOOD AND CLOTHES\n");
            F -= 30;
            C -= 20;
            M -= 20 + random_int(20);
            break;
        case 13:
            printf("WILD ANIMALS ATTACK!\n");
            shooting_subroutine();
            if (B <= 39) {
                printf("YOU WERE TOO LOW ON BULLETS--\n");
                printf("THE WOLVES OVERPOWERED YOU\n");
                K8 = 1;
                dying(4);
                return;
            }
            if (B1 <= 2) {
                printf("NICE SHOOTIN' PARDNER---THEY DIDN'T GET MUCH\n");
            } else {
                printf("SLOW ON THE DRAW---THEY GOT AT YOUR FOOD AND CLOTHES\n");
            }
            B -= 20 * B1;
            C -= B1 * 4;
            F -= B1 * 8;
            break;
        case 14:
            printf("HAIL STORM---SUPPLIES DAMAGED\n");
            M -= 5 + random_int(10);
            B -= 200;
            M1 -= 4 + random_int(3);
            break;
        case 15:
            if (E == 1) {
                illness_subroutine();
            } else if (E == 3) {
                if (random_float() < 0.5) {
                    illness_subroutine();
                }
            } else {
                if (random_float() <= 0.25) {
                    illness_subroutine();
                }
            }
            break;
    }
}

void mountains() {
    if (M <= 950) return;

    float mountain_event_chance = 9 - (((M / 100.0 - 15) * (M / 100.0 - 15) + 72) / ((M / 100.0 - 15) * (M / 100.0 - 15) + 12));
    
    if (random_float() * 10 > mountain_event_chance) {
        printf("RUGGED MOUNTAINS\n");
        float r = random_float();
        if (r <= 0.1) {
            printf("YOU GOT LOST---LOSE VALUABLE TIME TRYING TO FIND TRAIL!\n");
            M -= 60;
        } else if (r <= 0.21) {
            printf("WAGON DAMAGED!---LOSE TIME AND SUPPLIES\n");
            M1 -= 5;
            B -= 200;
            M -= 20 + random_int(30);
        } else {
            printf("THE GOING GETS SLOW\n");
            M -= 45 + (int)(random_float() / 0.02);
        }
    }

    if (F1 == 0 && M >= 950) {
        F1 = 1;
        if (random_float() < 0.8) {
            printf("BLIZZARD IN MOUNTAIN PASS--TIME AND SUPPLIES LOST\n");
            L1 = 1;
            F -= 25;
            M1 -= 10;
            B -= 300;
            M -= 30 + random_int(40);
            if (C < 18 + random_int(2)) {
                illness_subroutine();
            }
        } else {
            printf("YOU MADE IT SAFELY THROUGH SOUTH PASS--NO SNOW\n");
        }
    }

    if (M >= 1700 && F2 == 0) {
        F2 = 1;
        if (random_float() < 0.7) {
            printf("BLIZZARD IN MOUNTAIN PASS--TIME AND SUPPLIES LOST\n");
            L1 = 1;
            F -= 25;
            M1 -= 10;
            B -= 300;
            M -= 30 + random_int(40);
            if (C < 18 + random_int(2)) {
                illness_subroutine();
            }
        }
    }
}

void shooting_subroutine() {
    S6 = random_int(4) + 1;
    printf("TYPE %s: ", shooting_words[S6]);

    clock_t start_time = clock();
    fgets(input_buffer, sizeof(input_buffer), stdin);
    clock_t end_time = clock();

    input_buffer[strcspn(input_buffer, "\n")] = 0;

    for (int i = 0; input_buffer[i]; i++) {
        input_buffer[i] = toupper(input_buffer[i]);
    }

    double response_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    B1 = (int)((response_time * 1000) - (D9 - 1) * 100);

    if (B1 < 0) B1 = 0;
    if (strcmp(input_buffer, shooting_words[S6]) != 0) {
        B1 = 9;
    }

    printf("\n");
}

void illness_subroutine() {
    float r = random_float() * 100;
    
    if (E == 1) { // Poorly
        if (r < 10) {
            printf("MILD ILLNESS---MEDICINE USED\n");
            M -= 5;
            M1 -= 2;
        } else if (r < 100) {
            printf("BAD ILLNESS---MEDICINE USED\n");
            M -= 5;
            M1 -= 2;
        } else {
            printf("SERIOUS ILLNESS---\n");
            printf("YOU MUST STOP FOR MEDICAL ATTENTION\n");
            M1 -= 10;
            S4 = 1;
        }
    } else if (E == 2) { // Moderately
        if (r < 25) {
            printf("MILD ILLNESS---MEDICINE USED\n");
            M -= 5;
            M1 -= 2;
        } else {
            printf("BAD ILLNESS---MEDICINE USED\n");
            M -= 5;
            M1 -= 2;
        }
    } else { // Well
        if (r < 50) {
            printf("MILD ILLNESS---MEDICINE USED\n");
            M -= 5;
            M1 -= 2;
        } else {
            printf("BAD ILLNESS---MEDICINE USED\n");
            M -= 5;
            M1 -= 2;
        }
    }
    
    if (M1 < 0) {
        printf("YOU RAN OUT OF MEDICAL SUPPLIES\n");
        dying(4);
    }
}

void dying(int cause) {
    char response[10];

    switch (cause) {
        case 1:
            printf("YOU RAN OUT OF FOOD AND STARVED TO DEATH\n");
            break;
        case 2:
            printf("YOU DIED OF SNAKEBITE\n");
            break;
        case 3:
            printf("YOU DIED IN COMBAT\n");
            break;
        case 4:
            printf("YOU DIED OF INJURIES OR PNEUMONIA\n");
            break;
        case 5:
            printf("YOUR FAMILY DIES IN THE FIRST BLIZZARD OF WINTER\n");
            break;
    }

    printf("DUE TO YOUR UNFORTUNATE SITUATION, THERE ARE A FEW\n");
    printf("FORMALITIES WE MUST GO THROUGH\n");

    printf("WOULD YOU LIKE A MINISTER? ");
    fgets(response, sizeof(response), stdin);
    printf("WOULD YOU LIKE A FANCY FUNERAL? ");
    fgets(response, sizeof(response), stdin);

    printf("WOULD YOU LIKE US TO INFORM YOUR NEXT OF KIN? ");
    fgets(response, sizeof(response), stdin);
    response[strcspn(response, "\n")] = 0;

    for (int i = 0; response[i]; i++) {
        response[i] = toupper(response[i]);
    }

    if (strncmp(response, "YES", 3) == 0) {
        printf("THAT WILL BE $%d FOR THE TELEGRAPH CHARGE.\n", S4 * 50);
    } else {
        printf("BUT YOUR AUNT SADIE IN ST. LOUIS IS REALLY WORRIED ABOUT YOU\n");
    }

    printf("WE THANK YOU FOR THIS INFORMATION AND WE ARE SORRY YOU\n");
    printf("DIDN'T MAKE IT TO THE GREAT TERRITORY OF OREGON\n");
    printf("BETTER LUCK NEXT TIME\n");
    printf("                  SINCERELY\n");
    printf("        THE OREGON CITY CHAMBER OF COMMERCE\n");

    exit(0);
}

void final_turn() {
    float F9 = (2040.0 - M2) / (M - M2);
    F += (1.0 - F9) * (8 + 5 * E);

    printf("YOU FINALLY ARRIVED AT OREGON CITY\n");
    printf("AFTER 2040 LONG MILES---HOORAY!!!!!\n");
    printf("A REAL PIONEER!\n");

    int days_in_final_turn = (int)(F9 * 14);
    D3 = (D3 - 1) * 14 + days_in_final_turn + 1;

    const char* weekdays[] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"};
    int day_of_week = (D3 + 1 - 1) % 7;
    printf("%s ", weekdays[day_of_week]);

    if (D3 <= 124) {
        printf("JULY %d 1847\n", D3 - 93);
    } else if (D3 <= 155) {
        printf("AUGUST %d 1847\n", D3 - 124);
    } else if (D3 <= 185) {
        printf("SEPTEMBER %d 1847\n", D3 - 155);
    } else if (D3 <= 216) {
        printf("OCTOBER %d 1847\n", D3 - 185);
    } else if (D3 <= 246) {
        printf("NOVEMBER %d 1847\n", D3 - 216);
    } else {
        printf("DECEMBER %d 1847\n", D3 - 246);
    }

    printf("\n");
    print_supplies();

    printf("                  PRESIDENT JAMES K. POLK SENDS YOU HIS\n");
    printf("                     HEARTIEST CONGRATULATIONS\n");
    printf("                     AND WISHES YOU A PROSPEROUS LIFE AHEAD\n");
    printf("                           AT YOUR NEW HOME\n");
}

void print_supplies() {
    printf("FOOD\t\tBULLETS\t\tCLOTHING\tMISC. SUPP.\tCASH\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
           (F > 0) ? F : 0,
           (B > 0) ? B : 0,
           (C > 0) ? C : 0,
           (M1 > 0) ? M1 : 0,
           (T > 0) ? T : 0);
}

int get_input_with_validation(const char* prompt, int min, int max) {
    int value;
    char buffer[100];
    int valid_input;

    do {
        if (strlen(prompt) > 0) {
            printf("%s", prompt);
        }
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            valid_input = 0;
        } else {
            value = atoi(buffer);
            valid_input = (value >= min && value <= max);
        }
    } while (!valid_input);

    return value;
}

float get_float_input(const char* prompt) {
    float value;
    char buffer[100];

    if (strlen(prompt) > 0) {
        printf("%s", prompt);
    }
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    value = atof(buffer);

    return value;
}

float random_float() {
    return (float)rand() / RAND_MAX;
}

int random_int(int max) {
    if (max <= 0) return 0;
    return rand() % max;
}
