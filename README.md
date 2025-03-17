# ChessBot Hackathon

Organizer repo: [@Codam/chess-hackathon](https://github.com/codam-coding-college/chess-hackathon) 

Team: [@rubenfin](https://github.com/rubenfin)  [@jackdehaan](https://github.com/Jackdehaan)  [@michmos](https://github.com/michmos)

## Task
This hackathon challenged us to optimize a preexisting ChessBot with minimal functionality. We were provided with boilerplate code and had 5 days to improve its performance and features.

## Optimizations
We implemented the following enhancements:

- Upgraded the **Minimax algorithm** to **Alpha-Beta pruning** for faster decision-making.
- Added a **simple dynamic move ordering** mechanism using **transition tables**.
- Improved the **evaluation function** by integrating **state-dependent piece-square tables**.
- Implemented an **opening book** using **Zobrist hashing** and **transition tables**.

## Further Optimizations
Given the time constraints, there were several optimizations we couldn't complete but would have pursued:

- **Incremental updates:** Implement an `undo_move` function to minimize position copies in recursive functions.
- **Zobrist hash updates:** Instead of recomputing the hash for every move, update the previous hash incrementally.
- **More sophisticated move ordering:** Prioritizing better moves allows for more pruning and faster searches.
- **Dynamic search depth:** Adjust depth based on evaluation scores and game phase.
- **Bitboards:** Use a more efficient board representation for improved performance.

## Learnings
1. **Working with pre-existing code:**  
   Initially, we considered rewriting the entire codebase. However, we quickly realized that modifying and optimizing the existing implementation was a more efficient use of our limited time.
2. **Time management in a hackathon:**  
   We spent too much time implementing features, leaving insufficient time for proper testing and debugging. A well-structured timeline and strict adherence to it are crucial in time-sensitive projects.

## Usage

### Build
```sh
git clone https://github.com/rubenfin/ChessBot.git && cd ChessBot && make
```
### Use
The bot follows the UCI (Universal Chess Interface) protocol, meaning you can use any UCI-compatible chess GUI to play against our engine e.g. [@cutechess](https://github.com/cutechess/cutechess)
