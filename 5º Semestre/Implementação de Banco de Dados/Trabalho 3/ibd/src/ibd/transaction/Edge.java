/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ibd.transaction;

/**
 *
 * @author kikog
 */
public class Edge {
    private Vertex[] edge;
    
    public Edge(Vertex source, Vertex destiny){
        edge = new Vertex[]{source, destiny};
    }

    public Vertex getSource() {
        return edge[0];
    }
    
    public Vertex getDestiny(){
        return edge[1];
    }
    
    public boolean hasTransaction(Transaction t){
        if (getSource().getTransaction().equals(t) || getDestiny().getTransaction().equals(t)){
            return true;
        }
        return false;
    }
}
