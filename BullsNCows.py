from itertools import product
from collections import Counter
import random


def bulls_and_cows(secret, guess):
    """Returns (bulls, cows) for two equal-length strings/sequences of digits."""
    bulls = sum(s == g for s, g in zip(secret, guess))
    common = 0
    from collections import Counter
    sc, gc = Counter(secret), Counter(guess)
    for k in sc:
        common += min(sc[k], gc.get(k, 0))
    cows = common - bulls
    return bulls, cows


def mastermind_solver(secret_len=4, digits="0123456789", secret=None, max_guesses=15):
    """Simple guess-and-narrow solver (Knuth-style, simplified brute force):
    maintains the set of candidates consistent with all past feedback."""
    if secret is None:
        secret = "".join(random.choice(digits) for _ in range(secret_len))
    candidates = ["".join(p) for p in product(digits, repeat=secret_len)]
    history = []
    guess = candidates[0]
    for _ in range(max_guesses):
        b, c = bulls_and_cows(secret, guess)
        history.append((guess, b, c))
        if b == secret_len:
            return secret, history
        candidates = [cand for cand in candidates
                      if bulls_and_cows(cand, guess) == (b, c)]
        if not candidates:
            break
        guess = candidates[len(candidates) // 2]
    return secret, history


if __name__ == "__main__":
    print("BULLS AND COWS / MASTERMIND")
    print("bulls_and_cows('1234','1243') =", bulls_and_cows("1234", "1243"))
    secret, history = mastermind_solver(secret_len=4, digits="0123", secret="0213", max_guesses=20)
    print("Solved secret", secret, "in", len(history), "guesses")
