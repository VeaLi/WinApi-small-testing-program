#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for random seed
#include <fstream> // for saving user score
#include <iostream>





#define ID_BUTTON_1 3000
#define ID_BUTTON_2 3001
#define ID_BUTTON_3 3002
#define ID_BUTTON_4 3003
#define ID_BUTTON_n 3004
#define ID_BUTTON_q 3005
#define ID_QUIT 3006
#define ID_ONLY 3007
#define ID_ONLY_RETURN 3008

#define ID_LINE 3009

#define ID_MORNING 4001
#define ID_DAY 4002
#define ID_EVENING 4003

#define ID_OVERALL 4004
#define ID_SCORE 4005


HWND hBtn1;
HWND hBtn2;
HWND hBtn3;
HWND hBtn4;
HWND hBtnn;
HWND hBtnq;
HWND line;
HWND overall;
HWND score;

using namespace std;

LRESULT CALLBACK WndProc ( HWND, UINT, UINT, LONG );
int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR IpszCmdParam, int nCmdShow )
{
    HWND hWnd ;
    WNDCLASS WndClass;
    MSG Msg;
    char szClassName[] = "Georgian";
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance ;
    WndClass.hIcon = (HICON)LoadImage(NULL, TEXT("icon.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    WndClass.hCursor = LoadCursor (NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);

    WndClass.lpszClassName = szClassName;
    if (!RegisterClass(&WndClass))
    {
        MessageBox(NULL, "Cannot register class", "Error", MB_OK);
        return 0;
    }
    hWnd = CreateWindow(szClassName, "Georgian A1",
                        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        1000, 600,
                        NULL, NULL,
                        hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, "Cannot create window", "Error", MB_OK);
        return 0;
    }
    //using | BS_BITMAP
    hBtn1 = CreateWindow("BUTTON", "One", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 100, 30, 220, 220, hWnd, (HMENU)ID_BUTTON_1, hInstance, NULL);
    hBtn2 = CreateWindow("BUTTON", "Two", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 100, 290, 220, 220, hWnd, (HMENU)ID_BUTTON_2, hInstance, NULL);
    hBtn3 = CreateWindow("BUTTON", "Three", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 350, 30, 220, 220, hWnd, (HMENU)ID_BUTTON_3, hInstance, NULL);
    hBtn4 = CreateWindow("BUTTON", "Four", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_BITMAP, 350, 290, 220, 220, hWnd, (HMENU)ID_BUTTON_4, hInstance, NULL);

    hBtnn = CreateWindow("BUTTON", "Next", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 710, 310, 120, 20, hWnd, (HMENU)ID_BUTTON_n, hInstance, NULL);
    //static-control-styles
    hBtnq = CreateWindow("STATIC", "TEXT", BS_TEXT | WS_VISIBLE | WS_CHILD | SS_CENTER, 710, 240, 120, 20, hWnd, (HMENU)ID_BUTTON_q, hInstance, NULL);
    line = CreateWindow("STATIC", "TEXT", BS_TEXT | WS_VISIBLE | WS_CHILD | SS_CENTER | SS_BLACKRECT, 710, 260, 120, 4, hWnd, (HMENU)ID_LINE, hInstance, NULL);

    overall = CreateWindow("STATIC", "Overall score:", BS_TEXT | WS_VISIBLE | WS_CHILD | SS_CENTER, 880, 0, 120, 20, hWnd, (HMENU)ID_BUTTON_q, hInstance, NULL);
    score = CreateWindow("STATIC", "0", BS_TEXT | WS_VISIBLE | WS_CHILD | SS_CENTER, 880, 20, 120, 20, hWnd, (HMENU)ID_BUTTON_q, hInstance, NULL);





    /* Show window */
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    /* Beginning of messages cycle */
    while (GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}







//can read from file, but noo
char ITEMS[15][30] = { "src/boy.bmp", "src/girl.bmp", "src/cat.bmp", "src/dog.bmp", "src/fish.bmp", "src/book.bmp", "src/water.bmp", "src/bird.bmp", "src/rain.bmp", "src/tea.bmp", "src/tree.bmp", "src/coffee.bmp", "src/sun.bmp", "src/computer.bmp", "src/flower.bmp"};
char NAMES[15][30] = { "bich’i (boy)", "gogo (girl)", "k’at’a (cat)", "dzaghli (dog)", "tevzi (fish)", "ts’igni (book)", "ts’q’ali (water)", "prinveli (bird)", "ts’vima (rain)", "chai (tea)", "khe (tree)", "q’ava (coffee)", "mze (sun)", "k’omp’iut’eri", "q’vavili (flower)"};
char NAMESO[15][30] = { "bich’i", "gogo", "k’at’a", "dzaghli", "tevzi", "ts’igni", "ts’q’ali", "prinveli", "ts’vima", "chai", "khe", "q’ava", "mze", "k’omp’iut’eri", "q’vavili"};
int NOW[4] = {0, 0, 0, 0};
int CORRECT = -1;
int MODE = 1;
int NN = 15; //size of items
HMENU* ptr; // this is for updating radio buttons
UINT CURRENT = ID_EVENING; // this is for updating radio buttons globally
int SCORE = 0;



void update_score() {
    fstream file;
    file.open("score.txt", ios_base::out);
    char str[10];
    sprintf(str, "%d", SCORE);
    file << str;
    file.close();

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT Message,
                         UINT wParam, LONG IParam )
{
    HDC hDC, hCompatibleDC;
    PAINTSTRUCT PaintStruct;
    HANDLE hOldBitmap;
    HANDLE hBitmap;
    RECT Rect;
    BITMAP Bitmap;
    HMENU hMenubar;
    HMENU hMenu, hMenu_2, hMenu_0;




    switch (Message)
    {


    case WM_PAINT:
    {
        printf("painting\n");
        //background first layer
        hDC = BeginPaint(hWnd, &PaintStruct);
        hBitmap = (HBITMAP)LoadImage(NULL, "src/tbilisi_2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
        hCompatibleDC = CreateCompatibleDC(hDC);
        hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
        GetClientRect(hWnd, &Rect);
        StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
        SelectObject(hCompatibleDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hCompatibleDC);

        //background second layer options
        if (CURRENT == 4001)
        {
            hBitmap = (HBITMAP)LoadImage(NULL, "src/tbilisi_2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        }
        if (CURRENT == 4002)
        {
            hBitmap = (HBITMAP)LoadImage(NULL, "src/river.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        }
        if (CURRENT == 4003)
        {
            hBitmap = (HBITMAP)LoadImage(NULL, "src/evening.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        }
        GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
        hCompatibleDC = CreateCompatibleDC(hDC);
        hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
        GetClientRect(hWnd, &Rect);
        BitBlt(hDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hCompatibleDC, 0, 0, SRCCOPY);
        SelectObject(hCompatibleDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hCompatibleDC);

        EndPaint(hWnd, &PaintStruct);

        //I have found out that WM_PAINT HAS HIGHT PRIORITY -> so first set of cards is initialized here
        int I0 = NOW[0];
        char* item = ITEMS[I0];
        HBITMAP hBitmap1 = (HBITMAP) LoadImage (NULL, item, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
        SendMessage (hBtn1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);

        int I1 = NOW[1];
        char* item2 = ITEMS[I1];
        HBITMAP hBitmap2 = (HBITMAP) LoadImage (NULL, item2, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
        SendMessage (hBtn2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);

        int I2 = NOW[2];
        char* item3 = ITEMS[I2];
        HBITMAP hBitmap3 = (HBITMAP) LoadImage (NULL, item3, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
        SendMessage (hBtn3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap3);

        int I3 = NOW[3];
        char* item4 = ITEMS[I3];
        HBITMAP hBitmap4 = (HBITMAP) LoadImage (NULL, item4, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
        SendMessage (hBtn4, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap4);

        int Ind = rand() % 4;
        CORRECT = NOW[Ind];

        char* item5;
        if (MODE == 1)
        {
            item5 = NAMES[CORRECT];
        }
        else
        {
            item5 = NAMESO[CORRECT];
        }

        SetWindowText(hBtnq, item5);

        char str[10];
        sprintf(str, "%d", SCORE);
        SetWindowText(score, str);


        return 0;

    }
    case WM_DESTROY:
        PostQuitMessage(0);

    case WM_COMMAND:
        switch (wParam)
        {

        case ID_BUTTON_1:
        {
            int I = NOW[0];
            if (I == CORRECT)
            {
                HBITMAP hBitmap1 = (HBITMAP) LoadImage (NULL, "src/aye.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
                SendMessage (hBtn1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);

                SCORE += 1;
                char str[10];
                sprintf(str, "%d", SCORE);
                SetWindowText(score, str);

                //well this function will update the score
                update_score();
            }
            else
            {
                HBITMAP hBitmap1 = (HBITMAP) LoadImage (NULL, "src/nea.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
                SendMessage (hBtn1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);

                SCORE -= 1;
                char str[10];
                sprintf(str, "%d", SCORE);
                SetWindowText(score, str);

                update_score();
            }
            break;
        }

        case ID_BUTTON_2:
        {
            int I = NOW[1];
            if (I == CORRECT)
            {
                HBITMAP hBitmap2 = (HBITMAP) LoadImage (NULL, "src/aye.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
                SendMessage (hBtn2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);

                SCORE += 1;
                char str[10];
                sprintf(str, "%d", SCORE);
                SetWindowText(score, str);

                update_score();

            }
            else
            {
                HBITMAP hBitmap2 = (HBITMAP) LoadImage (NULL, "src/nea.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
                SendMessage (hBtn2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);

                SCORE -= 1;
                char str[10];
                sprintf(str, "%d", SCORE);
                SetWindowText(score, str);

                update_score();
            }
            break;
        }
        case ID_BUTTON_3:
        {
            int I = NOW[2];
            if (I == CORRECT)
            {
                HBITMAP hBitmap3 = (HBITMAP) LoadImage (NULL, "src/aye.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
                SendMessage (hBtn3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap3);

                SCORE += 1;
                char str[10];
                sprintf(str, "%d", SCORE);
                SetWindowText(score, str);

                update_score();
            }
            else
            {
                HBITMAP hBitmap3 = (HBITMAP) LoadImage (NULL, "src/nea.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
                SendMessage (hBtn3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap3);

                SCORE -= 1;
                char str[10];
                sprintf(str, "%d", SCORE);
                SetWindowText(score, str);

                update_score();
            }
            break;
        }
        case ID_BUTTON_4:
        {
            int I = NOW[3];
            if (I == CORRECT)
            {
                HBITMAP hBitmap4 = (HBITMAP) LoadImage (NULL, "src/aye.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
                SendMessage (hBtn4, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap4);

                SCORE += 1;
                char str[10];
                sprintf(str, "%d", SCORE);
                SetWindowText(score, str);

                update_score();
            }
            else
            {
                HBITMAP hBitmap4 = (HBITMAP) LoadImage (NULL, "src/nea.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
                SendMessage (hBtn4, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap4);

                SCORE -= 1;
                char str[10];
                sprintf(str, "%d", SCORE);
                SetWindowText(score, str);

                update_score();
            }
            break;
        }
        case ID_BUTTON_n:
        {
            srand(time(NULL));// new seed
            int Ind = rand() % NN;
            NOW[0] = Ind;
            Ind = rand() % NN;
            NOW[1] = Ind;
            Ind = rand() % NN;
            NOW[2] = Ind;
            Ind = rand() % NN;
            NOW[3] = Ind;


            int I0 = NOW[0];
            char* item1 = ITEMS[I0];
            HBITMAP hBitmap1 = (HBITMAP) LoadImage (NULL, item1, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
            SendMessage (hBtn1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);

            int I1 = NOW[1];
            char* item2 = ITEMS[I1];
            HBITMAP hBitmap2 = (HBITMAP) LoadImage (NULL, item2, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
            SendMessage (hBtn2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);

            int I2 = NOW[2];
            char* item3 = ITEMS[I2];
            HBITMAP hBitmap3 = (HBITMAP) LoadImage (NULL, item3, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
            SendMessage (hBtn3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap3);

            int I3 = NOW[3];
            char* item4 = ITEMS[I3];
            printf(item4);
            HBITMAP hBitmap4 = (HBITMAP) LoadImage (NULL, item4, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
            SendMessage (hBtn4, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap4);

            srand(time(NULL));// new seed
            Ind = rand() % 4; // 4 buttons
            CORRECT = NOW[Ind];

            // menu options handled
            char* item5;
            if (MODE == 1)
            {
                item5 = NAMES[CORRECT];
            }
            else
            {
                item5 = NAMESO[CORRECT];
            }
            SetWindowText(hBtnq, item5);
            break;
        }
        case ID_QUIT:
        {

            SendMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        }
        case ID_ONLY:
        {
            MODE = 2;
            char* item5 = NAMESO[CORRECT];
            SetWindowText(hBtnq, item5);
            break;
        }
        case ID_ONLY_RETURN:
        {
            MODE = 1;
            char* item5 = NAMES[CORRECT];
            SetWindowText(hBtnq, item5);
            break;
        }
        case ID_MORNING:

        {
            // getsubmenu was not working
            //printf("!!!!!!!!!!!!!!!!!!!!!!!!");
            //hMenu = GetMenu(hWnd);
            //int cnt = GetMenuItemCount(hMenu);
            //printf("%d\n",cnt);

            CURRENT = ID_MORNING;

            //well i need to redraw the background -> i need to provoke wm_painy
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

            break;

        }
        case ID_DAY:
        {
            CURRENT = ID_DAY;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        }
        case ID_EVENING:
        {
            CURRENT = ID_EVENING;
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;

        }

        }


    // closes on escape
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            SendMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        }

    // has the highest priority
    case WM_CREATE:

    {
        //AddMenus(hWnd);
        printf("updating\n");

        hMenubar = CreateMenu();

        hMenu_0 = CreateMenu();
        AppendMenuW(hMenu_0, MF_STRING, ID_QUIT, L"&Quit");
        AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu_0, L"&File");

        hMenu = CreateMenu();
        AppendMenuW(hMenu, MF_STRING, ID_ONLY, L"&Georgian only");
        AppendMenuW(hMenu, MF_STRING, ID_ONLY_RETURN, L"&With translation");
        AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&Options");

        hMenu_2 = CreateMenu();
        AppendMenuW(hMenu_2, MF_STRING, ID_MORNING, L"&Morning");
        AppendMenuW(hMenu_2, MF_STRING, ID_DAY, L"&Day");
        AppendMenuW(hMenu_2, MF_STRING, ID_EVENING, L"&Evening");
        ptr = &hMenu_2;// is working here but not in wm_command

        CheckMenuRadioItem(*ptr, ID_MORNING, ID_EVENING, CURRENT, MF_BYCOMMAND);

        AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu_2, L"&Background");

        SetMenu(hWnd, hMenubar);


        if (CORRECT == -1)

        {
            fstream file;
            file.open("score.txt", ios::in);
            file >> SCORE;
            printf("%d\n", SCORE);
            file.close();

            int msgboxID = MessageBox(NULL, "Find the right image for the word\nYour score will be saved when you close the program. Press Ok to start", "Welcome", MB_OKCANCEL);
            switch (msgboxID)
            {
            case IDCANCEL:// you check msdn for more cases
                SendMessage(hWnd, WM_CLOSE, 0, 0);
                break;

            case IDOK:
                // create first set of cards
                srand(time(NULL));// new seed
                int Ind = rand() % NN;
                NOW[0] = Ind;
                Ind = rand() % NN;
                NOW[1] = Ind;
                Ind = rand() % NN;
                NOW[2] = Ind;
                Ind = rand() % NN;
                NOW[3] = Ind;

                break;
            }
            break;
        }
        return 0;
    }
    return 0;
    }
    return DefWindowProc(hWnd, Message, wParam, IParam);
}




