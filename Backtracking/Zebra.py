from itertools import permutations


def zebra_puzzle():
    """Classic 5-house logic puzzle. Returns (water_drinker_house, zebra_owner_house)
    as indices into the 'houses' orderings, plus prints the answer."""
    
    houses = [1, 2, 3, 4, 5]
    orderings = list(permutations(houses))

    def right_of(a, b):
        return a - b == 1

    def next_to(a, b):
        return abs(a - b) == 1

    for (red, green, ivory, yellow, blue) in orderings:
        if not right_of(green, ivory):
            continue
        for (english, spaniard, ukrainian, norwegian, japanese) in orderings:
            if english != red:
                continue
            if norwegian != 1:
                continue
            if not next_to(norwegian, blue):
                continue
            for (coffee, tea, milk, oj, water) in orderings:
                if coffee != green:
                    continue
                if ukrainian != tea:
                    continue
                if milk != 3:
                    continue
                for (oldgold, kools, chesterfield, luckystrike, parliament) in orderings:
                    if kools != yellow:
                        continue
                    if luckystrike != oj:
                        continue
                    if japanese != parliament:
                        continue
                    for (dog, snails, fox, horse, zebra) in orderings:
                        if oldgold != snails:
                            continue
                        if not next_to(chesterfield, fox):
                            continue
                        if not next_to(kools, horse):
                            continue
                        if spaniard != dog:
                            continue
                        # All 15 constraints satisfied
                        water_house = water
                        zebra_house = zebra
                        nationalities = {english: "Englishman", spaniard: "Spaniard",
                                          ukrainian: "Ukrainian", norwegian: "Norwegian",
                                          japanese: "Japanese"}
                        return {
                            "water_drinker": nationalities[water_house],
                            "zebra_owner": nationalities[zebra_house],
                        }
    return None

if __name__ == "__main__":
    print("ZEBRA PUZZLE")
    print(zebra_puzzle())