# QLearning Car

This is my QLearning Car project. It's my first pure c++ project. I've been wanting to dwell into making a c++ only project for 2 years now and here we are!

## How does this work?

This car works via Q-Learning (hence the name). I did want to switch to neural networking but I stuck with Q-Learning. Q-Learning has a fancy equation which in extremely simple terms is `I can do actions and I have states, I have a table of actions with states that is zero, I pick a random action, that action gave me a positive number! I'm gonna repeat that.`. Of course, there is more to it (like exploitation vs exploration and negative values if it does a wrong move) but that's not for me to explain here (more at [My site](https://jaskowicz.xyz)).

The algorithm picks random moves and either gets a positive number, negative number or nothing. The AI also gets a constant negative number for the longer the lap is. The AI will get a positive value for hitting the goal and a negative for a wall. However, this would quickly be met with exploitation as it would just go forward then back and instantly win so there are checkpoints for the AI to reach. The Checkpoints also tell the AI it's doing well so it can keep remembering where it went well.

## Why Q-Learning?

Well, just a bit of fun. I explain further down that this project was inspired by Code Bullet so that's a reason for it but other than that it's just funny. This does mean that the AI will be dreadful at other tracks so it'll always need to be re-trained if the track moves even the slightest. Remember, Q-Learning doesn't learn really how to drive, it just remembers where's it's been and does something random from there.

## Libraries Used

- [SFML](https://www.sfml-dev.org/index.php)
- [NumCpp](https://github.com/dpilger26/NumCpp)

## Commands

- ShowStats
- ShowFPS
- ShowCheckpoints

## Fastest times

- Me : 13.917
- AI : N/A (Yet to be made)

## Credits:

- Nick Koirala, ahnonay, switchboy | collision (.cpp and .h)

## Inspiration & tiny ramble

This was inspired by Code Bullet's video (hence why the track is sorta similar) along with my love for F1. I also wanted to see how the AI would handle a chicane (the bump on the back straight) so that's in there. I'd love to also get it to drive f1 circuits (I did want to do Monaco but oh well).

![image](https://user-images.githubusercontent.com/46899449/193789791-0c15480c-3ad1-42bf-b217-eeaa2bf41136.png)
