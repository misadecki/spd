import random

def generate_flowshop_general(num_tasks, num_machines, filename):
    """
    Generuje instancję problemu Flow Shop dla dowolnej liczby zadań i maszyn.
    Format wyjściowy:
    Pierwsza linia: num_tasks num_machines
    Kolejne linie (dla każdego zadania): 0 czas_0 1 czas_1 ... m-1 czas_m-1
    """
    with open(filename, 'w') as f:
        # Pierwsza linia: liczba zadań i liczba maszyn
        f.write(f"{num_tasks} {num_machines}\n")
        
        # Generowanie linii dla każdego zadania
        for _ in range(num_tasks):
            task_line_parts = []
            for machine_id in range(num_machines):
                time = random.randint(5, 99)  # Losowy czas wykonywania od 5 do 99
                task_line_parts.append(f"{machine_id} {time}")
            
            # Łączenie i zapisanie całej linii dla danego zadania
            f.write(" ".join(task_line_parts) + "\n")
            
    print(f"Wygenerowano instancję: {filename} ({num_tasks} zadań, {num_machines} maszyn)")

# --- PRZYKŁAD UŻYCIA ---

# Słownik definiujący pliki wyjściowe: 'nazwa_pliku': (liczba_zadań, liczba_maszyn)
test_cases = {
    'flowshop_16_5.txt': (16, 5),    # Mała instancja, 2 maszyny
}

for filename, (tasks, machines) in test_cases.items():
    generate_flowshop_general(tasks, machines, filename)
