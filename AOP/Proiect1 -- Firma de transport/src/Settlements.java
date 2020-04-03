abstract class BaseSettlement {
    private String name;
    private int size;

    BaseSettlement() {
        name = "";
        size = 0;
    }

    BaseSettlement(String name) {
        this.name = name;
        size = 0;
    }

    BaseSettlement(String name, int size) {
        this.name = name;
        this.size = size;
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

class Hamlet extends BaseSettlement {
}

class Village extends BaseSettlement {
}

class Town extends BaseSettlement {
}

class City extends BaseSettlement {
}