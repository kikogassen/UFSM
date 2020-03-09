package trab_ed;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Scanner;

public class Trab_ed {

    public static void main(String[] args){
        Scanner entrada = new Scanner(System.in);
        
        Grafo g = le_arquivo();
        
        mostra_cidades(g);
        System.out.println("Qual o índice da cidade inicial?");
        int inicio = entrada.nextInt();
        System.out.println("Qual o índice da cidade final?");
        int fim = entrada.nextInt();
        
        if (inicio < 0 || inicio >= g.getQtde_vertices() || fim < 0 || fim >= g.getQtde_vertices() || inicio==fim){
            System.out.println("Valores invalidos!");
            System.exit(0);
        }
        
        calcula_resultado(g, g.getVertices().get(inicio), g.getVertices().get(fim));
    }
    
    private static void mostra_cidades(Grafo g){
        for (int x=0;x<g.getQtde_vertices();x++){
            if (g.getVertices().get(x).isPosto()){
                System.out.println("(" + x + ") " + g.getVertices().get(x).getNome() + " - tem posto");
            } else {
                System.out.println("(" + x + ") " + g.getVertices().get(x).getNome() + " - não tem posto");
            }
        }
    }
    
    private static Rota retorna_melhor_rota(Grafo g, LinkedList<Rota> listaRotas){
        Rota melhorRota = null;
        
        for (int x=0;x<listaRotas.size();x++){
            // para cada rota, verificar se ela eh possivel, depois verificar se ela eh a melhor
            if (listaRotas.get(x).EhPossivel(g)){
                if (melhorRota == null){
                    melhorRota = listaRotas.get(x);
                } else {
                    if (listaRotas.get(x).distanciaPercorrida(g)<melhorRota.distanciaPercorrida(g)){
                        melhorRota = listaRotas.get(x);
                    }
                }
            }
        }
        
        return melhorRota;
    }
    
    private static void calcula_resultado(Grafo g, Vertice inicio, Vertice fim){
        //monta a lista de possiveis rotas
        LinkedList<Rota> listaRotas = new LinkedList<Rota>();
        Rota rotaPrevia = new Rota();
        rotaPrevia.adicionaVertice(inicio);
        preenche_lista_rotas(g, inicio, fim, rotaPrevia, listaRotas);
        if (listaRotas.size()==0){
            System.out.println("Não existe rodovia conectando as cidades " + inicio.getNome() + " e " + fim.getNome());
            System.exit(0);
        }
        Rota melhorRota = retorna_melhor_rota(g, listaRotas);
        mostra_melhor_rota(melhorRota, g, inicio, fim);
    }
    
    private static void mostra_melhor_rota(Rota rota, Grafo g, Vertice inicio, Vertice fim){
        if (rota == null){
            System.out.println("As rodovias conectando as cidades " + inicio.getNome() + " e " + fim.getNome() + " não possuem postos de combustível suficientes para manter o carro abastecido durante a viagem");
            System.exit(0);
        }
        int[] abastecimentos = retorna_vetor_abastecimentos(rota, g);
        System.out.println("O roteiro de viagem que vai de " + inicio.getNome() + " até " + fim.getNome() + " é:");
        for (int x=0;x<rota.getVertices().size();x++){
            if (x>0){
                if (abastecimentos[x-1]==0){
                    System.out.println("cidade " + rota.getVertices().get(x).getNome() + " (sem paradas)");
                } else {
                    System.out.println("cidade " + rota.getVertices().get(x).getNome() + " (parada para abastecer " + (float)abastecimentos[x-1]/10 + " litros)");
                }
            } else {
                System.out.println("cidade " + rota.getVertices().get(x).getNome() + " (sem paradas)");
            }
        }
    }
    
    private static int[] retorna_vetor_abastecimentos(Rota rota, Grafo g){
        int[] abastecimentos = new int[rota.getVertices().size()-1];
        for (int x=0;x<abastecimentos.length;x++){
            abastecimentos[x] = 0;
        }
        
        int gasolina = 100;
        int distancia_restante = rota.distanciaPercorrida(g);
        
        for (int x=1;x<rota.getVertices().size();x++){
            gasolina -= g.getMatriz()[g.retornaIndiceNomeVertice(rota.getVertices().get(x-1).getNome())][g.retornaIndiceNomeVertice(rota.getVertices().get(x).getNome())];
            distancia_restante -= g.getMatriz()[g.retornaIndiceNomeVertice(rota.getVertices().get(x-1).getNome())][g.retornaIndiceNomeVertice(rota.getVertices().get(x).getNome())];
            if (rota.getVertices().get(x).isPosto()){
                if (gasolina<distancia_restante){ // se não tem gasolina pra ir ate o final
                    int qto_gasolina_falta = distancia_restante - gasolina;
                    int espaco_tanque = 100-gasolina;
                    if (qto_gasolina_falta>espaco_tanque){ // se a distancia que falta for maior que o espaco livre do tanque
                        abastecimentos[x-1] = espaco_tanque;
                        gasolina = 100;
                    } else { // se pode abastecer o que falta pra terminar
                        abastecimentos[x-1] = qto_gasolina_falta;
                        gasolina += qto_gasolina_falta;
                    }
                }
            }
        }
        
        return abastecimentos;
    }
    
    private static void preenche_lista_rotas(Grafo g, Vertice inicio, Vertice fim, Rota rotaPrevia, LinkedList<Rota> listaRotas){
        LinkedList<Vertice> verticesSaida = g.retornaVerticesSaida(inicio);
        for (int x=0;x<verticesSaida.size();x++){
            Rota rotaTmp = new Rota();
            for (int y=0;y<rotaPrevia.getVertices().size();y++){
                rotaTmp.getVertices().add(new Vertice(rotaPrevia.getVertices().get(y).getNome(), rotaPrevia.getVertices().get(y).isPosto()));
            }
            if (!rotaTmp.rotaContemEsseVertice(verticesSaida.get(x))){
                rotaTmp.adicionaVertice(verticesSaida.get(x));
                if (verticesSaida.get(x).equals(fim)){
                    listaRotas.add(rotaTmp);
                } else {
                    preenche_lista_rotas(g, verticesSaida.get(x), fim, rotaTmp, listaRotas);
                }
            }
        }
    }
    
    private static Grafo le_arquivo(){
        boolean vertice = true;
        Grafo g = null;
        try {
            FileReader arq = new FileReader("Mapa.txt");
            BufferedReader br = new BufferedReader(arq);
            int qtde = qtde_vertices();
            g = new Grafo(qtde);
            String linha = br.readLine();
            while (linha != null) {
                if (linha.equals("---")){
                    vertice = false;
                } else {
                    if (vertice){ // se for vertice
                        String[] linha_splitada = linha.split(",");
                        String nome = linha_splitada[0];
                        boolean posto;
                        if (Integer.parseInt(linha_splitada[1]) == 1){
                            posto = true;
                        } else {
                            posto = false;
                        }
                        g.adicionaVertice(nome, posto);
                    } else { // se for aresta
                        String[] linha_splitada = linha.split(",");
                        int indice0 = g.retornaIndiceNomeVertice(linha_splitada[0]);
                        int indice1 = g.retornaIndiceNomeVertice(linha_splitada[1]);
                        int peso = Integer.parseInt(linha_splitada[2]);
                        g.adicionaAresta(indice0, indice1, peso);
                    }
                }
                linha = br.readLine();
            }
        } catch (IOException ioe){
            System.out.println("Erro na leitura do arquivo");
            System.exit(0);
        }
        return g;
    }
    
    private static int qtde_vertices() throws IOException{
        FileReader arq = new FileReader("Mapa.txt");
        BufferedReader br = new BufferedReader(arq);
        String linha = br.readLine();
        int cont = 0;
        while (!linha.equals("---")) {
            cont++;
            linha = br.readLine();
        }
        br.close();
        arq.close();
        return cont;
    }
    
}
