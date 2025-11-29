# ADVENTURE-ENGINE
Adventure Game Engine

Adventure Game Engine
A modular C++ engine for turn-based adventure games, featuring player and enemy stat management, combat, inventory, leveling, and Python interoperability.

Features
Player and enemy stats (health, attack, defense, mana, gold, XP, level)
Combat system with random damage, critical hits, and healing
Leveling and experience system with stat progression
Inventory management (potions, weapons, armor)
Reward and gold system
Mana management and spell usage
Quick Time Event (QTE) keypress support
Python interoperability via exported functions (DLL)

Requirements
C++17 or later
Windows (uses __declspec(dllexport) and <conio.h>)
Optionally, Python (for integration via ctypes or cffi)

Usage
Compile the engine as a DLL/shared library for use in C++ or Python projects.
Import and call exported functions to manage game logic and player/enemy interactions.

Notes
Designed for extensibility and integration with other languages.
All game logic is handled via exported functions for easy use in external applications.
