# -*- coding: utf-8 -*-

import pandas as pd
import numpy as np
from sklearn.linear_model import  LogisticRegression
from sklearn.svm import SVC

def csv_data(filename):
    df = pd.read_csv(filename)
    data = df.as_matrix(columns = ['Ambiant Temp C', 'Object Temp C'])
    #data = df.as_matrix(columns = [ 'Object Temp C'])
    return data


def predict_using_weights(X, weights, intercept):
    y = np.zeros(X.shape[0])
    
    for i in range(0,len(y)):
        y[i] = np.dot(X[i],weights) + intercept
        if y[i] >= 0:
            y[i] = 1
        else:
            y[i] = 0
    return  y

################################################################################
if __name__ == "__main__":

    # Make binary data from two reading files

    X_hot = csv_data('ir-sensor/record-power.csv')
    y_hot = np.ones(X_hot.shape[0])

    X_cold = csv_data('ir-sensor/record-desk.csv')
    y_cold = np.zeros(X_cold.shape[0])

    X = np.concatenate((X_hot, X_cold), axis=0)
    y = np.concatenate((y_hot, y_cold), axis=0)

   
    

    
