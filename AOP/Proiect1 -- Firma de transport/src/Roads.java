abstract class BaseRoad {
    private String name;
    private BaseSettlement from, to;
    private int length;

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
}

class RuralRoad extends BaseRoad {
}

class DistrictRoad extends BaseRoad {
}

class StateHighway extends BaseRoad {
}

class NationalHighway extends BaseRoad {
}

class TruckOnlyRoad extends BaseRoad {
}
