
Color Ball Sort Puzzle  
 Data Structures and Algorithms Based Implementation 
 
1. Introduction 
The Color Ball Sort Puzzle Game is a logic-based puzzle where the player organizes colored balls 
into tubes so that each tube contains balls of only one color. The game tests problem-solving 
skills, planning, and algorithmic thinking. The project uses C++ along with SFML for graphics and 
audio. Although it has a graphical interface, the primary focus of the project is the use of Data 
Structures & Algorithms to efficiently manage game logic, sorting, leaderboard ranking, and 
gameplay interaction. 
 
2. Project Overview 
The game consists of: 
• Welcome screen 
• Main menu 
• Gameplay screen (Ball sorting) 
• Leaderboard with ranking using Heap Sort 
• Win/Lose result screen 
The player is allowed a limited number of moves to sort the balls. There is also a timer which 
tracks the time you spent playing the game. 
 
3. Data Structures Used & Justification
Stack  
    For Tube Representation 
        Each tube uses: 
        stack<Color> balls; 
    Usage: 
        • The game allows removing only the top ball. 
        • A ball can be placed only on top of the destination tube. 
        • Tubes behave like vertical containers which is exactly a LIFO structure. 
        • Constant time operations. 
    We didn’t use any other data structure because :  
        • Vector allows random indexing which is unrealistic for tubes. 
        • Queue is FIFO which is opposite of tube behavior. 
        • Stack is naturally restrictive so no illegal operations possible. As the tube behaves 
        exactly like a stack, we used stack. 
    Time Complexity: 
        • push(): O(1) 
        • pop(): O(1) 
        • top(): O(1) 
 
Vector  
    Vector is one of the most widely used structures in this project due to its flexibility, dynamic 
    size, and fast random access. We use it in several core components of the game. 

    1. All Balls Storage: 
        Before the balls are distributed into tubes, they are stored in: 
        vector<Color> allBalls; 
    This vector allows: 
        • easy appending of colors 
        • fast shuffle using shuffle() 
        • sequential pushing into tube stacks 
    Choosing a vector here is ideal because we can: 
        • store a variable number of balls 
        • shuffle them easily 
        • access any index 
        • iterate efficiently 
    
    2. Tube Container List 
        All the tube objects are stored in: 
        vector<Tube> tubes; 
    Reasons: 
        • random access by index  
        • resizing based on number of colors 
        • efficient iteration during rendering 
        • good cache locality for repeated drawing 
         Since tubes are accessed by index constantly, vector is the most optimal choice. 

    3. List of Available Ball Colors 
        The game stores all available colors in: 
        vector<Color> COLORS = { Color::Red, Color::Yellow, Color::Magenta, Color::Cyan }; 
    Reasons: 
        • Defines the set of colors used to create balls. 
        • Used when filling allBalls vector. 
        • Allows the program to easily scale — adding more colors means simply adding more 
        entries. 
    We used vector here: 
        • vector is simple and efficient to store fixed small list of colors. 
        • Allows indexed access when assigning colors. 
        • Works seamlessly with shuffling and random distribution. 
 
    4. Leaderboard Storage  
        The leaderboard uses a vector: 
        vector<Player> leaderboard; 
    because: 
        • new players can be appended 
        • we can pass it to heap sort easily 
        • order can be rearranged 
        • random access is required by heapify operations 
    
Min-Heap For Sorting Leaderboard 
    In this project, the leaderboard requires ranking players based on three priority conditions: 
        1. Players who won should always rank above those who lost 
        2. Among winners or losers, the player with fewer moves should rank higher 
        3. If moves are same, the player with less time should rank higher 
    This creates a multi-key ranking system and a Min-Heap is an ideal data structure for 
    implementing such priority rules. 
Min-Heap + Heap Sort 
        void heapifyDownMin(vector<Player>& heap, int n, int i); 
        void heapSort(vector<Player>& arr); 
    1. Custom Ranking Priority 
        We rank players by: 
        1. Winner   
        2. Least Moves  
        3. Least Time 
        A Min-Heap naturally supports multi-criteria comparison so the worst record rises to the top and gets removed first during heap           sort. 
    2. Extracting Loser First for Final Ascending Ranking 
        Leaderboards display best players at the top so during heap sort we repeatedly extract the minimum (loser) and place it at the             end, resulting in the array being sorted from best to worst. 
    3. Efficient Sorting for Dynamic Leaderboards 
        Min-Heap operations run in: 
        • Build Heap: O(N) 
        • Each extraction: O(log N) 
        • Heap Sort Total: O(N log N) 
    4. Stable and Predictable Ordering 
        Heap ensures strict ordering based on our compare function. 
        This avoids ambiguous cases where two players share moves but differ in win or time. 
    5. Handles Increasing Data Smoothly 
        As leaderboard entries grow, heap-based sorting keeps performance stable compared to simple 
        repeated sorting. 
    We didn’t use a Binary Search Tree or Vector because: 
        A tree may become unbalanced, making operations degrade to O(N). 
        Heap always maintains complete-tree balance. 
        Vector sort directly sorts values but does not allow controlled extraction needed during heap 
        sort. 
 
 
4. Main Features 
    1. Interactive Gameplay: Players can select tubes and move balls. 
    2. Move & Time Tracking: Displays number of moves and elapsed time. 
    3. Win/Loss Detection: Automatically detects win or max-move loss. 
    4. Leaderboard: Maintains a sorted record of player performance in a file. 
    5. Graphics & Audio: Enhances user experience (SFML graphics and music). 
 
5. Algorithms Implemented 
1. Game Win Check 
    • Function checkWin() iterates over all tubes to check if they are sorted. 
    • Each tube is considered sorted if all balls are of the same color using isSorted(). 
2. Ball Transfer Logic 
    • Player selects a source tube and a target tube. 
    • Checks: 
        1. Source tube is not empty. 
        2. Target tube is not full. 
    • Transfers the top ball using stack.pop() and stack.push(). 
3. Leaderboard Sorting 
    • Heap sort is used to sort players by: 
        1. Win status 
        2. Number of moves 
        3. Time taken 
    • Ensures players with wins, fewer moves, and less time appear first. 
 
6. Conclusion 
This project demonstrates the practical use of stacks, vectors, and heaps in implementing a 
real-world puzzle game. The focus on data structure manipulation and algorithmic efficiency 
makes it a strong representation of DSA concepts, while the graphical and audio components 
enhance user engagement.
