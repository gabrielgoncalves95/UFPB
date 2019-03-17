# -*- coding: utf-8 -*-
import cv2
import copy
import numpy as np


def mostra_imagem(imagem, title = 'Imagem'):
    cv2.imshow(title, imagem)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def salvar_imagem(imagem):
    cv2.imwrite("noise.jpg", imagem)


def salvar_imagem1(imagem):
    cv2.imwrite("mediana.jpg", imagem)


def salvar_imagem2(imagem):
    cv2.imwrite("media.jpg", imagem)


def salt_n_pepper(imagem, pad=200):
    imagem = imagem.astype(np.float32)
    noise = np.random.randint(pad, size=(imagem.shape[0], imagem.shape[1], 1))
    imagem = np.where(noise == 0, 0, imagem)
    imagem = np.where(noise == (pad - 1), 255, imagem)
    imagem = imagem.astype(np.uint8)
    salvar_imagem(imagem)
    return imagem



def mediana (imagem):
    media_img = copy.copy(imagem)
    n = raw_input("Digite a ordem n: ")
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            aList = []
            va_i = i-int(n)
            va_f = i+int(n)
            vb_i = j-int(n)
            vb_f = j+int(n)
            for k in range (va_i, va_f):
                for l in range (vb_i, vb_f):
                    if (k < 0) or (k >= imagem.shape[0]) or (l < 0) or (l >= imagem.shape[1]): continue
                    else:
                        aList.append(imagem[k, l])
            media_img[i, j] = np.median(aList, axis = 0)
    imagem = copy.copy(media_img)
    salvar_imagem1(imagem)
    #mostra_imagem(imagem)


def media (imagem):
    media_img = copy.copy(imagem)
    n = raw_input("Digite a ordem n: ")
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            aList = []
            va_i = i-int(n)
            va_f = i+int(n)
            vb_i = j-int(n)
            vb_f = j+int(n)
            for k in range (va_i, va_f):
                for l in range (vb_i, vb_f):
                    if (k < 0) or (k >= imagem.shape[0]) or (l < 0) or (l >= imagem.shape[1]): continue
                    else:
                        aList.append(imagem[k, l])
            media_img[i, j] = np.average(aList, axis = 0)
    imagem = copy.copy(media_img)
    salvar_imagem2(imagem)
    #mostra_imagem(imagem)


imagem = cv2.imread("castelo.jpg")

imagem = salt_n_pepper(imagem)
mostra_imagem(imagem, 'Imagem com Salt & Pepper')

media(imagem)
mediana(imagem)

