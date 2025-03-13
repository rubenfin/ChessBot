def get_unique_moves(moves):
    # Create an empty list to store unique moves
    unique_moves = []
    
    for move in moves:
        if move not in unique_moves:
            unique_moves.append(move)
    
    return unique_moves

def process_moves_from_file(file_path):
    try:
        # Read the content from the file
        with open(file_path, 'r') as file:
            moves = file.readlines()
        
        # Clean up any leading/trailing whitespace
        moves = [move.strip() for move in moves if move.strip()]
        
        # Get the unique moves
        unique_moves = get_unique_moves(moves)
        
        # Write the unique moves to a new file
        with open('unique_moves.txt', 'w') as file:
            file.write("\n".join(unique_moves))
        
        print("Unique moves written to 'unique_moves.txt'")
    
    except FileNotFoundError:
        print(f"Error: The file '{file_path}' was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Provide the path to your text file containing the moves
process_moves_from_file('opening.txt')
