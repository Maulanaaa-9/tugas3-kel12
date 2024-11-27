#include <ncurses/curses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

void print_menu(WINDOW *menu_win, int pilihanTerpilih, const char *opsi[], int jumlahopsi);
void registration(), login(), list_akun();

int main() {
    initscr();
    clear();
    noecho();
    cbreak();
// --------------------------------------------------------------------
    	int row, col;
getmaxyx(stdscr, row, col);
		int loading_y = row / 2 - 1;
		int loading_x = col / 2 - 20;
		int lebar_loading = 40;
		int tinggi_loading = 5;


	WINDOW *loading_win = newwin(tinggi_loading, lebar_loading, loading_y - 2, loading_x);
		box(loading_win, 0, 0);
	wrefresh(loading_win);

for (int progress = 0; progress <= 100; progress += 7) {
    box(loading_win, 0, 0);
    		mvwprintw(loading_win, 1, (lebar_loading - 10) / 2, "Loading");
    for (int titik = 0; titik < 4; titik++) {
        	mvwprintw(loading_win, 1, (lebar_loading - 10) / 2 + 7, "   ");
        	wmove(loading_win, 1, (lebar_loading - 10) / 2 + 7);
        for (int i = 0; i < titik; i++) {
            wprintw(loading_win, ".");
        }
        wrefresh(loading_win);
        usleep(100000); 
    }
    mvwprintw(loading_win, 2, (lebar_loading - 20) / 2, "Progress: %3d%%", progress);
    wrefresh(loading_win);
}
refresh();
usleep(500000);
delwin(loading_win);
clear();

//--------------------------------------------------------------------------------------
    int menu_y = row / 2 - 5; 
    int menu_x = col / 2 - 15; 
    int lebar = 30, tinggi = 12;

    WINDOW *menu_win = newwin(tinggi, lebar, menu_y, menu_x);
    	keypad(menu_win, TRUE);

    const char *opsi[] = {
        "NEW GAME",
        "CONTINUE",
        "LEADERBOARD",
        "EXIT"
    };
    
    int jumlahopsi = sizeof(opsi) / sizeof(char *);
    int pilihanTerpilih = 0;
    int pilihan = -1;
		
	while (1) {
        	print_menu(menu_win, pilihanTerpilih, opsi, jumlahopsi);
				int tombol = wgetch(menu_win);
		switch (tombol) {
    case KEY_UP:
                pilihanTerpilih = (pilihanTerpilih == 0) ? jumlahopsi - 1 : pilihanTerpilih - 1;
            break;
	case KEY_DOWN:
                pilihanTerpilih = (pilihanTerpilih == jumlahopsi - 1) ? 0 : pilihanTerpilih + 1;
            break;
	case 10:
                pilihan = pilihanTerpilih;
            break;
        }

        if (pilihan == 0) {
            endwin();
            	registration();
            	initscr();
            clear(); 
        } else if (pilihan == 1) {
            endwin();
            	login();
            	initscr();
            clear(); 
        } else if (pilihan == 2) {
            endwin();
            	list_akun();
            	initscr();
            clear();
        } else if (pilihan == 3) {
            break;
        }

        pilihan = -1;
    }

    endwin();
    return 0;
}
