package trab_ed;

public class Vertice {
    private String nome;
    private boolean posto;

    public Vertice(String nome, boolean posto) {
        this.nome = nome;
        this.posto = posto;
    }

    public boolean isPosto() {
        return posto;
    }

    public void setPosto(boolean posto) {
        this.posto = posto;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }
}
