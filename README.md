# Little Shepherd

A small life-simulation game I'm building in C++20 with raylib — villagers going about their day, and different ways to interact with and affect them.

## Running it

```
cmake -B cmake-build-debug
cmake --build cmake-build-debug --target WildlifeSim
```

You'll need the art in place first — see below.

## About the art

Two of the packs I used while building this are paid, so they're not in the repo (excluded via `.gitignore`):

- `Assets/Ultimate_Isometric_Pack` — [Ultimate RPG Tileset](https://penzilla.itch.io/ultimate-rpg-tileset)
- `Assets/IsometricEnemies` — [Ultimate Enemy Pack](https://penzilla.itch.io/ultimate-enemy-pack)

If you want the real visuals, grab those yourself and drop them in at those paths. Everything else under `Assets/` (`Character0`, `Ui`, `Maps`) is free and already sitting in the repo.
