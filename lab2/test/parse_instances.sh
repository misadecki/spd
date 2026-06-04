#!/bin/bash

INPUT_FILE="tail.dat"
OUTPUT_DIR="data"
if [ -d "$OUTPUT_DIR" ]; then
	rm -r "$OUTPUT_DIR" 
else
	mkdir -p "$OUTPUT_DIR"
fi


if [ ! -f "$INPUT_FILE" ]; then
	echo "Błąd: Plik $INPUT_FILE nie istnieje."
	exit 1
fi

read -r RAW_TOTAL_TASKS < "$INPUT_FILE"
TOTAL_TASKS=$(echo "$RAW_TOTAL_TASKS" | tr -d '\r')
exec 3< <(tail -n +2 "$INPUT_FILE")
echo "Znaleziono $TOTAL_TASKS instancji."

for ((task_num=1; task_num<=TOTAL_TASKS; task_num++)); do
	if ! read -u 3 -r RAW_HEADER_LINE; then
		echo "Przedwczesny koniec pliku przy instancji $task_num."
		break
	fi

	HEADER_LINE=$(echo "$RAW_HEADER_LINE" | tr -d '\r')

	if [ -z "$HEADER_LINE" ]; then
		((task_num--))
		continue
	fi

	NUM_OPERATIONS=$(echo "$HEADER_LINE" | awk '{print $1}')

	OUTPUT_FILE="data/instance${task_num}.txt"
	echo "$HEADER_LINE" > "$OUTPUT_FILE"
	for ((task=1; task<=NUM_OPERATIONS; task++)); do
		if read -u 3 -r RAW_TASK_LINE; then
			TASK_LINE=$(echo "$RAW_OP_LINE" | tr -d '\r')
			echo "$TASK_LINE" >> "$OUTPUT_FILE"
		else
			echo "Błąd: Brak danych dla zadania $task w instancji $task_num."
			break 2
		fi
	done

	echo "Utworzono plik: $OUTPUT_FILE (liczba zadań: $NUM_OPERATIONS)"
done

exec 3<&-
echo "Zakończono przetwarzanie danych."
