/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package classe;

/**
 *
 * @author kikog
 */
public class Estacionada {

    private String placa_veiculo;
    private String nome_estacionamento;
    private String nome_usuario;
    private String datahora_entrada;
    private String datahora_saida;

    public Estacionada(String placa_veiculo, String nome_estacionamento, String nome_usuario, String datahora_entrada, String datahora_saida) {
        this.placa_veiculo = placa_veiculo;
        this.nome_estacionamento = nome_estacionamento;
        this.nome_usuario = nome_usuario;
        this.datahora_entrada = datahora_entrada;
        if (datahora_saida == null) {
            this.datahora_saida = "";
        } else {
            this.datahora_saida = datahora_saida;
        }
    }

    public String getDatahora_saida() {
        if (datahora_saida.equals("")) {
            return "";
        } else {
            String[] data = datahora_saida.split(" ")[0].split("-");
            String retorno = data[2] + "/" + data[1] + "/" + data[0] + " - " + datahora_saida.split(" ")[1].replace(".0", "");
            return retorno;
        }
    }

    public void setDatahora_saida(String datahora_saida) {
        this.datahora_saida = datahora_saida;
    }

    public String getPlaca_veiculo() {
        return placa_veiculo;
    }

    public void setPlaca_veiculo(String placa_veiculo) {
        this.placa_veiculo = placa_veiculo;
    }

    public String getNome_estacionamento() {
        return nome_estacionamento;
    }

    public void setNome_estacionamento(String nome_estacionamento) {
        this.nome_estacionamento = nome_estacionamento;
    }

    public String getNome_usuario() {
        return nome_usuario;
    }

    public void setNome_usuario(String nome_usuario) {
        this.nome_usuario = nome_usuario;
    }

    public String getDatahora_entrada() {
        String[] data = datahora_entrada.split(" ")[0].split("-");
        String retorno = data[2] + "/" + data[1] + "/" + data[0] + " - " + datahora_entrada.split(" ")[1].replace(".0", "");
        return retorno;
    }

    public void setDatahora_entrada(String datahora_entrada) {
        this.datahora_entrada = datahora_entrada;
    }
}
