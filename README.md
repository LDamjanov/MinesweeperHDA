# MinesweeperHDA

Minesweeper game checklist:

✅-Uncover fields like this:
Game asks for y-coordinate and input is either small or big letter
Game asks for x-coordinate and input is a number
Game asks to mark or open field (type 'MARK' to mark the field with the letter 'F' (flag))

✅-Randomize amount of mines using 'rand' function

✅-Show number of mines in adjascent fields.

✅-Open nearby fields if they don't have a mine and mark them with number '0'

✅-A main menu with the options: 'Tutorial (Anleitung)', 'Play (Spielen)', 'Highscores (Highscores)', 'Demo', 'Exit (Beenden)'

✅-After each game, the game asks the player for a name and the highscores are saved in a local file.

✅-The 'Highscores' option in the main menu shows the top 10 players with their name and their score.

✅-Ability to mark/flag fields that the player thinks have a mine

-Object oriented. There should be two classes: 'MinesweeperField' and 'MinesweeperGame'. The class 'MinesweeperGame' needs to inherit from the class 'MinesweeperField'

-Demo/Autoplay option: This option replays the best game up to now (The best game is stored in a local file like the highscores are)
