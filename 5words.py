def extract_opening_moves(input_file, output_file, num_moves=6):
    with open(input_file, "r") as infile, open(output_file, "w") as outfile:
        games = infile.read().split("\n")  # Separate games by double newlines
        
        for game in games:
            moves = game.strip().split()
            opening_moves = " ".join(moves[:num_moves])  # Each move has white and black moves
            outfile.write(opening_moves + "\n")  # Separate games by newline

# Usage example
extract_opening_moves("library/june2025", "output5words.uci")
