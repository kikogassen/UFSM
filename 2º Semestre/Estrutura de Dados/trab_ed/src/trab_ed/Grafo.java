package trab_ed;

import java.util.LinkedList;

public class Grafo {
    private int[][] matriz;
    private LinkedList<Vertice> vertices;
    private int qtde_vertices;

    public Grafo(int qtde_vertices) {
        this.matriz = new int[qtde_vertices][qtde_vertices];
        this.qtde_vertices = qtde_vertices;
        this.vertices = new LinkedList<Vertice>();
        
        for (int x=0;x<qtde_vertices;x++){
            for (int y=0;y<qtde_vertices;y++){
                if (x!=y){
                    this.matriz[x][y] = -1;
                } else {
                    this.matriz[x][y] = 0;
                }
            }
        }
    }
    
    public LinkedList<Vertice> retornaVerticesSaida(Vertice v){
        LinkedList<Vertice> verticesSaida = new LinkedList<Vertice>();
        int indice = -1;
        
        for (int x=0;x<qtde_vertices;x++){
            if (vertices.get(x).equals(v)){
                indice = x;
            }
        }
        
        for (int x=0;x<qtde_vertices;x++){
            if (matriz[indice][x] != -1){
                verticesSaida.add(vertices.get(x));
            }
        }
        
        return verticesSaida;
    }
    
    public void adicionaVertice(String nome, boolean posto){
        Vertice v = new Vertice(nome, posto);
        vertices.add(v);
    }
    
    public int retornaIndiceNomeVertice(String nome){
        for (int x=0;x<qtde_vertices;x++){
            //System.out.println("X: " + x + ", ");
            if (nome.equals(vertices.get(x).getNome())){
                return x;
            }
        }
        return -1;
    }
    
    public void adicionaAresta(int indice0, int indice1, int peso){
        matriz[indice0][indice1] = peso;
        matriz[indice1][indice0] = peso;
    }

    public int getQtde_vertices() {
        return qtde_vertices;
    }

    public void setQtde_vertices(int qtde_vertices) {
        this.qtde_vertices = qtde_vertices;
    }

    public int[][] getMatriz() {
        return matriz;
    }

    public void setMatriz(int[][] matriz) {
        this.matriz = matriz;
    }

    public LinkedList<Vertice> getVertices() {
        return vertices;
    }

    public void setVertices(LinkedList<Vertice> vertices) {
        this.vertices = vertices;
    }
}
