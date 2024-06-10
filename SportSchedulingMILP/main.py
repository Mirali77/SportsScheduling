from ortools.linear_solver import pywraplp
import time

def main():
    solver = pywraplp.Solver.CreateSolver("SAT")
    if not solver:
        return

    # Input
    input_path = input()
    input_file = open(input_path, "r")

    lines = input_file.readlines()

    n, m = map(int, lines[0].split())

    alpha, beta = map(int, lines[1].split())

    q, b = [], []

    tn = n
    if n % 2 == 0:
        tn -= 1

    for i in range(n):
        q.append(list(map(int, lines[2 + i].split())))

    for i in range(tn):
        b.append(list(map(int, lines[2 + n + i].split())))

    cost = list(map(int, lines[-1].split()))

    # To mip model

    X = []
    ind = 0
    for i in range(n):
        l2 = []
        for j in range(n):
            l3 = []
            for t in range(tn):
                l4 = []
                for s in range(m):
                    l5 = solver.IntVar(0.0, 1.0, str(ind))
                    ind += 1
                    l4.append(l5)
                l3.append(l4)
            l2.append(l3)
        X.append(l2)
    #print(solver.NumVariables())

    # Constraints

    for i in range(n):
        for t in range(tn):
            constraint = solver.RowConstraint(0, 1, "")
            for j in range(n):
                if i == j:
                    continue
                for s in range(m):
                    constraint.SetCoefficient(X[min(i, j)][max(i, j)][t][s], 1)

    for i in range(n):
        for j in range(i + 1, n):
            constraint = solver.RowConstraint(1, 1, "")
            for t in range(tn):
                for s in range(m):
                    constraint.SetCoefficient(X[i][j][t][s], 1)

    for t in range(tn):
        for s in range(m):
            constraint = solver.RowConstraint(0, b[t][s], "")
            for i in range(n):
                for j in range(i + 1, n):
                    constraint.SetCoefficient(X[i][j][t][s], 1)
    #print(solver.NumConstraints())

    # Objective function

    objective = solver.Objective()
    for i in range(n):
        for j in range(i + 1, n):
            for t in range(tn):
                for s in range(m):
                    c = alpha * (-q[i][s] - q[j][s]) + beta * cost[s]
                    objective.SetCoefficient(X[i][j][t][s], c)
    objective.SetMinimization()

    # Solving

    start_time = time.perf_counter()
    status = solver.Solve()
    if status == pywraplp.Solver.OPTIMAL:
        print("Objective value =", -solver.Objective().Value())
        print()
        passed = round((time.perf_counter() - start_time) * 1000)
        print(f"Problem solved in {passed:d} milliseconds")
    else:
        print("The problem does not have an optimal solution.")


if __name__ == "__main__":
    main()