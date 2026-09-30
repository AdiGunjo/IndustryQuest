def kakuro_solve(cells, clues):
    
    """Simplified Kakuro solver for a set of runs.
    cells: dict (r,c) -> variable name (all blank cells).
    clues: list of (list_of_cell_coords_in_run, target_sum).
    Solves for digit 1-9 assignment (no repeats within a run) satisfying all clues.
    Returns dict cell->digit or None."""
    
    variables = list(cells.keys())
    runs = clues

    def run_ok(assignment):
        for run_cells, total in runs:
            vals = [assignment[c] for c in run_cells if c in assignment]
            if len(vals) != len(set(vals)):
                return False
            if len(vals) == len(run_cells) and sum(vals) != total:
                return False
            if sum(vals) > total:
                return False
        return True

    def backtrack(i, assignment):
        if i == len(variables):
            return dict(assignment) if run_ok(assignment) else None
        var = variables[i]
        for d in range(1, 10):
            assignment[var] = d
            if run_ok(assignment):
                result = backtrack(i + 1, assignment)
                if result:
                    return result
            del assignment[var]
        return None

    return backtrack(0, {})

if __name__ == "__main__":
    print("KAKURO PROBLEM (tiny demo)")
    demo_cells = {(0, 0): 'a', (0, 1): 'b'}
    demo_clues = [([(0, 0), (0, 1)], 4)]
    print(kakuro_solve(demo_cells, demo_clues))


