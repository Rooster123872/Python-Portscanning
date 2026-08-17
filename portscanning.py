#!/usr/bin/python

import socket, sys

print ("==== ROOSTER ===")
print ("Portscaning em Python")
print ("======  1.0 VERSION ==========")

ip = input("Digite o IP que você quer verificar as portas abertas ")
portas_totais = range(1, 6500)

for porta in portas_totais:
    meusocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    meusocket.settimeout(0.1)
    res = meusocket.connect_ex((ip,porta))
    if res == 0:
        print (" Porta ", porta, "ABERTA! [*] ")
    meusocket.close()
    
    ## OBRIGADO POR TER LIDO MEU SCRIPT NO GIT HUb
