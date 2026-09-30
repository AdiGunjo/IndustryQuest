def tug_of_war(nums):
    n = len(nums)
    total = sum(nums)
    best = {"diff": float('inf'), "set1": []}

    def backtrack(index, count1, sum1, chosen):
        remaining = n - index
        # Prune: not enough elements left to fill team 1 to n//2
        if count1 > n // 2 or count1 + remaining < n // 2:
            return
        if index == n:
            if count1 == n // 2 or count1 == (n + 1) // 2:
                diff = abs((2 * sum1) - total)
                if diff < best["diff"]:
                    best["diff"] = diff
                    best["set1"] = chosen[:]
            return

        # Include nums[index] in team 1
        chosen.append(nums[index])
        backtrack(index + 1, count1 + 1, sum1 + nums[index], chosen)
        chosen.pop()

        # Exclude nums[index] from team 1
        backtrack(index + 1, count1, sum1, chosen)

    backtrack(0, 0, 0, [])
    set1 = best["set1"]
    set2 = [x for x in nums if x not in set1 or set1.remove(x)]
    print(f"Team 1: {set1}  |  Team 2: {set2}  |  Difference: {best['diff']}")

tug_of_war([23, 45, -34, 12, 0, 98, -73, 235, 1, 37])