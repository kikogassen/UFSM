/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ibd.transaction;

import ibd.Table;
import static ibd.transaction.Instruction.WRITE;
import java.util.ArrayList;

/**
 *
 * @author pccli
 */
public class Item {

    public Table table;
    public long primaryKey;

    public LockTable lockTable;

    ArrayList<Lock> locks = new ArrayList<>();

    public Item(LockTable lockTable, Table table, long pk) {
        this.table = table;
        primaryKey = pk;
        this.lockTable = lockTable;
    }

    public Transaction addToQueue(Transaction t, Instruction instruction) {
 

        if (!alreadyInQueue(t, instruction.getMode())) {
            
            ArrayList cycleList = createDependencies(t);
            boolean needToAbort = false;
            //estratégia de detecção de deadlock
            needToAbort = (cycleList != null);
            
            /*
            //estratégia de prevenção de deadlock wait-die
            needToAbort = isYounger(t, instruction.getMode());
            
            //estratégia de prevenção de deadlock wound-wait
            Transaction toAbort = getYounger(t, instruction.getMode());
            needToAbort = false;
            needToAbort = (toAbort!=null);
            */
            
            Lock l = new Lock(t, instruction.getMode());
            locks.add(l);
            instruction.setItem(this);
            if (needToAbort)
                return choseTransaction(cycleList);
                //return t;
                //return null;
                //return toAbort;
        }

        return null;

    }

    private boolean alreadyInQueue(Transaction t, int mode){
        for (int i = 0; i < locks.size(); i++) {
            Lock l = locks.get(i);
            if (l.transaction.equals(t)) {
                if (mode == l.mode || l.mode==WRITE) {
                return true;
            }
        }
        }
        return false;
    } 
    
    
    //wait-die
    private boolean isYounger(Transaction t, int mode){
        for (int i = 0; i < locks.size(); i++) {
            Lock l = locks.get(i);
            if (!l.transaction.equals(t)) {
                if (mode == WRITE || l.mode==WRITE) {
                if (t.getId()>l.transaction.getId())
                    return true;
            }
        }
        }
        return false;
    }
    
    //wound-wait
    private Transaction getYounger(Transaction t, int mode){
        for (int i = 0; i < locks.size(); i++) {
            Lock l = locks.get(i);
            if (!l.transaction.equals(t)) {
                if (mode == WRITE || l.mode==WRITE) {
                if (t.getId()<l.transaction.getId())
                    return l.transaction;
            }
        }
        }
        return null;
    } 
    
    public Transaction choseTransaction_(ArrayList<Transaction> transactions) {

        Transaction chosenT = transactions.get(0);
        for (int i = 1; i < transactions.size(); i++) {
            Transaction t = transactions.get(i);
            int missingChosen = chosenT.getInstructionsSize() - chosenT.getCurrentInstructionIndex();
            int missing = t.getInstructionsSize() - t.getCurrentInstructionIndex();
            if (missing > missingChosen) {
                chosenT = t;
            } else if (missing == missingChosen) {
                if (t.getCurrentInstructionIndex() < chosenT.getCurrentInstructionIndex()) {
                    chosenT = t;
                }
            }

        }
        return chosenT;
    }
    
    public Transaction choseTransaction(ArrayList<Transaction> transactions) {

        Transaction chosenT = transactions.get(0);
        for (int i = 1; i < transactions.size(); i++) {
            Transaction t = transactions.get(i);
            if (t.getId() > chosenT.getId()) {
                chosenT = t;
            }

        }
        return chosenT;
    }

    public void removeTransaction(Transaction t) {

        for (int i = locks.size() - 1; i >= 0; i--) {
            Lock lock = locks.get(i);
            if (lock.transaction.equals(t)) {
                locks.remove(i);
            }

        }

    }

    public void printLocks() {
        System.out.print("Item:" + SimulatedIterations.getChar((int) primaryKey) + "=>");
        for (int i = 0; i < locks.size(); i++) {
            Lock lock = locks.get(i);
            System.out.print(lock.transaction.getId() + ":" + Instruction.getModeType(lock.mode));

        }
        System.out.println("");

    }

    public boolean canBeLockedBy(Transaction t) {
        int currentMode = t.getCurrentInstruction().getMode();
        for (int i = 0; i < locks.size(); i++) {
            Lock l = locks.get(i);
            if (l.transaction.equals(t)) {
                return true;
            }
            if (l.mode == Instruction.WRITE) {
                return false;
            }
            if (currentMode == Instruction.WRITE) {
                return false;
            }
        }
        System.out.println("não deveria chegar aqui");
        return false;
    }

    private ArrayList createDependencies(Transaction t) {
        ArrayList cycleList = null;
        int currentMode = t.getCurrentInstruction().getMode();
        for (int i = 0; i < locks.size(); i++) {
            Lock l = locks.get(i);
            if (!t.equals(l.transaction))
            if (l.mode == Instruction.WRITE || currentMode == Instruction.WRITE) {
                ArrayList list = lockTable.addDependency(t, l.transaction);
                if (list != null) {
                    cycleList = list;
                }
            }
        }
        return cycleList;
    }

}
