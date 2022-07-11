#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

void game() {
    while (1) {
        FILE * fptr;
        char config_path[100] = {0};
        strncat(config_path, getenv("HOME"), 99);
        strncat(config_path, "/.config/idle.txt", 100 - strlen(config_path) - 1);

        fptr = fopen(config_path, "r");

        if (fptr == NULL) {
            printf(COLOR_RED "Error: Can't open config file\n" COLOR_RESET);
            exit(1);
        }
        
        char first_line[500];
        fscanf(fptr, "%s", first_line);
        fclose(fptr);
        
        char *points;
        char *pps;
        char *split = ",";

        points = strtok(first_line, split);
        pps = strtok(NULL, split);
        
        int points_int;
        points_int = atoi(points);
        points_int += atoi(pps);

        char points_char[100];
        sprintf(points_char, "%d", points_int);

        fptr = fopen(config_path, "w");

        if (fptr == NULL) {
            printf(COLOR_RED "Error: Can't open config file\n" COLOR_RESET);
            exit(1);
        }

        fprintf(fptr, "%s,%s", points_char, pps);
        fclose(fptr);

        printf("\e[1;1H\e[2J"); // Clears the terminal
        printf("Points: %s\n", points);
        printf("Points per second: %s\n", pps);
        printf("\n");
        printf("[ Press Control + C to exit ]\n"); // Todo: Nicer way to exit
        printf("\n");
        printf("{ This screen updates every second }\n");
        printf("{ Made by BrandonDoesDev }\n");

        sleep(1);
    }
}

void shop() {
    while(1) {
        printf("\e[1;1H\e[2J"); // Clears the terminal
        printf("Welcome to the shop!\n");
        printf("--------------------\n");
        printf("1) Idle Booster - (+5 points per second) - 500 points\n");
        printf("2) Idle Worker - (+20 points per second) - 2.5k points\n");
        printf("3) Idle Farm - (+75 points per second) - 10k points\n");
        printf("4) Idle Lab - (+250 points per second) - 75k points\n");
        printf("5) Idle Factory - (+500 points per second) - 500k points\n");
        printf("6) Idle Empire - (+1000 points per second) - 1.25M points\n");
        printf("7) Idle Portal - (+5000 points per second) - 5M points\n");
        printf("\n");
        printf("[ Press Control + C to exit ]\n");

        int costs[7] = { 500, 2500, 10000, 75000, 500000, 1250000, 5000000 };
        int ppss[7] = { 5, 20, 75, 250, 500, 1000, 5000 };
      
        int choice;
        scanf("%d", &choice);
        printf("\e[1;1H\e[2J"); // Clears the terminal
      
        int cost = costs[choice - 1];
        int pps_to_add = ppss[choice - 1];

        FILE * fptr;
        char config_path[100] = {0};
        strncat(config_path, getenv("HOME"), 99);
        strncat(config_path, "/.config/idle.txt", 100 - strlen(config_path) - 1);
        fptr = fopen(config_path, "r");

        char first_line[500];
        fscanf(fptr, "%s", first_line);
        fclose(fptr);
        
        char *points;
        char *pps;
        char *split = ",";

        points = strtok(first_line, split);
        pps = strtok(NULL, split);
        
        int points_int;
        points_int = atoi(points);

        if (points_int <= cost) {
            printf(COLOR_RED "You don't have enough points to buy that!\n" COLOR_RESET);
            exit(0);
        }

        points_int -= cost;

        char points_char[100];
        sprintf(points_char, "%d", points_int);

        int pps_int;
        pps_int = atoi(pps);
        pps_int += pps_to_add;

        char pps_char[100];
        sprintf(pps_char, "%d", pps_int);

        fptr = fopen(config_path, "w");

        if (fptr == NULL) {
            printf(COLOR_RED "Error: Can't open config file\n" COLOR_RESET);
            exit(1);
        }

        fprintf(fptr, "%s,%s", points_char, pps_char);
        fclose(fptr);
    }
}

void help() {
    printf("----------------------\n");
    printf("-------- Idle --------\n");
    printf("----------------------\n");

    printf("\n");

    printf("Idle is pretty self-explanatory.\n");
    printf("You have to idle to gain points, and you can buy upgrades to help you out.\n");
    printf("Just make sure to configure your game before playing!\n");

    printf("\n");

    printf(COLOR_CYAN "Developer: BrandonDoesDev\n" COLOR_RESET);

}

void config() {
    printf("Hey there! Before you get started, you need to configure your game's save file.\n");
    printf("Thankfully, Idle handles that all for you - just confirm you haven't done this before and you'll be on your way!\n");
    printf("(If you HAVE already configured your game, doing this will wipe your progress.)\n");
    printf("Do you want to continue? (y/n)\n");

      while((getchar()) != '\n');

    char choice;
    scanf("%c", &choice);

    if (choice == 'y') {
      char data[] = "0,1"; 
          FILE * fptr;

          char config_path[100] = {0};
          strncat(config_path, getenv("HOME"), 99);
          strncat(config_path, "/.config/idle.txt", 100 - strlen(config_path) - 1);

          fptr = fopen(config_path, "w");

          if (fptr == NULL) {
              printf(COLOR_RED "Error: Can't open config file\n" COLOR_RESET);
              exit(1);
          }

          fputs(data, fptr);
          fclose(fptr);
          printf("Idle has been configured.\n");
    } else {
      printf("You chose to quit configuration. See you next time!\n");
    }
}

int main () {
    printf(COLOR_CYAN "Welcome to Idle!\n" COLOR_RESET);

    printf("\nWhat do you want to do?\n");
    printf("> 1 - Play\n");
    printf("> 2 - Shop\n");
    printf("> 3 - Help\n");
    printf("> 4 - Configure\n");
    printf("> 5 - Quit\n");

    int choice;
    scanf("%d", &choice);
    printf("\e[1;1H\e[2J"); // Clears the terminal

    switch (choice) {
        case 1:
            game();
            break;

        case 2:
            shop();
            break;

        case 3:
            help();
            break;

        case 4:
            config();
            break;

        case 5:
            exit(0);
            break;

        default:
            printf(COLOR_RED "Please enter a valid option!\n" COLOR_RESET);
            break;
    }

    return 0;
}
