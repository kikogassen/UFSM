/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ibd.transaction.log;

import ibd.Record;
import ibd.transaction.*;
import ibd.Table;
import ibd.Utils;
import static ibd.transaction.Instruction.READ;
import static ibd.transaction.Instruction.WRITE;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author pccli
 */
public class Main {

    public void reset(String folder, String file) throws Exception {

        Manager manager = new Manager();
        manager.clearLog();

        Utils.createTable(folder, file, 1800, true, 1);

    }

    public void recover() throws Exception {

        Manager manager = new Manager();
        manager.recoverFromLog();

    }

    public void testConsistency(String folder, String file) throws Exception {

        Table table1 = Table.getTable(folder, file);

        for (long i = 1; i < 10; i++) {
            Record r = table1.getRecord(i);
            char c = SimulatedIterations.getChar((int) r.getPrimaryKey());
            System.out.println(c + " - " + r.getContent());
        }

    }

    public void prova3_1(String folder, String file, int errorStep) throws Exception {
        Table table1 = Table.getTable(folder, file);

        Transaction t1 = new Transaction();
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "1"));
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('C'), null));

        Transaction t2 = new Transaction();
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('B'), null));
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "2"));

        Transaction t3 = new Transaction();
        t3.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('C'), null));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('D'), "3"));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('E'), "10"));

        Transaction t4 = new Transaction();
        t4.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('D'), null));
        t4.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('E'), "4"));

        Transaction t5 = new Transaction();
        t5.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('E'), null));
        t5.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));

        SimulatedIterations simulation = new SimulatedIterations();
        simulation.addTransaction(t1);
        simulation.addTransaction(t2);
        simulation.addTransaction(t3);
        simulation.addTransaction(t4);
        simulation.addTransaction(t5);
        simulation.run(errorStep);

    }

    public void prova3_2(String folder, String file, int errorStep) throws Exception {
        Table table1 = Table.getTable(folder, file);

        Transaction t1 = new Transaction();
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "1"));
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('G'), null));

        Transaction t2 = new Transaction();
        t2.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('B'), null));
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "2"));

        Transaction t3 = new Transaction();
        t3.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('C'), null));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('D'), "3"));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('G'), "9"));

        Transaction t4 = new Transaction();
        t4.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('D'), null));
        t4.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('F'), "4"));

        Transaction t5 = new Transaction();
        t5.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('E'), null));
        t5.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('F'), null));
        t5.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "5"));

        SimulatedIterations simulation = new SimulatedIterations();
        simulation.addTransaction(t1);
        simulation.addTransaction(t2);
        simulation.addTransaction(t3);
        simulation.addTransaction(t4);
        simulation.addTransaction(t5);
        simulation.run(errorStep);

    }

    public void prova3_3(String folder, String file, int errorStep) throws Exception {
        Table table1 = Table.getTable(folder, file);

        Transaction t1 = new Transaction();
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "3"));
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('D'), null));

        Transaction t2 = new Transaction();
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "1"));
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "4"));

        Transaction t3 = new Transaction();
        t3.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('C'), null));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "5"));
        //t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "7"));

        Transaction t4 = new Transaction();
        t4.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t4.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "6"));

        SimulatedIterations simulation = new SimulatedIterations();
        simulation.addTransaction(t1);
        simulation.addTransaction(t2);
        simulation.addTransaction(t3);
        simulation.addTransaction(t4);

        simulation.run(errorStep);

    }

    public void prova3_4(String folder, String file, int errorStep) throws Exception {
        Table table1 = Table.getTable(folder, file);

        Transaction t1 = new Transaction();
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "3"));
        t1.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('D'), null));

        Transaction t2 = new Transaction();
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "1"));
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "4"));

        Transaction t3 = new Transaction();
        t3.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('C'), null));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "5"));
        //t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "7"));

        Transaction t4 = new Transaction();
        t4.addInstruction(new Instruction(table1, Instruction.READ, SimulatedIterations.getValue('A'), null));
        t4.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('D'), "6"));

        SimulatedIterations simulation = new SimulatedIterations();
        simulation.addTransaction(t1);
        simulation.addTransaction(t2);
        simulation.addTransaction(t3);
        simulation.addTransaction(t4);

        simulation.run(errorStep);

    }
    
     public void test3(String folder, String file, int errorStep) throws Exception {

        Table table1 = Table.getTable(folder, file);

        Transaction t1 = new Transaction();
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('A'), "change A=10"));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "change B=10"));
        t1.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('D'), "change D=10"));

        Transaction t2 = new Transaction();
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('B'), "change B=20"));
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "change C=30"));
        t2.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('D'), "change D=0"));

        Transaction t3 = new Transaction();
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('C'), "change C=40"));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('D'), "change D=30"));
        t3.addInstruction(new Instruction(table1, Instruction.WRITE, SimulatedIterations.getValue('F'), "change F=30"));

        SimulatedIterations simulation = new SimulatedIterations();
        simulation.addTransaction(t1);
        simulation.addTransaction(t2);
        simulation.addTransaction(t3);
        simulation.run(errorStep);

        table1.flushDB();

    }


    public static void main(String[] args) {
        Main m = new Main();
        try {
            //cada teste tem duas execuções independentes: etapa 1 e etapa 2 

            /**
             * ******** inicio da etapa 1 ***************
             */
            //comece resetando a(s) tabela(s) envolvida(s)
            //m.reset("c:\\teste\\ibd", "t1.ibd");

            //rode o simulador usando algum caso de teste contendo transações e um passo de erro. 
            //para simplificar, os casos de teste abaixo fazem todos referência à uma mesma tabela.
            //mas é importante que a recuperação funcione mesmo com mais tabelas envolvidas.
            //m.prova3_1("c:\\teste\\ibd", "t1.ibd", 13);
            //m.prova3_2("c:\\teste\\ibd","t1.ibd", 8);
            //m.prova3_3("c:\\teste\\ibd","t1.ibd", 8);
            //m.prova3_4("c:\\teste\\ibd","t1.ibd", 8);
            //m.test3("c:\\teste\\ibd","t1.ibd", 8);
            /**
             * ******** fim da etapa 1 ***************
             */

            /**
             * ******** inicio da etapa 2 ***************
             */
            //execute a recuperação
            m.recover();
            //a função abaixo verifica como ficaram os primeiros registros de uma tabela após a recuperação
            //m.testConsistency("c:\\teste\\ibd","t1.ibd");
            /**
             * ******** fim da etapa 2 ***************
             */
        } catch (Exception ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

}
