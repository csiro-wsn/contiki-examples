# -*- coding: utf-8 -*-

from sklearn import svm
from sklearn.datasets import load_iris, load_digits
from sklearn.cross_validation import train_test_split
from sklearn.metrics import accuracy_score, confusion_matrix
from sklearn.grid_search import GridSearchCV
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier


################################################################################
def iris_binary_data(rseed=42):
    # load the IRIS datasets
    #data = load_iris()
    data = load_digits()
    
    # Print summary
    print "No. Samples: ", data.data.shape[0]
    print "No. Features: ", data.data.shape[1]
    for i in range(0,max(data.target)+1):
        print "Class ", i , "samples: ", sum(data.target == i)
    return data

################################################################################
def compute_accuracy(clf, data, target):
    y = clf.predict(data)
    score = accuracy_score(target, y)
    return score

################################################################################
def print_accuracy(clf, data1, target1, data2, target2):
    print "- Training set", compute_accuracy(clf, data1, target1)
    print "- Testing set", compute_accuracy(clf, data2, target2)

################################################################################
def print_gridsearch_summary(clf, parameters):
    print "parameters:"
    print parameters
    
    print("Best parameters set:")
    best_parameters = clf.best_estimator_.get_params()
    for param_name in sorted(parameters.keys()):
        print("\t%s: %r" % (param_name, best_parameters[param_name]))


################################################################################        
def tune_svm_lin(data, target, rseed=42, verbose=1):
    print ""
    print "Tuning Linear SVM ..."
    print "--------------------------------------------------------------------------------"
    parameters = {
                  'C': [0.1, 1, 10, 100]
    }

    classifier = SVC(kernel='linear', random_state=rseed)
    clf = GridSearchCV(classifier, parameters, verbose=verbose)
    clf.fit(data, target)

    print_gridsearch_summary(clf, parameters)

    return clf

################################################################################
def tune_knn(data, target, rseed=42, verbose=1):
    print ""
    print "Tuning K-NN "
    print "--------------------------------------------------------------------------------"
    

################################################################################
def tune_decision_tree(data, target, rseed=42, verbose=1):
    print ""
    print "Tuning Decision Tree "
    print "--------------------------------------------------------------------------------"


################################################################################
def tune_random_forest(data, target, rseed=42, verbose=1):
    print ""
    print "Tuning Random Forest "
    print "--------------------------------------------------------------------------------"


################################################################################
if __name__ == "__main__":

    data = iris_binary_data()

    # Split to training and testing groups
    data1, data2, target1, target2 = train_test_split(data.data, \
                                                      data.target, \
                                                      test_size=0.8, \
                                                      random_state=42)
    # Train classifiers
    verbosity = 1
    
    clf_svm_lin = tune_svm_lin(data1, target1, verbose=verbosity)
    #clf_knn = tune_knn(data1, target1, verbose=verbosity)
    

    
    # Print performance
    print ""
    print "Classifier Performance"
    print "--------------------------------------------------------------------------------"
    print ""
   
    print ""
    print "Accuracy with linear SVM and parameter tuning:"
    print_accuracy(clf_svm_lin, data1, target1, data2, target2)

    print ""
    print "Accuracy with k-nn classifier with  parameter tuning:"

    print ""
    print "Accuracy with a decision tree and parameter tuning:"
   
    
    print ""
    print "Accuracy with a random forest and parameter tuning:"
   

   
