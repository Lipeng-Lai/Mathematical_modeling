import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

# Load the dataset
dataset = pd.read_excel('./问题2数据.xlsx')
X = dataset.iloc[:, 0:8].values
y = dataset.iloc[:, 8].values

# Define a range of test set ratios to test
test_ratios = np.arange(0.1, 1.0, 0.1)

# Initialize a list to store accuracies for each test ratio
accuracies = []

# Fix the K value to 30
k = 30

# Train the KNN classifier for different test set ratios and compute accuracies
for test_ratio in test_ratios:
    # Split the data into training and testing sets
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=test_ratio, random_state=0)
    
    # Standardize the features
    sc = StandardScaler()
    X_train = sc.fit_transform(X_train)
    X_test = sc.transform(X_test)
    
    # Initialize the KNN classifier
    classifier = KNeighborsClassifier(n_neighbors=k, metric='euclidean')
    
    # Train the classifier and make predictions
    classifier.fit(X_train, y_train)
    y_pred = classifier.predict(X_test)
    
    # Compute and store the accuracy for the current test ratio
    ac = accuracy_score(y_test, y_pred)
    accuracies.append(ac)

# Plot the accuracy vs. test set ratio graph
plt.plot(test_ratios, accuracies, marker='o')
plt.xlabel('Test Set Ratio')
plt.ylabel('Accuracy')
plt.title('KNN Accuracy vs. Test Set Ratio (K = 30)')
plt.grid(True)
plt.show()
