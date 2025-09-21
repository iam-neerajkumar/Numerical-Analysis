import matplotlib.pyplot as plt

# Data 
terms = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
relative_error = [
    0.5708900069, 0.0751896650, 0.0045267264, 0.0001569824, 
    0.0000035449, 0.0000000563, 0.0000001273, 0.0000003094, 
    0.0000077963, 0.0000564139
]

plt.figure(figsize=(8, 6))

plt.plot(terms, relative_error, marker='o', linestyle='-', color='b', label='Relative Error')

# labels and title
plt.xlabel('Terms')
plt.ylabel('Relative Error')
plt.title('Relative Error vs Terms')

# grid and legend
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.show()
