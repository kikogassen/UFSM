#!/usr/bin/env python
from scapy.all import sniff

def trata_pacote(pacote):
    
	#FAZER O QUE FOR PRECISO COM O PACOTE
	#Exemplo: 
		#if TCP in pacote: # Verifica se o pacote utiliza o protocolo TCP
		#if ICMP in pacote: # Verifica se o pacote utiliza o protocolo ICMP
		#if pacote.src == "X.X.X.X": # Verifica se o pacote eh proveniente de um determinado IP de origem
		#...

    pacote.show() #Mostra o pacote completo
    print("\n=============================================\n")


def main():
    sniff(iface = "enp0s3", prn = lambda x: trata_pacote(x), filter="") 

if __name__ == '__main__':
    main()
