#include "io_utils.h"
#include "System.h"
#include "Symbols.h"
#include "Functions.h"
using::cout;


int main() {
    std::string path = ".";
    std::vector<std::string> names;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().string().ends_with("screen")) {
            std::string temp = entry.path().string();
            temp.erase(0, 2);
            names.push_back(temp);
        }
    }
    std::sort(names.begin(), names.end());

    int choice = 0;
    while (choice != EXITGAME) {
        clear_screen();
        printMenu();
        choice = _getch();
        switch (choice) {
        case NEWGAME:
            handleNewGame(names);
            break;
        case SCREENUSER:
            handleScreenUser();
            break;
        case INSTRUCTIONS:
            clear_screen();
            printInstructions();
            _getch();
            clear_screen();
            break;
        case EXITGAME:
            clear_screen();
            std::cout << "Goodbye";
            break;
        default:
            clear_screen();
            break;
        }
    }

    return 0;
}





