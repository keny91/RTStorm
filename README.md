#	**RT ANALYSIS API FOR HEROES OF THE STORM**

## /*** Version 0.1 - Development build	***/


#### This Program is built by combining different projects together. Given their separate funtionalities, they are classified as:


| **Project** | **Description** |
| --- | --- |
| **Host Engine** | Link and process a sequential game progression based on the stored line registers in the replay. |
| **RT Engine** | Tie all engines together, makes sure all actions and processed results are ordered. |
| **CV Engine** | Extract visual information from the physical replay in RT. |
| **Value Engine** | Performing the same action in different contexts might have a very different impact in the game´s result. |






/** CV Engine :		DESCRIPTION

This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).

These first interaction is designed to analyze RT results in a recorded match replay.
The program is currently optimize to capture 5v5 matches of any kind since the UI 
shares a common design. Replays can be accelerated so the match does not need to 
be run at normal speed. However it might be important to specify such speed (although
later interactions of the program will try to detect the match speed automatically)

Ideally it is planned to replace heroes map icons with more easily recognized
QR codes for each of the players. Early versions will not support the multi/dual 
controlled heroes such as "Cho-gall" (2 playes, 1 character) or "the Lost Vikings"
(1 player - 3 characters).


The applications -will- (BIG MIGHT) be powered by a computer vision engine based on OpenCV 3.3
It will be interesting to include a KNN or NN to do some character/portrait recognition.
*/


MOAR TO COME...
