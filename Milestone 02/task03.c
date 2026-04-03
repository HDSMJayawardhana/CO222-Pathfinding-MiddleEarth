#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 26
#define MAX_H 10
#define MAX_W 10

// Structure to represent a cell in the map
typedef struct {
    int row, col;
} Cell;

// Global arrays
char map[MAX_H][MAX_W];
bool visited[MAX_H][MAX_W];
int distance[MAX_H][MAX_W];

// Queue for BFS
typedef struct {
    Cell items[MAX_SIZE * MAX_SIZE];
    int front, rear;
} Queue;

// Function to create a 2D array for a given string
void createmaparray(int H, int W, char mapstring[]) {
    int index = 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            map[i][j] = mapstring[index++];
        }
    }
}

// Function to check if the cell is within bounds
bool validcell(int row, int col, int H, int W) {
    return row >= 0 && row < H && col >= 0 && col < W;
}

// Function to check if a move is valid based on conditions
bool validmove(char from, char to) {
    int diff = to - from;
    return (diff <= 2 && diff >= 0) || (diff >= -3 && diff <= 0);
}

// Function to calculate the Fibonacci number
int fibonacci(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Function to perform Breadth-First Search
int bfs(int H, int W, Cell start, Cell end, Cell teleport1, Cell teleport2) {
    // Directional vectors for up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Reset global arrays
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            visited[i][j] = false;
            distance[i][j] = 0;
        }
    }

    // Initialize the queue for BFS
    Queue queue;
    queue.front = queue.rear = -1;

    // Enqueue the starting cell
    queue.items[++queue.rear] = start;
    visited[start.row][start.col] = true;

    // BFS
    while (queue.front < queue.rear) {
        Cell current = queue.items[++queue.front];

        // Check if the current cell is the destination
        if (current.row == end.row && current.col == end.col) {
            return distance[current.row][current.col];
        }

        // Explore neighboring cells
        for (int i = 0; i < 4; ++i) {
            int newrow = current.row + dr[i];
            int newcol = current.col + dc[i];

            // Check the new position is within bounds
            if (validcell(newrow, newcol, H, W)) {
                // Check the move is valid
                if (!visited[newrow][newcol] && validmove(map[current.row][current.col], map[newrow][newcol])) {
                    // Enqueue the new cell
                    queue.items[++queue.rear] = (Cell){newrow, newcol};
                    visited[newrow][newcol] = true;
                    distance[newrow][newcol] = distance[current.row][current.col] + 1;
                }
            }
        }
    }

    // No path found
    return -1;
}

// Function to calculate the calculated number for a given cell
int calculate_number(int row, int col, int W) {
    return row * W + col;
}

int main() {
    // Input variables
    int H, W; // Height and Width of the map
    int S1, S2; // Start
    int E1, E2; // End
    int M1, M2; // Fibonacci matching numbers
    int ND; // Number of Door cells

    // Reading input
    scanf("%d %d", &H, &W);
    scanf("%d %d", &S1, &S2);
    scanf("%d %d", &E1, &E2);

    char mapstring[H * W + 1];
    scanf("%s", mapstring);

    scanf("%d", &M1);
    scanf("%d", &M2);

    scanf("%d", &ND);
    int doors[ND][2]; // Array to store door cell positions
    for (int i = 0; i < ND; ++i) {
        scanf("%d %d", &doors[i][0], &doors[i][1]);
    }

    // Create a 2D array for the map
    createmaparray(H, W, mapstring);

    Cell start = {S1, S2};  // Starting position
    Cell end = {E1, E2};    // Ending position

    // Find teleportation doors
    Cell teleport1 = {-1, -1};
    Cell teleport2 = {-1, -1};
    for (int i = 0; i < ND; ++i) {
        int calculated_number = calculate_number(doors[i][0], doors[i][1], W);
        int fib = fibonacci(calculated_number);
        if (fib == M1) {
            teleport1.row = doors[i][0];
            teleport1.col = doors[i][1];
        } else if (fib == M2) {
            teleport2.row = doors[i][0];
            teleport2.col = doors[i][1];
        }
    }

    // Calculate the minimum distance considering teleportation
    int min_distance = bfs(H, W, start, end, teleport1, teleport2);

    // Output
    if (min_distance != -1) {
        printf("The minimum distance from %c to %c is %d\n", map[S1][S2], map[E1][E2], min_distance);
    } else {
        printf("There is no possible path from %c to %c\n", map[S1][S2], map[E1][E2]);
    }

    return 0;
}

