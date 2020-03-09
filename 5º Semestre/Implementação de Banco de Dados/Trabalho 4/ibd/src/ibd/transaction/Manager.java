/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ibd.transaction;

import ibd.Record;
import ibd.transaction.log.Logger;
import java.io.FileNotFoundException;
import java.util.ArrayList;


/**
 *
 * @author pccli
 */
public class Manager {

    LockTable lockTable = new LockTable();
    
    Logger logger;

    static int cont = 0;
    
    ArrayList<Transaction> activeTransactions = new ArrayList<>();
    
    public Manager() throws Exception{
        logger = new Logger("c:\\teste\\ibd","log.txt");
    }
    
    public void recoverFromLog() throws Exception{
        logger.recover();
    }
    
    public void clearLog() throws Exception{
        logger.clear();
    }
    
    
    public Record processNextInstruction(Transaction t) throws Exception {
        
        if (!activeTransactions.contains(t)){
            activeTransactions.add(t);
            logger.transactionStart(t);
        }
        
        if (!t.waitingLockRelease()) {
            Transaction toAbort = lockTable.queueTransaction(t.getCurrentInstruction());
            if (toAbort!=null)
            {
                
                abort(toAbort); 
                return null;
            }
        }

        if (t.canLockCurrentInstruction()) {
            return t.processCurrentInstruction();
        }
        
        return null;

    }

    public void flushLog() throws Exception{
        logger.writeLog();
    }
    

    public void commit(Transaction t) throws Exception{
        t.commit();
        lockTable.removeTransaction(t);
        logger.transactionCommit(t);
        activeTransactions.remove(t);
    }
    
    public void abort(Transaction t) throws Exception{
        //System.out.println("Aborting "+t);
        System.out.println(SimulatedIterations.getTab(t.getId()-1)+t.getId()+" Abort");
        t.abort();
        lockTable.removeTransaction(t);
        logger.transactionAbort(t);
        activeTransactions.remove(t);
        
    }
    
    
    
    

    
}
