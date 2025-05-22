# Ping Pong Game Implementation 

## Requirements Met
| Requirement | Description | Status | Percentage |
|------------|-------------|--------|------------|
| Window Setup | Set up a graphical window with a defined size | ✅ Completed | 5% |
| Paddles and Controls | Draw paddles and implement player controls | ✅ Completed | 15% |
| Screen Boundaries | Prevent movement outside the screen | ✅ Completed | 5% |
| Ball Physics | Add ball that bounces off walls and paddles | ✅ Completed | 20% |
| Random Direction | Initialize ball movement with a random direction | ✅ Completed | 5% |
| Score Tracking | Track and display player scores (resets ball after scoring) | ✅ Completed | 15% |
| Win Condition | Define a winning score and display victory message | ✅ Completed | 10% |
| Speed Increment | Gradually increase speed on paddle collisions | ✅ Completed | 10% |
| AI Opponent | Implement a basic AI that tracks and follows the ball | ✅ Completed | 10% |
| Sound Effects | Add sound effects for collisions and scoring | ✅ Completed | 5% |
| **Total** | | **100%** | **100%** |

## How to Build and Run

1. Make sure you have SFML 2.5 installed on your system
2. go to the root directory of the project
3. Build using CMake:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Run the game:
   ```
   ./assignment_3_1
   ```

## Controls
- Use W/S or Up/Down arrow keys to move the left paddle
- Press SPACE to start the game or restart after game over
- First player to reach 5 points wins

PS: made it slightly fast. (its more fun) 
you can change the speed in the `main.cpp` file by modifying these variable.
```cpp
const float INITIAL_BALL_SPEED = 420.f;
const float BALL_SPEED_INCREMENT = 69.f;
```