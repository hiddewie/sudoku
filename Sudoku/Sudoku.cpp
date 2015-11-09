#include "stdafx.h"
#include <windows.h>
#include <Windows.h>
#include <iostream>
#include <sstream> 
#include <string>
#include <stdio.h>
#include <Commctrl.h>
#include "resource.h"
#include "cstring"
#include <atlstr.h>

using namespace std;

BOOL CALLBACK DialProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void solve(HWND);
bool getint (HWND);
void checkFull (void);
void checkBox (void);
void checkRow (void); int getEmptyR (int); int getEmptyNumR (int); int getEmptyBoxR (int);
void checkCol (void); int getEmptyC (int); int getEmptyNumC (int); int getEmptyBoxC (int);
void checkLose (void);
void checkWin (void);
void putint (HWND);

class Sudoku {
	int box[4][4];
	bool pos[4][4];
public:
	Sudoku () {for (int i = 1; i<=3; i++) {
		for (int j = 1; j<=3; j++){
			box[i][j] = 0; pos[i][j] = false;
		}}
	}
	void setBox (int a, int b, int n) {box [a][b] = n;}
	int getBox (int a, int b) {return box[a][b];}
	void setPos (int a, int b, bool x) {pos[a][b] = x;}
	bool getPos (int a, int b) {return pos[a][b];}

	int getEmptyB (void) {
		int count = 0;
		for (int i=1; i<=3; i++){
			for (int j=1; j<=3; j++){
				if (!box[i][j])
					count ++;
			}}
		return count;
	}
	int getEmptyNumB (void) {
		int nums[4][4];
		for (int i=1; i<=3; i++){
			for (int j=1; j<=3; j++){ nums[i][j] = 3*(i-1)+j;
			}}

		if (getEmptyB() == 1){
			for (int i=1; i<=3; i++){
				for (int j=1; j<=3; j++){
					if (box[i][j])
						nums [ ((box[i][j]-1)/3)+1 ][ ((box[i][j]-1)%3)+1] =0;
				}}

			for (int i=1; i<=3; i++){
				for (int j=1; j<=3; j++){
					if (nums[i][j])
						return 3*(i-1)+j;
				}}}
	}
	int getEmptyBoxB (void){
		if (getEmptyB() == 1){
			for (int i=1; i<=3; i++){
				for (int j=1; j<=3; j++){
					if (!box[i][j])
						return 3*(i-1)+j;

				}}}
	}
	void fill (void){
		int count  = 0;
		for (int i = 1; i<=3; i++){
			for (int j = 1; j<=3; j++){
				if (box[i][j])
					pos[i][j] = true;
			}}
	}
	int getFill (bool hor, int num){
		if (hor){
			for (int i = 1; i<=3; i++){
			if (box[i][1] == num || box[i][2] == num || box [i][3] == num)
				return i;
			}
		}
		else {
			for (int i = 1; i<=3; i++){
			if (box[1][i] == num || box[2][i] == num || box [3][i] == num)
				return i;
			}
		}
		return 0;
	}
};

int num [83];
char put [83];
bool win, lose;
Sudoku block[4][4];

/*CString str;
str.Format(_T("Getempty B = %d"), block[1].getEmptyB());
MessageBox(NULL, str, _T("caption"), MB_OK);*/

int WINAPI WinMain  (HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int       nCmdShow)
{
	return DialogBox (hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, DialProc);
}

BOOL CALLBACK DialProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) {

	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId) {
		case IDC_SOLVE:
			solve (hwnd);
			break;

		case IDCANCEL:
			PostQuitMessage(0);
			break;

		default:
			return FALSE;

		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return FALSE;

	}
	return 0;
}

bool getint (HWND hwnd) {
	for (int i = 1; i <=83; i++) {
		if (i != 16 && i != 17){
			if (i <16)
				num[i] = GetDlgItemInt(hwnd, i+1000, 0, true);
			else
				num[i-2] = GetDlgItemInt(hwnd, i+1000, 0, true);
		}
	}

	int a[10][10];
	int m,n;
	for (int i=0; i<=9; i++){
		for (int j=0; j<=9; j++){
			a[i][j] = 0;
		}
	}

	for (int i = 1; i<=81; i++){
		m = ((i-1)/9)+1;
		n = ((i-1)%9)+1;

		a[m][n] = num[i];
	}
	for (int i=1; i<=9; i++){
		for (int j=1; j<=9; j++){
			block[((i-1)/3)+1][((j-1)/3)+1].setBox(((i-1)%3)+1,((j-1)%3)+1, a[i][j]);
		}
	}

	return true;
}
void putint (HWND hwnd) {
	int a[10][10];
	int m,n;
	for (int i=0; i<=9; i++){
		for (int j=0; j<=9; j++){
			a[i][j] = 0;
		}
	}

	for (int i=1; i<=9; i++){
		for (int j=1; j<=9; j++){
			a[i][j] = block[((i-1)/3)+1][((j-1)/3)+1].getBox(((i-1)%3)+1,((j-1)%3)+1);
		}
	}
	for (int i = 1; i<=81; i++){
		m = ((i-1)/9)+1;
		n = ((i-1)%9)+1;

		num[i] = a[m][n];
	}

	//MessageBox (hwnd, L"Joy!!!",L"",MB_OK);
	for (int i = 1; i<=81; i++){
		if (num[i]){
			sprintf (put, "%d", num[i]);
			if (i <16)
				SendDlgItemMessage (hwnd, i+1000, WM_SETTEXT, 0, (LPARAM)put);
			else
				SendDlgItemMessage (hwnd, i+1002, WM_SETTEXT, 0, (LPARAM)put);
		}
	}
}

void solve (HWND hwnd) {

	win = lose = false;

	getint (hwnd);
	//while (!win && !lose){

	checkLose ();

	//checkFull();
	checkBox ();
	checkRow ();
	checkCol ();	

	checkWin();
	//}
	putint (hwnd);

	if (win) 
		MessageBox (hwnd, L"Sudoku opgelost!", L"Gereed", MB_OK);
	if (lose)
		MessageBox (NULL, L"Fout:\nU heeft verkeerde getallen ingevoerd, de sudoku kon niet opgelost worden. Probeer nog een keer.", L"Fout", MB_OK | MB_ICONERROR);

}
void checkFull (void) {
	for (int i = 1; i<=3; i++){
		for (int j = 1; j<=3; j++){
			for (int k = 1; k<=9; k++){
				int count = 0;
				for (int l = 1; l<=9; l++){
					if (block[i][j].getBox(((l-1)/3)+1, ((l-1)%3)+1) == k)
						count ++;
				}
				if (!count){
					block[i][j].fill();

					if (i == 1){
						if (j == 1 ){
							if (block[i][j+1].getFill(true,k) || block[i][j+2].getFill(true,k))
								for (int n = 1; n<=3; n++)
									block[i][j].setPos(block[i][

						}
						else if (j == 2)

						else

					}
					else if (i == 2){
						if (j == 1)

						else if (j == 2)

						else

					}
					else{
						if (j == 1)

						else if (j == 2)

						else

					}
				}
			}
		}
	}
}
void checkBox (void) {
	for (int i = 1; i<=3; i++){
		for (int j = 1; j <=3; j++){
			if (block[i][j].getEmptyB () == 1)
				block[i][j].setBox( ((block[i][j].getEmptyBoxB ()-1)/3)+1, ((block[i][j].getEmptyBoxB ()-1)%3)+1, block[i][j].getEmptyNumB() );
		}
	}
}

void checkRow (void) {
	for (int i=1; i<=9; i++){
		if (getEmptyR (i) == 1)
			block [((i-1)/3)+1] [((getEmptyBoxR(i)-1)/3)+1] .setBox( ((i-1)%3)+1, ((getEmptyBoxR(i)-1)%3)+1 ,getEmptyNumR (i));
	}
}
int getEmptyR (int a) {
	int count = 0;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <=3; j++) {
			if (!block [((a-1)/3)+1] [i] .getBox(((a-1)%3)+1, j))
				count ++;
		}
	}
	return count;
}
int getEmptyNumR (int a) {
	int nums[10];
	for (int i=1; i<=9; i++){
		nums[i] = i;
	}

	if (getEmptyR(a) == 1){
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <=3; j++) {
				if (block [((a-1)/3)+1] [i] .getBox(((a-1)%3)+1, j))
					nums[block [((a-1)/3)+1] [i] .getBox(((a-1)%3)+1, j)] = 0;
			}
		}
		for (int i = 1; i <= 9; i++) {
			if (nums[i])
				return i;
		}}
}
int getEmptyBoxR (int a) {
	if (getEmptyR(a) == 1){
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <=3; j++) {
				if (!block [((a-1)/3)+1] [i] .getBox(((a-1)%3)+1, j))
					return 3*(i-1)+j;
			}}}
}

void checkCol (void) {
	int boxC = getEmptyBoxC(5);
	int number = getEmptyNumC(5);

	for (int i=1; i<=9; i++){
		if (getEmptyC (i) == 1)
			block [((getEmptyBoxC(i)-1)/3)+1] [((i-1)/3)+1] .setBox( ((getEmptyBoxC(i)-1)%3)+1, ((i-1)%3)+1, getEmptyNumC (i));
	}
}
int getEmptyC (int a){
	int count = 0;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <=3; j++) {
			if (!block [i][((a-1)/3)+1]  .getBox(j, ((a-1)%3)+1))
				count ++;
		}
	}
	return count;
}
int getEmptyNumC (int a){
	int nums[10];
	for (int i=1; i<=9; i++){
		nums[i] = i;
	}

	if (getEmptyC(a) == 1){
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <=3; j++) {
				if (block [i] [((a-1)/3)+1] .getBox(j, ((a-1)%3)+1))
					nums[block [i] [((a-1)/3)+1] .getBox(j, ((a-1)%3)+1)] = 0;
			}
		}
		for (int i = 1; i <= 9; i++) {
			if (nums[i])
				return i;
		}}
}
int getEmptyBoxC (int a){
	if (getEmptyC(a) == 1){
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <=3; j++) {
				if (!block [i] [((a-1)/3)+1] .getBox(j, ((a-1)%3)+1))
					return 3*(i-1)+j;
			}}}
}

void checkLose (void) {
	int count = 0;
	for (int i = 1; i<=3; i++){
		for (int j = 1; j <=3; j++) {
			for (int k = 1; k<=3; k++){
				for (int l = 1; l <=3; l++) {
					if (block[i][j].getBox(k,l) > 9 || block[i][j].getBox(k,l) < 0)
						lose = true;
				}}}}
	/*for (int i = 1; i<=3; i++){
	for (int j = 1; j <=3; j++) {
	for (int k = 1; k<=3; k++){
	for (int l = 1; l <=3; l++) {
	if (!block[i][j].getBox(k,l))
	count++;
	}}}}
	if (count > 50)
	lose = true;*/
}
void checkWin (void) {
	int count = 0;

	for (int i = 1; i<=3; i++){
		for (int j = 1; j <=3; j++){
			for (int k = 1; k<=3; k++){
				for (int l = 1; l <=3; l++){
					if (!block[i][j].getBox(k,l))
						count ++;
				}}}}
	if (!count)
		win = true;
}
