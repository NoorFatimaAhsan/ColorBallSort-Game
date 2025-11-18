//CT-24052 NOOR FATIMA AHSAN
//CT-24054 EMAN ANJUM FAIZ
//CT-24098 AYESHA RAUF

//-----------------------------COLOR BALL SORT GAME-----------------------------------
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
#include<chrono>
#include <random>

using namespace sf;
using namespace std;

struct Tube {
    stack<Color> balls;
    RectangleShape shape;
    Vector2f position;
};

struct Player {
    string name;
    int moves;
    int timeSec; 
    bool won;
};

bool compare(const Player& a, const Player& b) {
    if (a.won != b.won)
        return a.won < b.won; 
    if (a.moves != b.moves)
        return a.moves > b.moves; 

    return a.timeSec > b.timeSec; 
}
void heapifyDownMin(vector<Player>& heap, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(heap[left], heap[smallest]))
        smallest = left;
    if (right < n&& compare(heap[right], heap[smallest]))
        smallest = right;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyDownMin(heap, n, smallest);
    }
}
void heapSort(vector<Player>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyDownMin(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyDownMin(arr, i, 0);
    }
}

bool isSorted(const Tube& tube, int ballsPerTube) {
    if (tube.balls.empty()) 
        return true;
    stack<Color> temp = tube.balls;
    Color top = temp.top();
    int count = 0;
    while (!temp.empty()) {
        if (temp.top() != top)
            return false;
        temp.pop();
        count++;
    }
    return count == ballsPerTube;
}

bool checkWin(const vector<Tube>& tubes, int ballsPerTube) {
    for (int i=0;i<tubes.size();i++)
        if (!isSorted(tubes[i], ballsPerTube))
            return false;
    return true;
}

void saveLeaderboard(const vector<Player>& leaderboard, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file for saving leaderboard.\n";
        return;
    }

    for (int i = 0; i < leaderboard.size(); ++i) {
        file << leaderboard[i].name << " "
            << leaderboard[i].moves << " "
            << leaderboard[i].timeSec << " "
            << leaderboard[i].won << "\n";
    }
    file.close();
}
void loadLeaderboard(vector<Player>& leaderboard, const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
        return; 

    leaderboard.clear();
    Player p;
    while (file >> p.name >> p.moves >> p.timeSec >> p.won) {
        leaderboard.push_back(p);
    }
    file.close();
}

int main() {
    RenderWindow window(VideoMode(900, 500), "Water Sort Puzzle");
    window.setFramerateLimit(60);

    vector<Player> leaderboard;
    loadLeaderboard(leaderboard, "colorballsort.txt"); 

    string playerName = "";
    bool isEnteringName = false;
    bool showWelcome = true;
    bool showMenu = false;
    bool showGame = false;
    bool showLeaderboard = false;

    Clock welcomeClock;
    float welcomeDuration = 5.f; 

    Music welcomegame;
    if (!welcomegame.openFromFile("C:/Users/Computer World/Desktop/sfmlcheck/pics/gamemusic-163649.mp3"))
    {
        cout << "cannot open music file" << endl;
    }
    welcomegame.setPitch(2);
    welcomegame.setVolume(50);
    welcomegame.play();

    Music ball;
    if (!ball.openFromFile("C:/Users/Computer World/Desktop/sfmlcheck/pics/tennis-ball-hit-151257.mp3"))
    {
        cout << "cannot open music file" << endl;
    }
    ball.setPitch(2);
    ball.setVolume(50);

    RectangleShape welcomeBackground(Vector2f(900, 500));
    Texture wb;
    if (wb.loadFromFile("C:/Users/Computer World/Desktop/sfmlcheck/pics/back.png"))
        welcomeBackground.setTexture(&wb);

    RectangleShape menuBackground(Vector2f(900, 500));
    Texture mb;
    if (mb.loadFromFile("C:/Users/Computer World/Desktop/sfmlcheck/pics/themeblue.png"))
        menuBackground.setTexture(&mb);

    RectangleShape gameBackground(Vector2f(900, 500));
    Texture gb;
    if (gb.loadFromFile("C:/Users/Computer World/Desktop/sfmlcheck/pics/themeblue.png"))
        gameBackground.setTexture(&gb);

    RectangleShape leaderboardBackground(Vector2f(900, 500));
    Texture lb;
    if (lb.loadFromFile("C:/Users/Computer World/Desktop/sfmlcheck/pics/themeblue.png"))
        leaderboardBackground.setTexture(&lb);

    Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
        cout << "Error loading font!\n";

    RectangleShape playButton(Vector2f(200, 50));
    playButton.setPosition(350, 150);
    playButton.setFillColor(Color::Transparent);
    playButton.setOutlineColor(Color::White);
    playButton.setOutlineThickness(2.f);

    RectangleShape leaderboardButton(Vector2f(200, 50));
    leaderboardButton.setPosition(350, 250);
    leaderboardButton.setFillColor(Color::Transparent);
    leaderboardButton.setOutlineColor(Color::White);
    leaderboardButton.setOutlineThickness(2.f);

    RectangleShape exitButton(Vector2f(200, 50));
    exitButton.setPosition(350, 350);
    exitButton.setFillColor(Color::Transparent);
    exitButton.setOutlineColor(Color::White);
    exitButton.setOutlineThickness(2.f);

    RectangleShape exitLeaderBoardButton(Vector2f(100, 50));
    exitLeaderBoardButton.setPosition(600, 25);
    exitLeaderBoardButton.setFillColor(Color::Transparent);
    exitLeaderBoardButton.setOutlineColor(Color::White);
    exitLeaderBoardButton.setOutlineThickness(2.f);

    Text playText("Play", font, 24);
    playText.setFillColor(Color::White);
    playText.setPosition(430, 160);


    Text leaderboardText("Leaderboard", font, 24);
    leaderboardText.setFillColor(Color::White);
    leaderboardText.setPosition(390, 260);

    Text exitText("Exit", font, 24);
    exitText.setFillColor(Color::White);
    exitText.setPosition(430, 360);

    Text exitLeaderBoardText("Exit", font, 24);
    exitLeaderBoardText.setFillColor(Color::White);
    exitLeaderBoardText.setPosition(625, 27.5);

    const int colorCount = 4;
    const int tubesCount = colorCount + 1;
    const int maxMoves = 25;
    const int ballsPerTube = 4;
    const float tubeWidth = 80.f;
    const float tubeHeight = 245.f;
    const float ballRadius = 25.f;
    const float spacing = 10.f;
    string inputError = "";

    vector<Color> COLORS = { Color::Red, Color::Yellow, Color::Magenta, Color::Cyan };
    vector<Color> allBalls;

    for (int i = 0; i < colorCount; ++i)
        for (int j = 0; j < ballsPerTube; ++j)
            allBalls.push_back(COLORS[i]);
    shuffle(allBalls.begin(), allBalls.end(), random_device{});

    vector<Tube> tubes(tubesCount);
    float startX = 120.f, gap = 150.f, yCenter = 300.f;

    for (int i = 0; i < tubesCount; ++i) {
        tubes[i].position = { startX + i * gap, yCenter };
        tubes[i].shape.setSize({ tubeWidth, tubeHeight });
        tubes[i].shape.setOrigin(tubeWidth / 2.f, tubeHeight / 2.f);
        tubes[i].shape.setPosition(tubes[i].position);
        tubes[i].shape.setFillColor(Color::Transparent);
        tubes[i].shape.setOutlineColor(Color::White);
        tubes[i].shape.setOutlineThickness(2.f);
    }

    int idx = 0; 
    for (int t = 0; t < colorCount; ++t)
        for (int b = 0; b < ballsPerTube; ++b)
            tubes[t].balls.push(allBalls[idx++]);

    int selectedTube = -1;
    int moveCount = 0;
    Clock gameClock;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

            if (showMenu && !isEnteringName && event.type == Event::MouseButtonPressed ) {
                if (playButton.getGlobalBounds().contains(mousePos)) {
                    isEnteringName = true;
                }
                else if (leaderboardButton.getGlobalBounds().contains(mousePos)) {
                    showMenu = false;
                    showLeaderboard = true;
                }
                else if (exitButton.getGlobalBounds().contains(mousePos)) {
                    window.close();
                }
            }
            if (isEnteringName && event.type == Event::TextEntered)
            {
                inputError = "";
                if (event.text.unicode == 8) { 
                    if (!playerName.empty()) 
                        playerName.pop_back();
                }
                else if (event.text.unicode == 13) {
                    if (!playerName.empty()) {
                        isEnteringName = false;
                        showMenu = false;
                        showGame = true;
                        moveCount = 0;
                        gameClock.restart();
                    }
                    else {
                        inputError = "Name cannot be empty!";
                    }
                }
                else if (
                    (event.text.unicode >= 'a' && event.text.unicode <= 'z') ||
                    (event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
                    event.text.unicode == ' '
                    )
                {
                    if (playerName.length() < 10) {
                        playerName += static_cast<char>(event.text.unicode);
                    }
                    else {
                        inputError = "Name cannot exceed 10 characters!";
                    }
                }
                else {
                    inputError = "Invalid character! Use A-Z or a-z only.";
                }
            }
            if (showGame && event.type == Event::MouseButtonPressed) { 
                for (int i = 0; i < tubesCount; ++i) {
                    if (tubes[i].shape.getGlobalBounds().contains(mousePos)) {
                        if (selectedTube == -1 && !tubes[i].balls.empty()) {
                            selectedTube = i;
                            tubes[i].shape.setOutlineColor(Color::Yellow);
                        }
                        else if (selectedTube != i ) {
                            if (!tubes[selectedTube].balls.empty() && tubes[i].balls.size() < ballsPerTube) {
                                Color c = tubes[selectedTube].balls.top();
                                tubes[selectedTube].balls.pop();
                                tubes[i].balls.push(c);
                                ball.play();
                                moveCount++;

                            }
                            tubes[selectedTube].shape.setOutlineColor(Color::White);
                            selectedTube = -1;
                        }
                    }
                }
            }
            if (showLeaderboard && event.type == Event::MouseButtonPressed ) {
                if (exitLeaderBoardButton.getGlobalBounds().contains(mousePos)) {
                    showLeaderboard = false;
                    showMenu = true;
                }
            }
      
    }

        if (showWelcome && welcomeClock.getElapsedTime().asSeconds() > welcomeDuration) {
            showWelcome = false;
            showMenu = true;
        }
    
        window.clear();


        if (showWelcome) {
            window.draw(welcomeBackground);
        }
        else if (showMenu) {
            window.draw(menuBackground);
            window.draw(playButton);
            window.draw(playText);
            window.draw(leaderboardButton);
            window.draw(leaderboardText);
            window.draw(exitButton);
            window.draw(exitText);
            if (isEnteringName) {
                Text namePrompt("Enter Name: " + playerName, font, 24);
                namePrompt.setFillColor(Color::White);
                namePrompt.setPosition(300, 70);
                window.draw(namePrompt);

                if (!inputError.empty()) {
                    Text err(inputError, font, 22);
                    err.setFillColor(Color::Red);
                    err.setPosition(300, 100);
                    window.draw(err);
                }
            }

        }
        else if (showGame) {
            window.draw(gameBackground);
            for (int i = 0; i < tubesCount; ++i) {
                window.draw(tubes[i].shape);

                stack<Color> temp = tubes[i].balls; 
                vector<Color> drawOrder;

                while (!temp.empty()) {
                    drawOrder.push_back(temp.top());
                    temp.pop();
                }

                for (int j = drawOrder.size() - 1; j >= 0; --j) {
                    CircleShape ball(ballRadius);
                    ball.setFillColor(drawOrder[j]);
                    ball.setOutlineColor(Color::Black);
                    ball.setOutlineThickness(1);
                    float x = tubes[i].position.x - ballRadius;
                    float y = tubes[i].position.y + (tubeHeight / 2.f)
                        - (((drawOrder.size() - j)) * (2 * ballRadius + spacing));
                    ball.setPosition(x, y);   
                    window.draw(ball);
                }
            }

            Text timerText;
            Text moveText;

            timerText.setFont(font);
            moveText.setFont(font);

            timerText.setCharacterSize(25);
            moveText.setCharacterSize(25);

            timerText.setFillColor(Color::White);
            moveText.setFillColor(Color::White);

            int elapsedSec = gameClock.getElapsedTime().asSeconds();
            string timeText = "Time: " + to_string(elapsedSec) + " s";
            string moveCountText = "Moves: " + to_string(moveCount) + "/" + to_string(maxMoves);

            timerText.setString(timeText);
            moveText.setString(moveCountText);

            timerText.setPosition(10, 10);
            moveText.setPosition(10, 40);

            window.draw(timerText);
            window.draw(moveText);

            bool won = checkWin(tubes, ballsPerTube);
            if ( won || moveCount >= maxMoves) {
                Player p;
                    p.name = playerName;
                    p.moves = moveCount;
                    p.timeSec = elapsedSec; 
                    p.won = won;
                    leaderboard.push_back(p);
                    saveLeaderboard(leaderboard, "colorballsort.txt");
                

                RenderWindow resultWin(VideoMode(900, 500), "Result");
                RectangleShape resultBg(Vector2f(900,500));
                Texture WinT;
                Texture LossT;

                Music win;
                if (!win.openFromFile("C:/Users/Computer World/Desktop/sfmlcheck/pics/winner-game-sound-404167.mp3"))
                {
                    cout << "cannot open music file" << endl;
                }
                win.setPitch(2);
                win.setVolume(50);

                Music lose;
                if (!lose.openFromFile("C:/Users/Computer World/Desktop/sfmlcheck/pics/winlose.mp3"))
                {
                    cout << "cannot open music file" << endl;
                }
                lose.setPitch(2);
                lose.setVolume(50);

                if (won) {
                    if (WinT.loadFromFile("C:/Users/Computer World/Desktop/sfmlcheck/pics/youwin.png"))
                        resultBg.setTexture(&WinT);
                        win.play();
                }
                else {
                    if (LossT.loadFromFile("C:/Users/Computer World/Desktop/sfmlcheck/pics/lose(5).png"))
                        resultBg.setTexture(&LossT);
                        lose.play();
                }
                    

                Clock resClock;
                while (resClock.getElapsedTime().asSeconds() < 2.f) {
                    Event revent;
                    while (resultWin.pollEvent(revent)) {
                        if (revent.type == Event::Closed)
                            resultWin.close();
                    }
                    resultWin.clear();
                    resultWin.draw(resultBg);
                    resultWin.display();
                }

                shuffle(allBalls.begin(), allBalls.end(), random_device{});
                for (int t = 0; t < tubesCount; ++t) {
                    while (!tubes[t].balls.empty())
                        tubes[t].balls.pop();
                }

                int idx = 0;
                for (int t = 0; t < colorCount; ++t) {
                    for (int b = 0; b < ballsPerTube; ++b) {
                        tubes[t].balls.push(allBalls[idx++]);
                    }
                }
                moveCount = 0;
                gameClock.restart();
                showGame = false;
                showMenu = true;
                playerName = "";
            }
        }
        else if (showLeaderboard) {
            window.draw(leaderboardBackground);
            window.draw(exitLeaderBoardButton);
            window.draw(exitLeaderBoardText);

            vector<Player> sortedPlayers = leaderboard; 
            heapSort(sortedPlayers);

            Text title("Leaderboard", font, 30);
            title.setFillColor(Color::White);
            title.setPosition(180, 10);
            window.draw(title);

            int y = 70;

            for (int i = 0; i < (int)sortedPlayers.size(); i++) {
                Player p = sortedPlayers[i];

                string record = p.name + " | Moves: " + to_string(p.moves)
                    + " | Time: " + to_string(p.timeSec)
                    + " | " + (p.won ? "Won" : "Lost");

                Text line(record, font, 22);
                line.setFillColor(Color::White);
                line.setPosition(50, (float)y); 

                window.draw(line);
                y += 35; 
            }
        }
        window.display();
    }
    return 0;

}
