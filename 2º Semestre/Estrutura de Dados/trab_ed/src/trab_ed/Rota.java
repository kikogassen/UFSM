package trab_ed;

import java.util.LinkedList;

public class Rota{
    private LinkedList<Vertice> vertices;

    public Rota() {
        vertices = new LinkedList<Vertice>();
    }
    
    public void mostraRota(){
        for (int x=0;x<vertices.size();x++){
            System.out.print(vertices.get(x).getNome() + "-");
        }
        System.out.println(".");
    }
    
    public int distanciaPercorrida(Grafo g){
        int distancia = 0;
        for (int x=1;x<vertices.size();x++){
            distancia += g.getMatriz()[g.retornaIndiceNomeVertice(vertices.get(x-1).getNome())][g.retornaIndiceNomeVertice(vertices.get(x).getNome())];
        }
        return distancia;
    }
    
    public boolean EhPossivel(Grafo g){
        int gasolinaDisponivel = 100;
        for (int x=1;x<vertices.size();x++){
            gasolinaDisponivel -= g.getMatriz()[g.retornaIndiceNomeVertice(vertices.get(x-1).getNome())][g.retornaIndiceNomeVertice(vertices.get(x).getNome())];
            if (gasolinaDisponivel < 0){
                return false;
            }
            if (vertices.get(x).isPosto()){
                gasolinaDisponivel = 100;
            }
        }
        return true;
        
    }
    
    public boolean rotaContemEsseVertice(Vertice v){
        for (int x=0;x<vertices.size();x++){
            if (vertices.get(x).getNome().equals(v.getNome())){
                return true;
            }
        }
        return false;
    }
    
    public void adicionaVertice(Vertice v){
        vertices.add(v);
    }

    public LinkedList<Vertice> getVertices() {
        return vertices;
    }

    public void setVertices(LinkedList<Vertice> vertices) {
        this.vertices = vertices;
    }
}
