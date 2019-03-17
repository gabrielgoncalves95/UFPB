# -*- coding: utf-8 -*-
import cv2
import copy
import numpy as np

def mostra_img(imagem):
    show_img = copy.copy(imagem)
    show_img = show_img.astype(np.uint8)
    cv2.imshow("Visualizacao", show_img)
    cv2.waitKey(0)


def convert_rgb_yuv(imagem):
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            px = imagem[i, j]
            y = (px[2] * 0.299) + (px[1] * 0.587) + (px[0] * 0.114)
            u = 0.492 * (px[0] - y)
            v = 0.877 * (px[2] - y)
            px = [y, u, v]
            imagem[i, j] = px


def convert_yuv_rgb(imagem):
    # imagem = imagem.astype(np.float32)
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            px = imagem[i, j]
            r = px[0] + (1.140 * px[2])
            if (r > 255):
                r = 255
            elif (r < 0):
                r = 0
            g = px[0] - (0.395 * px[1]) - (0.581 * px[2])
            if (g > 255):
                g = 255
            elif (g < 0):
                g = 0
            b = px[0] + (2.032 * px[1])
            if (b > 255):
                b = 255
            elif (b < 0):
                b = 0
            px = [b, g, r]
            imagem[i, j] = px


# aplica filtro vermelho
def red(imagem):
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            px = imagem[i, j]
            px[0] = 0
            px[1] = 0
            imagem[i, j] = px
    mostra_img(imagem)
    salvar_imagem(imagem)


# aplica filtro azul
def blue(imagem):
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            px = imagem[i, j]
            px[1] = 0
            px[2] = 0
            imagem[i, j] = px
    mostra_img(imagem)
    salvar_imagem(imagem)


# aplica filtro verde
def green(imagem):
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            px = imagem[i, j]
            px[0] = 0
            px[2] = 0
            imagem[i, j] = px
    mostra_img(imagem)
    salvar_imagem(imagem)


# aplica filtro negativo
def negativo_rgb(imagem):
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            px = imagem[i, j]
            px[0] = 255 - px[0]
            px[1] = 255 - px[1]
            px[2] = 255 - px[2]
            imagem[i, j] = px
    mostra_img(imagem)
    salvar_imagem(imagem)


def negativo_yuv(imagem):
    convert_rgb_yuv(imagem)
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            px = imagem[i, j]
            px[0] = 255 - px[0]
            imagem[i, j] = px
    convert_yuv_rgb(imagem)
    mostra_img(imagem)
    salvar_imagem(imagem)


# salva a imagem
def salvar_imagem(imagem):
    cv2.imwrite("editada.jpg", imagem)


# adicionar brilho rgb
def brilho_rgb(imagem):
    ad_brilho = raw_input("Digite o valor do brilho que deseja alterar em porcentagem (positivo +)(negativo -): ")
    modo = raw_input("Multiplicativo (*) ou Aditivo (+): ")
    ad_brilhom = float(ad_brilho)
    ad_brilho = float(ad_brilho) / 100
    if (ad_brilho > 1.0): ad_brilho = 1.0
    print (ad_brilho)
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            px = imagem[i, j]
            if (ad_brilho > 0):
                aux0 = 255 - px[0]
                aux1 = 255 - px[1]
                aux2 = 255 - px[2]
            elif (ad_brilho < 0):
                aux0 = (0 - px[0])*(-1)
                aux1 = (0 - px[1])*(-1)
                aux2 = (0 - px[2])*(-1)
            if (modo == '+'):
                px[0] = px[0] + (aux0 * float(ad_brilho))
                px[1] = px[1] + (aux1 * float(ad_brilho))
                px[2] = px[2] + (aux2 * float(ad_brilho))
            if (modo == '*'):
                px[0] = px[0] + (aux0 * float(ad_brilhom))
                if (px[0] > 255): px[0] = 255
                if (px[0] < 0): px[0] = 0
                px[1] = px[1] + (aux1 * float(ad_brilhom))
                if (px[1] > 255): px[1] = 255
                if (px[1] < 0): px[1] = 0
                px[2] = px[2] + (aux2 * float(ad_brilhom))
                if (px[2] > 255): px[2] = 255
                if (px[2] < 0): px[2] = 0
            imagem[i, j] = px
    mostra_img(imagem)
    salvar_imagem(imagem)


#BRILHO YUV FUNCIONANDO
def brilho_yuv(imagem):
    brilho = raw_input("Digite o valor do brilho que deseja alterar (positivo +) (negativo -): ")
    modo = raw_input("Multiplicativo (*) ou Aditivo (+): ")
    convert_rgb_yuv(imagem)
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            px = imagem[i, j]
            if (modo == '+'):
                px[0] = px[0] + float(brilho)
            if (modo == '*'):
                px[0] = px[0] * float(brilho)
            imagem[i, j] = px
    convert_yuv_rgb(imagem)
    mostra_img(imagem)
    salvar_imagem(imagem)


def mediana_rgb (imagem):
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
    salvar_imagem(imagem)
    mostra_img(imagem)



def mediana_yuv (imagem):
    convert_rgb_yuv(imagem)
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
    convert_yuv_rgb(imagem)
    salvar_imagem(imagem)
    mostra_img(imagem)


def media_rgb (imagem):
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
    salvar_imagem(imagem)
    mostra_img(imagem)


def media_yuv (imagem):
    convert_rgb_yuv(imagem)
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
    convert_yuv_rgb(imagem)
    salvar_imagem(imagem)
    mostra_img(imagem)


def contraste (imagem):
    media_img = copy.copy(imagem)
    desvio_img = copy.copy(imagem)
    cont_img = copy.copy(imagem)
    n = raw_input("Digite a ordem n: ")
    c = raw_input("Digite o contraste c: ")
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
            desvio_img[i, j] = np.std(aList, axis = 0)
            for m in range (0, 2):
                if (desvio_img[i, j, m] == 0):
                    cont_img[i, j, m] = imagem[i, j, m]
                elif (desvio_img[i, j, m] != 0):
                    cont_img[i, j, m] = media_img[i, j, m] + ((float(c)*(imagem[i, j, m] - media_img[i, j, m]))/desvio_img [i, j, m])

    imagem = copy.copy(cont_img)
    salvar_imagem(imagem)


def soma (imagem):
    imagem1 = cv2.imread("deserto.jpg")
    imagem1 = imagem1.astype(np.float32)
    imagem2 = cv2.imread("paisagem.jpg")
    imagem2 = imagem2.astype(np.float32)
    imagem = copy.copy(imagem1)
    for i in range(0, imagem.shape[0]):
        for j in range(0, imagem.shape[1]):
            imagem[i, j] = (imagem1[i, j] + imagem2[i, j])/2

    salvar_imagem(imagem)


name = raw_input("Digite o nome da imagem com a extensão correta ex: 'feijao.jpg': ")
imagem = cv2.imread(name)
imagem = imagem.astype(np.float32)
backup = copy.copy(imagem)

mostra_img(imagem)

opcao = 4500

while (opcao != 's'):
    cv2.destroyAllWindows()

    print "Digite 0 = filtro vermelho\nDigite 1 = filtro azul\nDigite 2 = filtro verde\nDigite 3 = filtro negativo rgb\nDigite 4 = filtro negativo yuv\nDigite 5 = brilho rgb\nDigite 6 = brilho yuv\nDigite 7 = restaurar imagem original\nDigite 8 = Aplicar Media RGB\nDigite 9 = Aplicar Mediana RGB\nDigite 10 = Aplicar contraste\nDigite 11 = Soma\nDigite 12 = Media YUV\nDigite 13 = Mediana YUV\nDigite s = sair"
    opcao = raw_input("Digite uma opcao: ")

    if opcao == '0':
        red(imagem)

    if opcao == '1':
        blue(imagem)

    if opcao == '2':
        green(imagem)

    if opcao == '3':
        negativo_rgb(imagem)

    if opcao == '4':
        negativo_yuv(imagem)

    if opcao == '5':
        brilho_rgb(imagem)

    if opcao == '6':
        brilho_yuv(imagem)

    if opcao == '7':
        imagem = copy.copy(backup)
        print "restaurou"

    if opcao == '8':
        media_rgb(imagem)

    if opcao == '9':
        mediana_rgb(imagem)

    if opcao == '10':
        contraste(imagem)

    if opcao == '11':
        soma(imagem)

    if opcao == '12':
        media_yuv(imagem)

    if opcao == '13':
        mediana_yuv(imagem)

    if opcao == '00':
        salvar_imagem(imagem)
