GRAPHICS LIBRARY SFML 
FUNCTIONS, CLASSES AND LOGICS USED

1.	CircleShape
	
	      Used to draw balls inside the tubes.
  	
	      Functions used:
		        1.	CircleShape(radius)
		        2.	circle.setFillColor(Color::X)
		        3.	circle.setPosition(x, y)
		        4.	window.draw(circle)

2.	Vector2f
   
	    Stores 2D positions and sizes.
  	
	    Used for:
		      1.	Tube positions
		      2.	Ball placement
		      3.	Button positions
		      4.	Mouse position conversion
	    Example:
	     		 Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

3.	Clock
   
	    Used to measure game time.
	    Functions:
		      clock.restart()
		      clock.getElapsedTime().asSeconds()
	    Used for:
		      1.	Game timer
		      2.	Auto-switch from welcome screen after 3 seconds
		      3.	Reset when new game starts

4. Color
   
	    Used for ball colors, outline colors, button text, etc.
	    Colors used:
		        Color::Red, Color::Blue, Color::Green, Color::Yellow,

5. Music
    
	    Used to play sound when a ball moves.
	    Functions used:
		      1.	music.openFromFile("...")
		      2.	music.setPitch()
		      3.	music.setVolume()
		      4.	music.play()

6. Event
    
	    Captures all user interactions.
	    Events used:
		      1.	Event::Closed  Detects window close
		      2.	Event::MouseButtonPressed  Detects button/tube clicks
		      3.	Event::TextEntered  Handles name typing
		      4.	Event::KeyPressed  Used for leaderboard exit (ESC)
	    Purpose:
		      1.	Name input
		      2.	Tube selection and ball movement
		      3.	Buttons (Play / Leaderboard / Exit)
		      4.	Keyboard handling

7. Click Detection & Mouse

	    Used with:
		      1.	shape.getGlobalBounds().contains(mousePos)
		      2.	event.type == Event::MouseButtonPressed
		      3.	Mouse::getPosition(window)   
	    Purpose:
		      1.	Detect tube selection
		      2.	Detect button clicks
		      3.	Detect leaderboard exit
		      4.	Detects mouse movements and clicks.

8. State Management

	    Game states controlled using boolean flags:
	    Usage 
		      1.	showMenu
		      2.	showGame
		      3.	showLeaderboard
		      4.	showWelcome
		      5.	isEnteringName
	    SFML does not provide state machines, so custom logic was used.

9. font

	    Loads a font file so text can be displayed.
	    Function used:
	     		 font.loadFromFile("...")

10. RectangleShape

	    Specialized shape representing a rectangle.
	    Usage Examples
		      1.	RectangleShape menuBackground(Vector2f(900, 500));
		      2.	RectangleShape playButton(Vector2f(200, 50));
		      3.	struct Tube {
		      RectangleShape shape;
		      };
	    Purpose:
		      1.	Buttons (Play, Leaderboard, Exit)
		      2.	Tubes
		      3.	Backgrounds (menu screen, welcome screen)

11. Texture

	    Image living on the graphics card that can be used for drawing.
	    Usage Example
		      Texture wb;
		      wb.loadFromFile("back.png");
		      welcomeBackground.setTexture(&wb);
	    Purpose:
		      1.	Loads image files from disk.
		      2.	Applied to shapes (rectangle backgrounds).

12. RenderWindow
    
	    Creates the main application window and acts as the drawing target.
	    Functions used:
		      1.	RenderWindow(VideoMode, title) Creates the window
		      2.	window.clear()  Clears previous frame
		      3.	window.draw(object)  Draws shapes/text/images
		      4.	window.display()  Shows new frame
		      5.	window.isOpen()  Checks if window is running
		      6.	window.close() Closes the window
		Purpose in project:
	      	Core game window for menu, game screen, leaderboard, and welcome screen.

