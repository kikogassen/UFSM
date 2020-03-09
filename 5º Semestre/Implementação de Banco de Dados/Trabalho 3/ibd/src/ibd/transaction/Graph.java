/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ibd.transaction;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Iterator;

/**
 *
 * @author kikog
 */
public class Graph {

    ArrayList<Vertex> vertexList = new ArrayList<>();
    ArrayList<Edge> edgeList = new ArrayList<>();
    Vertex nullVertex = new Vertex(null);

    public Graph(ArrayList<Transaction> listTransactions) {
        for (Transaction t : listTransactions) {
            addVertex(t);
        }
    }

    private void addVertex(Transaction t) {
        vertexList.add(new Vertex(t));
    }

    public void addEdge(Transaction source, Transaction destiny) {
        Edge e = new Edge(getVertexByTransaction(source), getVertexByTransaction(destiny));
        if (!hasEdge(source, destiny)) {
            edgeList.add(e);
        }
    }

    private boolean hasEdge(Transaction source, Transaction destiny) {
        for (Edge e : edgeList) {
            if (e.getSource().getTransaction().equals(source) && e.getDestiny().getTransaction().equals(destiny)) {
                return true;
            }
        }
        return false;
    }

    private Vertex getVertexByTransaction(Transaction transaction) {
        for (Vertex v : vertexList) {
            if (v.getTransaction().equals(transaction)) {
                return v;
            }
        }
        return null;
    }

    public Transaction hasCycle() {
        ArrayList<Vertex> whiteList = new ArrayList<>();
        ArrayList<Vertex> greyList = new ArrayList<>();
        ArrayList<Vertex> blackList = new ArrayList<>();
        Hashtable<Vertex, Vertex> navigationMap = new Hashtable<>();
        initializeMap(navigationMap);
        initializeWhiteList(whiteList);
        while (!whiteList.isEmpty()) {
            Vertex vertex = whiteList.get(0);
            Vertex resp = dfs(vertex, whiteList, greyList, blackList, navigationMap);
            if (resp != null) {
                Transaction younger = getYoungerTransaction(navigationMap, resp);
                clearEdgesWithTransaction(younger);
                return younger;
            }
        }
        return null;
    }

    private void clearEdgesWithTransaction(Transaction t) {
        for (int i = edgeList.size() - 1; i >= 0; i--) {
            Edge e = edgeList.get(i);
            if (e.hasTransaction(t)) {
                edgeList.remove(e);
            }
        }
    }

    private Transaction getYoungerTransaction(Hashtable navigationMap, Vertex resp) {
        ArrayList<Vertex> listVertexCycle = new ArrayList<>();
        Vertex tmp = null;
        while (tmp == null || !listVertexCycle.contains(tmp)) {
            tmp = (Vertex) navigationMap.get(resp);
            listVertexCycle.add(resp);
            resp = tmp;
        }

        Transaction younger = null;
        for (Vertex v : listVertexCycle) {
            if (younger == null || v.getTransaction().getId() > younger.getId()) {
                younger = v.getTransaction();
            }
        }
        return younger;
    }

    private Vertex dfs(Vertex vertex, ArrayList whiteList, ArrayList greyList, ArrayList blackList, Hashtable navigationMap) {
        if (blackList.contains(vertex)) {
            return null;
        }
        if (greyList.contains(vertex)) {
            return vertex;
        }
        greyList.add(vertex);
        whiteList.remove(vertex);
        ArrayList<Vertex> vertexDestiny = getExitVertex(vertex);
        for (Vertex v : vertexDestiny) {
            navigationMap.put(v, vertex);
            Vertex resp = dfs(v, whiteList, greyList, blackList, navigationMap);
            if (resp != null) {
                return resp;
            }
        }
        greyList.remove(vertex);
        blackList.add(vertex);
        return null;
    }

    private ArrayList<Vertex> getExitVertex(Vertex vertex) {
        ArrayList<Vertex> listExitVertex = new ArrayList<>();
        for (Edge e : edgeList) {
            if (e.getSource().equals(vertex)) {
                listExitVertex.add(e.getDestiny());
            }
        }
        return listExitVertex;
    }

    private void initializeMap(Hashtable navigationMap) {
        for (Vertex v : vertexList) {
            navigationMap.put(v, nullVertex);
        }
    }

    private void initializeWhiteList(ArrayList whiteList) {
        for (Vertex v : vertexList) {
            whiteList.add(v);
        }
    }
}
