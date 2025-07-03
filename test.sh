#!/bin/bash

MAPS_DIR="maps/invalid"
EXEC="./so_long"
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes"

# Liste manuelle des fichiers de test
MAPS=(
    "duplicate_exit.ber"
    "duplicate_player.ber"
    "empty_file.ber"
    "empty_line_at_start.ber"
    "empty_line_in_between.ber"
    "invalid_entities.ber"
    "invalid_ext.ber"
    "no_coins.ber"
    "no_coins_path.ber"
    "no_corner_walls.ber"
    "no_exit.ber"
    "no_exit_path.ber"
    "no_outter_walls.ber"
    "no_player.ber"
    "non_rectangular.ber"
    "one_character.ber"
)

for map in "${MAPS[@]}"; do
    echo -e "\n=============================="
    echo "🗺️  Testing: $map"
    echo "=============================="
    $VALGRIND $EXEC "$MAPS_DIR/$map"
    echo -e "\n------------------------------\n"
done
