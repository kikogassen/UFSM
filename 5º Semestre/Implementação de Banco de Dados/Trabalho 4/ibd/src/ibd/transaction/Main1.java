/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package ibd.transaction;

import ibd.Table;
import ibd.Utils;
import ibd.transaction.log.Logger;


/**
 *
 * @author pccli
 */
public class Main1 {
    
    
    
    
    
    
    public void test1() throws Exception{
        Table table1 = Utils.createTable("c:\\teste\\ibd","t1.ibd",1000, true, 1);
        Transaction t1 = new Transaction();
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "bla"));
        
        
        Transaction t2 = new Transaction();
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('D'), null));
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('B'), null));
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "bla"));
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('H'), null));
        
        Transaction t3 = new Transaction();
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('D'), "bla"));
        t3.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('E'), null));
        t3.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('B'), null));
        
        Transaction t4 = new Transaction();
        t4.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('F'), null));
        t4.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('G'), null));
        t4.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        
        Transaction t5 = new Transaction();
        t5.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "bla"));
        t5.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('F'), "bla"));
        t5.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('G'), null));
        
        
        SimulatedIterations simulation = new SimulatedIterations();
        simulation.addTransaction(t1);
        simulation.addTransaction(t2);
        simulation.addTransaction(t3);
        simulation.addTransaction(t4);
        simulation.addTransaction(t5);
        simulation.run(100);
        
        
        
    }
    
    public void test2() throws Exception{
        Table table1 = Utils.createTable("c:\\teste\\ibd","t1.ibd",1000, true, 1);
        Transaction t1 = new Transaction();
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "bla"));
        
        Transaction t2 = new Transaction();
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('B'), null));
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "bla"));
        
        
        
        SimulatedIterations simulation = new SimulatedIterations();
        simulation.addTransaction(t1);
        simulation.addTransaction(t2);
        simulation.run(100);
        
        
        
    }
    
    
    
    public void test3() throws Exception{
        Table table1 = Utils.createTable("c:\\teste\\ibd","t1.ibd",1000, true, 1);
        Transaction t1 = new Transaction();
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('B'), null));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "bla"));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "bla"));
        
        
        Transaction t2 = new Transaction();
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('B'), null));
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('C'), null));
        
        Transaction t3 = new Transaction();
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "bla"));
        t3.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "bla"));
        
        
        SimulatedIterations simulation = new SimulatedIterations();
        simulation.addTransaction(t1);
        simulation.addTransaction(t2);
        simulation.addTransaction(t3);
        simulation.run(100);
        
        
        
    }
    
    public void test4() throws Exception{
        Table table1 = Utils.createTable("c:\\teste\\ibd","t1.ibd",1000, true, 1);
        Transaction t1 = new Transaction();
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('B'), null));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "bla"));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "bla"));
        
        
        Transaction t2 = new Transaction();
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('B'), null));
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('C'), null));
        
        Transaction t3 = new Transaction();
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "bla"));
        t3.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "bla"));
        
        Transaction t4 = new Transaction();
        t4.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "bla"));
        t4.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('F'), null));
        
        
        SimulatedIterations simulation = new SimulatedIterations();
        simulation.addTransaction(t1);
        simulation.addTransaction(t2);
        simulation.addTransaction(t3);
        simulation.addTransaction(t4);
        simulation.run(100);
        
        
        
    }
    
    public void test5() throws Exception{
        Table table1 = Utils.createTable("c:\\teste\\ibd","t1.ibd",1000, true, 1);
        Transaction t1 = new Transaction();
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "bla"));
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('D'), null));
        
        
        Transaction t2 = new Transaction();
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "ds"));
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "ds"));
        
        Transaction t3 = new Transaction();
        t3.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('C'), null));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "dd"));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "bla"));
        
        Transaction t4 = new Transaction();
        t4.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('F'), null));
        t4.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('E'), "ss"));
        
        Transaction t5 = new Transaction();
        t5.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "dsds"));
        t5.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('B'), null));
        t5.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "bla"));
        
        
        SimulatedIterations simulation = new SimulatedIterations();
        simulation.addTransaction(t1);
        simulation.addTransaction(t2);
        simulation.addTransaction(t3);
        simulation.addTransaction(t4);
        simulation.addTransaction(t5);
        simulation.run(100);
        
        
        
    }
    
    
    public static void main(String[] args) {
     Main1 m = new Main1();
        try {
            m.test1();
        } catch (Exception ex) {
            
        }
    }
    
}
