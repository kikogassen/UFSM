#!/usr/bin/env python
from scapy.all import *


def main():

	#Montando o pacote
	pacote_ping = IP(dst="8.8.8.8") / ICMP()

	#Envia o pacote e aguarda a primeira resposta, utilizando sr1(). Resposta armazenada na variavel "resposta"
	resposta = sr1(pacote_ping)

	print("SUMARIO : " + resposta[0].summary() ) # sumario dos pacotes recebidos

	print("\nENDERECO DE ORIGEM DO PACOTE: " + resposta.src) # campo "src" do protocolo IP do pacote respondido
	print("\nENDERECO DE DESTINO DO PACOTE (meu IP):" + resposta.dst) # campo "dst" do protocolo IP do pacote respondido(meu proprio endereco)

	print("\nPACOTE COMPLETO:\n" )
	resposta.show() # printa TODOS os campos do pacote recebido


if __name__ == '__main__':
    main()
