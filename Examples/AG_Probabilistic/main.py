import itertools as it


class ProbabilisticAutomata:
    def __init__(self, S: set[int], s_init: tuple[int], alpha: set, delta: set[tuple], L=None):
        """
        Initialize the ProbabilisticAutomata class with member variables.
        """
        self.S = S
        self.s_init = s_init
        self.alpha = alpha
        self.delta = delta
        self.L = L

    def __str__(self):
        """
        String representation of the ProbabilisticAutomata class.
        """
        return (
            "{"
            + f"\n  S={self.S}\n  s_init={self.s_init}\n  alpha={self.alpha}\n  delta={self.delta}\n  L={self.L}\n"
            + "}"
        )

    def compose(self, other):
        """
        Description goes here :)
        """
        states = set(it.product(self.S, other.S))
        s_init = (self.s_init, other.s_init)
        alpha = self.alpha | other.alpha
        delta = []  # not sure how this one works yet...
        L = []  # yeah also not sure how this one works...

        return ProbabilisticAutomata(states, s_init, alpha, delta, L)


M1 = ProbabilisticAutomata({0, 1, 2, 3}, (0), {}, [], [])
M2 = ProbabilisticAutomata({0, 1, 2, 3}, (0), {}, [], [])

Composition = M1.compose(M2)

print(M1)
print(M2)
print(Composition)
