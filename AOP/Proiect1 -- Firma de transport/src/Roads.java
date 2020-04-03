abstract class BaseRoad {
    private static int index;
    private String name;
    private BaseSettlement from, to;
    private int length;

    BaseRoad(BaseSettlement from, BaseSettlement to) {
        name = "";
        this.from = from;
        this.to = to;
        length = 0;
    }

    BaseRoad(BaseSettlement from, BaseSettlement to, int length) {
        name = "";
        this.from = from;
        this.to = to;
        this.length = length;
    }

    BaseRoad(String name, BaseSettlement from, BaseSettlement to, int length) {
        this.name = name;
        this.from = from;
        this.to = to;
        this.length = length;
    }

    @Override
    public void finalize() {
        index--;
    }

    public int getLength() {
        return length;
    }

    public void setLength(int length) {
        this.length = length;
    }

    public BaseSettlement getFrom() {
        return from;
    }

    public void setFrom(BaseSettlement from) {
        this.from = from;
    }

    public BaseSettlement getTo() {
        return to;
    }

    public void setTo(BaseSettlement to) {
        this.to = to;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    protected void flip() {
        BaseSettlement aux = from;
        from = to;
        to = aux;
    }
}

class RuralRoad extends BaseRoad {
    RuralRoad(BaseSettlement from, BaseSettlement to) {
        super(from, to);
    }

    RuralRoad(BaseSettlement from, BaseSettlement to, int length) {
        super(from, to, length);
    }

    RuralRoad(String name, BaseSettlement from, BaseSettlement to, int length) {
        super(name, from, to, length);
    }
}

class DistrictRoad extends BaseRoad {
    DistrictRoad(BaseSettlement from, BaseSettlement to) {
        super(from, to);
    }

    DistrictRoad(BaseSettlement from, BaseSettlement to, int length) {
        super(from, to, length);
    }

    DistrictRoad(String name, BaseSettlement from, BaseSettlement to, int length) {
        super(name, from, to, length);
    }
}

class StateHighway extends BaseRoad {
    StateHighway(BaseSettlement from, BaseSettlement to) {
        super(from, to);
    }

    StateHighway(BaseSettlement from, BaseSettlement to, int length) {
        super(from, to, length);
    }

    StateHighway(String name, BaseSettlement from, BaseSettlement to, int length) {
        super(name, from, to, length);
    }
}

class NationalHighway extends BaseRoad {
    NationalHighway(BaseSettlement from, BaseSettlement to) {
        super(from, to);
    }

    NationalHighway(BaseSettlement from, BaseSettlement to, int length) {
        super(from, to, length);
    }

    NationalHighway(String name, BaseSettlement from, BaseSettlement to, int length) {
        super(name, from, to, length);
    }
}

class TruckOnlyRoad extends BaseRoad {
    TruckOnlyRoad(BaseSettlement from, BaseSettlement to) {
        super(from, to);
    }
}
