# break-brick-cpp

## Launch
```bash
make
./bin/break-brick
```

## Levels
- Add or remove levels in `levels/` director
- Levels are in `assets/levels`, level file are represented as file containg the number of rows and columns of the bricks and the bricks themselves, example: 
```
12 3
HHHHHHHHHHH
HHHHHHHHHHH
NNNNNNNNNNN
```
Where
  - N -> NormalBrick
  - H -> HardBrick
  - D -> HardenedBrick
  - U -> UnbreakableBrick