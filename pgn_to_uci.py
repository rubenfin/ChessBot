import re
import chess
import chess.pgn
import io

def pgn_to_uci(pgn_text):
    """
    Convert PGN chess game notation to UCI move notation.
    
    Args:
        pgn_text (str): The PGN text containing chess game(s)
        
    Returns:
        list: A list of UCI moves for each game in the PGN
    """
    # Initialize results list
    results = []
    
    # Create a string IO object from the PGN text
    pgn_io = io.StringIO(pgn_text)
    
    # Process each game in the PGN file
    game = chess.pgn.read_game(pgn_io)
    while game is not None:
        # Extract header information
        # headers = {
        #     "Event": game.headers.get("Event", "?"),
        #     "White": game.headers.get("White", "?"),
        #     "Black": game.headers.get("Black", "?"),
        #     "Result": game.headers.get("Result", "?")
        # }
        
        # Initialize a chess board
        board = game.board()
        
        # Extract moves in UCI format
        uci_moves = []
        for move in game.mainline_moves():
            uci_move = move.uci()
            uci_moves.append(uci_move)
            board.push(move)
        
        # Add game to results
        results.append({
            # "headers": headers,
            "uci_moves": uci_moves
        })
        
        # Read the next game
        game = chess.pgn.read_game(pgn_io)
    
    return results

def save_uci_to_file(results, output_file):
    """
    Save UCI moves to a text file.
    
    Args:
        results (list): List of dictionaries containing game info and UCI moves
        output_file (str): Path to save the UCI moves
    """
    with open(output_file, 'w', encoding='utf-8') as f:
        for game in results:
            # Write game headers
            # f.write(f"Event: {game['headers']['Event']}\n")
            # f.write(f"White: {game['headers']['White']}\n")
            # f.write(f"Black: {game['headers']['Black']}\n")
            # f.write(f"Result: {game['headers']['Result']}\n")
            
            # # Write UCI moves
            # f.write("Moves (UCI):\n")
            f.write(" ".join(game['uci_moves']))
            f.write("\n")

def main():
    """
    Main function to process PGN files and convert them to UCI.
    """
    import argparse
    
    parser = argparse.ArgumentParser(description='Convert PGN chess notation to UCI format')
    parser.add_argument('input_file', help='Input PGN file path')
    parser.add_argument('--output', '-o', default='input_file.uci', help='Output UCI file path')
    parser.add_argument('--encoding', '-e', default='latin-1', 
                        help='File encoding (default: latin-1, alternatives: utf-8, iso-8859-1, etc.)')
    
    args = parser.parse_args()
    
    # Read the PGN file with the specified encoding
    try:
        with open(args.input_file, 'r', encoding=args.encoding) as f:
            pgn_text = f.read()
    except UnicodeDecodeError:
        print(f"Error: Could not decode file with {args.encoding} encoding.")
        print("Try specifying a different encoding with the --encoding option.")
        print("Common encodings: latin-1, utf-8-sig, cp1252, iso-8859-1")
        return
    except FileNotFoundError:
        print(f"Error: Input file '{args.input_file}' not found.")
        return
    
    # Convert PGN to UCI
    results = pgn_to_uci(pgn_text)
    
    # Save results to file
    save_uci_to_file(results, args.output)
    
    print(f"Successfully converted {len(results)} game(s) from PGN to UCI format.")
    print(f"UCI moves saved to '{args.output}'")

if __name__ == "__main__":
    main()
