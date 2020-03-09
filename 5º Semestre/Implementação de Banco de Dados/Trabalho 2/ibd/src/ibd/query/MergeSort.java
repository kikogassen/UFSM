/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ibd.query;

import java.util.ArrayList;

/**
 *
 * @author kikog
 */
public class MergeSort implements Operation {

    private Operation os1, os2;
    private ArrayList<TableTuple> listTuple;
    private int actualIndex;

    public MergeSort(Operation os1, Operation os2) {
        this.os1 = os1;
        this.os2 = os2;
    }

    @Override
    public void open() throws Exception {
        listTuple = new ArrayList<>();
        actualIndex = 0;
        os1.open();
        os2.open();
        TableTuple t1 = null;
        TableTuple t2 = null;
        while (true) {
            if (t1 == null && t2 == null) {
                if (os1.hasNext()) t1 = (TableTuple) os1.next(); else break;
                if (os2.hasNext()) t2 = (TableTuple) os2.next(); else break;
            } else if (t1.primaryKey == t2.primaryKey) {
                TableTuple result = new TableTuple();
                result.primaryKey = t1.primaryKey;
                result.content = t1.content + " " + t2.content;
                listTuple.add(result);
                if (os1.hasNext()) t1 = (TableTuple) os1.next(); else break;
                if (os2.hasNext()) t2 = (TableTuple) os2.next(); else break;
            } else if (t1.primaryKey > t2.primaryKey) {
                if (os2.hasNext()) t2 = (TableTuple) os2.next(); else break;
            } else {
                if (os1.hasNext()) t1 = (TableTuple) os1.next(); else break;
            }
        }
        os1.close();
        os2.close();
    }

    @Override
    public Tuple next() throws Exception {
        int actualIndex_ = actualIndex;
        actualIndex++;
        if (actualIndex_ >= listTuple.size()) {
            throw new Exception("No records after this point");
        }
        return listTuple.get(actualIndex_);
    }

    @Override
    public boolean hasNext() throws Exception {
        return actualIndex < listTuple.size();
    }

    @Override
    public void close() throws Exception {

    }

}
