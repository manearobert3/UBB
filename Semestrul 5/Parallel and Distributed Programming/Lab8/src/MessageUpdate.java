public class MessageUpdate extends BaseMessage{
    public String variableName;
    public int newValue;

    public MessageUpdate(String variableName, int newValue) {
        this.variableName = variableName;
        this.newValue = newValue;
    }
}
