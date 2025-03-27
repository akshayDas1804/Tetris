#include "user.h"
#include "leaderboard.h"
#include "game.h"
#include "headerfiles.h"


using namespace chrono;

void InitializeColors()
{
    if (has_colors())
    {
        start_color();

        // Initialize color pairs dynamically from `colours.h`
        vector<Colours> allColours = GetCellColours();
        for (size_t i = 0; i < allColours.size(); i++)
        {
            init_color(i + 1, allColours[i].r * 1000 / 255, allColours[i].g * 1000 / 255, allColours[i].b * 1000 / 255);
            init_pair(i + 1, i + 1, 0); // Set color pair ID
        }
    }
}

// Function to check if an event should be triggered
bool EventTriggered(milliseconds interval)
{
    static auto lastUpdateTime = steady_clock::now();
    auto currentTime = steady_clock::now();
    if (duration_cast<milliseconds>(currentTime - lastUpdateTime) >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

// Select difficulty with centered menu
int SelectDifficulty()
{
    int choice = 0;
    int termHeight, termWidth;
    getmaxyx(stdscr, termHeight, termWidth); // Get terminal size

    InitializeColors();
    while (true)
    {
        clear();

        int startRow = termHeight / 2 - 3; // Center vertically
        int startCol = termWidth / 2 - 10; // Center horizontally (approx.)

        attron(COLOR_PAIR(7));  
        move(startRow, startCol);
        printw("=============================");
        move(startRow + 1, startCol);
        printw("      SELECT DIFFICULTY    ");
        move(startRow + 2, startCol);
        printw("=============================");
        move(startRow + 4, startCol + 11);
        printw("1. EASY");
        move(startRow + 5, startCol + 11);
        printw("2. MEDIUM");
        move(startRow + 6, startCol + 11);
        printw("3. HARD");
        move(startRow + 8, startCol + 1);
        printw("Press 1, 2, or 3 to select.");
        attroff(COLOR_PAIR(7));  


        refresh();
        timeout(-1); // Block input until user selects
        int ch = getch();
        timeout(0); // Restore non-blocking input

        if (ch == '1')
            return 500; // Easy: Slowest speed (500ms)
        if (ch == '2')
            return 400; // Medium: Moderate speed (400ms)
        if (ch == '3')
            return 200; // Hard: Fastest speed (200ms)
    }
}

void mainMenu(Leaderboard &lb)
{
    int termHeight, termWidth;
    while (true)
    {
        clear();
        // InitializeColors();
        getmaxyx(stdscr, termHeight, termWidth);

        int startRow = termHeight / 2 - 5;
        int startCol = termWidth / 2 - 20;
        attron(COLOR_PAIR(7));  
        mvprintw(startRow, startCol, "===== MAIN MENU =====");
        mvprintw(startRow + 2, startCol, "1. Play Game (Existing User)");
        mvprintw(startRow + 3, startCol, "2. Display Existing Users");
        mvprintw(startRow + 4, startCol, "3. Create New User");
        mvprintw(startRow + 5, startCol, "4. Display Last 5 Scores of All Users");
        mvprintw(startRow + 6, startCol, "5. Display Leaderboard");
        mvprintw(startRow + 7, startCol, "6. Exit");
        mvprintw(startRow + 9, startCol, "Select an option: ");
        attroff(COLOR_PAIR(7));  
        refresh();

        int choice = getch();

        switch (choice)
        {
        case '1':
        {
            if (lb.usersEmpty())
            {
                clear();
                // InitializeColors();
                mvprintw(termHeight / 2, termWidth / 2 - 15, "No users exist. Please create a user first.");
                mvprintw(termHeight / 2 + 1, termWidth / 2 - 15, "Press any key...");
                getch();
                break;
            }
            echo();
            char name[50];
            clear();
            mvprintw(termHeight / 2, termWidth / 2 - 15, "Enter username: ");
            getstr(name);
            noecho();
            User *user = lb.findUser(name);
            if (user == nullptr)
            {
                mvprintw(termHeight / 2 + 2, termWidth / 2 - 15, "User '%s' does not exist. Press any key...", name);
                getch();
            }
            else
            {
                bool playAgain = true;
                while (playAgain)
                {
                    int speed = SelectDifficulty();
                    Game game(speed, &lb, name);
                    while (!game.gameOver)
                    {
                        game.HandleInput();
                        if (EventTriggered(game.dropSpeed))
                        {
                            game.MoveBlockDown();
                        }
                        if (game.gameOver)
                            break;
                        clear();
                        game.Draw();
                        refresh();
                        this_thread::sleep_for(milliseconds(50));
                    }
                    lb.addScore(name, game.getScore());

                    nodelay(stdscr, FALSE);
                    flushinp();

                    clear();
                    mvprintw(termHeight / 2, termWidth / 2 - 15, "Play again with same username? (y/n): ");
                    // InitializeColors();
                    // refresh();
                    int again = getch();
                    playAgain = (again == 'y' || again == 'Y');
                }
            }
            break;
        }

        case '2':
            clear();
            lb.displayAllUsers();
            mvprintw(termHeight - 2, termWidth / 2 - 15, "Press any key to return...");
            refresh();
            getch();
            break;

        case '3':
        {
            echo();
            char newName[50];
            clear();
            mvprintw(termHeight / 2, termWidth / 2 - 15, "Enter new username: ");
            getstr(newName);
            noecho();
            if (lb.findUser(newName) != nullptr)
                mvprintw(termHeight / 2 + 2, termWidth / 2 - 15, "Username already exists!");
            else
            {
                lb.createUser(newName);
                mvprintw(termHeight / 2 + 2, termWidth / 2 - 15, "User created successfully!");
            }
            mvprintw(termHeight - 2 , termWidth / 2 - 15, "Press any key to return...");
            getch();
            break;
        }

        case '4':
            clear();
            lb.displayLastFiveScoresAllUsers();
            mvprintw(termHeight - 2, termWidth / 2 - 15, "Press any key to return...");
            refresh();
            getch();
            break;

        case '5':
            clear();
            lb.displayLeaderboard();
            mvprintw(termHeight - 2, termWidth / 2 - 15, "Press any key to return...");
            refresh();
            getch();
            break;

        case '6':
            return;

        default:
            mvprintw(termHeight - 2, termWidth / 2 - 15, "Invalid option. Press any key to return...");
            refresh();
            getch();
        }
    }
}


int main()
{   
    srand(time(0));
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    InitializeColors();

    Leaderboard lb;
    lb.loadFromFile("users.csv");

    mainMenu(lb);

    lb.saveToFile("users.csv");
    lb.saveLeaderboardToFile("leaderboard.csv");

    curs_set(1);
    endwin();

    return 0;
}