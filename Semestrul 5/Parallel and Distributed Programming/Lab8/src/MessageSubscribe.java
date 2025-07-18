public class MessageSubscribe extends BaseMessage{
    public String variableName;
    public int senderRank;

    public MessageSubscribe(String variableName, int senderRank){
        this.variableName = variableName;
        this.senderRank = senderRank;
    }
}
