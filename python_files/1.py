#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Sample code of HW4, Problem 3
"""

import matplotlib.pyplot as plt
import pickle
import numpy as np
from scipy.stats import pearsonr
from scipy import linalg


myfile = open('hw4_p3_data.pickle', 'rb')
mydict = pickle.load(myfile)

X_train = mydict['X_train']
X_test = mydict['X_test']
Y_train = mydict['Y_train']
Y_test = mydict['Y_test']

predictive_mean = np.empty(X_test.shape[0])
predictive_std = np.empty(X_test.shape[0])

sigma = 0.1
sigma_f = 1.0
ls = 0.06

#-------- Your code (~10 lines) ---------
delta = 0
xi_count = 0
xj_count = 0
arr_count = 0
covariance_term1 = np.zeros((1, len(X_train)))
covariance_term2 = np.zeros((len(X_train), len(X_train) ))
# for xi in X_test:
term1 = np.square(sigma_f)

for xi in X_test:
    xi_count = 0
    xj_count = 0
    for xj in X_train:
        if xi_count == xj_count:
            delta = 1
        else:
            delta = 0
        term2 = np.exp(-(np.square(xi-xj)) / (2 * np.square(ls)))
        term3 = np.square(sigma) * delta
        cal1 = term1*term2+term3

        covariance_term1[0, xj_count] = cal1
        xj_count += 1

    xi_count = 0
    xj_count = 0
    for xi in X_train:
        xj_count = 0
        for xj in X_train:
            if xi_count == xj_count:
                delta = 1
            else:
                delta = 0
            term2 = np.exp(-(np.square(xi-xj)) / (2 * np.square(ls)))
            term3 = np.square(sigma) * delta
            cal2 = term1*term2+term3
            covariance_term2[xi_count, xj_count] = cal2

            xj_count += 1
        xi_count += 1

    covariance_term3 = np.square(sigma) * np.identity(len(X_train))
    value = np.dot(np.dot(covariance_term1, np.linalg.inv(covariance_term2 + covariance_term3)),np.transpose(Y_train))
    predictive_mean[arr_count] = value

    variance_term1 = term1 + np.square(sigma)
    a = np.linalg.inv(covariance_term2 + covariance_term3)
    b = np.dot(np.dot(covariance_term1, a),np.transpose(covariance_term1))
    variance = variance_term1 - b
    predictive_std[arr_count] = np.sqrt(variance)

    arr_count += 1

print(predictive_mean)
print(predictive_std)

#---------- End of your code -----------

# Optional: Visualize the training data, testing data, and predictive distributions
fig = plt.figure()
plt.plot(X_train, Y_train, linestyle='', color='b', markersize=3, marker='+',label="Training data")
plt.plot(X_test, Y_test, linestyle='', color='orange', markersize=2, marker='^',label="Testing data")
plt.plot(X_test, predictive_mean, linestyle=':', color='green')
plt.fill_between(X_test.flatten(), predictive_mean - predictive_std, predictive_mean + predictive_std, color='green', alpha=0.13)
plt.fill_between(X_test.flatten(), predictive_mean - 2*predictive_std, predictive_mean + 2*predictive_std, color='green', alpha=0.07)
plt.fill_between(X_test.flatten(), predictive_mean - 3*predictive_std, predictive_mean + 3*predictive_std, color='green', alpha=0.04)
plt.xlabel("X")
plt.ylabel("Y")
plt.show()
