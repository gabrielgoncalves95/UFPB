# -*- coding: utf-8 -*-

# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import GridSearchCV, cross_val_score
from sklearn import metrics
import time

#Lista de acurácias e tempos de processamento
all_scores = []
all_times = []

#Função para testar os modelos com a função gridscore
def Classification_model_gridsearchCV(model, param_grid, data_X, data_y):
    start_time = time.time()
    # busca pela combinação de parâmetros que possui maior acurácia utilizando cross-validation
    clf = GridSearchCV(model,param_grid,cv=10,scoring="accuracy")
    # ajuste do modelo com os parâmetros encontrados
    clf.fit(data_X,data_y)  
    
    method_score = clf.best_score_*100
    processing_time = time.time() - start_time
    
    print("Melhor combinação de parâmetros encontrada:")
    print(clf.best_params_)
    print()
    print("Cross-validation score proporcionada por essa combinação de parâmetros: %s" %"{0:.3f}%".format(method_score))
    print("Processing time: %s seconds" % (processing_time))
    
    return method_score, processing_time


# Importando o dataset
dataset = pd.read_csv('dataproc.csv')

#Para utilizar só as variáveis relevantes
dataset = dataset.drop(['duration_ms', 'key', 'mode', 'time_signature'], axis=1)

X = dataset.iloc[:, :-1].values
y = dataset.iloc[:, 9].values


#Separação em amostra de treinamento e teste
from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.25)


##############Normalização##############################
from sklearn.preprocessing import StandardScaler
sc_X = StandardScaler()
X_train = sc_X.fit_transform(X_train)
X_test = sc_X.fit_transform(X_test)
X = sc_X.fit_transform(X)


#Classificador SVM
print("####################   SVM   ###########################")

start_time = time.time()
from sklearn.svm import SVC
classifier = SVC(kernel='poly', degree = 3)
classifier.fit(X_train, y_train)
processing_time = time.time() - start_time   

param_grid = [
              {'C': [1, 10, 100, 1000], # valores de parâmetros a serem testados
               'kernel': ['linear']
              },
              {'C':  [1, 10, 100, 1000],
               'kernel': ['poly'],
               'degree': [2, 3],
               },
              {'C': [1, 10, 100, 1000], 
               'gamma': [0.001, 0.0001], 
               'kernel': ['rbf']
              },
]


sc,tm = Classification_model_gridsearchCV(classifier,param_grid,X,y)
all_scores.append(sc)
all_times.append(tm)

        
#teste de predição
y_pred = classifier.predict(X_test)
   
accuracy = metrics.accuracy_score(y_pred, y_test)  # cálculo da acurácia a partir dos resultados obtidos
print("Accuracy : %s" % "{0:.3%}\n".format(accuracy))   

'''
#CROSS VALIDATION#############################
scores = cross_val_score(classifier, X, y, cv=5)
for i in range(0,5):
    print("Cross-Validation Score : %s" % "{0:.3%}".format(scores[i]))
    
print("Cross-Validation Mean Score : %s" % "{0:.3%}\n".format(np.mean(scores)))

print("Processing time: %s seconds\n" % (processing_time))
'''
#matriz de confusão
from sklearn.metrics import confusion_matrix
cm = confusion_matrix(y_test, y_pred)
print("Matriz de Confusão")
print (cm)



#Classificador KNN
print("####################   KNN   ###########################")
start_time = time.time()

from sklearn.neighbors import KNeighborsClassifier

classifier = KNeighborsClassifier(n_neighbors = 5)
classifier.fit(X_train, y_train)
processing_time = time.time() - start_time   

k_range = list(range(1, 30))  # valores de parâmetros a serem testados
leaf_size = list(range(1,30))
weight_options = ['uniform', 'distance']
param_grid = {'n_neighbors': k_range, 'leaf_size': leaf_size, 'weights': weight_options}


sc,tm = Classification_model_gridsearchCV(classifier,param_grid,X,y)
all_scores.append(sc)
all_times.append(tm)
 
        
#teste de predição
y_pred = classifier.predict(X_test)
   
accuracy = metrics.accuracy_score(y_pred, y_test)  # cálculo da acurácia a partir dos resultados obtidos
print("Accuracy : %s" % "{0:.3%}\n".format(accuracy))   

'''
#CROSS VALIDATION#############################
scores = cross_val_score(classifier, X, y, cv=5)
for i in range(0,5):
    print("Cross-Validation Score : %s" % "{0:.3%}".format(scores[i]))
    
print("Cross-Validation Mean Score : %s" % "{0:.3%}\n".format(np.mean(scores)))
print("Processing time: %s seconds\n" % (processing_time))
'''

#matriz de confusão
from sklearn.metrics import confusion_matrix
cm = confusion_matrix(y_test, y_pred)
print("Matriz de Confusão")
print (cm)


#CLassificador Random forest
print("####################   RANDOM FOREST   ###########################")
start_time = time.time()

from sklearn.ensemble import RandomForestClassifier

classifier = RandomForestClassifier()
classifier.fit(X_train, y_train)
processing_time = time.time() - start_time   


param_grid = {"n_estimators": [10,20,40,60],  # valores de parâmetros a serem testados
              "max_depth": [3, None],
              "max_features": [1,6],
              "min_samples_split": [2,6,8,10],
              "min_samples_leaf": [1, 3, 10],
              "criterion": ["gini", "entropy"]}


sc,tm = Classification_model_gridsearchCV(classifier,param_grid,X,y)
all_scores.append(sc)
all_times.append(tm)

        
#teste de predição
y_pred = classifier.predict(X_test)
   
accuracy = metrics.accuracy_score(y_pred, y_test)  # cálculo da acurácia a partir dos resultados obtidos
print("Accuracy : %s" % "{0:.3%}\n".format(accuracy))   

'''
#CROSS VALIDATION#############################
scores = cross_val_score(classifier, X, y, cv=5)
for i in range(0,5):
    print("Cross-Validation Score : %s" % "{0:.3%}".format(scores[i]))
    
print("Cross-Validation Mean Score : %s" % "{0:.3%}\n".format(np.mean(scores)))
print("Processing time: %s seconds\n" % (processing_time))
'''

#matriz de confusão
from sklearn.metrics import confusion_matrix
cm = confusion_matrix(y_test, y_pred)
print("Matriz de Confusão")
print (cm)



print("###############   ÁRVORE DE DECISÃO   ####################")
start_time = time.time()

from sklearn.tree import DecisionTreeClassifier

param_grid = {'max_features': ['auto', 'sqrt', 'log2'],  # valores de parâmetros a serem testados
              'min_samples_split': [2,3,4,5,6,7,8,9,10], 
              'min_samples_leaf':[2,3,4,5,6,7,8,9,10] }
classifier = DecisionTreeClassifier()
classifier.fit(X_train, y_train)
processing_time = time.time() - start_time   


sc,tm = Classification_model_gridsearchCV(classifier,param_grid,X,y)
all_scores.append(sc)
all_times.append(tm)
 
        
#teste de predição
y_pred = classifier.predict(X_test)
   
accuracy = metrics.accuracy_score(y_pred, y_test)  # cálculo da acurácia a partir dos resultados obtidos
print("Accuracy : %s" % "{0:.3%}\n".format(accuracy))   

'''
#CROSS VALIDATION#############################
scores = cross_val_score(classifier, X, y, cv=5)
for i in range(0,5):
    print("Cross-Validation Score : %s" % "{0:.3%}".format(scores[i]))
    
print("Cross-Validation Mean Score : %s" % "{0:.3%}\n".format(np.mean(scores)))
print("Processing time: %s seconds\n" % (processing_time))
'''

#matriz de confusão
from sklearn.metrics import confusion_matrix
cm = confusion_matrix(y_test, y_pred)
print("Matriz de Confusão")
print (cm)




#Salva tabela com resultados
raw_data = {
         "Método": ["SVM", "KNN", "Random Forest", "Arvore de Decisão"],
         "Acurácia(%)": all_scores,
         "Tempo(s)": all_times
        }
        
dfr = pd.DataFrame(raw_data, columns = ['Método', 'Acurácia(%)','Tempo(s)'])
dfr
