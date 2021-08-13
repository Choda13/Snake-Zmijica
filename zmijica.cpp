#define _WIN32_WINNT 0x0500
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <io.h>
#include <thread>
#include <mutex>
#include <ctype.h>
#include <vector>
#include <limits>
#include <time.h>
#pragma warning(disable:4996)
#pragma comment(lib, "winmm.lib")

#define BUTTON1_START_Y 65
#define BUTTON2_START_Y 85
#define BUTTON3_START_Y 105
#define BUTTON4_START_Y 86
#define BUTTON5_START_Y 106
#define BUTTON6_START_Y 30
#define BUTTON7_START_Y 50

#define AUDIO_DIR "Audio\\"
#define UI_DIR "UI\\"
#define ANIM_DIR "Animations\\"

#define BUTTON1 UI_DIR "playDugme.txt"
#define BUTTON2 UI_DIR "pickLevel.txt"
#define BUTTON3 UI_DIR "exit.txt"
#define BUTTON4 UI_DIR "textColor.txt"
#define BUTTON5 UI_DIR "settings2.txt"
#define BUTTON6 UI_DIR "mode1.txt"
#define BUTTON7 UI_DIR "mode2.txt"
#define BUTTON8 UI_DIR "settings.txt"
#define MAPAS UI_DIR "mapa.txt"

#define CLICK AUDIO_DIR "click.wav"
#define CONFIRM AUDIO_DIR "confirm.wav"
#define MUSIC AUDIO_DIR "idezmija.wav"
#define TURBO_MUSIC AUDIO_DIR "tokio.wav"
#define GAME_OVER_MUSIC AUDIO_DIR "astronomia.wav"
#define PROJECTOR_MUSIC AUDIO_DIR "projector.wav"

#define COUNTDOWN_ANIM ANIM_DIR "CountdownAnim\\frame"
#define DEAD_ANIM ANIM_DIR "DEAD\\frame"
#define SNAKE_GIF ANIM_DIR "Snake\\frame"

#define VEL 0.85
#define SAT 0.85


#define BLOK_TELO_LEVO 200
#define BLOK_TELO_DESNO 201
#define BLOK_TELO_GORE 202
#define BLOK_TELO_DOLE 203
#define BLOK_TELO_KRIVINA_GORE_LEVO 204
#define BLOK_TELO_KRIVINA_GORE_DESNO 205
#define BLOK_TELO_KRIVINA_DOLE_LEVO 206
#define BLOK_TELO_KRIVINA_DOLE_DESNO 207
#define BLOK_TELO_PROGUTAO_LEVO 208
#define BLOK_TELO_PROGUTAO_DESNO 209
#define BLOK_TELO_PROGUTAO_GORE 210
#define BLOK_TELO_PROGUTAO_DOLE 211

#define BLOK_GLAVA_LEVO 212
#define BLOK_GLAVA_DESNO 213
#define BLOK_GLAVA_GORE 214
#define BLOK_GLAVA_DOLE 215
#define BLOK_GLAVA_GORE_GUTA 216
#define BLOK_GLAVA_DOLE_GUTA 217
#define BLOK_GLAVA_LEVO_GUTA 218
#define BLOK_GLAVA_DESNO_GUTA 219

#define BLOK_REP_LEVO 220
#define BLOK_REP_DESNO 221
#define BLOK_REP_GORE 222
#define BLOK_REP_DOLE 223

#define BLOK_HRANA 224

#define SMER_LEVO 225
#define SMER_DESNO 226
#define SMER_GORE 227
#define SMER_DOLE 228

#define BORDER_THICKNES_Y 3
#define BORDER_THICKNES_X 5

#define BEGIN_SIZE 5
#define MAX_SIZE 100

#define HUDS UI_DIR "hudSurvival.txt"

#define DELAY 50 //gif delay in ms

#define DEFAULT_SPEED 150
#define ULTRA_MOD 10
using namespace std;

struct BLOK_ZMIJE
{
	COORD position;
	int oblik;
};

void changeConsole2(SHORT width, SHORT height, int font, int fontx);
void gotoxy(int x, int y);
void changeFgBg(int fg, int bg);
void gif(int x, int y);
void changeConsole(SHORT width, SHORT height, int font);
void SakriKursor();
void odrediDugme(char buffer[], int dugme);
void settings();
void ispisiOpet(void (*fun)());
void meni();
void playPickMode();
void startGameModeS();
void startGameModeC();
void sarenilo();
void update();

/****************************
-----------CIFRE-------------
*****************************/
void exitAnim();
void brJedan(int x, int y1);
void brDva(int x, int y1);
void brTri(int x, int y1);
void brCet(int x, int y1);
void brPet(int x, int y1);
void brSest(int x, int y1);
void brSedam(int x, int y1);
void brOsam(int x, int y1);
void brDevet(int x, int y1);
void brNula(int x, int y1);
void ispisBroj(int x, int y, int broj);
/****************************
*****************************/

/****************************
---------PROJECTOR-----------
*****************************/
void startAnim();
void ispisiMapu(int width, int height);
void promeniCord(BLOK_ZMIJE* blok);
int isteCoord(BLOK_ZMIJE* zmija, COORD korde, int n, int snakeORnot);
void blinkAnim(BLOK_ZMIJE* zmija, int snakeSize);
void GameOver();
/****************************
*****************************/

/*******************************
---------IZGLED-ZMIJE-----------
********************************/
void teloLevo(int x, int y);
void teloDesno(int x, int y);
void teloGore(int x, int y);
void teloDole(int x, int y);
void krivinaGoreLevo(int x, int y);
void krivinaGoreDesno(int x, int y);
void krivinaDoleLevo(int x, int y);
void krivinaDoleDesno(int x, int y);
void teloProgutaoLevo(int x, int y);
void teloProgutaoDesno(int x, int y);
void teloProgutaoGore(int x, int y);
void teloProgutaoDole(int x, int y);
void glavaLevo(int x, int y);
void glavaDesno(int x, int y);
void glavaGore(int x, int y);
void glavaDole(int x, int y);
void glavaLevoGuta(int x, int y);
void glavaDesnoGuta(int x, int y);
void glavaGoreGuta(int x, int y);
void glavaDoleGuta(int x, int y);
void repLevo(int x, int y);
void repDesno(int x, int y);
void repGore(int x, int y);
void repDole(int x, int y);
void hrana(int x, int y);
void obrisiPolje(int x, int y);
void siftujPoziciju(BLOK_ZMIJE *niz, int n);
/****************************
*****************************/

void zid(int x, int y);

void mapa1();
void mapa2();

wchar_t* ucitajFajl(const char imeFajla[]);
int izbor(char c);

mutex mtx;
BOOL gifRadi = false;
BOOL sareniloSareni = false;

int fgc=4; //default boja teksta
int bgc=0;//default pozadina
int width=310;
int height=600;
int font = 4;
int selfg = 14;//Boja teksta za neko dugme koje je izabrano // trenutno je ista kao boja gifa tj menja se
int gifFg = 14;
int speedZmije = DEFAULT_SPEED;


int mapWidth = 300;
int mapHeight = 100;

int marginaDesno = mapWidth - BORDER_THICKNES_X - 3;
int marginaLevo = BORDER_THICKNES_X + 3;
int marginaGore = BORDER_THICKNES_Y + 3;
int marginaDole = mapHeight - BORDER_THICKNES_Y - 3;

COORD LevelPozicija;	//pozicija broja
COORD SpeedPozicija;	//pozicija broja
COORD ScorePozicija;	//pozicija broja
COORD prepreke[200];
int brPepreka;

BLOK_ZMIJE zmija[100];
BLOK_ZMIJE hranaBlok;		//mozda je najbolje promeniti ime strukture BLOK_ZMIJE u blok ili piksel ili tako nesto

int snakeSize = BEGIN_SIZE;

CONSOLE_SCREEN_BUFFER_INFOEX info;

void ispisiBlok(BLOK_ZMIJE blok);

int main()
{
	info.cbSize = sizeof(info);
	srand((unsigned int)time(0));
	meni();
    return 0;

}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/**************************
----Menja-boju-ispisa-duh--
**************************/
void changeFgBg(int fg, int bg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (fg + (bg * 16)));
}

void sarenilo()
{
	int r = 216, g = 33, b = 33;
	int hue = 0;
	//thread th(update);
	//th.detach();
	while(sareniloSareni)
	for (hue = 0; hue <= 360; hue++)
	{
		if (!sareniloSareni)
			return;
		if (hue >= 0 && hue <= 60)
			g += 3;
		if (hue > 60 && hue <= 120)
			r -= 3;
		if (hue > 120 && hue <= 180)
			b += 3;
		if (hue > 180 && hue <= 240)
			g -= 3;
		if (hue > 240 && hue <= 300)
			r += 3;
		if (hue > 300 && hue < 360)
			b -= 3;
		info.ColorTable[14] = RGB(r, g, b);

		mtx.lock();
		SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		changeFgBg(selfg, bgc);
		gotoxy(width, height);
		/*_setmode(_fileno(stdout), _O_TEXT);
		printf("");*/
		mtx.unlock();

		Sleep(1);
		if (hue == 359)
			hue = 0;
	}
}

/**************************
----GIF-STA-DA-SE-KAZE-----
**************************/
void gif(int x, int y)
{
	char frame[100] = SNAKE_GIF;
	char frameNum[3];
	wchar_t* niz;

	if (sareniloSareni == false)
	{
		thread th(sarenilo);
		th.detach();
		sareniloSareni = true;
	}

	while (gifRadi)
	{
		for (int i = 0; i < 10; i++)
		{
			SakriKursor();

			itoa(i, frameNum, 10);
			strcat(frame, frameNum);
			strcat(frame, ".txt");

			niz = ucitajFajl(frame);
			if (gifRadi == false)
				break;

			mtx.lock();

			_setmode(_fileno(stdout), _O_TEXT);
			changeFgBg(gifFg, bgc);
			gotoxy(0, 0);
			wprintf(L"%s", niz);

			mtx.unlock();

			free(niz);

			strcpy(frame, SNAKE_GIF);
			Sleep(DELAY);
		}
	}
}

/*****************************************
----MENJA-SE-VELICINA-I-FONT-KONZOLE------
*****************************************/

void changeConsole(SHORT width, SHORT height, int font)
{
	CONSOLE_FONT_INFOEX cfi;
	char komanda[50]="mode";
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = font;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	/*info.cbSize = sizeof(info);
	GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	info.dwSize.X = width;
	info.dwMaximumWindowSize.X = 1920;
	info.dwMaximumWindowSize.Y = 1080;
	info.srWindow.Bottom = height;
	info.cbSize = sizeof(info);
	SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	mtx.unlock();*/

	HWND hwnd = GetConsoleWindow();
	COORD ok;
	ok.X = 1920;
	ok.Y = 1080;
	if (hwnd != NULL) {
		SetWindowPos(hwnd, 0, 10, 0, width, height, SWP_SHOWWINDOW | SWP_NOMOVE); 
		SetConsoleScreenBufferSize (hwnd, ok);
	}


}

/************************************************************
----UCITAVA-SADRZAJ-FAJLA-U-DINM-MEMORIJU-ZA-LEPSI-ISPIS-----
************************************************************/
wchar_t* ucitajFajl(const char imeFajla[])
{
	FILE* f = fopen(imeFajla, "r+,ccs=UTF-8");
	wchar_t* niz;
	size_t ArraySize = 500 * 200;
	niz = (wchar_t*)calloc(ArraySize, sizeof(wchar_t));
	
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	rewind(f);
	if(niz)
		fread(niz, sizeof(wchar_t), ArraySize, f);
	fclose(f);

	return niz;
}

/**************************
----SKLANJA-KURSOR---------
**************************/
void SakriKursor() {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/********************************************
----ODREDJUJE-TRENUTNO-SELEKTOVANO-DUGME-----
********************************************/
void odrediDugme(char buffer[], int dugme)
{
	if (dugme == BUTTON1_START_Y || dugme == 0)
		strcpy(buffer, BUTTON1);
	else if (dugme == BUTTON2_START_Y)
		strcpy(buffer, BUTTON2);
	else if (dugme == BUTTON3_START_Y)
		strcpy(buffer, BUTTON3);
	else if (dugme == BUTTON4_START_Y)
		strcpy(buffer, BUTTON4);
	else if (dugme == BUTTON5_START_Y)
		strcpy(buffer, BUTTON5);
	else if (dugme == BUTTON6_START_Y)
		strcpy(buffer, BUTTON6);
	else
		strcpy(buffer, BUTTON7);
}	

/**************************
------SETTINGS-PANEL-------
**************************/
void settings()
{
	wchar_t* niz;
	char c;
	niz = ucitajFajl(BUTTON8);
	changeConsole2(150, 150, font, 0);
	mtx.lock();
	info.srWindow.Bottom = height/font+20;
	mtx.unlock();

	mtx.lock();
	changeFgBg(fgc, bgc);
	for (int i = 0; i < 70; i++)
	{
		_setmode(_fileno(stdout), _O_TEXT);
		gotoxy(0, i + 65);
		printf("%c[2K", 27);
	}
	gotoxy(0, 65);	
	//changeConsole(width + 30, height, font);
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	wprintf(L"%s", niz);
	mtx.unlock();
	free(niz);

	niz = ucitajFajl(BUTTON4);

	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(0, 86);
	wprintf(L"%s", niz);
	free(niz);

	wprintf(L"\n");
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 4; j++)
			wprintf(L" ");
		for (int k = 0; k < 13; k++)
		{
			changeFgBg(k, bgc);
			for (int j = 0; j <= 4; j++)
				wprintf(L"█");
			for (int j = 0; j <= 4; j++)
				wprintf(L" ");
		}
		wprintf(L"\n");
	}
	mtx.unlock();

	niz = ucitajFajl(BUTTON5);

	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(0, 106);
	wprintf(L"%s", niz);
	mtx.unlock();
	free(niz);
	
	mtx.lock();
	gotoxy(0, 116);
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	wprintf(L"\n");
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 4; j++)
			wprintf(L" ");
		for (int k = 0; k < 13; k++)
		{
			changeFgBg(k, bgc);
			for (int j = 0; j <= 4; j++)
				wprintf(L"█");
			for (int j = 0; j <= 4; j++)
				wprintf(L" ");
		}
		wprintf(L"\n");
	}
	mtx.unlock();

	/****************************
	 -----------MENU--------------
	 ****************************/
	char dugme[50];
	int y=0;
	int ispisi = 0;
	void(*fun_ptr)=settings;
	while (1)
	{
		if (kbhit())
		{
			
			c = getch();

			/****************************
			------SELEKCIJA-NA-DOLE------
			****************************/

			if (c == 's' || c == 'S' || c==40)
			{
				if (y)
				{
					odrediDugme(dugme, y);
					niz = ucitajFajl(dugme);

					mtx.lock();
					_setmode(_fileno(stdout), _O_WTEXT);
					changeFgBg(fgc, bgc);
					gotoxy(0, y);
					wprintf(L"%s", niz);
					mtx.unlock();

					free(niz);
				}

				if (!y || y == BUTTON5_START_Y)
					y = BUTTON4_START_Y;
				else
					y = BUTTON5_START_Y;

				odrediDugme(dugme, y);
				niz = ucitajFajl(dugme);

				mtx.lock();
				_setmode(_fileno(stdout), _O_WTEXT);
				changeFgBg(selfg, bgc);
				gotoxy(0, y);
				wprintf(L"%s", niz);
				mtx.unlock();
				free(niz); 
				PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
				PlaySound(TEXT(CLICK), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
				Sleep(40);
			}

			/****************************
			------SELEKCIJA-NA-GORE------
			****************************/

			if (c == 'w' || c == 'W' || c==38)
			{
				if (y)
				{
					odrediDugme(dugme, y);
					niz = ucitajFajl(dugme);

					mtx.lock();
					_setmode(_fileno(stdout), _O_WTEXT);
					changeFgBg(fgc, bgc);
					gotoxy(0, y);
					wprintf(L"%s", niz);
					mtx.unlock();

					free(niz);
				}

				if (!y || y == BUTTON4_START_Y)
					y = BUTTON5_START_Y;
				else
					y = BUTTON4_START_Y;

				odrediDugme(dugme, y);
				niz = ucitajFajl(dugme);

				mtx.lock();
				_setmode(_fileno(stdout), _O_WTEXT);
				changeFgBg(selfg, bgc);
				gotoxy(0, y);
				wprintf(L"%s", niz);
				mtx.unlock();
				free(niz);
				PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
				PlaySound(TEXT(CLICK), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
				Sleep(40);

			}


			/**************************
			----IZBOR-NEKE-OPCIJE------
			**************************/

			if (y == BUTTON4_START_Y && izbor(c) != -1)
			{
				fgc = izbor(c);
				changeFgBg(fgc, bgc);
				ispisi = 1;
				PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
				PlaySound(TEXT(CONFIRM), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
				break;
			}
			if (y == BUTTON5_START_Y && izbor(c) != -1)
			{
				bgc = izbor(c);
				changeFgBg(fgc, bgc);
				fun_ptr = settings;
				ispisi = 1;
				PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
				PlaySound(TEXT(CONFIRM), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
				break;
			}
			if (c == 27)
			{
				ispisi = 2;
				PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
				PlaySound(TEXT(CONFIRM), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
				break;
			}
		}
	}

	/**************************
	---PONOVNI-ISPIS-KONZOLE--
	**************************/
	if (ispisi)
	{
		if (ispisi == 1)
		{
			ispisi = 0;
			ispisiOpet(settings);
		}
		else if (ispisi == 2)
		{
			ispisi = 0;
			ispisiOpet(meni);
		}
	}
}


/**********************************************
----PROVERAVA-DA-LI-ZNAK-IMA-NEKU-FUNKCIJU-----
**********************************************/

int izbor(char c)
{
	int boja=-1;
	if (c >= '0' && c <= '9')
		boja = c - 48;
	else if (c == 'a' || c == 'A')
		boja = 10;
	else if (c == 'b' || c == 'B')
		boja = 11;
	else if (c == 'c' || c == 'C')
		boja = 12;
	else if (c == 'd' || c == 'D')
		boja = 13;

	return boja;
}

/**************************
---PONOVNI-ISPIS-KONZOLE--
**************************/
void ispisiOpet(void (*fun)())
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	system("cls");
	mtx.unlock();
	(fun)();
}

/**************************
-------POCETNI-MENI--------
**************************/
bool FirstTime = true;
void meni()
{
	void SakriKursor();
	changeFgBg(fgc, bgc);
	changeConsole2(130, 170, font, 0);
	if (FirstTime)
	{
		FirstTime = false;
		GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		HWND consoleWindow = GetConsoleWindow();
		SetWindowLongW(consoleWindow, GWL_STYLE, GetWindowLongW(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX & ~WS_VSCROLL);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS);
	}

	wchar_t* niz;
	niz = ucitajFajl(BUTTON1);

	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(0, BUTTON1_START_Y);
	wprintf(L"%s", niz);
	free(niz);
		mtx.unlock();

	niz = ucitajFajl(BUTTON2);

	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(0, BUTTON2_START_Y);
	wprintf(L"%s", niz);
	free(niz);
	mtx.unlock();

	niz = ucitajFajl(BUTTON3);

	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(0, BUTTON3_START_Y);
	wprintf(L"%s", niz);
	free(niz);
	mtx.unlock();
	
	/****************************
	-----------GIF--------------
	****************************/

	if (gifRadi==false)
	{
		gifRadi = true;
		thread th(gif, 0, 0);
		th.detach();
	}

	/****************************
	 -----------MENU--------------
	 ****************************/
	char c;
	char dugme[50];
	int y = 0;
	while (1)
	{
		if (kbhit())
		{
			c = getch();

			/****************************
			------SELEKCIJA-NA-DOLE------
			****************************/

			if (c == 's' || c == 'S' || c==40)
			{
				if (y)
				{
					odrediDugme(dugme, y);
					niz = ucitajFajl(dugme);

					mtx.lock();
					_setmode(_fileno(stdout), _O_WTEXT);
					changeFgBg(fgc, bgc);
					gotoxy(0, y);
					wprintf(L"%s", niz);
					mtx.unlock();

					free(niz);
				}

				if (y == BUTTON3_START_Y || !y)
					y = BUTTON1_START_Y;
				else if (y == BUTTON1_START_Y)
					y = BUTTON2_START_Y;
				else
					y = BUTTON3_START_Y;
				odrediDugme(dugme, y);
				niz = ucitajFajl(dugme);
				
				mtx.lock();
				_setmode(_fileno(stdout), _O_WTEXT);
				changeFgBg(selfg, bgc);
				gotoxy(0, y);
				wprintf(L"%s", niz);
				mtx.unlock();
				PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
				PlaySound(TEXT(CLICK), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
				Sleep(40);
				free(niz);
			}

			/****************************
			------SELEKCIJA-NA-GORE------
			****************************/

			else if (c == 'w' || c == 'W' || c==38)
			{
				if (y)
				{
					odrediDugme(dugme, y);
					niz = ucitajFajl(dugme);

					mtx.lock();
					_setmode(_fileno(stdout), _O_WTEXT);
					changeFgBg(fgc,bgc);
					gotoxy(0, y);
					wprintf(L"%s", niz);
					mtx.unlock();

					free(niz);
				}

				if (y == BUTTON1_START_Y || !y)
					y = BUTTON3_START_Y;
				else if (y == BUTTON3_START_Y)
					y = BUTTON2_START_Y;
				else
					y = BUTTON1_START_Y;

				odrediDugme(dugme, y);
				niz = ucitajFajl(dugme);

				mtx.lock();
				_setmode(_fileno(stdout), _O_WTEXT);
				changeFgBg(selfg, bgc);
				gotoxy(0, y);
				wprintf(L"%s", niz);
				mtx.unlock();
				PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
				PlaySound(TEXT(CLICK), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
				free(niz);
				Sleep(40);
			}

			/****************************
			------ODABIR-POLJA-----------
			****************************/
			if (c == 13)
			{
				odrediDugme(dugme, y);
				if (!strcmp(dugme, BUTTON2))
				{
					PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
					PlaySound(TEXT(CONFIRM), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
					mtx.lock();
					changeFgBg(fgc, bgc);
					system("cls");
					mtx.unlock();
					settings();
				}
				if (!strcmp(dugme, BUTTON3))
				{
					PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
					PlaySound(TEXT(CONFIRM), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
					exitAnim();
					exit(EXIT_SUCCESS);
				}
				if (!strcmp(dugme, BUTTON1))
				{
					PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
					PlaySound(TEXT(CONFIRM), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
					playPickMode();
				}
			}
		}
	}
}

void playPickMode()
{
	wchar_t* niz;
	changeConsole2(150, 100, font, 0);
	gifRadi = false;
	//sareniloSareni = true;
	SakriKursor();

	mtx.lock();
	changeFgBg(fgc, bgc);
	system("cls");
	mtx.unlock();

	niz = ucitajFajl(BUTTON6);
	mtx.lock();
	gotoxy(0, BUTTON6_START_Y);
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	wprintf(L"%s", niz);
	mtx.unlock();
	free(niz);

	niz = ucitajFajl(BUTTON7);
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(0, BUTTON7_START_Y);
	wprintf(L"%s", niz);
	mtx.unlock();
	free(niz);

	/****************************
	 -----------MENU--------------
	 ****************************/
	char c;
	char dugme[50];
	int y = 0;
	int ispisi = 0;
	while (1)
	{
		if (kbhit())
		{
			c = getch();

			/****************************
			------SELEKCIJA-NA-DOLE------
			****************************/

			if (c == 's' || c == 'S' || c == 40)
			{
				if (y)
				{
					odrediDugme(dugme, y);
					niz = ucitajFajl(dugme);
					mtx.lock();
					_setmode(_fileno(stdout), _O_WTEXT);
					gotoxy(0, y);
					changeFgBg(fgc, bgc);
					wprintf(L"%s", niz);
					mtx.unlock();
					free(niz);
				}

				if (y == BUTTON7_START_Y || !y)
					y = BUTTON6_START_Y;
				else
					y = BUTTON7_START_Y;

				odrediDugme(dugme, y);
				niz = ucitajFajl(dugme);

				mtx.lock();
				changeFgBg(selfg, bgc);
				_setmode(_fileno(stdout), _O_WTEXT);
				gotoxy(0, y);
				wprintf(L"%s", niz);
				mtx.unlock();
				free(niz);
				PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
				PlaySound(TEXT(CLICK), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
				Sleep(40);
			}

			/****************************
			------SELEKCIJA-NA-GORE------
			****************************/

			else if (c == 'w' || c == 'W' || c == 38)
			{
				if (y)
				{
					odrediDugme(dugme, y);
					niz = ucitajFajl(dugme);

					mtx.lock();
					_setmode(_fileno(stdout), _O_WTEXT);
					changeFgBg(fgc, bgc);
					gotoxy(0, y);
					wprintf(L"%s", niz);	
					mtx.unlock();

					free(niz);
				}

				if (y == BUTTON6_START_Y || !y)
					y = BUTTON7_START_Y;
				else
					y = BUTTON6_START_Y;

				odrediDugme(dugme, y);
				niz = ucitajFajl(dugme);
				mtx.lock();
				changeFgBg(selfg, bgc);
				_setmode(_fileno(stdout), _O_WTEXT);
				gotoxy(0, y);
				wprintf(L"%s", niz);
				mtx.unlock();
				free(niz);
				PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
				PlaySound(TEXT(CLICK), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
				Sleep(40);
			}

			/****************************
			------ODABIR-POLJA-----------
			****************************/
			if (c == 13)
			{
				odrediDugme(dugme, y);

				if (!strcmp(dugme, BUTTON6))
				{
					PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
					PlaySound(TEXT(CONFIRM), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
					startGameModeS();
				}
				if (!strcmp(dugme, BUTTON7))
				{
					PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
					PlaySound(TEXT(CONFIRM), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
					startGameModeC();
				}
			}

			if (c == 27)
			{
				PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
				PlaySound(TEXT(CONFIRM), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC);
				ispisi = 1;
				break;
			}
		}
	}
	if (ispisi)
		ispisiOpet(meni);
}

void update()
{
	while (1)
	{
		mtx.lock();
		gotoxy(183, height);
		changeFgBg(selfg, bgc);
		_setmode(_fileno(stdout), _O_TEXT);
		wprintf(L" ");
		mtx.unlock();
	}
}

void exitAnim()
{
	mtx.lock();
		changeFgBg(fgc, bgc);
		for (int i = 0; i < height/font; i++)
		{
			_setmode(_fileno(stdin), _O_WTEXT);
			gotoxy(0, i);
			wprintf(L"%c[2K", 27);
			Sleep(10);
		}
	mtx.unlock();
	return;
}

void startGameModeS()
{
	wchar_t* niz;
	char c;
	char d[50] = {};
	BLOK_ZMIJE defBlok;
	int trenutniSmer = SMER_DESNO;
	int prosliSmer = SMER_DESNO;
	int score = 0;
	int level = 0;
	int speed = 5;
	snakeSize = BEGIN_SIZE;
	speedZmije = DEFAULT_SPEED;
	BOOL guta=false;
	BOOL prviput=true;
	BOOL mute = false;
	//ispisiHranu();
	defBlok.oblik = BLOK_TELO_DESNO;
	defBlok.position.X = 10;
	defBlok.position.Y = 10;

	for (int i = 0; i < snakeSize; i++)
		zmija[i] = defBlok;

	zmija[snakeSize - 1].oblik = BLOK_REP_DESNO;
	zmija[0].oblik = BLOK_GLAVA_DESNO;

	sareniloSareni = false;
	startAnim();
	ispisiMapu(mapWidth, mapHeight);

	LevelPozicija.X = 64;  LevelPozicija.Y = mapHeight + 7;		
	ScorePozicija.X = 165; ScorePozicija.Y = mapHeight + 7;
	SpeedPozicija.X = 274; SpeedPozicija.Y = mapHeight + 7;

	niz = ucitajFajl(HUDS);				//ispisuje hud

	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	wprintf(L"%s", niz);
	mtx.unlock();

	ispisBroj(LevelPozicija.X, LevelPozicija.Y, level);
	ispisBroj(ScorePozicija.X, ScorePozicija.Y, score);
	ispisBroj(SpeedPozicija.X, SpeedPozicija.Y, speed);

	zmija[2].position.X = marginaLevo + (4 * 20);
	zmija[1].position.X = zmija[2].position.X+4;
	zmija[0].position.X = zmija[1].position.X+4;
	zmija[3].position.X = zmija[2].position.X-4;
	zmija[4].position.X = zmija[3].position.X-4;

	zmija[0].position.Y = marginaGore + (4 * 20);
	zmija[1].position.Y = zmija[0].position.Y;
	zmija[2].position.Y = zmija[0].position.Y;
	zmija[3].position.Y = zmija[0].position.Y;
	zmija[4].position.Y = zmija[0].position.Y;

	for (int i = 0; i < snakeSize; i++)
		ispisiBlok(zmija[i]);

	hranaBlok.position.X = marginaLevo + (4 * 20);
	hranaBlok.position.Y = marginaGore + (4 * 10);

	hrana(hranaBlok.position.X, hranaBlok.position.Y);
	PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC );
	PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (1) {
		Sleep(speedZmije);
		if (!guta)
			obrisiPolje(zmija[snakeSize - 1].position.X, zmija[snakeSize - 1].position.Y);

		siftujPoziciju(zmija, snakeSize);
		prosliSmer = trenutniSmer;
		if (_kbhit())
		{
			c = _getch();
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			if ((c == 'w' || c == 'W') && trenutniSmer != SMER_DOLE)
			{
				prosliSmer = trenutniSmer;
				trenutniSmer = SMER_GORE;
			}

			if ((c == 's' || c == 'S') && trenutniSmer != SMER_GORE)
			{
				prosliSmer = trenutniSmer;
				trenutniSmer = SMER_DOLE;
			}

			if ((c == 'a' || c == 'A') && trenutniSmer != SMER_DESNO)
			{
				prosliSmer = trenutniSmer;
				trenutniSmer = SMER_LEVO;
			}

			if ((c == 'd' || c == 'D') && trenutniSmer != SMER_LEVO)
			{
				prosliSmer = trenutniSmer;
				trenutniSmer = SMER_DESNO;
			}

			if (c == 13)
			{
				while (!kbhit())
				{

				}
			}
			
			if (c >= '0' && c <= '9')
			{
				switch (c-48)
				{
				case 0:
					if (speedZmije != ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(TURBO_MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = ULTRA_MOD;
					break;
				case 1:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED + 100;
					break;
				case 2:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED + 75;
					break;
				case 3:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED + 50;
					break;
				case 4:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED + 25;
					break;
				case 5:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED;
					break;
				case 6:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED - 25;
					break;
				case 7:
					if (speedZmije == ULTRA_MOD)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED - 50;
					break;
				case 8:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED - 75;
					break;
				case 9:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED - 100;
					break;
				}
				speed = c-48;
				ispisBroj(SpeedPozicija.X, SpeedPozicija.Y, speed);
			}
			if (c == 'm' || c == 'M')
			{
				if (!mute)
				{
					PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
					mute = true;
				}
				else if (mute)
				{
					if(speed)
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					else
						PlaySound(TEXT(TURBO_MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					mute = false;
				}

			}
			if (c == 'p' || c == 'P')
			{
				while (1)
				{
					if (!kbhit())
					{
						char d;
						d = getch();
						if (d == 'p' || d == 'P')
							break;
					}
				}
			}

		}

		/*************************************************************************************************
		 *-OBLIK-ZMIJE-U-ODNOSU-NA-PROMENLJIV-PARAMETAR-TRENUTNI-SMER-I-CONST-PARAM-PROSLI-SMER=SMER_DESNO
		 *************************************************************************************************/
		if (trenutniSmer == SMER_DESNO && prosliSmer == SMER_DESNO)			
		{																	
			zmija[0].position.X += 4;
			if(guta)
				zmija[1].oblik = BLOK_TELO_PROGUTAO_DESNO;
			else
				zmija[1].oblik = BLOK_TELO_DESNO;

			if (hranaBlok.position.Y == zmija[0].position.Y && zmija[0].position.X == (hranaBlok.position.X - 4))
				zmija[0].oblik = BLOK_GLAVA_DESNO_GUTA;
			else
				zmija[0].oblik = BLOK_GLAVA_DESNO;
		}																	
																			
		else if (trenutniSmer == SMER_DOLE && prosliSmer == SMER_DESNO)		
		{																	
			zmija[0].position.Y += 4;	
			zmija[1].oblik = BLOK_TELO_KRIVINA_GORE_DESNO;					
			zmija[0].oblik = BLOK_GLAVA_DOLE;

		}																	
																			
		else if (trenutniSmer == SMER_GORE && prosliSmer == SMER_DESNO)		
		{																	
			zmija[0].position.Y -= 4;										
			zmija[1].oblik = BLOK_TELO_KRIVINA_DOLE_DESNO;					
			zmija[0].oblik = BLOK_GLAVA_GORE;
		}																	
		/***************************************************************
		****************************************************************/

		/************************************************************************************************
		 *-OBLIK-ZMIJE-U-ODNOSU-NA-PROMENLJIV-PARAMETAR-TRENUTNI-SMER-I-CONST-PARAM-PROSLI-SMER=SMER_GORE
		 ************************************************************************************************/
		else if (trenutniSmer == SMER_GORE && prosliSmer == SMER_GORE)                                                                     
		{                                                                                                                                    
			zmija[0].position.Y -= 4;                                                                                                         
			if (guta)
				zmija[1].oblik = BLOK_TELO_PROGUTAO_GORE;
			else
				zmija[1].oblik = BLOK_TELO_GORE;

			if (hranaBlok.position.X == zmija[0].position.X && zmija[0].position.Y == (hranaBlok.position.Y + 4))
				zmija[0].oblik = BLOK_GLAVA_GORE_GUTA;
			else
				zmija[0].oblik = BLOK_GLAVA_GORE;
		}																																		
		
		else if (trenutniSmer == SMER_LEVO && prosliSmer == SMER_GORE)
		{
			zmija[0].position.X -= 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_GORE_DESNO;
			zmija[0].oblik = BLOK_GLAVA_LEVO;
		}

		else if (trenutniSmer == SMER_DESNO && prosliSmer == SMER_GORE)
		{
			zmija[0].position.X += 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_GORE_LEVO;
			zmija[0].oblik = BLOK_GLAVA_DESNO;
		}
		/***************************************************************
		****************************************************************/

		/************************************************************************************************
		 *-OBLIK-ZMIJE-U-ODNOSU-NA-PROMENLJIV-PARAMETAR-TRENUTNI-SMER-I-CONST-PARAM-PROSLI-SMER=SMER_DOLE
		 ************************************************************************************************/
		else if (trenutniSmer == SMER_DOLE && prosliSmer == SMER_DOLE)
		{
			zmija[0].position.Y += 4;
			if (guta)
				zmija[1].oblik = BLOK_TELO_PROGUTAO_DOLE;
			else
				zmija[1].oblik = BLOK_TELO_DOLE;


			if (hranaBlok.position.X == zmija[0].position.X && zmija[0].position.Y == (hranaBlok.position.Y - 4))
				zmija[0].oblik = BLOK_GLAVA_DOLE_GUTA;
			else
				zmija[0].oblik = BLOK_GLAVA_DOLE;
		}

		else if (trenutniSmer == SMER_LEVO && prosliSmer == SMER_DOLE)
		{
			zmija[0].position.X -= 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_DOLE_DESNO;
			zmija[0].oblik = BLOK_GLAVA_LEVO;
		}

		else if (trenutniSmer == SMER_DESNO && prosliSmer == SMER_DOLE)
		{
			zmija[0].position.X += 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_DOLE_LEVO;
			zmija[0].oblik = BLOK_GLAVA_DESNO;
		}
		/***************************************************************
		****************************************************************/

		/************************************************************************************************
		 *-OBLIK-ZMIJE-U-ODNOSU-NA-PROMENLJIV-PARAMETAR-TRENUTNI-SMER-I-CONST-PARAM-PROSLI-SMER=SMER_LEVO
		 ************************************************************************************************/
		else if (trenutniSmer == SMER_LEVO && prosliSmer == SMER_LEVO)
		{
			zmija[0].position.X -= 4;
			
			if (guta)
				zmija[1].oblik = BLOK_TELO_PROGUTAO_LEVO;
			else
				zmija[1].oblik = BLOK_TELO_LEVO;

			if (hranaBlok.position.Y == zmija[0].position.Y && zmija[0].position.X == (hranaBlok.position.X + 4))
				zmija[0].oblik = BLOK_GLAVA_LEVO_GUTA;
			else
				zmija[0].oblik = BLOK_GLAVA_LEVO;
		}

		else if (trenutniSmer == SMER_DOLE && prosliSmer == SMER_LEVO)
		{
			zmija[0].position.Y += 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_GORE_LEVO;
			zmija[0].oblik = BLOK_GLAVA_DOLE;
		}

		else if (trenutniSmer == SMER_GORE && prosliSmer == SMER_LEVO)
		{
			zmija[0].position.Y -= 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_DOLE_LEVO;
			zmija[0].oblik = BLOK_GLAVA_GORE;
		}
		/***************************************************************
		****************************************************************/


		if (zmija[snakeSize - 1].oblik == BLOK_REP_DESNO || zmija[snakeSize-1].oblik  == BLOK_REP_LEVO)
		{
			if (zmija[snakeSize - 1].position.Y > zmija[snakeSize - 2].position.Y)
				zmija[snakeSize - 1].oblik = BLOK_REP_GORE;

			if (zmija[snakeSize - 1].position.Y < zmija[snakeSize - 2].position.Y)
				zmija[snakeSize - 1].oblik = BLOK_REP_DOLE;

			if (zmija[snakeSize - 1].position.Y == (marginaDole - 4) && zmija[snakeSize - 2].position.Y == marginaGore)
				zmija[snakeSize - 1].oblik = BLOK_REP_DOLE;

			if (zmija[snakeSize - 2].position.Y == (marginaDole - 4) && zmija[snakeSize - 1].position.Y == marginaGore)
				zmija[snakeSize - 1].oblik = BLOK_REP_GORE;
			
		}
		
		else
		{
			if (zmija[snakeSize - 1].position.X > zmija[snakeSize - 2].position.X)
				zmija[snakeSize - 1].oblik = BLOK_REP_LEVO;

			if (zmija[snakeSize - 1].position.X < zmija[snakeSize - 2].position.X)
				zmija[snakeSize - 1].oblik = BLOK_REP_DESNO;

			if (zmija[snakeSize - 1].position.X == (marginaDesno - 4) && zmija[snakeSize - 2].position.X == marginaLevo)
				zmija[snakeSize - 1].oblik = BLOK_REP_DESNO;

			if (zmija[snakeSize - 2].position.X == (marginaDesno - 4) && zmija[snakeSize - 1].position.X == marginaLevo)
				zmija[snakeSize - 1].oblik = BLOK_REP_LEVO;
		}
		
		if (isteCoord(zmija, zmija[0].position, snakeSize, 1))
		{
			//blinkAnim(zmija, snakeSize);
			GameOver();
		}

		if (zmija[0].position.X == marginaDesno)
			zmija[0].position.X = marginaLevo;

		if (zmija[0].position.X == marginaLevo - 4)
			zmija[0].position.X = marginaDesno - 4;

		if (zmija[0].position.Y == marginaDole)
			zmija[0].position.Y = marginaGore;

		if (zmija[0].position.Y == marginaGore - 4)
			zmija[0].position.Y = marginaDole - 4;

		if (!guta)
			ispisiBlok(zmija[snakeSize - 1]);

		ispisiBlok(zmija[0]);
		ispisiBlok(zmija[1]);
		

		guta = false;
		
		if (zmija[0].position.X == hranaBlok.position.X && zmija[0].position.Y == hranaBlok.position.Y)
		{
			if (speed)
				score += speed;
			else
				score += 20;
			ispisBroj(ScorePozicija.X, ScorePozicija.Y, score);
			guta = true;
			do
				promeniCord(&hranaBlok);
			while (isteCoord(zmija, hranaBlok.position, snakeSize, 0));
			hrana(hranaBlok.position.X, hranaBlok.position.Y);

			snakeSize++;
			zmija[snakeSize - 1] = zmija[snakeSize - 2];

			if (zmija[snakeSize - 1].oblik == BLOK_REP_DESNO)
				zmija[snakeSize - 1].position.X -= 4;

			else if (zmija[snakeSize - 1].oblik == BLOK_REP_LEVO)
				zmija[snakeSize - 1].position.X += 4;

			else if (zmija[snakeSize - 1].oblik == BLOK_REP_GORE)
				zmija[snakeSize - 1].position.Y += 4;

			else
				zmija[snakeSize - 1].position.Y -= 4;

		}

	}

}
void startGameModeC()
{
	wchar_t* niz;
	char c;
	char d[50] = {};
	BLOK_ZMIJE defBlok;
	int trenutniSmer = SMER_DESNO;
	int prosliSmer = SMER_DESNO;
	int score = 0;
	int level = 1;
	int speed = 5;
	snakeSize = BEGIN_SIZE;
	speedZmije = DEFAULT_SPEED;
	BOOL guta = false;
	BOOL prviput = true;
	BOOL mute = false;
	//ispisiHranu();
	defBlok.oblik = BLOK_TELO_DESNO;
	defBlok.position.X = 10;
	defBlok.position.Y = 10;

	for (int i = 0; i < snakeSize; i++)
		zmija[i] = defBlok;

	zmija[snakeSize - 1].oblik = BLOK_REP_DESNO;
	zmija[0].oblik = BLOK_GLAVA_DESNO;

	sareniloSareni = false;
	startAnim();
	ispisiMapu(mapWidth, mapHeight);	//ovo je zapravo ram ali nmvz
	LevelPozicija.X = 64;  LevelPozicija.Y = mapHeight + 7;
	ScorePozicija.X = 165; ScorePozicija.Y = mapHeight + 7;
	SpeedPozicija.X = 274; SpeedPozicija.Y = mapHeight + 7;

	niz = ucitajFajl(HUDS);				//ispisuje hud

	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	wprintf(L"%s", niz);
	mtx.unlock();

	mapa1();

	ispisBroj(LevelPozicija.X, LevelPozicija.Y, level);
	ispisBroj(ScorePozicija.X, ScorePozicija.Y, score);
	ispisBroj(SpeedPozicija.X, SpeedPozicija.Y, speed);

	zmija[2].position.X = marginaLevo + (4 * 20);
	zmija[1].position.X = zmija[2].position.X + 4;
	zmija[0].position.X = zmija[1].position.X + 4;
	zmija[3].position.X = zmija[2].position.X - 4;
	zmija[4].position.X = zmija[3].position.X - 4;

	zmija[0].position.Y = marginaGore + (4 * 20);
	zmija[1].position.Y = zmija[0].position.Y;
	zmija[2].position.Y = zmija[0].position.Y;
	zmija[3].position.Y = zmija[0].position.Y;
	zmija[4].position.Y = zmija[0].position.Y;

	for (int i = 0; i < snakeSize; i++)
		ispisiBlok(zmija[i]);

	hranaBlok.position.X = marginaLevo + (4 * 20);
	hranaBlok.position.Y = marginaGore + (4 * 10);

	hrana(hranaBlok.position.X, hranaBlok.position.Y);
	PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
	PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (1) {
		Sleep(speedZmije);
		if (!guta)
			obrisiPolje(zmija[snakeSize - 1].position.X, zmija[snakeSize - 1].position.Y);

		if (snakeSize == 10)
		{
			level++;
			ispisBroj(LevelPozicija.X, LevelPozicija.Y, level);
			for (int i = 0; i < snakeSize; i++)
			{
				obrisiPolje(zmija[i].position.X, zmija[i].position.Y);
				zmija[i].position.X = 0;
				zmija[i].position.Y = 0;
				zmija[i].oblik = 0;
			}
			for (int i = 0; i < brPepreka; i++)
			{
				obrisiPolje(prepreke[i].X, prepreke[i].Y);
				prepreke[i].X = 0, prepreke[i].Y = 0;
			}
			brPepreka = 0;
			if (level == 3)
				mapa2();
			if (level == 4)
			{
				system("cls");
				meni();
			}
			snakeSize = 5;
			zmija[2].position.X = marginaLevo + (4 * 20);
			zmija[1].position.X = zmija[2].position.X + 4;
			zmija[0].position.X = zmija[1].position.X + 4;
			zmija[3].position.X = zmija[2].position.X - 4;
			zmija[4].position.X = zmija[3].position.X - 4;

			zmija[0].position.Y = marginaGore + (4 * 20);
			zmija[1].position.Y = zmija[0].position.Y;
			zmija[2].position.Y = zmija[0].position.Y;
			zmija[3].position.Y = zmija[0].position.Y;
			zmija[4].position.Y = zmija[0].position.Y;
			ispisBroj(LevelPozicija.X, LevelPozicija.Y, level);


			for (int i = 0; i < snakeSize; i++)
				ispisiBlok(zmija[i]);

			trenutniSmer = SMER_DESNO;
			prosliSmer = SMER_DESNO;
		}

		siftujPoziciju(zmija, snakeSize);
		prosliSmer = trenutniSmer;
		if (_kbhit())
		{
			c = _getch();
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			if ((c == 'w' || c == 'W') && trenutniSmer != SMER_DOLE)
			{
				prosliSmer = trenutniSmer;
				trenutniSmer = SMER_GORE;
			}

			if ((c == 's' || c == 'S') && trenutniSmer != SMER_GORE)
			{
				prosliSmer = trenutniSmer;
				trenutniSmer = SMER_DOLE;
			}

			if ((c == 'a' || c == 'A') && trenutniSmer != SMER_DESNO)
			{
				prosliSmer = trenutniSmer;
				trenutniSmer = SMER_LEVO;
			}

			if ((c == 'd' || c == 'D') && trenutniSmer != SMER_LEVO)
			{
				prosliSmer = trenutniSmer;
				trenutniSmer = SMER_DESNO;
			}

			if (c == 13)
			{
				while (!kbhit())
				{

				}
			}

			if (c >= '0' && c <= '9')
			{
				switch (c - 48)
				{
				case 0:
					if (speedZmije != ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(TURBO_MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = ULTRA_MOD;
					break;
				case 1:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED + 100;
					break;
				case 2:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED + 75;
					break;
				case 3:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED + 50;
					break;
				case 4:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED + 25;
					break;
				case 5:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED;
					break;
				case 6:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED - 25;
					break;
				case 7:
					if (speedZmije == ULTRA_MOD)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED - 50;
					break;
				case 8:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED - 75;
					break;
				case 9:
					if (speedZmije == ULTRA_MOD && !mute)
					{
						PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					}
					speedZmije = DEFAULT_SPEED - 100;
					break;
				}
				speed = c - 48;
				ispisBroj(SpeedPozicija.X, SpeedPozicija.Y, speed);
			}
			if (c == 'm' || c == 'M')
			{
				if (!mute)
				{
					PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
					mute = true;
				}
				else if (mute)
				{
					if (speed)
						PlaySound(TEXT(MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					else
						PlaySound(TEXT(TURBO_MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);
					mute = false;
				}

			}
			if (c == 'p' || c == 'P')
			{
				while (1)
				{
					if (!kbhit())
					{
						char d;
						d = getch();
						if (d == 'p' || d == 'P')
							break;
					}
				}
			}

		}

		/*************************************************************************************************
		 *-OBLIK-ZMIJE-U-ODNOSU-NA-PROMENLJIV-PARAMETAR-TRENUTNI-SMER-I-CONST-PARAM-PROSLI-SMER=SMER_DESNO
		 *************************************************************************************************/
		if (trenutniSmer == SMER_DESNO && prosliSmer == SMER_DESNO)
		{
			zmija[0].position.X += 4;
			if (guta)
				zmija[1].oblik = BLOK_TELO_PROGUTAO_DESNO;
			else
				zmija[1].oblik = BLOK_TELO_DESNO;

			if (hranaBlok.position.Y == zmija[0].position.Y && zmija[0].position.X == (hranaBlok.position.X - 4))
				zmija[0].oblik = BLOK_GLAVA_DESNO_GUTA;
			else
				zmija[0].oblik = BLOK_GLAVA_DESNO;
		}

		else if (trenutniSmer == SMER_DOLE && prosliSmer == SMER_DESNO)
		{
			zmija[0].position.Y += 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_GORE_DESNO;
			zmija[0].oblik = BLOK_GLAVA_DOLE;

		}

		else if (trenutniSmer == SMER_GORE && prosliSmer == SMER_DESNO)
		{
			zmija[0].position.Y -= 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_DOLE_DESNO;
			zmija[0].oblik = BLOK_GLAVA_GORE;
		}
		/***************************************************************
		****************************************************************/

		/************************************************************************************************
		 *-OBLIK-ZMIJE-U-ODNOSU-NA-PROMENLJIV-PARAMETAR-TRENUTNI-SMER-I-CONST-PARAM-PROSLI-SMER=SMER_GORE
		 ************************************************************************************************/
		else if (trenutniSmer == SMER_GORE && prosliSmer == SMER_GORE)
		{
			zmija[0].position.Y -= 4;
			if (guta)
				zmija[1].oblik = BLOK_TELO_PROGUTAO_GORE;
			else
				zmija[1].oblik = BLOK_TELO_GORE;

			if (hranaBlok.position.X == zmija[0].position.X && zmija[0].position.Y == (hranaBlok.position.Y + 4))
				zmija[0].oblik = BLOK_GLAVA_GORE_GUTA;
			else
				zmija[0].oblik = BLOK_GLAVA_GORE;
		}

		else if (trenutniSmer == SMER_LEVO && prosliSmer == SMER_GORE)
		{
			zmija[0].position.X -= 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_GORE_DESNO;
			zmija[0].oblik = BLOK_GLAVA_LEVO;
		}

		else if (trenutniSmer == SMER_DESNO && prosliSmer == SMER_GORE)
		{
			zmija[0].position.X += 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_GORE_LEVO;
			zmija[0].oblik = BLOK_GLAVA_DESNO;
		}
		/***************************************************************
		****************************************************************/

		/************************************************************************************************
		 *-OBLIK-ZMIJE-U-ODNOSU-NA-PROMENLJIV-PARAMETAR-TRENUTNI-SMER-I-CONST-PARAM-PROSLI-SMER=SMER_DOLE
		 ************************************************************************************************/
		else if (trenutniSmer == SMER_DOLE && prosliSmer == SMER_DOLE)
		{
			zmija[0].position.Y += 4;
			if (guta)
				zmija[1].oblik = BLOK_TELO_PROGUTAO_DOLE;
			else
				zmija[1].oblik = BLOK_TELO_DOLE;


			if (hranaBlok.position.X == zmija[0].position.X && zmija[0].position.Y == (hranaBlok.position.Y - 4))
				zmija[0].oblik = BLOK_GLAVA_DOLE_GUTA;
			else
				zmija[0].oblik = BLOK_GLAVA_DOLE;
		}

		else if (trenutniSmer == SMER_LEVO && prosliSmer == SMER_DOLE)
		{
			zmija[0].position.X -= 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_DOLE_DESNO;
			zmija[0].oblik = BLOK_GLAVA_LEVO;
		}

		else if (trenutniSmer == SMER_DESNO && prosliSmer == SMER_DOLE)
		{
			zmija[0].position.X += 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_DOLE_LEVO;
			zmija[0].oblik = BLOK_GLAVA_DESNO;
		}
		/***************************************************************
		****************************************************************/

		/************************************************************************************************
		 *-OBLIK-ZMIJE-U-ODNOSU-NA-PROMENLJIV-PARAMETAR-TRENUTNI-SMER-I-CONST-PARAM-PROSLI-SMER=SMER_LEVO
		 ************************************************************************************************/
		else if (trenutniSmer == SMER_LEVO && prosliSmer == SMER_LEVO)
		{
			zmija[0].position.X -= 4;

			if (guta)
				zmija[1].oblik = BLOK_TELO_PROGUTAO_LEVO;
			else
				zmija[1].oblik = BLOK_TELO_LEVO;

			if (hranaBlok.position.Y == zmija[0].position.Y && zmija[0].position.X == (hranaBlok.position.X + 4))
				zmija[0].oblik = BLOK_GLAVA_LEVO_GUTA;
			else
				zmija[0].oblik = BLOK_GLAVA_LEVO;
		}

		else if (trenutniSmer == SMER_DOLE && prosliSmer == SMER_LEVO)
		{
			zmija[0].position.Y += 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_GORE_LEVO;
			zmija[0].oblik = BLOK_GLAVA_DOLE;
		}

		else if (trenutniSmer == SMER_GORE && prosliSmer == SMER_LEVO)
		{
			zmija[0].position.Y -= 4;
			zmija[1].oblik = BLOK_TELO_KRIVINA_DOLE_LEVO;
			zmija[0].oblik = BLOK_GLAVA_GORE;
		}
		/***************************************************************
		****************************************************************/


		if (zmija[snakeSize - 1].oblik == BLOK_REP_DESNO || zmija[snakeSize - 1].oblik == BLOK_REP_LEVO)
		{
			if (zmija[snakeSize - 1].position.Y > zmija[snakeSize - 2].position.Y)
				zmija[snakeSize - 1].oblik = BLOK_REP_GORE;

			if (zmija[snakeSize - 1].position.Y < zmija[snakeSize - 2].position.Y)
				zmija[snakeSize - 1].oblik = BLOK_REP_DOLE;

			if (zmija[snakeSize - 1].position.Y == (marginaDole - 4) && zmija[snakeSize - 2].position.Y == marginaGore)
				zmija[snakeSize - 1].oblik = BLOK_REP_DOLE;

			if (zmija[snakeSize - 2].position.Y == (marginaDole - 4) && zmija[snakeSize - 1].position.Y == marginaGore)
				zmija[snakeSize - 1].oblik = BLOK_REP_GORE;

		}

		else
		{
			if (zmija[snakeSize - 1].position.X > zmija[snakeSize - 2].position.X)
				zmija[snakeSize - 1].oblik = BLOK_REP_LEVO;

			if (zmija[snakeSize - 1].position.X < zmija[snakeSize - 2].position.X)
				zmija[snakeSize - 1].oblik = BLOK_REP_DESNO;

			if (zmija[snakeSize - 1].position.X == (marginaDesno - 4) && zmija[snakeSize - 2].position.X == marginaLevo)
				zmija[snakeSize - 1].oblik = BLOK_REP_DESNO;

			if (zmija[snakeSize - 2].position.X == (marginaDesno - 4) && zmija[snakeSize - 1].position.X == marginaLevo)
				zmija[snakeSize - 1].oblik = BLOK_REP_LEVO;
		}

		if (isteCoord(zmija, zmija[0].position, snakeSize, 1))
		{
			//blinkAnim(zmija, snakeSize);
			GameOver();
		}

		
		for (int p = 0; p < brPepreka; p++)
		{
			if (zmija[0].position.X == prepreke[p].X && zmija[0].position.Y == prepreke[p].Y)
				GameOver();
		}

		if (zmija[0].position.X == marginaDesno)
			zmija[0].position.X = marginaLevo;

		if (zmija[0].position.X == marginaLevo - 4)
			zmija[0].position.X = marginaDesno - 4;

		if (zmija[0].position.Y == marginaDole)
			zmija[0].position.Y = marginaGore;

		if (zmija[0].position.Y == marginaGore - 4)
			zmija[0].position.Y = marginaDole - 4;

		if (!guta)
			ispisiBlok(zmija[snakeSize - 1]);

		ispisiBlok(zmija[0]);
		ispisiBlok(zmija[1]);


		guta = false;

		if (zmija[0].position.X == hranaBlok.position.X && zmija[0].position.Y == hranaBlok.position.Y)
		{
			/*if (speed)
				score += speed;
			else
				score += 20;
			ispisBroj(ScorePozicija.X, ScorePozicija.Y, score);*/
			guta = true;
			BOOL prepreka = false;
			do
			{
				prepreka = false;
				promeniCord(&hranaBlok);
				for (int p = 0; p < brPepreka; p++)
				{
					if (hranaBlok.position.X == prepreke[p].X && hranaBlok.position.Y == prepreke[p].Y)
						prepreka = true;
				}
			}
			while (isteCoord(zmija, hranaBlok.position, snakeSize, 0)||prepreka);
			hrana(hranaBlok.position.X, hranaBlok.position.Y);

			snakeSize++;
			zmija[snakeSize - 1] = zmija[snakeSize - 2];

			if (zmija[snakeSize - 1].oblik == BLOK_REP_DESNO)
				zmija[snakeSize - 1].position.X -= 4;

			else if (zmija[snakeSize - 1].oblik == BLOK_REP_LEVO)
				zmija[snakeSize - 1].position.X += 4;

			else if (zmija[snakeSize - 1].oblik == BLOK_REP_GORE)
				zmija[snakeSize - 1].position.Y += 4;

			else
				zmija[snakeSize - 1].position.Y -= 4;

		}

	}
}

int isteCoord(BLOK_ZMIJE* zmija, COORD korde, int n, int snakeORnot)//1 for snake comparing 0 for not snake comparing
{
	int i;
	i = snakeORnot;
	for (; i < n; i++)
	{
		if (korde.X == zmija[i].position.X && korde.Y == zmija[i].position.Y)
			return 1;
	}
	return 0;
}

void promeniCord(BLOK_ZMIJE* blok)
{
	do
		blok->position.X = marginaLevo + ((rand() % mapWidth + 1) * 4);
	while (blok->position.X <= marginaLevo || blok->position.X > marginaDesno-4);

	do
		blok->position.Y = marginaGore + ((rand() % mapHeight+ 1) * 4);
	 while (blok->position.Y <= marginaGore || blok->position.Y > marginaDole - 4);
}

void changeConsole2(SHORT width, SHORT height, int font, int fontx)
{
	CONSOLE_FONT_INFOEX cfi;
	char komanda[50] = "mode";
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontx;
	cfi.dwFontSize.Y = font;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	if (!sareniloSareni)
	{
		CONSOLE_SCREEN_BUFFER_INFOEX cinfo;
		cinfo.cbSize = sizeof(cinfo);
		GetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo);
		cinfo.dwSize.X = width;
		cinfo.dwMaximumWindowSize.X = 1920;
		cinfo.dwMaximumWindowSize.Y = 1080;
		cinfo.srWindow.Bottom = height;
		cinfo.cbSize = sizeof(cinfo);
		SetConsoleScreenBufferInfoEx(GetStdHandle(STD_OUTPUT_HANDLE), &cinfo);
		info.dwSize.X = width;
		info.srWindow.Bottom = height;
	}
	else
	{
		info.dwSize.X = width;
		info.srWindow.Bottom = height;
	}
}

void brJedan(int x, int y1)//70
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	int y = y1;
	_setmode(_fileno(stdout), _O_WTEXT);

	gotoxy(x, y);	wprintf(L" ████     "); y++;
	gotoxy(x, y);	wprintf(L"█████     "); y++;
	gotoxy(x, y);	wprintf(L"  ███     "); y++;
	gotoxy(x, y);	wprintf(L"  ███     "); y++;
	gotoxy(x, y);	wprintf(L"  ███     "); y++;
	gotoxy(x, y);	wprintf(L"  ███     "); y++;
	gotoxy(x, y);	wprintf(L"  ███     "); y++;
	gotoxy(x, y);	wprintf(L"███████   "); y++;

	mtx.unlock();
}
void brDva(int x, int y1)//dodaj pocetak i kraj, y1 i y2
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	int y = y1;
	_setmode(_fileno(stdout), _O_WTEXT);

	gotoxy(x, y);	wprintf(L" ▄██████▄ "); y++;
	gotoxy(x, y);   wprintf(L"████  ████"); y++;
	gotoxy(x, y);   wprintf(L"       ███"); y++;
	gotoxy(x, y);	wprintf(L"     ▄████"); y++;
	gotoxy(x, y);	wprintf(L" ▄██████  "); y++;
	gotoxy(x, y);   wprintf(L"████      "); y++;
	gotoxy(x, y);   wprintf(L"███       "); y++;
	gotoxy(x, y);	wprintf(L"██████████"); y++;

	mtx.unlock();
}
void brTri(int x, int y1)
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	int y = y1;
	_setmode(_fileno(stdout), _O_WTEXT);

	gotoxy(x, y);	wprintf(L" ▄██████▄ "); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L"     ▄████"); y++;
	gotoxy(x, y);	wprintf(L"    ████▀ "); y++;
	gotoxy(x, y);	wprintf(L"     ▀███▄"); y++;
	gotoxy(x, y);	wprintf(L"███    ███"); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L" ▀██████▀ "); y++;

	mtx.unlock();
}
void brCet(int x, int y1)
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	int y = y1;
	_setmode(_fileno(stdout), _O_WTEXT);

	gotoxy(x, y);	wprintf(L"    █████ "); y++;
	gotoxy(x, y);	wprintf(L"   ██████ "); y++;
	gotoxy(x, y);	wprintf(L"  ███ ███ "); y++;
	gotoxy(x, y);	wprintf(L" ███  ███ "); y++;
	gotoxy(x, y);	wprintf(L"███   ███ "); y++;
	gotoxy(x, y);	wprintf(L"██████████"); y++;
	gotoxy(x, y);	wprintf(L"      ███ "); y++;
	gotoxy(x, y);	wprintf(L"      ███ "); y++;

	mtx.unlock();

}
void brPet(int x, int y1)
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	int y = y1;
	_setmode(_fileno(stdout), _O_WTEXT);

	gotoxy(x, y);	wprintf(L"█████████ "); y++;
	gotoxy(x, y);	wprintf(L"███       "); y++;
	gotoxy(x, y);	wprintf(L"███       "); y++;
	gotoxy(x, y);	wprintf(L"████████▄ "); y++;
	gotoxy(x, y);	wprintf(L"     ▀████"); y++;
	gotoxy(x, y);	wprintf(L"       ███"); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L" ▀██████▀ "); y++;

	mtx.unlock();

}
void brSest(int x, int y1)
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	int y = y1;
	_setmode(_fileno(stdout), _O_WTEXT);

	gotoxy(x, y);	wprintf(L" ▄██████▄ "); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L"███       "); y++;
	gotoxy(x, y);	wprintf(L"████████▄ "); y++;
	gotoxy(x, y);	wprintf(L"████ ▀████"); y++;
	gotoxy(x, y);	wprintf(L"███    ███"); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L" ▀██████▀ "); y++;

	mtx.unlock();

}
void brSedam(int x, int y1)
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	int y = y1;
	_setmode(_fileno(stdout), _O_WTEXT);

	gotoxy(x, y);	wprintf(L"██████████"); y++;
	gotoxy(x, y);	wprintf(L"      ████"); y++;
	gotoxy(x, y);	wprintf(L"     ████ "); y++;
	gotoxy(x, y);	wprintf(L"    ████  "); y++;
	gotoxy(x, y);	wprintf(L" ████████ "); y++;
	gotoxy(x, y);	wprintf(L"  ████    "); y++;
	gotoxy(x, y);	wprintf(L" ████     "); y++;
	gotoxy(x, y);	wprintf(L"████      "); y++;

	mtx.unlock();
}
void brOsam(int x, int y1)
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	int y = y1;
	_setmode(_fileno(stdout), _O_WTEXT);

	gotoxy(x, y);	wprintf(L" ▄██████▄ "); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L"████▄ ████"); y++;
	gotoxy(x, y);	wprintf(L" ▀██████▀ "); y++;
	gotoxy(x, y);	wprintf(L"▄███▀▀███▄"); y++;
	gotoxy(x, y);	wprintf(L"███    ███"); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L" ▀██████▀ "); y++;

	mtx.unlock();
}
void brDevet(int x, int y1)
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	int y = y1;
	_setmode(_fileno(stdout), _O_WTEXT);

	gotoxy(x, y);	wprintf(L" ▄██████▄ "); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L"███    ███"); y++;
	gotoxy(x, y);	wprintf(L"████▄ ████"); y++;
	gotoxy(x, y);	wprintf(L" ▀████████"); y++;
	gotoxy(x, y);	wprintf(L"       ███"); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L" ▀██████▀ "); y++;


	mtx.unlock();
}
void brNula(int x, int y1)
{
	mtx.lock();
	changeFgBg(fgc, bgc);
	int y = y1;
	_setmode(_fileno(stdout), _O_WTEXT);

	gotoxy(x, y);	wprintf(L" ▄██████▄ "); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L"███    ███"); y++;
	gotoxy(x, y);	wprintf(L"███    ███"); y++;
	gotoxy(x, y);	wprintf(L"███    ███"); y++;
	gotoxy(x, y);	wprintf(L"███    ███"); y++;
	gotoxy(x, y);	wprintf(L"████  ████"); y++;
	gotoxy(x, y);	wprintf(L" ▀██████▀ "); y++;

	mtx.unlock();
}

void ispisBroj(int x, int y, int broj) 
{
	char brojs[10];
	int i=0;
	itoa(broj, brojs, 10);

	while (brojs[i])
	{
		switch (brojs[i]-48)
		{
			case 0:brNula(x, y); break;
			case 1:brJedan(x, y); break;
			case 2:brDva(x, y); break;
			case 3:brTri(x, y); break;
			case 4:brCet(x, y); break;
			case 5:brPet(x, y); break;
			case 6:brSest(x, y); break;
			case 7:brSedam(x, y); break;
			case 8:brOsam(x, y); break;
			case 9:brDevet(x, y); break;
		}
		x+=11;
		i++;
	}
}

void startAnim()
{
	char ime[100] = COUNTDOWN_ANIM;
	char broj[20];
	wchar_t *niz;

	mtx.lock();
	changeConsole2(150, 50, font, 0);
	changeFgBg(0, 15);
	gotoxy(0, 0);
	system("cls");
	mtx.unlock();
	PlaySound(TEXT(PROJECTOR_MUSIC), NULL, SND_FILENAME|SND_ASYNC);
	Sleep(10);
	for (int i = 0; i <= 52; i++)
	{
		itoa(i, broj, 10);
		strcat(ime, broj);
		strcat(ime, ".txt");
		niz = ucitajFajl(ime);
		mtx.lock();
		_setmode(_fileno(stdout), _O_TEXT);
		gotoxy(0, 0);
		changeFgBg(0, 15);
		wprintf(L"%s", niz);
		mtx.unlock();
		strcpy(ime, COUNTDOWN_ANIM);
		free(niz);
		Sleep(50);
	}
}

void teloLevo(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"    "); y++;
	gotoxy(x, y);	wprintf(L"██ █"); y++;
	gotoxy(x, y);	wprintf(L"█ ██"); y++;
	gotoxy(x, y);	wprintf(L"    "); y++;
	mtx.unlock();
}

void teloDesno(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"    "); y++;
	gotoxy(x, y);	wprintf(L"█ ██"); y++;
	gotoxy(x, y);	wprintf(L"██ █"); y++;
	gotoxy(x, y);	wprintf(L"    "); y++;
	mtx.unlock();
}

void teloGore(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L"  █ "); y++;
	gotoxy(x, y);	wprintf(L" █  "); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	mtx.unlock();
}

void teloDole(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L" █  "); y++;
	gotoxy(x, y);	wprintf(L"  █ "); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	mtx.unlock();
}

void krivinaGoreLevo(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"    "); y++;
	gotoxy(x, y);	wprintf(L"  ██"); y++;
	gotoxy(x, y);	wprintf(L" █ █"); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	mtx.unlock();
}

void krivinaGoreDesno(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"    "); y++;
	gotoxy(x, y);	wprintf(L"██ "); y++;
	gotoxy(x, y);	wprintf(L"█ █"); y++;
	gotoxy(x, y);	wprintf(L" ██"); y++;
	mtx.unlock();
}

void krivinaDoleLevo(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L" █ █"); y++;
	gotoxy(x, y);	wprintf(L"  ██"); y++;
	mtx.unlock();	
}

void krivinaDoleDesno(int x, int y)			
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc); 
	gotoxy(x, y);	wprintf(L" ██"); y++;
	gotoxy(x, y);	wprintf(L"█ █"); y++;
	gotoxy(x, y);	wprintf(L"██ "); y++;
	mtx.unlock();
}

void teloProgutaoLevo(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);	
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L"██ █"); y++;
	gotoxy(x, y);	wprintf(L"█ ██"); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	mtx.unlock();
}
void teloProgutaoDesno(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L"█ ██"); y++;
	gotoxy(x, y);	wprintf(L"██ █"); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	mtx.unlock();
}

void teloProgutaoGore(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L"█ ██"); y++;
	gotoxy(x, y);	wprintf(L"██ █"); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	mtx.unlock();
}

void teloProgutaoDole(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L"██ █"); y++;
	gotoxy(x, y);	wprintf(L"█ ██"); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	mtx.unlock();
}

void glavaLevo(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"   █"); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L" ███"); y++;
	gotoxy(x, y);	wprintf(L"    "); y++;
	mtx.unlock();
}

void glavaDesno(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"█  "); y++;
	gotoxy(x, y);	wprintf(L" ██"); y++;
	gotoxy(x, y);	wprintf(L"███"); y++;
	gotoxy(x, y);	wprintf(L"   "); y++;
	mtx.unlock();
}

void glavaGore(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"   "); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L"█ █ "); y++;
	mtx.unlock();
}

void glavaDole(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"█ █ "); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	mtx.unlock();
}

void glavaLevoGuta(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"█ █"); y++;
	gotoxy(x, y);	wprintf(L" █ █"); y++;
	gotoxy(x, y);	wprintf(L" ███"); y++;
	gotoxy(x, y);	wprintf(L"█  "); y++;
	mtx.unlock();
}

void glavaDesnoGuta(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"█ █"); y++;
	gotoxy(x, y);	wprintf(L" █ "); y++;
	gotoxy(x, y);	wprintf(L"██ "); y++;
	gotoxy(x, y);	wprintf(L"  █"); y++;
	mtx.unlock();

}

void glavaGoreGuta(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"█  █"); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L"█ █ "); y++;
	mtx.unlock();
}

void glavaDoleGuta(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"█ █ "); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L"█  █"); y++;
	mtx.unlock();
}

void repDesno(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"    "); y++;
	gotoxy(x, y);	wprintf(L"  ██"); y++;
	gotoxy(x, y);	wprintf(L"████"); y++;
	gotoxy(x, y);	wprintf(L"    "); y++;
	mtx.unlock();
}

void repLevo(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"    "); y++;
	gotoxy(x, y);	wprintf(L"██  "); y++;
	gotoxy(x, y);	wprintf(L"████"); y++;
	gotoxy(x, y);	wprintf(L"    "); y++;
	mtx.unlock();	
}

void repGore(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L"  █ "); y++;
	gotoxy(x, y);	wprintf(L"  █ "); y++;
	mtx.unlock();
}

void repDole(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"  █ "); y++;
	gotoxy(x, y);	wprintf(L"  █ "); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	gotoxy(x, y);	wprintf(L" ██ "); y++;
	mtx.unlock();
}

void hrana(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	//gotoxy(x, y);	wprintf(L"   "); y++;
	gotoxy(x, y);	wprintf(L" █ "); y++;
	gotoxy(x, y);	wprintf(L"█ █"); y++;
	gotoxy(x, y);	wprintf(L" █ "); y++;
	mtx.unlock();
}

void obrisiPolje(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y); wprintf(L"    "); y++;
	gotoxy(x, y); wprintf(L"    "); y++;
	gotoxy(x, y); wprintf(L"    "); y++;
	gotoxy(x, y); wprintf(L"    "); y++;
	mtx.unlock();
}

void ispisiMapu(int width, int height)
{
	changeConsole2(width, height + 30, font, font);
	changeFgBg(fgc, bgc);
	system("cls");
	for (int j = 0; j < BORDER_THICKNES_Y; j++)	
		for (int i = 0; i < width; i++)
		{
			mtx.lock();
			_setmode(_fileno(stdout), _O_WTEXT);
			changeFgBg(fgc, bgc);
			wprintf(L"█");
			mtx.unlock();
		}

	for (int i = 0; i < height - BORDER_THICKNES_Y*2; i++)	
	{
		for (int j = 0; j < BORDER_THICKNES_X; j++)			
		{
			mtx.lock();
			_setmode(_fileno(stdout), _O_WTEXT);
			changeFgBg(fgc, bgc);
			wprintf(L"█");
			mtx.unlock();
		}
		for (int j = 0; j < width - BORDER_THICKNES_X*2; j++)
		{
			mtx.lock();
			_setmode(_fileno(stdout), _O_WTEXT);
			changeFgBg(fgc, bgc);
			wprintf(L" ");
			mtx.unlock();
		}

		for (int j = 0; j < 5; j++)				//zameni 5 sa BORDER_THICKNES_X
		{
			mtx.lock();
			_setmode(_fileno(stdout), _O_WTEXT);
			changeFgBg(fgc, bgc);
			wprintf(L"█");
			mtx.unlock();
		}

	}

	for (int j = 0; j < 3; j++)				//zameni 3 sa BORDER_THICKNES_Y
		for (int i = 0; i < width; i++)
		{
			mtx.lock();
			_setmode(_fileno(stdout), _O_WTEXT);
			changeFgBg(fgc, bgc);
			wprintf(L"█");
			mtx.unlock();
		}
}

void ispisiBlok(BLOK_ZMIJE blok)
{
		switch (blok.oblik)
		{
		case BLOK_TELO_LEVO: teloLevo(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_DESNO: teloDesno(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_GORE: teloGore(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_DOLE: teloDole(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_KRIVINA_GORE_LEVO: krivinaGoreLevo(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_KRIVINA_GORE_DESNO: krivinaGoreDesno(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_KRIVINA_DOLE_LEVO: krivinaDoleLevo(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_KRIVINA_DOLE_DESNO: krivinaDoleDesno(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_PROGUTAO_LEVO: teloProgutaoLevo(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_PROGUTAO_DESNO: teloProgutaoDesno(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_PROGUTAO_GORE: teloProgutaoGore(blok.position.X, blok.position.Y); break;
		case BLOK_TELO_PROGUTAO_DOLE: teloProgutaoDole(blok.position.X, blok.position.Y); break;
		case BLOK_GLAVA_LEVO: glavaLevo(blok.position.X, blok.position.Y); break;
		case BLOK_GLAVA_DESNO: glavaDesno(blok.position.X, blok.position.Y); break;
		case BLOK_GLAVA_GORE:glavaGore(blok.position.X, blok.position.Y); break;
		case BLOK_GLAVA_DOLE: glavaDole(blok.position.X, blok.position.Y); break;
		case BLOK_GLAVA_GORE_GUTA: glavaGoreGuta(blok.position.X, blok.position.Y); break;
		case BLOK_GLAVA_DOLE_GUTA: glavaDoleGuta(blok.position.X, blok.position.Y); break;
		case BLOK_GLAVA_DESNO_GUTA: glavaDesnoGuta(blok.position.X, blok.position.Y); break;
		case BLOK_GLAVA_LEVO_GUTA: glavaLevoGuta(blok.position.X, blok.position.Y); break;
		case BLOK_REP_LEVO: repLevo(blok.position.X, blok.position.Y); break;
		case BLOK_REP_DESNO: repDesno(blok.position.X, blok.position.Y); break;
		case BLOK_REP_GORE: repGore(blok.position.X, blok.position.Y); break;
		case BLOK_REP_DOLE: repDole(blok.position.X, blok.position.Y); break;
		}
}

void siftujPoziciju(BLOK_ZMIJE *niz, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		niz[i].position = niz[i - 1].position;
		if (i != 1 && i != n-1)
			niz[i].oblik = niz[i - 1].oblik;
	}
}

void blinkAnim(BLOK_ZMIJE* zmija, int snakeSize)
{
	for (int i = 0; i < 4; i++)
	{
		Sleep(350);
		for (int j = 0; j < snakeSize; j++)
			obrisiPolje(zmija[j].position.X, zmija[j].position.Y);
		Sleep(350);
		for (int j = 0; j < snakeSize; j++)
			ispisiBlok(zmija[j]);
	}
	while (1);
}

void GameOver()
{
	PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
	PlaySound(TEXT(GAME_OVER_MUSIC), NULL, SND_NODEFAULT | SND_FILENAME | SND_ASYNC | SND_LOOP);

	char frame[100] = DEAD_ANIM;
	char frameNum[3];
	wchar_t* niz;
	system("cls");
	gotoxy(0, 0);
	changeConsole2(500, 150, 1, 0);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	while (!_kbhit())
	{
		for (int i = 0; i < 39; i++)
		{
			SakriKursor();

			itoa(i, frameNum, 10);
			strcat(frame, frameNum);
			strcat(frame, ".txt");

			niz = ucitajFajl(frame);

			mtx.lock();

			_setmode(_fileno(stdout), _O_TEXT);
			changeFgBg(0, 15);
			gotoxy(0, 0);
			wprintf(L"%s", niz);

			mtx.unlock();

			free(niz);

			strcpy(frame, DEAD_ANIM);
			Sleep(25);
		}
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	PlaySound(NULL, NULL, SND_NODEFAULT | SND_ASYNC);
	system("cls");
	meni();
}

void zid(int x, int y)
{
	mtx.lock();
	_setmode(_fileno(stdout), _O_WTEXT);
	changeFgBg(fgc, bgc);
	gotoxy(x, y);	wprintf(L"████"); y++;
	gotoxy(x, y);	wprintf(L"████"); y++;
	gotoxy(x, y);	wprintf(L"████"); y++;
	gotoxy(x, y);	wprintf(L"████"); y++;
	mtx.unlock();
}

void mapa1()
{
	int pocetniX=marginaLevo;
	int pocetniY=marginaGore;
	int i = 0;
	prepreke[i].Y = pocetniY;
	prepreke[i].X = pocetniX;
	i++;
	while (pocetniX!=marginaDesno)
	{
		zid(pocetniX, pocetniY);
		pocetniX += 4;
		if (pocetniX == marginaDesno)
			break;
		prepreke[i].Y = pocetniY;
		prepreke[i].X = pocetniX;
		i++;
	}

	pocetniY += 4;
	while (pocetniY != marginaDole-4)
	{
		pocetniX = marginaLevo;
		zid(pocetniX, pocetniY);
		prepreke[i].X = pocetniX;
		prepreke[i].Y = pocetniY;
		i++;
		pocetniX = marginaDesno - 4;
		zid(pocetniX, pocetniY);
		prepreke[i].X = pocetniX;
		prepreke[i].Y = pocetniY;
		i++;
		pocetniY += 4;
	}
	pocetniX = marginaLevo;

	prepreke[i].Y = pocetniY;
	prepreke[i].X = pocetniX;
	i++;
	while (pocetniX != marginaDesno)
	{
		zid(pocetniX, pocetniY);
		pocetniX += 4;
		if (pocetniX == marginaDesno)
			break;
		prepreke[i].Y = pocetniY;
		prepreke[i].X = pocetniX;
		i++;
	}

	brPepreka = i;
}

void mapa2()
{

	int pocetniX = marginaLevo+16;
	int pocetniY = marginaGore;
	int j = 0;
	for (int i = 0; i < 4; i++)
	{
		pocetniX += 56;
		pocetniY = marginaGore+40;

			while (pocetniY!=marginaDole)
			{
				zid(pocetniX, pocetniY);
				prepreke[j].X = pocetniX;
				prepreke[j].Y = pocetniY;
				pocetniY += 4;
				j++;
			}
	}
	brPepreka = j;
}