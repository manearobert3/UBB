import mpi.MPI;

public class ReceiverThread implements Runnable{

    private final  DSMNode dsmNode;
    public ReceiverThread(DSMNode dsmNode) {
        this.dsmNode = dsmNode;
    }

    @Override
    public void run() {
        while (true){
            Object[] buf = new Object[1];
            MPI.COMM_WORLD.Recv(buf, 0, 1, MPI.OBJECT, MPI.ANY_SOURCE, MPI.ANY_TAG);
            BaseMessage msg = (BaseMessage) buf[0];

            if (msg instanceof MessageClose){
                System.out.println("Rank " + MPI.COMM_WORLD.Rank() + " received CloseMessage. Stopping receiver...");
                break;
            }
            else if (msg instanceof MessageSubscribe msgSubscribe){
                dsmNode.handleSubscription(msgSubscribe.variableName, msgSubscribe.senderRank);
                System.out.println("Rank " + MPI.COMM_WORLD.Rank() +
                        " acknowledges subscription to " + msgSubscribe.variableName + " from rank " + msgSubscribe.senderRank);
            }
            else if (msg instanceof MessageUpdate msgUpdate){
                dsmNode.handleUpdate(msgUpdate.variableName, msgUpdate.newValue);
            }
        }
        System.out.println("Rank " + MPI.COMM_WORLD.Rank() + " final local state: " + dsmNode.getLocalVariables());

    }
}
