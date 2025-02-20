package main

import (
	"context"
	"database/sql"
	"fmt"
	"log"
	"time"

	_ "github.com/lib/pq"
)

// Database connection configuration
const (
	host     = "localhost"
	port     = 5432
	user     = "postgres"
	password = "your_password"
	dbname   = "testdb"
)

// User represents a user in our system
type User struct {
	ID        int
	FirstName string
	LastName  string
	Email     string
	CreatedAt time.Time
}

// DBConnection wraps database connection and provides optimization settings
type DBConnection struct {
	db *sql.DB
}

// NewDBConnection creates and configures a new database connection with optimized settings
func NewDBConnection() (*DBConnection, error) {
	// Connection string with additional parameters for optimization
	connStr := fmt.Sprintf("host=%s port=%d user=%s password=%s dbname=%s "+
		"sslmode=disable application_name=query_optimization_example",
		host, port, user, password, dbname)

	// Open database connection
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		return nil, fmt.Errorf("error opening database: %v", err)
	}

	// Configure connection pool
	db.SetMaxOpenConns(25)                 // Limit maximum number of open connections
	db.SetMaxIdleConns(10)                 // Set maximum number of idle connections
	db.SetConnMaxLifetime(5 * time.Minute) // Set maximum lifetime for connections

	// Verify connection
	if err = db.Ping(); err != nil {
		return nil, fmt.Errorf("error connecting to database: %v", err)
	}

	return &DBConnection{db: db}, nil
}

// CreateUserTable creates the users table with appropriate indexes
func (d *DBConnection) CreateUserTable() error {
	// Create users table with appropriate data types and constraints
	createTableQuery := `
		CREATE TABLE IF NOT EXISTS users (
			id SERIAL PRIMARY KEY,
			first_name VARCHAR(50) NOT NULL,
			last_name VARCHAR(50) NOT NULL,
			email VARCHAR(255) NOT NULL UNIQUE,
			created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
		);
		
		-- Create indexes for commonly queried columns
		CREATE INDEX IF NOT EXISTS idx_users_email ON users(email);
		CREATE INDEX IF NOT EXISTS idx_users_names ON users(last_name, first_name);
		CREATE INDEX IF NOT EXISTS idx_users_created_at ON users(created_at);
	`

	_, err := d.db.Exec(createTableQuery)
	return err
}

// InsertUserBatch demonstrates efficient batch insertion
func (d *DBConnection) InsertUserBatch(users []User) error {
	// Start a transaction for batch insert
	tx, err := d.db.Begin()
	if err != nil {
		return fmt.Errorf("error starting transaction: %v", err)
	}
	defer tx.Rollback() // Rollback transaction if something goes wrong

	// Prepare statement for batch insert
	stmt, err := tx.Prepare(`
		INSERT INTO users (first_name, last_name, email, created_at)
		VALUES ($1, $2, $3, $4)
	`)
	if err != nil {
		return fmt.Errorf("error preparing statement: %v", err)
	}
	defer stmt.Close()

	// Execute batch insert
	for _, user := range users {
		_, err = stmt.Exec(user.FirstName, user.LastName, user.Email, user.CreatedAt)
		if err != nil {
			return fmt.Errorf("error inserting user: %v", err)
		}
	}

	// Commit transaction
	if err = tx.Commit(); err != nil {
		return fmt.Errorf("error committing transaction: %v", err)
	}

	return nil
}

// GetUsersByLastName demonstrates query optimization with EXPLAIN ANALYZE
func (d *DBConnection) GetUsersByLastName(ctx context.Context, lastName string) ([]User, error) {
	// First, analyze the query plan
	explainQuery := fmt.Sprintf("EXPLAIN ANALYZE SELECT * FROM users WHERE last_name = $1")
	rows, err := d.db.QueryContext(ctx, explainQuery, lastName)
	if err != nil {
		return nil, fmt.Errorf("error executing EXPLAIN ANALYZE: %v", err)
	}
	defer rows.Close()

	// Print query plan
	fmt.Println("Query Plan:")
	for rows.Next() {
		var plan string
		if err := rows.Scan(&plan); err != nil {
			return nil, fmt.Errorf("error scanning plan: %v", err)
		}
		fmt.Println(plan)
	}

	// Execute the actual query with context for timeout
	query := `
		SELECT id, first_name, last_name, email, created_at
		FROM users
		WHERE last_name = $1
		ORDER BY created_at DESC
	`

	rows, err = d.db.QueryContext(ctx, query, lastName)
	if err != nil {
		return nil, fmt.Errorf("error executing query: %v", err)
	}
	defer rows.Close()

	var users []User
	for rows.Next() {
		var user User
		err := rows.Scan(&user.ID, &user.FirstName, &user.LastName, &user.Email, &user.CreatedAt)
		if err != nil {
			return nil, fmt.Errorf("error scanning user: %v", err)
		}
		users = append(users, user)
	}

	return users, nil
}

// GetUsersWithPagination demonstrates efficient pagination
func (d *DBConnection) GetUsersWithPagination(limit, offset int) ([]User, error) {
	// Use LIMIT and OFFSET with ordered results for consistent pagination
	query := `
		SELECT id, first_name, last_name, email, created_at
		FROM users
		ORDER BY id
		LIMIT $1 OFFSET $2
	`

	rows, err := d.db.Query(query, limit, offset)
	if err != nil {
		return nil, fmt.Errorf("error executing pagination query: %v", err)
	}
	defer rows.Close()

	var users []User
	for rows.Next() {
		var user User
		err := rows.Scan(&user.ID, &user.FirstName, &user.LastName, &user.Email, &user.CreatedAt)
		if err != nil {
			return nil, fmt.Errorf("error scanning user: %v", err)
		}
		users = append(users, user)
	}

	return users, nil
}

func main() {
	// Create database connection
	db, err := NewDBConnection()
	if err != nil {
		log.Fatalf("Failed to connect to database: %v", err)
	}
	defer db.db.Close()

	// Create tables and indexes
	if err := db.CreateUserTable(); err != nil {
		log.Fatalf("Failed to create table: %v", err)
	}

	// Insert sample users
	sampleUsers := []User{
		{
			FirstName: "John",
			LastName:  "Doe",
			Email:     "john@example.com",
			CreatedAt: time.Now(),
		},
		{
			FirstName: "Jane",
			LastName:  "Doe",
			Email:     "jane@example.com",
			CreatedAt: time.Now(),
		},
	}

	if err := db.InsertUserBatch(sampleUsers); err != nil {
		log.Fatalf("Failed to insert users: %v", err)
	}

	// Create context with timeout
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	// Query users with lastname "Doe"
	users, err := db.GetUsersByLastName(ctx, "Doe")
	if err != nil {
		log.Fatalf("Failed to get users: %v", err)
	}

	// Print results
	fmt.Println("\nFound users:")
	for _, user := range users {
		fmt.Printf("- %s %s (%s)\n", user.FirstName, user.LastName, user.Email)
	}

	// Demonstrate pagination
	paginatedUsers, err := db.GetUsersWithPagination(10, 0)
	if err != nil {
		log.Fatalf("Failed to get paginated users: %v", err)
	}

	fmt.Println("\nPaginated users (first 10):")
	for _, user := range paginatedUsers {
		fmt.Printf("- %s %s (%s)\n", user.FirstName, user.LastName, user.Email)
	}
}
