package data.roads;

import data.settlements.BaseSettlement;

public class RuralRoad extends BaseRoad {
    RuralRoad(BaseSettlement from, BaseSettlement to) {
        super(from, to);
    }

    RuralRoad(BaseSettlement from, BaseSettlement to, int length) {
        super(from, to, length);
    }

    public RuralRoad(String name, BaseSettlement from, BaseSettlement to, int length) {
        super(name, from, to, length);
    }

    @Override
    public BaseRoad flip() {
        return new RuralRoad(super.name, super.to, super.from, super.length);
    }
}
