import mpi.MPI;

import java.util.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class DSMNode
{

    private final Lock lock = new ReentrantLock();

    private final Map<String, Integer> localVariables = new HashMap<>();

    private final Map<String, Set<Integer>> subscriptionMap = new HashMap<>();

    public DSMNode(List<String> variables, List<Integer> initialValues) {
        for (int i = 0; i < variables.size(); i++) {
            localVariables.put(variables.get(i), initialValues.get(i));
            subscriptionMap.put(variables.get(i), new HashSet<>());
        }
    }

    public void subscribe(String varName){
        lock.lock();
        try{
            subscriptionMap.get(varName).add(MPI.COMM_WORLD.Rank());
        } finally {
            lock.unlock();
        }

        MessageSubscribe msg = new MessageSubscribe(varName, MPI.COMM_WORLD.Rank());
        broadcastMessage(msg);
    }


    public void compareAndSwap(String varName, int oldValue, int newValue) {
        lock.lock();
        try{
            int currentVal = localVariables.get(varName);
            if (currentVal == oldValue) {
                localVariables.put(varName, newValue);
                broadcastUpdate(varName,newValue);
            }
        } finally {
            lock.unlock();
        }
    }

    public void setLocal(String varName, int newValue){
        lock.lock();
        try{
            localVariables.put(varName, newValue);
        }
        finally {
            lock.unlock();
        }
    }

    public void update(String varName, int newValue){
        lock.lock();
        try{
            localVariables.put(varName, newValue);
        } finally{
            lock.unlock();
        }
        broadcastUpdate(varName, newValue);
    }

    public void handleSubscription(String varName, int rank){
        lock.lock();
        try{
            subscriptionMap.get(varName).add(rank);
        }
        finally {
            lock.unlock();
        }
    }
    public void handleUpdate(String varName, int newValue){
        lock.lock();
        try{
            localVariables.put(varName, newValue);
        } finally {
            lock.unlock();
        }
        System.out.println("Rank " + MPI.COMM_WORLD.Rank() +
                " updated " + varName + " to " + newValue);
    }

    public Map<String,Integer> getLocalVariables(){
        return localVariables;
    }

    private void broadcastMessage(BaseMessage msg){
        int worldSize = MPI.COMM_WORLD.Size();
        for(int i = 0; i<worldSize; i++){
            if (i == MPI.COMM_WORLD.Rank()){
                continue; // dont send data to self
            }
            MPI.COMM_WORLD.Send(new Object[] {msg}, 0, 1, MPI.OBJECT, i, 101);
        }
    }

    private void broadcastUpdate(String varName, int newValue){
        Set<Integer> subscribers;
        lock.lock();
        try{
            subscribers = new HashSet<>(subscriptionMap.get(varName));
        } finally{
            lock.unlock();
        }
        for (int rank: subscribers){
            if (rank == MPI.COMM_WORLD.Rank()){
                continue;
            }
            MessageUpdate update = new MessageUpdate(varName, newValue);
            MPI.COMM_WORLD.Send(new Object[] { update }, 0, 1, MPI.OBJECT, rank, 102);
        }
    }

    public void close() {
        int size = MPI.COMM_WORLD.Size();
        for (int i = 0; i < size; i++) {
            MessageClose msg = new MessageClose();
            MPI.COMM_WORLD.Send(new Object[] { msg }, 0, 1, MPI.OBJECT, i, 103);
        }
    }

}
