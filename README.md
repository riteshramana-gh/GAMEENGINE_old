# PixelForge Multi-Game Engine

## Overview
PixelForge is a C++ terminal-based multi-game engine featuring 5 classic games:
- **Battleship** - Naval warfare strategy game
- **Connect Four** - Strategic column-dropping game
- **Minesweeper** - Classic mine-detection puzzle
- **Wordle** - Word guessing game
- **Tic Tac Toe** - Classic 3x3 strategy game

The project includes a comprehensive leaderboard system that tracks scores across all games.

## Project Architecture

### Core Structure
- **mainBattle.cpp** - Main entry point with menu system and game launcher
- **Game.h/cpp** - Abstract base class for all games
- **player.h** - Player data structure with score tracking
- **Leaderboard.h** - Leaderboard management with file persistence
- **templates.h** - Template utilities for game object creation

### Game Implementations
Each game is implemented as a class inheriting from the `Game` base class:
- `Battleship.h/cpp` - Battleship game implementation
- `connectfour.h/cpp` - Connect Four implementation
- `minesweeper.h/cpp` - Minesweeper implementation
- `tictactoe.h/cpp` - Tic Tac Toe implementation
- `wordle.h/cpp` - Wordle implementation

### Features
- Animated ASCII art logo and menu
- Color-coded terminal output using ANSI escape codes
- Cross-platform support (Windows/Linux/macOS)
- File-based leaderboard persistence
- Combined leaderboard view across all games
- Single-key menu navigation using platform-specific `getch()` implementation

## Technical Details
- Language: C++17
- Platform: Cross-platform (Linux/macOS/Windows)
- UI: Terminal-based with ANSI color codes
- Data Storage: Text files for leaderboards
- Threading: Uses std::thread for animations
