package classe;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author kikog
 */
public class Usuario {
    private int id_usuario;
    private int id_cargo;
    private String nome_usuario;
    private String nome_cargo;

    public String getNome_cargo() {
        return nome_cargo;
    }

    public void setNome_cargo(String nome_cargo) {
        this.nome_cargo = nome_cargo;
    }

    public Usuario(int id_usuario, int id_cargo, String nome_usuario, String nome_cargo) {
        this.id_usuario = id_usuario;
        this.id_cargo = id_cargo;
        this.nome_usuario = nome_usuario;
        this.nome_cargo = nome_cargo;
    }

    public String getNome_usuario() {
        return nome_usuario;
    }

    public void setNome_usuario(String nome_usuario) {
        this.nome_usuario = nome_usuario;
    }

    public int getId_usuario() {
        return id_usuario;
    }

    public void setId_usuario(int id_usuario) {
        this.id_usuario = id_usuario;
    }

    public int getId_cargo() {
        return id_cargo;
    }

    public void setId_cargo(int id_cargo) {
        this.id_cargo = id_cargo;
    }
}
