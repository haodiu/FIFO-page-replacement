#include <iostream>
#include "mylib.h"
#include <fstream>
#include <sstream>
using namespace std;
const int ngang = 18;
const int W = 123;
const int H = 42;
//=============================================================
struct ToaDo{
	int x, y;
	ToaDo(int a, int b){
		x = a;
		y = b;
	}
};

//=============================================================
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;
    
    SetConsoleCursorInfo(handle, &ConCurInf);
}
void setFontSize(int FontSize)
{
    CONSOLE_FONT_INFOEX info = {0};
    info.cbSize       = sizeof(info);
    info.dwFontSize.Y = FontSize;
    info.FontWeight   = FW_NORMAL;
    wcscpy(info.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

//=============================================================
void init(int *arr, int n){
	for(int i = 0; i < n; i++){
		arr[i] = -1;
	}
}
void nhap(int *arr, int n){
	for(int i = 0; i < n; i++){
		cin>>arr[i];
	}
}
bool isExists(int *arr, int n, int value){
	for(int i = 0; i < n; i++){
		if(arr[i] == value)
			return true;
	}
	return false;
}

void banner(){
	int i = 0;
	fstream file("banner.txt", ios::in);
	if(!file.is_open())
		return;
	string line;
	while(file){
		getline(file, line);
		gotoxy(11, 3+(i++));
		SetColor(11);
		cout<<line;
	}
	gotoxy(51, 40);
	SetColor(15);
	cout<<"PRESS ANY KEY TO START";
}

//=================================================================
void outChar(int x, int y, char data){
	gotoxy(x,y);
	cout<<data;
}

void line(ToaDo start, int length, int character){
	int i;
	for(i = start.x; i <= start.x+length; i++)
		outChar(i, start.y, (char)character);
}

void colorBox(ToaDo A, ToaDo C, string text,  int BGcolor, int textcolor){
	int rong = C.x-A.x;
	int cao = (A.y+C.y)/2;
	int vitriText =A.x + (rong-text.length())/2;
	SetBGColor(BGcolor);
	for(int j = 0; j<C.y-A.y+1; j++){
		gotoxy(A.x, A.y+j);
		for(int i = A.x+1; i<=C.x+1; i++){
			cout<<" ";
		}
		gotoxy(vitriText, cao);
		SetColor(textcolor);
		cout<<text;
		ShowCur(false);
	}
}	 

void xoaNoiDung(int y, int sodong, int color){  
	SetBGColor(color);
	for(int i=0; i<sodong; i++){
		gotoxy(2,y+i);  
		cout<<"                                                                                                                          "<<endl;
	}
}

void thongTinThuatToan(){
	string str[] = {"NUMBER OF PAGES", "PAGES", "NUMBER OF FRAME"};
	int x = 10;
	int y = 2;
	int rong = 19;
	for(int i=0; i<3; i++){
		colorBox(ToaDo(x, y+4*i), ToaDo(x+rong, y+2+4*i), str[i], 11, 0);
		if(i == 1)  colorBox(ToaDo(x+rong+8, y+4*i), ToaDo(x+rong+8+76, y+2+4*i), "",15, 0);
		else{
			colorBox(ToaDo(x+rong+8, y+4*i), ToaDo(x+rong+8+10, y+2+4*i), "",15,0);
		}
	}
}

void input(int *pages, int &soTrang, int &soKhungTrang){
	thongTinThuatToan();
	SetBGColor(15);
	SetColor(0);
	ShowCur(true);
	gotoxy(40, 3);
	cin>>soTrang;
	gotoxy(40, 7);
	nhap(pages, soTrang);
	gotoxy(40, 11);
	cin>>soKhungTrang;
	ShowCur(false);
}

void drawBorder(int soTrang, int soKhungTrang){
	int kc = 5, doc;
	SetColor(15);
	SetBGColor(0);
	outChar(12, ngang, 218);
	outChar(17 + kc*(soTrang-1), ngang, 191);
	for(int i = 0; i < soTrang-1; i++){
		outChar(17 + kc*i, ngang, 194);
		for(int j = 0; j < soKhungTrang-1; j++){
			outChar(17 + kc*i, ngang+2 + 2*j, 197);
			outChar(12, ngang+2 + 2*j, 195);
			outChar(12+kc*soTrang, ngang+2 + 2*j, 180);
		}
		outChar(17 + kc*i, ngang+2 + 2*(soKhungTrang-1), 193);
	}
	for(int i = 0; i < soTrang; i++){
		for(int j = 0; j <= soKhungTrang; j++){
			line(ToaDo(13+kc*i , ngang+2*j), 3, 196);
		}
	}
	for(int i = 0; i <= soTrang; i++){
		for(int j = 0; j < soKhungTrang; j++){
			outChar(12+kc*i, ngang+1 + 2*j, 179);
		}
	}
	outChar(17 + kc*(soTrang-1), ngang+2 + 2*(soKhungTrang-1), 217);
	outChar(12, ngang+2 + 2*(soKhungTrang-1), 192);
}
void pagesOut(int *pages, int soTrang){
	SetColor(11);
	SetBGColor(0);
	for(int i = 0; i < soTrang; i++){
		gotoxy(14+5*i, ngang-1);
		cout<<pages[i];
	}
}

void display(int *tmpArr, int soKhungTrang, int soTrang, int column){
	for(int i = 0; i < soKhungTrang; i++){
		gotoxy(14 + column * 5, ngang+1 + 2 * i);
		if(tmpArr[i] != -1)
			cout<<tmpArr[i];
		else	cout<<""; 
	}
}

int fifoPageReplacement(int *pages, int soTrang, int soKhungTrang){
	int tmpArr[soKhungTrang];
	int soLoiTrang = 0, x = 0;
	init(tmpArr, soKhungTrang);
	pagesOut(pages, soTrang);
	for(int i = 0; i < soTrang; i++){
		bool exists = false;
		if(isExists(tmpArr, soKhungTrang, pages[i])){
			soLoiTrang--;
			exists = true;
		}
		soLoiTrang++;
		SetColor(11);
		SetBGColor(0);
		if((soLoiTrang <= soKhungTrang) && (exists == false)){
			tmpArr[x++] = pages[i];
		}
		else if(exists == false){
			int idx = (soLoiTrang - 1) % soKhungTrang;
			tmpArr[idx] = pages[i];
		}
		if(exists == false){
			gotoxy(14 + i * 5, ngang+1 + 2 * soKhungTrang);
			cout<<"*";
		}
		drawBorder(soTrang, soKhungTrang);
		display(tmpArr, soKhungTrang, soTrang, i);
		Sleep(300);
	}
	return soLoiTrang;
}

void result(int pageFaults){
	stringstream ss;
	string tmp;
	ss << pageFaults;
	ss >> tmp;
	colorBox(ToaDo(34, 34), ToaDo(70, 36), "TOTAL NUMBER OF PAGE FAULTS", 11, 0);
	colorBox(ToaDo(72, 34), ToaDo(85, 36), tmp, 15, 0);	
	SetBGColor(0);
	SetColor(15);
	gotoxy(114, 1);
	cout<<"ESC : QUIT";
	gotoxy(50, 40);
	cout<<"PRESS ANY KEY TO CONTINUE";
}

//================================================================================
int main(){
	SetConsoleTitle("FIFO PAGE REPLACEMENT");
	resizeConsole(1024, 720);
	setFontSize(14);
	int soTrang, soKhungTrang;
	int pages[100];
	clrscr();
	ShowCur(false);
	banner();
	getch();
	while(true){
		xoaNoiDung(1, 40, 0);
		input(pages, soTrang, soKhungTrang);
		int soLoiTrang = fifoPageReplacement(pages, soTrang, soKhungTrang);
		result(soLoiTrang);
		int ch = getch();
		if(ch == 27){
			xoaNoiDung(1, 40, 0);
			gotoxy(59, 21);
			SetColor(11);
			cout<<"GOODBYE!";
			SetColor(0);
			return 0;
		}
	}
	return 0;
}
