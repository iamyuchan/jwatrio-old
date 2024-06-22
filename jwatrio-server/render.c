#include "render.h"
#include "text.h"

ConsoleRender* createRender(int x, int y, char** menuSelectText, int menuItems) {
    ConsoleRender* console = (ConsoleRender*)malloc(sizeof(ConsoleRender));

    if (console != NULL) {
        console->key = 0;
        console->menu = 0;
        console->x = x;
        console->y = y;
        console->renderCheck = 0;
        console->menuItems = menuItems;
        console->menuSelectText = (char**)malloc(menuItems * sizeof(char*));
        for (int i = 0; i < menuItems; i++) {
            console->menuSelectText[i] = (char*)malloc(500 * sizeof(char));
            strncpy_s(console->menuSelectText[i], 500, menuSelectText[i], 499);
            console->menuSelectText[i][499] = '\0';  // Null-terminate
        }

        console->movePos = movePos;
        console->setColor = setColor;
        console->start = start;
        console->renderMenu = renderMenu;
        console->menuKeyDetect = menuKeyDetect;
        console->getSelectedMenu = getSelectedMenu;
    }
    return console;
}


void start(ConsoleRender* console) {
    console->renderMenu(console);

    while (1) {
        int callbackCode = console->menuKeyDetect(console);
        if (callbackCode < 0) {
            break;
        }
    }
}

void renderMenu(ConsoleRender* console) {
    int selected = 0;
    for (int yPos = 7; yPos < 7 + console->menuItems; yPos++) {
        if (console->menu + 7 == yPos) {
            // �̸� ���õ� �޴��� ���
            console->setColor(CONSOLE_SELECTED);
            selected = 1;
        }
        console->movePos(console->x + 5, console->y + yPos); printf("%s", console->menuSelectText[yPos - 7]);
        if (selected) {
            console->setColor(CONSOLE_DEFAULT);
            selected = 0;
        }
    }
}

int menuKeyDetect(ConsoleRender* console) {
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            ch = _getch(); // ����Ű �Է�
            if (ch == 72) { // ���� ȭ��ǥ
                if (console->menu > 0) {
                    console->menu--;
                }
                console->renderMenu(console);
            }
            else if (ch == 80) { // �Ʒ��� ȭ��ǥ
                if (console->menu < console->menuItems - 1) {
                    console->menu++;
                }
                console->renderMenu(console);
            }
        }
        else if (ch == 13) { // Enter Ű
            console->renderCheck = 1; // �޴� ����
            return -1;
        }
    }
    return 0;
}

int getSelectedMenu(ConsoleRender* console) {
    return console->menu;
}
