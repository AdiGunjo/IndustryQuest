def solve_maze(maze):
    n = len(maze)
    solution = [[0] * n for _ in range(n)]

    def is_safe(r, c):
        return 0 <= r < n and 0 <= c < n and maze[r][c] == 1 and solution[r][c] == 0

    def backtrack(r, c):
        if r == n - 1 and c == n - 1 and is_safe(r, c):
            solution[r][c] = 1
            return True
        if not is_safe(r, c):
            return False

        solution[r][c] = 1
        for dr, dc in [(1,0),(0,1),(-1,0),(0,-1)]:
            if backtrack(r + dr, c + dc):
                return True
        solution[r][c] = 0  # backtrack: this cell is not part of the solution
        return False

    if backtrack(0, 0):
        for row in solution:
            print(row)
    else:
        print("No path exists")

maze = [
    [1, 0, 0, 0],
    [1, 1, 0, 1],
    [0, 1, 0, 0],
    [1, 1, 1, 1],
]
solve_maze(maze)
