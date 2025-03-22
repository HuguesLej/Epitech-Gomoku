# Gomoku - Smart bots for a simple game

Gomoku is an {Epitech} 3rd year project. It's part of the *Artificial Intelligence* module.

**⚠️ If you're an Epitech student, be aware that copying any part of this code is considered cheating and would cause an -42!**

## Team

This project was developed by the following team members:
- [HuguesLej](https://github.com/HuguesLej)
- [Raphael_m](https://github.com/Raphael-Mabille)
- [Yarin35](https://github.com/Yarin35)

## Purpose

The purpose of this project is to implement a [Gomoku Narabe](https://en.wikipedia.org/wiki/Gomoku) bot, focusing on its performance. \
A simplified version of the game is used. There are 2 players on a 20x20 board, each one playing a stone at their turn.
The game ends when a player has 5 stones in a row (vertically, horizontally or diagonaly) and win.

## Constraints

The project has to be developed following certain constraints:
- Only standard libraries from the chosen development language are allowed.
- Each move has to be done in 5 seconds maximum.
- Each bot has to use a maximum of 70 MB of memory.
- The program has to be compliant with the defined [Communication protocol](#communication-protocol).

## Communication protocol

Here is a brief description of the communication protocol. This protocol describes communication between a gomoku manager and a gomoku bot.
Each bot must be able to receive and handle all the [mandatory commands](#mandatory-commands) and optionally the [optional commands](#optional-commands).
Additionally, each bot must be able to send the [sent commands](#sent-commands).

### Mandatory commands

#### START [size]

Indicates that the bot must initialize an empty board of the specified size.

The bot responds with `OK` if the board is successfully initialized or with the [ERROR](#error-error-message) command.

#### TURN [X],[Y]

Indicates an opponent's move with its coordinates. Coordinates are numbered from 0.

The bot responds with the coordinates of its own move in the following format: `[X],[Y]`.

#### BEGIN

Indicates to the bot that it's expected to open the match.

The bot responds with the coordinates of its move in the following format: `[X],[Y]`.

#### BOARD

This command is used for continuation of an opened match. It's followed by a list of lines ended by `DONE` and with the following format: `[X],[Y],[field]`.
`[X]` and `[Y]` are coordinates and `[field]` is either `1` (own player stone) or `2` (opponent's stone).

The bot responds with the coordinates of its move in the following format: `[X],[Y]`.

#### INFO [key] [value]

The manager sends informations to the bot, usually at the beginning of a match. The time limits cannot be changed in the middle of a match.
The manager doesn't always send all the informations. \
The key can be:
- `timeout_turn` - time limit for each move (milliseconds, 0=play as fast as possible)
- `timeout_match` - time limit of a whole match (milliseconds, 0=no limit)
- `max_memory` - memory limit (bytes, 0=no limit)
- `time_left` - remaining time limit of a whole match (milliseconds)
- `game_type` - 0=opponent is human, 1=opponent is brain, 2=tournament, 3=network tournament
- `rule` - bitmask or sum of 1=exactly five in a row win, 2=continuous game, 4=renju, 8=caro
- `evaluate` - coordinates X,Y representing current position of the mouse cursor
- `folder` - folder for persistent files

The remaining time (`time_left` key) can be negative when the brain runs out of time. Remaining time is equal to 2147483647 if the time for a whole match is unlimited.

The bot doesn't have to respond to this command as the manager doesn't read any answers.

#### END

Indicates the bot to terminate as soon as possible. The manager waits until the bot terminates. If it takes too long, the manager ends the bot.

The bot doesn't have to respond to this command as the manager doesn't read any answers.

#### ABOUT

Indicates the bot to respond with information about itself on one line. Each information has to be written in the format `key=value` with `value` in quotation marks. Values must be separated by commas.
Recommended keywords are name, version, author, country, www, email.

### Optional commands

#### RECSTART [width],[height]

This command behaves like the [START](#start-size) command except it's used for rectangular boards. `width` corresponds to X coordinates and `height` corresponds to Y coordinates.
If the board is squared, the manager must use the [START](#start-size) command.

#### RESTART

Indicates the bot that the game restart with the same starting parameters.

The bot responds `OK` and communication continues after the manager send the [START](#start-size) command.
If the bot answers with [UNKNOWN](#unknown-error-message) command, the manager sends [END](#end) command and executes the bot again.

#### TAKEBACK [X],[Y]

Indicates the bot that the last played move is canceled.

The bot responds `OK` and removes the stone at the specified coordinates.

#### PLAY [X],[Y]

This command is the manager's response to the bot [SUGGEST](#suggest-xy) command. It imposes the brain to play a move at the specified coordinates.

The bot responds with the coordinates of its own move in the following format: `[X],[Y]`.

### Sent commands

#### UNKNOWN [error message]

The bot sends this as a response to a command which is unknown or not implemented yet. The bot can send an optional message along with the command.

#### ERROR [error message]

The bot sends this as a response to a known command which it cannot handle correctly (e.g. the board is too large). The bot can send an optional message along with the command.

#### MESSAGE [message]

The bots sends this command as a message for the user. The manager can log this message in a window or a file.
The bot is expected to send this command just before responding to a command from the manager.
The message must contain not new line character and multi-line texts can be sent as a sequence of multiple `MESSAGE` commands.

#### DEBUG [message]

The bot sends this command to debug informations for the author of the bot. The command is similar to [MESSAGE](#message-message) except that messages are not publicly visible.

#### SUGGEST [X],[Y]

The bot can suggest a move to the manager instead of playing one. The manager is expected to answer with either [PLAY](#play-xy) or [END](#end).

## Tests results

<table>
  <thead>
    <tr>
      <th>Name</th>
      <th>Percentage</th>
      <th>Tests</th>
      <th>Crash ?</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>mandatory commands</td>
      <td>100%</td>
      <td>6/6</td>
      <td>No</td>
    </tr>
    <tr>
      <td>basic attack/defense</td>
      <td>100%</td>
      <td>10/10</td>
      <td>No</td>
    </tr>
    <tr>
      <td>basic priority</td>
      <td>100%</td>
      <td>3/3</td>
      <td>No</td>
    </tr>
    <tr>
      <td>ab_4_bf_v2 AI</td>
      <td>50%</td>
      <td>2/4</td>
      <td>No</td>
    </tr>
    <tr>
      <td>ab_4_scd_v2 AI</td>
      <td>50%</td>
      <td>2/4</td>
      <td>No</td>
    </tr>
    <tr>
      <td>ab_4_mc_v2 AI</td>
      <td>100%</td>
      <td>4/4</td>
      <td>No</td>
    </tr>
    <tr>
      <td>ab_4_pdy AI</td>
      <td>50%</td>
      <td>2/4</td>
      <td>No</td>
    </tr>
    <tr>
      <td>pattern_heuristics AI</td>
      <td>50%</td>
      <td>2/4</td>
      <td>No</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th>Total</th>
      <th>79.5%</th>
      <th>31/39</th>
      <th>No</th>
    </tr>
  </tfoot>
</table>

## How to use

### Requirements

To use this program, you need to install some tools:
- [g++](https://gcc.gnu.org/)
- [liskvork](https://github.com/liskvork/liskvork/releases)

### Basic usage

To compile the bot brain, run:
```sh
make
```

To compile and get 2 executables instead of one (executables will be the same), run:
```sh
make bin
```

To clean the build files, run:
```sh
make clean
```

To clean the executables, run:
```sh
make fclean
```

To rebuild the executables, run:
```sh
make fclean
```

To use the bot brain(s), you have to run once the liskvork executable. It will create a `config.ini`. Use it to configure the game, including the **bot brains executables path**.
After this, re-run the liskvork executables so it run the game.

### Testing usage

If you want to test the bot, first compile it using the above commands. Then move in the `testBoard` directory and compile the test binary using `make` command.
You can know run the tests using the following command:
```sh
./testBoard <path-to-bot-brain>
```

It will run the tests located in the `testBoard/boards` directory. You can add your own tests in it if you want to.
