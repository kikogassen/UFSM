/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ibd.transaction.log;

import ibd.Table;
import ibd.transaction.SimulatedIterations;
import ibd.transaction.Transaction;
import java.io.RandomAccessFile;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;

/**
 *
 * @author pccli
 */
public class Logger {

    ArrayList<Entry> entries = new ArrayList();
    String file;
    int start = 0;

    RandomAccessFile log;

    public Logger(String folder, String name) throws Exception {

        Path path = Paths.get(folder);
        Files.createDirectories(path);

        file = folder + "\\" + name;
        log = new RandomAccessFile(file, "rw");

    }

    public void transactionStart(Transaction transaction) throws Exception {

        transaction.setLogger(this);

        StartEntry entry = new StartEntry();
        entry.setTransactionId(transaction.getId());
        entries.add(entry);
        writeLog();
    }

    public void transactionCommit(Transaction transaction) throws Exception {
        CommitEntry entry = new CommitEntry();
        entry.setTransactionId(transaction.getId());
        entries.add(entry);
        writeLog();
    }

    public void transactionAbort(Transaction transaction) throws Exception {
        AbortEntry entry = new AbortEntry();
        entry.setTransactionId(transaction.getId());
        entries.add(entry);
        writeLog();
    }

    public void transactionWrite(Transaction transaction, Table table, long pk, String oldValue, String newValue) throws Exception {
        WriteEntry entry = new WriteEntry();
        entry.table = table;
        entry.pk = pk;
        entry.oldValue = oldValue;
        entry.newValue = newValue;
        entry.setTransactionId(transaction.getId());
        entries.add(entry);
        writeLog();
    }

    public void writeLog() throws Exception {

        for (int x = start; x < entries.size(); x++) {
            log.writeBytes(entries.get(x).write());
            log.writeBytes(System.lineSeparator());
        }
        start = entries.size();

    }

    public void recover() throws Exception {

        readLog();

        recover1();

        clear();

    }

    private void readLog() throws Exception {
        RandomAccessFile readLog = new RandomAccessFile(file, "rw");

        try {
            String line = readLog.readLine();
            Entry entry = null;
            while (line != null) {
                if (line.charAt(0) == 'C') {
                    entry = new CommitEntry();
                } else if (line.charAt(0) == 'A') {
                    entry = new AbortEntry();
                } else if (line.charAt(0) == 'S') {
                    entry = new StartEntry();
                } else {
                    entry = new WriteEntry();
                }

                entry.read(line);
                entries.add(entry);

                line = readLog.readLine();
            }

        } finally {
            readLog.close();
        }

    }

    public void clear() throws Exception {
        new RandomAccessFile(file, "rw").setLength(0);
        entries.clear();
    }

    private void recover1() throws Exception {

        //primeiro vê todas as transactions envolvidas no log
        ArrayList<Integer> transactionsEnvolved = new ArrayList<>();
        for (Entry e : entries) {
            if (!transactionsEnvolved.contains(e.getTransactionId())) {
                transactionsEnvolved.add(e.getTransactionId());
            }
        }

        //lista de tabelas pra dar flush
        ArrayList<Table> tablesEnvolved = new ArrayList<>();

        //lista de transactions pra dar undo
        ArrayList<Integer> transactionsForUndo = new ArrayList<>();

        //primeiro é undo
        for (Integer transactionId : transactionsEnvolved) {
            boolean hasStart = false, hasCommit = false;

            for (Entry e : entries) {

                if (e.getTransactionId() != transactionId) {
                    continue;
                }

                if (e instanceof StartEntry) {
                    hasStart = true;
                } else if (e instanceof CommitEntry) {
                    hasCommit = true;
                }
            }
            if (hasStart && !hasCommit) {
                transactionsForUndo.add(transactionId);
            }
        }

        //undo tem que fazer do mais recente pro mais antigo, então navega na lista ao contrário
        for (int i = entries.size() - 1; i >= 0; i--) {
            Entry e = entries.get(i);
            if (transactionsForUndo.contains(e.getTransactionId()) && e instanceof WriteEntry) {
                WriteEntry writeEntry = (WriteEntry) e;
                System.out.println("undo table: " + Table.getTableFolder(writeEntry.table.key) + Table.getTableFile(writeEntry.table.key) + "," + String.valueOf(SimulatedIterations.getChar((int) writeEntry.pk)) + "," + writeEntry.oldValue);
                writeEntry.table.updateRecord(writeEntry.pk, writeEntry.oldValue);
                if (!tablesEnvolved.contains(writeEntry.table)) {
                    tablesEnvolved.add(writeEntry.table);
                }
            }
        }

        //lista de transactions pra dar redo
        ArrayList<Integer> transactionsForRedo = new ArrayList<>();

        //depois é redo
        for (Integer transactionId : transactionsEnvolved) {
            boolean hasStart = false, hasCommit = false;

            for (Entry e : entries) {

                if (e.getTransactionId() != transactionId) {
                    continue;
                }

                if (e instanceof StartEntry) {
                    hasStart = true;
                } else if (e instanceof CommitEntry) {
                    hasCommit = true;
                }
            }
            if (hasStart && hasCommit) {
                transactionsForRedo.add(transactionId);
            }
        }

        //redo é na ordem normal
        for (Entry e : entries) {
            if (transactionsForRedo.contains(e.getTransactionId()) && e instanceof WriteEntry) {
                WriteEntry writeEntry = (WriteEntry) e;
                System.out.println("redo table: " + Table.getTableFolder(writeEntry.table.key) + Table.getTableFile(writeEntry.table.key) + "," + String.valueOf(SimulatedIterations.getChar((int) writeEntry.pk)) + "," + writeEntry.newValue);
                writeEntry.table.updateRecord(writeEntry.pk, writeEntry.newValue);
                if (!tablesEnvolved.contains(writeEntry.table)) {
                    tablesEnvolved.add(writeEntry.table);
                }
            }
        }

        //dá os flush
        for (Table t : tablesEnvolved) {
            t.flushDB();
            System.out.println("flushing table " + Table.getTableFolder(t.key) + Table.getTableFile(t.key));
        }
    }
}
