# ComBoard #
There supposed to be two ways of player control - with keyboard or cameras. Unfortunately friend who has been responsible for motion capture module didn't manage to finish his assignment yet, so only keyboard control via ComBoard module is functional.
Fighting styles are defined in the `/Data/models/anim/*.txt` files. Each style contains a list of possible actions. Each action is defined by set of skeletal animations and keyboard combos leading to other actions.
For more info on creating your own fighting styles check [Configuration](Configuration.md).

Default keyboard binding for ComBoard is following:

| Movement | One player (second uses cameras) | Two players - player 1 | Two players - player 2 |
|:---------|:---------------------------------|:-----------------------|:-----------------------|
| Left Hand Block  | A     | Caps Lock  | I     |
| Left Hand Punch  | S     | A          | O     |
| Right Hand Punch | D     | S          | P     |
| Right Hand Block | F     | D          | [     |
| Left Leg Block   | Z     | Lewy Shift | K     |
| Left Kick        | X     | Z          | L     |
| Right Kick       | C     | X          | ;     |
| Right Leg Block  | V     | C          | '     |
| Forward          | up    | T          | up    |
| Backward         | down  | G          | down  |
| Left             | left  | F          | left  |
| Right            | right | H          | right |

The meaning of the keys is approximate, because final action depends on key combination - ex. when Left Kick starts "kick" action, than Forward key may in this context mean "high kick", and not "abandon kick and move forward". Everything is up to the designer of the fighting style.
The 'karate' style included in game contains limited set of animations. The main combos are:

Forward - step forward
> Forward - jump forward
> Backward - stop
> any of the attacks below - stop and attack
Backward - step backward
> Forward - stop
> any of the attacks below - stop and attack
Left - rotate left
> Left when the right leg is the front leg - rotate 180 degrees
> Right - stop
> any of the attacks below - stop and attack
Right - rotate right
> Left - stop
> Right when the left leg is the front leg - rotate 180 degrees
> any of the attacks below - stop and attack
front hand punch - gyaku-tsuki punch
> Forward - high punch
> Backward - low punch
back hand punch - oi-tsuki punch
> Forward - high punch
> Backward - low punch
front leg kick - low raising kick
> front leg kick - front mai-geri kick
> > Forward - high front mai-geri kick
back leg kick - back

> front leg kick - back mai-geri kick
> > Forward - high back mai-geri kick