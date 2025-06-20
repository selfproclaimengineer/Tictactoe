#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PLAYER 'X'
#define BOT 'O'
#define PLAYER1 'A'
#define PLAYER2 'B'

// Deklarasi fungsi
void showTutorial();
void initBoard(char board[3][3]);
void printBoard(char board[3][3]);
int isWinner(char board[3][3], char symbol);
int isDraw(char board[3][3]);
void playerMove(char board[3][3]);
void easyBotMove(char board[3][3]);
void mediumBotMove(char board[3][3]);
void hardBotMove(char board[3][3]);
int isValidMove(char board[3][3], int row, int col);
void playerMovePvP(char board[3][3], char symbol);

int main() {
    while (1){
        char board[3][3];
        int difficulty;

        srand(time(NULL)); // Seed untuk random

        printf("Tic Tac Toe - Melawan Bot Atau Pemain\n");
        printf("Pilih Mode Permainan:\n");
        printf("1. Easy (Bot)\n2. Medium (Bot)\n3. Hard (Bot)\n4. Tutorial\n5. Player Vs Player\n6. E untuk keluar\n");
        printf("Masukkan pilihanmu (1-5): ");
        scanf("%d", &difficulty);
        while (getchar() != '\n' && getchar() != EOF);
        system("clear"); // Bersihkan layar (Linux/Mac) atau gunakan "cls" untuk Windows
        if (difficulty < 1 || difficulty > 5) {
            printf("Pilihan tidak valid. Silakan pilih 1-5.\n");
            return 1; // Keluar dari program jika pilihan tidak valid
        }

        if (difficulty == 4) {
            showTutorial();
            printf("Tekan Enter untuk kembali ke menu...");
            while (getchar() != '\n'); // Bersihkan buffer
            getchar();
            system("clear");
            continue; // Kembali ke menu utama
        }
        if (difficulty == 5) {// mode pvp
		    initBoard(board);
		    int i = 0;
		    while (1) {
		        printBoard(board);
		        char currentPlayer = (i % 2 == 0) ? PLAYER1 : PLAYER2;
		        printf("Giliran Pemain %c\n", currentPlayer);
		        playerMovePvP(board, currentPlayer);
		
		        if (isWinner(board, currentPlayer)) {
		            printBoard(board);
		            printf("Pemain %c menang!\n", currentPlayer);
		            break;
		        }
		        if (isDraw(board)) {
		            printBoard(board);
		            printf("Seri!\n");
		            break;
		        }
		        i++;
		    }
		    printf("Tekan Enter untuk kembali ke menu...");
		    while (getchar() != '\n'); // Bersihkan buffer
		    getchar();
		    system("clear");
		    continue;
		}

        initBoard(board);

        while (1) {
            printBoard(board);
            playerMove(board);
            if (isWinner(board, PLAYER)) {
                printBoard(board);
                printf("Kamu menang!\n");
                break;
            }
            if (isDraw(board)) {
                printBoard(board);
                printf("Seri!\n");
                break;
            }

            // BOT MOVE
            if (difficulty == 1)
                easyBotMove(board);
            else if (difficulty == 2)
                mediumBotMove(board);
            else if (difficulty == 3)
                hardBotMove(board);
            else if (difficulty == 4) {
                showTutorial();
                continue; // Kembali ke awal loop
            } else {
                printf("Pilihan tidak valid. Silakan pilih 1-3.\n");
                continue; // Kembali ke awal loop

            }

            if (isWinner(board, BOT)) {
                printBoard(board);
                printf("Bot menang!\n");
                break;
            }
            if (isDraw(board)) {
                printBoard(board);
                printf("Seri!\n");
                break;
            }
        }
        printf("Tekan Enter untuk kembali ke menu...");
        while (getchar() != '\n'); // Bersihkan buffer
        getchar();
        system("clear");
    }
    return 0;
}

void showTutorial() {
    printf("=====================================\n");
    printf("      TUTORIAL: TIC TAC TOE vs BOT\n");
    printf("=====================================\n");
    printf("Tujuan:\n");
    printf("  Susun 3 simbol X (kamu) secara horizontal, vertikal, atau diagonal.\n\n");

    printf("Cara Bermain:\n");
    printf("  - Kamu bermain sebagai X.\n");
    printf("  - Bot bermain sebagai O.\n");
    printf("  - Kamu selalu jalan duluan.\n");
    printf("  - Input posisi dengan format: baris kolom (angka 0-2)\n");
    printf("    Contoh: Masukkan baris dan kolom: 1 2\n\n");

    printf("Mode Bot:\n");
    printf("  1. Easy   - Langkah acak\n");
    printf("  2. Medium - Bisa menang/blok\n");
    printf("  3. Hard   - Tidak bisa dikalahkan\n\n");

    printf("Peta Papan:\n");
    printf("     0   1   2\n");
    printf("   -------------\n");
    printf(" 0 |   |   |   |\n");
    printf("   -------------\n");
    printf(" 1 |   |   |   |\n");
    printf("   -------------\n");
    printf(" 2 |   |   |   |\n");
    printf("   -------------\n\n");

    printf("Tekan E untuk keluar kapanpun\n\n");
    printf("Tips:\n");
    printf("  Ambil tengah lebih dulu. Jangan biarkan bot punya 2 peluang menang!\n");
    printf("  Tapi kalau main lawan Hard Bot, ya� good luck ??\n\n");
}

void initBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

int isValidMove(char board[3][3], int row, int col) {
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
}


void playerMove(char board[3][3]) {
    char input[10];
    int row, col;
    while (1) {
        printf("Giliran kamu (format: baris kolom, 0-2, atau E untuk keluar): ");
        if (!fgets(input, sizeof(input), stdin)) continue;
        system("clear");
        if (input[0] == 'E' || input[0] == 'e') {
            printf("Keluar dari permainan. Sampai jumpa!\n");
            exit(0);
        }
        if (sscanf(input, "%d %d", &row, &col) == 2) {
            if (row < 0 || row > 2 || col < 0 || col > 2) {
                printf("Input tidak valid! Masukkan angka antara 0-2.\n");
                continue;
            }
            if (!isValidMove(board, row, col)) {
                printf("Posisi sudah terisi! Coba lagi.\n");
                continue;
            }
            board[row][col] = PLAYER;
            break;
        } else {
            printf("Input tidak valid! Masukkan dua angka atau E untuk keluar.\n");
        }
    }
}


int isWinner(char board[3][3], char symbol) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return 1;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return 1;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return 1;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return 1;
    return 0;
}

int isDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void easyBotMove(char board[3][3]) {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (!isValidMove(board, row, col));
    printf("Bot (Easy) memilih: %d %d\n", row, col);
    board[row][col] = BOT;
}

// Mencoba menang atau blok, tergantung simbol ('O' untuk menang, 'X' untuk blok)
int tryWinOrBlock(char board[3][3], char symbol) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = symbol;
                if (isWinner(board, symbol)) {
                    if (symbol == BOT)
                        printf("Bot (Medium) memilih: %d %d\n", i, j);
                    board[i][j] = BOT; // Pasang langkah
                    return 1; // Langkah ditemukan
                }
                board[i][j] = ' '; // Undo langkah
            }
        }
    }
    return 0;
}

void mediumBotMove(char board[3][3]) {
    // 1. Coba menang
    if (tryWinOrBlock(board, BOT)) return;

    // 2. Coba blok pemain
    if (tryWinOrBlock(board, PLAYER)) return;

    // 3. Kalau tidak bisa, random
    easyBotMove(board);
}

int minimax(char board[3][3], int depth, int isMaximizing) {
    if (isWinner(board, BOT)) return 1;
    if (isWinner(board, PLAYER)) return -1;
    if (isDraw(board)) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = BOT;
                    int score = minimax(board, depth + 1, 0);
                    board[i][j] = ' ';
                    if (score > bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    int score = minimax(board, depth + 1, 1);
                    board[i][j] = ' ';
                    if (score < bestScore) bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

void hardBotMove(char board[3][3]) {
    int bestScore = -1000;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = BOT;
                int score = minimax(board, 0, 0);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    printf("Bot (Hard) memilih: %d %d\n", moveRow, moveCol);
    board[moveRow][moveCol] = BOT;
}

void playerMovePvP(char board[3][3], char symbol) {
    char input[10];
    int row, col;
    while (1) {
        printf("Masukkan baris dan kolom (0-2), atau E untuk keluar: ");
        if (!fgets(input, sizeof(input), stdin)) continue;
        system("clear");
        if (input[0] == 'E' || input[0] == 'e') {
            printf("Keluar dari permainan. Sampai jumpa!\n");
            exit(0);
        }
        if (sscanf(input, "%d %d", &row, &col) == 2) {
            if (row < 0 || row > 2 || col < 0 || col > 2) {
                printf("Input tidak valid! Masukkan angka antara 0-2.\n");
                continue;
            }
            if (!isValidMove(board, row, col)) {
                printf("Posisi sudah terisi! Coba lagi.\n");
                continue;
            }
            board[row][col] = symbol;
            break;
        } else {
            printf("Input tidak valid! Masukkan dua angka atau E untuk keluar.\n");
        }
    }
}
