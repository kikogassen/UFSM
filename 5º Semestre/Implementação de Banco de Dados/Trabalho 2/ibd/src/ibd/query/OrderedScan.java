/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ibd.query;

import ibd.Table;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

/**
 *
 * @author kikog
 */
public class OrderedScan implements Operation{

    private Operation op;
    private ArrayList<TableTuple> listTuple;
    private int actualIndex;
    
    public OrderedScan(Operation op){
        this.op = op;
    }
    
    @Override
    public void open() throws Exception {
        listTuple = new ArrayList<>();
        op.open();
        while (op.hasNext()){
            TableTuple tuple = (TableTuple) op.next();
            listTuple.add(tuple);
        }
        op.close();
        Collections.sort(listTuple, (TableTuple tuple1, TableTuple tuple2) -> tuple1.primaryKey > tuple2.primaryKey ? 1 : tuple1.primaryKey < tuple2.primaryKey ? -1 : 0);
        actualIndex = 0;
    }

    @Override
    public Tuple next() throws Exception {
        int actualIndex_ = actualIndex;
        actualIndex++;
        if (actualIndex_>=listTuple.size()){
            throw new Exception("No records after this point");
        }
        return listTuple.get(actualIndex_);
    }

    @Override
    public boolean hasNext() throws Exception {
        return actualIndex<listTuple.size();
    }

    @Override
    public void close() throws Exception {
        
    }
    
}
