import psycopg2

try:
    # Connect to the PostgreSQL database
    conn = psycopg2.connect(
        dbname="postgres",
        user="postgres",
        password="save6425",
        host="localhost",  # Use 'localhost' since it's on the same server
        port="5432"  # Default PostgreSQL port
    )

    # Create a cursor to execute queries
    cur = conn.cursor()

    # Example query to check connection
    cur.execute("SELECT version();")
    version = cur.fetchone()
    print(f"Connected to PostgreSQL, version: {version}")

    # Close cursor and connection
    cur.close()
    conn.close()

except Exception as e:
    print(f"Error: {e}")