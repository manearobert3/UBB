import mpi.MPI;
import mpi.MPIException;

import javax.sound.midi.Receiver;
import java.util.Arrays;


public class Main {
    public static void main(String[] args) throws MPIException ,InterruptedException {

        MPI.Init(args);
        int myRank = MPI.COMM_WORLD.Rank();
        int worldSize = MPI.COMM_WORLD.Size();

        DSMNode dsmNode = new DSMNode(
                Arrays.asList("A", "B", "C"),
                Arrays.asList(0, 1, 2)
        );

        Thread receiver = new Thread(new ReceiverThread(dsmNode));
        receiver.start();

        if (myRank == 0){
            // sub to all variables

            dsmNode.subscribe("A");
            dsmNode.subscribe("B");
            dsmNode.subscribe("C");
            Thread.sleep(1000);

            // Compare & Swap on A: if it's 0, set to 10
            dsmNode.compareAndSwap("A", 0, 10);
            Thread.sleep(1000);

            // Compare & Swap on C: if it's 2, set to 30
            dsmNode.compareAndSwap("C", 2, 30);
            Thread.sleep(1000);

            // Compare & Swap on B: if it's 1, set to 999
            dsmNode.compareAndSwap("B", 1, 999);
            Thread.sleep(1000);

            // Done, close
            dsmNode.close();
            Thread.sleep(500);
            System.out.println("Rank " + MPI.COMM_WORLD.Rank() + " waiting for receiver to finish.");
            receiver.join();
            System.out.println("Rank " + MPI.COMM_WORLD.Rank() + " finished waiting for receiver.");
        }
        else if (myRank == 1){
            // sub to only A
            dsmNode.subscribe("A");
            Thread.sleep(5000);

            // wait for close
            System.out.println("Rank " + MPI.COMM_WORLD.Rank() + " waiting for receiver to finish.");
            receiver.join();
            System.out.println("Rank " + MPI.COMM_WORLD.Rank() + " finished waiting for receiver.");
        }
        else if (myRank == 2){
            // sub to only B
            dsmNode.subscribe("B");
            Thread.sleep(8000);

            dsmNode.compareAndSwap("B", 1, 500);
            Thread.sleep(3000);

            System.out.println("Rank " + MPI.COMM_WORLD.Rank() + " waiting for receiver to finish.");
            receiver.join();
            System.out.println("Rank " + MPI.COMM_WORLD.Rank() + " finished waiting for receiver.");
        }
        System.out.println("Rank " + myRank + " finalizing.");
        MPI.Finalize();
    }
}