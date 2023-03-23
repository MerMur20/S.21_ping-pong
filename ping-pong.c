// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>
int put_in_map();
void print_frame();
int move_racket1(int racket1_y, char mv_opt);
int move_racked2(int racket2_y, char mv_opt);

int main() {
    int racket1_y = 12;
    int racket2_y = 12;

    int ballx = 40;
    int bally = 12;
    int ball_direction = 0;

    int scoreL = 0;
    int scoreR = 0;

    int game_over = 0;

    print_frame(racket1_y, racket2_y, ballx, bally, scoreL, scoreR);
    while (game_over == 0) {
        char input_key = getchar();
        if (input_key == '\n') {
            print_frame(racket1_y, racket2_y, ballx, bally, scoreL, scoreR);
            continue;
        }
        if (input_key == 'q' || scoreL == 21 || scoreR == 21) {
            game_over = 1;

        } else if (input_key == ' ' || input_key == 'k' || input_key == 'z' || input_key == 'a' ||
                   input_key == 'm') {
            racket1_y = move_racket1(racket1_y, input_key);
            racket2_y = move_racked2(racket2_y, input_key);
            if (ballx >= 78) {
                racket1_y = 13;
                racket2_y = 13;
                ballx = 40;
                bally = 12;
                if (scoreR % 2) {
                    ball_direction = 0;
                } else {
                    ball_direction = 3;
                }
                scoreR++;
                //отражение от первой рамки
            } else if (bally >= racket1_y - 1 && bally <= racket1_y + 3 && ballx == 4) {
                if (ball_direction == 3 && bally == racket1_y + 3) {
                } else if (ball_direction == 3 && bally == racket1_y - 1) {
                    ball_direction = 0;
                } else if (ball_direction == 2 && bally == racket1_y - 1) {
                } else if (ball_direction == 2 && bally == racket1_y + 3) {
                    ball_direction = 1;
                } else if (ball_direction == 2) {
                    ball_direction = 1;
                } else {
                    ball_direction = 0;
                }
                // отражение от второй рамки
            } else if (bally >= racket2_y - 1 && bally <= racket2_y + 3 && ballx == 77) {
                if (ball_direction == 0 && bally == racket2_y - 1) {
                    ball_direction = 3;
                } else if (ball_direction == 0 && bally == racket2_y + 3) {
                } else if (ball_direction == 1 && bally == racket2_y + 1) {
                    ball_direction = 1;
                } else if (ball_direction == 1 && bally == racket2_y - 1) {
                } else if (ball_direction == 0) {
                    ball_direction = 3;
                } else {
                    ball_direction = 2;
                }

            } else if (ballx <= 2) {
                racket1_y = 13;
                racket2_y = 13;
                ballx = 40;
                bally = 12;
                if (scoreL % 2) {
                    ball_direction = 1;
                } else {
                    ball_direction = 2;
                }
                scoreL++;
            }
            if (bally <= 1) {
                if (ball_direction == 1) {
                    ball_direction = 0;
                } else {
                    ball_direction = 3;
                }
            } else if (bally >= 25) {
                if (ball_direction == 0) {
                    ball_direction = 1;
                } else {
                    ball_direction = 2;
                }
            }

            if (ball_direction == 0) {
                ballx = put_in_map(ballx + 1, 1, 80);
                bally = put_in_map(bally + 1, 1, 25);
            } else if (ball_direction == 1) {
                ballx = put_in_map(ballx + 1, 1, 80);
                bally = put_in_map(bally - 1, 1, 25);
            } else if (ball_direction == 2) {
                ballx = put_in_map(ballx - 1, 1, 80);
                bally = put_in_map(bally - 1, 1, 25);
            } else if (ball_direction == 3) {
                ballx = put_in_map(ballx - 1, 1, 80);
                bally = put_in_map(bally + 1, 1, 25);
            }
            print_frame(racket1_y, racket2_y, ballx, bally, scoreL, scoreR);

        } else {
            printf("\033[0d\033[2J");
            print_frame(racket1_y, racket2_y, ballx, bally, scoreL, scoreR);
            continue;
        }
    }

    return 0;
}
int put_in_map(int x, int from, int to) {
    if (x <= from) {
        x = from;
    } else if (x >= to) {
        x = to;
    }

    return x;
}

void print_frame(int racket1_y, int racket2_y, int ballx, int bally, int scoreL, int scoreR) {
    int height = 26;
    int width = 81;
    printf("\033[0d\033[2J");
    printf("Score: %d | %d\n", scoreL, scoreR);
    for (int y = 0; y <= height; y++) {     //поля вертикальные
        for (int x = 0; x <= width; x++) {  //поля горизонтальные
            if (y == 0 || y == 26) {
                printf("*");
                continue;
            } else if (x == 0 || x == 81) {
                printf("*");
                continue;
            } else if (x == ballx && y == bally) {
                printf("©");  //печать шарика
                continue;
            } else if (x == 40) {
                printf("|");  //печать центрального поля
                continue;
            } else if (x == 3 && (y == racket1_y || y == (racket1_y + 1) || (y == (racket1_y + 2)))) {
                printf("#");
                continue;
            } else if (x == 78 && (y == racket2_y || y == (racket2_y + 1) || (y == (racket2_y + 2)))) {
                printf("#");
                continue;
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    if (scoreL == 21) {
        printf("Congratulations, Player 1 won!");
    }
    if (scoreR == 21) {
        printf("Congratulations, Player 2 won!");
    }
}

int move_racket1(int racket1_y, char mv_opt) {
    if (mv_opt == 'a' || mv_opt == 'z') {
        if (mv_opt == 'a') {
            racket1_y = racket1_y - 1;
        }
        if (mv_opt == 'z') {
            racket1_y = racket1_y + 1;
        }

        racket1_y = put_in_map(racket1_y, 1, 23);
    }

    return racket1_y;
}

int move_racked2(int racket2_y, char mv_opt) {
    if (mv_opt == 'k' || mv_opt == 'm') {
        if (mv_opt == 'k') {
            racket2_y = racket2_y - 1;
        }
        if (mv_opt == 'm') {
            racket2_y = racket2_y + 1;
        }
        racket2_y = put_in_map(racket2_y, 1, 23);
    }

    return racket2_y;
}

