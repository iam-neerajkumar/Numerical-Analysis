import matplotlib.pyplot as plt

# Read the data from the file
def read_data(file_name):
    iterations = []
    residuals = []
    
    with open(file_name, 'r') as file:
        for line in file:
            data = line.split()
            if len(data) == 2:
                iterations.append(int(data[0]))
                residuals.append(float(data[1]))
    
    return iterations, residuals

# Plot 
def plot_convergence(iterations, residuals):
    plt.plot(iterations, residuals, marker='o')
    plt.xlabel('Iteration')
    plt.ylabel('Residual')
    plt.title('Convergence Plot: Iteration vs Residual')
    plt.grid(True)
    plt.show()

# Main function
def main():
    file_name = 'a_iterationVSresidual.txt'  # Replace with your file name
    iterations, residuals = read_data(file_name)
    
    if iterations and residuals:
        plot_convergence(iterations, residuals)

if __name__ == "__main__":
    main()
