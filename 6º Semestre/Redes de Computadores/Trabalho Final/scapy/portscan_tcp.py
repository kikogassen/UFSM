#!/usr/bin/env python

from scapy.all import *

IP_ROTEADOR = "10.0.2.2" #ip do roteador:
                         #No linux: "netstat -nr", coluna "Gateway"
                         #No windows: "ipconfig", linha "Gateway Padrao"

def main():
  	
    for porta in range (0, 1024):
        
		#Montando um pacote TCP SYN. Destino eh o IP do roteador da rede, e a porta a proxima do loop. Flag TCP "S" == "SYN"
		pacote = IP(dst=IP_ROTEADOR)/TCP(dport=80,flags='S')
        
		#Enviando o pacote e esperando pela resposta (timeout = 2 segundos)
		resposta = sr1(pacote , verbose=0, timeout=2)
		resultado = 0

		try:
			resultado = resposta["TCP"].flags # resultado = flags do pacote TCP recebido como resposta
		except:
			print("Sem resposta.")

		if resultado == 18: # se a flag do pacote respondido for "SYN ACK", a conexao foi feita com sucesso e a porta esta aberta
			print("PORTA " + str(porta) + " ABERTA.")
		else: #se nao, a porta esta fechada
			print("PORTA " + str(porta) + " FECHADA.")


if __name__ == '__main__':
    main()
