package data.settlements;

public abstract class BaseSettlement {
    private static int index;
    private String name;
    private int size;

    BaseSettlement() {
        name = "";
        size = 0;
        index++;
    }

    BaseSettlement(String name) {
        this.name = name;
        size = 0;
        index++;
    }

    BaseSettlement(String name, int size) {
        this.name = name;
        this.size = size;
        index++;
    }

    BaseSettlement(BaseSettlement other) {
        this.name = other.name;
        this.size = other.size;
    }

    @Override
    public void finalize() {
        index--;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }
}
