# Bouncing-Ball
The project is done in C++ using GLUT library, which is an OpenGL utility toolkit for
C++ Programming Language. At first, a new project was created alongside a C++ source
file. The GLUT was used to create window with particular size and position and handle
motion event, reshape event, mouse event and so on.

![Screenshot (6)](https://github.com/a-b365/Bouncing-Ball/assets/63753115/23c1bea4-7491-4ec0-a0f3-5b60756eb225)

For displaying score after each click to the ball is made, a variable called score is maintained.
glutBitmapCharacter() is used to render character in particular font. And the position of the
text is maintained with glRasterPos2f(). The speed of the ball is increased every time user
click the ball and to display the result every 30 milliseconds to give much smoother action.
The mouse callback is setup for increasing speed in both directions and score by 1.After the
ball touches the ground the window is closed automatically and the final score is displayed.

Project Video Demonstration Link:
https://www.youtube.com/watch?v=-99znnFnTPs
