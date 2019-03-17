# -*- coding: utf-8 -*-

import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np



dataset = pd.read_csv('data.csv')
dataset.info()

#mostra a distribuição de classes
sns.countplot(dataset['class'], label = "Quantidade")

#Exclui dados duplicados
dataset = dataset.drop_duplicates(subset=None, keep='first', inplace=False)

#Exclui colunas irrelevantes
dataset = dataset.drop(['analysis_url', 'id', 'track_href', 'type', 'uri', ], axis=1)

#Salva dataset processado
dataset.to_csv("dataproc.csv", index_label=False, encoding='utf-8')

#TODOS OS DADOS SCATTERPLOT################################################################
g = sns.pairplot(dataset, hue="class")

sns.distplot( dataset["acousticness"] , color="blue", label="acousticness")
sns.distplot( dataset["class"] , color="red", label="class")
sns.plt.legend()

#Divide dados por classe
d1=dataset[dataset['class'] ==1]
d0=dataset[dataset['class'] ==0]

#Lista de atributos
features = list(dataset.columns[:])

#HISTOGRAMAS##############################################################################
plt.rcParams.update({'font.size': 8})
fig, axes = plt.subplots(nrows=7, ncols=2, figsize=(15,15))
axes = axes.ravel()
for idx,ax in enumerate(axes):
    ax.figure
    binwidth= (max(dataset[features[idx]]) - min(dataset[features[idx]]))/50
    ax.hist([d1[features[idx]],d0[features[idx]]], bins=np.arange(min(dataset[features[idx]]), max(dataset[features[idx]]) + binwidth, binwidth) , alpha=0.5,stacked=True, normed = True, label=['1','0'],color=['r','b'])
    ax.legend(loc='upper right')
    ax.set_title(features[idx])
plt.tight_layout()
plt.show()