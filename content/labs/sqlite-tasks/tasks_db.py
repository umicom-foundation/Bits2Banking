import sqlite3

connection = sqlite3.connect("tasks.db")
try:
    connection.execute("""
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY,
            title TEXT NOT NULL,
            status TEXT NOT NULL
        )
    """)

    with connection:
        connection.execute(
            "INSERT INTO tasks (title, status) VALUES (?, ?)",
            ("Review Umicom Studio", "todo")
        )

    for row in connection.execute(
        "SELECT id, title, status FROM tasks ORDER BY id"
    ):
        print(row)
finally:
    connection.close()
