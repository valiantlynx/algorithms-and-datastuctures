#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

// Constant defaults
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PADDLE_WIDTH = 15.f;
const float PADDLE_HEIGHT = 100.f;
const float BALL_RADIUS = 10.f;
const float PADDLE_SPEED = 400.f;
const float INITIAL_BALL_SPEED = 420.f;
const float BALL_SPEED_INCREMENT = 69.f;
const float MAX_BALL_SPEED = 800.f;
const float PI = 3.14159f;
const int WINNING_SCORE = 5;

int main() {
    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create the game window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong Pong Game");
    window.setFramerateLimit(60);

    // Initialize game objects
    // Left paddle (Player)
    sf::RectangleShape leftPaddle;
    leftPaddle.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    leftPaddle.setFillColor(sf::Color::White);
    leftPaddle.setPosition(30.f, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2);

    // Right paddle(AI but not really)
    sf::RectangleShape rightPaddle;
    rightPaddle.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    rightPaddle.setFillColor(sf::Color::White);
    rightPaddle.setPosition(WINDOW_WIDTH - 30.f - PADDLE_WIDTH, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2);

    // Ballz
    sf::CircleShape ball;
    ball.setRadius(BALL_RADIUS);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(WINDOW_WIDTH / 2 - BALL_RADIUS, WINDOW_HEIGHT / 2 - BALL_RADIUS);

    // Middle line
    sf::RectangleShape middleLine;
    middleLine.setSize(sf::Vector2f(2.f, WINDOW_HEIGHT));
    middleLine.setFillColor(sf::Color(100, 100, 100));
    middleLine.setPosition(WINDOW_WIDTH / 2 - 1.f, 0.f);

    // ingame variables
    int leftScore = 0;
    int rightScore = 0;
    float ballSpeedX = 0.f;
    float ballSpeedY = 0.f;
    float currentBallSpeed = INITIAL_BALL_SPEED;
    bool gameStarted = false;
    bool gameOver = false;
    std::string winnerText;

    //  reset the ball with random direction (this doesnt work like i intended)
    auto resetBall = [&]() {
        ball.setPosition(WINDOW_WIDTH / 2 - BALL_RADIUS, WINDOW_HEIGHT / 2 - BALL_RADIUS);
        
        // Random angle between -PI/4 and PI/4 or between 3PI/4 and 5PI/4
        float angle;
        if (std::rand() % 2 == 0) {
            // Towards right player
            angle = -PI/4 + (std::rand() % 100) / 100.f * PI/2;
        } else {
            // Toward left player
            angle = 3*PI/4 + (std::rand() % 100) / 100.f * PI/2;
        }
        
        currentBallSpeed = INITIAL_BALL_SPEED;
        ballSpeedX = std::cos(angle) * currentBallSpeed;
        ballSpeedY = std::sin(angle) * currentBallSpeed;
        
        gameStarted = true;
    };

    // Text scores
    sf::Font font;
    if (!font.loadFromFile("resources/arial.ttf")) {
        std::cout << "Error loading font!" << std::endl;
        // Continue without text
    }

    sf::Text leftScoreText;
    leftScoreText.setFont(font);
    leftScoreText.setCharacterSize(40);
    leftScoreText.setFillColor(sf::Color::White);
    leftScoreText.setPosition(WINDOW_WIDTH / 4, 30);
    sf::Text rightScoreText;
    rightScoreText.setFont(font);
    rightScoreText.setCharacterSize(40);
    rightScoreText.setFillColor(sf::Color::White);
    rightScoreText.setPosition(3 * WINDOW_WIDTH / 4, 30);
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 30);
    sf::Text instructionText;
    instructionText.setFont(font);
    instructionText.setCharacterSize(24);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setString("Press SPACE to start");
    instructionText.setPosition(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 50);

    // Sound effects //TODO: if i want to make this available online. check the licencing of the resources. i got them from https://pixabay.com/sound-effects/search/collision/ Font: https://ttfonts.net/
    sf::SoundBuffer paddleHitBuffer;
    sf::SoundBuffer wallHitBuffer;
    sf::SoundBuffer scoreBuffer;
    sf::Sound paddleHitSound;
    sf::Sound wallHitSound;
    sf::Sound scoreSound;

    bool soundEffectsLoaded = true;

    if (!paddleHitBuffer.loadFromFile("resources/paddle_hit.wav")) {
        std::cout << "Error loading paddle hit sound!" << std::endl;
        soundEffectsLoaded = false;
    } else {
        paddleHitSound.setBuffer(paddleHitBuffer);
    }

    if (!wallHitBuffer.loadFromFile("resources/wall_hit.wav")) {
        std::cout << "Error loading wall hit sound!" << std::endl;
        soundEffectsLoaded = false;
    } else {
        wallHitSound.setBuffer(wallHitBuffer);
    }

    if (!scoreBuffer.loadFromFile("resources/score.wav")) {
        std::cout << "Error loading score sound!" << std::endl;
        soundEffectsLoaded = false;
    } else {
        scoreSound.setBuffer(scoreBuffer);
    }

    // Clock for delta time calculation
    sf::Clock clock;

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (!gameStarted) {
                    resetBall();
                }
                
                if (gameOver) {
                    // reset the game
                    leftScore = 0;
                    rightScore = 0;
                    gameOver = false;
                    resetBall();
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (!gameOver) {
            //  control (left paddle, player)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                leftPaddle.move(0, -PADDLE_SPEED * deltaTime);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                leftPaddle.move(0, PADDLE_SPEED * deltaTime);
            }
            // Prevent paddles from moving outside the screen
            if (leftPaddle.getPosition().y < 0) {
                leftPaddle.setPosition(leftPaddle.getPosition().x, 0);
            }
            if (leftPaddle.getPosition().y + PADDLE_HEIGHT > WINDOW_HEIGHT) {
                leftPaddle.setPosition(leftPaddle.getPosition().x, WINDOW_HEIGHT - PADDLE_HEIGHT);
            }
            // control (right paddle, bot)
            if (gameStarted) {
                float ballCenterY = ball.getPosition().y + BALL_RADIUS;
                float paddleCenterY = rightPaddle.getPosition().y + PADDLE_HEIGHT / 2;
                
                // Simple algo that follows the ball with a delay
                if (paddleCenterY < ballCenterY - 10) {
                    rightPaddle.move(0, PADDLE_SPEED * 0.7f * deltaTime);
                } else if (paddleCenterY > ballCenterY + 10) {
                    rightPaddle.move(0, -PADDLE_SPEED * 0.7f * deltaTime);
                }
                
                // Prevent bot paddle from moving outside the screen
                if (rightPaddle.getPosition().y < 0) {
                    rightPaddle.setPosition(rightPaddle.getPosition().x, 0);
                }
                if (rightPaddle.getPosition().y + PADDLE_HEIGHT > WINDOW_HEIGHT) {
                    rightPaddle.setPosition(rightPaddle.getPosition().x, WINDOW_HEIGHT - PADDLE_HEIGHT);
                }
            }

            // Ballz movement
            if (gameStarted) {
                ball.move(ballSpeedX * deltaTime, ballSpeedY * deltaTime);
                
                // Ball collision with top and bottom walls
                if (ball.getPosition().y <= 0 || 
                    ball.getPosition().y + 2 * BALL_RADIUS >= WINDOW_HEIGHT) {
                    ballSpeedY = -ballSpeedY;
                    if (soundEffectsLoaded) {
                        wallHitSound.play();
                    }
                }
                // Ball collision with left paddle
                if (ballSpeedX < 0 && 
                    ball.getPosition().x <= leftPaddle.getPosition().x + PADDLE_WIDTH &&
                    ball.getPosition().x >= leftPaddle.getPosition().x &&
                    ball.getPosition().y + BALL_RADIUS >= leftPaddle.getPosition().y &&
                    ball.getPosition().y + BALL_RADIUS <= leftPaddle.getPosition().y + PADDLE_HEIGHT) {
                    
                    //  collision position relative to paddle center
                    float relativeIntersectY = (leftPaddle.getPosition().y + PADDLE_HEIGHT/2) - (ball.getPosition().y + BALL_RADIUS);
                    float normalizedRelativeIntersectionY = relativeIntersectY / (PADDLE_HEIGHT/2);
                    float bounceAngle = normalizedRelativeIntersectionY * (PI/3); // Max bounce angle: 60 degrees
                    
                    // Increase ball speed and reverse direction
                    currentBallSpeed = std::min(currentBallSpeed + BALL_SPEED_INCREMENT, MAX_BALL_SPEED);
                    ballSpeedX = std::cos(bounceAngle) * currentBallSpeed;
                    ballSpeedY = -std::sin(bounceAngle) * currentBallSpeed;
                    if (soundEffectsLoaded) {
                        paddleHitSound.play();
                    }
                }
                
                // Ball collision with right paddle
                if (ballSpeedX > 0 && 
                    ball.getPosition().x + 2 * BALL_RADIUS >= rightPaddle.getPosition().x &&
                    ball.getPosition().x + 2 * BALL_RADIUS <= rightPaddle.getPosition().x + PADDLE_WIDTH &&
                    ball.getPosition().y + BALL_RADIUS >= rightPaddle.getPosition().y &&
                    ball.getPosition().y + BALL_RADIUS <= rightPaddle.getPosition().y + PADDLE_HEIGHT) {
                    
                    // collision position relative to paddle center
                    float relativeIntersectY = (rightPaddle.getPosition().y + PADDLE_HEIGHT/2) - (ball.getPosition().y + BALL_RADIUS);
                    float normalizedRelativeIntersectionY = relativeIntersectY / (PADDLE_HEIGHT/2);
                    float bounceAngle = normalizedRelativeIntersectionY * (PI/3); // Max bounce angle: 60 degrees
                    
                    // Increase ball speed and reverse direction
                    currentBallSpeed = std::min(currentBallSpeed + BALL_SPEED_INCREMENT, MAX_BALL_SPEED);
                    ballSpeedX = -std::cos(bounceAngle) * currentBallSpeed;
                    ballSpeedY = -std::sin(bounceAngle) * currentBallSpeed;
                    if (soundEffectsLoaded) {
                        paddleHitSound.play();
                    }
                }
                
                // Ball goes out of bounds (in other words scoring)
                if (ball.getPosition().x + 2 * BALL_RADIUS < 0) {
                    // Right player scores
                    rightScore++;
                    
                    if (soundEffectsLoaded) {
                        scoreSound.play();
                    }
                    
                    if (rightScore >= WINNING_SCORE) {
                        gameOver = true;
                        winnerText = "AI Wins!";
                        gameStarted = false;
                    } else {
                        resetBall();
                    }
                } else if (ball.getPosition().x > WINDOW_WIDTH) {
                    // Left player scores
                    leftScore++;
                    
                    if (soundEffectsLoaded) {
                        scoreSound.play();
                    }
                    
                    if (leftScore >= WINNING_SCORE) {
                        gameOver = true;
                        winnerText = "Player Wins!";
                        gameStarted = false;
                    } else {
                        resetBall();
                    }
                }
            }

            // Update score text
            leftScoreText.setString(std::to_string(leftScore));
            rightScoreText.setString(std::to_string(rightScore));
        }

        window.clear(sf::Color(50, 50, 50));
        
        // Draw middle line
        window.draw(middleLine);
        
        // Draw paddles and ball
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        
        // Draw scores
        window.draw(leftScoreText);
        window.draw(rightScoreText);
        
        // Draw instructions 
        if (!gameStarted && !gameOver) {
            window.draw(instructionText);
        }
        
        // Draw game over 
        if (gameOver) {
            gameOverText.setString(winnerText);
            window.draw(gameOverText);
            
            sf::Text restartText;
            restartText.setFont(font);
            restartText.setCharacterSize(24);
            restartText.setFillColor(sf::Color::White);
            restartText.setString("Press SPACE to restart");
            restartText.setPosition(WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT / 2 + 50);
            window.draw(restartText);
        }
        
        window.display();
    }
    return 0;
}
