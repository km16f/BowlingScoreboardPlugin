# BowlingScoreboardPlugin
Bowling Scoreboard Exercise in Unreal Engine 5

**Description:**

This is a C++ plugin for Unreal Engine 5 aimed at simulating a bowling scoreboard.

Contains a custom Widget Blueprint for the GUI elements of the scoreboard

Includes C++ code needed to properly implement the scoring features


---------------------------------------------------------------------------------------------------


**INSTALL INFO:**


Engine Version: 5.5.3

Clone Repository to a safe location. Wherever you like Unreal Project files to live

Open BowlingProject.uproject with Unreal Engine. Make sure to use version 5.5

If prompted to rebuild modules select yes.

Once unreal loads make sure to compile project again.


**TO RUN SCOREBOARD:**


Click "Window" Toolbar Menu in Unreal

Click the "BowlingScoreBoard" button at the very bottom

This should spawn an actor and start the bowling scoreboard GUI

From here you enter any number 0-9, "X", "x", or "/" in each box and hit enter

The board will unlock the next boxes and calculate the running score if your 
inputs are valid.


**KNOWN BUGS:**

- IN PROGRESS:
  - Cursor does not automatically move to next box (Unreal UI is being wonky here)
  - If you click out of the socreboard into the level you can press SHIFT + F1 to get back to the board
  - Final block sometimes doesn't add to total score
