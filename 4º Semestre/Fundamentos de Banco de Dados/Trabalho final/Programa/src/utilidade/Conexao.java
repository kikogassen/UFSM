package utilidade;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;

/**
 *
 * @author Kiko
 */
public class Conexao {
    Connection conexao;
    Statement st;
    ResultSet rs;

    public Conexao() throws SQLException{
        String dados[]= abreDados();
        String host = "/" + dados[0];
        String banco = "/" + dados[1];
        String login = dados[2];
        String senha = dados[3];
        String url = "jdbc:mysql:/"+host+banco;
        
        conexao = DriverManager.getConnection(url, login, senha);
    }
    
    private String[] abreDados(){
        Cript crip = new Cript();
        try {
            FileReader fr = new FileReader("dados.txt");
            BufferedReader br = new BufferedReader(fr);
            String[] dados = new String[4];
            for (int x=0;x<4;x++){
                dados[x] = crip.descrip(br.readLine());
            }
            return dados;
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null, "Exception: "+ex, "Estacionamento Universitário", JOptionPane.ERROR_MESSAGE);
            return null;
        }
    }
    
    public ResultSet select(String query) throws SQLException {
        st=conexao.createStatement();
        st.executeQuery(query);
        rs=st.getResultSet();
        return rs;
    }
    
    public void insert (String query) throws SQLException {
        st=conexao.createStatement();
        st.executeUpdate(query);
    }
}
